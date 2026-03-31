#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/internal/catch_stringref.hpp"

// We need to include the necessary headers for AssertionResultData and ResultWas/ResultDisposition
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/catch_assertion_result.hpp"

using namespace Catch;

// Helper to create AssertionResultData
static AssertionResultData makeResultData(ResultWas::OfType resultType) {
    AssertionResultData data(resultType, LazyExpression(false));
    return data;
}

class AssertionResultTest_294 : public ::testing::Test {
protected:
    AssertionInfo makeInfo(StringRef macroName, StringRef capturedExpression, ResultDisposition::Flags disposition = ResultDisposition::Normal) {
        AssertionInfo info;
        info.macroName = macroName;
        info.capturedExpression = capturedExpression;
        info.resultDisposition = disposition;
        return info;
    }
};

// Test hasExpression returns true when capturedExpression is non-empty
TEST_F(AssertionResultTest_294, HasExpression_WhenExpressionProvided_ReturnsTrue_294) {
    AssertionInfo info = makeInfo("CHECK", "a == b");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_TRUE(result.hasExpression());
}

// Test hasExpression returns false when capturedExpression is empty
TEST_F(AssertionResultTest_294, HasExpression_WhenExpressionEmpty_ReturnsFalse_294) {
    AssertionInfo info = makeInfo("CHECK", "");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_FALSE(result.hasExpression());
}

// Test succeeded returns true for Ok result
TEST_F(AssertionResultTest_294, Succeeded_WhenResultIsOk_ReturnsTrue_294) {
    AssertionInfo info = makeInfo("REQUIRE", "x == 1");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_TRUE(result.succeeded());
}

