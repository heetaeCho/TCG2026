#include "adapter/IDBAdapter.hpp"
#include "infrastructure/DBImpl/AbsDBImpl.hpp"
#include "AbsDependencyTracer.hpp"
#include "domain/dependency_tracer/model/HeaderModel.hpp"

#include "CodeAnalyzer.hpp"
#include "FrontendAction.hpp"
#include <clang/Tooling/Tooling.h>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace adapter = NewTCG::adapter;
namespace infra_db = NewTCG::infrastructure::DBImpl;

namespace NewTCG {
    std::string read_file(const std::string& file_path) {
        std::ifstream file(file_path);
        std::stringstream buffer;
        buffer << file.rdbuf(); // add file contents to buffer
        return buffer.str(); // convert buffer contents to string
    }

    std::vector<std::string> get_headers(std::string& file_path) {
        std::vector<std::string> headers;
        std::ifstream file(file_path);
        std::string line;
        while(getline(file, line)) {
            line = utils::rtrim(utils::ltrim(line));
            if (utils::starts_with(line, "#include")) {
                headers.push_back(line);
            }
        }
        file.close();
        return headers;
    }

    void add_to_db(domain::dependency_tracer::HeaderModel& model) {
        std::unique_ptr<adapter::IDBAdapter> db = std::make_unique<infra_db::AbsDBImpl>();
        db->add_to_db("HeaderTrace", model);
    }
}

int main(int argc, char** argv) {
    std::string file_path = argv[1];
    
    NewTCG::domain::dependency_tracer::AbsModel common;
    common.file_name = file_path;
    NewTCG::domain::dependency_tracer::HeaderModel model = NewTCG::domain::dependency_tracer::HeaderModel(common);
    model.headers = NewTCG::get_headers(file_path);
    NewTCG::add_to_db(model);

    if (!(NewTCG::utils::ends_with(file_path, ".h") || NewTCG::utils::ends_with(file_path, ".hpp"))) {
        std::ifstream file("config.json");
        json config;
        file >> config;
        std::string context = NewTCG::read_file(file_path);
        // std::cout << context << std::endl;
        clang::tooling::runToolOnCodeWithArgs\
        (std::make_unique<NewTCG::domain::dependency_tracer::FrontendAction>(), context, config["args"], file_path);
    }
}