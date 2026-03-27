#include "CXXRecordFinder.hpp"

#include <iostream>

namespace NewTCG::domain::dependency_tracer {
    CXXRecordFinder::CXXRecordFinder() {}

    void CXXRecordFinder::find(clang::FunctionDecl* decl) {
        TraverseStmt(decl->getBody());
        if (auto* ctorDecl = llvm::dyn_cast<clang::CXXConstructorDecl>(decl)) {
            TraverseDecl(ctorDecl);
        } else {
            TraverseDecl(decl);
        }
    }

    bool CXXRecordFinder::VisitCXXMethodDecl(CXXMethodDecl *decl) {
        std::string className = decl->getParent()->getNameAsString();
        SourceLocation Loc = decl->getLocation();
        clang::SourceManager &SM = decl->getASTContext().getSourceManager();
        std::string fileName = SM.getFilename(Loc).str();

        if (fileName.find(config.project_name) == std::string::npos) {
            return true;  // 프로젝트 외부 파일 무시
        }

        std::cout << "📌 CXXRecord 사용: " << className
                        << ", 파일: " << fileName << "\n";

        // CXXRecordTraceInfo _cxrtInfo;
        // _cxrtInfo.cxxRecord_name = className;
        // _cxrtInfo.def_file = fileName;
        // if (auto* ctorDecl = llvm::dyn_cast<clang::CXXConstructorDecl>(decl)) {
        //     _cxrtInfo.isCallerConstructor = true;
        // }
        // cxrtInfo->insert(_cxrtInfo);
        return true;
    }

    bool CXXRecordFinder::VisitCXXConstructorDecl(CXXConstructorDecl *ctorDecl) {
        std::string className = ctorDecl->getParent()->getNameAsString();
        SourceLocation Loc = ctorDecl->getLocation();
        clang::SourceManager &SM = ctorDecl->getASTContext().getSourceManager();
        std::string fileName = SM.getFilename(Loc).str();

        if (fileName.find(config.project_name) == std::string::npos) {
            return true;  // 프로젝트 외부 파일 무시
        }

        // 생성자 맴버 초기화 확인
        for (auto* init : ctorDecl->inits()) {
            // 필드 초기화
            if (auto* declRefExpr = llvm::dyn_cast<clang::DeclRefExpr>(init->getInit())) {
                // isCallerConstructor = true;
                VisitDeclRefExpr(declRefExpr);
                // isCallerConstructor = false;
            }
            else if (init->isMemberInitializer()) {
                if (auto* fieldDecl = init->getMember()) {
                    std::string initFileName = SM.getFilename(fieldDecl->getLocation()).str();
                    std::string initClassName = fieldDecl->getParent()->getNameAsString();  // 필드가 속한 클래스
                    // if (!initClassName.empty()) {
                    //     CXXRecordTraceInfo _cxrtInfo;
                    //     _cxrtInfo.cxxRecord_name = initClassName;
                    //     _cxrtInfo.def_file = initFileName;
                    //     _cxrtInfo.isCallerConstructor = true;
                    //     cxrtInfo->insert(_cxrtInfo);
                    // }
                    std::cout << "📌 CXXRecord 사용: " << initClassName
                        << ", 파일: " << initFileName << "\n";
                }
            // 부모 클래스 초기화
            } else if (init->isBaseInitializer()) {
                if (auto* baseClass = init->getBaseClass()->getAsRecordDecl()) {
                    std::string baseFileName = SM.getFilename(baseClass->getLocation()).str();
                    std::string baseClassName = baseClass->getNameAsString();  // 부모 클래스 이름
                    // if (!baseClassName.empty()) {
                    //     CXXRecordTraceInfo _cxrtInfo;
                    //     _cxrtInfo.cxxRecord_name = baseClassName;
                    //     _cxrtInfo.def_file = baseFileName;
                    //     _cxrtInfo.isCallerConstructor = true;
                    //     cxrtInfo->insert(_cxrtInfo);
                    // }
                    std::cout << "📌 CXXRecord 사용: " << baseClassName
                        << ", 파일: " << baseFileName << "\n";
                }
            }
        }
        return true;
    }

