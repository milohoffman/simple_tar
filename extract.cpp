/*
 * extract.cpp
 *
 *  Created on: 20.01.2014
 *      Author: milo
 */

#include "extract.hpp"
#include "extractor.hpp"

namespace SimpleTar {

void extract(const boost::filesystem::path& archive, const boost::filesystem::path& output_dir) {
    Extractor ex(archive, output_dir);

    ex.extract();
}

}
