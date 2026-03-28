#include <gtest/gtest.h>
#include <string>

// Include the necessary headers from the Catch2 project
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;

// Helper to create AssertionResultData with default values
namespace {
    AssertionResultData makeResultData(ResultWas::OfType resultType = ResultWas::Ok) {
        AssertionResultData data(resultType, LazyExpression(false));
        return data;
    }

    AssertionResult makeResult(StringRef macroName, StringRef capturedExpression,
                                ResultWas::OfType resultType = ResultWas::Ok) {
        AssertionInfo info;
        info.macroName = macroName;
        info.capturedExpression = capturedExpression;
        info.resultDisposition = ResultDisposition::Normal;
        return AssertionResult(info, makeResultData(resultType));
    }
}

// Test getExpressionInMacro when macroName is empty
TEST(AssertionResultTest_297, GetExpressionInMacro_EmptyMacroName_ReturnsCapturedExpression_297) {
    auto result = makeResult("", "a == b");
    std::string expr = result.getExpressionInMacro();
    EXPECT_EQ(expr, "a == b");
}

// Test getExpressionInMacro when macroName is non-empty
TEST(AssertionResultTest_297, GetExpressionInMacro_WithMacroName_ReturnsFormattedExpression_297) {
    auto result = makeResult("REQUIRE", "a == b");
    std::string expr = result.getExpressionInMacro();
    EXPECT_EQ(expr, "REQUIRE( a == b )");
}

// Test getExpressionInMacro with CHECK macro name
TEST(AssertionResultTest_297, GetExpressionInMacro_CheckMacro_ReturnsFormattedExpression_297) {
    auto result = makeResult("CHECK", "x > 0");
    std::string expr = result.getExpressionInMacro();
    EXPECT_EQ(expr, "CHECK( x > 0 )");
}

// Test getExpressionInMacro when both macroName and capturedExpression are empty
TEST(AssertionResultTest_297, GetExpressionInMacro_BothEmpty_ReturnsEmptyString_297) {
    auto result = makeResult("", "");
    std::string expr = result.getExpressionInMacro();
    EXPECT_EQ(expr, "");
}

// Test getExpressionInMacro when macroName is set but capturedExpression is empty
TEST(AssertionResultTest_297, GetExpressionInMacro_MacroNameSetExpressionEmpty_ReturnsWrappedEmpty_297) {
    auto result = makeResult("REQUIRE", "");
    std::string expr = result.getExpressionInMacro();
    EXPECT_EQ(expr, "REQUIRE(  )");
}

// Test getExpressionInMacro with long expression
TEST(AssertionResultTest_297, GetExpressionInMacro_LongExpression_ReturnsCorrectFormat_297) {
    auto result = makeResult("REQUIRE_THAT", "someVeryLongVariableName == anotherVeryLongVariableName");
    std::string expr = result.getExpressionInMacro();
    EXPECT_EQ(expr, "REQUIRE_THAT( someVeryLongVariableName == anotherVeryLongVariableName )");
}

// Test getExpression (without macro wrapping)
TEST(AssertionResultTest_297, GetExpression_ReturnsCapturedExpression_297) {
    auto result = makeResult("REQUIRE", "a == b");
    std::string expr = result.getExpression();
    EXPECT_EQ(expr, "a == b");
}

// Test hasExpression when capturedExpression is not empty
TEST(AssertionResultTest_297, HasExpression_NonEmpty_ReturnsTrue_297) {
    auto result = makeResult("REQUIRE", "a == b");
    EXPECT_TRUE(result.hasExpression());
}

// Test hasExpression when capturedExpression is empty
TEST(AssertionResultTest_297, HasExpression_Empty_ReturnsFalse_297) {
    auto result = makeResult("REQUIRE", "");
    EXPECT_FALSE(result.hasExpression());
}

// Test getTestMacroName
TEST(AssertionResultTest_297, GetTestMacroName_ReturnsCorrectMacroName_297) {
    auto result = makeResult("CHECK", "a == b");
    StringRef macroName = result.getTestMacroName();
    EXPECT_EQ(std::string(macroName), "CHECK");
}

// Test succeeded with Ok result
TEST(AssertionResultTest_297, Succeeded_OkResult_ReturnsTrue_297) {
    auto result = makeResult("REQUIRE", "a == b", ResultWas::Ok);
    EXPECT_TRUE(result.succeeded());
}

// Test succeeded with ExpressionFailed result
TEST(AssertionResultTest_297, Succeeded_ExpressionFailed_ReturnsFalse_297) {
    auto result = makeResult("REQUIRE", "a == b", ResultWas::ExpressionFailed);
    EXPECT_FALSE(result.succeeded());
}

// Test isOk with Ok result
TEST(AssertionResultTest_297, IsOk_OkResult_ReturnsTrue_297) {
    auto result = makeResult("REQUIRE", "a == b", ResultWas::Ok);
    EXPECT_TRUE(result.isOk());
}

// Test isOk with ExpressionFailed result
TEST(AssertionResultTest_297, IsOk_ExpressionFailed_ReturnsFalse_297) {
    auto result = makeResult("REQUIRE", "a == b", ResultWas::ExpressionFailed);
    EXPECT_FALSE(result.isOk());
}

// Test getResultType
TEST(AssertionResultTest_297, GetResultType_ReturnsCorrectType_297) {
    auto result = makeResult("REQUIRE", "a == b", ResultWas::Ok);
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

// Test getResultType with ExplicitFailure
TEST(AssertionResultTest_297, GetResultType_ExplicitFailure_ReturnsCorrectType_297) {
    auto result = makeResult("FAIL", "", ResultWas::ExplicitFailure);
    EXPECT_EQ(result.getResultType(), ResultWas::ExplicitFailure);
}

// Test getExpressionInMacro with special characters in expression
TEST(AssertionResultTest_297, GetExpressionInMacro_SpecialCharsInExpression_297) {
    auto result = makeResult("REQUIRE", "str == \"hello world\"");
    std::string expr = result.getExpressionInMacro();
    EXPECT_EQ(expr, "REQUIRE( str == \"hello world\" )");
}

// Test getExpressionInMacro with single character macro name
TEST(AssertionResultTest_297, GetExpressionInMacro_SingleCharMacroName_297) {
    auto result = makeResult("X", "y");
    std::string expr = result.getExpressionInMacro();
    EXPECT_EQ(expr, "X( y )");
}

// Test that m_info is accessible and holds correct values
TEST(AssertionResultTest_297, InfoMember_HoldsCorrectValues_297) {
    auto result = makeResult("REQUIRE", "a == b");
    EXPECT_EQ(std::string(result.m_info.macroName), "REQUIRE");
    EXPECT_EQ(std::string(result.m_info.capturedExpression), "a == b");
}
