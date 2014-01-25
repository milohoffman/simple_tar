/*
 * compress.cpp
 *
 *  Created on: 19.01.2014
 *      Author: milo
 */

#include <boost/bind.hpp>

#include <algorithm>

#include "compress.hpp"
#include "compressor.hpp"
#include "archive_transaction.hpp"

namespace SimpleTar {

namespace fs = boost::filesystem;

void compress(const fs::path& compress_path, const fs::path& output_path) {
    ArchiveTransaction tr(output_path);

    Compressor c(output_path);

    fs::file_status status = fs::status(compress_path);
    if (fs::is_regular_file(status)) {
        c.compress(fs::directory_entry(compress_path));
    } else if (fs::is_directory(status)) {
        //TODO: path must be relative!
        std::for_each(fs::recursive_directory_iterator(compress_path), fs::recursive_directory_iterator(),
                boost::bind(&Compressor::compress, &c, _1));
    }

    tr.commit();
}

} //namespace SimpleTar
