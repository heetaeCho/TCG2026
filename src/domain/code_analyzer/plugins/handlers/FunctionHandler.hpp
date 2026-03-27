#pragma once

#include "AbsHandler.hpp"
#include "FunctionModel.hpp"

namespace NewTCG::domain::code_analyzer {
        class HandlerFunctions {
        public:
        clang::SourceRange range;
        clang::SourceLocation startLoc;
        clang::SourceLocation endLoc;
        std::string parent_type;
        std::string parent_name;
        std::string _template;

        public:
        std::string getTemplateAsString(const clang::FunctionTemplateDecl* funcTemplate) {
            std::string result = "template <";

            clang::TemplateParameterList* params = funcTemplate->getTemplateParameters();
            const clang::ASTContext& context = funcTemplate->getASTContext();
            clang::PrintingPolicy policy(context.getLangOpts());
            policy.adjustForCPlusPlus();

            for (unsigned i = 0; i < params->size(); ++i) {
                if (i > 0) result += ", ";

                clang::NamedDecl* param = params->getParam(i);

                // 1. TemplateTypeParmDecl 처리
                if (auto* typeParam = llvm::dyn_cast<clang::TemplateTypeParmDecl>(param)) {
                    result += "typename";
                    if (!typeParam->getName().empty()) {
                        result += " " + typeParam->getNameAsString();
                    }

                    if (typeParam->hasDefaultArgument()) {
                        const clang::TemplateArgumentLoc& argLoc = typeParam->getDefaultArgument();
                        const clang::TemplateArgument& arg = argLoc.getArgument();

                        if (arg.getKind() == clang::TemplateArgument::Type) {
                            clang::QualType defaultType = arg.getAsType();
                            result += " = " + defaultType.getAsString(policy);
                        }
                    }
                }

                // 2. NonTypeTemplateParmDecl 처리
                else if (auto* nonTypeParam = llvm::dyn_cast<clang::NonTypeTemplateParmDecl>(param)) {
                    result += nonTypeParam->getType().getAsString(policy) + " " + nonTypeParam->getNameAsString();

                    if (nonTypeParam->hasDefaultArgument()) {
                        const clang::TemplateArgumentLoc& argLoc = nonTypeParam->getDefaultArgument();
                        const clang::TemplateArgument& arg = argLoc.getArgument();
                        if (arg.getKind() == clang::TemplateArgument::Expression) {
                            const clang::Expr* expr = arg.getAsExpr();
                            if (expr) {
                                std::string defaultStr;
                                llvm::raw_string_ostream stream(defaultStr);
                                expr->printPretty(stream, nullptr, policy);
                                result += " = " + stream.str();
                            }
                        }
                    }
                }

                // 3. TemplateTemplateParmDecl 처리 (기본 인자 생략)
                else if (auto* templateParam = llvm::dyn_cast<clang::TemplateTemplateParmDecl>(param)) {
                    result += "template <...> " + templateParam->getNameAsString();
                }
            }

            result += ">";
            return result;
        }




        void determineParentContext(clang::FunctionDecl* decl) {
            const clang::DeclContext* context = decl->getLexicalDeclContext();

            if (const clang::CXXRecordDecl* parent = clang::dyn_cast<clang::CXXRecordDecl>(context)) {
                parent_type = parent->isStruct() ? "struct" : parent->isUnion() ? "union" : "class";
                parent_name = parent->getNameAsString();
            }
            else if (const clang::NamespaceDecl* ns = clang::dyn_cast<clang::NamespaceDecl>(context)) {
                parent_type = "namespace";
                parent_name = ns->getNameAsString();
            }
            else if (clang::isa<clang::TranslationUnitDecl>(context)) {
                parent_type = "file";
                parent_name = "(Global Scope)";
            }
        }

        void get_source_locations(clang::FunctionDecl* decl) {
            range = decl->getSourceRange();
            startLoc = range.getBegin();
            endLoc = range.getEnd();

            // 2️⃣ 템플릿 생성자인 경우
            if (const clang::FunctionTemplateDecl* templateDecl = decl->getDescribedFunctionTemplate()) {
                _template = getTemplateAsString(templateDecl);
                range = templateDecl->getSourceRange();
                startLoc = range.getBegin();
                endLoc = range.getEnd();
            }
        }

        std::string getParameters(clang::FunctionDecl* decl) {
            std::string params;
            for (unsigned i = 0; i < decl->getNumParams(); ++i) {
                if (i > 0) params += ", ";
                const clang::ParmVarDecl* param = decl->getParamDecl(i);
                std::string paramType = param->getType().getAsString();
                if (paramType == "_Bool") {
                    paramType = "bool";
                }
                std::string paramName = param->getNameAsString();

                params += paramType + " " + (paramName.empty() ? "unnamed" : paramName);
            }
            return params;
        }

        std::string getBody(clang::FunctionDecl* decl, clang::SourceManager &sourceManager) {
            if (!decl->hasBody() || 
                (clang::isa<clang::CompoundStmt>(decl->getBody()) && clang::cast<clang::CompoundStmt>(decl->getBody())->body_empty())) {
                return "";
            } else {
                // ✅ 본문이 존재하면 출력
                clang::Stmt *body = decl->getBody();
                clang::SourceRange bodyRange = body->getSourceRange();
                clang::StringRef bodyText = clang::Lexer::getSourceText(clang::CharSourceRange::getTokenRange(bodyRange), sourceManager, clang::LangOptions());
                return bodyText.str();
            }
        }
    };

    class DefinitionHandler : public AbsHandler, public HandlerFunctions {
        public:
        DefinitionHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}
        DefinitionModel model;

        void handle(clang::FunctionDecl* decl);
        
        void add_to_db() {
            if (model.__type == "constructor") {
                db->add_to_db("ConstructorDefinition", model);
            } else {
                db->add_to_db("FunctionDefinition", model);
            }
        }
    };

    class DeclarationHandler : public AbsHandler, public HandlerFunctions {
        public:
        DeclarationHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}
        DeclarationModel model;

        void handle(clang::FunctionDecl* decl);

        void add_to_db() {
            if (model.__type == "constructor") {
                db->add_to_db("ConstructorDeclaration", model);
            } else {
                db->add_to_db("FunctionDeclaration", model);
            }
        }
    };

    class FunctionHandler : public AbsHandler {
        public:
        FunctionHandler() = delete;
        FunctionHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        void handle(clang::FunctionDecl* decl) {
            if (decl->isThisDeclarationADefinition()) {
                DefinitionHandler handler(sourceManager, db);
                handler.handle(decl);
            } 
            else {
                DeclarationHandler handler(sourceManager, db);
                handler.handle(decl);
            }
        }
    };
}