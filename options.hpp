/*
 * options.hpp
 *
 *  Created on: 18.01.2014
 *      Author: milo
 */

#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>

#include <exception>
#include <string>

namespace SimpleTar {

class ProgramOptions {
public:
    enum EOperationType {
        Compress,
        Extract,
        NotSet
    };

    ProgramOptions();

    void printHelp();

    void setHelpString(const std::string & helpString) {
        helpString_ = helpString;
    }

    bool isNeedHelp() const {
        return needHelp_;
    }

    void setNeedHelp(bool getHelp) {
        needHelp_ = getHelp;
    }

    EOperationType getOperation() const {
        return operation_;
    }

    void setOperation(EOperationType operation) {
        operation_ = operation;
    }

    std::string getOperationPath() const {
        return operationPath_;
    }

    void setOperationPath(const std::string & operationPath) {
        operationPath_ = operationPath;
    }

    std::string getOutputPath() const {
        return outputPath_;
    }

    void setOutputPath(const std::string & outputPath) {
        outputPath_ = outputPath;
    }

private:
    EOperationType operation_;
    std::string operationPath_;
    std::string outputPath_;
    bool needHelp_;
    std::string helpString_;
};

bool parseOptions(int ac, char** av, ProgramOptions& options);

} //namespace SimpleTar

#endif /* OPTIONS_HPP_ */
