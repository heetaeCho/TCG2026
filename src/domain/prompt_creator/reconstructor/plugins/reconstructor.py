from domain.prompt_creator.reconstructor.plugins.renderers.function_renderer import FunctionRenderer
from domain.prompt_creator.reconstructor.plugins.renderers.constructor_renderer import ConstructorRenderer
from domain.prompt_creator.reconstructor.plugins.renderers.variable_renderer import VariableRenderer
from domain.prompt_creator.reconstructor.plugins.renderers.enum_renderer import EnumRenderer
from domain.prompt_creator.reconstructor.plugins.renderers.record_renderer import RecordRenderer
from domain.prompt_creator.reconstructor.plugins.renderers.cxxrecord_renderer import CXXRecordRenderer

class Reconstructor:
    def __init__(self, db):
        self.db = db
        self.renderers = {
            "function": FunctionRenderer(db),
            "constructor": ConstructorRenderer(db),
            "enum": EnumRenderer(db),
            "record": RecordRenderer(db),
            "cxxrecord": CXXRecordRenderer(db),
            "variable": VariableRenderer(db)
        }

    def run(self, input_type, target: list[tuple]) -> str:
        this_target_map = {}

        file_id = target[-3]
        headers = '\n'.join(self._get_file_headers(file_id).split(', '))
        this_target_map["headers"] = headers

        # 1. 중심 row 렌더링
        # print(row)
        main_rendered = self.renderers[input_type].render(target, True)
        # print(main_rendered)
        this_target_map["target_function"] = main_rendered

        # 2. 관련된 row들 DB에서 조회
        related_map = self._collect_related_rows(target, input_type)
        # print(related_map)

        for kind, rows in related_map.items():
            if rows is None:
                continue
            if kind.startswith('function'):
                re_kind = 'function'
            elif kind.startswith('constructor'):
                re_kind = 'constructor'
            else:
                re_kind = kind
            if re_kind in self.renderers:
                for related_row in rows:
                    rendered = self.renderers[re_kind].render(related_row)
                    if kind in this_target_map.keys():
                        this_target_map[kind].append(rendered)
                    else:
                        this_target_map[kind] = [rendered]
        return this_target_map

    def _collect_related_rows(self, row: tuple, input_type: str) -> dict[str, list[tuple]]:
        # TODO: 실제 DB 쿼리 로직 구현
        def_id = row[0]
        function_callee_of_target = None
        function_caller_of_target = None
        constructor_callee_of_target = None
        constructor_caller_of_target = None
        if input_type == "function":
            function_callee_of_target = self.db.select("SELECT fd.* FROM FunctionDefinition fd JOIN FunctionCallTrace fct ON fd.function_def_id = fct.callee_id WHERE fct.caller_id = '{}' AND fct.caller_type = '{}'".format(def_id, input_type))
            function_caller_of_target = self.db.select("SELECT fd.* FROM FunctionDefinition fd JOIN FunctionCallTrace fct ON fd.function_def_id = fct.caller_id WHERE fct.callee_id = '{}' AND fct.callee_type = '{}'".format(def_id, input_type))
        else:
            constructor_callee_of_target = self.db.select("SELECT fd.* FROM ConstructorDefinition fd JOIN FunctionCallTrace fct ON fd.constructor_def_id = fct.callee_id WHERE fct.caller_id = '{}' AND fct.caller_type = '{}'".format(def_id, input_type))
            constructor_caller_of_target = self.db.select("SELECT fd.* FROM ConstructorDefinition fd JOIN FunctionCallTrace fct ON fd.constructor_def_id = fct.caller_id WHERE fct.callee_id = '{}' AND fct.callee_type = '{}'".format(def_id, input_type))
        
        enum_trace=self.db.select("SELECT e.* FROM Enum e JOIN EnumTrace et ON e.enum_id = et.enum_id WHERE et.caller_id = '{}' AND et.caller_type = '{}'".format(def_id, input_type))
        record_trace=self.db.select("SELECT r.* FROM Record r JOIN RecordTrace rt ON r.record_id = rt.record_id WHERE rt.caller_id = '{}' AND rt.caller_type = '{}'".format(def_id, input_type))
        cxxrecord_trace=self.db.select("SELECT c.* FROM CXXRecord c JOIN CXXRecordTrace ct ON c.cxxrecord_id = ct.cxxrecord_id WHERE ct.caller_id = '{}' AND ct.caller_type = '{}'".format(def_id, input_type))
        var_trace=self.db.select("SELECT v.* FROM Variable v JOIN VarTrace vt ON v.variable_id = vt.var_id WHERE vt.caller_id = '{}' AND vt.caller_type = '{}'".format(def_id, input_type))

        return {
            "function_callee_of_target": function_callee_of_target,
            "function_caller_of_target": function_caller_of_target,
            "constructor_callee_of_target": constructor_callee_of_target,
            "constructor_caller_of_target": constructor_caller_of_target,
            "enum": enum_trace,
            "record": record_trace,
            "cxxrecord": cxxrecord_trace,
            "variable": var_trace
        }
    
    def _get_file_headers(self, file_id):
        headers = self.db.select(f"SELECT headers FROM HeaderTrace where file_id = {file_id}")
        if headers:
            return headers[0][0]
        else:
            return ""