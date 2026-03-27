#include "CodeAnalyzer.hpp"
#include "FrontendAction.hpp"
#include <clang/Tooling/Tooling.h>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string read_file(const std::string& file_path) {
    std::ifstream file(file_path);
    std::stringstream buffer;
    buffer << file.rdbuf(); // add file contents to buffer
    return buffer.str(); // convert buffer contents to string
}

int main(int argc, char** argv) {
    std::ifstream file("config.json");
    json config;
    file >> config;

    std::string file_path = argv[1];
    std::string context = read_file(file_path);
    // std::cout << context << std::endl;
    clang::tooling::runToolOnCodeWithArgs\
    (std::make_unique<NewTCG::domain::code_analyzer::FrontendAction>(), context, config["args"], file_path);
}