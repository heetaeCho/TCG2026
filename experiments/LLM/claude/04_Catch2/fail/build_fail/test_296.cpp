#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/internal/catch_result_type.hpp"

using namespace Catch;

namespace {

// Helper to create AssertionResult with specific parameters
AssertionResult makeResult(StringRef macroName, StringRef capturedExpression,
                           ResultDisposition::Flags disposition,
                           ResultWas::OfType resultType,
                           std::string message = "",
                           std::string reconstructedExpression = "") {
    AssertionInfo info;
    info.macroName = macroName;
    info.capturedExpression = capturedExpression;
    info.resultDisposition = disposition;

    AssertionResultData data;
    data.resultType = resultType;
    data.message = message;
    data.reconstructedExpression = reconstructedExpression;

    return AssertionResult(info, std::move(data));
}

} // anonymous namespace

class AssertionResultTest_296 : public ::testing::Test {
protected:
};

// ============================================================
// getExpression tests
// ============================================================

TEST_F(AssertionResultTest_296, GetExpression_NormalExpression_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_EQ(result.getExpression(), "a == b");
}

TEST_F(AssertionResultTest_296, GetExpression_FalseTest_WrapsWithNegation_296) {
    auto result = makeResult("REQUIRE_FALSE", "a == b",
                             ResultDisposition::FalseTest,
                             ResultWas::Ok);
    std::string expr = result.getExpression();
    EXPECT_EQ(expr, "!(a == b)");
}

TEST_F(AssertionResultTest_296, GetExpression_EmptyExpression_296) {
    auto result = makeResult("REQUIRE", "",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_EQ(result.getExpression(), "");
}

TEST_F(AssertionResultTest_296, GetExpression_FalseTestEmptyExpression_296) {
    auto result = makeResult("REQUIRE_FALSE", "",
                             ResultDisposition::FalseTest,
                             ResultWas::Ok);
    std::string expr = result.getExpression();
    EXPECT_EQ(expr, "!()");
}

// ============================================================
// hasExpression tests
// ============================================================

TEST_F(AssertionResultTest_296, HasExpression_WithExpression_ReturnsTrue_296) {
    auto result = makeResult("REQUIRE", "x > 0",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_TRUE(result.hasExpression());
}

TEST_F(AssertionResultTest_296, HasExpression_EmptyExpression_ReturnsFalse_296) {
    auto result = makeResult("REQUIRE", "",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_FALSE(result.hasExpression());
}

// ============================================================
// succeeded / isOk tests
// ============================================================

TEST_F(AssertionResultTest_296, Succeeded_WhenOk_ReturnsTrue_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_TRUE(result.succeeded());
}

TEST_F(AssertionResultTest_296, Succeeded_WhenFailed_ReturnsFalse_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::ExpressionFailed);
    EXPECT_FALSE(result.succeeded());
}

TEST_F(AssertionResultTest_296, IsOk_WhenOk_ReturnsTrue_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_TRUE(result.isOk());
}

TEST_F(AssertionResultTest_296, IsOk_WhenFailed_ReturnsFalse_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::ExpressionFailed);
    EXPECT_FALSE(result.isOk());
}

TEST_F(AssertionResultTest_296, IsOk_WhenExplicitFailure_ReturnsFalse_296) {
    auto result = makeResult("FAIL", "",
                             ResultDisposition::Normal,
                             ResultWas::ExplicitFailure);
    EXPECT_FALSE(result.isOk());
}

// ============================================================
// getResultType tests
// ============================================================

TEST_F(AssertionResultTest_296, GetResultType_ReturnsCorrectType_Ok_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

TEST_F(AssertionResultTest_296, GetResultType_ReturnsCorrectType_Failed_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::ExpressionFailed);
    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

TEST_F(AssertionResultTest_296, GetResultType_ReturnsCorrectType_ThrewException_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::ThrewException);
    EXPECT_EQ(result.getResultType(), ResultWas::ThrewException);
}

// ============================================================
// hasMessage / getMessage tests
// ============================================================

TEST_F(AssertionResultTest_296, HasMessage_WithMessage_ReturnsTrue_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::ExpressionFailed,
                             "failure message");
    EXPECT_TRUE(result.hasMessage());
}

TEST_F(AssertionResultTest_296, HasMessage_EmptyMessage_ReturnsFalse_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::Ok,
                             "");
    EXPECT_FALSE(result.hasMessage());
}

TEST_F(AssertionResultTest_296, GetMessage_ReturnsCorrectMessage_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::ExpressionFailed,
                             "expected equal");
    std::string msg = std::string(result.getMessage());
    EXPECT_EQ(msg, "expected equal");
}

// ============================================================
// getExpandedExpression / hasExpandedExpression tests
// ============================================================

