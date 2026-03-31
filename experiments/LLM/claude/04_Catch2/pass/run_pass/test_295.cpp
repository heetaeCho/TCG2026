#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_lazy_expr.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/interfaces/catch_interfaces_capture.hpp>
#include <catch2/catch_message.hpp>
#include <gtest/gtest.h>
#include <string>

using namespace Catch;

namespace {

// Helper to create AssertionResultData with a given result type
AssertionResultData makeResultData(ResultWas::OfType resultType) {
    LazyExpression lazyExpr(false);
    return AssertionResultData(resultType, lazyExpr);
}

// Helper to create AssertionInfo
AssertionInfo makeInfo(StringRef macroName = "TEST_MACRO"_sr,
                       SourceLineInfo lineInfo = SourceLineInfo("test_file.cpp", 42),
                       StringRef expression = "a == b"_sr) {
    return AssertionInfo{macroName, lineInfo, expression};
}

class AssertionResultTest_295 : public ::testing::Test {
protected:
};

// Test hasMessage when message is empty
TEST_F(AssertionResultTest_295, HasMessageReturnsFalseWhenEmpty_295) {
    auto data = makeResultData(ResultWas::Ok);
    // message should be empty by default
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_FALSE(result.hasMessage());
}

// Test hasMessage when message is non-empty
TEST_F(AssertionResultTest_295, HasMessageReturnsTrueWhenNonEmpty_295) {
    auto data = makeResultData(ResultWas::Ok);
    data.message = "This is a test message";
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_TRUE(result.hasMessage());
}

// Test getMessage returns the message
TEST_F(AssertionResultTest_295, GetMessageReturnsCorrectMessage_295) {
    auto data = makeResultData(ResultWas::Ok);
    data.message = "Expected message";
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_EQ(std::string(result.getMessage()), "Expected message");
}

// Test getResultType returns correct type for Ok
TEST_F(AssertionResultTest_295, GetResultTypeReturnsOk_295) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

// Test getResultType returns correct type for ExpressionFailed
TEST_F(AssertionResultTest_295, GetResultTypeReturnsExpressionFailed_295) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

// Test succeeded returns true for Ok
TEST_F(AssertionResultTest_295, SucceededReturnsTrueForOk_295) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_TRUE(result.succeeded());
}

// Test succeeded returns false for ExpressionFailed
TEST_F(AssertionResultTest_295, SucceededReturnsFalseForFailure_295) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_FALSE(result.succeeded());
}

// Test isOk returns true for Ok
TEST_F(AssertionResultTest_295, IsOkReturnsTrueForOk_295) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_TRUE(result.isOk());
}

// Test isOk returns false for failure
TEST_F(AssertionResultTest_295, IsOkReturnsFalseForFailure_295) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_FALSE(result.isOk());
}

// Test hasExpression returns true when expression is provided
TEST_F(AssertionResultTest_295, HasExpressionReturnsTrueWhenExpressionProvided_295) {
    auto info = makeInfo("CHECK"_sr, SourceLineInfo("file.cpp", 10), "x > 0"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasExpression());
}

// Test hasExpression returns false when expression is empty
TEST_F(AssertionResultTest_295, HasExpressionReturnsFalseWhenEmpty_295) {
    auto info = makeInfo("CHECK"_sr, SourceLineInfo("file.cpp", 10), ""_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.hasExpression());
}

// Test getExpression returns the correct expression
TEST_F(AssertionResultTest_295, GetExpressionReturnsCorrectValue_295) {
    auto info = makeInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 20), "a == b"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getExpression(), "a == b");
}

// Test getSourceInfo returns correct source info
TEST_F(AssertionResultTest_295, GetSourceInfoReturnsCorrectInfo_295) {
    auto info = makeInfo("REQUIRE"_sr, SourceLineInfo("myfile.cpp", 99), "expr"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    auto srcInfo = result.getSourceInfo();
    EXPECT_EQ(srcInfo.line, 99u);
    EXPECT_STREQ(srcInfo.file, "myfile.cpp");
}

// Test getTestMacroName returns correct macro name
TEST_F(AssertionResultTest_295, GetTestMacroNameReturnsCorrectName_295) {
    auto info = makeInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 1), "expr"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(std::string(result.getTestMacroName()), "REQUIRE");
}

// Test getExpressionInMacro wraps expression with macro name
TEST_F(AssertionResultTest_295, GetExpressionInMacroContainsExpression_295) {
    auto info = makeInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 1), "a == b"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    std::string exprInMacro = result.getExpressionInMacro();
    // Should contain both the macro name and the expression
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("a == b"), std::string::npos);
}

// Test with ResultWas::ExplicitFailure
TEST_F(AssertionResultTest_295, ExplicitFailureIsNotOk_295) {
    auto data = makeResultData(ResultWas::ExplicitFailure);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_FALSE(result.isOk());
    EXPECT_FALSE(result.succeeded());
}

// Test with ResultWas::ThrewException
TEST_F(AssertionResultTest_295, ThrewExceptionIsNotOk_295) {
    auto data = makeResultData(ResultWas::ThrewException);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_FALSE(result.isOk());
    EXPECT_FALSE(result.succeeded());
}

// Test hasExpandedExpression when no expansion available
TEST_F(AssertionResultTest_295, HasExpandedExpressionWhenNoExpansion_295) {
    auto info = makeInfo("CHECK"_sr, SourceLineInfo("file.cpp", 5), "x == y"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    // Without a lazy expression that expands differently, behavior depends on implementation
    // We just verify it doesn't crash and returns a bool
    bool hasExpanded = result.hasExpandedExpression();
    (void)hasExpanded;
}

// Test getExpandedExpression doesn't crash
TEST_F(AssertionResultTest_295, GetExpandedExpressionDoesNotCrash_295) {
    auto info = makeInfo("CHECK"_sr, SourceLineInfo("file.cpp", 5), "x == y"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    std::string expanded = result.getExpandedExpression();
    EXPECT_FALSE(expanded.empty());
}

// Test boundary: empty message string
TEST_F(AssertionResultTest_295, EmptyMessageString_295) {
    auto data = makeResultData(ResultWas::Ok);
    data.message = "";
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_FALSE(result.hasMessage());
}

// Test boundary: whitespace-only message
TEST_F(AssertionResultTest_295, WhitespaceOnlyMessageIsConsideredPresent_295) {
    auto data = makeResultData(ResultWas::Ok);
    data.message = "   ";
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_TRUE(result.hasMessage());
}

// Test with DidntThrowException result type
TEST_F(AssertionResultTest_295, DidntThrowExceptionResultType_295) {
    auto data = makeResultData(ResultWas::DidntThrowException);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::DidntThrowException);
    EXPECT_FALSE(result.succeeded());
}

// Test with Info result type
TEST_F(AssertionResultTest_295, InfoResultType_295) {
    auto data = makeResultData(ResultWas::Info);
    data.message = "Informational message";
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::Info);
    EXPECT_TRUE(result.hasMessage());
    EXPECT_EQ(std::string(result.getMessage()), "Informational message");
}

// Test with Warning result type
TEST_F(AssertionResultTest_295, WarningResultType_295) {
    auto data = makeResultData(ResultWas::Warning);
    AssertionResult result(makeInfo(), std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::Warning);
}

} // anonymous namespace
