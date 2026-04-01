from infrastructure.PyDBImpl.SQLiteAdapter import SQLiteAdapter
from domain.prompt_creator.test_target_identifier.plugins.test_target_identifier import TestTargetIdentifier
from error_analyzer import ErrorAnalyzer
from error_category import CATEGORIES
import os
import re
import pandas as pd
import statsmodels.api as sm
from sklearn.preprocessing import StandardScaler
import clang.cindex as cl

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

            halstead = self.measure_halstead(function)
            metrics = {
                'loc': self.measure_loc(function),
                'cc': self.measure_cc(function),
                'nested_depth': self.measure_nested_depth(function),
                'params':self.measure_params(params),
                'object_params': self.measure_object_params(params),
                'fan_in': self.measure_fan_in(function_id),
                'fan_out': self.measure_fan_out(function_id),
                "halstead_volume": halstead.get("volume"),
                "halstead_effort": halstead.get("effort")
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

    def measure_halstead(self, function):
        index = cl.Index.create()
        import tempfile
        with tempfile.NamedTemporaryFile(suffix=".cpp", mode='w', delete=False) as f:
            f.write(function)
            temp = f.name
        tu = index.parse(temp, args=['-ferror-limit=0'])
        os.unlink(temp)

        operators = []
        operands = []

        for token in tu.get_tokens(extent=tu.cursor.extent):
            if token.kind == cl.TokenKind.KEYWORD or token.kind == cl.TokenKind.PUNCTUATION:
                operators.append(token.spelling)
            elif token.kind == cl.TokenKind.IDENTIFIER or token.kind == cl.TokenKind.LITERAL:
                operands.append(token.spelling)
        
        n1, n2 = len(set(operators)), len(set(operands))
        N1, N2 = len(operators), len(operands)

        if n1 == 0 or n2 == 0:
            return {"volume": 0, "effort": 0}
        
        from math import log2
        vocabulary  = n1 + n2
        length      = N1 + N2
        volume     = length * log2(vocabulary)
        difficulty  = (n1 / 2) * (N2 / n2)
        effort      = difficulty * volume
        print(volume)
        print(difficulty)
        print(effort)
        exit()
        return {"volume": round(volume, 2), "effort": round(effort, 2)}

class Integrator:
    def __init__(self, cwd):
        self.cwd = cwd
        self.llms = ["GPT5", "claude", "qwen2.5_coder_32b-8k"]
        self.r_csv = "structural_metric.csv"
        self.results = {"integrated": {}}

    def analyze(self):
        integrated_df = []
        for llm in self.llms:
            self.results[llm] = {}
            base_path = os.path.join("experiments", f"LLM/{llm}")
            csv_path = os.path.join(base_path, self.r_csv)
            df = pd.read_csv(csv_path)
            self._apf(llm, df)
            self._pe(llm, df)
            integrated_df.append(df)
        integrated_df = pd.concat(integrated_df, ignore_index=True)
        self._apf("integrated", integrated_df)
        self._pe("integrated", integrated_df)

    def _apf(self, llm, df):
        df_all = df
        df_pass = df[df['error_type'] == "PASS"]
        df_fail = df[df['error_type'] != "PASS"]

        mean_all = df_all.mean(numeric_only=True)
        mean_pass = df_pass.mean(numeric_only=True)
        mean_fail = df_fail.mean(numeric_only=True)

        result = pd.DataFrame({
            "ALL": mean_all,
            "PASS": mean_pass,
            "FAIL": mean_fail
        }).T
        self.results[llm]['apf'] = result

    def _pe(self, llm, df):
        df_fail = df[df['error_type'] != "PASS"]
        result = df_fail.groupby('error_type').mean(numeric_only=True)
        self.results[llm]['pe'] = result

    def get_integrated_apf(self):
        return self.results["integrated"].get("apf")
    def get_integrated_pe(self):
        return self.results["integrated"].get("pe")
    def get_gpt_apf(self):
        return self.results["GPT5"].get("apf")
    def get_gpt_pe(self):
        return self.results["GPT5"].get("pe")
    def get_claude_apf(self):
        return self.results["claude"].get("apf")
    def get_claude_pe(self):
        return self.results["claude"].get("pe")
    def get_qwen_apf(self):
        return self.results["qwen2.5_coder_32b-8k"].get("apf")
    def get_qwen_pe(self):
        return self.results["qwen2.5_coder_32b-8k"].get("pe")

class LogisticAnalyzer:
    def __init__(self, cwd):
        self.cwd = cwd
        self.llms = ["GPT5", "claude", "qwen2.5_coder_32b-8k"]
        self.r_csv = "structural_metric.csv"

    def analyze(self):
        integrated_df = []
        for llm in self.llms:
            base_path = os.path.join("experiments", f"LLM/{llm}")
            csv_path = os.path.join(base_path, self.r_csv)
            df = pd.read_csv(csv_path)
            integrated_df.append(df)
        integrated_df = pd.concat(integrated_df, ignore_index=True)
        self.bin_model = self.logistic_binary(integrated_df)
        self.mn_model = self.logistic_pe(integrated_df)
    
    def get_bin(self):
        return self.bin_model

    def get_mn(self):
        return self.mn_model
    
    def logistic_binary(self, df):
        # 1에 대한 영향력
        # pass = 0, error = 1
        df['target'] = (df['error_type'] != "PASS").astype(int)
        X = df[['loc', 'cc', 'nested_depth', 'params', 'object_params', 'fan_in','fan_out','halstead_volume','halstead_effort']]
        Y = df['target']

        scaler = StandardScaler()
        X_scaled = pd.DataFrame(scaler.fit_transform(X), columns=X.columns, index=X.index)

        X_const = sm.add_constant(X_scaled)
        model = sm.Logit(Y, X_const).fit(
            method='lbfgs',
            maxiter=1000,
            disp=True
        )

        # print(model.summary().tables[1].as_text())
        # print(model.pvalues)
        return model.summary2().tables[1].drop("const")

    def logistic_pe(self, df):
        scaler = StandardScaler()
        y = df['error_type']
        categories = ['PASS'] + [c for c in y.unique() if c != "PASS"]
        class_map = {i: c for i, c in enumerate(categories)}
        y_encoded = pd.Categorical(y, categories=categories).codes # pass=0

        X = df[['loc', 'cc', 'nested_depth', 'params', 'object_params', 'fan_in','fan_out','halstead_volume','halstead_effort']]
        X_scaled = pd.DataFrame(scaler.fit_transform(X), columns=X.columns, index=X.index)
        
        X_const = sm.add_constant(X_scaled)

        # print(y_encoded)
        # print(X_const)

        print("in MNLogit")
        model = sm.MNLogit(y_encoded, X_const).fit(
            method='lbfgs',
            maxiter=1000,
            disp=True
        )
        # print(model.summary())
        result = model.summary2().tables[1].drop("const")
        print(result.index)
        print(result.columns)

        result.columns = pd.MultiIndex.from_tuples(
            [class_map[int(col.split('=')[1])] if '=' in str(col) else col for col in result.columns]
        )
        return result

        