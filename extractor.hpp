/*
 * extractor.hpp
 *
 *  Created on: 20.01.2014
 *      Author: milo
 */

#ifndef EXTRACTOR_HPP_
#define EXTRACTOR_HPP_

#include <boost/filesystem.hpp>
#include <boost/utility.hpp>

#include <fstream>

#include "entity_header.hpp"

namespace SimpleTar {

class Extractor : boost::noncopyable {
public:
    Extractor(const boost::filesystem::path& archive,
            const boost::filesystem::path& output_dir);

    void extract();

private:
    void readHeader(EntityHeader& header);
    void extractEntity(const EntityHeader& header);
    void extractFile(const EntityHeader& header);
    void extractDirectory(const EntityHeader& header);
    size_t readBytes(char * buf, size_t bytes);
    void copyFileFromArchive(const EntityHeader&header, const boost::filesystem::path& out_path);
    void createDirs(const boost::filesystem::path& out_path);
    bool archiveEnd();

    boost::filesystem::path output_dir_;
    std::ifstream archive_;
};

} //namespace SimpleTar


#endif /* EXTRACTOR_HPP_ */
