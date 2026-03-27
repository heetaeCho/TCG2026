#include "CodeAnalyzer.hpp"
#include "FrontendAction.hpp"
#include <clang/Tooling/Tooling.h>
#include <iostream>

namespace NewTCG::domain::code_analyzer {
    bool CodeAnalyzer::execute() {
        std::cout << " ============== CodeAnalyzer ============== " << std::endl;
        std::vector<std::string> code_file = find_all_code_files();
        std::cout << "#code files: " << code_file.size() << std::endl;

        int i = 0;
        for (std::string file_path : code_file) {
            // std::cout << "file_path: " << file_path << std::endl;
            const std::string context = read_file(file_path);
            run_clang_ast(context, config.args, file_path);
        }

        std::cout << " ========================================== " << std::endl;
        return true;
    }

    void CodeAnalyzer::run_clang_ast\
    (const std::string& context, const std::vector<std::string> args, const std::string& file_path) {
        clang::tooling::runToolOnCodeWithArgs(std::make_unique<FrontendAction>(), context, args, file_path);
    }
}
