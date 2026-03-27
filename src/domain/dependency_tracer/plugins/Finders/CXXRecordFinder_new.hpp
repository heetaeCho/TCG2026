#pragma once

#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>
#include "IFinder.hpp"

#include "domain/dependency_tracer/model/CXXRecordModel.hpp"

using namespace clang;

namespace NewTCG::domain::dependency_tracer {

class CXXRecordFinderNew : public RecursiveASTVisitor<CXXRecordFinderNew>, public IFinder {
    private:
    CXXRecordModel model;
    void add_to_db() {
        db->add_to_db("CXXRecordTrace", model);
    }

    public:
    CXXRecordFinderNew(const AbsModel& base, adapter::IDBAdapter* db);

    void find(clang::FunctionDecl* decl);

    // AST 방문 함수들
    bool VisitParmVarDecl(clang::ParmVarDecl* paramDecl);
    bool VisitMemberExpr(clang::MemberExpr* memberExpr);
    bool VisitCXXMethodDecl(clang::CXXMethodDecl* decl);
    bool VisitCXXConstructorDecl(clang::CXXConstructorDecl* ctorDecl);
    bool VisitDeclRefExpr(clang::DeclRefExpr* declRefExpr);
    bool VisitCallExpr(CallExpr *call);

    private:
    void logIfInProject(const clang::RecordDecl* recordDecl, const clang::ASTContext& ctx);
};

}
