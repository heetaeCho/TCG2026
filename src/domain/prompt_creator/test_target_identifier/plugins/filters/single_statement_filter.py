# test_target_identifier/plugins/filters/single_statement_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class SingleStatementFilter(IPipeline):
    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        if input_type not in ("function", "constructor"):
            raise ValueError(f"Unsupported input_type: {input_type}")

        body_index = 7 if input_type == "function" else 6
        result = []

        for row in input_data:
            body = row[body_index] or ""
            body_lines = [line for line in body.strip().splitlines() if line.strip()]

            # 2줄 이상일 때만 통과 (1줄 이하 제외)
            if len(body_lines) > 1:
                result.append(row)

        return result
