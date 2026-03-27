#pragma once 

#include <clang/Basic/SourceManager.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>

#include <vector>
#include <string>
#include "IFinder.hpp"

namespace NewTCG::domain::dependency_tracer {
    class FinderDispatcher {
        private:
        std::vector<std::unique_ptr<IFinder>> finders;
        adapter::IDBAdapter* db;

        public:
        FinderDispatcher(adapter::IDBAdapter* db) : db(db) {}
        void setup(clang::FunctionDecl* decl);
        void explore(clang::FunctionDecl* decl);
    };
}