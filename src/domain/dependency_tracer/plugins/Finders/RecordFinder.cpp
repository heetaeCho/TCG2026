#include "RecordFinder.hpp"
#include <iostream>

namespace NewTCG::domain::dependency_tracer {

RecordFinder::RecordFinder(const AbsModel& base, adapter::IDBAdapter* db) : IFinder(db) {
    model = RecordModel(base);
}

void RecordFinder::find(clang::FunctionDecl* decl) {
    TraverseStmt(decl->getBody());
    TraverseDecl(decl);
}

void RecordFinder::logIfCStyleRecord(const clang::Type* type, const clang::ASTContext& ctx) {
    if (!type) return;

    // Canonicalize, strip typedef, pointer, reference
    clang::QualType qt = clang::QualType(type, 0); // type → QualType 로 wrapping
    clang::QualType canonical = qt.getCanonicalType().getLocalUnqualifiedType();


    while (canonical->isPointerType() || canonical->isReferenceType()) {
        canonical = canonical->getPointeeType();
    }

    if (auto* recordType = canonical->getAs<clang::RecordType>()) {
        logIfRecord(recordType->getDecl(), ctx);
    }
}

void RecordFinder::logIfRecord(const clang::RecordDecl* recordDecl, const clang::ASTContext& ctx) {
    if (!recordDecl || llvm::isa<clang::CXXRecordDecl>(recordDecl)) return;

    if (!recordDecl->isStruct() && !recordDecl->isUnion()) return;

    const auto& SM = ctx.getSourceManager();
    clang::SourceLocation Loc = recordDecl->getLocation();
    std::string fileName = SM.getFilename(Loc).str();

    if (fileName.find(config.project_name) == std::string::npos) return;

    // std::string name = recordDecl->getNameAsString();
    model.record_qualified_name = recordDecl->getQualifiedNameAsString();
    model.record_type = recordDecl->isStruct() ? "struct" : "union";
    add_to_db();
    // std::cout << "📌 C-style Record 사용: " << name << ", 파일: " << fileName << "\n";
}

bool RecordFinder::VisitParmVarDecl(clang::ParmVarDecl* paramDecl) {
    logIfCStyleRecord(paramDecl->getType().getTypePtr(), paramDecl->getASTContext());
    return true;
}

bool RecordFinder::VisitVarDecl(clang::VarDecl* varDecl) {
    logIfCStyleRecord(varDecl->getType().getTypePtr(), varDecl->getASTContext());
    return true;
}

bool RecordFinder::VisitMemberExpr(clang::MemberExpr* memberExpr) {
    if (auto* fieldDecl = llvm::dyn_cast<clang::FieldDecl>(memberExpr->getMemberDecl())) {
        logIfRecord(fieldDecl->getParent(), fieldDecl->getASTContext());
    }
    return true;
}

}
