#include "Visitor.hpp"

#include "handlers/NamespaceHandler.hpp"
#include "handlers/CXXRecordHandler.hpp"
#include "handlers/FunctionHandler.hpp"
#include "handlers/VariableHandler.hpp"
#include "handlers/EnumHandler.hpp"
#include "handlers/RecordHandler.hpp"
#include "handlers/FieldHandler.hpp"
#include "handlers/TypedefHandler.hpp"
#include "handlers/TypeAliasHandler.hpp"
#include "handlers/UsingDirectiveHandler.hpp"
#include "handlers/UsingHandler.hpp"
#include "handlers/LinkageSpecHandler.hpp"
#include "handlers/NamespaceAliasHandler.hpp"
#include "handlers/FriendHandler.hpp"

#include <iostream>
namespace NewTCG::domain::code_analyzer {
    Visitor::Visitor(clang::CompilerInstance& compiler, adapter::IDBAdapter* db) \
    : compiler(compiler), sourceManager(compiler.getSourceManager()), db(db) {}

    bool Visitor::TraverseDecl(clang::Decl* decl) {
        if (!decl) { return true; }
        if (decl->getLocation().isMacroID()) {
            return true;
        }
        return RecursiveASTVisitor::TraverseDecl(decl);
    }

    bool Visitor::TraverseNamespaceDecl(clang::NamespaceDecl* decl) {
        NamespaceHandler handler(sourceManager, db);
        handler.handle(decl);
        RecursiveASTVisitor::TraverseNamespaceDecl(decl);
        handler.resolve_current_id();
        return true;
    }

    bool Visitor::TraverseCXXRecordDecl(clang::CXXRecordDecl* decl) {
        CXXRecordHandler handler(sourceManager, db);
        bool go_inside = handler.handle(decl); // 함수 내부의 CXXRecord. 이러면 내부로 안들어가니까. 함수도 안가겠지?
        if (go_inside) {
            RecursiveASTVisitor::TraverseCXXRecordDecl(decl);
            handler.resolve_current_id();
        }
        return true;
    }

    bool Visitor::VisitFunctionDecl(clang::FunctionDecl* decl) {
        // 람다가 아니면 함수안에 함수를 직접 작성하는건 불가능이라고 함.
        FunctionHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitVarDecl(clang::VarDecl* decl) {
        if (decl->isLocalVarDecl()) { // skip function_local
            return true;
        }
        if (decl->isStaticDataMember()) { // skip any static
            return true;
        }
        VariableHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitEnumDecl(clang::EnumDecl* decl) {
        if (!decl->isThisDeclarationADefinition()) {
            return true;
        }
        EnumHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitRecordDecl(clang::RecordDecl* decl) {
        if (!decl->isThisDeclarationADefinition()) {
            return true;
        }
        RecordHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitFieldDecl(clang::FieldDecl* decl) {
        FieldHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitTypedefDecl(clang::TypedefDecl* decl) {
        TypedefHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitTypeAliasDecl(clang::TypeAliasDecl* decl) {
        TypeAliasHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitUsingDirectiveDecl(clang::UsingDirectiveDecl* decl) {
        UsingDirectiveHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitUsingDecl(clang::UsingDecl* decl) {
        UsingHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitLinkageSpecDecl(clang::LinkageSpecDecl* decl) {
        // LinkageSpecHandler handler(sourceManager);
        // handler.handle(decl);
        return true;
    }

    bool Visitor::VisitNamespaceAliasDecl(clang::NamespaceAliasDecl* decl) {
        NamespaceAliasHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }

    bool Visitor::VisitFriendDecl(clang::FriendDecl* decl) {
        FriendHandler handler(sourceManager, db);
        handler.handle(decl);
        return true;
    }
}