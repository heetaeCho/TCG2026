#pragma once

#include "BasicModel.hpp"
#include "clang/AST/Attr.h" 
#include <vector>
#include <string>

namespace NewTCG::domain::code_analyzer {
    class AbsModel {
        protected:
        BasicModel& basic = BasicModel::get_instance();

        public:
        int get_current_file_id() {return basic.get_current_file_id();}
        void set_current_file_id(int current_file_id) {basic.set_current_file_id(current_file_id);}

        int get_current_namespace_id() {return basic.get_current_namespace_id();}
        void set_current_namespace_id(int current_namespace_id) {basic.set_current_namespace_id(current_namespace_id);}

        int get_current_cxxrecord_id() {return basic.get_current_cxxrecord_id();}
        void set_current_cxxrecord_id(int current_cxxrecord_id) {basic.set_current_cxxrecord_id(current_cxxrecord_id);}

        public:
        virtual ~AbsModel() = default;
        virtual std::vector<std::string> get_data() = 0;
    };
}