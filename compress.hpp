/*
 * compress.hpp
 *
 *  Created on: 19.01.2014
 *      Author: milo
 */

#ifndef COMPRESS_HPP_
#define COMPRESS_HPP_

#include <boost/filesystem.hpp>

namespace SimpleTar {

void compress(const boost::filesystem::path& compress_path, const boost::filesystem::path& output_path);

}

#endif /* COMPRESS_HPP_ */
