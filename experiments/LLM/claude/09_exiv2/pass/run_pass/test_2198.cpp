#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <cstring>
#include <string>

// Include necessary headers
#include "exiv2/asfvideo.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

class GUIDTagTest_2198 : public ::testing::Test {
protected:
  // Helper to create a 16-byte buffer with specific values
  void createGUIDBytes(uint8_t* bytes, uint32_t data1, uint16_t data2, uint16_t data3,
                       const std::array<uint8_t, 8>& data4) {
    // data1 in little-endian
    bytes[0] = static_cast<uint8_t>(data1 & 0xFF);
    bytes[1] = static_cast<uint8_t>((data1 >> 8) & 0xFF);
    bytes[2] = static_cast<uint8_t>((data1 >> 16) & 0xFF);
    bytes[3] = static_cast<uint8_t>((data1 >> 24) & 0xFF);
    // data2 in little-endian
    bytes[4] = static_cast<uint8_t>(data2 & 0xFF);
    bytes[5] = static_cast<uint8_t>((data2 >> 8) & 0xFF);
    // data3 in little-endian
    bytes[6] = static_cast<uint8_t>(data3 & 0xFF);
    bytes[7] = static_cast<uint8_t>((data3 >> 8) & 0xFF);
    // data4 copied directly
    std::copy(data4.begin(), data4.end(), bytes + 8);
  }
};

// Test: Construct from bytes and verify equality with constexpr constructor
TEST_F(GUIDTagTest_2198, ConstructFromBytesMatchesConstexpr_2198) {
  uint8_t bytes[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes, 0x12345678, 0xABCD, 0xEF01, data4);

  AsfVideo::GUIDTag fromBytes(bytes);
  AsfVideo::GUIDTag fromConstexpr(0x12345678, 0xABCD, 0xEF01, data4);

  EXPECT_TRUE(fromBytes == fromConstexpr);
}

// Test: Two identical byte arrays produce equal GUIDTags
TEST_F(GUIDTagTest_2198, EqualityOfIdenticalByteArrays_2198) {
  uint8_t bytes1[16];
  uint8_t bytes2[16];
  std::array<uint8_t, 8> data4 = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11};
  createGUIDBytes(bytes1, 0xDEADBEEF, 0x1234, 0x5678, data4);
  createGUIDBytes(bytes2, 0xDEADBEEF, 0x1234, 0x5678, data4);

  AsfVideo::GUIDTag tag1(bytes1);
  AsfVideo::GUIDTag tag2(bytes2);

  EXPECT_TRUE(tag1 == tag2);
}

// Test: Different data1 produces non-equal GUIDTags
TEST_F(GUIDTagTest_2198, InequalityDifferentData1_2198) {
  uint8_t bytes1[16];
  uint8_t bytes2[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes1, 0x00000001, 0x0001, 0x0001, data4);
  createGUIDBytes(bytes2, 0x00000002, 0x0001, 0x0001, data4);

  AsfVideo::GUIDTag tag1(bytes1);
  AsfVideo::GUIDTag tag2(bytes2);

  EXPECT_FALSE(tag1 == tag2);
}

// Test: Different data2 produces non-equal GUIDTags
TEST_F(GUIDTagTest_2198, InequalityDifferentData2_2198) {
  uint8_t bytes1[16];
  uint8_t bytes2[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes1, 0x00000001, 0x0001, 0x0001, data4);
  createGUIDBytes(bytes2, 0x00000001, 0x0002, 0x0001, data4);

  AsfVideo::GUIDTag tag1(bytes1);
  AsfVideo::GUIDTag tag2(bytes2);

  EXPECT_FALSE(tag1 == tag2);
}

