#pragma once

#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>
#include "IFinder.hpp"

#include "domain/dependency_tracer/model/VarModel.hpp"

using namespace clang;

namespace NewTCG::domain::dependency_tracer {
    class VarFinder : public RecursiveASTVisitor<VarFinder>, public IFinder {
    private:
    VarModel model;
    void add_to_db() {
        db->add_to_db("VarTrace", model);
    }

    public:
    VarFinder(const AbsModel& base, adapter::IDBAdapter* db);

    public:
        void find(clang::FunctionDecl* decl) override;
        bool VisitVarDecl(clang::VarDecl* decl);
        bool VisitDeclRefExpr(DeclRefExpr *DRE);

    private:
    std::string stmtToString(const clang::Stmt* stmt) {
        if (!stmt) return "<null>";
        clang::LangOptions langOpts;
        langOpts.CPlusPlus = true;
        clang::PrintingPolicy policy(langOpts);
        std::string result;
        llvm::raw_string_ostream stream(result);
        stmt->printPretty(stream, nullptr, policy);
        return stream.str();
    }
    };
}