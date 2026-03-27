#include <gtest/gtest.h>

#include "catch2/internal/catch_result_type.hpp"



using namespace Catch;

using namespace Catch::ResultWas;



class ResultTypeTest_60 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(ResultTypeTest_60, IsOk_ReturnsTrueForOk_60) {

    EXPECT_TRUE(isOk(Ok));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsTrueForInfo_60) {

    EXPECT_TRUE(isOk(Info));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsTrueForWarning_60) {

    EXPECT_TRUE(isOk(Warning));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsFalseForExplicitSkip_60) {

    EXPECT_FALSE(isOk(ExplicitSkip));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsFalseForExpressionFailed_60) {

    EXPECT_FALSE(isOk(ExpressionFailed));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsFalseForExplicitFailure_60) {

    EXPECT_FALSE(isOk(ExplicitFailure));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsFalseForException_60) {

    EXPECT_FALSE(isOk(Exception));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsFalseForThrewException_60) {

    EXPECT_FALSE(isOk(ThrewException));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsTrueForDidntThrowException_60) {

    EXPECT_TRUE(isOk(DidntThrowException));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsFalseForFatalErrorCondition_60) {

    EXPECT_FALSE(isOk(FatalErrorCondition));

}



TEST_F(ResultTypeTest_60, IsOk_ReturnsTrueForUnknown_60) {

    EXPECT_TRUE(isOk(Unknown));

}
