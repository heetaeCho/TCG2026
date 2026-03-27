#include "NamespaceHandler.hpp"

namespace NewTCG::domain::code_analyzer {
    void NamespaceHandler::handle(clang::NamespaceDecl* decl) {
        // namespace에는 이름이 없을 수 있음.
        model.name = decl->getNameAsString();
        if (model.name.empty()) {
            model.name = "Anonimous_id_"+std::to_string(NamespaceModel::anonimous_id);
            NamespaceModel::anonimous_id += 1;
        }

        clang::NamespaceDecl* parentNamespace = llvm::dyn_cast<clang::NamespaceDecl>(decl->getParent());
        if (parentNamespace) {
            model.parent_name = parentNamespace->getNameAsString();
        }
        
        add_to_db();
    }

    void NamespaceHandler::resolve_current_id() {
        model.set_current_namespace_id(model.parent_namespace_id);
    }

    void NamespaceHandler::add_to_db() {
        int parent_id = db->add_to_db("Namespace", model);
        model.parent_namespace_id = parent_id;
    }
}