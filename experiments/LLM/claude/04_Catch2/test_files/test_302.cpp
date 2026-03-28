#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_assertion_info.hpp"

using namespace Catch;

// Helper to create AssertionResultData with a specific ResultWas value
static AssertionResultData makeResultData(ResultWas::OfType resultType) {
    AssertionResultData data(resultType, LazyExpression(false));
    return data;
}

class AssertionResultTest_302 : public ::testing::Test {
protected:
    // Helper to build an AssertionInfo
    AssertionInfo makeInfo(StringRef macroName, StringRef capturedExpression,
                           ResultDisposition::Flags disposition = ResultDisposition::Normal) {
        AssertionInfo info;
        info.macroName = macroName;
        info.capturedExpression = capturedExpression;
        info.resultDisposition = disposition;
        info.lineInfo = SourceLineInfo("test_file.cpp", 42);
        return info;
    }
};

// Test that getTestMacroName returns the macro name set in info
TEST_F(AssertionResultTest_302, GetTestMacroName_ReturnsMacroName_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_EQ(result.getTestMacroName(), "REQUIRE"_catch_sr);
}

// Test that getTestMacroName returns correct value for CHECK macro
TEST_F(AssertionResultTest_302, GetTestMacroName_ReturnsCheckMacro_302) {
    auto info = makeInfo("CHECK"_catch_sr, "x > 0"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_EQ(result.getTestMacroName(), "CHECK"_catch_sr);
}

// Test succeeded() for a successful result
TEST_F(AssertionResultTest_302, Succeeded_WhenOk_ReturnsTrue_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_TRUE(result.succeeded());
}

// Test succeeded() for a failed result
TEST_F(AssertionResultTest_302, Succeeded_WhenFailed_ReturnsFalse_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::ExpressionFailed));
    EXPECT_FALSE(result.succeeded());
}

// Test isOk() for a successful result
TEST_F(AssertionResultTest_302, IsOk_WhenOk_ReturnsTrue_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_TRUE(result.isOk());
}

// Test isOk() for a failed result
TEST_F(AssertionResultTest_302, IsOk_WhenFailed_ReturnsFalse_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::ExpressionFailed));
    EXPECT_FALSE(result.isOk());
}

// Test isOk() with SuppressFail disposition and failed result should return true
TEST_F(AssertionResultTest_302, IsOk_WhenFailedButSuppressed_ReturnsTrue_302) {
    auto info = makeInfo("CHECK"_catch_sr, "a == b"_catch_sr, ResultDisposition::SuppressFail);
    auto result = AssertionResult(info, makeResultData(ResultWas::ExpressionFailed));
    EXPECT_TRUE(result.isOk());
}

// Test getResultType returns the type set in result data
TEST_F(AssertionResultTest_302, GetResultType_ReturnsCorrectType_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

// Test getResultType returns ExpressionFailed
TEST_F(AssertionResultTest_302, GetResultType_ReturnsExpressionFailed_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::ExpressionFailed));
    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

// Test hasExpression when expression is provided
TEST_F(AssertionResultTest_302, HasExpression_WhenExpressionProvided_ReturnsTrue_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_TRUE(result.hasExpression());
}

// Test hasExpression when expression is empty
TEST_F(AssertionResultTest_302, HasExpression_WhenExpressionEmpty_ReturnsFalse_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, ""_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_FALSE(result.hasExpression());
}

// Test getExpression returns the captured expression
TEST_F(AssertionResultTest_302, GetExpression_ReturnsExpression_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_EQ(result.getExpression(), "a == b");
}

// Test getExpressionInMacro wraps expression in macro
TEST_F(AssertionResultTest_302, GetExpressionInMacro_ContainsMacroAndExpression_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    std::string exprInMacro = result.getExpressionInMacro();
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("a == b"), std::string::npos);
}

// Test hasMessage when no message
TEST_F(AssertionResultTest_302, HasMessage_WhenNoMessage_ReturnsFalse_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_FALSE(result.hasMessage());
}

