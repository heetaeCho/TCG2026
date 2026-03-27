#pragma once

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInstance.h>
#include "domain/configurator/model/ConfigModel.hpp"
#include "adapter/IDBAdapter.hpp"

namespace configurator = NewTCG::domain::configurator;
namespace adapter = NewTCG::adapter;

namespace NewTCG::domain::code_analyzer {
    class Visitor : public clang::RecursiveASTVisitor<Visitor> {
        private:
        configurator::ConfigModel& config = configurator::ConfigModel::get_instance();
        clang::CompilerInstance& compiler;
        clang::SourceManager &sourceManager;
        adapter::IDBAdapter* db;

        public:
        Visitor(clang::CompilerInstance& compiler, adapter::IDBAdapter* db);
        // void set_file(std::string file_path);
        // void add_macros();

        public:
        bool TraverseDecl(clang::Decl* decl);
        bool TraverseNamespaceDecl(clang::NamespaceDecl* decl);
        bool TraverseCXXRecordDecl(clang::CXXRecordDecl* decl);
        
        bool VisitFunctionDecl(clang::FunctionDecl* decl);
        bool VisitVarDecl(clang::VarDecl* decl);
        bool VisitEnumDecl(clang::EnumDecl* decl);
        bool VisitRecordDecl(clang::RecordDecl* decl);
        bool VisitFieldDecl(clang::FieldDecl* decl);
        bool VisitTypedefDecl(clang::TypedefDecl* decl);
        bool VisitTypeAliasDecl(clang::TypeAliasDecl* decl);
        bool VisitUsingDirectiveDecl(clang::UsingDirectiveDecl* decl);
        bool VisitUsingDecl(clang::UsingDecl* decl);
        bool VisitLinkageSpecDecl(clang::LinkageSpecDecl* decl);
        bool VisitNamespaceAliasDecl(clang::NamespaceAliasDecl* decl);
        bool VisitFriendDecl(clang::FriendDecl* decl);
    };
}