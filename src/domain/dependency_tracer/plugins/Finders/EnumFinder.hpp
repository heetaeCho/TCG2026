#pragma once

#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>
#include "IFinder.hpp"

#include "domain/dependency_tracer/model/EnumModel.hpp"

using namespace clang;

namespace NewTCG::domain::dependency_tracer {
    class EnumFinder : public RecursiveASTVisitor<EnumFinder>, public IFinder {
    private:
    EnumModel model;
    void add_to_db() {
        db->add_to_db("EnumTrace", model);
    }

    public:
    EnumFinder(const AbsModel& base, adapter::IDBAdapter* db);

    public:
        void find(clang::FunctionDecl* decl) override;
        bool VisitDeclRefExpr(DeclRefExpr *DRE);
    };
}