/*
 * options.cpp
 *
 *  Created on: 18.01.2014
 *      Author: milo
 */

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include "options.hpp"

namespace po = boost::program_options;

namespace {

bool setOperation(SimpleTar::ProgramOptions& options, SimpleTar::ProgramOptions::EOperationType type, const std::string& path) {
        if (options.getOperation() != SimpleTar::ProgramOptions::NotSet) {
            std::cerr << "You can't set both compress and extract operations" << std::endl;
            return false;
        }

        options.setOperation(type);
        options.setOperationPath(path);

        return true;
    }

    bool setOptions(const po::variables_map& vm, SimpleTar::ProgramOptions& options) {
        if (vm.count("help")) {
            options.setNeedHelp(true);
            return true;
        }

        if (vm.count("compress")) {
            if (!setOperation(options, SimpleTar::ProgramOptions::Compress, vm["compress"].as<std::string>()))
                return false;
        }

        if (vm.count("extract")) {
            if (!setOperation(options, SimpleTar::ProgramOptions::Extract, vm["extract"].as<std::string>()))
                return false;
        }

        if (options.getOperation() == SimpleTar::ProgramOptions::NotSet) {
            std::cerr << "You must choose operation: compress or extract" << std::endl;
            return false;
        }

        if (!vm.count("output")) {
            if (options.getOperation() == SimpleTar::ProgramOptions::Compress)
                options.setOutputPath("output.arch");
            else
                options.setOutputPath(".");
        } else
            options.setOutputPath(vm["output"].as<std::string>());

        return true;
    }
}

namespace SimpleTar {

ProgramOptions::ProgramOptions() {
    operation_ = SimpleTar::ProgramOptions::NotSet;
    needHelp_ = false;
}

void ProgramOptions::printHelp() {
    std::cerr << helpString_ << std::endl;
}

bool parseOptions(int ac, char** av, ProgramOptions& options) {
    po::positional_options_description positional_options;
    po::options_description desc;

    positional_options.add("compress", 1);

    desc.add_options()
            ("help,h", "this help message")
            ("output,o", po::value<std::string>(),
                    "for compression: output file (default is 'output.arch'), for extraction: output directory (current directory by default).")
            ("extract,x", po::value<std::string>(), "extract archive")
            ("compress", po::value<std::string>(), "compress file or folder");

    std::stringstream ss;
    ss << desc;
    options.setHelpString(ss.str());

    po::variables_map vm;

    try {
        po::store(
                po::command_line_parser(ac, av).options(desc).positional(
                        positional_options).run(), vm);
        po::notify(vm);

        return setOptions(vm, options);
    } catch (std::exception & ex) {
        std::cerr << ex.what() << std::endl;
        return false;
    }

}

} //namespace SimpleTar