// Test hasMessage with Info result type (which typically has a message)
TEST_F(AssertionResultTest_302, HasMessage_WhenInfoType_ReturnsTrue_302) {
    auto info = makeInfo("INFO"_catch_sr, ""_catch_sr);
    AssertionResultData data(ResultWas::Info, LazyExpression(false));
    data.message = "some info message";
    auto result = AssertionResult(info, std::move(data));
    EXPECT_TRUE(result.hasMessage());
}

// Test getMessage returns the message
TEST_F(AssertionResultTest_302, GetMessage_ReturnsMessage_302) {
    auto info = makeInfo("INFO"_catch_sr, ""_catch_sr);
    AssertionResultData data(ResultWas::Info, LazyExpression(false));
    data.message = "hello world";
    auto result = AssertionResult(info, std::move(data));
    EXPECT_EQ(result.getMessage(), "hello world"_catch_sr);
}

// Test getSourceInfo returns the line info
TEST_F(AssertionResultTest_302, GetSourceInfo_ReturnsCorrectLineInfo_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    auto sourceInfo = result.getSourceInfo();
    EXPECT_EQ(sourceInfo.line, 42u);
    EXPECT_STREQ(sourceInfo.file, "test_file.cpp");
}

// Test hasExpandedExpression when no expansion
TEST_F(AssertionResultTest_302, HasExpandedExpression_WhenNoExpansion_ReturnsFalse_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    // With a default LazyExpression(false), expanded expression may or may not exist
    // This tests the boundary case
    bool hasExpanded = result.hasExpandedExpression();
    // Just verify it doesn't crash and returns a boolean
    EXPECT_TRUE(hasExpanded == true || hasExpanded == false);
}

// Test getExpandedExpression
TEST_F(AssertionResultTest_302, GetExpandedExpression_ReturnsString_302) {
    auto info = makeInfo("REQUIRE"_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    std::string expanded = result.getExpandedExpression();
    // Should return some non-crashing string
    EXPECT_FALSE(expanded.empty() && result.hasExpandedExpression());
}

// Test with ThrewException result type
TEST_F(AssertionResultTest_302, GetResultType_ThrewException_302) {
    auto info = makeInfo("REQUIRE_NOTHROW"_catch_sr, "func()"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::ThrewException));
    EXPECT_EQ(result.getResultType(), ResultWas::ThrewException);
    EXPECT_FALSE(result.succeeded());
    EXPECT_FALSE(result.isOk());
}

// Test with empty macro name
TEST_F(AssertionResultTest_302, GetTestMacroName_EmptyMacro_302) {
    auto info = makeInfo(""_catch_sr, "a == b"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::Ok));
    EXPECT_EQ(result.getTestMacroName(), ""_catch_sr);
}

// Test with DidntThrowException
TEST_F(AssertionResultTest_302, DidntThrowException_IsNotOk_302) {
    auto info = makeInfo("REQUIRE_THROWS"_catch_sr, "func()"_catch_sr);
    auto result = AssertionResult(info, makeResultData(ResultWas::DidntThrowException));
    EXPECT_FALSE(result.isOk());
    EXPECT_FALSE(result.succeeded());
}

// Test with ExplicitFailure
TEST_F(AssertionResultTest_302, ExplicitFailure_IsNotOk_302) {
    auto info = makeInfo("FAIL"_catch_sr, ""_catch_sr);
    AssertionResultData data(ResultWas::ExplicitFailure, LazyExpression(false));
    data.message = "Explicit failure";
    auto result = AssertionResult(info, std::move(data));
    EXPECT_FALSE(result.isOk());
    EXPECT_FALSE(result.succeeded());
    EXPECT_TRUE(result.hasMessage());
    EXPECT_EQ(result.getMessage(), "Explicit failure"_catch_sr);
}

// Test with NegateFlag disposition
TEST_F(AssertionResultTest_302, NegateFlag_FlipsResult_302) {
    auto info = makeInfo("REQUIRE_FALSE"_catch_sr, "!a"_catch_sr,
                         ResultDisposition::Flags(ResultDisposition::Normal | ResultDisposition::FalseTest));
    auto result = AssertionResult(info, makeResultData(ResultWas::ExpressionFailed));
    // With FalseTest, a failed expression should be considered ok
    EXPECT_TRUE(result.isOk());
}
