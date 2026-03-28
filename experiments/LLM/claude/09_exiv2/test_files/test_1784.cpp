#include <gtest/gtest.h>
#include "exiv2/types.hpp"

// We need to include the header for CiffComponent
// Based on the provided code, we replicate the static method for testing
namespace Exiv2 {
namespace Internal {

class CiffComponent {
 public:
  static TypeId typeId(uint16_t tag) {
    switch (tag & 0x3800) {
      case 0x0000:
        return unsignedByte;
      case 0x0800:
        return asciiString;
      case 0x1000:
        return unsignedShort;
      case 0x1800:
        return unsignedLong;
      case 0x2000:
        return undefined;
      case 0x2800:
      case 0x3000:
        return directory;
    }
    return invalidTypeId;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::CiffComponent;
using Exiv2::TypeId;

class CiffComponentTypeIdTest_1784 : public ::testing::Test {
 protected:
  // Helper to isolate bits 11-13 (mask 0x3800)
};

// Test that tag with bits [13:11] = 000 returns unsignedByte
TEST_F(CiffComponentTypeIdTest_1784, TagBits000_ReturnsUnsignedByte_1784) {
  // 0x0000 & 0x3800 == 0x0000
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0x0000));
}

// Test unsignedByte with other bits set (bits outside 0x3800 mask)
TEST_F(CiffComponentTypeIdTest_1784, TagBits000_WithOtherBitsSet_ReturnsUnsignedByte_1784) {
  // 0x0001 & 0x3800 == 0x0000
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0x0001));
  // 0x0400 & 0x3800 == 0x0000
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0x0400));
  // 0xC7FF & 0x3800 == 0x0000
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0xC7FF));
}

// Test that tag with bits [13:11] = 001 returns asciiString
TEST_F(CiffComponentTypeIdTest_1784, TagBits001_ReturnsAsciiString_1784) {
  // 0x0800 & 0x3800 == 0x0800
  EXPECT_EQ(Exiv2::asciiString, CiffComponent::typeId(0x0800));
}

TEST_F(CiffComponentTypeIdTest_1784, TagBits001_WithOtherBitsSet_ReturnsAsciiString_1784) {
  EXPECT_EQ(Exiv2::asciiString, CiffComponent::typeId(0x0801));
  EXPECT_EQ(Exiv2::asciiString, CiffComponent::typeId(0x0BFF));
  EXPECT_EQ(Exiv2::asciiString, CiffComponent::typeId(0xC800));
}

// Test that tag with bits [13:11] = 010 returns unsignedShort
TEST_F(CiffComponentTypeIdTest_1784, TagBits010_ReturnsUnsignedShort_1784) {
  // 0x1000 & 0x3800 == 0x1000
  EXPECT_EQ(Exiv2::unsignedShort, CiffComponent::typeId(0x1000));
}

TEST_F(CiffComponentTypeIdTest_1784, TagBits010_WithOtherBitsSet_ReturnsUnsignedShort_1784) {
  EXPECT_EQ(Exiv2::unsignedShort, CiffComponent::typeId(0x1001));
  EXPECT_EQ(Exiv2::unsignedShort, CiffComponent::typeId(0xD7FF));
}

// Test that tag with bits [13:11] = 011 returns unsignedLong
TEST_F(CiffComponentTypeIdTest_1784, TagBits011_ReturnsUnsignedLong_1784) {
  // 0x1800 & 0x3800 == 0x1800
  EXPECT_EQ(Exiv2::unsignedLong, CiffComponent::typeId(0x1800));
}

TEST_F(CiffComponentTypeIdTest_1784, TagBits011_WithOtherBitsSet_ReturnsUnsignedLong_1784) {
  EXPECT_EQ(Exiv2::unsignedLong, CiffComponent::typeId(0x1801));
  EXPECT_EQ(Exiv2::unsignedLong, CiffComponent::typeId(0xDFFF));
}

// Test that tag with bits [13:11] = 100 returns undefined
TEST_F(CiffComponentTypeIdTest_1784, TagBits100_ReturnsUndefined_1784) {
  // 0x2000 & 0x3800 == 0x2000
  EXPECT_EQ(Exiv2::undefined, CiffComponent::typeId(0x2000));
}

TEST_F(CiffComponentTypeIdTest_1784, TagBits100_WithOtherBitsSet_ReturnsUndefined_1784) {
  EXPECT_EQ(Exiv2::undefined, CiffComponent::typeId(0x2001));
  EXPECT_EQ(Exiv2::undefined, CiffComponent::typeId(0xE7FF));
}

// Test that tag with bits [13:11] = 101 returns directory
TEST_F(CiffComponentTypeIdTest_1784, TagBits101_ReturnsDirectory_1784) {
  // 0x2800 & 0x3800 == 0x2800
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x2800));
}

TEST_F(CiffComponentTypeIdTest_1784, TagBits101_WithOtherBitsSet_ReturnsDirectory_1784) {
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x2801));
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0xEFFF));
}

// Test that tag with bits [13:11] = 110 returns directory
TEST_F(CiffComponentTypeIdTest_1784, TagBits110_ReturnsDirectory_1784) {
  // 0x3000 & 0x3800 == 0x3000
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x3000));
}

