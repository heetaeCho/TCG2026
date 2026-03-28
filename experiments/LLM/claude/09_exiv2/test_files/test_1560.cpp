#include <gtest/gtest.h>
#include <cstring>
#include "exiv2/asfvideo.hpp"

using namespace Exiv2;

// Helper function to construct bytes from GUIDTag components
// ASF GUIDs are stored in a specific byte order:
// data1: little-endian 4 bytes
// data2: little-endian 2 bytes
// data3: little-endian 2 bytes
// data4: 8 bytes as-is
static void makeGUIDBytes(uint8_t* buf, uint32_t data1, uint16_t data2, uint16_t data3, const std::array<uint8_t, 8>& data4) {
    // data1 - little endian
    buf[0] = static_cast<uint8_t>(data1 & 0xFF);
    buf[1] = static_cast<uint8_t>((data1 >> 8) & 0xFF);
    buf[2] = static_cast<uint8_t>((data1 >> 16) & 0xFF);
    buf[3] = static_cast<uint8_t>((data1 >> 24) & 0xFF);
    // data2 - little endian
    buf[4] = static_cast<uint8_t>(data2 & 0xFF);
    buf[5] = static_cast<uint8_t>((data2 >> 8) & 0xFF);
    // data3 - little endian
    buf[6] = static_cast<uint8_t>(data3 & 0xFF);
    buf[7] = static_cast<uint8_t>((data3 >> 8) & 0xFF);
    // data4 - as-is
    std::memcpy(buf + 8, data4.data(), 8);
}

class GUIDTagTest_1560 : public ::testing::Test {
protected:
    // Header GUID: {75B22630-668E-11CF-A6D9-00AA0062CE6C}
    // data1=1974609456 (0x75B22630), data2=26254 (0x668E), data3=4559 (0x11CF)
    // data4={0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C}
    static constexpr uint32_t headerData1 = 0x75B22630;
    static constexpr uint16_t headerData2 = 0x668E;
    static constexpr uint16_t headerData3 = 0x11CF;
    const std::array<uint8_t, 8> headerData4 = {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
};

// Test that GUIDTag constructed from bytes matching the Header GUID equals the Header constant
TEST_F(GUIDTagTest_1560, ConstructFromHeaderBytes_EqualsHeader_1560) {
    uint8_t buf[16];
    makeGUIDBytes(buf, headerData1, headerData2, headerData3, headerData4);

    AsfVideo::GUIDTag tag(buf);
    AsfVideo::GUIDTag header(headerData1, headerData2, headerData3, headerData4);

    EXPECT_TRUE(tag == header);
}

// Test that GUIDTag constructed with constexpr constructor matches itself
TEST_F(GUIDTagTest_1560, ConstexprConstructorSelfEquality_1560) {
    AsfVideo::GUIDTag tag1(headerData1, headerData2, headerData3, headerData4);
    AsfVideo::GUIDTag tag2(headerData1, headerData2, headerData3, headerData4);

    EXPECT_TRUE(tag1 == tag2);
}

// Test that different GUIDs are not equal
TEST_F(GUIDTagTest_1560, DifferentGUIDsAreNotEqual_1560) {
    AsfVideo::GUIDTag tag1(headerData1, headerData2, headerData3, headerData4);
    // Change data1
    AsfVideo::GUIDTag tag2(0x12345678, headerData2, headerData3, headerData4);

    EXPECT_FALSE(tag1 == tag2);
}

// Test that differing data2 results in inequality
TEST_F(GUIDTagTest_1560, DifferentData2NotEqual_1560) {
    AsfVideo::GUIDTag tag1(headerData1, headerData2, headerData3, headerData4);
    AsfVideo::GUIDTag tag2(headerData1, 0x0000, headerData3, headerData4);

    EXPECT_FALSE(tag1 == tag2);
}

// Test that differing data3 results in inequality
TEST_F(GUIDTagTest_1560, DifferentData3NotEqual_1560) {
    AsfVideo::GUIDTag tag1(headerData1, headerData2, headerData3, headerData4);
    AsfVideo::GUIDTag tag2(headerData1, headerData2, 0x0000, headerData4);

    EXPECT_FALSE(tag1 == tag2);
}

// Test that differing data4 results in inequality
TEST_F(GUIDTagTest_1560, DifferentData4NotEqual_1560) {
    AsfVideo::GUIDTag tag1(headerData1, headerData2, headerData3, headerData4);
    std::array<uint8_t, 8> differentData4 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    AsfVideo::GUIDTag tag2(headerData1, headerData2, headerData3, differentData4);

    EXPECT_FALSE(tag1 == tag2);
}

// Test the less-than operator for ordering
TEST_F(GUIDTagTest_1560, LessThanOperator_1560) {
    AsfVideo::GUIDTag smaller(0x00000001, 0x0000, 0x0000, {0, 0, 0, 0, 0, 0, 0, 0});
    AsfVideo::GUIDTag larger(0xFFFFFFFF, 0xFFFF, 0xFFFF, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF});

    EXPECT_TRUE(smaller < larger);
    EXPECT_FALSE(larger < smaller);
}

