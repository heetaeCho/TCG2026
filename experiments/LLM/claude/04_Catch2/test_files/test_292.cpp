#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_result_type.hpp"
#include "catch2/catch_lazy_expr.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_tostring.hpp"

using namespace Catch;

namespace {

// Helper to create AssertionResultData with a given result type
AssertionResultData makeResultData(ResultWas::OfType resultType) {
    return AssertionResultData(resultType, LazyExpression(false));
}

// Helper to create AssertionInfo
AssertionInfo makeInfo(StringRef macroName = ""_sr,
                       StringRef capturedExpression = ""_sr,
                       ResultDisposition::Flags disposition = ResultDisposition::Normal) {
    return AssertionInfo{macroName, capturedExpression, {}, disposition};
}

AssertionInfo makeInfoWithDisposition(ResultDisposition::Flags disposition,
                                      StringRef macroName = ""_sr,
                                      StringRef capturedExpression = ""_sr) {
    return AssertionInfo{macroName, capturedExpression, {}, disposition};
}

} // anonymous namespace

class AssertionResultTest_292 : public ::testing::Test {
protected:
};

// ==================== isOk() tests ====================

TEST_F(AssertionResultTest_292, IsOk_WhenResultIsOk_ReturnsTrue_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.isOk());
}

TEST_F(AssertionResultTest_292, IsOk_WhenExpressionFailed_ReturnsFalse_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
}

TEST_F(AssertionResultTest_292, IsOk_WhenExplicitFailure_ReturnsFalse_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::ExplicitFailure);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
}

TEST_F(AssertionResultTest_292, IsOk_WhenFailureSuppressed_ReturnsTrue_292) {
    auto info = makeInfoWithDisposition(ResultDisposition::SuppressFail);
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.isOk());
}

TEST_F(AssertionResultTest_292, IsOk_WhenDidntThrowAndNormal_ReturnsFalse_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::DidntThrowException);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
}

// ==================== succeeded() tests ====================

TEST_F(AssertionResultTest_292, Succeeded_WhenResultIsOk_ReturnsTrue_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.succeeded());
}

TEST_F(AssertionResultTest_292, Succeeded_WhenExpressionFailed_ReturnsFalse_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.succeeded());
}

// ==================== getResultType() tests ====================

TEST_F(AssertionResultTest_292, GetResultType_ReturnsCorrectType_Ok_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::Ok);
}

TEST_F(AssertionResultTest_292, GetResultType_ReturnsCorrectType_ExpressionFailed_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::ExpressionFailed);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::ExpressionFailed);
}

TEST_F(AssertionResultTest_292, GetResultType_ReturnsCorrectType_ExplicitFailure_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::ExplicitFailure);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::ExplicitFailure);
}

TEST_F(AssertionResultTest_292, GetResultType_ReturnsCorrectType_ThrewException_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::ThrewException);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getResultType(), ResultWas::ThrewException);
}

// ==================== hasExpression() tests ====================

TEST_F(AssertionResultTest_292, HasExpression_WhenExpressionProvided_ReturnsTrue_292) {
    auto info = makeInfo(""_sr, "a == b"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasExpression());
}

TEST_F(AssertionResultTest_292, HasExpression_WhenNoExpression_ReturnsFalse_292) {
    auto info = makeInfo(""_sr, ""_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.hasExpression());
}

// ==================== hasMessage() tests ====================

TEST_F(AssertionResultTest_292, HasMessage_WhenMessageSet_ReturnsTrue_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Info);
    data.message = "some message";
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasMessage());
}

TEST_F(AssertionResultTest_292, HasMessage_WhenNoMessage_ReturnsFalse_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.hasMessage());
}

// ==================== getExpression() tests ====================

TEST_F(AssertionResultTest_292, GetExpression_ReturnsCorrectExpression_292) {
    auto info = makeInfo(""_sr, "x > 0"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getExpression(), "x > 0");
}

TEST_F(AssertionResultTest_292, GetExpression_WhenEmpty_ReturnsEmpty_292) {
    auto info = makeInfo(""_sr, ""_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getExpression(), "");
}

// ==================== getExpressionInMacro() tests ====================

