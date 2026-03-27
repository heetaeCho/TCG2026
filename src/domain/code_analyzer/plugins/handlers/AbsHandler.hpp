#pragma once

#include "adapter/IDBAdapter.hpp"
#include "infrastructure/DBImpl/AbsDBImpl.hpp"
#include "AbsModel.hpp"

#include <string>
#include <vector>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>
#include <clang/AST/DeclTemplate.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/DeclFriend.h>
#include <clang/Basic/LangOptions.h>
#include <clang/AST/PrettyPrinter.h>
#include <clang/AST/Stmt.h>
#include <clang/AST/StmtCXX.h>

#include <iostream>

namespace adapter = NewTCG::adapter;
namespace infra_db = NewTCG::infrastructure::DBImpl;

namespace NewTCG::domain::code_analyzer {
    class AbsHandler {
        protected:
        clang::SourceManager &sourceManager;
        adapter::IDBAdapter* db;

        protected:
        std::string getAccess(clang::AccessSpecifier access) {
            std::string accessStr = (access == clang::AS_private) ? "private" :
                                    (access == clang::AS_protected) ? "protected" :
                                    (access == clang::AS_public) ? "public" :
                                    "none";
            return accessStr;
        }

        std::string stmtToString(const clang::Stmt* stmt) {
            if (!stmt) return "<null>";
            clang::LangOptions langOpts;
            langOpts.CPlusPlus = true;
            clang::PrintingPolicy policy(langOpts);
            std::string result;
            llvm::raw_string_ostream stream(result);
            stmt->printPretty(stream, nullptr, policy);
            return stream.str();
        }

        std::string getFile(clang::SourceLocation declLoc) {
            // clang::SourceLocation declLoc = decl->getCanonicalDecl()->getLocation();
            std::string filename = sourceManager.getFilename(declLoc).str();
            return filename; 
        }

        std::string getOrigineCode(clang::SourceLocation StartLoc, clang::SourceLocation EndLoc) {
            // clang::SourceRange range = decl->getSourceRange();
            // clang::SourceLocation startLoc = range.getBegin();
            // clang::SourceLocation endLoc = range.getEnd();
            std::string sourceText = clang::Lexer::getSourceText(
                clang::CharSourceRange::getTokenRange\
                (StartLoc, EndLoc), sourceManager, clang::LangOptions()).str();
            return sourceText;
        }

        public:
        virtual ~AbsHandler() = default;
        AbsHandler() = delete;
        AbsHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) \
        : sourceManager(sourceManager), db(db) {}
    };
}