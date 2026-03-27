from domain.prompt_creator.test_target_identifier.interface.IPipeline import IPipeline

# 필터 import
from domain.prompt_creator.test_target_identifier.plugins.filters.no_logic_filter import NoLogicFilter
from domain.prompt_creator.test_target_identifier.plugins.filters.single_statement_filter import SingleStatementFilter
from domain.prompt_creator.test_target_identifier.plugins.filters.trivial_constructor_filter import TrivialConstructorFilter
from domain.prompt_creator.test_target_identifier.plugins.filters.uncalled_function_filter import UncalledFunctionFilter
from domain.prompt_creator.test_target_identifier.plugins.filters.no_type_dependency_filter import NoTypeDependencyFilter
from domain.prompt_creator.test_target_identifier.plugins.filters.void_function_no_effect_filter import VoidFunctionNoEffectFilter
from domain.prompt_creator.test_target_identifier.plugins.filters.private_access_filter import PrivateAccessFilter
from domain.prompt_creator.test_target_identifier.plugins.filters.anonymous_namespace_filter import AnonymousNamespaceFilter

class TestTargetIdentifier:
    def __init__(
        self,
        project_name,
        function_call_trace: list[tuple],
        enum_trace: list[tuple],
        record_trace: list[tuple],
        cxxrecord_trace: list[tuple]
    ):
        # 함수 필터 조립
        self.function_filters = [
            AnonymousNamespaceFilter(),
            PrivateAccessFilter(),
            NoLogicFilter(),
            VoidFunctionNoEffectFilter(function_call_trace, enum_trace, record_trace, cxxrecord_trace)
        ]
        self.constructor_filters: list[IPipeline] = [
            AnonymousNamespaceFilter(),
            PrivateAccessFilter(),
            NoLogicFilter(),
            TrivialConstructorFilter(),
        ]
        # if project_name == 'leveldb':
        #     self.function_filters: list[IPipeline] = [
        #         AnonymousNamespaceFilter(),
        #         PrivateAccessFilter(),
        #         NoLogicFilter(),
        #         VoidFunctionNoEffectFilter(function_call_trace, enum_trace, record_trace, cxxrecord_trace)
        #         # SingleStatementFilter(),
        #         # UncalledFunctionFilter(function_call_trace),
        #         # NoTypeDependencyFilter(enum_trace, record_trace, cxxrecord_trace),
        #     ]
        #     # 생성자 필터 조립
        #     self.constructor_filters: list[IPipeline] = [
        #         AnonymousNamespaceFilter(),
        #         PrivateAccessFilter(),
        #         NoLogicFilter(),
        #         TrivialConstructorFilter(),
        #         NoTypeDependencyFilter(enum_trace, record_trace, cxxrecord_trace)
        #     ]
        # elif project_name == "JsonBox":
        #     self.function_filters: list[IPipeline] = [
        #         AnonymousNamespaceFilter(),
        #         PrivateAccessFilter(),
        #         NoLogicFilter(),
        #         SingleStatementFilter(),
        #     ]
        #     # 생성자 필터 조립
        #     self.constructor_filters: list[IPipeline] = [
        #         AnonymousNamespaceFilter(),
        #         PrivateAccessFilter(),
        #         NoLogicFilter(),
        #         TrivialConstructorFilter(),
        #         NoTypeDependencyFilter(enum_trace, record_trace, cxxrecord_trace)
        #     ]
        # else:
        #     self.function_filters: list[IPipeline] = [
        #         AnonymousNamespaceFilter(),
        #         PrivateAccessFilter(),
        #         NoLogicFilter(),
        #         SingleStatementFilter(),
        #         UncalledFunctionFilter(function_call_trace),
        #         NoTypeDependencyFilter(enum_trace, record_trace, cxxrecord_trace),
        #         VoidFunctionNoEffectFilter(function_call_trace, enum_trace, record_trace, cxxrecord_trace)
        #     ]
        #     # 생성자 필터 조립
        #     self.constructor_filters: list[IPipeline] = [
        #         AnonymousNamespaceFilter(),
        #         PrivateAccessFilter(),
        #         NoLogicFilter(),
        #         TrivialConstructorFilter(),
        #         NoTypeDependencyFilter(enum_trace, record_trace, cxxrecord_trace)
        #     ]


    def identify(self, input_type: str, input_data: list[tuple]) -> list[tuple]:
        if input_type == "function":
            filters = self.function_filters
        elif input_type == "constructor":
            filters = self.constructor_filters
        else:
            raise ValueError(f"Unsupported input_type: {input_type}")

        for f in filters:
            input_data = f.identify(input_type, input_data)

        return input_data
