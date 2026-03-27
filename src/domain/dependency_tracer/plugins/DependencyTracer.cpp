#include "DependencyTracer.hpp"
#include "FrontendAction.hpp"
#include <clang/Tooling/Tooling.h>

#include "utils/StringUtils.hpp"
#include <fstream>

#include <iostream>

namespace NewTCG::domain::dependency_tracer {
    bool DependencyTracer::execute() {
        std::cout << " ============== DependencyTracer ============== " << std::endl;
        std::vector<std::string> code_file = find_all_code_files();
        std::cout << "#code files: " << code_file.size() << std::endl;

        int i = 0;
        for (std::string file_path : code_file) {
            const std::string context = read_file(file_path);
            run_clang_ast(context, config.args, file_path);

            AbsModel common;
            common.file_name = file_path;
            model = HeaderModel(common);
            model.headers = get_headers(file_path);
            add_to_db();
        }

        std::cout << " ========================================== " << std::endl;
        return true;
    }

    void DependencyTracer::run_clang_ast\
    (const std::string& context, const std::vector<std::string> args, const std::string& file_path) {
        clang::tooling::runToolOnCodeWithArgs(std::make_unique<FrontendAction>(), context, args, file_path);
    }

    std::vector<std::string> DependencyTracer::get_headers(std::string& file_path) {
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

    void DependencyTracer::add_to_db() {
        std::unique_ptr<adapter::IDBAdapter> db = std::make_unique<infra_db::AbsDBImpl>();
        db->add_to_db("HeaderTrace", model);
    }
}