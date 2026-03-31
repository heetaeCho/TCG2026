#include <gtest/gtest.h>
#include <cmath>
#include <cstdint>
#include <limits>

// Forward declare the function we're testing
namespace Exiv2 {
namespace Internal {

// URational is typically std::pair<uint32_t, uint32_t> or a struct with first/second
using URational = std::pair<uint32_t, uint32_t>;

URational exposureTime(float shutterSpeedValue);

} // namespace Internal
} // namespace Exiv2

using Exiv2::Internal::exposureTime;
using Exiv2::Internal::URational;

class ExposureTimeTest_1375 : public ::testing::Test {
protected:
};

// When shutterSpeedValue = 0, 2^0 = 1, which is not > 1, so we go to else branch
// 1/tmp = 1/1 = 1, round(1) = 1, so ur.first = 1, ur.second = 1
TEST_F(ExposureTimeTest_1375, ShutterSpeedZero_ReturnsOneOverOne_1375) {
    URational result = exposureTime(0.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1u);
}

// When shutterSpeedValue = 1, 2^1 = 2 > 1, round(2) = 2
// So ur = 1/2
TEST_F(ExposureTimeTest_1375, ShutterSpeedOne_ReturnsOneOverTwo_1375) {
    URational result = exposureTime(1.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 2u);
}

// When shutterSpeedValue = 2, 2^2 = 4 > 1, round(4) = 4
// So ur = 1/4
TEST_F(ExposureTimeTest_1375, ShutterSpeedTwo_ReturnsOneOverFour_1375) {
    URational result = exposureTime(2.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 4u);
}

// When shutterSpeedValue = 3, 2^3 = 8 > 1
// So ur = 1/8
TEST_F(ExposureTimeTest_1375, ShutterSpeedThree_ReturnsOneOverEight_1375) {
    URational result = exposureTime(3.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 8u);
}

// When shutterSpeedValue = 10, 2^10 = 1024 > 1
// So ur = 1/1024
TEST_F(ExposureTimeTest_1375, ShutterSpeedTen_ReturnsOneOver1024_1375) {
    URational result = exposureTime(10.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1024u);
}

// When shutterSpeedValue = -1, 2^(-1) = 0.5, not > 1
// 1/0.5 = 2, round(2) = 2, ur.first = 2, ur.second = 1
TEST_F(ExposureTimeTest_1375, ShutterSpeedNegOne_ReturnsTwoOverOne_1375) {
    URational result = exposureTime(-1.0f);
    EXPECT_EQ(result.first, 2u);
    EXPECT_EQ(result.second, 1u);
}

// When shutterSpeedValue = -2, 2^(-2) = 0.25, not > 1
// 1/0.25 = 4, round(4) = 4, ur.first = 4, ur.second = 1
TEST_F(ExposureTimeTest_1375, ShutterSpeedNegTwo_ReturnsFourOverOne_1375) {
    URational result = exposureTime(-2.0f);
    EXPECT_EQ(result.first, 4u);
    EXPECT_EQ(result.second, 1u);
}

// When shutterSpeedValue = -3, 2^(-3) = 0.125
// 1/0.125 = 8, ur.first = 8
TEST_F(ExposureTimeTest_1375, ShutterSpeedNegThree_ReturnsEightOverOne_1375) {
    URational result = exposureTime(-3.0f);
    EXPECT_EQ(result.first, 8u);
    EXPECT_EQ(result.second, 1u);
}

// When shutterSpeedValue = -5, 2^(-5) = 1/32
// 1/(1/32) = 32, ur.first = 32
TEST_F(ExposureTimeTest_1375, ShutterSpeedNegFive_Returns32OverOne_1375) {
    URational result = exposureTime(-5.0f);
    EXPECT_EQ(result.first, 32u);
    EXPECT_EQ(result.second, 1u);
}

// Fractional shutter speed value: 0.5
// 2^0.5 ≈ 1.414 > 1, round(1.414) = 1
// So ur = 1/1
TEST_F(ExposureTimeTest_1375, ShutterSpeedHalf_ReturnsOneOverOne_1375) {
    URational result = exposureTime(0.5f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1u);
}

// Fractional shutter speed value: 1.5
// 2^1.5 ≈ 2.828 > 1, round(2.828) = 3
// So ur = 1/3
TEST_F(ExposureTimeTest_1375, ShutterSpeedOnePointFive_ReturnsOneOverThree_1375) {
    URational result = exposureTime(1.5f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 3u);
}

// Shutter speed value corresponding to common exposure: 6 => 2^6 = 64 => 1/64
TEST_F(ExposureTimeTest_1375, ShutterSpeedSix_ReturnsOneOver64_1375) {
    URational result = exposureTime(6.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 64u);
}

