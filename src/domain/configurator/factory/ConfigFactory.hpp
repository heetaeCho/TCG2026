#pragma once

#include "ModelConfigurator.hpp"
#include "JsonConfigurator.hpp"
#include <memory>
#include <string>
#include <iostream>

namespace application = NewTCG::application;

namespace NewTCG::domain::configurator {
    class ConfigFactory {
        public:
        std::unique_ptr<application::IPipelineStep> create(const std::string& project_path, const std::string& type) {
            std::unique_ptr<application::IPipelineStep> test = nullptr;
            if (type == "model") {
                return std::make_unique<ModelConfigurator>(project_path);
            } else if (type == "json") {
                return std::make_unique<JsonConfigurator>(project_path);
            }
            return test;
        }
    };
}