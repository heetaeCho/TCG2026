#include <gtest/gtest.h>

#include "Stream.h"



class BufStreamTest_204 : public ::testing::Test {

protected:

    BufStream stream;

};



TEST_F(BufStreamTest_204, GetPSFilter_ReturnsEmptyOptional_204) {

    auto result = stream.getPSFilter(1, "indent");

    EXPECT_FALSE(result.has_value());

}



TEST_F(BufStreamTest_204, GetPSFilter_BoundaryCondition_ZeroPSLevel_204) {

    auto result = stream.getPSFilter(0, "indent");

    EXPECT_FALSE(result.has_value());

}



TEST_F(BufStreamTest_204, GetPSFilter_BoundaryCondition_NegativePSLevel_204) {

    auto result = stream.getPSFilter(-1, "indent");

    EXPECT_FALSE(result.has_value());

}



TEST_F(BufStreamTest_204, GetPSFilter_NullIndent_204) {

    auto result = stream.getPSFilter(1, nullptr);

    EXPECT_FALSE(result.has_value());

}