// Shutter speed value = 8 => 2^8 = 256 => 1/256
TEST_F(ExposureTimeTest_1375, ShutterSpeedEight_ReturnsOneOver256_1375) {
    URational result = exposureTime(8.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 256u);
}

// Large positive value: shutterSpeedValue = 20
// 2^20 = 1048576 > 1, round gives 1048576
// ur = 1/1048576
TEST_F(ExposureTimeTest_1375, ShutterSpeedTwenty_ReturnsOneOverLargeValue_1375) {
    URational result = exposureTime(20.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1048576u);
}

// Large negative value: shutterSpeedValue = -10
// 2^(-10) = 1/1024, 1/(1/1024) = 1024
// ur.first = 1024
TEST_F(ExposureTimeTest_1375, ShutterSpeedNegTen_Returns1024OverOne_1375) {
    URational result = exposureTime(-10.0f);
    EXPECT_EQ(result.first, 1024u);
    EXPECT_EQ(result.second, 1u);
}

// Test a fractional value in the else branch: -0.5
// 2^(-0.5) ≈ 0.707, 1/0.707 ≈ 1.414, round(1.414) = 1
// ur.first = 1, ur.second = 1
TEST_F(ExposureTimeTest_1375, ShutterSpeedNegHalf_ReturnsOneOverOne_1375) {
    URational result = exposureTime(-0.5f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1u);
}

// Test a fractional value in else branch: -1.5
// 2^(-1.5) ≈ 0.3536, 1/0.3536 ≈ 2.828, round = 3
// ur.first = 3
TEST_F(ExposureTimeTest_1375, ShutterSpeedNegOnePointFive_ReturnsThreeOverOne_1375) {
    URational result = exposureTime(-1.5f);
    EXPECT_EQ(result.first, 3u);
    EXPECT_EQ(result.second, 1u);
}

// Boundary near tmp = 1: shutterSpeedValue very slightly above 0
// 2^(0.001) ≈ 1.000693 > 1, round(1.000693) = 1
// ur = 1/1
TEST_F(ExposureTimeTest_1375, ShutterSpeedSlightlyAboveZero_ReturnsOneOverOne_1375) {
    URational result = exposureTime(0.001f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1u);
}

// Boundary: shutterSpeedValue very slightly below 0
// 2^(-0.001) ≈ 0.99931, not > 1
// 1/0.99931 ≈ 1.00069, round = 1
// ur.first = 1, ur.second = 1
TEST_F(ExposureTimeTest_1375, ShutterSpeedSlightlyBelowZero_ReturnsOneOverOne_1375) {
    URational result = exposureTime(-0.001f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1u);
}

// Test with shutterSpeedValue = 31 (2^31 = 2147483648, which is within uint32_t max)
TEST_F(ExposureTimeTest_1375, ShutterSpeed31_ReturnsOneOverTwoTo31_1375) {
    URational result = exposureTime(31.0f);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 2147483648u);
}

// Test that result types are properly uint32_t (non-negative)
TEST_F(ExposureTimeTest_1375, ResultAlwaysNonNegative_1375) {
    URational result = exposureTime(5.0f);
    // Both first and second should be valid uint32_t values
    EXPECT_GE(result.first, 0u);
    EXPECT_GE(result.second, 0u);
}

// Typical photography value: 1/125 is approximately APEX 6.97
// 2^6.97 ≈ 125.2, round = 125
TEST_F(ExposureTimeTest_1375, ShutterSpeedTypicalPhotography_1375) {
    URational result = exposureTime(6.97f);
    EXPECT_EQ(result.first, 1u);
    // 2^6.97 ≈ 125.2, round to 125
    EXPECT_NEAR(static_cast<double>(result.second), 125.0, 2.0);
}

// 1/1000s corresponds to APEX ~9.97
// 2^9.97 ≈ 1000
TEST_F(ExposureTimeTest_1375, ShutterSpeed1Over1000_1375) {
    float sv = std::log2(1000.0f);
    URational result = exposureTime(sv);
    EXPECT_EQ(result.first, 1u);
    EXPECT_NEAR(static_cast<double>(result.second), 1000.0, 1.0);
}

// 30 seconds exposure: shutterSpeedValue = -log2(30) ≈ -4.907
// 2^(-4.907) ≈ 0.0333, 1/0.0333 ≈ 30
TEST_F(ExposureTimeTest_1375, ShutterSpeed30Seconds_1375) {
    float sv = -std::log2(30.0f);
    URational result = exposureTime(sv);
    EXPECT_EQ(result.second, 1u);
    EXPECT_NEAR(static_cast<double>(result.first), 30.0, 1.0);
}
