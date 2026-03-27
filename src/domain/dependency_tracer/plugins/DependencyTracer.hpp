#pragma once

#include "adapter/IDBAdapter.hpp"
#include "infrastructure/DBImpl/AbsDBImpl.hpp"
#include "AbsDependencyTracer.hpp"
#include "domain/dependency_tracer/model/HeaderModel.hpp"

namespace adapter = NewTCG::adapter;
namespace infra_db = NewTCG::infrastructure::DBImpl;

namespace NewTCG::domain::dependency_tracer {
    class DependencyTracer : public AbsDependencyTracer {
    private:
    HeaderModel model;

    public:
    bool execute() override;
    void run_clang_ast(const std::string& context, const std::vector<std::string> args, const std::string& file_path);
    void add_to_db();
    std::vector<std::string> get_headers(std::string& file_path);
    };
}