/*
 * archive_transaction.cpp
 *
 *  Created on: 23.01.2014
 *      Author: milo
 */

#include "archive_transaction.hpp"
#include "utils.hpp"

namespace SimpleTar {

namespace fs = boost::filesystem;

ArchiveTransaction::ArchiveTransaction(const fs::path& archive) :
        archive_(archive), commited_(false)
{
    throwIfExists(archive_);
}

ArchiveTransaction::~ArchiveTransaction() {
    if (!commited_) {
        boost::system::error_code ignore;
        fs::remove(archive_);
    }
}

void ArchiveTransaction::commit() {
    commited_ = true;
}

} //namespace SimpleTar
