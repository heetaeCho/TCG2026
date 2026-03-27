#pragma once

#include "IConfigurator.hpp"
#include "ConfigModel.hpp"
#include "utils/StringUtils.hpp"
#include <vector>
#include <algorithm>
#include <memory>
#include <filesystem>
#include <ctime>

#include <iostream>

namespace NewTCG::domain::configurator {
    class AbsConfigurator : public IConfigurator {
        private:
        std::string project_path;

        std::vector<std::string> find_header_files() {
            std::vector<std::string> files;
            for (const auto &entry : std::filesystem::recursive_directory_iterator(config.project_path)) {
                std::string fileName = entry.path().string();
                if (utils::ends_with(fileName, ".hpp") || utils::ends_with(fileName, ".h"))
                    files.push_back(fileName);
                if (fileName.find("test") != std::string::npos || fileName.find("tests") != std::string::npos || fileName.find("build/") != std::string::npos \
                    || fileName.find("third_party") != std::string::npos || fileName.find("third-party") != std::string::npos || fileName.find("thirdparty") != std::string::npos \
                    || fileName.find("issues") != std::string::npos || fileName.find("fuzz") != std::string::npos || fileName.find("app") != std::string::npos \
                    || fileName.find("samples") != std::string::npos || fileName.find("contrib") != std::string::npos || fileName.find("unitTests") != std::string::npos \
                    || fileName.find("xmlsdk") != std::string::npos || fileName.find("scripts") != std::string::npos || fileName.find("qt6") != std::string::npos) {
                    continue;
                }
            }
            return files;
        }

        protected:
        void project_configuration() override {
            config.root_path = std::filesystem::current_path();
            config.project_path = project_path;

            std::filesystem::path project_path = this->project_path;
            config.project_name = project_path.filename().string();

            std::time_t t = std::time(nullptr);
            std::tm* now = std::localtime(&t);
            config.test_base_path = config.project_path + \
            "/generated_" + std::to_string(now->tm_mon+1) + std::to_string(now->tm_mday);

            config.prompt_save_path = config.test_base_path + config.prompt_save_path;
            config.response_save_path = config.test_base_path + config.response_save_path;
            config.test_save_path = config.test_base_path + config.test_save_path;
            // config.database_path = config.root_path + config.database_path;
            config.database_path = "."+config.database_path;

            make_dir(config.test_base_path);
            make_dir(config.prompt_save_path);
            make_dir(config.response_save_path);
            make_dir(config.test_save_path);
            make_dir(config.database_path);
        }

        void make_dir(const std::string& dirName) {
            std::filesystem::create_directories(dirName);
        }

        std::vector<std::string> find_include_dirs() override {
            std::vector<std::string> includes;
            std::vector<std::string> headers = find_header_files();
            for (std::string header : headers) {
                header = utils::split(header, config.project_path).at(1);
                std::vector<std::string> include_path = utils::split(header, "/");

                std::string temp_path = "";
                for (std::string path : include_path) {
                    if (utils::ends_with(path, ".h") || utils::ends_with(path, ".hpp")) {
                        continue;
                    } else {
                        if (temp_path != "") {
                            path = config.project_path+'/'+temp_path+'/'+path;
                        } else {
                            temp_path += path;
                            path = config.project_path+'/'+path;
                        }

                        if (std::find(includes.begin(), includes.end(), path) != includes.end()) {
                            continue;
                        } else {
                            includes.push_back(path);
                        }
                    }
                }
            }
            // ubuntu 22?
            includes.push_back(config.project_path);

            if (config.project_name == "JsonBox") {
                includes.push_back("./TestProjects/JsonBox/build");
            } else if (config.project_name == "Catch2") {
                includes.push_back("./TestProjects/Catch2/build/generated_includes");
                includes.push_back("./TestProjects/Catch2/third_party");
            } else if (config.project_name == "glomap") {
                includes.push_back("/usr/include/eigen3");
                includes.push_back("/usr/include/ceres");
                includes.push_back("/usr/local/include/colmap");
            } else if (config.project_name == "exiv2") {
                includes.push_back("./TestProjects/exiv2/build");
                includes.push_back("./TestProjects/exiv2/include/exiv2");
                includes.push_back("./TestProjects/exiv2/xmpsdk/include");
            } else if (config.project_name == "poppler") {
                includes.push_back("./TestProjects/poppler/build");
                includes.push_back("./TestProjects/poppler/cpp");
                includes.push_back("./TestProjects/poppler/fofi");
                includes.push_back("./TestProjects/poppler/glib");
                includes.push_back("./TestProjects/poppler/goo");
                includes.push_back("./TestProjects/poppler/poppler");
                includes.push_back("./TestProjects/poppler/qt5");
                includes.push_back("./TestProjects/poppler/splash");
                includes.push_back("./TestProjects/poppler/utils");
            } 
            
            includes.push_back("/usr/include/c++/11");
            includes.push_back("/usr/include/c++/13");
            includes.push_back("/usr/include/x86_64-linux-gnu/c++/11");
            includes.push_back("/usr/include/x86_64-linux-gnu/c++/13");
            includes.push_back("/usr/lib/clang/20.0.0/include");
            return includes;
        }
        
        std::vector<std::string> make_args() override {
            std::vector<std::string> args= {
                };
            std::vector<std::string> includes = find_include_dirs();

            if (config.project_name == "leveldb") {
                args.push_back("-DLEVELDB_PLATFORM_POSIX");
            } else if (config.project_name == "exiv2") {
                args.push_back("-std=c++20");
            } else if (config.project_name == "poppler") {
                args.push_back("-std=c++20");
            }

            for (std::string include : includes) {
                args.push_back("-I"+include);
            }

            return args;
        }

        public:
        AbsConfigurator(const std::string& project_path) : project_path(project_path) {};
    };
}
