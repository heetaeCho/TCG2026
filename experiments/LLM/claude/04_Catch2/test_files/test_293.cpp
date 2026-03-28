#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/internal/catch_lazy_expr.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"

// We need to include enough of Catch2's internals to construct test objects
// If direct includes don't work, we may need catch_all.hpp or similar

namespace {

using namespace Catch;

// Helper to create an AssertionResult with a given result type
AssertionResult makeResult(ResultWas::OfType resultType,
                           const char* macroName = "REQUIRE",
                           const char* expr = "",
                           const char* filename = "test.cpp",
                           std::size_t lineNum = 1,
                           const std::string& message = "") {
    AssertionInfo info;
    info.macroName = StringRef(macroName);
    info.lineInfo = SourceLineInfo(filename, lineNum);
    info.capturedExpression = StringRef(expr);
    info.resultDisposition = ResultDisposition::Normal;

    LazyExpression lazyExpr(false);
    AssertionResultData data(resultType, lazyExpr);
    if (!message.empty()) {
        data.message = message;
    }
    if (expr && expr[0] != '\0') {
        data.reconstructedExpression = expr;
    }

    return AssertionResult(info, std::move(data));
}

class AssertionResultTest_293 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getResultType returns the correct result type for Ok
TEST_F(AssertionResultTest_293, GetResultType_Ok_293) {
    auto result = makeResult(ResultWas::Ok);
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

// Test getResultType returns the correct result type for ExpressionFailed
TEST_F(AssertionResultTest_293, GetResultType_ExpressionFailed_293) {
    auto result = makeResult(ResultWas::ExpressionFailed);
    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

// Test getResultType returns the correct result type for ThrewException
TEST_F(AssertionResultTest_293, GetResultType_ThrewException_293) {
    auto result = makeResult(ResultWas::ThrewException);
    EXPECT_EQ(result.getResultType(), ResultWas::ThrewException);
}

// Test getResultType for ExplicitFailure
TEST_F(AssertionResultTest_293, GetResultType_ExplicitFailure_293) {
    auto result = makeResult(ResultWas::ExplicitFailure);
    EXPECT_EQ(result.getResultType(), ResultWas::ExplicitFailure);
}

// Test succeeded returns true for Ok
TEST_F(AssertionResultTest_293, Succeeded_Ok_293) {
    auto result = makeResult(ResultWas::Ok);
    EXPECT_TRUE(result.succeeded());
}

// Test succeeded returns false for ExpressionFailed
TEST_F(AssertionResultTest_293, Succeeded_ExpressionFailed_293) {
    auto result = makeResult(ResultWas::ExpressionFailed);
    EXPECT_FALSE(result.succeeded());
}

// Test succeeded returns false for ThrewException
TEST_F(AssertionResultTest_293, Succeeded_ThrewException_293) {
    auto result = makeResult(ResultWas::ThrewException);
    EXPECT_FALSE(result.succeeded());
}

// Test isOk returns true for Ok
TEST_F(AssertionResultTest_293, IsOk_Ok_293) {
    auto result = makeResult(ResultWas::Ok);
    EXPECT_TRUE(result.isOk());
}

// Test isOk returns false for ExpressionFailed
TEST_F(AssertionResultTest_293, IsOk_ExpressionFailed_293) {
    auto result = makeResult(ResultWas::ExpressionFailed);
    EXPECT_FALSE(result.isOk());
}

// Test isOk returns false for ExplicitFailure
TEST_F(AssertionResultTest_293, IsOk_ExplicitFailure_293) {
    auto result = makeResult(ResultWas::ExplicitFailure);
    EXPECT_FALSE(result.isOk());
}

// Test hasExpression with a non-empty expression
TEST_F(AssertionResultTest_293, HasExpression_NonEmpty_293) {
    auto result = makeResult(ResultWas::Ok, "REQUIRE", "a == b");
    EXPECT_TRUE(result.hasExpression());
}

// Test hasExpression with an empty expression
TEST_F(AssertionResultTest_293, HasExpression_Empty_293) {
    auto result = makeResult(ResultWas::Ok, "REQUIRE", "");
    EXPECT_FALSE(result.hasExpression());
}

// Test hasMessage with a message
TEST_F(AssertionResultTest_293, HasMessage_WithMessage_293) {
    auto result = makeResult(ResultWas::ExplicitFailure, "REQUIRE", "", "test.cpp", 1, "something went wrong");
    EXPECT_TRUE(result.hasMessage());
}

// Test hasMessage without a message
TEST_F(AssertionResultTest_293, HasMessage_WithoutMessage_293) {
    auto result = makeResult(ResultWas::Ok);
    EXPECT_FALSE(result.hasMessage());
}

// Test getExpression returns the expression string
TEST_F(AssertionResultTest_293, GetExpression_293) {
    auto result = makeResult(ResultWas::Ok, "REQUIRE", "x > 0");
    std::string expr = result.getExpression();
    EXPECT_FALSE(expr.empty());
}

// Test getExpressionInMacro wraps expression with macro name
TEST_F(AssertionResultTest_293, GetExpressionInMacro_293) {
    auto result = makeResult(ResultWas::Ok, "REQUIRE", "x > 0");
    std::string exprInMacro = result.getExpressionInMacro();
    // Should contain the macro name and expression
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
}

// Test getMessage returns the message
TEST_F(AssertionResultTest_293, GetMessage_293) {
    auto result = makeResult(ResultWas::ExplicitFailure, "FAIL", "", "test.cpp", 1, "explicit failure message");
    StringRef msg = result.getMessage();
    EXPECT_FALSE(msg.empty());
}

// Test getSourceInfo returns correct file and line
TEST_F(AssertionResultTest_293, GetSourceInfo_293) {
    auto result = makeResult(ResultWas::Ok, "REQUIRE", "a == b", "myfile.cpp", 42);
    SourceLineInfo sourceInfo = result.getSourceInfo();
    EXPECT_EQ(sourceInfo.line, 42u);
    EXPECT_STREQ(sourceInfo.file, "myfile.cpp");
}

// Test getTestMacroName returns the macro name
TEST_F(AssertionResultTest_293, GetTestMacroName_293) {
    auto result = makeResult(ResultWas::Ok, "CHECK", "a == b");
    StringRef macroName = result.getTestMacroName();
    EXPECT_EQ(macroName, StringRef("CHECK"));
}

// Test hasExpandedExpression when there is a reconstructed expression
TEST_F(AssertionResultTest_293, HasExpandedExpression_293) {
    auto result = makeResult(ResultWas::ExpressionFailed, "REQUIRE", "a == b");
    // Depending on whether lazy expression was set, this might or might not have expanded expression
    // At minimum, we verify the method is callable
    bool hasExpanded = result.hasExpandedExpression();
    (void)hasExpanded; // Just verify it doesn't crash
}

// Test getExpandedExpression
TEST_F(AssertionResultTest_293, GetExpandedExpression_293) {
    auto result = makeResult(ResultWas::ExpressionFailed, "REQUIRE", "a == b");
    std::string expanded = result.getExpandedExpression();
    // Should return something (either the reconstructed expression or original)
    EXPECT_FALSE(expanded.empty());
}

// Test with DidntThrowException result type
TEST_F(AssertionResultTest_293, GetResultType_DidntThrowException_293) {
    auto result = makeResult(ResultWas::DidntThrowException);
    EXPECT_EQ(result.getResultType(), ResultWas::DidntThrowException);
    EXPECT_FALSE(result.succeeded());
    EXPECT_FALSE(result.isOk());
}

// Test with Info result type
TEST_F(AssertionResultTest_293, GetResultType_Info_293) {
    auto result = makeResult(ResultWas::Info, "INFO", "", "test.cpp", 1, "info message");
    EXPECT_EQ(result.getResultType(), ResultWas::Info);
}

// Test with Warning result type
TEST_F(AssertionResultTest_293, GetResultType_Warning_293) {
    auto result = makeResult(ResultWas::Warning, "WARN", "", "test.cpp", 1, "warning message");
    EXPECT_EQ(result.getResultType(), ResultWas::Warning);
}

// Test getExpression when empty expression is provided
TEST_F(AssertionResultTest_293, GetExpression_Empty_293) {
    auto result = makeResult(ResultWas::Ok, "REQUIRE", "");
    std::string expr = result.getExpression();
    EXPECT_TRUE(expr.empty());
}

// Test getExpressionInMacro with empty expression
TEST_F(AssertionResultTest_293, GetExpressionInMacro_EmptyExpr_293) {
    auto result = makeResult(ResultWas::Ok, "REQUIRE", "");
    std::string exprInMacro = result.getExpressionInMacro();
    // With no expression, the macro-wrapped version should also reflect that
    // (may be empty or just contain the macro with empty parens)
}

// Boundary: SourceLineInfo with line 0
TEST_F(AssertionResultTest_293, GetSourceInfo_LineZero_293) {
    auto result = makeResult(ResultWas::Ok, "REQUIRE", "a", "file.cpp", 0);
    SourceLineInfo sourceInfo = result.getSourceInfo();
    EXPECT_EQ(sourceInfo.line, 0u);
}

// Boundary: very long expression
TEST_F(AssertionResultTest_293, GetExpression_LongExpression_293) {
    std::string longExpr(1000, 'x');
    auto result = makeResult(ResultWas::Ok, "REQUIRE", longExpr.c_str());
    std::string expr = result.getExpression();
    EXPECT_FALSE(expr.empty());
}

// Test multiple result types for isOk
TEST_F(AssertionResultTest_293, IsOk_FatalErrorCondition_293) {
    auto result = makeResult(ResultWas::FatalErrorCondition);
    EXPECT_FALSE(result.isOk());
    EXPECT_FALSE(result.succeeded());
}

} // anonymous namespace
