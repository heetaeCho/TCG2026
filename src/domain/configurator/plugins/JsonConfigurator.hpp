#pragma once

#include "AbsConfigurator.hpp"
#include "ConfigModel.hpp"
#include <memory>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace NewTCG::domain::configurator {
    class JsonConfigurator : public AbsConfigurator {
        private:
        std::string project_path;
        
        public:
        JsonConfigurator(const std::string& project_path) :  AbsConfigurator(project_path), project_path(project_path) {};
        bool execute() override;
    };
}