TEST_F(AssertionResultTest_296, HasExpandedExpression_WithReconstructed_ReturnsTrue_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::ExpressionFailed,
                             "",
                             "1 == 2");
    EXPECT_TRUE(result.hasExpandedExpression());
}

TEST_F(AssertionResultTest_296, HasExpandedExpression_SameAsOriginal_ReturnsFalse_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::Ok,
                             "",
                             "a == b");
    EXPECT_FALSE(result.hasExpandedExpression());
}

TEST_F(AssertionResultTest_296, GetExpandedExpression_ReturnsDifferentFromOriginal_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::ExpressionFailed,
                             "",
                             "1 == 2");
    EXPECT_EQ(result.getExpandedExpression(), "1 == 2");
}

TEST_F(AssertionResultTest_296, GetExpandedExpression_NoExpression_ReturnsMessage_296) {
    auto result = makeResult("FAIL", "",
                             ResultDisposition::Normal,
                             ResultWas::ExplicitFailure,
                             "explicit fail message",
                             "");
    // When there is no expression, getExpandedExpression should return something meaningful
    std::string expanded = result.getExpandedExpression();
    // It should not be empty - it typically returns the message or some representation
    EXPECT_FALSE(expanded.empty());
}

// ============================================================
// getExpressionInMacro tests
// ============================================================

TEST_F(AssertionResultTest_296, GetExpressionInMacro_NormalDisposition_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    std::string exprInMacro = result.getExpressionInMacro();
    // Should contain the macro name and the expression
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("a == b"), std::string::npos);
}

TEST_F(AssertionResultTest_296, GetExpressionInMacro_FalseTest_296) {
    auto result = makeResult("REQUIRE_FALSE", "a == b",
                             ResultDisposition::FalseTest,
                             ResultWas::Ok);
    std::string exprInMacro = result.getExpressionInMacro();
    EXPECT_NE(exprInMacro.find("REQUIRE_FALSE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("!(a == b)"), std::string::npos);
}

// ============================================================
// getTestMacroName tests
// ============================================================

TEST_F(AssertionResultTest_296, GetTestMacroName_ReturnsCorrectName_296) {
    auto result = makeResult("CHECK", "x > 0",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_EQ(std::string(result.getTestMacroName()), "CHECK");
}

TEST_F(AssertionResultTest_296, GetTestMacroName_RequireFalse_296) {
    auto result = makeResult("REQUIRE_FALSE", "x > 0",
                             ResultDisposition::FalseTest,
                             ResultWas::Ok);
    EXPECT_EQ(std::string(result.getTestMacroName()), "REQUIRE_FALSE");
}

// ============================================================
// getSourceInfo tests
// ============================================================

TEST_F(AssertionResultTest_296, GetSourceInfo_ReturnsValidInfo_296) {
    auto result = makeResult("REQUIRE", "a == b",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    // getSourceInfo should return a SourceLineInfo - just verify it doesn't crash
    auto sourceInfo = result.getSourceInfo();
    // Verify we can access it (basic sanity)
    (void)sourceInfo;
}

// ============================================================
// Edge cases
// ============================================================

TEST_F(AssertionResultTest_296, GetExpression_ComplexExpression_Normal_296) {
    auto result = makeResult("REQUIRE", "func(a, b) == expected && valid",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_EQ(result.getExpression(), "func(a, b) == expected && valid");
}

TEST_F(AssertionResultTest_296, GetExpression_ComplexExpression_FalseTest_296) {
    auto result = makeResult("REQUIRE_FALSE", "func(a, b) == expected && valid",
                             ResultDisposition::FalseTest,
                             ResultWas::Ok);
    EXPECT_EQ(result.getExpression(), "!(func(a, b) == expected && valid)");
}

TEST_F(AssertionResultTest_296, GetExpression_SingleChar_296) {
    auto result = makeResult("CHECK", "x",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_EQ(result.getExpression(), "x");
}

TEST_F(AssertionResultTest_296, GetExpression_SingleChar_FalseTest_296) {
    auto result = makeResult("CHECK_FALSE", "x",
                             ResultDisposition::FalseTest,
                             ResultWas::Ok);
    EXPECT_EQ(result.getExpression(), "!(x)");
}

TEST_F(AssertionResultTest_296, Succeeded_WhenDidntThrow_ReturnsTrue_296) {
    auto result = makeResult("REQUIRE_NOTHROW", "func()",
                             ResultDisposition::Normal,
                             ResultWas::Ok);
    EXPECT_TRUE(result.succeeded());
}

TEST_F(AssertionResultTest_296, IsOk_SuppressFail_296) {
    auto result = makeResult("CHECK", "a == b",
                             ResultDisposition::Flags(ResultDisposition::ContinueOnFailure),
                             ResultWas::ExpressionFailed);
    // With ContinueOnFailure, isOk might behave differently than succeeded
    // Just verify both are callable
    (void)result.isOk();
    (void)result.succeeded();
}
