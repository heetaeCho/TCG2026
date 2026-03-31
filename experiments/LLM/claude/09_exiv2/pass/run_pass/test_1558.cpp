#include <gtest/gtest.h>
#include <cstdint>
#include <array>
#include <string>

// Include the header for AsfVideo and GUIDTag
#include "exiv2/asfvideo.hpp"

using namespace Exiv2;

// Helper type alias
using byte = uint8_t;

class GUIDTagTest_1558 : public ::testing::Test {
protected:
};

// Test to_string with all zeros
TEST_F(GUIDTagTest_1558, ToStringAllZeros_1558) {
    std::array<byte, 8> data4 = {0, 0, 0, 0, 0, 0, 0, 0};
    AsfVideo::GUIDTag tag(0x00000000, 0x0000, 0x0000, data4);
    std::string result = tag.to_string();
    EXPECT_EQ(result, "00000000-0000-0000-0000-000000000000");
}

// Test to_string with typical GUID values
TEST_F(GUIDTagTest_1558, ToStringTypicalValues_1558) {
    std::array<byte, 8> data4 = {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71};
    AsfVideo::GUIDTag tag(0x75B22630, 0x668E, 0x11CF, data4);
    std::string result = tag.to_string();
    EXPECT_EQ(result, "75B22630-668E-11CF-8000-00AA00389B71");
}

// Test to_string with all max values (0xFF...)
TEST_F(GUIDTagTest_1558, ToStringAllMaxValues_1558) {
    std::array<byte, 8> data4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    AsfVideo::GUIDTag tag(0xFFFFFFFF, 0xFFFF, 0xFFFF, data4);
    std::string result = tag.to_string();
    EXPECT_EQ(result, "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF");
}

// Test equality operator with identical tags
TEST_F(GUIDTagTest_1558, EqualityOperatorIdenticalTags_1558) {
    std::array<byte, 8> data4 = {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71};
    AsfVideo::GUIDTag tag1(0x75B22630, 0x668E, 0x11CF, data4);
    AsfVideo::GUIDTag tag2(0x75B22630, 0x668E, 0x11CF, data4);
    EXPECT_TRUE(tag1 == tag2);
}

// Test equality operator with different data1
TEST_F(GUIDTagTest_1558, EqualityOperatorDifferentData1_1558) {
    std::array<byte, 8> data4 = {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71};
    AsfVideo::GUIDTag tag1(0x75B22630, 0x668E, 0x11CF, data4);
    AsfVideo::GUIDTag tag2(0x75B22631, 0x668E, 0x11CF, data4);
    EXPECT_FALSE(tag1 == tag2);
}

// Test equality operator with different data2
TEST_F(GUIDTagTest_1558, EqualityOperatorDifferentData2_1558) {
    std::array<byte, 8> data4 = {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71};
    AsfVideo::GUIDTag tag1(0x75B22630, 0x668E, 0x11CF, data4);
    AsfVideo::GUIDTag tag2(0x75B22630, 0x668F, 0x11CF, data4);
    EXPECT_FALSE(tag1 == tag2);
}

// Test equality operator with different data3
TEST_F(GUIDTagTest_1558, EqualityOperatorDifferentData3_1558) {
    std::array<byte, 8> data4 = {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71};
    AsfVideo::GUIDTag tag1(0x75B22630, 0x668E, 0x11CF, data4);
    AsfVideo::GUIDTag tag2(0x75B22630, 0x668E, 0x11D0, data4);
    EXPECT_FALSE(tag1 == tag2);
}

// Test equality operator with different data4
TEST_F(GUIDTagTest_1558, EqualityOperatorDifferentData4_1558) {
    std::array<byte, 8> data4a = {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71};
    std::array<byte, 8> data4b = {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x72};
    AsfVideo::GUIDTag tag1(0x75B22630, 0x668E, 0x11CF, data4a);
    AsfVideo::GUIDTag tag2(0x75B22630, 0x668E, 0x11CF, data4b);
    EXPECT_FALSE(tag1 == tag2);
}

