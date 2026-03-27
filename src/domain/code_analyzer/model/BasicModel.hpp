#pragma once

namespace NewTCG::domain::code_analyzer {
    class BasicModel {
        private:
        BasicModel() {};
        int current_file_id = -1;
        int current_namespace_id = -1;
        int current_cxxrecord_id = -1;

        public:
        static BasicModel& get_instance() {
            static BasicModel instance;
            return instance;
        }

        BasicModel(const BasicModel&) = delete;
        BasicModel& operator=(const BasicModel) = delete;

        public:
        int get_current_file_id() {return current_file_id;}
        void set_current_file_id(int current_file_id) {this->current_file_id = current_file_id;}

        int get_current_namespace_id() {return current_namespace_id;}
        void set_current_namespace_id(int current_namespace_id) {this->current_namespace_id = current_namespace_id;}

        int get_current_cxxrecord_id() {return current_cxxrecord_id;}
        void set_current_cxxrecord_id(int current_cxxrecord_id) {this->current_cxxrecord_id = current_cxxrecord_id;}
    };
}