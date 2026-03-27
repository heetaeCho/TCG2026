#include "ASTConsumer.hpp"

#include <iostream>

namespace NewTCG::domain::dependency_tracer {
    ASTConsumer::ASTConsumer(clang::CompilerInstance& compiler) \
    : compiler(compiler), sourceManager(compiler.getSourceManager()), visitor(Visitor(compiler)) {}

    bool ASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef DR) {
        for (auto *decl : DR) {
            if (!decl) {continue;}
            if (!decl->getDeclContext()->isTranslationUnit()) { continue; }
            clang::SourceLocation Loc = decl->getLocation();
            if (!Loc.isValid()) continue; // 유효한 소스 위치가 아닐 경우 무시

            std::string file_name = sourceManager.getFilename(Loc).str();
            // 특정 파일만 Visitor에 넘기기
            if (file_name.find(config.project_path) == std::string::npos) {
                // llvm::outs() << "Skipping AST for: " << filename << "\n";
                continue; // 원하는 파일이 아니면 스킵
            } else if (file_name.find("build/") != std::string::npos) {
                continue;
            } else if (file_name.find("third_party/") != std::string::npos) {
                continue;
            }
            visitor.TraverseDecl(decl);
        }
        return true;
    }
}