# test_target_identifier/plugins/filters/void_function_no_effect_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class VoidFunctionNoEffectFilter(IPipeline):
    def __init__(
        self,
        function_call_trace: list[tuple],
        enum_trace: list[tuple],
        record_trace: list[tuple],
        cxxrecord_trace: list[tuple]
    ):
        self.calling_functions = set()
        self.typed_functions = set()
        self._build(function_call_trace, enum_trace, record_trace, cxxrecord_trace)

    def _build(self, call_trace, enum_trace, record_trace, cxxrecord_trace):
        for row in call_trace:
            caller_type = str(row[2]).lower()
            if caller_type == 'function':  # function
                self.calling_functions.add(row[1])

        for row in enum_trace + record_trace + cxxrecord_trace:
            caller_type = str(row[2]).lower()
            if caller_type == 'function':  # function
                self.typed_functions.add(row[1])

    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        if input_type != "function":
            return input_data  # 생성자는 처리하지 않음

        result = []
        for row in input_data:
            function_id = row[0]
            return_type = (row[5] or "").strip().lower()

            is_void = return_type == "void"
            calls_something = function_id in self.calling_functions
            uses_type = function_id in self.typed_functions

            if not is_void or calls_something or uses_type:
                result.append(row)

        return result


'''
call_trace = db.select("SELECT * FROM FunctionCallTrace")
enum_trace = db.select("SELECT * FROM EnumTrace")
record_trace = db.select("SELECT * FROM RecordTrace")
cxxrecord_trace = db.select("SELECT * FROM CXXRecordTrace")

void_filter = VoidFunctionNoEffectFilter(call_trace, enum_trace, record_trace, cxxrecord_trace)

filtered_functions = void_filter.identify("function", function_defs)
'''