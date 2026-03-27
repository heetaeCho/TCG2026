#include "VariableHandler.hpp"

namespace NewTCG::domain::code_analyzer {
    void VariableHandler::handle(clang::VarDecl* decl) {
        model.name = decl->getNameAsString();
        model.type = decl->getType().getAsString();
        if (model.type == "_Bool") {
            model.type = "bool";
        }
        if(const auto* init = decl->getInit()) {
            model.value = AbsHandler::stmtToString(init);
        }

        if (decl->getType().isConstQualified())
            model.is_const = "true";
        if (decl->isStaticDataMember())
            model.is_static = "true";
        
        // std::cout << model.name << std::endl;
        // std::cout << model.type << std::endl;
        // std::cout << model.is_const << std::endl;
        // std::cout << model.is_static << std::endl;

        add_to_db();
    }
}