# test_target_identifier/plugins/filters/example_filter.py
from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

class ExampleFilter(IPipeline):
    def identify(self, data):
        # 예: "test" 라는 단어를 포함한 항목만 통과
        return [item for item in data if "test" in item.lower()]
