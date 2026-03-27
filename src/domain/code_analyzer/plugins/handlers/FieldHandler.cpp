#include "FieldHandler.hpp"

namespace NewTCG::domain::code_analyzer {
    void FieldHandler::handle(clang::FieldDecl* decl) {
        model.name = decl->getNameAsString();
        model.type = decl->getType().getAsString();
        if (model.type == "_Bool") {
            model.type = "bool";
        }

        if(const auto* init = decl->getInClassInitializer()) {
            model.value = AbsHandler::stmtToString(init);
        }

        if (utils::starts_with(model.type, "const")) {
            model.is_const = "true";
        }

        if (clang::VarDecl* temp_decl = llvm::dyn_cast<clang::VarDecl>(decl)) {
            if (temp_decl->isStaticDataMember()) {
                model.is_static = "true";
            }
        }
            
        model.access = getAccess(decl->getAccess());

        add_to_db();
    }

    void FieldHandler::handle(clang::CXXRecordDecl* decl) {
            model.name = decl->getNameAsString();
            model.type = decl->isClass() ? "class" : decl->isStruct() ? "struct" : "union";
            model.access = getAccess(decl->getAccess());
            if (model.access == "none") {
                model.access = "private";
            }

            add_to_db();
        }
}