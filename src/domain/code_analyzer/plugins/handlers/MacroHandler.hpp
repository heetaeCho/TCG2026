#pragma once 

#include "domain/configurator/model/ConfigModel.hpp"
#include "AbsHandler.hpp"
#include "MacroModel.hpp"
#include <clang/Frontend/CompilerInstance.h>
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Basic/IdentifierTable.h"
#include "llvm/Support/raw_ostream.h"
#include "utils/StringUtils.hpp"

namespace utils = NewTCG::utils;

namespace NewTCG::domain::code_analyzer {
    class MacroHandler : public AbsHandler {
        private:
        configurator::ConfigModel& config = configurator::ConfigModel::get_instance();

        public:
        MacroModel model;
        MacroHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::CompilerInstance& compiler) {
            clang::Preprocessor &PP = compiler.getPreprocessor();
            for (auto &Entry : PP.getIdentifierTable()) {
                clang::IdentifierInfo *II = Entry.second;
                if (II->hasMacroDefinition()) { // 매크로인지 확인
                    clang::MacroInfo *MI = PP.getMacroInfo(II);
                    if (MI) { 
                        // 매크로가 정의된 파일 및 위치 정보 가져오기
                        if (MI->getDefinitionLoc().isValid()) {
                            if (sourceManager.getFilename(MI->getDefinitionLoc()).str().find(config.project_name) != std::string::npos) {
                                // 매크로의 값(토큰) 가져오기
                                std::string macroValue;
                                clang::SourceLocation StartLoc = MI->getDefinitionLoc();
                                clang::SourceLocation EndLoc = MI->getDefinitionEndLoc();  // 매크로의 끝 위치 가져오기

                                // 매크로 범위가 유효한 경우에만 처리
                                if (StartLoc.isValid() && EndLoc.isValid()) {
                                    llvm::StringRef macroText = clang::Lexer::getSourceText(
                                        clang::CharSourceRange::getTokenRange(StartLoc, EndLoc),
                                        sourceManager, PP.getLangOpts());

                                    macroValue = macroText.str();
                                }
                                if (!utils::ends_with(macroValue, "_H") && !utils::ends_with(macroValue, "_H_"))
                                    model.macros.push_back(macroValue);
                            }
                        }
                    }
                }
            }
            add_to_db();
        }

        void add_to_db() {
            db->add_to_db("Macro", model);
        }
    };
}