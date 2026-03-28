#include <gtest/gtest.h>

#include "catch2/internal/catch_result_type.hpp"



using namespace Catch;

using namespace Catch::ResultWas;



class ResultTypeTest_61 : public ::testing::Test {};



TEST_F(ResultTypeTest_61, IsJustInfo_ReturnsTrueForInfo_61) {

    EXPECT_TRUE(isJustInfo(Info));

}



TEST_F(ResultTypeTest_61, IsJustInfo_ReturnsFalseForNonInfo_61) {

    EXPECT_FALSE(isJustInfo(Unknown));

    EXPECT_FALSE(isJustInfo(Ok));

    EXPECT_FALSE(isJustInfo(Warning));

    EXPECT_FALSE(isJustInfo(ExpressionFailed));

    EXPECT_FALSE(isJustInfo(Exception));

}



TEST_F(ResultTypeTest_61, IsJustInfo_ReturnsFalseForBoundaryValues_61) {

    EXPECT_FALSE(isJustInfo(-2)); // Below the lowest known value

    EXPECT_FALSE(isJustInfo(3));  // Above the highest known non-exception value

}
