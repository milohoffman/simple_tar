/*
 * main.cpp
 *
 *  Created on: 17.01.2014
 *      Author: milo
 */

#include "options.hpp"
#include "compress.hpp"
#include "extract.hpp"

int main(int argc, char ** argv) {
    SimpleTar::ProgramOptions options;

//    try {

        if (!parseOptions(argc, argv, options)) {
            options.printHelp();
            return 1;
        }

        if (options.isNeedHelp()) {
            options.printHelp();
            return 0;
        }

        if (options.getOperation() == SimpleTar::ProgramOptions::Compress)
            SimpleTar::compress(options.getOperationPath(), options.getOutputPath());
        else
            SimpleTar::extract(options.getOperationPath(), options.getOutputPath());

//    } catch (std::exception& ex) {
//        std::cerr << "Error: " << ex.what() << std::endl;
//        return 1;
//    }

    return 0;
}
