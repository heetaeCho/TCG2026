#pragma once

#include "infrastructure/DBImpl/Controllers/IDBController.hpp"

namespace NewTCG::infrastructure::DBImpl {
    class DBFactory {
        public:
        std::unique_ptr<IDBController> create(const std::string& type);
    };
}