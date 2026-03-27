#pragma once

#include "ICodeAnalyzer.hpp"
#include <filesystem>
#include <fstream>
#include "utils/StringUtils.hpp"

namespace NewTCG::domain::code_analyzer {
    class AbsCodeAnalyzer : public ICodeAnalyzer {
    protected:
    configurator::ConfigModel& config = configurator::ConfigModel::get_instance();

    std::vector<std::string> find_all_code_files() override {
        std::vector<std::string> files;
        for (const auto &entry : std::filesystem::recursive_directory_iterator(config.project_path)) {
            std::string fileName = entry.path().string();
            if (fileName.find("test") != std::string::npos || fileName.find("tests") != std::string::npos || fileName.find("build/") != std::string::npos \
                    || fileName.find("third_party") != std::string::npos || fileName.find("third-party") != std::string::npos || fileName.find("thirdparty") != std::string::npos \
                    || fileName.find("issues") != std::string::npos || fileName.find("fuzz") != std::string::npos || fileName.find("app") != std::string::npos \
                    || fileName.find("samples") != std::string::npos || fileName.find("contrib") != std::string::npos || fileName.find("unitTests") != std::string::npos \
                    || fileName.find("xmlsdk") != std::string::npos || fileName.find("scripts") != std::string::npos || fileName.find("qt6") != std::string::npos) {
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
