# test_target_identifier/plugins/filters/anonymous_namespace_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class AnonymousNamespaceFilter(IPipeline):
    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        if input_type not in ("function", "constructor"):
            raise ValueError(f"Unsupported input_type: {input_type}")

        qualified_name_index = 2  # 공통

        return [
            row for row in input_data
            if "(anonymous namespace)" not in (row[qualified_name_index] or "")
        ]
