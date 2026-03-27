#pragma once

#include <sqlite3.h>
#include "adapter/IDBAdapter.hpp"
#include "domain/configurator/model/ConfigModel.hpp"
#include "domain/code_analyzer/model/AbsModel.hpp"
#include "domain/dependency_tracer/model/AbsModel.hpp"
#include "infrastructure/DBImpl/TopLevelQueries.hpp"
#include "infrastructure/DBImpl/DBFactory.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace adapter = NewTCG::adapter;
namespace configurator = NewTCG::domain::configurator;

namespace NewTCG::infrastructure::DBImpl {
    class AbsDBImpl : public adapter::IDBAdapter {
        protected:
        sqlite3* db;
        DBFactory controllerFactory;
        configurator::ConfigModel& config = configurator::ConfigModel::get_instance();
        std::vector<std::string> tables = {
            "File",
            "Namespace",
            "CXXRecord",
            "ConstructorDeclaration",
            "ConstructorDefinition",
            "FunctionDeclaration",
            "FunctionDefinition",
            "Enum",
            "Record",
            "Field",
            "Variable",
            "Typedef",
            "NamespaceAlias",
            "TypeAlias",
            "Friend",
            "UsingDirective",
            "Using",
            "Macro",
            "FunctionCallTrace",
            "VarTrace",
            "EnumTrace",
            "RecordTrace",
            "CXXRecordTrace",
            "HeaderTrace",
        };
        
        public:
        AbsDBImpl() {
            std::ifstream file("config.json");
            json json_config;
            file >> json_config;
            config.load_from_json(json_config);
            open_db();
            create_tables();
        }

        // virtual ~AbsDBImpl() = default;
        ~AbsDBImpl() { sqlite3_close(db); }

        bool open_db();
        bool create_tables();
        int add_to_db(const std::string& type, entity_model::AbsModel& model) final override ;
        int add_to_db(const std::string& type, trace_model::AbsModel& model) final override ;
    };
}