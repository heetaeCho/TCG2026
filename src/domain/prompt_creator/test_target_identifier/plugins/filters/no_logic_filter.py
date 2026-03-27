# test_target_identifier/plugins/filters/no_logic_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class NoLogicFilter(IPipeline):
    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        result = []

        if input_type not in ("function", "constructor"):
            raise ValueError(f"Unsupported type: {input_type}")

        body_index = 7 if input_type == "function" else 6

        for row in input_data:
            body = row[body_index] or ""
            body_str = body.strip()

            # '{}' 또는 'pass' 외의 실제 로직이 있을 때만 통과
            if body_str and body_str not in ("{}", "pass"):
                result.append(row)

        return result