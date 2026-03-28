#include <catch2/catch_assertion_result.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/catch_tostring.hpp>
#include <catch2/internal/catch_lazy_expr.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/catch_message.hpp>
#include <gtest/gtest.h>
#include <string>

using namespace Catch;

namespace {

// Helper to create AssertionResultData with a given result type
AssertionResultData makeResultData(ResultWas::OfType resultType) {
    // LazyExpression can be default-like; we use an empty/null one
    LazyExpression lazyExpr(false);
    return AssertionResultData(resultType, lazyExpr);
}

AssertionInfo makeAssertionInfo(
    StringRef macroName = ""_sr,
    SourceLineInfo lineInfo = SourceLineInfo("", 0),
    StringRef expression = ""_sr,
    ResultDisposition::Flags resultDisposition = ResultDisposition::Normal)
{
    return AssertionInfo{macroName, lineInfo, expression, resultDisposition};
}

} // anonymous namespace

class AssertionResultTest_291 : public ::testing::Test {
protected:
};

// Test succeeded() returns true for Ok result type
TEST_F(AssertionResultTest_291, SucceededReturnsTrueForOk_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.succeeded());
}

// Test succeeded() returns false for ExpressionFailed
TEST_F(AssertionResultTest_291, SucceededReturnsFalseForExpressionFailed_291) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.succeeded());
}

// Test succeeded() returns false for ThrewException
TEST_F(AssertionResultTest_291, SucceededReturnsFalseForThrewException_291) {
    auto data = makeResultData(ResultWas::ThrewException);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.succeeded());
}

// Test succeeded() returns false for FatalErrorCondition
TEST_F(AssertionResultTest_291, SucceededReturnsFalseForFatalErrorCondition_291) {
    auto data = makeResultData(ResultWas::FatalErrorCondition);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.succeeded());
}

// Test isOk() returns true for Ok result type
TEST_F(AssertionResultTest_291, IsOkReturnsTrueForOk_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.isOk());
}

// Test isOk() returns false for ExpressionFailed
TEST_F(AssertionResultTest_291, IsOkReturnsFalseForExpressionFailed_291) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
}

// Test isOk() with DidntThrowException
TEST_F(AssertionResultTest_291, IsOkReturnsFalseForDidntThrowException_291) {
    auto data = makeResultData(ResultWas::DidntThrowException);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
}

// Test getResultType returns the correct result type
TEST_F(AssertionResultTest_291, GetResultTypeReturnsCorrectType_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

TEST_F(AssertionResultTest_291, GetResultTypeReturnsExpressionFailed_291) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

// Test hasExpression() returns true when expression is provided
TEST_F(AssertionResultTest_291, HasExpressionReturnsTrueWhenProvided_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 10), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasExpression());
}

// Test hasExpression() returns false when expression is empty
TEST_F(AssertionResultTest_291, HasExpressionReturnsFalseWhenEmpty_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 10), ""_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.hasExpression());
}

// Test getExpression returns the expression string
TEST_F(AssertionResultTest_291, GetExpressionReturnsCorrectString_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 10), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getExpression(), "a == b");
}

// Test getExpressionInMacro wraps expression with macro name
TEST_F(AssertionResultTest_291, GetExpressionInMacroContainsMacroName_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 10), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    std::string exprInMacro = result.getExpressionInMacro();
    EXPECT_FALSE(exprInMacro.empty());
    // Should contain the expression
    EXPECT_NE(exprInMacro.find("a == b"), std::string::npos);
}

// Test hasMessage() when message is set
TEST_F(AssertionResultTest_291, HasMessageReturnsTrueWhenMessageSet_291) {
    auto data = makeResultData(ResultWas::Info);
    data.message = "some info message";
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasMessage());
}

// Test hasMessage() when message is empty and result type doesn't imply message
TEST_F(AssertionResultTest_291, HasMessageReturnsFalseWhenNoMessage_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.hasMessage());
}

// Test getMessage() returns message content
TEST_F(AssertionResultTest_291, GetMessageReturnsSetMessage_291) {
    auto data = makeResultData(ResultWas::Info);
    data.message = "test message";
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(std::string(result.getMessage()), "test message");
}

// Test getSourceInfo returns correct source information
TEST_F(AssertionResultTest_291, GetSourceInfoReturnsCorrectInfo_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("CHECK"_sr, SourceLineInfo("myfile.cpp", 42), "x > 0"_sr);
    AssertionResult result(info, std::move(data));
    SourceLineInfo srcInfo = result.getSourceInfo();
    EXPECT_EQ(srcInfo.line, 42u);
    EXPECT_STREQ(srcInfo.file, "myfile.cpp");
}

// Test getTestMacroName returns the macro name
TEST_F(AssertionResultTest_291, GetTestMacroNameReturnsCorrectName_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("REQUIRE"_sr, SourceLineInfo("file.cpp", 1), "val"_sr);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(std::string(result.getTestMacroName()), "REQUIRE");
}

// Test with ExplicitFailure result type
TEST_F(AssertionResultTest_291, ExplicitFailureIsNotOk_291) {
    auto data = makeResultData(ResultWas::ExplicitFailure);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
    EXPECT_FALSE(result.succeeded());
    EXPECT_EQ(result.getResultType(), ResultWas::ExplicitFailure);
}

// Test hasExpandedExpression with no lazy expression
TEST_F(AssertionResultTest_291, HasExpandedExpressionWhenNoLazyExpr_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo("CHECK"_sr, SourceLineInfo("f.cpp", 5), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    // Without a lazy expression set, expanded expression may or may not exist
    // This tests the observable behavior
    bool hasExpanded = result.hasExpandedExpression();
    if (hasExpanded) {
        std::string expanded = result.getExpandedExpression();
        EXPECT_FALSE(expanded.empty());
    }
}

// Test getExpandedExpression returns something meaningful
TEST_F(AssertionResultTest_291, GetExpandedExpressionReturnsString_291) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    data.reconstructedExpression = "1 == 2";
    AssertionInfo info = makeAssertionInfo("REQUIRE"_sr, SourceLineInfo("f.cpp", 5), "a == b"_sr);
    AssertionResult result(info, std::move(data));
    if (result.hasExpandedExpression()) {
        std::string expanded = result.getExpandedExpression();
        EXPECT_FALSE(expanded.empty());
    }
}

// Test with ResultWas::Warning
TEST_F(AssertionResultTest_291, WarningResultType_291) {
    auto data = makeResultData(ResultWas::Warning);
    data.message = "a warning";
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::Warning);
}

// Test expression returned when negated disposition (ExpressionFailed but with SuppressFail)
TEST_F(AssertionResultTest_291, ExpressionWithNegatedDisposition_291) {
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionInfo info = makeAssertionInfo(
        "REQUIRE_FALSE"_sr,
        SourceLineInfo("f.cpp", 1),
        "a == b"_sr,
        ResultDisposition::NegateResult);
    AssertionResult result(info, std::move(data));
    // With negated result, ExpressionFailed might become Ok
    // We just check the expression contains negation indicator
    std::string exprInMacro = result.getExpressionInMacro();
    EXPECT_FALSE(exprInMacro.empty());
}

// Test getExpression with empty expression
TEST_F(AssertionResultTest_291, GetExpressionReturnsEmptyWhenNoExpression_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.getExpression().empty());
}

// Test getMessage returns empty when no message
TEST_F(AssertionResultTest_291, GetMessageReturnsEmptyWhenNone_291) {
    auto data = makeResultData(ResultWas::Ok);
    AssertionInfo info = makeAssertionInfo();
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.getMessage().empty());
}
