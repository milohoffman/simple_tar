/*
 * archive_transaction.hpp
 *
 *  Created on: 23.01.2014
 *      Author: milo
 */

#ifndef ARCHIVE_TRANSACTION_HPP_
#define ARCHIVE_TRANSACTION_HPP_

#include <boost/filesystem.hpp>
#include <boost/utility.hpp>

namespace SimpleTar {

class ArchiveTransaction : boost::noncopyable {
public:
    ArchiveTransaction(const boost::filesystem::path& archive);
    ~ArchiveTransaction();

    void commit();

private:
    boost::filesystem::path archive_;
    bool commited_;
};

} //namespace SimpleTar


#endif /* ARCHIVE_TRANSACTION_HPP_ */
