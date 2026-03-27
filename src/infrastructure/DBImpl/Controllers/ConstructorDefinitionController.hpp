#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class ConstructorDefinitionController : public IDBController{
        public:
        ConstructorDefinitionController() {}
        int add_to_db(sqlite3* db, entity_model::AbsModel& model) override;
    };
}