# test_target_identifier/plugins/filters/trivial_constructor_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class TrivialConstructorFilter(IPipeline):
    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        if input_type != "constructor":
            return input_data  # 이 필터는 생성자만 처리

        result = []

        for row in input_data:
            parameters = (row[5] or "").strip()
            body = (row[6] or "").strip()
            definition = (row[7] or "").strip()

            is_deleted = "= delete" in definition
            is_empty = body in ("", "{}", "pass")
            is_paramless = parameters in ("", "()")

            # trivial 조건
            if (is_paramless and is_empty) or is_deleted:
                continue  # 제외

            result.append(row)

        return result
