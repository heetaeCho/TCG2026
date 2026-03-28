#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_lazy_expr.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/catch_tostring.hpp"

using namespace Catch;

class AssertionResultTest_300 : public ::testing::Test {
protected:
    // Helper to create AssertionResult with given parameters
    AssertionResult createResult(
        ResultWas::OfType resultType,
        const std::string& macroName = "REQUIRE",
        const std::string& expr = "",
        const SourceLineInfo& lineInfo = SourceLineInfo("test.cpp", 1),
        const std::string& message = ""
    ) {
        AssertionInfo info;
        info.macroName = StringRef(macroName.c_str());
        info.lineInfo = lineInfo;
        info.capturedExpression = StringRef(expr.c_str());

        LazyExpression lazyExpr(false);
        AssertionResultData data(resultType, lazyExpr);
        data.message = message;

        return AssertionResult(info, std::move(data));
    }
};

// Test getMessage returns the message set in result data
TEST_F(AssertionResultTest_300, GetMessageReturnsSetMessage_300) {
    auto result = createResult(ResultWas::ExplicitFailure, "REQUIRE", "a == b",
                               SourceLineInfo("file.cpp", 10), "custom message");
    EXPECT_EQ(std::string(result.getMessage()), "custom message");
}

// Test getMessage returns empty when no message set
TEST_F(AssertionResultTest_300, GetMessageReturnsEmptyWhenNoMessage_300) {
    auto result = createResult(ResultWas::Ok);
    EXPECT_EQ(std::string(result.getMessage()), "");
}

// Test succeeded returns true for Ok result
TEST_F(AssertionResultTest_300, SucceededReturnsTrueForOk_300) {
    auto result = createResult(ResultWas::Ok);
    EXPECT_TRUE(result.succeeded());
}

// Test succeeded returns false for ExplicitFailure
TEST_F(AssertionResultTest_300, SucceededReturnsFalseForExplicitFailure_300) {
    auto result = createResult(ResultWas::ExplicitFailure);
    EXPECT_FALSE(result.succeeded());
}

// Test succeeded returns false for ExpressionFailed
TEST_F(AssertionResultTest_300, SucceededReturnsFalseForExpressionFailed_300) {
    auto result = createResult(ResultWas::ExpressionFailed);
    EXPECT_FALSE(result.succeeded());
}

// Test isOk returns true for Ok result
TEST_F(AssertionResultTest_300, IsOkReturnsTrueForOkResult_300) {
    auto result = createResult(ResultWas::Ok);
    EXPECT_TRUE(result.isOk());
}

// Test isOk returns false for failure results
TEST_F(AssertionResultTest_300, IsOkReturnsFalseForFailure_300) {
    auto result = createResult(ResultWas::ExpressionFailed);
    EXPECT_FALSE(result.isOk());
}

// Test getResultType returns the correct type
TEST_F(AssertionResultTest_300, GetResultTypeReturnsCorrectType_300) {
    auto result = createResult(ResultWas::Ok);
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

TEST_F(AssertionResultTest_300, GetResultTypeReturnsExplicitFailure_300) {
    auto result = createResult(ResultWas::ExplicitFailure);
    EXPECT_EQ(result.getResultType(), ResultWas::ExplicitFailure);
}

// Test hasExpression returns true when expression is present
TEST_F(AssertionResultTest_300, HasExpressionReturnsTrueWhenExprSet_300) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "a == b");
    EXPECT_TRUE(result.hasExpression());
}

// Test hasExpression returns false when expression is empty
TEST_F(AssertionResultTest_300, HasExpressionReturnsFalseWhenEmpty_300) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "");
    EXPECT_FALSE(result.hasExpression());
}

// Test hasMessage returns true when message is set
TEST_F(AssertionResultTest_300, HasMessageReturnsTrueWhenMessageSet_300) {
    auto result = createResult(ResultWas::ExplicitFailure, "REQUIRE", "", 
                               SourceLineInfo("f.cpp", 1), "error msg");
    EXPECT_TRUE(result.hasMessage());
}