    bool CXXRecordFinder::VisitMemberExpr(MemberExpr *memberExpr) {
        if (auto* fieldDecl = llvm::dyn_cast<clang::FieldDecl>(memberExpr->getMemberDecl())) {
            SourceLocation Loc = fieldDecl->getLocation();
            clang::SourceManager &SM = fieldDecl->getASTContext().getSourceManager();
            std::string fileName = SM.getFilename(Loc).str();
            if (fileName.find(config.project_name) == std::string::npos) {
                return true;
            }
            if (auto* parentRecord = fieldDecl->getParent()) {
                std::string className = parentRecord->getNameAsString(); // 클래스 이름 추출
                // if (!className.empty()) {
                //     CXXRecordTraceInfo _cxrtInfo;
                //     _cxrtInfo.cxxRecord_name = className;
                //     _cxrtInfo.def_file = fileName;
                //     cxrtInfo->insert(_cxrtInfo);
                // }
                std::cout << "📌 CXXRecord 사용: " << className
                        << ", 파일: " << fileName << "\n";
            }
        }
        return true;
    }

    bool CXXRecordFinder::VisitParmVarDecl(ParmVarDecl *paramDecl) {
        std::string paramType = paramDecl->getType().getAsString();
        std::string paramName = paramDecl->getNameAsString();
        SourceLocation paramLoc = paramDecl->getLocation();
        
        clang::SourceManager &SM = paramDecl->getASTContext().getSourceManager();
        std::string paramFileName = SM.getFilename(paramLoc).str();

        if (paramFileName.find(config.project_name) == std::string::npos) {
            return true; // 프로젝트 외부 파일 무시
        }

        QualType type = paramDecl->getType();
        // 1. typedef 해제 및 수식어 제거
        type = type.getCanonicalType().getLocalUnqualifiedType();
        // 2. 참조(&) 제거
        if (type->isReferenceType()) {
            type = type.getNonReferenceType();
        }
        // 3. 포인터(*) 제거
        while (type->isPointerType()) {
            type = type->getPointeeType();
        }
        // 4. CXXRecordDecl에서 순수한 클래스/구조체 이름 가져오기
        std::string pureType;
        if (auto* recordDecl = type->getAsCXXRecordDecl()) {
            pureType = recordDecl->getNameAsString();  // 네임스페이스 제거된 순수 클래스 이름
        } else {
            pureType = type.getAsString();  // 기본 타입이면 그대로 출력
        }

        auto* parentDecl = llvm::dyn_cast<FunctionDecl>(paramDecl->getDeclContext());
        bool isConstructor = false;
        if (parentDecl){
           isConstructor = llvm::isa<CXXConstructorDecl>(parentDecl); // 생성자인지 확인
        }
            
        // 2. 부모가 `FunctionDecl`인지 확인
        // if (!pureType.empty() && !paramName.empty()) {
        //     CXXRecordTraceInfo _cxrtInfo;
        //     _cxrtInfo.cxxRecord_name = pureType;  // 파라미터의 타입 저장
        //     _cxrtInfo.def_file = paramFileName;
        //     _cxrtInfo.isCallerConstructor = isConstructor; // is this 생성자의 파라미터?
        //     cxrtInfo->insert(_cxrtInfo);
        // }
        std::cout << "📌 CXXRecord 사용: " << pureType
                        << ", 파일: " << paramFileName << "\n";
        return true;
    }

    bool CXXRecordFinder::VisitDeclRefExpr(DeclRefExpr *declRefExpr) {
        Decl *decl = declRefExpr->getDecl();

        // 2. 참조된 변수(VarDecl)가 네임스페이스에 속하는지 확인
        if (auto *varDecl = llvm::dyn_cast<clang::VarDecl>(decl)) {
            SourceLocation Loc = varDecl->getLocation();

            clang::SourceManager &SM = varDecl->getASTContext().getSourceManager();
            std::string fileName = SM.getFilename(Loc).str();
            if (fileName.find(config.project_name) == std::string::npos) {
                return true;
            }
            // 변수 선언이 속한 컨텍스트를 추적
            auto* context = varDecl->getDeclContext();
            
            // 3. 컨텍스트가 네임스페이스라면 네임스페이스 추적
            if (auto* enclosingNamespace = llvm::dyn_cast<clang::NamespaceDecl>(context)) {
                std::string namespaceName = enclosingNamespace->getNameAsString();
                // if (!namespaceName.empty()) {
                //     CXXRecordTraceInfo _cxrtInfo;
                //     _cxrtInfo.cxxRecord_name = namespaceName;
                //     _cxrtInfo.def_file = fileName;
                //     _cxrtInfo.isCallerConstructor = isCallerConstructor;
                //     _cxrtInfo.is_namespace = true;
                //     cxrtInfo->insert(_cxrtInfo);
                // }
                std::cout << "📌 CXXRecord 사용: " << namespaceName
                        << ", 파일: " << fileName << "\n";
            }
        }
        return true;
    }
}