// Test less-than operator
TEST_F(GUIDTagTest_1558, LessThanOperatorDifferentData1_1558) {
    std::array<byte, 8> data4 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    AsfVideo::GUIDTag tag1(0x00000001, 0x0000, 0x0000, data4);
    AsfVideo::GUIDTag tag2(0x00000002, 0x0000, 0x0000, data4);
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test less-than operator with equal tags (should be false)
TEST_F(GUIDTagTest_1558, LessThanOperatorEqualTags_1558) {
    std::array<byte, 8> data4 = {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71};
    AsfVideo::GUIDTag tag1(0x75B22630, 0x668E, 0x11CF, data4);
    AsfVideo::GUIDTag tag2(0x75B22630, 0x668E, 0x11CF, data4);
    EXPECT_FALSE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test construction from bytes
TEST_F(GUIDTagTest_1558, ConstructFromBytes_1558) {
    // ASF Header Object GUID: 75B22630-668E-11CF-A6D9-00AA0062CE6C
    // In little-endian byte representation as stored in ASF files
    uint8_t bytes[16] = {
        0x30, 0x26, 0xB2, 0x75,  // data1 (LE): 0x75B22630
        0x8E, 0x66,              // data2 (LE): 0x668E
        0xCF, 0x11,              // data3 (LE): 0x11CF
        0xA6, 0xD9,              // data4[0-1]
        0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C  // data4[2-7]
    };
    AsfVideo::GUIDTag tag(bytes);
    std::string result = tag.to_string();
    EXPECT_EQ(result, "75B22630-668E-11CF-A6D9-00AA0062CE6C");
}

// Test to_string with mixed values in data4
TEST_F(GUIDTagTest_1558, ToStringMixedData4_1558) {
    std::array<byte, 8> data4 = {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
    AsfVideo::GUIDTag tag(0x75B22630, 0x668E, 0x11CF, data4);
    std::string result = tag.to_string();
    EXPECT_EQ(result, "75B22630-668E-11CF-A6D9-00AA0062CE6C");
}

// Test to_string with value 1 in each field
TEST_F(GUIDTagTest_1558, ToStringMinimalValues_1558) {
    std::array<byte, 8> data4 = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
    AsfVideo::GUIDTag tag(0x00000001, 0x0001, 0x0001, data4);
    std::string result = tag.to_string();
    EXPECT_EQ(result, "00000001-0001-0001-0101-010101010101");
}

// Test less-than operator with different data2
TEST_F(GUIDTagTest_1558, LessThanOperatorDifferentData2_1558) {
    std::array<byte, 8> data4 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    AsfVideo::GUIDTag tag1(0x00000001, 0x0001, 0x0000, data4);
    AsfVideo::GUIDTag tag2(0x00000001, 0x0002, 0x0000, data4);
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test less-than operator with different data3
TEST_F(GUIDTagTest_1558, LessThanOperatorDifferentData3_1558) {
    std::array<byte, 8> data4 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    AsfVideo::GUIDTag tag1(0x00000001, 0x0001, 0x0001, data4);
    AsfVideo::GUIDTag tag2(0x00000001, 0x0001, 0x0002, data4);
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test less-than operator with different data4
TEST_F(GUIDTagTest_1558, LessThanOperatorDifferentData4_1558) {
    std::array<byte, 8> data4a = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    std::array<byte, 8> data4b = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
    AsfVideo::GUIDTag tag1(0x00000001, 0x0001, 0x0001, data4a);
    AsfVideo::GUIDTag tag2(0x00000001, 0x0001, 0x0001, data4b);
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test to_string format has correct separators
TEST_F(GUIDTagTest_1558, ToStringFormatCorrectSeparators_1558) {
    std::array<byte, 8> data4 = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89};
    AsfVideo::GUIDTag tag(0x12345678, 0x9ABC, 0xDEF0, data4);
    std::string result = tag.to_string();
    // Verify dashes at correct positions
    EXPECT_EQ(result[8], '-');
    EXPECT_EQ(result[13], '-');
    EXPECT_EQ(result[18], '-');
    EXPECT_EQ(result[23], '-');
    // Verify total length: 8+1+4+1+4+1+4+1+12 = 36
    EXPECT_EQ(result.length(), 36u);
}

// Test construction from bytes then comparison with constexpr constructed
TEST_F(GUIDTagTest_1558, ByteConstructorMatchesConstexprConstructor_1558) {
    // Construct a known GUID via constexpr constructor
    std::array<byte, 8> data4 = {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
    AsfVideo::GUIDTag tagConstexpr(0x75B22630, 0x668E, 0x11CF, data4);

    // Construct the same GUID from bytes (little-endian for data1, data2, data3)
    uint8_t bytes[16] = {
        0x30, 0x26, 0xB2, 0x75,
        0x8E, 0x66,
        0xCF, 0x11,
        0xA6, 0xD9,
        0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    AsfVideo::GUIDTag tagBytes(bytes);

    EXPECT_TRUE(tagConstexpr == tagBytes);
    EXPECT_EQ(tagConstexpr.to_string(), tagBytes.to_string());
}

// Test to_string uppercase hex formatting
TEST_F(GUIDTagTest_1558, ToStringUppercaseHex_1558) {
    std::array<byte, 8> data4 = {0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89};
    AsfVideo::GUIDTag tag(0xabcdef01, 0xabcd, 0xef01, data4);
    std::string result = tag.to_string();
    EXPECT_EQ(result, "ABCDEF01-ABCD-EF01-ABCD-EF0123456789");
}
