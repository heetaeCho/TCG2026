#include "JsonConfigurator.hpp"
#include <fstream>
#include <iostream>

namespace NewTCG::domain::configurator {
    bool JsonConfigurator::execute() {
        json json_config;
        project_configuration();
        config.args = make_args();
        
        json_config["root_path"] = config.root_path;
        json_config["project_path"] = config.project_path;
        json_config["project_name"] = config.project_name;
        json_config["test_base_path"] = config.test_base_path;
        json_config["prompt_save_path"] = config.prompt_save_path;
        json_config["response_save_path"] = config.response_save_path;
        json_config["test_save_path"] = config.test_save_path;
        json_config["database_path"] = config.database_path;
        json_config["args"] = config.args;

        std::ofstream out_file("./config.json");
        if (out_file.is_open()) {
            out_file << json_config.dump(2);
            out_file.close();
        }

        return true;
    }
}