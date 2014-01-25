/*
 * entity_header.hpp
 *
 *  Created on: 20.01.2014
 *      Author: milo
 */

#ifndef ENTITY_HEADER_HPP_
#define ENTITY_HEADER_HPP_

#include <stdint.h>
#include <string>

#include "permissions.hpp"

namespace SimpleTar {

struct EntityHeader {
    enum EntityType {
        FILE = 0,
        DIRECTORY = 1
    };

    char type;
    uint64_t entity_size;
    permissions_t perms;
    std::string path;
};

} //namespace SimpleTar

#endif /* ENTITY_HEADER_HPP_ */
