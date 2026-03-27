# test_target_identifier/plugins/filters/uncalled_function_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class UncalledFunctionFilter(IPipeline):
    def __init__(self, trace_rows: list[tuple]):
        self.called_function_ids = set()
        self.called_constructor_ids = set()
        self._build_called_id_sets(trace_rows)

    def _build_called_id_sets(self, trace_rows: list[tuple]):
        # trace_row: (function_call_trace_id, caller_id, caller_type, callee_id, callee_type, file_id)
        for row in trace_rows:
            callee_id = row[3]
            callee_type = str(row[4]).lower()  # normalize: 'false' / 'true'

            if callee_type == 'function':
                self.called_function_ids.add(callee_id)
            elif callee_type == 'constructor':
                self.called_constructor_ids.add(callee_id)

    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        if input_type not in ("function", "constructor"):
            raise ValueError(f"Unsupported input_type: {input_type}")

        id_index = 0  # function_def_id / constructor_def_id
        result = []

        if input_type == "function":
            called_ids = self.called_function_ids
        else:
            called_ids = self.called_constructor_ids

        for row in input_data:
            def_id = row[id_index]
            if def_id in called_ids:
                result.append(row)

        return result

'''
trace_rows = db.select("SELECT * FROM FunctionCallTrace")

uncalled_filter = UncalledFunctionFilter(trace_rows)

filtered_functions = uncalled_filter.identify("function", function_defs)
filtered_constructors = uncalled_filter.identify("constructor", constructor_defs)
'''