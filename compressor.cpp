/*
 * compressor.cpp
 *
 *  Created on: 19.01.2014
 *      Author: milo
 */

#include "compressor.hpp"
#include "entity_header.hpp"
#include "permissions.hpp"
#include "utils.hpp"

#include <stdint.h>
#include <algorithm>
#include <functional>

#include <boost/scoped_array.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>

namespace fs = boost::filesystem;

namespace {

void append_path(fs::path& init, const fs::path& append) {
    init /= append;
}

fs::path removeUpper(const fs::path& original) {
    std::not_equal_to<fs::path> func;
    fs::path::iterator it = std::find_if(original.begin(), original.end(), boost::bind(func, fs::path(".."), _1));

    fs::path res;
    std::for_each(it, original.end(), boost::bind(append_path, boost::ref(res), _1));

    return res;
}

}

namespace SimpleTar {

Compressor::Compressor(const fs::path& outfile) {
    throwIfExists(outfile);

    outfile_.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    outfile_.open(outfile.c_str(), std::ofstream::out | std::ofstream::binary);

    throwIfNotGood(outfile_, outfile.native());
}

void Compressor::compress(const fs::directory_entry& dirent) {
    if (dirent.status().type() == fs::regular_file)
        writeFile(dirent);
    else if (dirent.status().type() == fs::directory_file) {
        writeDirectory(dirent);
    }
}

void Compressor::writeDirectory(const boost::filesystem::directory_entry& dirent) {
    std::cout << "Compressing: " << dirent.path().native() << std::endl;

    writeHeader(dirent);
}

void Compressor::writeFile(const fs::directory_entry& dirent) {
    std::ifstream source;

    source.open(dirent.path().c_str(), std::ifstream::in | std::ifstream::binary);
    throwIfNotGood(source, dirent.path().native());

    std::cout << "Compressing: " << dirent.path().native() << std::endl;

    writeHeader(dirent);
    writeBody(source);
}

void Compressor::writeHeader(const fs::directory_entry& dirent) {
    /*
     * The header is:
     * 1 byte for type (0 - file, 1 - directory)
     * 8 bytes for size of file (0 for directory)
     * 2 bytes for permissions
     * 4 bytes for path length (as string)
     * Path length bytes for path
     * */

    char type;
    uint64_t file_size;

    if (dirent.status().type() == fs::regular_file) {
        type = EntityHeader::FILE;
        file_size = fs::file_size(dirent.path());
    } else {
        type = EntityHeader::DIRECTORY;
        file_size = 0;
    }

    writeBytes(reinterpret_cast<const char *>(&type), sizeof(type));
    writeBytes(reinterpret_cast<const char *>(&file_size), sizeof(file_size));

    permissions_t perms = getFilePermissions(dirent.path());
    writeBytes(reinterpret_cast<const char *>(&perms), sizeof(perms));

    fs::path new_path = removeUpper(dirent.path());
    int path_len = new_path.string().length();
    writeBytes(reinterpret_cast<const char *>(&path_len), sizeof(path_len));
    writeBytes(reinterpret_cast<const char *>(new_path.c_str()), path_len);
}

void Compressor::writeBody(std::ifstream& source) {
    static const uint32_t CHUNK_SIZE = 4096;

    boost::scoped_array<char> chunk(new char [CHUNK_SIZE]);
    std::streamsize size;

    do {
        source.read(chunk.get(), CHUNK_SIZE);
        size = source.gcount();

        writeBytes(chunk.get(), size);
    } while (source);
}

void Compressor::writeBytes(const char * buf, size_t bytes) {
    outfile_.write(buf, bytes);
}

}
