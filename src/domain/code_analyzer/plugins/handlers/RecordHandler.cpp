#include "RecordHandler.hpp"

namespace NewTCG::domain::code_analyzer {
    void RecordHandler::handle(clang::RecordDecl* decl) {
        if (clang::CXXRecordDecl* cxxDecl = clang::dyn_cast<clang::CXXRecordDecl>(decl)) {
            return;
        }
        determineParentContext(decl);
        if (model.parent_type == "function") {
            return;
        }
        model.type = decl->isUnion() ? "union" : "struct";
        model.name = decl->getNameAsString();
        if (model.name.empty()) {
            model.name = "Anonimous_id_"+std::to_string(RecordModel::anonimous_id);
            RecordModel::anonimous_id += 1;
        }
        model.qualified_name = decl->getQualifiedNameAsString();
        model.variables = getVariables(decl);
        if (model.parent_type == "struct" || model.parent_type == "class") {
            model.access = getAccess(decl->getAccess());
        }

        add_to_db();
    }

    void RecordHandler::determineParentContext(clang::RecordDecl* decl) {
        const clang::DeclContext* context = decl->getLexicalDeclContext();

        if (const clang::CXXRecordDecl* parent = clang::dyn_cast<clang::CXXRecordDecl>(context)) {
            model.parent_type = parent->isStruct() ? "struct" : parent->isClass() ? "class" : "union";
            model.parent_name = parent->getNameAsString();
        }
        else if (const clang::NamespaceDecl* ns = clang::dyn_cast<clang::NamespaceDecl>(context)) {
            model.parent_type = "namespace";
            model.parent_name = ns->getNameAsString();
        }
        else if (const clang::FunctionDecl* func = clang::dyn_cast<clang::FunctionDecl>(context)) {
            model.parent_type = "function";
            model.parent_name = func->getNameAsString();
        }
        else if (clang::isa<clang::TranslationUnitDecl>(context)) {
            model.parent_type = "file";
            model.parent_name = "(Global Scope)";
        }
    }

    std::string RecordHandler::getVariables(clang::RecordDecl* decl) {
        std::string vars;
        for (const auto* field : decl->fields()) { // 모든 멤버 변수 탐색
            if (!vars.empty()) {
                vars += ", ";
            }
            std::string fieldType = field->getType().getAsString();
            std::string fieldName = field->getNameAsString();
            vars += fieldType + " " + fieldName;
        }
        return vars;
    }
}