#pragma once

#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>
#include "IFinder.hpp"

#include "domain/dependency_tracer/model/RecordModel.hpp"

using namespace clang;

namespace NewTCG::domain::dependency_tracer {

class RecordFinder : public RecursiveASTVisitor<RecordFinder>, public IFinder  {
    private:
    RecordModel model;
    void add_to_db() {
        db->add_to_db("RecordTrace", model);
    }

    public:
    RecordFinder(const AbsModel& base, adapter::IDBAdapter* db);

    void find(clang::FunctionDecl* decl);

    bool VisitParmVarDecl(clang::ParmVarDecl* paramDecl);
    bool VisitVarDecl(clang::VarDecl* varDecl);
    bool VisitMemberExpr(clang::MemberExpr* memberExpr);

    private:
    void logIfCStyleRecord(const clang::Type* type, const clang::ASTContext& ctx);
    void logIfRecord(const clang::RecordDecl* recordDecl, const clang::ASTContext& ctx);
};

}
