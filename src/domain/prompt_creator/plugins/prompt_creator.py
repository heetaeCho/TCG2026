# domain.prompt_creator.plugin.prompt_creator.py
from domain.prompt_creator.test_target_identifier.plugins.test_target_identifier import TestTargetIdentifier
from domain.prompt_creator.reconstructor.plugins.reconstructor import Reconstructor
from domain.prompt_creator.reconstructor.plugins.post_render_processor import PostRenderProcessor

class PromptCreator:
    def __init__(self, db, project_name):
        self.project_name = project_name
        self.db = db
        self.identifier = TestTargetIdentifier(
            self.project_name,
            function_call_trace=db.select("SELECT * FROM FunctionCallTrace"),
            enum_trace=db.select("SELECT * FROM EnumTrace"),
            record_trace=db.select("SELECT * FROM RecordTrace"),
            cxxrecord_trace=db.select("SELECT * FROM CXXRecordTrace")
        )
        self.reconstructor = Reconstructor(self.db)
        self.post_processor = PostRenderProcessor()

    def run(self, input_data):
        prompts = []
        targets = self.identifier.identify(input_data["type"], input_data["data"])
        for target in targets:
            this_target_map = self.reconstructor.run(input_data["type"], target)
            prompts.append(self.post_processor.run(this_target_map))
        return prompts
