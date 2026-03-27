#pragma once

#include "AbsCodeAnalyzer.hpp"

namespace NewTCG::domain::code_analyzer {
    class CodeAnalyzer : public AbsCodeAnalyzer {
    public:
    bool execute() override;
    void run_clang_ast(const std::string& context, const std::vector<std::string> args, const std::string& file_path);
    };
}