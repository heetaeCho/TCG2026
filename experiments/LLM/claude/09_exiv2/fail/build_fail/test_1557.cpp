#include <gtest/gtest.h>
#include <array>
#include <cstdint>

// Include the header for the class under test
#include "exiv2/asfvideo.hpp"

using namespace Exiv2;

// Helper type alias
using byte = uint8_t;

class AsfVideoGUIDTagTest_1557 : public ::testing::Test {
protected:
    // Helper to create a GUIDTag using constexpr constructor
    AsfVideo::GUIDTag makeTag(uint32_t d1, uint16_t d2, uint16_t d3, std::array<byte, 8> d4) {
        return AsfVideo::GUIDTag(d1, d2, d3, d4);
    }
};

// Test equality of two identical GUIDTags created with same parameters
TEST_F(AsfVideoGUIDTagTest_1557, EqualTagsAreEqual_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4);
    auto tag2 = makeTag(0x12345678, 0x1234, 0x5678, data4);
    EXPECT_TRUE(tag1 == tag2);
}

// Test inequality when data1 differs
TEST_F(AsfVideoGUIDTagTest_1557, DifferentData1NotEqual_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4);
    auto tag2 = makeTag(0x87654321, 0x1234, 0x5678, data4);
    EXPECT_FALSE(tag1 == tag2);
}

// Test inequality when data2 differs
TEST_F(AsfVideoGUIDTagTest_1557, DifferentData2NotEqual_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4);
    auto tag2 = makeTag(0x12345678, 0x4321, 0x5678, data4);
    EXPECT_FALSE(tag1 == tag2);
}

// Test inequality when data3 differs
TEST_F(AsfVideoGUIDTagTest_1557, DifferentData3NotEqual_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4);
    auto tag2 = makeTag(0x12345678, 0x1234, 0x8765, data4);
    EXPECT_FALSE(tag1 == tag2);
}

// Test inequality when data4 differs
TEST_F(AsfVideoGUIDTagTest_1557, DifferentData4NotEqual_1557) {
    std::array<byte, 8> data4a = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    std::array<byte, 8> data4b = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x09};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4a);
    auto tag2 = makeTag(0x12345678, 0x1234, 0x5678, data4b);
    EXPECT_FALSE(tag1 == tag2);
}

// Test inequality when data4 differs at first byte
TEST_F(AsfVideoGUIDTagTest_1557, DifferentData4FirstByteNotEqual_1557) {
    std::array<byte, 8> data4a = {0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    std::array<byte, 8> data4b = {0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4a);
    auto tag2 = makeTag(0x12345678, 0x1234, 0x5678, data4b);
    EXPECT_FALSE(tag1 == tag2);
}

// Test with all zero values
TEST_F(AsfVideoGUIDTagTest_1557, AllZerosEqual_1557) {
    std::array<byte, 8> data4 = {0, 0, 0, 0, 0, 0, 0, 0};
    auto tag1 = makeTag(0, 0, 0, data4);
    auto tag2 = makeTag(0, 0, 0, data4);
    EXPECT_TRUE(tag1 == tag2);
}

// Test with max values
TEST_F(AsfVideoGUIDTagTest_1557, MaxValuesEqual_1557) {
    std::array<byte, 8> data4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    auto tag1 = makeTag(0xFFFFFFFF, 0xFFFF, 0xFFFF, data4);
    auto tag2 = makeTag(0xFFFFFFFF, 0xFFFF, 0xFFFF, data4);
    EXPECT_TRUE(tag1 == tag2);
}

// Test construction from bytes and equality
TEST_F(AsfVideoGUIDTagTest_1557, ConstructFromBytesEqualToSelf_1557) {
    // A GUID is 16 bytes: 4 bytes data1, 2 bytes data2, 2 bytes data3, 8 bytes data4
    uint8_t bytes[16] = {
        0x78, 0x56, 0x34, 0x12,  // data1 (little-endian: 0x12345678)
        0x34, 0x12,              // data2 (little-endian: 0x1234)
        0x78, 0x56,              // data3 (little-endian: 0x5678)
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08  // data4
    };
    AsfVideo::GUIDTag tag1(bytes);
    AsfVideo::GUIDTag tag2(bytes);
    EXPECT_TRUE(tag1 == tag2);
}

// Test to_string returns non-empty string
TEST_F(AsfVideoGUIDTagTest_1557, ToStringReturnsNonEmpty_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag = makeTag(0x12345678, 0x1234, 0x5678, data4);
    std::string result = tag.to_string();
    EXPECT_FALSE(result.empty());
}

// Test to_string for zero GUID
TEST_F(AsfVideoGUIDTagTest_1557, ToStringZeroGUID_1557) {
    std::array<byte, 8> data4 = {0, 0, 0, 0, 0, 0, 0, 0};
    auto tag = makeTag(0, 0, 0, data4);
    std::string result = tag.to_string();
    EXPECT_FALSE(result.empty());
}

// Test that equal tags produce the same to_string output
TEST_F(AsfVideoGUIDTagTest_1557, EqualTagsSameToString_1557) {
    std::array<byte, 8> data4 = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11};
    auto tag1 = makeTag(0xDEADBEEF, 0xCAFE, 0xBABE, data4);
    auto tag2 = makeTag(0xDEADBEEF, 0xCAFE, 0xBABE, data4);
    EXPECT_EQ(tag1.to_string(), tag2.to_string());
}

