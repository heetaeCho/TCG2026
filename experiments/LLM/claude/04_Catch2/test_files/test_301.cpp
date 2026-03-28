#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_assertion_info.hpp"

using namespace Catch;

// Helper to create AssertionResultData with a specific ResultWas value
namespace {

AssertionResultData makeResultData(ResultWas::OfType resultType) {
    AssertionResultData data(resultType, LazyExpression(false));
    return data;
}

AssertionResultData makeResultDataWithMessage(ResultWas::OfType resultType, const std::string& msg) {
    AssertionResultData data(resultType, LazyExpression(false));
    data.message = msg;
    return data;
}

AssertionInfo makeInfo(StringRef macroName, StringRef capturedExpression, 
                       ResultDisposition::Flags disposition, 
                       SourceLineInfo lineInfo) {
    AssertionInfo info;
    info.macroName = macroName;
    info.capturedExpression = capturedExpression;
    info.resultDisposition = disposition;
    info.lineInfo = lineInfo;
    return info;
}

} // anonymous namespace

class AssertionResultTest_301 : public ::testing::Test {
protected:
    SourceLineInfo defaultLineInfo{"test_file.cpp", 42};
};

// Test getSourceInfo returns the correct source line info
TEST_F(AssertionResultTest_301, GetSourceInfo_ReturnsCorrectLineInfo_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, SourceLineInfo("myfile.cpp", 100));
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    auto sourceInfo = result.getSourceInfo();
    EXPECT_STREQ(sourceInfo.file, "myfile.cpp");
    EXPECT_EQ(sourceInfo.line, 100u);
}

// Test getTestMacroName returns the macro name
TEST_F(AssertionResultTest_301, GetTestMacroName_ReturnsCorrectMacroName_301) {
    auto info = makeInfo("CHECK"_catch_sr, "a == b"_catch_sr, 
                         ResultDisposition::ContinueOnFailure, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    EXPECT_EQ(result.getTestMacroName(), "CHECK"_catch_sr);
}

// Test succeeded returns true when result is Ok
TEST_F(AssertionResultTest_301, Succeeded_ReturnsTrueOnOk_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    EXPECT_TRUE(result.succeeded());
}

// Test succeeded returns false when result is ExpressionFailed
TEST_F(AssertionResultTest_301, Succeeded_ReturnsFalseOnFailure_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(info, std::move(data));
    
    EXPECT_FALSE(result.succeeded());
}

// Test isOk returns true when result is Ok
TEST_F(AssertionResultTest_301, IsOk_ReturnsTrueOnOk_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    EXPECT_TRUE(result.isOk());
}

// Test isOk returns false on failure
TEST_F(AssertionResultTest_301, IsOk_ReturnsFalseOnFailure_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(info, std::move(data));
    
    EXPECT_FALSE(result.isOk());
}

// Test getResultType returns the correct result type
TEST_F(AssertionResultTest_301, GetResultType_ReturnsCorrectType_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

// Test getResultType returns ExpressionFailed
TEST_F(AssertionResultTest_301, GetResultType_ReturnsExpressionFailed_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(info, std::move(data));
    
    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

// Test hasExpression returns true when expression is provided
TEST_F(AssertionResultTest_301, HasExpression_ReturnsTrueWhenExpressionExists_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    EXPECT_TRUE(result.hasExpression());
}

// Test hasExpression returns false when expression is empty
TEST_F(AssertionResultTest_301, HasExpression_ReturnsFalseWhenExpressionEmpty_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, ""_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    EXPECT_FALSE(result.hasExpression());
}

// Test getExpression returns the captured expression
TEST_F(AssertionResultTest_301, GetExpression_ReturnsCorrectExpression_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    EXPECT_EQ(result.getExpression(), "x == 1");
}

// Test hasMessage returns true when message exists
TEST_F(AssertionResultTest_301, HasMessage_ReturnsTrueWhenMessageExists_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultDataWithMessage(ResultWas::ExpressionFailed, "some message");
    AssertionResult result(info, std::move(data));
    
    EXPECT_TRUE(result.hasMessage());
}

// Test hasMessage returns false when no message
TEST_F(AssertionResultTest_301, HasMessage_ReturnsFalseWhenNoMessage_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    EXPECT_FALSE(result.hasMessage());
}

// Test getMessage returns the stored message
TEST_F(AssertionResultTest_301, GetMessage_ReturnsCorrectMessage_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultDataWithMessage(ResultWas::ExpressionFailed, "failure reason");
    AssertionResult result(info, std::move(data));
    
    EXPECT_EQ(std::string(result.getMessage()), "failure reason");
}

// Test getExpressionInMacro wraps expression with macro name
TEST_F(AssertionResultTest_301, GetExpressionInMacro_WrapsExpressionWithMacro_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    std::string exprInMacro = result.getExpressionInMacro();
    // The expression in macro should contain both the macro name and the expression
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("x == 1"), std::string::npos);
}

// Test with negated disposition and ExpressionFailed should succeed
TEST_F(AssertionResultTest_301, IsOk_WithNegateFlag_InvertsResult_301) {
    auto info = makeInfo("REQUIRE_FALSE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Flags(ResultDisposition::Normal | ResultDisposition::FalseTest), 
                         defaultLineInfo);
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(info, std::move(data));
    
    EXPECT_TRUE(result.isOk());
}

// Test with ExplicitFailure result type
TEST_F(AssertionResultTest_301, GetResultType_ExplicitFailure_301) {
    auto info = makeInfo("FAIL"_catch_sr, ""_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::ExplicitFailure);
    AssertionResult result(info, std::move(data));
    
    EXPECT_EQ(result.getResultType(), ResultWas::ExplicitFailure);
    EXPECT_FALSE(result.isOk());
    EXPECT_FALSE(result.succeeded());
}

// Test getExpandedExpression with no expansion
TEST_F(AssertionResultTest_301, HasExpandedExpression_WhenNoExpansion_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    // Even without expansion, getExpandedExpression should return something
    std::string expanded = result.getExpandedExpression();
    EXPECT_FALSE(expanded.empty());
}

// Test source info with different file and line
TEST_F(AssertionResultTest_301, GetSourceInfo_DifferentFileAndLine_301) {
    auto info = makeInfo("CHECK"_catch_sr, "a > b"_catch_sr, 
                         ResultDisposition::ContinueOnFailure, 
                         SourceLineInfo("another_file.cpp", 999));
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    auto srcInfo = result.getSourceInfo();
    EXPECT_STREQ(srcInfo.file, "another_file.cpp");
    EXPECT_EQ(srcInfo.line, 999u);
}

// Test with ThrewException result type
TEST_F(AssertionResultTest_301, GetResultType_ThrewException_301) {
    auto info = makeInfo("REQUIRE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Normal, defaultLineInfo);
    auto data = makeResultData(ResultWas::ThrewException);
    AssertionResult result(info, std::move(data));
    
    EXPECT_EQ(result.getResultType(), ResultWas::ThrewException);
    EXPECT_FALSE(result.isOk());
}

// Test getExpression with negated expression
TEST_F(AssertionResultTest_301, GetExpression_NegatedExpression_301) {
    auto info = makeInfo("REQUIRE_FALSE"_catch_sr, "x == 1"_catch_sr, 
                         ResultDisposition::Flags(ResultDisposition::Normal | ResultDisposition::FalseTest), 
                         defaultLineInfo);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    
    std::string expr = result.getExpression();
    // With FalseTest, the expression should be negated
    EXPECT_NE(expr.find("!"), std::string::npos);
}
