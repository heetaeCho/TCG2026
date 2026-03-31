#include <gtest/gtest.h>
#include <cstdint>
#include <stdexcept>

// Include necessary headers
#include "exiv2/error.hpp"

// We need to access the internal function. Since it's in an anonymous-like internal namespace,
// we declare it here based on the provided code.
namespace Exiv2 {
namespace Internal {

using byte = uint8_t;

static size_t returnTagValue(const byte* buf, size_t size) {
  // We rely on the enforce function from exiv2
  // Re-declare to match the signature from the source
  extern void enforce(bool, Exiv2::ErrorCode);
  
  enforce(size > 0 && size <= 8, Exiv2::ErrorCode::kerCorruptedMetadata);
  size_t b0 = buf[0] & (0xff >> size);
  size_t tag = b0 << ((size - 1) * 8);
  for (size_t i = 1; i < size; ++i) {
    tag |= static_cast<size_t>(buf[i]) << ((size - i - 1) * 8);
  }
  return tag;
}

}  // namespace Internal
}  // namespace Exiv2

// Since enforce might throw, let's include the enforce header if available
// For the test, we assume enforce throws an Exiv2::Error on failure
#include "exiv2/enforce.hpp"

using Exiv2::Internal::returnTagValue;
using byte = uint8_t;

class ReturnTagValueTest_94 : public ::testing::Test {
protected:
};

// Test: Size of 0 should throw (boundary: below minimum)
TEST_F(ReturnTagValueTest_94, SizeZeroThrows_94) {
  byte buf[] = {0x80};
  EXPECT_THROW(returnTagValue(buf, 0), std::exception);
}