// Test that different tags produce different to_string output
TEST_F(AsfVideoGUIDTagTest_1557, DifferentTagsDifferentToString_1557) {
    std::array<byte, 8> data4a = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    std::array<byte, 8> data4b = {0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4a);
    auto tag2 = makeTag(0x87654321, 0x4321, 0x8765, data4b);
    EXPECT_NE(tag1.to_string(), tag2.to_string());
}

// Test operator< (less than) - reflexivity: a tag is not less than itself
TEST_F(AsfVideoGUIDTagTest_1557, LessThanNotReflexive_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag = makeTag(0x12345678, 0x1234, 0x5678, data4);
    EXPECT_FALSE(tag < tag);
}

// Test operator< with different data1 values
TEST_F(AsfVideoGUIDTagTest_1557, LessThanByData1_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tagSmall = makeTag(0x00000001, 0x1234, 0x5678, data4);
    auto tagLarge = makeTag(0xFFFFFFFF, 0x1234, 0x5678, data4);
    // One must be less than the other
    EXPECT_TRUE((tagSmall < tagLarge) || (tagLarge < tagSmall));
    // They should not be equal
    EXPECT_FALSE(tagSmall == tagLarge);
}

// Test operator< antisymmetry
TEST_F(AsfVideoGUIDTagTest_1557, LessThanAntisymmetric_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag1 = makeTag(0x00000001, 0x1234, 0x5678, data4);
    auto tag2 = makeTag(0x00000002, 0x1234, 0x5678, data4);
    if (tag1 < tag2) {
        EXPECT_FALSE(tag2 < tag1);
    } else {
        EXPECT_TRUE(tag2 < tag1);
    }
}

// Test operator< with equal tags returns false
TEST_F(AsfVideoGUIDTagTest_1557, LessThanEqualTagsFalse_1557) {
    std::array<byte, 8> data4 = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11};
    auto tag1 = makeTag(0xDEADBEEF, 0xCAFE, 0xBABE, data4);
    auto tag2 = makeTag(0xDEADBEEF, 0xCAFE, 0xBABE, data4);
    EXPECT_FALSE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test that equality and less-than are consistent
TEST_F(AsfVideoGUIDTagTest_1557, EqualityAndLessThanConsistent_1557) {
    std::array<byte, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4);
    auto tag2 = makeTag(0x12345678, 0x1234, 0x5678, data4);
    // If equal, neither should be less than the other
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_FALSE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test construction from bytes produces consistent results
TEST_F(AsfVideoGUIDTagTest_1557, ByteConstructorConsistency_1557) {
    uint8_t bytes1[16] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00,
                          0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};
    uint8_t bytes2[16] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00,
                          0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};
    AsfVideo::GUIDTag tag1(bytes1);
    AsfVideo::GUIDTag tag2(bytes2);
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_EQ(tag1.to_string(), tag2.to_string());
}

// Test byte constructor with different bytes produces inequality
TEST_F(AsfVideoGUIDTagTest_1557, ByteConstructorDifferentBytes_1557) {
    uint8_t bytes1[16] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00,
                          0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};
    uint8_t bytes2[16] = {0xFF, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00,
                          0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};
    AsfVideo::GUIDTag tag1(bytes1);
    AsfVideo::GUIDTag tag2(bytes2);
    EXPECT_FALSE(tag1 == tag2);
}

// Test with only data4 middle byte different
TEST_F(AsfVideoGUIDTagTest_1557, Data4MiddleByteDifference_1557) {
    std::array<byte, 8> data4a = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    std::array<byte, 8> data4b = {0x01, 0x02, 0x03, 0xFF, 0x05, 0x06, 0x07, 0x08};
    auto tag1 = makeTag(0x12345678, 0x1234, 0x5678, data4a);
    auto tag2 = makeTag(0x12345678, 0x1234, 0x5678, data4b);
    EXPECT_FALSE(tag1 == tag2);
}

// Test symmetry of equality
TEST_F(AsfVideoGUIDTagTest_1557, EqualityIsSymmetric_1557) {
    std::array<byte, 8> data4 = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE};
    auto tag1 = makeTag(0xAAAAAAAA, 0xBBBB, 0xCCCC, data4);
    auto tag2 = makeTag(0xAAAAAAAA, 0xBBBB, 0xCCCC, data4);
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_TRUE(tag2 == tag1);
}

// Test inequality symmetry
TEST_F(AsfVideoGUIDTagTest_1557, InequalityIsSymmetric_1557) {
    std::array<byte, 8> data4 = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE};
    auto tag1 = makeTag(0xAAAAAAAA, 0xBBBB, 0xCCCC, data4);
    auto tag2 = makeTag(0x11111111, 0xBBBB, 0xCCCC, data4);
    EXPECT_FALSE(tag1 == tag2);
    EXPECT_FALSE(tag2 == tag1);
}
