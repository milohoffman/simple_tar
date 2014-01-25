/*
 * extract.hpp
 *
 *  Created on: 20.01.2014
 *      Author: milo
 */

#ifndef EXTRACT_HPP_
#define EXTRACT_HPP_

#include <boost/filesystem.hpp>

namespace SimpleTar {

void extract(const boost::filesystem::path& archive, const boost::filesystem::path& output_dir);

} //namespace SimpleTar



#endif /* EXTRACT_HPP_ */
