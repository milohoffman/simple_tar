/*
 * extractor.cpp
 *
 *  Created on: 20.01.2014
 *      Author: milo
 */

#include <exception>
#include <sstream>

#include <boost/scoped_array.hpp>

#include "extractor.hpp"
#include "permissions.hpp"
#include "utils.hpp"

namespace fs = boost::filesystem;

namespace {
    void checkIfPathExistsAndIsRegularFile(const fs::path& archive) {
        fs::directory_entry dirent(archive);

        if (!fs::exists(dirent.status())) {
            std::stringstream ss;
            ss << "The archive file doesn't exist: ";
            ss << archive.native();
            throw std::runtime_error(ss.str());
        }

        if (dirent.status().type() != fs::regular_file) {
            std::stringstream ss;
            ss << "The archive '" << archive.native() << "' is not a regular file";
            throw std::runtime_error(ss.str());
        }
    }

    void createOutputDirIfDoesntExist(const fs::path& dir) {
        fs::create_directories(dir);
    }
}

namespace SimpleTar {

Extractor::Extractor(const fs::path& archive, const fs::path& output_dir) : output_dir_(output_dir) {
    checkIfPathExistsAndIsRegularFile(archive);

    archive_.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    archive_.open(archive.c_str(), std::ifstream::in | std::ifstream::binary);
    throwIfNotGood(archive_, archive.native());

    createOutputDirIfDoesntExist(output_dir);
}

void Extractor::extract() {
    //TODO: make exceptions more readable
    while (!archiveEnd()) {
        EntityHeader header;

        readHeader(header);
        extractEntity(header);
    }
}

void Extractor::readHeader(EntityHeader& header) {
    readBytes(&header.type, sizeof(header.type));
    readBytes(reinterpret_cast<char *>(&header.entity_size), sizeof(header.entity_size));
    readBytes(reinterpret_cast<char *>(&header.perms), sizeof(header.perms));

    int path_len;
    readBytes(reinterpret_cast<char *>(&path_len), sizeof(path_len));

    boost::scoped_array<char> path_buf(new char[path_len]);
    readBytes(path_buf.get(), path_len);
    header.path.assign(path_buf.get(), path_len);
}

void Extractor::extractEntity(const EntityHeader& header) {
    fs::path dest = output_dir_ / fs::path(header.path);
    std::cout << "Extracting: " << dest.native() << std::endl;

    if (header.type == EntityHeader::DIRECTORY) {
        extractDirectory(header);
        return;
    }

    extractFile(header);
}

void Extractor::extractDirectory(const EntityHeader& header) {
    fs::path dir = output_dir_ / fs::path(header.path);

    fs::create_directories(dir);

    setPermissions(dir, header.perms);
}

void Extractor::extractFile(const EntityHeader& header) {
    fs::path out_path = output_dir_;
    out_path /= fs::path(header.path);

    createDirs(out_path);

    copyFileFromArchive(header, out_path);

    setPermissions(out_path, header.perms);
}

void Extractor::copyFileFromArchive(const EntityHeader& header, const boost::filesystem::path& out_path) {
    static const uint32_t CHUNK_SIZE = 4096;

    throwIfExists(out_path);

    std::ofstream outfile;
    outfile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    outfile.open(out_path.c_str(), std::ofstream::out | std::ofstream::binary);
    throwIfNotGood(outfile, out_path.native());

    boost::scoped_array<char> chunk(new char [CHUNK_SIZE]);
    uint64_t to_read = header.entity_size;

    while (to_read) {
        size_t bytes = readBytes(chunk.get(), (CHUNK_SIZE > to_read) ? to_read : CHUNK_SIZE);

        outfile.write(chunk.get(), bytes);
        to_read -= bytes;
    }

    outfile.close();
}

size_t Extractor::readBytes(char * buf, size_t bytes) {
    archive_.read(buf, bytes);

    return archive_.gcount();
}

void Extractor::createDirs(const fs::path& out_path) {
    fs::path dir = out_path;
    dir = dir.remove_filename();

    fs::create_directories(dir);
}

bool Extractor::archiveEnd() {
    //this is the consequence of ifstream's stupid interface:
    //it doesn't return eof until you started to read outbound of a file
    return archive_.peek() == std::char_traits<char>::eof();
}

} //namespace SimpleTar
