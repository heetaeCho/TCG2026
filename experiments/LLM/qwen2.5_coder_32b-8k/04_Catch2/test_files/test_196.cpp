#include <gtest/gtest.h>

#include <catch2/internal/catch_floating_point_helpers.hpp>

#include <cmath>

#include <limits>



using namespace Catch;



TEST_F(FloatingPointHelpersTest_196, EqualValuesReturnZeroDistance_196) {

    EXPECT_EQ(ulpDistance(1.0f, 1.0f), 0);

    EXPECT_EQ(ulpDistance(-1.0f, -1.0f), 0);

    EXPECT_EQ(ulpDistance(2.5, 2.5), 0);

}



TEST_F(FloatingPointHelpersTest_196, DifferentSignValuesCalculateCorrectly_196) {

    EXPECT_EQ(ulpDistance(1.0f, -1.0f), ulpDistance(1.0f, 0.0f) + ulpDistance(1.0f, 0.0f));

    EXPECT_EQ(ulpDistance(-2.5, 3.5), ulpDistance(2.5, 0.0) + ulpDistance(3.5, 0.0));

}



TEST_F(FloatingPointHelpersTest_196, PositiveValuesCalculateCorrectly_196) {

    EXPECT_EQ(ulpDistance(2.0f, 1.0f), Detail::convertToBits(2.0f) - Detail::convertToBits(1.0f));

}



TEST_F(FloatingPointHelpersTest_196, NegativeValuesCalculateCorrectly_196) {

    EXPECT_EQ(ulpDistance(-1.0f, -2.0f), Detail::convertToBits(-1.0f) - Detail::convertToBits(-2.0f));

}



TEST_F(FloatingPointHelpersTest_196, PositiveZeroHandling_196) {

    EXPECT_EQ(ulpDistance(std::numeric_limits<float>::denorm_min(), 0.0f), 1);

    EXPECT_EQ(ulpDistance(0.0f, std::numeric_limits<double>::denorm_min()), 1);

}



TEST_F(FloatingPointHelpersTest_196, NegativeZeroHandling_196) {

    float negative_zero = -static_cast<float>(std::copysign(std::numeric_limits<float>::min(), -1));

    EXPECT_EQ(ulpDistance(negative_zero, 0.0f), 0);

}



TEST_F(FloatingPointHelpersTest_196, NaNValuesTriggerAssertion_196) {

    EXPECT_DEATH(ulpDistance(std::numeric_limits<double>::quiet_NaN(), 0.0), "Distance between NaN and number is not meaningful");

    EXPECT_DEATH(ulpDistance(0.0f, std::numeric_limits<float>::quiet_NaN()), "Distance between NaN and number is not meaningful");

}



TEST_F(FloatingPointHelpersTest_196, LargeValuesCalculateCorrectly_196) {

    double large_value = std::numeric_limits<double>::max();

    double small_large_value = std::nextafter(large_value, 0.0);

    EXPECT_EQ(ulpDistance(large_value, small_large_value), 1);

}



TEST_F(FloatingPointHelpersTest_196, DenormalizedValuesCalculateCorrectly_196) {

    float denorm_min = std::numeric_limits<float>::denorm_min();

    float next_denorm = std::nextafter(denorm_min, 0.0f);

    EXPECT_EQ(ulpDistance(next_denorm, denorm_min), 1);

}
