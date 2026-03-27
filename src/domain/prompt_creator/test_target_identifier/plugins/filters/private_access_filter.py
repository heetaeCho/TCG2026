# test_target_identifier/plugins/filters/private_access_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class PrivateAccessFilter(IPipeline):
    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        if input_type not in ("function", "constructor"):
            raise ValueError(f"Unsupported input_type: {input_type}")

        access_index = 3  # 공통

        return [row for row in input_data if (row[access_index] or "").strip().lower() != "private"]
