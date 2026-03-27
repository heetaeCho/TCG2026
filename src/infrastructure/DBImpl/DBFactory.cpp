#include "DBFactory.hpp"

#include "infrastructure/DBImpl/Controllers/FileController.hpp"
#include "infrastructure/DBImpl/Controllers/NamespaceController.hpp"
#include "infrastructure/DBImpl/Controllers/CXXRecordController.hpp"
#include "infrastructure/DBImpl/Controllers/FieldController.hpp"
#include "infrastructure/DBImpl/Controllers/VariableController.hpp"
#include "infrastructure/DBImpl/Controllers/EnumController.hpp"
#include "infrastructure/DBImpl/Controllers/RecordController.hpp"

#include "infrastructure/DBImpl/Controllers/ConstructorDefinitionController.hpp"
#include "infrastructure/DBImpl/Controllers/FunctionDefinitionController.hpp"
#include "infrastructure/DBImpl/Controllers/ConstructorDeclarationController.hpp"
#include "infrastructure/DBImpl/Controllers/FunctionDeclarationController.hpp"

#include "infrastructure/DBImpl/Controllers/TypedefController.hpp"
#include "infrastructure/DBImpl/Controllers/NamespaceAliasController.hpp"
#include "infrastructure/DBImpl/Controllers/TypeAliasController.hpp"
#include "infrastructure/DBImpl/Controllers/FriendController.hpp"
#include "infrastructure/DBImpl/Controllers/UsingDirectiveController.hpp"
#include "infrastructure/DBImpl/Controllers/UsingController.hpp"
#include "infrastructure/DBImpl/Controllers/MacroController.hpp"

#include "infrastructure/DBImpl/Controllers/FunctionCallTraceController.hpp"
#include "infrastructure/DBImpl/Controllers/VarTraceController.hpp"
#include "infrastructure/DBImpl/Controllers/EnumTraceController.hpp"
#include "infrastructure/DBImpl/Controllers/RecordTraceController.hpp"
#include "infrastructure/DBImpl/Controllers/CXXRecordTraceController.hpp"

#include "infrastructure/DBImpl/Controllers/HeaderTraceController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    std::unique_ptr<IDBController> DBFactory::create(const std::string& type) {
        if (type == "File") {
            return std::make_unique<FileController>();
        } else if (type == "Namespace") {
            return std::make_unique<NamespaceController>();
        } else if (type == "CXXRecord") {
            return std::make_unique<CXXRecordController>();
        } else if (type == "Field") {
            return std::make_unique<FieldController>();
        } else if (type == "Variable") {
            return std::make_unique<VariableController>();
        } else if (type == "Enum") {
            return std::make_unique<EnumController>();
        } else if (type == "Record") {
            return std::make_unique<RecordController>();
        } else if (type == "ConstructorDefinition") {
            return std::make_unique<ConstructorDefinitionController>();
        } else if (type == "FunctionDefinition") {
            return std::make_unique<FunctionDefinitionController>();
        } else if (type == "ConstructorDeclaration") {
            return std::make_unique<ConstructorDeclarationController>();
        } else if (type == "FunctionDeclaration") {
            return std::make_unique<FunctionDeclarationController>();
        } else if (type == "Typedef") {
            return std::make_unique<TypedefController>();
        } else if (type == "NamespaceAlias") {
            return std::make_unique<NamespaceAliasController>();
        } else if (type == "TypeAlias") {
            return std::make_unique<TypeAliasController>();
        } else if (type == "Friend") {
            return std::make_unique<FriendController>();
        } else if (type == "UsingDirective") {
            return std::make_unique<UsingDirectiveController>();
        } else if (type == "Using") {
            return std::make_unique<UsingController>();
        } else if (type == "Macro") {
            return std::make_unique<MacroController>();
        } else if (type == "FunctionCallTrace") {
            return std::make_unique<FunctionCallTraceController>();
        } else if (type == "VarTrace") {
            return std::make_unique<VarTraceController>();
        } else if (type == "EnumTrace") {
            return std::make_unique<EnumTraceController>();
        } else if (type == "RecordTrace") {
            return std::make_unique<RecordTraceController>();
        } else if (type == "CXXRecordTrace") {
            return std::make_unique<CXXRecordTraceController>();
        } else if (type == "HeaderTrace") {
            return std::make_unique<HeaderTraceController>();
        }
        return nullptr;
    }
}