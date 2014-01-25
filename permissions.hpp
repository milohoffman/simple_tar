/*
 * permissions.hpp
 *
 *  Created on: 23.01.2014
 *      Author: milo
 */

#ifndef PERMISSIONS_HPP_
#define PERMISSIONS_HPP_

#include <stdint.h>

#include <boost/filesystem.hpp>

namespace SimpleTar {

typedef uint16_t permissions_t;

int getFilePermissions(const boost::filesystem::path& path);
void setPermissions(const boost::filesystem::path& path, permissions_t perms);

} //namespace SimpleTar

#endif /* PERMISSIONS_HPP_ */
