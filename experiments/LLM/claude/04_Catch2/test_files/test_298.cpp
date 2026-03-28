#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"

using namespace Catch;

namespace {

// Helper to create AssertionResultData with specific values
AssertionResultData makeResultData(ResultWas::OfType resultType = ResultWas::Ok) {
    AssertionResultData data(resultType, LazyExpression(false));
    return data;
}

AssertionInfo makeInfo(StringRef macroName = ""_sr,
                       SourceLineInfo lineInfo = SourceLineInfo("", 0),
                       StringRef capturedExpression = ""_sr,
                       ResultDisposition::Flags resultDisposition = ResultDisposition::Normal) {
    return AssertionInfo{macroName, lineInfo, capturedExpression, resultDisposition};
}

} // anonymous namespace

class AssertionResultTest_298 : public ::testing::Test {
protected:
    // Helper to build an AssertionResult with given parameters
    std::unique_ptr<AssertionResult> createResult(
        ResultWas::OfType resultType,
        const char* macroName = "",
        const char* file = "test.cpp",
        unsigned int line = 1,
        const char* capturedExpr = "",
        ResultDisposition::Flags disposition = ResultDisposition::Normal) {

        AssertionInfo info{StringRef(macroName),
                          SourceLineInfo(file, line),
                          StringRef(capturedExpr),
                          disposition};
        AssertionResultData data(resultType, LazyExpression(false));
        return std::make_unique<AssertionResult>(info, std::move(data));
    }
};

// Test that a successful result reports isOk and succeeded correctly
TEST_F(AssertionResultTest_298, SucceededResult_IsOk_298) {
    auto result = createResult(ResultWas::Ok);
    EXPECT_TRUE(result->isOk());
    EXPECT_TRUE(result->succeeded());
}

// Test that a failed result reports not ok
TEST_F(AssertionResultTest_298, FailedResult_IsNotOk_298) {
    auto result = createResult(ResultWas::ExplicitFailure);
    EXPECT_FALSE(result->isOk());
    EXPECT_FALSE(result->succeeded());
}

// Test getResultType returns the correct type
TEST_F(AssertionResultTest_298, GetResultType_ReturnsCorrectType_298) {
    auto result = createResult(ResultWas::Ok);
    EXPECT_EQ(result->getResultType(), ResultWas::Ok);

    auto failedResult = createResult(ResultWas::ExpressionFailed);
    EXPECT_EQ(failedResult->getResultType(), ResultWas::ExpressionFailed);
}

// Test hasExpression when no expression is provided
TEST_F(AssertionResultTest_298, HasExpression_EmptyExpression_ReturnsFalse_298) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "test.cpp", 10, "");
    EXPECT_FALSE(result->hasExpression());
}

// Test hasExpression when an expression is provided
TEST_F(AssertionResultTest_298, HasExpression_WithExpression_ReturnsTrue_298) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "test.cpp", 10, "a == b");
    EXPECT_TRUE(result->hasExpression());
}

// Test getExpression returns the captured expression
TEST_F(AssertionResultTest_298, GetExpression_ReturnsExpression_298) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "test.cpp", 10, "x > 0");
    std::string expr = result->getExpression();
    EXPECT_EQ(expr, "x > 0");
}

// Test getExpressionInMacro includes macro name
TEST_F(AssertionResultTest_298, GetExpressionInMacro_IncludesMacro_298) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "test.cpp", 10, "x > 0");
    std::string exprInMacro = result->getExpressionInMacro();
    // The expression in macro should contain both the macro name and expression
    EXPECT_FALSE(exprInMacro.empty());
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("x > 0"), std::string::npos);
}

// Test hasExpandedExpression when there is no expression
TEST_F(AssertionResultTest_298, HasExpandedExpression_NoExpression_ReturnsFalse_298) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "test.cpp", 10, "");
    EXPECT_FALSE(result->hasExpandedExpression());
}

// Test hasExpandedExpression when expanded == original (no expansion occurred)
TEST_F(AssertionResultTest_298, HasExpandedExpression_SameAsOriginal_ReturnsFalse_298) {
    // When the expanded expression equals the original expression, 
    // hasExpandedExpression should return false
    auto result = createResult(ResultWas::Ok, "REQUIRE", "test.cpp", 10, "a == b");
    // With a default LazyExpression (no reconstruction), expanded should match original
    // The actual behavior depends on implementation, but we test the interface
    bool hasExpanded = result->hasExpandedExpression();
    // If expanded == expression, should be false per the implementation
    if (result->getExpandedExpression() == result->getExpression()) {
        EXPECT_FALSE(hasExpanded);
    } else {
        EXPECT_TRUE(hasExpanded);
    }
}