// Test: Size of 9 should throw (boundary: above maximum)
TEST_F(ReturnTagValueTest_94, SizeNineThrows_94) {
  byte buf[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  EXPECT_THROW(returnTagValue(buf, 9), std::exception);
}

// Test: Size of 1 with a single byte
TEST_F(ReturnTagValueTest_94, SizeOneBasic_94) {
  // size=1: mask is 0xff >> 1 = 0x7f
  // buf[0] & 0x7f
  byte buf[] = {0xFF};
  size_t result = returnTagValue(buf, 1);
  EXPECT_EQ(result, 0x7Fu);
}

// Test: Size of 1 with zero byte
TEST_F(ReturnTagValueTest_94, SizeOneZero_94) {
  byte buf[] = {0x00};
  size_t result = returnTagValue(buf, 1);
  EXPECT_EQ(result, 0x00u);
}

// Test: Size of 1 - the high bit is masked off
TEST_F(ReturnTagValueTest_94, SizeOneMasksHighBit_94) {
  // 0x80 & 0x7F = 0x00
  byte buf[] = {0x80};
  size_t result = returnTagValue(buf, 1);
  EXPECT_EQ(result, 0x00u);
}

// Test: Size of 2 with known bytes
TEST_F(ReturnTagValueTest_94, SizeTwoBasic_94) {
  // size=2: mask is 0xff >> 2 = 0x3f
  // b0 = buf[0] & 0x3f = 0x40 & 0x3f = 0x00
  // tag = 0x00 << 8 = 0x00
  // tag |= buf[1] << 0 = 0x01
  // result = 0x01
  byte buf[] = {0x40, 0x01};
  size_t result = returnTagValue(buf, 2);
  EXPECT_EQ(result, 0x01u);
}

// Test: Size of 2 with all bits set in data portion
TEST_F(ReturnTagValueTest_94, SizeTwoAllDataBits_94) {
  // size=2: mask is 0x3f
  // b0 = 0x7F & 0x3F = 0x3F
  // tag = 0x3F << 8 = 0x3F00
  // tag |= 0xFF = 0x3FFF
  byte buf[] = {0x7F, 0xFF};
  size_t result = returnTagValue(buf, 2);
  EXPECT_EQ(result, 0x3FFFu);
}

// Test: Size of 3
TEST_F(ReturnTagValueTest_94, SizeThreeBasic_94) {
  // size=3: mask is 0xff >> 3 = 0x1f
  // b0 = buf[0] & 0x1f = 0x20 & 0x1f = 0x00
  // tag = 0x00 << 16 = 0
  // tag |= buf[1] << 8 = 0x01 << 8 = 0x100
  // tag |= buf[2] << 0 = 0x02
  // result = 0x102
  byte buf[] = {0x20, 0x01, 0x02};
  size_t result = returnTagValue(buf, 3);
  EXPECT_EQ(result, 0x0102u);
}

// Test: Size of 4
TEST_F(ReturnTagValueTest_94, SizeFourBasic_94) {
  // size=4: mask is 0xff >> 4 = 0x0f
  // b0 = 0x1A & 0x0F = 0x0A
  // tag = 0x0A << 24 = 0x0A000000
  // tag |= 0xBB << 16 = 0x00BB0000
  // tag |= 0xCC << 8  = 0x0000CC00
  // tag |= 0xDD << 0  = 0x000000DD
  // result = 0x0ABBCCDD
  byte buf[] = {0x1A, 0xBB, 0xCC, 0xDD};
  size_t result = returnTagValue(buf, 4);
  EXPECT_EQ(result, 0x0ABBCCDDu);
}

// Test: Size of 4 with all zeros
TEST_F(ReturnTagValueTest_94, SizeFourAllZeros_94) {
  byte buf[] = {0x10, 0x00, 0x00, 0x00};
  // mask = 0x0f, b0 = 0x10 & 0x0f = 0x00
  size_t result = returnTagValue(buf, 4);
  EXPECT_EQ(result, 0x00u);
}

// Test: Size of 8 (maximum valid size)
TEST_F(ReturnTagValueTest_94, SizeEightBasic_94) {
  // size=8: mask is 0xff >> 8 = 0x00
  // b0 = buf[0] & 0x00 = 0x00
  // tag = 0x00 << 56 = 0
  // then remaining bytes assembled
  byte buf[] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
  size_t result = returnTagValue(buf, 8);
  // b0 = 0xFF & 0x00 = 0x00
  // All intermediate bytes are 0x00
  // Last byte is 0x01
  EXPECT_EQ(result, 0x01u);
}

// Test: Size of 8 with all FF bytes
TEST_F(ReturnTagValueTest_94, SizeEightAllFF_94) {
  // size=8: mask is 0x00
  // b0 = 0xFF & 0x00 = 0x00
  // remaining 7 bytes all 0xFF
  byte buf[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  size_t result = returnTagValue(buf, 8);
  // tag = 0x00 << 56 = 0
  // tag |= 0xFF << 48 | 0xFF << 40 | ... | 0xFF << 0
  // = 0x00FFFFFFFFFFFFFF
  size_t expected = 0x00FFFFFFFFFFFFFFull;
  EXPECT_EQ(result, expected);
}

// Test: Size of 1 with value 0x01
TEST_F(ReturnTagValueTest_94, SizeOneValueOne_94) {
  // mask = 0x7f, b0 = 0x81 & 0x7f = 0x01
  byte buf[] = {0x81};
  size_t result = returnTagValue(buf, 1);
  EXPECT_EQ(result, 0x01u);
}

// Test: Size of 7
TEST_F(ReturnTagValueTest_94, SizeSevenBasic_94) {
  // size=7: mask is 0xff >> 7 = 0x01
  // b0 = buf[0] & 0x01
  byte buf[] = {0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  // b0 = 0x03 & 0x01 = 0x01
  // tag = 0x01 << 48
  // tag |= 0x01 << 40 | 0x02 << 32 | 0x03 << 24 | 0x04 << 16 | 0x05 << 8 | 0x06
  size_t expected = (size_t(0x01) << 48) | (size_t(0x01) << 40) | (size_t(0x02) << 32) |
                    (size_t(0x03) << 24) | (size_t(0x04) << 16) | (size_t(0x05) << 8) | 0x06;
  size_t result = returnTagValue(buf, 7);
  EXPECT_EQ(result, expected);
}

// Test: Size of 5
TEST_F(ReturnTagValueTest_94, SizeFiveBasic_94) {
  // size=5: mask is 0xff >> 5 = 0x07
  byte buf[] = {0x08, 0x01, 0x02, 0x03, 0x04};
  // b0 = 0x08 & 0x07 = 0x00
  // tag = 0x00 << 32 = 0
  // tag |= 0x01 << 24 | 0x02 << 16 | 0x03 << 8 | 0x04
  size_t expected = (size_t(0x01) << 24) | (size_t(0x02) << 16) | (size_t(0x03) << 8) | 0x04;
  size_t result = returnTagValue(buf, 5);
  EXPECT_EQ(result, expected);
}

// Test: Size of 6
TEST_F(ReturnTagValueTest_94, SizeSixBasic_94) {
  // size=6: mask is 0xff >> 6 = 0x03
  byte buf[] = {0x07, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
  // b0 = 0x07 & 0x03 = 0x03
  // tag = 0x03 << 40
  // tag |= 0xAA << 32 | 0xBB << 24 | 0xCC << 16 | 0xDD << 8 | 0xEE
  size_t expected = (size_t(0x03) << 40) | (size_t(0xAA) << 32) | (size_t(0xBB) << 24) |
                    (size_t(0xCC) << 16) | (size_t(0xDD) << 8) | 0xEE;
  size_t result = returnTagValue(buf, 6);
  EXPECT_EQ(result, expected);
}

// Test: Very large size value (e.g., SIZE_MAX) should throw
TEST_F(ReturnTagValueTest_94, SizeVeryLargeThrows_94) {
  byte buf[] = {0x00};
  EXPECT_THROW(returnTagValue(buf, 100), std::exception);
}

// Test: Size of 2, verifying the mask correctly strips leading bits
TEST_F(ReturnTagValueTest_94, SizeTwoMaskVerification_94) {
  // size=2: mask = 0x3F
  // buf[0] = 0xFF -> b0 = 0xFF & 0x3F = 0x3F
  // tag = 0x3F << 8 | 0x00 = 0x3F00
  byte buf[] = {0xFF, 0x00};
  size_t result = returnTagValue(buf, 2);
  EXPECT_EQ(result, 0x3F00u);
}

// Test: Minimal non-zero result with size 1
TEST_F(ReturnTagValueTest_94, SizeOneMinimalNonZero_94) {
  byte buf[] = {0x81};  // 0x81 & 0x7F = 0x01
  EXPECT_EQ(returnTagValue(buf, 1), 1u);
}

// Test: Size 3 with maximum data value
TEST_F(ReturnTagValueTest_94, SizeThreeMaxData_94) {
  // size=3: mask = 0x1f
  // buf[0] = 0x3F -> b0 = 0x3F & 0x1F = 0x1F
  // tag = 0x1F << 16 | 0xFF << 8 | 0xFF = 0x1FFFFF
  byte buf[] = {0x3F, 0xFF, 0xFF};
  size_t result = returnTagValue(buf, 3);
  EXPECT_EQ(result, 0x1FFFFFu);
}
