/*
 * compressor.hpp
 *
 *  Created on: 19.01.2014
 *      Author: milo
 */

#ifndef COMPRESSOR_HPP_
#define COMPRESSOR_HPP_

#include <boost/utility.hpp>
#include <boost/filesystem.hpp>

#include <fstream>

namespace SimpleTar {

class Compressor : boost::noncopyable {
public:
    explicit Compressor(const boost::filesystem::path& outfile);

    void compress(const boost::filesystem::directory_entry& dirent);
private:
    void writeFile(const boost::filesystem::directory_entry& dirent);
    void writeDirectory(const boost::filesystem::directory_entry& dirent);
    void writeHeader(const boost::filesystem::directory_entry& dirent);
    void writeBody(std::ifstream& source);
    void writeBytes(const char * buf, size_t bytes);

    std::ofstream outfile_;
};

}


#endif /* COMPRESSOR_HPP_ */
