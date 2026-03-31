from infrastructure.PyDBImpl.SQLiteAdapter import SQLiteAdapter
from domain.prompt_creator.test_target_identifier.plugins.test_target_identifier import TestTargetIdentifier
from error_analyzer import ErrorAnalyzer
from error_category import CATEGORIES
import os
import re

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
        self.PASS_DIR = os.path.join(self.project_path, "pass")
        self.BUILD_PASS_DIR = os.path.join(self.PASS_DIR, "build_pass")
        self.db = SQLiteAdapter(DATABASE_PATH.format(self.project))

    
    def get_log_error_map(self):
        ea = ErrorAnalyzer(self.cwd, int(self.project_id), self.project, self.llm)
        return ea.get_map()

    def get_pass_log_list(self):
        pass_logs = os.listdir(self.BUILD_PASS_DIR)
        return [item.replace('.cpp', '.log') for item in pass_logs]

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
        DISCARD_PATTERNS = [
            r"\[-W[^\]]+\]$",
            r"requires\s+-f\w+",
            r"use\s+'?-f[\w-]+'?\s+(?:or\s+'?-f[\w-]+'?\s+)?to\s+enable",
            r"Cannot find .+\(needed for .+\)\.",
            r"is not defined\. Please include",
        ]

        def should_discard(error_message: str) -> bool:
            for pattern in DISCARD_PATTERNS:
                if re.search(pattern, error_message):
                    return True
            return False
        # function = (id, name, q_name, access, ?, return_type, parameters, body, full_function, cxx, names, file)
        # parameters = string => need to split by ',' 
        log_function_map = self.mapper.get_log_function_map()
        log_error_map = self.mapper.get_log_error_map()
        pass_log_list = self.mapper.get_pass_log_list()

        results = []

        for log_name, function_data in log_function_map.items():
            FUNCTION_ID_INDEX = 0
            FULL_FUNCTION_INDEX = -4
            PARAMETER_INDEX = 6

            function_id = function_data[FUNCTION_ID_INDEX]
            function = function_data[FULL_FUNCTION_INDEX]
            params = function_data[PARAMETER_INDEX]

            metrics = {
                'loc': self.measure_loc(function),
                'cc': self.measure_cc(function),
                'nested_depth': self.measure_nested_depth(function),
                'params':self.measure_params(params),
                'object_params': self.measure_object_params(params),
                'fan_in': self.measure_fan_in(function_id),
                'fan_out': self.measure_fan_out(function_id),
            }

            errors = log_error_map.get(log_name, [])
            if not errors:  # pass
                results.append({
                    'log': log_name, 
                    'error_type': 'PASS', 
                    **metrics
                    })
            else:
                for error_type in set(errors):  # 중복 제거
                    if error_type in CATEGORIES.keys():
                        results.append({
                            'log': log_name,
                            'error_type': error_type,
                            **metrics
                        })
                    else:
                        if error_type in CATEGORIES.get("Semantic").keys():
                            results.append({
                                'log': log_name,
                                'error_type': error_type,
                                **metrics
                            })
                        else:
                            if not should_discard(error_type):
                                print(error_type)
        return results


    def measure_loc(self, function):
        lines = function.split('\n')
        lines = [l for l in lines if l.strip()]
        return len(lines)
    
    def measure_cc(self, function):
        branch_keywords = ['if', 'else if', 'for', 'while', 'case', 'catch']
        count = 1
        for kw in branch_keywords:
            count += len(re.findall(r'\b' + kw + r'\b', function))
        # 논리 연산자
        count += function.count('&&')
        count += function.count('||')
        count += function.count('?')
        return count
    
    def measure_nested_depth(self, function):
        max_depth = 0
        current_depth = 0
        for char in function:
            if char == '{':
                current_depth += 1
                max_depth = max(max_depth, current_depth)
            elif char == '}':
                current_depth -= 1
        return max_depth - 1

    def measure_params(self, parameters):
        if not parameters.strip():
            return 0
        return len(parameters.split(','))
    
    def measure_object_params(self, parameters):
        primitives = {'int', 'float', 'double', 'char', 'bool', 'void','long', 'short', 'unsigned', 'size_t', 'string'}
        modifiers = {'const', 'static', 'volatile', 'unsigned', 'signed'}
        if not parameters.strip():
            return 0
        count = 0
        for param in parameters.split(','):
            tokens = param.strip().replace('*','').replace('&','').split()
            # modifier 제거하고 남은 타입 토큰 찾기
            type_tokens = [t for t in tokens if t not in modifiers]
            if type_tokens:
                ptype = type_tokens[0]
                if ptype not in primitives:
                    count += 1
        return count

    def measure_fan_in(self, function_id):
        result = self.mapper.db.select(
            f"SELECT COUNT(DISTINCT caller_id) FROM FunctionCallTrace WHERE callee_id = {function_id}",
        )
        return result[0][0]

    def measure_fan_out(self, function_id):
        result = self.mapper.db.select(
            f"SELECT COUNT(DISTINCT callee_id) FROM FunctionCallTrace WHERE caller_id = {function_id}",
        )
        return result[0][0]

class LogisticAnalyzer:
    pass