// Test: Different data3 produces non-equal GUIDTags
TEST_F(GUIDTagTest_2198, InequalityDifferentData3_2198) {
  uint8_t bytes1[16];
  uint8_t bytes2[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes1, 0x00000001, 0x0001, 0x0001, data4);
  createGUIDBytes(bytes2, 0x00000001, 0x0001, 0x0002, data4);

  AsfVideo::GUIDTag tag1(bytes1);
  AsfVideo::GUIDTag tag2(bytes2);

  EXPECT_FALSE(tag1 == tag2);
}

// Test: Different data4 produces non-equal GUIDTags
TEST_F(GUIDTagTest_2198, InequalityDifferentData4_2198) {
  uint8_t bytes1[16];
  uint8_t bytes2[16];
  std::array<uint8_t, 8> data4a = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  std::array<uint8_t, 8> data4b = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x09};
  createGUIDBytes(bytes1, 0x00000001, 0x0001, 0x0001, data4a);
  createGUIDBytes(bytes2, 0x00000001, 0x0001, 0x0001, data4b);

  AsfVideo::GUIDTag tag1(bytes1);
  AsfVideo::GUIDTag tag2(bytes2);

  EXPECT_FALSE(tag1 == tag2);
}

// Test: All zeros byte array
TEST_F(GUIDTagTest_2198, AllZerosBytes_2198) {
  uint8_t bytes[16] = {0};

  AsfVideo::GUIDTag tag(bytes);
  std::array<uint8_t, 8> zeroData4 = {0, 0, 0, 0, 0, 0, 0, 0};
  AsfVideo::GUIDTag expected(0, 0, 0, zeroData4);

  EXPECT_TRUE(tag == expected);
}

// Test: All 0xFF byte array
TEST_F(GUIDTagTest_2198, AllOnesBytes_2198) {
  uint8_t bytes[16];
  std::memset(bytes, 0xFF, 16);

  AsfVideo::GUIDTag tag(bytes);
  std::array<uint8_t, 8> ffData4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  AsfVideo::GUIDTag expected(0xFFFFFFFF, 0xFFFF, 0xFFFF, ffData4);

  EXPECT_TRUE(tag == expected);
}

// Test: to_string returns non-empty string
TEST_F(GUIDTagTest_2198, ToStringReturnsNonEmpty_2198) {
  uint8_t bytes[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes, 0x12345678, 0xABCD, 0xEF01, data4);

  AsfVideo::GUIDTag tag(bytes);
  std::string str = tag.to_string();

  EXPECT_FALSE(str.empty());
}

// Test: to_string for two equal tags returns same string
TEST_F(GUIDTagTest_2198, ToStringConsistentForEqualTags_2198) {
  uint8_t bytes[16];
  std::array<uint8_t, 8> data4 = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11};
  createGUIDBytes(bytes, 0xCAFEBABE, 0x1234, 0x5678, data4);

  AsfVideo::GUIDTag tag1(bytes);
  AsfVideo::GUIDTag tag2(bytes);

  EXPECT_EQ(tag1.to_string(), tag2.to_string());
}

// Test: to_string for two different tags returns different strings
TEST_F(GUIDTagTest_2198, ToStringDifferentForDifferentTags_2198) {
  uint8_t bytes1[16];
  uint8_t bytes2[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes1, 0x00000001, 0x0001, 0x0001, data4);
  createGUIDBytes(bytes2, 0x00000002, 0x0001, 0x0001, data4);

  AsfVideo::GUIDTag tag1(bytes1);
  AsfVideo::GUIDTag tag2(bytes2);

  EXPECT_NE(tag1.to_string(), tag2.to_string());
}

// Test: operator< provides strict weak ordering - less than
TEST_F(GUIDTagTest_2198, LessThanOperator_2198) {
  uint8_t bytes1[16];
  uint8_t bytes2[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes1, 0x00000001, 0x0001, 0x0001, data4);
  createGUIDBytes(bytes2, 0x00000002, 0x0001, 0x0001, data4);

  AsfVideo::GUIDTag tag1(bytes1);
  AsfVideo::GUIDTag tag2(bytes2);

  // One should be less than the other (they are not equal)
  EXPECT_TRUE(tag1 < tag2 || tag2 < tag1);
}

