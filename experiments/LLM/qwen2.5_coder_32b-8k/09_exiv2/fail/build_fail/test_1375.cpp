#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.cpp" // Assuming the file needs to be included directly for testing



using namespace Exiv2::Internal;



// Test fixture class (not strictly needed here as no setup/teardown required)

class URationalExposureTimeTest_1375 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(URationalExposureTimeTest_1375, NormalOperation_PositiveShutterSpeedValue_1375) {

    float shutterSpeedValue = 2.0f;

    URational result = exposureTime(shutterSpeedValue);

    EXPECT_EQ(result.first, 1u);

    EXPECT_EQ(result.second, 4u); // 2^2 = 4

}



TEST_F(URationalExposureTimeTest_1375, NormalOperation_ZeroShutterSpeedValue_1375) {

    float shutterSpeedValue = 0.0f;

    URational result = exposureTime(shutterSpeedValue);

    EXPECT_EQ(result.first, 1u);

    EXPECT_EQ(result.second, 1u); // 2^0 = 1

}



TEST_F(URationalExposureTimeTest_1375, NormalOperation_NegativeShutterSpeedValue_1375) {

    float shutterSpeedValue = -1.0f;

    URational result = exposureTime(shutterSpeedValue);

    EXPECT_EQ(result.first, 2u);

    EXPECT_EQ(result.second, 1u); // 1 / (2^-1) = 2

}



TEST_F(URationalExposureTimeTest_1375, BoundaryCondition_MaxUint32_ShutterSpeedValue_1375) {

    float shutterSpeedValue = std::log2(std::numeric_limits<uint32_t>::max());

    URational result = exposureTime(shutterSpeedValue);

    EXPECT_EQ(result.first, 1u);

    EXPECT_EQ(result.second, std::numeric_limits<uint32_t>::max());

}



TEST_F(URationalExposureTimeTest_1375, BoundaryCondition_MinUint32_ShutterSpeedValue_1375) {

    float shutterSpeedValue = -std::log2(std::numeric_limits<uint32_t>::max());

    URational result = exposureTime(shutterSpeedValue);

    EXPECT_EQ(result.first, std::numeric_limits<uint32_t>::max());

    EXPECT_EQ(result.second, 1u);

}



TEST_F(URationalExposureTimeTest_1375, ExceptionalCase_ShutterSpeedValue_OutOfRangeUpper_1375) {

    float shutterSpeedValue = std::log2(std::numeric_limits<uint32_t>::max()) + 1;

    URational result = exposureTime(shutterSpeedValue);

    EXPECT_EQ(result.first, 1u);

    EXPECT_EQ(result.second, 1u); // Should not exceed uint32 max

}



TEST_F(URationalExposureTimeTest_1375, ExceptionalCase_ShutterSpeedValue_OutOfRangeLower_1375) {

    float shutterSpeedValue = -std::log2(std::numeric_limits<uint32_t>::max()) - 1;

    URational result = exposureTime(shutterSpeedValue);

    EXPECT_EQ(result.first, 1u);

    EXPECT_EQ(result.second, 1u); // Should not be less than uint32 min

}
