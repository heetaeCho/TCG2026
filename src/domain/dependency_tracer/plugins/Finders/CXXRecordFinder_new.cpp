#include "CXXRecordFinder_new.hpp"

#include <iostream>

namespace NewTCG::domain::dependency_tracer {
    CXXRecordFinderNew::CXXRecordFinderNew(const AbsModel& base, adapter::IDBAdapter* db) : IFinder(db) {
        model = CXXRecordModel(base);
    }

    void CXXRecordFinderNew::find(clang::FunctionDecl* decl) {
        // decl->dumpColor();
        TraverseDecl(decl);
        TraverseStmt(decl->getBody());
    }

    void CXXRecordFinderNew::logIfInProject(const clang::RecordDecl* recordDecl, const clang::ASTContext& ctx) {
        if (!recordDecl) return;

        const auto& SM = ctx.getSourceManager();
        clang::SourceLocation Loc = recordDecl->getLocation();
        std::string fileName = SM.getFilename(Loc).str();

        if (fileName.find(config.project_name) != std::string::npos) {
            model.cxxrecord_qualified_name = recordDecl->getQualifiedNameAsString();
            model.cxxrecord_type = recordDecl->isClass() ? "class" : recordDecl->isStruct() ? "struct" : "union";
            add_to_db();
            // std::string className = recordDecl->getNameAsString();
            // std::cout << "📌 CXXRecord 사용: " << className << ", 파일: " << fileName << "\n";
        }
    }

    bool CXXRecordFinderNew::VisitParmVarDecl(clang::ParmVarDecl* paramDecl) {
        auto type = paramDecl->getType().getCanonicalType().getLocalUnqualifiedType();

        // 포인터/참조 제거
        while (type->isPointerType() || type->isReferenceType()) {
            type = type->getPointeeType();
        }

        if (auto* recordDecl = type->getAsCXXRecordDecl()) {
            logIfInProject(recordDecl, paramDecl->getASTContext());
        }

        return true;
    }

    bool CXXRecordFinderNew::VisitMemberExpr(clang::MemberExpr* memberExpr) {
        if (auto* fieldDecl = llvm::dyn_cast<clang::FieldDecl>(memberExpr->getMemberDecl())) {
            logIfInProject(fieldDecl->getParent(), fieldDecl->getASTContext());
        }
        return true;
    }

    bool CXXRecordFinderNew::VisitCXXConstructorDecl(clang::CXXConstructorDecl* ctorDecl) {
        auto& ctx = ctorDecl->getASTContext();

        for (auto* init : ctorDecl->inits()) {
            if (init->isMemberInitializer()) {
                if (auto* field = init->getMember()) {
                    logIfInProject(field->getParent(), ctx);
                }
            } else if (init->isBaseInitializer()) {
                if (auto* base = init->getBaseClass()->getAsRecordDecl()) {
                    logIfInProject(base, ctx);
                }
            } else if (auto* declRef = llvm::dyn_cast<clang::DeclRefExpr>(init->getInit())) {
                VisitDeclRefExpr(declRef);
            }
        }

        return true;
    }

    bool CXXRecordFinderNew::VisitDeclRefExpr(clang::DeclRefExpr* declRefExpr) {
        if (auto* varDecl = llvm::dyn_cast<clang::VarDecl>(declRefExpr->getDecl())) {
            if (auto* recordDecl = varDecl->getType()->getAsCXXRecordDecl()) {
                logIfInProject(recordDecl, varDecl->getASTContext());
            }
        }
        return true;
    }

    bool CXXRecordFinderNew::VisitCallExpr(CallExpr *call) {
        if (auto *callee = call->getDirectCallee()) {
            if (const auto *parent = dyn_cast<CXXRecordDecl>(callee->getParent())) {
                logIfInProject(parent, parent->getASTContext());
            }
        }
        return true;
    }

    bool CXXRecordFinderNew::VisitCXXMethodDecl(clang::CXXMethodDecl* decl) {
        if (const auto *parent = dyn_cast<CXXRecordDecl>(decl->getParent())) {
            logIfInProject(parent, parent->getASTContext());
        }
        return true;
    }
} 