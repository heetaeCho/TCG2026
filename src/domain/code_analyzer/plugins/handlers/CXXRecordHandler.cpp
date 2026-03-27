#include "CXXRecordHandler.hpp"

namespace NewTCG::domain::code_analyzer {
    bool CXXRecordHandler::handle(clang::CXXRecordDecl* decl) {
        if (decl->isThisDeclarationADefinition()) {
            if (clang::ClassTemplateDecl* classTemplate = decl->getDescribedClassTemplate()) {
                model._template = getClassTemplateAsString(classTemplate);
            }
            if (decl->isClass()) { model.record_type = "class"; }
            else if (decl->isStruct()) {model.record_type = "struct"; }
            else if (decl->isUnion()) {model.record_type = "union"; }
            else { return false; }

            // CXXRecord에는 이름이 없을 수 있음.
            model.name = decl->getNameAsString();
            model.qualified_name = decl->getQualifiedNameAsString();
            if (model.name.empty()) {
                model.name = "Anonimous_id_"+std::to_string(CXXRecordModel::anonimous_id);
                CXXRecordModel::anonimous_id += 1;
            }
            model.inheritances = getInheritance(decl);
            model.access = getAccess(decl->getAccess());
            determineParentContext(decl);

            if (model.parent_type != "function") {
                add_to_db();
            } else {
                return false;
            }
        } else {
            FieldHandler handler(sourceManager, db);
            handler.handle(decl);
            return false;
        }
        return true;
    }

    std::string CXXRecordHandler::getClassTemplateAsString(clang::ClassTemplateDecl* decl) {
        std::string result = "template <";
        clang::TemplateParameterList* params = decl->getTemplateParameters();

        for (unsigned i = 0; i < params->size(); ++i) {
            if (i > 0) result += ", ";
            clang::NamedDecl* param = params->getParam(i);
            if (auto* typeParam = llvm::dyn_cast<clang::TemplateTypeParmDecl>(param)) {
                result += "typename " + typeParam->getNameAsString();
            } 
            else if (auto* nonTypeParam = llvm::dyn_cast<clang::NonTypeTemplateParmDecl>(param)) {
                result += nonTypeParam->getType().getAsString() + " " + nonTypeParam->getNameAsString();
            } 
            else if (auto* templateParam = llvm::dyn_cast<clang::TemplateTemplateParmDecl>(param)) {
                result += "template <...> " + templateParam->getNameAsString();
            }
        }
        result += ">";
        return result;
    }

    std::string CXXRecordHandler::getInheritance(clang::CXXRecordDecl* decl) {
        std::string inheritanceStr;

        for (const auto& base : decl->bases()) {
            if (!inheritanceStr.empty()) {
                inheritanceStr += ", ";
            }

            clang::QualType baseType = base.getType();
            std::string baseName = baseType.getAsString();

            std::string accessStr = getAccess(base.getAccessSpecifier());

            inheritanceStr += accessStr + " " + baseName;
        }

        return inheritanceStr;
    }

    void CXXRecordHandler::determineParentContext(clang::CXXRecordDecl* decl) {
        const clang::DeclContext* context = decl->getDeclContext();

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
}