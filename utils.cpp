/*
 * utils.cpp
 *
 *  Created on: 23.01.2014
 *      Author: milo
 */

#include "utils.hpp"

#include <sstream>

namespace SimpleTar {

void throwIfNotGood(const std::ios& stream, const std::string& file) {
    if (!stream.good()) {
        std::stringstream ss;
        ss << "Cannot open file " << file;
        throw std::runtime_error(ss.str());
    }
}

void throwIfExists(const boost::filesystem::path& file) {
    if (boost::filesystem::exists(file)) {
        std::stringstream ss;
        ss << "File exists: " << file.native();
        throw std::runtime_error(ss.str());
    }
}


}
