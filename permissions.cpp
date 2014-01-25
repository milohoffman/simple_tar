/*
 * permissions.cpp
 *
 *  Created on: 23.01.2014
 *      Author: milo
 */

#include "permissions.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace SimpleTar {

int getFilePermissions(const boost::filesystem::path& path) {
    //boost::filesystem 1.48 had not file_status.permissions() yet

    struct stat buf;

    if (stat(path.c_str(), &buf)) {
        boost::system::error_code ec(errno, boost::system::system_category());
        throw boost::system::system_error (ec, "Cannot stat file");
    }

    permissions_t perms = 0;
    perms |= (buf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return perms;
}

void setPermissions(const boost::filesystem::path& path, permissions_t perms) {
    mode_t mode = perms;

    if (chmod(path.c_str(), mode) < 0) {
        boost::system::error_code ec(errno, boost::system::system_category());
        throw boost::system::system_error (ec, "Cannot set permissions to the file");
    }
}

} //namespace SimpleTar
