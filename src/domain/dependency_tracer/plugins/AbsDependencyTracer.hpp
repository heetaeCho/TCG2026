#pragma once

#include "IDependencyTracer.hpp"
#include <filesystem>
#include <fstream>
#include "utils/StringUtils.hpp"

namespace NewTCG::domain::dependency_tracer {
    class AbsDependencyTracer : public IDependencyTracer {
    protected:
    configurator::ConfigModel& config = configurator::ConfigModel::get_instance();
    
    std::vector<std::string> find_all_code_files() override {
        std::vector<std::string> files;
        for (const auto &entry : std::filesystem::recursive_directory_iterator(config.project_path)) {
            std::string fileName = entry.path().string();
            if (fileName.find("test") != std::string::npos || fileName.find("build/") != std::string::npos\
                || fileName.find("third_party/") != std::string::npos || fileName.find("benchmarks/") != std::string::npos) {
                continue;
            }
            if (utils::ends_with(fileName, ".cpp") || utils::ends_with(fileName, ".C") \
                || utils::ends_with(fileName, ".cxx") || utils::ends_with(fileName, ".cc"))
                files.push_back(fileName);
        }
        return files;
    }

    std::string read_file(const std::string& file_path) override {
        std::ifstream file(file_path);
        std::stringstream buffer;
        buffer << file.rdbuf(); // add file contents to buffer
        return buffer.str(); // convert buffer contents to string
    }

    std::string get_absolute_path(const std::string& file_path) {
        return std::filesystem::absolute(file_path).lexically_normal().string();
    }

    };
}