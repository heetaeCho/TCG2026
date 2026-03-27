#pragma once

#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>
#include "IFinder.hpp"

using namespace clang;

namespace NewTCG::domain::dependency_tracer {
    class CXXRecordFinder : public RecursiveASTVisitor<CXXRecordFinder>, public IFinder {

    public:
        CXXRecordFinder();
        void find(clang::FunctionDecl* decl) override;
        
        bool VisitMemberExpr(MemberExpr *memberExpr);
        bool VisitCXXConstructorDecl(CXXConstructorDecl *ctorDecl);
        bool VisitParmVarDecl(ParmVarDecl *paramDecl);
        bool VisitDeclRefExpr(DeclRefExpr *declRefExpr);
        bool VisitCXXMethodDecl(CXXMethodDecl *decl);
    };
}