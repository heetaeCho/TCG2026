#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/app/_re2.cc"



namespace re2_app {

using ::testing::_;

using ::testing::Return;

using ::testing::StrEq;



class InfoTest : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(InfoTest_NormalOperation_172, ValidPattern_ReturnsCorrectInfo_172) {

    Info info = GetInfo("abc");

    EXPECT_EQ(info.pattern, "abc");

    EXPECT_TRUE(info.error.empty());

    EXPECT_TRUE(info.prefix.empty());

    EXPECT_FALSE(info.prefix_foldcase);

    EXPECT_TRUE(info.accel_prefix.empty());

    EXPECT_FALSE(info.accel_prefix_foldcase);

    EXPECT_EQ(info.num_captures, 0);

    EXPECT_FALSE(info.is_one_pass);

    EXPECT_FALSE(info.can_bit_state);

    EXPECT_FALSE(info.bytecode.empty());

    EXPECT_FALSE(info.bytemap.empty());

}



TEST_F(InfoTest_NormalOperation_172, PatternWithCapturingGroup_ReturnsCorrectNumCaptures_172) {

    Info info = GetInfo("(abc)");

    EXPECT_EQ(info.num_captures, 1);

}



TEST_F(InfoTest_NormalOperation_172, CaseInsensitivePattern_ReturnsCaseSensitiveFalse_172) {

    re2::RE2::Options options;

    options.set_case_sensitive(false);



    Info info = GetInfo("abc");

    EXPECT_FALSE(info.prefix_foldcase);

    EXPECT_FALSE(info.accel_prefix_foldcase);

}



TEST_F(InfoTest_BoundaryConditions_172, EmptyPattern_ReturnsError_172) {

    Info info = GetInfo("");

    EXPECT_FALSE(info.error.empty());

}



TEST_F(InfoTest_BoundaryConditions_172, VeryLargePattern_ExceedsMaxMem_ReturnsError_172) {

    std::string large_pattern = std::string(10000000, 'a'); // Assuming max_mem is less than this

    Info info = GetInfo(large_pattern);

    EXPECT_FALSE(info.error.empty());

}



TEST_F(InfoTest_ErrorCases_172, InvalidPattern_ReturnsError_172) {

    Info info = GetInfo("[unclosed");

    EXPECT_FALSE(info.error.empty());

}



TEST_F(InfoTest_VerifyExternalInteractions_172, ValidPattern_CallsRegexpParseOnce_172) {

    using namespace re2;

    auto mock_parse = [](absl::string_view s, ParseFlags flags, RegexpStatus* status) -> Regexp* {

        return new Regexp(RegexpOp::kLiteral, flags);

    };



    testing::StrictMock<testing::FunctionMocker<Regexp*(absl::string_view, ParseFlags, RegexpStatus*)>> mock;

    EXPECT_CALL(mock, Call("abc", _, _)).WillOnce(testing::Invoke(mock_parse));



    // Replace the actual call with the mocked one

    re2::Regexp* (*original_parse)(absl::string_view s, ParseFlags flags, RegexpStatus* status) = &re2::Regexp::Parse;

    re2::Regexp::Parse = mock.AsStdFunction();



    Info info = GetInfo("abc");



    // Restore the original function

    re2::Regexp::Parse = original_parse;



    EXPECT_TRUE(info.error.empty());

}



TEST_F(InfoTest_VerifyExternalInteractions_172, ValidPattern_CallsCompileToProgOnce_172) {

    using namespace re2;

    auto mock_parse = [](absl::string_view s, ParseFlags flags, RegexpStatus* status) -> Regexp* {

        return new Regexp(RegexpOp::kLiteral, flags);

    };



    testing::StrictMock<testing::FunctionMocker<Regexp*(absl::string_view, ParseFlags, RegexpStatus*)>> mock_parse_func;

    EXPECT_CALL(mock_parse_func, Call("abc", _, _)).WillOnce(testing::Invoke(mock_parse));



    auto mock_compile = [](int64_t max_mem) -> Prog* {

        return new Prog();

    };



    testing::StrictMock<testing::FunctionMocker<Prog*(int64_t)>> mock_compile_func;

    EXPECT_CALL(mock_compile_func, Call(_)).WillOnce(testing::Invoke(mock_compile));



    // Replace the actual calls with the mocked ones

    re2::Regexp* (*original_parse)(absl::string_view s, ParseFlags flags, RegexpStatus* status) = &re2::Regexp::Parse;

    re2::Prog* (*original_compile_to_prog)(int64_t max_mem) = &re2::Regexp::CompileToProg;



    re2::Regexp::Parse = mock_parse_func.AsStdFunction();

    re2::Regexp::CompileToProg = mock_compile_func.AsStdFunction();



    Info info = GetInfo("abc");



    // Restore the original functions

    re2::Regexp::Parse = original_parse;

    re2::Regexp::CompileToProg = original_compile_to_prog;



    EXPECT_TRUE(info.error.empty());

}



}  // namespace re2_app
