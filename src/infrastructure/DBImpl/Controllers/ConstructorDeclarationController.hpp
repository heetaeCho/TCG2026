#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class ConstructorDeclarationController : public IDBController{
        public:
        ConstructorDeclarationController() {}
        int add_to_db(sqlite3* db, entity_model::AbsModel& model) override;
    };
}