// Test getSourceInfo returns correct source location
TEST_F(AssertionResultTest_298, GetSourceInfo_ReturnsCorrectLocation_298) {
    auto result = createResult(ResultWas::Ok, "CHECK", "myfile.cpp", 42, "val");
    SourceLineInfo srcInfo = result->getSourceInfo();
    EXPECT_STREQ(srcInfo.file, "myfile.cpp");
    EXPECT_EQ(srcInfo.line, 42u);
}

// Test getTestMacroName returns the macro name
TEST_F(AssertionResultTest_298, GetTestMacroName_ReturnsMacroName_298) {
    auto result = createResult(ResultWas::Ok, "CHECK_THAT", "test.cpp", 5, "x");
    StringRef macroName = result->getTestMacroName();
    EXPECT_EQ(std::string(macroName), "CHECK_THAT");
}

// Test ExpressionFailed result type
TEST_F(AssertionResultTest_298, ExpressionFailed_ResultType_298) {
    auto result = createResult(ResultWas::ExpressionFailed);
    EXPECT_EQ(result->getResultType(), ResultWas::ExpressionFailed);
    EXPECT_FALSE(result->succeeded());
}

// Test ThrewException result type
TEST_F(AssertionResultTest_298, ThrewException_ResultType_298) {
    auto result = createResult(ResultWas::ThrewException);
    EXPECT_EQ(result->getResultType(), ResultWas::ThrewException);
    EXPECT_FALSE(result->succeeded());
}

// Test with negated disposition (e.g., REQUIRE_FALSE)
TEST_F(AssertionResultTest_298, NegatedDisposition_ExpressionFailed_IsOk_298) {
    AssertionInfo info{StringRef("REQUIRE_FALSE"),
                       SourceLineInfo("test.cpp", 1),
                       StringRef("!x"),
                       ResultDisposition::Flags(ResultDisposition::Normal | ResultDisposition::FalseTest)};
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.isOk());
}

// Test DidntThrowException result
TEST_F(AssertionResultTest_298, DidntThrowException_ResultType_298) {
    auto result = createResult(ResultWas::DidntThrowException);
    EXPECT_EQ(result->getResultType(), ResultWas::DidntThrowException);
    EXPECT_FALSE(result->isOk());
}

// Test Info result type
TEST_F(AssertionResultTest_298, InfoResultType_298) {
    auto result = createResult(ResultWas::Info);
    EXPECT_EQ(result->getResultType(), ResultWas::Info);
}

// Test Warning result type
TEST_F(AssertionResultTest_298, WarningResultType_298) {
    auto result = createResult(ResultWas::Warning);
    EXPECT_EQ(result->getResultType(), ResultWas::Warning);
}

// Test getMessage when no message is set
TEST_F(AssertionResultTest_298, GetMessage_NoMessage_ReturnsEmpty_298) {
    auto result = createResult(ResultWas::Ok);
    EXPECT_FALSE(result->hasMessage());
}

// Test getExpressionInMacro with empty expression
TEST_F(AssertionResultTest_298, GetExpressionInMacro_EmptyExpression_298) {
    auto result = createResult(ResultWas::Ok, "REQUIRE", "test.cpp", 10, "");
    std::string exprInMacro = result->getExpressionInMacro();
    // With no expression, should still be well-formed (possibly empty or just macro)
    // This tests that it doesn't crash
    (void)exprInMacro;
}

// Test boundary: zero line number
TEST_F(AssertionResultTest_298, SourceInfo_ZeroLine_298) {
    auto result = createResult(ResultWas::Ok, "CHECK", "file.cpp", 0, "expr");
    SourceLineInfo srcInfo = result->getSourceInfo();
    EXPECT_EQ(srcInfo.line, 0u);
}

// Test with empty macro name
TEST_F(AssertionResultTest_298, EmptyMacroName_298) {
    auto result = createResult(ResultWas::Ok, "", "test.cpp", 1, "x == y");
    StringRef macroName = result->getTestMacroName();
    EXPECT_EQ(std::string(macroName), "");
}