// Test hasMessage returns false when no message
TEST_F(AssertionResultTest_300, HasMessageReturnsFalseWhenNoMessage_300) {
    auto result = createResult(ResultWas::Ok);
    EXPECT_FALSE(result.hasMessage());
}

// Test getExpression returns expression string
TEST_F(AssertionResultTest_300, GetExpressionReturnsExpression_300) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "x > 0");
    EXPECT_EQ(result.getExpression(), "x > 0");
}

// Test getExpression returns empty string when no expression
TEST_F(AssertionResultTest_300, GetExpressionReturnsEmptyWhenNone_300) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "");
    EXPECT_EQ(result.getExpression(), "");
}

// Test getExpressionInMacro wraps expression with macro name
TEST_F(AssertionResultTest_300, GetExpressionInMacroContainsMacroName_300) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "a == b");
    std::string exprInMacro = result.getExpressionInMacro();
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("a == b"), std::string::npos);
}

// Test getSourceInfo returns correct source info
TEST_F(AssertionResultTest_300, GetSourceInfoReturnsCorrectInfo_300) {
    SourceLineInfo srcInfo("myfile.cpp", 42);
    auto result = createResult(ResultWas::Ok, "REQUIRE", "x", srcInfo);
    SourceLineInfo retrieved = result.getSourceInfo();
    EXPECT_EQ(retrieved.line, 42u);
    EXPECT_STREQ(retrieved.file, "myfile.cpp");
}

// Test getTestMacroName returns the macro name
TEST_F(AssertionResultTest_300, GetTestMacroNameReturnsMacroName_300) {
    auto result = createResult(ResultWas::Ok, "CHECK", "val");
    EXPECT_EQ(std::string(result.getTestMacroName()), "CHECK");
}

// Test with ThrewException result type
TEST_F(AssertionResultTest_300, ThrewExceptionResultType_300) {
    auto result = createResult(ResultWas::ThrewException);
    EXPECT_EQ(result.getResultType(), ResultWas::ThrewException);
    EXPECT_FALSE(result.succeeded());
    EXPECT_FALSE(result.isOk());
}

// Test with DidntThrowException result type
TEST_F(AssertionResultTest_300, DidntThrowExceptionResultType_300) {
    auto result = createResult(ResultWas::DidntThrowException);
    EXPECT_EQ(result.getResultType(), ResultWas::DidntThrowException);
    EXPECT_FALSE(result.succeeded());
}

// Test hasExpandedExpression
TEST_F(AssertionResultTest_300, HasExpandedExpressionWhenNoExpression_300) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "");
    EXPECT_FALSE(result.hasExpandedExpression());
}

// Test with message containing special characters
TEST_F(AssertionResultTest_300, MessageWithSpecialCharacters_300) {
    auto result = createResult(ResultWas::ExplicitFailure, "FAIL", "",
                               SourceLineInfo("t.cpp", 1), 
                               "error: unexpected 'value' with \"quotes\" & <brackets>");
    EXPECT_EQ(std::string(result.getMessage()), 
              "error: unexpected 'value' with \"quotes\" & <brackets>");
}

// Test with very long message
TEST_F(AssertionResultTest_300, LongMessage_300) {
    std::string longMsg(10000, 'x');
    auto result = createResult(ResultWas::ExplicitFailure, "FAIL", "",
                               SourceLineInfo("t.cpp", 1), longMsg);
    EXPECT_EQ(std::string(result.getMessage()), longMsg);
}

// Test isOk for OkButWithWarnings (if it exists as warn-type)
TEST_F(AssertionResultTest_300, IsOkReturnsTrueForWarning_300) {
    auto result = createResult(ResultWas::Warning);
    // Warning results should still be considered "ok"
    EXPECT_TRUE(result.isOk());
}
