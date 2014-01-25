/*
 * utils.hpp
 *
 *  Created on: 23.01.2014
 *      Author: milo
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <ios>
#include <string>

#include <boost/filesystem.hpp>

namespace SimpleTar {

void throwIfNotGood(const std::ios& stream, const std::string& file);
void throwIfExists(const boost::filesystem::path& file);

} //namespace SimpleTar


#endif /* UTILS_HPP_ */
