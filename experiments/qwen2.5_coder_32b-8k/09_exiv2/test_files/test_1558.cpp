#include <gtest/gtest.h>

#include "exiv2/asfvideo.hpp"

#include <array>



namespace {



using Exiv2::AsfVideo::GUIDTag;



// Test fixture for GUIDTag tests

class GUIDTagTest_1558 : public ::testing::Test {

protected:

    static constexpr std::array<uint8_t, 16> testData = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,

                                                         0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    GUIDTag testGuid{testData.data()};

};



// Test normal operation of to_string

TEST_F(GUIDTagTest_1558, ToStringNormalOperation_1558) {

    EXPECT_EQ(testGuid.to_string(), "12345678-9ABC-DEF0-1234-56789ABCDEF0");

}



// Test boundary condition with all zeros

TEST_F(GUIDTagTest_1558, ToStringAllZeros_1558) {

    GUIDTag zeroGuid{std::array<uint8_t, 16>{}.data()};

    EXPECT_EQ(zeroGuid.to_string(), "00000000-0000-0000-0000-000000000000");

}



// Test boundary condition with all ones

TEST_F(GUIDTagTest_1558, ToStringAllOnes_1558) {

    GUIDTag oneGuid{std::array<uint8_t, 16>{0xFF}.data()};

    EXPECT_EQ(oneGuid.to_string(), "FFFFFFFF-FFFF-FFFF-FFFD-FFFFFFFFFFFF");

}



// Test operator== with identical GUIDs

TEST_F(GUIDTagTest_1558, OperatorEqualIdentical_1558) {

    GUIDTag sameGuid{testData.data()};

    EXPECT_TRUE(testGuid == sameGuid);

}



// Test operator== with different GUIDs

TEST_F(GUIDTagTest_1558, OperatorEqualDifferent_1558) {

    GUIDTag diffGuid{std::array<uint8_t, 16>{0x00}.data()};

    EXPECT_FALSE(testGuid == diffGuid);

}



// Test operator< with smaller and larger GUIDs

TEST_F(GUIDTagTest_1558, OperatorLessThan_1558) {

    GUIDTag smallerGuid{std::array<uint8_t, 16>{0x00}.data()};

    GUIDTag largerGuid{std::array<uint8_t, 16>{0xFF}.data()};

    EXPECT_TRUE(smallerGuid < testGuid);

    EXPECT_FALSE(testGuid < smallerGuid);

    EXPECT_FALSE(largerGuid < testGuid);

}



}  // namespace
