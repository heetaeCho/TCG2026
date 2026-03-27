#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace NewTCG::domain::configurator {
    class ConfigModel {
    private:
    ConfigModel() {};
    
    public:
    static ConfigModel& get_instance() {
        static ConfigModel instance;
        return instance;
    }
    ConfigModel(const ConfigModel&) = delete;
    ConfigModel& operator=(const ConfigModel) = delete;

    public:
    std::string root_path;
    std::string project_path;
    std::string project_name;
    std::string test_base_path;
    std::string prompt_save_path = "/prompts";
    std::string response_save_path = "/response";
    std::string test_save_path = "/generated_test";
    std::string database_path = "/Database";
    std::vector<std::string> include_dirs;
    std::vector<std::string> args;

    void load_from_json(const json& j) {
        if (j.contains("root_path")) root_path = j.at("root_path").get<std::string>();
        if (j.contains("project_path")) project_path = j.at("project_path").get<std::string>();
        if (j.contains("project_name")) project_name = j.at("project_name").get<std::string>();
        if (j.contains("test_base_path")) test_base_path = j.at("test_base_path").get<std::string>();
        if (j.contains("prompt_save_path")) prompt_save_path = j.at("prompt_save_path").get<std::string>();
        if (j.contains("response_save_path")) response_save_path = j.at("response_save_path").get<std::string>();
        if (j.contains("test_save_path")) test_save_path = j.at("test_save_path").get<std::string>();
        if (j.contains("database_path")) database_path = j.at("database_path").get<std::string>();
        if (j.contains("include_dirs")) include_dirs = j.at("include_dirs").get<std::vector<std::string>>();
        if (j.contains("args")) args = j.at("args").get<std::vector<std::string>>();
    }
    };
}