// Test that a tag is not less than itself
TEST_F(GUIDTagTest_1560, NotLessThanSelf_1560) {
    AsfVideo::GUIDTag tag(headerData1, headerData2, headerData3, headerData4);

    EXPECT_FALSE(tag < tag);
}

// Test to_string returns a non-empty string
TEST_F(GUIDTagTest_1560, ToStringReturnsNonEmpty_1560) {
    AsfVideo::GUIDTag tag(headerData1, headerData2, headerData3, headerData4);
    std::string str = tag.to_string();

    EXPECT_FALSE(str.empty());
}

// Test to_string for Header GUID contains expected components
TEST_F(GUIDTagTest_1560, ToStringContainsGUIDComponents_1560) {
    AsfVideo::GUIDTag tag(headerData1, headerData2, headerData3, headerData4);
    std::string str = tag.to_string();

    // The GUID string representation should contain hex digits
    // We check it has reasonable length (standard GUID format is 36 chars with dashes)
    EXPECT_GE(str.size(), 16u);
}

// Test constructing GUIDTag from all-zero bytes
TEST_F(GUIDTagTest_1560, AllZeroBytes_1560) {
    uint8_t buf[16] = {0};
    AsfVideo::GUIDTag tag(buf);
    AsfVideo::GUIDTag zero(0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});

    EXPECT_TRUE(tag == zero);
}

// Test constructing GUIDTag from all-0xFF bytes
TEST_F(GUIDTagTest_1560, AllFFBytes_1560) {
    uint8_t buf[16];
    std::memset(buf, 0xFF, 16);
    AsfVideo::GUIDTag tag(buf);
    AsfVideo::GUIDTag allFF(0xFFFFFFFF, 0xFFFF, 0xFFFF, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF});

    EXPECT_TRUE(tag == allFF);
}

// Test that zero GUID is not equal to Header GUID
TEST_F(GUIDTagTest_1560, ZeroNotEqualToHeader_1560) {
    AsfVideo::GUIDTag zero(0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    AsfVideo::GUIDTag header(headerData1, headerData2, headerData3, headerData4);

    EXPECT_FALSE(zero == header);
}

// Test less-than with data2 difference
TEST_F(GUIDTagTest_1560, LessThanByData2_1560) {
    AsfVideo::GUIDTag tag1(0x00000001, 0x0001, 0x0000, {0, 0, 0, 0, 0, 0, 0, 0});
    AsfVideo::GUIDTag tag2(0x00000001, 0x0002, 0x0000, {0, 0, 0, 0, 0, 0, 0, 0});

    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test less-than with data3 difference
TEST_F(GUIDTagTest_1560, LessThanByData3_1560) {
    AsfVideo::GUIDTag tag1(0x00000001, 0x0001, 0x0001, {0, 0, 0, 0, 0, 0, 0, 0});
    AsfVideo::GUIDTag tag2(0x00000001, 0x0001, 0x0002, {0, 0, 0, 0, 0, 0, 0, 0});

    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test less-than with data4 difference
TEST_F(GUIDTagTest_1560, LessThanByData4_1560) {
    AsfVideo::GUIDTag tag1(0x00000001, 0x0001, 0x0001, {0, 0, 0, 0, 0, 0, 0, 0});
    AsfVideo::GUIDTag tag2(0x00000001, 0x0001, 0x0001, {0, 0, 0, 0, 0, 0, 0, 1});

    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test that two identical GUIDTags produce the same to_string
TEST_F(GUIDTagTest_1560, IdenticalTagsSameToString_1560) {
    AsfVideo::GUIDTag tag1(headerData1, headerData2, headerData3, headerData4);
    AsfVideo::GUIDTag tag2(headerData1, headerData2, headerData3, headerData4);

    EXPECT_EQ(tag1.to_string(), tag2.to_string());
}

// Test that different GUIDTags produce different to_string
TEST_F(GUIDTagTest_1560, DifferentTagsDifferentToString_1560) {
    AsfVideo::GUIDTag tag1(headerData1, headerData2, headerData3, headerData4);
    AsfVideo::GUIDTag tag2(0x00000000, 0x0000, 0x0000, {0, 0, 0, 0, 0, 0, 0, 0});

    EXPECT_NE(tag1.to_string(), tag2.to_string());
}

// Test byte-constructed tag roundtrip consistency
TEST_F(GUIDTagTest_1560, ByteConstructorConsistency_1560) {
    uint8_t buf[16];
    makeGUIDBytes(buf, headerData1, headerData2, headerData3, headerData4);

    AsfVideo::GUIDTag tag1(buf);
    AsfVideo::GUIDTag tag2(buf);

    EXPECT_TRUE(tag1 == tag2);
    EXPECT_FALSE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test single byte difference in data4
TEST_F(GUIDTagTest_1560, SingleByteDifferenceInData4_1560) {
    std::array<uint8_t, 8> data4a = {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
    std::array<uint8_t, 8> data4b = {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6D}; // last byte differs

    AsfVideo::GUIDTag tag1(headerData1, headerData2, headerData3, data4a);
    AsfVideo::GUIDTag tag2(headerData1, headerData2, headerData3, data4b);

    EXPECT_FALSE(tag1 == tag2);
}