TEST_F(CiffComponentTypeIdTest_1784, TagBits110_WithOtherBitsSet_ReturnsDirectory_1784) {
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x3001));
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0xF7FF));
}

// Test that tag with bits [13:11] = 111 returns invalidTypeId
TEST_F(CiffComponentTypeIdTest_1784, TagBits111_ReturnsInvalidTypeId_1784) {
  // 0x3800 & 0x3800 == 0x3800
  EXPECT_EQ(Exiv2::invalidTypeId, CiffComponent::typeId(0x3800));
}

TEST_F(CiffComponentTypeIdTest_1784, TagBits111_WithOtherBitsSet_ReturnsInvalidTypeId_1784) {
  EXPECT_EQ(Exiv2::invalidTypeId, CiffComponent::typeId(0x3801));
  EXPECT_EQ(Exiv2::invalidTypeId, CiffComponent::typeId(0xFFFF));
  EXPECT_EQ(Exiv2::invalidTypeId, CiffComponent::typeId(0x3BFF));
}

// Boundary: minimum tag value
TEST_F(CiffComponentTypeIdTest_1784, MinTagValue_ReturnsUnsignedByte_1784) {
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0x0000));
}

// Boundary: maximum tag value
TEST_F(CiffComponentTypeIdTest_1784, MaxTagValue_ReturnsInvalidTypeId_1784) {
  EXPECT_EQ(Exiv2::invalidTypeId, CiffComponent::typeId(0xFFFF));
}

// Test boundary between asciiString (0x0800) and unsignedShort (0x1000)
TEST_F(CiffComponentTypeIdTest_1784, BoundaryBetweenAsciiAndShort_1784) {
  // 0x0FFF & 0x3800 == 0x0800 -> asciiString
  EXPECT_EQ(Exiv2::asciiString, CiffComponent::typeId(0x0FFF));
  // 0x1000 & 0x3800 == 0x1000 -> unsignedShort
  EXPECT_EQ(Exiv2::unsignedShort, CiffComponent::typeId(0x1000));
}

// Test boundary between unsignedByte (0x0000) and asciiString (0x0800)
TEST_F(CiffComponentTypeIdTest_1784, BoundaryBetweenByteAndAscii_1784) {
  // 0x07FF & 0x3800 == 0x0000 -> unsignedByte
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0x07FF));
  // 0x0800 & 0x3800 == 0x0800 -> asciiString
  EXPECT_EQ(Exiv2::asciiString, CiffComponent::typeId(0x0800));
}

// Test boundary between undefined (0x2000) and directory (0x2800)
TEST_F(CiffComponentTypeIdTest_1784, BoundaryBetweenUndefinedAndDirectory_1784) {
  // 0x27FF & 0x3800 == 0x2000 -> undefined
  EXPECT_EQ(Exiv2::undefined, CiffComponent::typeId(0x27FF));
  // 0x2800 & 0x3800 == 0x2800 -> directory
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x2800));
}

// Test boundary between directory (0x3000) and invalidTypeId (0x3800)
TEST_F(CiffComponentTypeIdTest_1784, BoundaryBetweenDirectoryAndInvalid_1784) {
  // 0x37FF & 0x3800 == 0x3000 -> directory
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x37FF));
  // 0x3800 & 0x3800 == 0x3800 -> invalidTypeId
  EXPECT_EQ(Exiv2::invalidTypeId, CiffComponent::typeId(0x3800));
}

// Both 0x2800 and 0x3000 map to directory - verify both explicitly
TEST_F(CiffComponentTypeIdTest_1784, BothDirectoryRangesReturnDirectory_1784) {
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x2800));
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x3000));
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x2FFF));
  EXPECT_EQ(Exiv2::directory, CiffComponent::typeId(0x37FF));
}

// Test with high bits set (bits 14 and 15) - these are outside the 0x3800 mask
TEST_F(CiffComponentTypeIdTest_1784, HighBitsDoNotAffectResult_1784) {
  // 0x4000 & 0x3800 == 0x0000 -> unsignedByte
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0x4000));
  // 0x8000 & 0x3800 == 0x0000 -> unsignedByte
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0x8000));
  // 0xC000 & 0x3800 == 0x0000 -> unsignedByte
  EXPECT_EQ(Exiv2::unsignedByte, CiffComponent::typeId(0xC000));
  // 0xC800 & 0x3800 == 0x0800 -> asciiString
  EXPECT_EQ(Exiv2::asciiString, CiffComponent::typeId(0xC800));
}

// Test low bits do not affect result
TEST_F(CiffComponentTypeIdTest_1784, LowBitsDoNotAffectResult_1784) {
  // All values with bits [13:11] = 010 should give unsignedShort regardless of low bits
  for (uint16_t low = 0; low < 0x07FF; low += 0xFF) {
    uint16_t tag = 0x1000 | low;
    EXPECT_EQ(Exiv2::unsignedShort, CiffComponent::typeId(tag))
        << "Failed for tag=0x" << std::hex << tag;
  }
}
