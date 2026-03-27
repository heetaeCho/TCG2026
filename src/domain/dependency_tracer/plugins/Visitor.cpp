#include "Visitor.hpp"
#include "Finders/FinderDispatcher.hpp"
#include <iostream>

namespace NewTCG::domain::dependency_tracer {
    Visitor::Visitor(clang::CompilerInstance& compiler) : sourceManager(compiler.getSourceManager()) {}
    
    bool Visitor::VisitFunctionDecl(clang::FunctionDecl* decl) {
        // std::cout << decl->getNameAsString() << std::endl;
        FinderDispatcher dispatcher(db.get());
        dispatcher.setup(decl);
        dispatcher.explore(decl);
        return true;
    }
}