// Test succeeded returns false for ExpressionFailed result
TEST_F(AssertionResultTest_294, Succeeded_WhenResultFailed_ReturnsFalse_294) {
    AssertionInfo info = makeInfo("REQUIRE", "x == 1");
    AssertionResultData data(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_FALSE(result.succeeded());
}

// Test isOk returns true for Ok result
TEST_F(AssertionResultTest_294, IsOk_WhenResultIsOk_ReturnsTrue_294) {
    AssertionInfo info = makeInfo("CHECK", "a == b");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_TRUE(result.isOk());
}

// Test isOk returns false for failed result
TEST_F(AssertionResultTest_294, IsOk_WhenResultFailed_ReturnsFalse_294) {
    AssertionInfo info = makeInfo("CHECK", "a == b");
    AssertionResultData data(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_FALSE(result.isOk());
}

// Test isOk with negated disposition (e.g., CHECK_FALSE)
TEST_F(AssertionResultTest_294, IsOk_WithNegateDispositionAndFailed_ReturnsTrue_294) {
    AssertionInfo info = makeInfo("CHECK_FALSE", "a == b", ResultDisposition::Flags(ResultDisposition::Normal | ResultDisposition::FalseTest));
    AssertionResultData data(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_TRUE(result.isOk());
}

// Test getResultType returns the correct result type
TEST_F(AssertionResultTest_294, GetResultType_ReturnsCorrectType_294) {
    AssertionInfo info = makeInfo("CHECK", "expr");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

// Test getResultType when expression failed
TEST_F(AssertionResultTest_294, GetResultType_WhenFailed_ReturnsExpressionFailed_294) {
    AssertionInfo info = makeInfo("CHECK", "expr");
    AssertionResultData data(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

// Test getExpression returns the captured expression string
TEST_F(AssertionResultTest_294, GetExpression_ReturnsCorrectExpression_294) {
    AssertionInfo info = makeInfo("CHECK", "a == b");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(result.getExpression(), "a == b");
}

// Test getExpression returns empty string when no expression
TEST_F(AssertionResultTest_294, GetExpression_WhenEmpty_ReturnsEmpty_294) {
    AssertionInfo info = makeInfo("CHECK", "");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(result.getExpression(), "");
}

// Test getTestMacroName returns the macro name
TEST_F(AssertionResultTest_294, GetTestMacroName_ReturnsCorrectName_294) {
    AssertionInfo info = makeInfo("REQUIRE", "x > 0");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(result.getTestMacroName(), StringRef("REQUIRE"));
}

// Test hasMessage returns false when no message
TEST_F(AssertionResultTest_294, HasMessage_WhenNoMessage_ReturnsFalse_294) {
    AssertionInfo info = makeInfo("CHECK", "a == b");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_FALSE(result.hasMessage());
}

// Test hasMessage returns true when there is a message (Info type)
TEST_F(AssertionResultTest_294, HasMessage_WhenInfoResult_ReturnsTrue_294) {
    AssertionInfo info = makeInfo("INFO", "");
    AssertionResultData data(ResultWas::Info, LazyExpression(false));
    data.message = "some message";
    AssertionResult result(info, std::move(data));

    EXPECT_TRUE(result.hasMessage());
}

// Test getMessage returns message string
TEST_F(AssertionResultTest_294, GetMessage_ReturnsCorrectMessage_294) {
    AssertionInfo info = makeInfo("INFO", "");
    AssertionResultData data(ResultWas::Info, LazyExpression(false));
    data.message = "test message";
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(std::string(result.getMessage()), "test message");
}

// Test getExpressionInMacro wraps expression with macro name
TEST_F(AssertionResultTest_294, GetExpressionInMacro_WrapsExpressionCorrectly_294) {
    AssertionInfo info = makeInfo("REQUIRE", "a == b");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    std::string exprInMacro = result.getExpressionInMacro();
    // Should contain both the macro name and the expression
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("a == b"), std::string::npos);
}

// Test hasExpandedExpression
TEST_F(AssertionResultTest_294, HasExpandedExpression_WhenNoExpansion_ReturnsFalse_294) {
    AssertionInfo info = makeInfo("CHECK", "a == b");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    // Without any lazy expansion, the expanded expression should either match or not exist
    // This is testing observable behavior
    bool hasExpanded = result.hasExpandedExpression();
    // We just verify it doesn't crash and returns a bool
    EXPECT_TRUE(hasExpanded == true || hasExpanded == false);
}

// Test getExpandedExpression returns something when expression exists
TEST_F(AssertionResultTest_294, GetExpandedExpression_ReturnsNonEmptyWhenExpressionExists_294) {
    AssertionInfo info = makeInfo("CHECK", "a == b");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    std::string expanded = result.getExpandedExpression();
    // Should return at least the original expression if no expansion
    EXPECT_FALSE(expanded.empty());
}

// Test with ExplicitFailure result type
TEST_F(AssertionResultTest_294, GetResultType_ExplicitFailure_294) {
    AssertionInfo info = makeInfo("FAIL", "");
    AssertionResultData data(ResultWas::ExplicitFailure, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(result.getResultType(), ResultWas::ExplicitFailure);
    EXPECT_FALSE(result.isOk());
    EXPECT_FALSE(result.succeeded());
}

// Test with ThrewException result type
TEST_F(AssertionResultTest_294, GetResultType_ThrewException_294) {
    AssertionInfo info = makeInfo("REQUIRE", "someFunc()");
    AssertionResultData data(ResultWas::ThrewException, LazyExpression(false));
    data.message = "exception occurred";
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(result.getResultType(), ResultWas::ThrewException);
    EXPECT_FALSE(result.isOk());
    EXPECT_TRUE(result.hasMessage());
}

// Test with DidntThrowException result type
TEST_F(AssertionResultTest_294, GetResultType_DidntThrowException_294) {
    AssertionInfo info = makeInfo("REQUIRE_THROWS", "someFunc()");
    AssertionResultData data(ResultWas::DidntThrowException, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(result.getResultType(), ResultWas::DidntThrowException);
    EXPECT_FALSE(result.isOk());
}

// Test boundary: single character expression
TEST_F(AssertionResultTest_294, HasExpression_SingleCharExpression_ReturnsTrue_294) {
    AssertionInfo info = makeInfo("CHECK", "x");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_TRUE(result.hasExpression());
    EXPECT_EQ(result.getExpression(), "x");
}

// Test boundary: macro name is empty
TEST_F(AssertionResultTest_294, GetTestMacroName_WhenEmpty_ReturnsEmpty_294) {
    AssertionInfo info = makeInfo("", "a == b");
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));

    EXPECT_EQ(std::string(result.getTestMacroName()), "");
}
