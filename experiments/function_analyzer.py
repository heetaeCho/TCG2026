from infrastructure.PyDBImpl.SQLiteAdapter import SQLiteAdapter
from domain.prompt_creator.test_target_identifier.plugins.test_target_identifier import TestTargetIdentifier
from error_analyzer import ErrorAnalyzer
import os

DATABASE_PATH = "./Database/{}_info.db"
class Mapper:
    def __init__(self, cwd, project_id, project, llm):
        self.cwd = cwd
        self.llm = llm
        self.project = project
        self.project_id = f"{project_id:02d}"
        self.project_path = os.path.join("experiments", f"LLM/{self.llm}", self.project_id + '_' + self.project)
        self.LOG_DIR = os.path.join(self.project_path, "log")
        self.BUILD_LOG_DIR = os.path.join(self.LOG_DIR, "build_log")
        self.db = SQLiteAdapter(DATABASE_PATH.format(self.project))
    
    def get_log_error_map(self):
        ea = ErrorAnalyzer(self.cwd, int(self.project_id), self.project, self.llm)
        return ea.get_map()

    def get_log_function_map(self):
        def get_id(name):
            return int(name.split("_")[-1].replace(".log", ""))-1
        log_function_map = {}
        functions, constructors = self._get_analyze_target()
        target = functions + constructors
        for log in os.listdir(self.BUILD_LOG_DIR):
            id = get_id(log)
            log_function_map[log] = target[id]
        return log_function_map

    def _get_analyze_target(self):
        def filter(input_data):
            identifier = TestTargetIdentifier(
                self.project,
                function_call_trace=self.db.select("SELECT * FROM FunctionCallTrace"),
                enum_trace=self.db.select("SELECT * FROM EnumTrace"),
                record_trace=self.db.select("SELECT * FROM RecordTrace"),
                cxxrecord_trace=self.db.select("SELECT * FROM CXXRecordTrace")
            )
            targets = identifier.identify(input_data["type"], input_data["data"])
            return targets
        
        input_data = {
            "type": "function",
            "data": self.db.select("SELECT * FROM FunctionDefinition")
        }
        az_target_functions = filter(input_data)

        input_data = {
            "type": "constructor",
            "data": self.db.select("SELECT * FROM ConstructorDefinition")
        }
        az_target_constructors = filter(input_data)

        return az_target_functions, az_target_constructors

class StructureMetric:
    def __init__(self, cwd, project_id, project, llm):
        self.cwd = cwd
        self.llm = llm
        self.project = project
        self.project_id = f"{project_id:02d}"
        self.mapper = Mapper(cwd, project_id, project, llm)

    def calculate(self):
        log_function_map = self.mapper.get_log_function_map()
        log_error_map = self.mapper.get_log_error_map()
        print(log_error_map)
        # print(log_function_map.keys())
        # print(log_function_map["test_1115.log"])

class LogisticAnalyzer:
    pass