// Test: operator< irreflexivity - a tag is not less than itself
TEST_F(GUIDTagTest_2198, LessThanIrreflexive_2198) {
  uint8_t bytes[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes, 0x12345678, 0xABCD, 0xEF01, data4);

  AsfVideo::GUIDTag tag(bytes);

  EXPECT_FALSE(tag < tag);
}

// Test: Equal tags are not less than each other
TEST_F(GUIDTagTest_2198, EqualTagsNotLessThan_2198) {
  uint8_t bytes[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes, 0x12345678, 0xABCD, 0xEF01, data4);

  AsfVideo::GUIDTag tag1(bytes);
  AsfVideo::GUIDTag tag2(bytes);

  EXPECT_FALSE(tag1 < tag2);
  EXPECT_FALSE(tag2 < tag1);
}

// Test: operator< asymmetry - if a < b then !(b < a)
TEST_F(GUIDTagTest_2198, LessThanAsymmetry_2198) {
  uint8_t bytes1[16];
  uint8_t bytes2[16];
  std::array<uint8_t, 8> data4 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  createGUIDBytes(bytes1, 0x00000001, 0x0001, 0x0001, data4);
  createGUIDBytes(bytes2, 0x00000002, 0x0001, 0x0001, data4);

  AsfVideo::GUIDTag tag1(bytes1);
  AsfVideo::GUIDTag tag2(bytes2);

  if (tag1 < tag2) {
    EXPECT_FALSE(tag2 < tag1);
  } else {
    EXPECT_TRUE(tag2 < tag1);
    EXPECT_FALSE(tag1 < tag2);
  }
}

