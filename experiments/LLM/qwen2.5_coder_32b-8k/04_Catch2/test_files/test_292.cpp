#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_assertion_result.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_assertion_info.hpp"



namespace Catch {

    struct LazyExpression {};

    enum class OfType { Success, Failure, ExplicitFailure };

    namespace ResultWas {

        using OfType = Catch::OfType;

    }

    namespace ResultDisposition {

        struct Flags {};

    }

}



using ::testing::Eq;



class AssertionResultTest_292 : public ::testing::Test {

protected:

    void SetUp() override {

        assertionInfo = Catch::AssertionInfo{};

        lazyExpression = Catch::LazyExpression{};

        resultData = Catch::AssertionResultData{Catch::ResultWas::OfType::Success, lazyExpression};

        assertionResult = Catch::AssertionResult(assertionInfo, std::move(resultData));

    }



    Catch::AssertionInfo assertionInfo;

    Catch::LazyExpression lazyExpression;

    Catch::AssertionResultData resultData;

    Catch::AssertionResult assertionResult;

};



TEST_F(AssertionResultTest_292, IsOk_ReturnsTrueForSuccess_292) {

    EXPECT_TRUE(assertionResult.isOk());

}



TEST_F(AssertionResultTest_292, Succeeded_ReturnsTrueForSuccess_292) {

    EXPECT_TRUE(assertionResult.succeeded());

}



TEST_F(AssertionResultTest_292, GetResultType_ReturnsSuccess_292) {

    EXPECT_EQ(assertionResult.getResultType(), Catch::ResultWas::OfType::Success);

}



TEST_F(AssertionResultTest_292, HasExpression_ReturnsFalseWhenNoExpression_292) {

    EXPECT_FALSE(assertionResult.hasExpression());

}



TEST_F(AssertionResultTest_292, HasMessage_ReturnsFalseWhenNoMessage_292) {

    EXPECT_FALSE(assertionResult.hasMessage());

}



TEST_F(AssertionResultTest_292, GetExpression_ReturnsEmptyStringWhenNoExpression_292) {

    EXPECT_EQ(assertionResult.getExpression(), "");

}



TEST_F(AssertionResultTest_292, GetExpressionInMacro_ReturnsEmptyStringWhenNoExpression_292) {

    EXPECT_EQ(assertionResult.getExpressionInMacro(), "");

}



TEST_F(AssertionResultTest_292, HasExpandedExpression_ReturnsFalseWhenNoExpandedExpression_292) {

    EXPECT_FALSE(assertionResult.hasExpandedExpression());

}



TEST_F(AssertionResultTest_292, GetExpandedExpression_ReturnsEmptyStringWhenNoExpandedExpression_292) {

    EXPECT_EQ(assertionResult.getExpandedExpression(), "");

}



TEST_F(AssertionResultTest_292, GetMessage_ReturnsEmptyStringWhenNoMessage_292) {

    EXPECT_EQ(std::string(assertionResult.getMessage()), "");

}



TEST_F(AssertionResultTest_292, GetSourceInfo_ReturnsDefaultConstructedSourceLineInfo_292) {

    Catch::SourceLineInfo defaultSourceLineInfo;

    EXPECT_EQ(assertionResult.getSourceInfo(), defaultSourceLineInfo);

}



TEST_F(AssertionResultTest_292, GetTestMacroName_ReturnsEmptyStringWhenNoMacroName_292) {

    EXPECT_EQ(std::string(assertionResult.getTestMacroName()), "");

}



TEST_F(AssertionResultTest_292, IsOk_ReturnsFalseForFailure_292) {

    resultData = Catch::AssertionResultData{Catch::ResultWas::OfType::Failure, lazyExpression};

    assertionResult = Catch::AssertionResult(assertionInfo, std::move(resultData));

    EXPECT_FALSE(assertionResult.isOk());

}



TEST_F(AssertionResultTest_292, Succeeded_ReturnsFalseForFailure_292) {

    resultData = Catch::AssertionResultData{Catch::ResultWas::OfType::Failure, lazyExpression};

    assertionResult = Catch::AssertionResult(assertionInfo, std::move(resultData));

    EXPECT_FALSE(assertionResult.succeeded());

}



TEST_F(AssertionResultTest_292, GetResultType_ReturnsFailure_292) {

    resultData = Catch::AssertionResultData{Catch::ResultWas::OfType::Failure, lazyExpression};

    assertionResult = Catch::AssertionResult(assertionInfo, std::move(resultData));

    EXPECT_EQ(assertionResult.getResultType(), Catch::ResultWas::OfType::Failure);

}



TEST_F(AssertionResultTest_292, IsOk_ReturnsFalseForExplicitFailure_292) {

    resultData = Catch::AssertionResultData{Catch::ResultWas::OfType::ExplicitFailure, lazyExpression};

    assertionResult = Catch::AssertionResult(assertionInfo, std::move(resultData));

    EXPECT_FALSE(assertionResult.isOk());

}



TEST_F(AssertionResultTest_292, Succeeded_ReturnsFalseForExplicitFailure_292) {

    resultData = Catch::AssertionResultData{Catch::ResultWas::OfType::ExplicitFailure, lazyExpression};

    assertionResult = Catch::AssertionResult(assertionInfo, std::move(resultData));

    EXPECT_FALSE(assertionResult.succeeded());

}



TEST_F(AssertionResultTest_292, GetResultType_ReturnsExplicitFailure_292) {

    resultData = Catch::AssertionResultData{Catch::ResultWas::OfType::ExplicitFailure, lazyExpression};

    assertionResult = Catch::AssertionResult(assertionInfo, std::move(resultData));

    EXPECT_EQ(assertionResult.getResultType(), Catch::ResultWas::OfType::ExplicitFailure);

}
