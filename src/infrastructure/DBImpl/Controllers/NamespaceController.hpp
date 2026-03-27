#pragma once

#include "IDBController.hpp"
#include <iostream>

namespace NewTCG::infrastructure::DBImpl {
    class NamespaceController : public IDBController{
        public:
        NamespaceController() {}
        int add_to_db(sqlite3* db, entity_model::AbsModel& model) override;
    };
}