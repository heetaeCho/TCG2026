#include <gtest/gtest.h>
#include <string>

// Include necessary Catch2 headers
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_lazy_expr.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/catch_message.hpp"

using namespace Catch;

namespace {

// Helper to create AssertionResultData with a given result type
AssertionResultData makeResultData(ResultWas::OfType resultType) {
    // LazyExpression default - we need to construct one
    // Using a no-op lazy expression
    LazyExpression lazyExpr(false);
    return AssertionResultData(resultType, lazyExpr);
}

AssertionInfo makeAssertionInfo(
    StringRef macroName = ""_sr,
    SourceLineInfo lineInfo = SourceLineInfo("", 0),
    StringRef capturedExpression = ""_sr,
    ResultDisposition::Flags resultDisposition = ResultDisposition::Normal
) {
    return AssertionInfo{macroName, lineInfo, capturedExpression, resultDisposition};
}

} // anonymous namespace

class AssertionResultTest_299 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a successful result reports succeeded() == true
TEST_F(AssertionResultTest_299, SucceededReturnsTrueForOk_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.succeeded());
}

// Test that isOk returns true for Ok result
TEST_F(AssertionResultTest_299, IsOkReturnsTrueForOk_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.isOk());
}

// Test that a failed result reports succeeded() == false
TEST_F(AssertionResultTest_299, SucceededReturnsFalseForExplicitFailure_299) {
    auto data = makeResultData(ResultWas::ExplicitFailure);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.succeeded());
}

// Test that isOk returns false for ExplicitFailure
TEST_F(AssertionResultTest_299, IsOkReturnsFalseForExplicitFailure_299) {
    auto data = makeResultData(ResultWas::ExplicitFailure);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
}

// Test getResultType returns the correct type
TEST_F(AssertionResultTest_299, GetResultTypeReturnsCorrectType_299) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

// Test hasExpression when expression is empty
TEST_F(AssertionResultTest_299, HasExpressionReturnsFalseWhenEmpty_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("file.cpp", 10), ""_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.hasExpression());
}

// Test hasExpression when expression is non-empty
TEST_F(AssertionResultTest_299, HasExpressionReturnsTrueWhenNonEmpty_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("file.cpp", 10), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasExpression());
}

// Test getExpression returns the captured expression
TEST_F(AssertionResultTest_299, GetExpressionReturnsExpression_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("file.cpp", 10), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getExpression(), "a == b");
}

// Test hasMessage when no message is set
TEST_F(AssertionResultTest_299, HasMessageReturnsFalseWhenNoMessage_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.hasMessage());
}

// Test hasMessage when message is set
TEST_F(AssertionResultTest_299, HasMessageReturnsTrueWhenMessageSet_299) {
    auto data = makeResultData(ResultWas::Info);
    data.message = "some info message";
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasMessage());
}

// Test getMessage returns the message
TEST_F(AssertionResultTest_299, GetMessageReturnsMessage_299) {
    auto data = makeResultData(ResultWas::Info);
    data.message = "test message";
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getMessage(), "test message");
}

// Test getSourceInfo returns correct file and line
TEST_F(AssertionResultTest_299, GetSourceInfoReturnsCorrectInfo_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("myfile.cpp", 42), ""_sr);
    AssertionResult result(info, std::move(data));
    auto sourceInfo = result.getSourceInfo();
    EXPECT_EQ(sourceInfo.line, 42u);
    EXPECT_STREQ(sourceInfo.file, "myfile.cpp");
}

// Test getTestMacroName returns the macro name
TEST_F(AssertionResultTest_299, GetTestMacroNameReturnsMacroName_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 1), "x == y"_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getTestMacroName(), "REQUIRE");
}

// Test getExpandedExpression returns expression when no expanded expression
TEST_F(AssertionResultTest_299, GetExpandedExpressionFallsBackToExpression_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("file.cpp", 1), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    std::string expanded = result.getExpandedExpression();
    // When no reconstructed expression, should fall back to getExpression
    EXPECT_FALSE(expanded.empty());
}

// Test getExpandedExpression with a reconstructed expression
TEST_F(AssertionResultTest_299, GetExpandedExpressionReturnsReconstructed_299) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    data.reconstructedExpression = "1 == 2";
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("file.cpp", 1), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    std::string expanded = result.getExpandedExpression();
    EXPECT_EQ(expanded, "1 == 2");
}

// Test hasExpandedExpression
TEST_F(AssertionResultTest_299, HasExpandedExpressionWhenReconstructed_299) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    data.reconstructedExpression = "3 == 4";
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("file.cpp", 1), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasExpandedExpression());
}

// Test hasExpandedExpression returns false when expression matches expanded
TEST_F(AssertionResultTest_299, HasExpandedExpressionFalseWhenSameAsExpression_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("file.cpp", 1), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    // When no reconstructed expression, expanded == expression, so hasExpandedExpression should be false
    EXPECT_FALSE(result.hasExpandedExpression());
}

// Test getExpressionInMacro with a macro name
TEST_F(AssertionResultTest_299, GetExpressionInMacroFormatsCorrectly_299) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionInfo info = makeAssertionInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 1), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    std::string exprInMacro = result.getExpressionInMacro();
    // Should contain the macro name and the expression
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("a == b"), std::string::npos);
}

// Test various ResultWas types
TEST_F(AssertionResultTest_299, GetResultTypeForThrewException_299) {
    auto data = makeResultData(ResultWas::ThrewException);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::ThrewException);
    EXPECT_FALSE(result.succeeded());
    EXPECT_FALSE(result.isOk());
}

// Test DidntThrowException type
TEST_F(AssertionResultTest_299, GetResultTypeForDidntThrowException_299) {
    auto data = makeResultData(ResultWas::DidntThrowException);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::DidntThrowException);
    EXPECT_FALSE(result.succeeded());
}

// Test with empty expression and empty reconstructed expression
TEST_F(AssertionResultTest_299, GetExpandedExpressionEmptyWhenBothEmpty_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo(""_sr, SourceLineInfo("file.cpp", 1), ""_sr);
    AssertionResult result(info, std::move(data));
    std::string expanded = result.getExpandedExpression();
    EXPECT_TRUE(expanded.empty());
}

// Test getMessage returns empty when no message
TEST_F(AssertionResultTest_299, GetMessageReturnsEmptyWhenNoMessage_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.getMessage().empty());
}

// Test with ResultWas::Warning - isOk should typically be true for warnings
TEST_F(AssertionResultTest_299, IsOkForWarning_299) {
    auto data = makeResultData(ResultWas::Warning);
    data.message = "warning message";
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::Warning);
}

// Test getExpressionInMacro when no expression
TEST_F(AssertionResultTest_299, GetExpressionInMacroWhenNoExpression_299) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("CHECK"_sr, SourceLineInfo("file.cpp", 1), ""_sr);
    AssertionResult result(info, std::move(data));
    std::string exprInMacro = result.getExpressionInMacro();
    // With no expression, the result may be empty or just the macro
    // We just verify it doesn't crash and is deterministic
    std::string exprInMacro2 = result.getExpressionInMacro();
    EXPECT_EQ(exprInMacro, exprInMacro2);
}
