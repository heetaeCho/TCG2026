#pragma once

#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>
#include "IFinder.hpp"

#include "domain/dependency_tracer/model/FunctionCallModel.hpp"

using namespace clang;

namespace NewTCG::domain::dependency_tracer {
    class FunctionCallFinder : public RecursiveASTVisitor<FunctionCallFinder>, public IFinder {
    private:
    FunctionCallModel model;
    void add_to_db() {
        db->add_to_db("FunctionCallTrace", model);
    }

    public:
    FunctionCallFinder(const AbsModel& base, adapter::IDBAdapter* db);

    public:
        void find(clang::FunctionDecl* decl) override;
        bool VisitCallExpr(CallExpr *CE) ;
        bool VisitVarDecl(VarDecl *VD);
        bool VisitCXXConstructExpr(CXXConstructExpr *CE);
    };
}