#pragma once

#include "AbsHandler.hpp"
#include "CXXRecordModel.hpp"
#include "FieldHandler.hpp"

namespace NewTCG::domain::code_analyzer {
    class CXXRecordHandler : public AbsHandler {
        public:
        CXXRecordModel model;
        CXXRecordHandler() = delete;
        CXXRecordHandler(clang::SourceManager &sourceManager, adapter::IDBAdapter* db) : AbsHandler(sourceManager, db) {}

        bool handle(clang::CXXRecordDecl* decl);
        std::string getClassTemplateAsString(clang::ClassTemplateDecl* decl);
        std::string getInheritance(clang::CXXRecordDecl* decl);
        void determineParentContext(clang::CXXRecordDecl* decl) ;

        void resolve_current_id() {
            model.set_current_cxxrecord_id(model.parent_cxxrecord_id);
        }

        void add_to_db() {
            int parent_id = db->add_to_db("CXXRecord", model);
            model.parent_cxxrecord_id = parent_id;
        }
    };
}