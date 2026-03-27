class PostRenderProcessor:
    def __init__(self):
        self.objectives = \
"""\
Instruction: Write C++ unit test case following the below.
Objectives
#1. Achieve 100% line coverage and 100% branch coverage through C++ unit tests.
 - Every line and every branch in the target code must be executed at least once.
#2. Use Google Test’s TEST_F format for all unit tests.
 - All tests must follow the TEST_F(TestSuiteName, TestName) structure exactly.
#3. Implement each test using only the minimal necessary setup and assertions required to cover the specified branches.
 - Do not add logic beyond what is present in the provided code.
#4. All tests must strictly adhere to the Mandates.
 - Any test that violates a Mandate is invalid, regardless of coverage or format.\
"""
        self.mandates = \
"""\
Mandates:
#1. Execute every branch without exception.
 - Each test case must explicitly satisfy the conditions needed to execute a specific branch.
 - Any prerequisite branches that must be passed through to reach a target branch must also be covered.
#2. Match parameter types exactly—no exceptions.
 - Parameter types must match exactly, including const qualifiers, references, and pointer indicators.
 - No implicit conversions, type promotions, or use of derived/base types is allowed.
#3. Use extern if no declaration exists.
 - If the target function is not declared in the visible scope, declare it using extern with the exact signature.
#4. Use only the given information—never assume.
 - Do not assume the existence, behavior, or structure of any code element not explicitly provided.
 - No inferred logic, helper methods, or undocumented dependencies are allowed.
#5. Include the test ID in every test suite and test name.
 - The test ID must appear as a continuous substring in both the test suite name and the test name (e.g., TEST_F(TEST_SUITE_01, TEST_CASE_01)) .
 - Only uppercase letters and digits are allowed—no symbols, underscores, or lowercase letters.
#6. Never access private members.
 - Private members must not be accessed directly or indirectly.
 - Techniques such as friend declarations, reflection, or helper accessors that expose private data are strictly prohibited.
#7. Explicitly declare required namespaces using using namespace.
 - If a namespace is needed, declare it explicitly in the test file using using namespace.
 - Do not rely on implicit or assumed namespace resolution.
#8. Include the gtest header, any required headers, and all provided headers at the very top of the test code.
 - All headers must be included in the exact order specified, starting from the top of the test file.
 - You may only include standard headers if they are required for compilation. Do not insert or reorder headers arbitrarily.\
"""
        self.target_prompt = "The target_function includes following headers {}\nAnd the test target function is {}\n"
        self.transition_prompt = "The following information is for reference only. Do not modify, assume, or reinterpret its content.\n"
        self.cxxrecord_prompt = "To test the target_function, you may refer to the following CXXRecord {}\n"
        self.enum_prompt = "To test the target_function, you may refer to the following Enum {}\n"
        self.record_prompt = "To test the target_function, you may refer to the following Record {}\n"
        self.constructor_callee_of_target_prompt = \
            "To test the target_function, you may refer to the following Constructors that callee of the test target function {}\n"
        self.constructor_caller_of_target_prompt = \
            "To test the target_function, you may refer to the following Constructors that caller of the test target function {}\n"
        self.function_callee_of_target_prompt = \
            "To test the target_function, you may refer to the following Functions that callee of the test target function {}\n"
        self.function_caller_of_target_prompt = \
            "To test the target_function, you may refer to the following Functions that caller of the test target function {}\n"

    def run(self, target_map):
        # map.keys() = ['headers', 'target_function', 'cxxrecord', 'enum', 'record', 
        #               'constructor_callee_of_target', 'constructor_caller_of_target', 
        #               'function_callee_of_target', 'function_caller_of_target']
        must_in_list = ['headers', 'target_function']
        key_order_list = ['cxxrecord', 'enum', 'record', \
                          'constructor_callee_of_target', 'constructor_caller_of_target', \
                          'function_callee_of_target', 'function_caller_of_target']
        prompt_map = {
            key_order_list[0] : self.cxxrecord_prompt,
            key_order_list[1] : self.enum_prompt,
            key_order_list[2] : self.record_prompt,
            key_order_list[3] : self.constructor_callee_of_target_prompt,
            key_order_list[4] : self.constructor_caller_of_target_prompt,
            key_order_list[5] : self.function_callee_of_target_prompt,
            key_order_list[6] : self.function_caller_of_target_prompt
        }

        prompt = self.objectives + '\n' + self.mandates + '\n\n'
        prompt = prompt + self.target_prompt.format(target_map[must_in_list[0]].replace('\n', ' '), target_map[must_in_list[1]])
        prompt = prompt + self.transition_prompt

        for key in key_order_list:
            if key in target_map.keys():
                temp_prompt = prompt_map[key]
                prompt = prompt + temp_prompt.format(target_map[key])
        return prompt