TEST_F(AssertionResultTest_292, GetExpressionInMacro_ContainsMacroAndExpression_292) {
    auto info = makeInfo("REQUIRE"_sr, "x == 5"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    std::string exprInMacro = result.getExpressionInMacro();
    EXPECT_FALSE(exprInMacro.empty());
    EXPECT_NE(exprInMacro.find("REQUIRE"), std::string::npos);
    EXPECT_NE(exprInMacro.find("x == 5"), std::string::npos);
}

// ==================== getMessage() tests ====================

TEST_F(AssertionResultTest_292, GetMessage_ReturnsSetMessage_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Info);
    data.message = "test message";
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getMessage(), "test message"_sr);
}

TEST_F(AssertionResultTest_292, GetMessage_WhenEmpty_ReturnsEmpty_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.getMessage().empty());
}

// ==================== getTestMacroName() tests ====================

TEST_F(AssertionResultTest_292, GetTestMacroName_ReturnsCorrectMacroName_292) {
    auto info = makeInfo("CHECK"_sr, "a == b"_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_EQ(result.getTestMacroName(), "CHECK"_sr);
}

TEST_F(AssertionResultTest_292, GetTestMacroName_WhenEmpty_ReturnsEmpty_292) {
    auto info = makeInfo(""_sr, ""_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.getTestMacroName().empty());
}

// ==================== hasExpandedExpression() tests ====================

TEST_F(AssertionResultTest_292, HasExpandedExpression_WhenReconstructedDiffersFromOriginal_292) {
    auto info = makeInfo(""_sr, "a == b"_sr);
    auto data = makeResultData(ResultWas::ExpressionFailed);
    data.reconstructedExpression = "1 == 2";
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.hasExpandedExpression());
}

TEST_F(AssertionResultTest_292, HasExpandedExpression_WhenNoExpression_ReturnsFalse_292) {
    auto info = makeInfo(""_sr, ""_sr);
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.hasExpandedExpression());
}

// ==================== getExpandedExpression() tests ====================

TEST_F(AssertionResultTest_292, GetExpandedExpression_ReturnsReconstructedExpression_292) {
    auto info = makeInfo(""_sr, "a == b"_sr);
    auto data = makeResultData(ResultWas::ExpressionFailed);
    data.reconstructedExpression = "1 == 2";
    AssertionResult result(info, std::move(data));
    std::string expanded = result.getExpandedExpression();
    EXPECT_FALSE(expanded.empty());
}

// ==================== Various ResultWas types ====================

TEST_F(AssertionResultTest_292, IsOk_WhenResultIsInfo_ReturnsTrue_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Info);
    AssertionResult result(info, std::move(data));
    // Info is considered Ok
    EXPECT_TRUE(result.isOk());
}

TEST_F(AssertionResultTest_292, IsOk_WhenResultIsWarning_ReturnsTrue_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::Warning);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.isOk());
}

TEST_F(AssertionResultTest_292, IsOk_WhenThrewException_ReturnsFalse_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::ThrewException);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
}

TEST_F(AssertionResultTest_292, IsOk_WhenFatalErrorCondition_ReturnsFalse_292) {
    auto info = makeInfo();
    auto data = makeResultData(ResultWas::FatalErrorCondition);
    AssertionResult result(info, std::move(data));
    EXPECT_FALSE(result.isOk());
}

// ==================== Boundary: SuppressFail with various types ====================

TEST_F(AssertionResultTest_292, IsOk_SuppressFailWithExplicitFailure_ReturnsTrue_292) {
    auto info = makeInfoWithDisposition(ResultDisposition::SuppressFail);
    auto data = makeResultData(ResultWas::ExplicitFailure);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.isOk());
}

TEST_F(AssertionResultTest_292, IsOk_SuppressFailWithThrewException_ReturnsTrue_292) {
    auto info = makeInfoWithDisposition(ResultDisposition::SuppressFail);
    auto data = makeResultData(ResultWas::ThrewException);
    AssertionResult result(info, std::move(data));
    EXPECT_TRUE(result.isOk());
}

// ==================== getSourceInfo() tests ====================

TEST_F(AssertionResultTest_292, GetSourceInfo_ReturnsSourceInfo_292) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_sr;
    info.capturedExpression = "x == 1"_sr;
    info.lineInfo = SourceLineInfo("test_file.cpp", 42);
    info.resultDisposition = ResultDisposition::Normal;
    auto data = makeResultData(ResultWas::Ok);
    AssertionResult result(info, std::move(data));
    auto sourceInfo = result.getSourceInfo();
    EXPECT_EQ(sourceInfo.line, 42u);
    EXPECT_STREQ(sourceInfo.file, "test_file.cpp");
}
