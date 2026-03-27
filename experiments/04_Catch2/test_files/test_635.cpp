#include <gtest/gtest.h>

#include <cmath> // For std::isnan



namespace Catch {

    bool isnan(float f);

}



class IsnanTest : public ::testing::Test {

protected:

    // Additional setup or teardown can be done here if needed.

};



TEST_F(IsnanTest_635, PositiveInfinity_ReturnsFalse_635) {

    EXPECT_FALSE(Catch::isnan(std::numeric_limits<float>::infinity()));

}



TEST_F(IsnanTest_635, NegativeInfinity_ReturnsFalse_635) {

    EXPECT_FALSE(Catch::isnan(-std::numeric_limits<float>::infinity()));

}



TEST_F(IsnanTest_635, NormalNumber_ReturnsFalse_635) {

    EXPECT_FALSE(Catch::isnan(42.0f));

}



TEST_F(IsnanTest_635, NaN_ReturnsTrue_635) {

    EXPECT_TRUE(Catch::isnan(std::numeric_limits<float>::quiet_NaN()));

}



TEST_F(IsnanTest_635, NegativeNaN_ReturnsTrue_635) {

    EXPECT_TRUE(Catch::isnan(-std::numeric_limits<float>::quiet_NaN()));

}



TEST_F(IsnanTest_635, SubnormalNumber_ReturnsFalse_635) {

    EXPECT_FALSE(Catch::isnan(std::numeric_limits<float>::denorm_min()));

}