// Test: Little-endian byte ordering for data1
TEST_F(GUIDTagTest_2198, LittleEndianData1_2198) {
  // Construct bytes where data1 in little-endian is 0x04030201
  uint8_t bytes[16] = {0x01, 0x02, 0x03, 0x04, // data1 = 0x04030201
                        0x00, 0x00,             // data2 = 0
                        0x00, 0x00,             // data3 = 0
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  AsfVideo::GUIDTag tagFromBytes(bytes);
  std::array<uint8_t, 8> zeroData4 = {0, 0, 0, 0, 0, 0, 0, 0};
  AsfVideo::GUIDTag tagExpected(0x04030201, 0x0000, 0x0000, zeroData4);

  EXPECT_TRUE(tagFromBytes == tagExpected);
}

// Test: Little-endian byte ordering for data2
TEST_F(GUIDTagTest_2198, LittleEndianData2_2198) {
  uint8_t bytes[16] = {0x00, 0x00, 0x00, 0x00, // data1 = 0
                        0x01, 0x02,             // data2 = 0x0201
                        0x00, 0x00,             // data3 = 0
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  AsfVideo::GUIDTag tagFromBytes(bytes);
  std::array<uint8_t, 8> zeroData4 = {0, 0, 0, 0, 0, 0, 0, 0};
  AsfVideo::GUIDTag tagExpected(0x00000000, 0x0201, 0x0000, zeroData4);

  EXPECT_TRUE(tagFromBytes == tagExpected);
}

// Test: Little-endian byte ordering for data3
TEST_F(GUIDTagTest_2198, LittleEndianData3_2198) {
  uint8_t bytes[16] = {0x00, 0x00, 0x00, 0x00, // data1 = 0
                        0x00, 0x00,             // data2 = 0
                        0x01, 0x02,             // data3 = 0x0201
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  AsfVideo::GUIDTag tagFromBytes(bytes);
  std::array<uint8_t, 8> zeroData4 = {0, 0, 0, 0, 0, 0, 0, 0};
  AsfVideo::GUIDTag tagExpected(0x00000000, 0x0000, 0x0201, zeroData4);

  EXPECT_TRUE(tagFromBytes == tagExpected);
}

// Test: data4 is copied directly (not endian-swapped)
TEST_F(GUIDTagTest_2198, Data4CopiedDirectly_2198) {
  std::array<uint8_t, 8> data4 = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18};
  uint8_t bytes[16] = {0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00,
                        0x00, 0x00,
                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18};

  AsfVideo::GUIDTag tagFromBytes(bytes);
  std::array<uint8_t, 8> zeroData4 = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18};
  AsfVideo::GUIDTag tagExpected(0x00000000, 0x0000, 0x0000, zeroData4);

  EXPECT_TRUE(tagFromBytes == tagExpected);
}

// Test: Constexpr constructor produces valid to_string
TEST_F(GUIDTagTest_2198, ConstexprConstructorToString_2198) {
  std::array<uint8_t, 8> data4 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  AsfVideo::GUIDTag tag(0, 0, 0, data4);

  std::string str = tag.to_string();
  EXPECT_FALSE(str.empty());
}

// Test: Known GUID-like pattern (resembling ASF Header Object GUID)
TEST_F(GUIDTagTest_2198, KnownGUIDPattern_2198) {
  // ASF Header Object: 75B22630-668E-11CF-A6D9-00AA0062CE6C
  uint8_t bytes[16] = {
    0x30, 0x26, 0xB2, 0x75,  // data1 = 0x75B22630 (LE)
    0x8E, 0x66,              // data2 = 0x668E (LE)
    0xCF, 0x11,              // data3 = 0x11CF (LE)
    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C  // data4
  };

  AsfVideo::GUIDTag tag(bytes);
  std::array<uint8_t, 8> data4 = {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
  AsfVideo::GUIDTag expected(0x75B22630, 0x668E, 0x11CF, data4);

  EXPECT_TRUE(tag == expected);
}

// Test: Transitivity of operator< 
TEST_F(GUIDTagTest_2198, LessThanTransitivity_2198) {
  std::array<uint8_t, 8> data4 = {0, 0, 0, 0, 0, 0, 0, 0};
  AsfVideo::GUIDTag a(1, 0, 0, data4);
  AsfVideo::GUIDTag b(2, 0, 0, data4);
  AsfVideo::GUIDTag c(3, 0, 0, data4);

  // Determine ordering
  if (a < b && b < c) {
    EXPECT_TRUE(a < c);
  } else if (c < b && b < a) {
    EXPECT_TRUE(c < a);
  }
  // At minimum, they should all be distinct
  EXPECT_FALSE(a == b);
  EXPECT_FALSE(b == c);
  EXPECT_FALSE(a == c);
}

// Test: Equality is symmetric
TEST_F(GUIDTagTest_2198, EqualitySymmetric_2198) {
  uint8_t bytes[16];
  std::array<uint8_t, 8> data4 = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
  createGUIDBytes(bytes, 0xABCDEF01, 0x2345, 0x6789, data4);

  AsfVideo::GUIDTag tag1(bytes);
  AsfVideo::GUIDTag tag2(bytes);

  EXPECT_TRUE(tag1 == tag2);
  EXPECT_TRUE(tag2 == tag1);
}

// Test: to_string for zero GUID
TEST_F(GUIDTagTest_2198, ToStringZeroGUID_2198) {
  uint8_t bytes[16] = {0};
  AsfVideo::GUIDTag tag(bytes);

  std::string str = tag.to_string();
  EXPECT_FALSE(str.empty());
}

// Test: Maximum values for all fields
TEST_F(GUIDTagTest_2198, MaxValuesAllFields_2198) {
  std::array<uint8_t, 8> data4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  AsfVideo::GUIDTag tag(0xFFFFFFFF, 0xFFFF, 0xFFFF, data4);

  uint8_t bytes[16];
  std::memset(bytes, 0xFF, 16);
  AsfVideo::GUIDTag tagFromBytes(bytes);

  EXPECT_TRUE(tag == tagFromBytes);
}
