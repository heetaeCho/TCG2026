#include "ModelConfigurator.hpp"
#include <iostream>

namespace NewTCG::domain::configurator {
    bool ModelConfigurator::execute() {
        project_configuration();
        config.args = make_args();
        // for (std::string arg : args) {
        //     std::cout << "arg: " << arg << std::endl;
        // }
        return true;
    }
}