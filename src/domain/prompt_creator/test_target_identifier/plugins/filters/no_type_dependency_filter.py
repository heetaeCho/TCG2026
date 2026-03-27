# test_target_identifier/plugins/filters/no_type_dependency_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class NoTypeDependencyFilter(IPipeline):
    def __init__(self, enum_trace: list[tuple], record_trace: list[tuple], cxxrecord_trace: list[tuple]):
        self.function_ids = set()
        self.constructor_ids = set()
        self._extract_ids(enum_trace, record_trace, cxxrecord_trace)

    def _extract_ids(self, enum_trace, record_trace, cxxrecord_trace):
        all_traces = enum_trace + record_trace + cxxrecord_trace
        for row in all_traces:
            caller_id = row[1]
            caller_type = str(row[2]).lower()

            if caller_type == 'function':
                self.function_ids.add(caller_id)
            elif caller_type == 'constructor':
                self.constructor_ids.add(caller_id)

    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        if input_type not in ("function", "constructor"):
            raise ValueError(f"Unsupported input_type: {input_type}")

        id_index = 0  # function_def_id / constructor_def_id
        result = []

        allowed_ids = self.function_ids if input_type == "function" else self.constructor_ids

        for row in input_data:
            if row[id_index] in allowed_ids:
                result.append(row)

        return result

'''
enum_trace = db.select("SELECT * FROM EnumTrace")
record_trace = db.select("SELECT * FROM RecordTrace")
cxxrecord_trace = db.select("SELECT * FROM CXXRecordTrace")

type_filter = NoTypeDependencyFilter(enum_trace, record_trace, cxxrecord_trace)

filtered_functions = type_filter.identify("function", function_defs)
filtered_constructors = type_filter.identify("constructor", constructor_defs)
'''