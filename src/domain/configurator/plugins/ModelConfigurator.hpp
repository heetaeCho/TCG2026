#pragma once

#include "AbsConfigurator.hpp"
#include "ConfigModel.hpp"
#include <memory>

namespace NewTCG::domain::configurator {
    class ModelConfigurator : public AbsConfigurator {
        private:
        std::string project_path;
        
        public:
        ModelConfigurator(const std::string& project_path) :  AbsConfigurator(project_path), project_path(project_path) {};
        bool execute() override;
    };
}