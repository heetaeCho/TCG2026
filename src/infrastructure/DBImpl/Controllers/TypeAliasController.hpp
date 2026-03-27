#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class TypeAliasController : public IDBController{
        public:
        TypeAliasController() {}
        int add_to_db(sqlite3* db, entity_model::AbsModel& model) override;
    };
}