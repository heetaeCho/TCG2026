#include "FunctionHandler.hpp"

namespace NewTCG::domain::code_analyzer {
    void DefinitionHandler::handle(clang::FunctionDecl* decl) {
        determineParentContext(decl);
        get_source_locations(decl);
        model.name = decl->getNameAsString();
        model.qualified_name = decl->getQualifiedNameAsString();
        model.access = AbsHandler::getAccess(decl->getCanonicalDecl()->getAccess());
        model._template = _template;
        model.parameters = getParameters(decl);
        model.body = getBody(decl, sourceManager);
        model.definition = AbsHandler::getOrigineCode(startLoc, endLoc);

        model.parent_type = parent_type;
        model.parent_name = parent_name;

        if (const auto *record = llvm::dyn_cast<clang::CXXRecordDecl>(decl->getParent())) {
            model.cxx_record_qname = record->getQualifiedNameAsString();
        }

        if (clang::CXXConstructorDecl* constructor_decl = llvm::dyn_cast<clang::CXXConstructorDecl>(decl)) {
            model.__type = "constructor";
        } else {
            model.__type = "function";
            model.return_type = decl->getReturnType().getAsString();
            if (model.return_type == "_Bool") {
                model.return_type = "bool";
            }
        }
        add_to_db();
    }

    void DeclarationHandler::handle(clang::FunctionDecl* decl) {
        determineParentContext(decl);
        get_source_locations(decl);
        model.name = decl->getNameAsString();
        model.qualified_name = decl->getQualifiedNameAsString();
        model.access = AbsHandler::getAccess(decl->getCanonicalDecl()->getAccess());
        model._template = _template;
        model.parameters = getParameters(decl);

        model.parent_type = parent_type;
        model.parent_name = parent_name;

        if (clang::CXXConstructorDecl* constructor_decl = llvm::dyn_cast<clang::CXXConstructorDecl>(decl)) {
            model.__type = "constructor";
            if (constructor_decl->getExplicitSpecifier().isExplicit()) {
                model.is_explicit = "true";
            }
            if (decl->isConstexpr()) {
                model.is_const = "true";
            }
            if (decl->isDeleted()) {
                model.is_delete = "true";
            }
        } else {
            model.__type = "function";
            model.return_type = decl->getReturnType().getAsString();
            if (model.return_type == "_Bool") {
                model.return_type = "bool";
            }

            if (decl->isStatic()) {
                model.is_static = "true";
            }
            if (decl->isConstexpr()) {
                model.is_const = "true";
            }
            if (decl->isVirtualAsWritten()) {
                model.is_virtual = "true";
            }
            if (const clang::CXXMethodDecl* methodDecl = llvm::dyn_cast<clang::CXXMethodDecl>(decl)) {
                if (methodDecl->getMethodQualifiers().hasConst()) {
                    model.is_const = "true";
                }
                if (methodDecl->doesDeclarationForceExternallyVisibleDefinition()) {
                    model.is_friend = "true";
                }
                if (methodDecl->size_overridden_methods() > 0) {
                    model.is_override = "true";
                }
                if(methodDecl->getAttr<clang::FinalAttr>()) {
                    model.is_final = "true";
                }
            }
        }
        add_to_db();
    }
}