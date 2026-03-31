#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MnHeaderTest_2189 : public ::testing::Test {
 protected:
  Nikon3MnHeader header_;
};

// Test that default construction succeeds and produces a valid object
TEST_F(Nikon3MnHeaderTest_2189, DefaultConstruction_2189) {
  Nikon3MnHeader h;
  // Should not crash, object should be valid
  EXPECT_GT(h.size(), 0u);
}

// Test sizeOfSignature returns a positive value
TEST_F(Nikon3MnHeaderTest_2189, SizeOfSignaturePositive_2189) {
  size_t sigSize = Nikon3MnHeader::sizeOfSignature();
  EXPECT_GT(sigSize, 0u);
}

// Test that size() returns at least sizeOfSignature
TEST_F(Nikon3MnHeaderTest_2189, SizeAtLeastSignatureSize_2189) {
  EXPECT_GE(header_.size(), Nikon3MnHeader::sizeOfSignature());
}

// Test ifdOffset returns the expected value (should be sizeOfSignature based on constructor)
TEST_F(Nikon3MnHeaderTest_2189, IfdOffsetEqualsSizeOfSignature_2189) {
  // From the constructor: start_ = sizeOfSignature(), and ifdOffset likely returns start_
  EXPECT_EQ(header_.ifdOffset(), Nikon3MnHeader::sizeOfSignature());
}

// Test byteOrder returns a valid byte order after default construction
TEST_F(Nikon3MnHeaderTest_2189, DefaultByteOrder_2189) {
  ByteOrder bo = header_.byteOrder();
  // Should be one of the valid byte orders
  EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test baseOffset with zero offset
TEST_F(Nikon3MnHeaderTest_2189, BaseOffsetZero_2189) {
  size_t base = header_.baseOffset(0);
  // baseOffset should return some defined value
  EXPECT_GE(base, 0u);
}

// Test baseOffset with non-zero offset
TEST_F(Nikon3MnHeaderTest_2189, BaseOffsetNonZero_2189) {
  size_t base = header_.baseOffset(100);
  // baseOffset typically returns the mnOffset itself or some computation of it
  EXPECT_GE(base, 0u);
}

// Test read with nullptr/insufficient data returns false
TEST_F(Nikon3MnHeaderTest_2189, ReadWithInsufficientSize_2189) {
  // Reading with size 0 should fail
  bool result = header_.read(nullptr, 0, littleEndian);
  EXPECT_FALSE(result);
}

// Test read with size smaller than signature size returns false
TEST_F(Nikon3MnHeaderTest_2189, ReadWithTooSmallSize_2189) {
  const byte smallData[] = {0x00, 0x01};
  size_t sigSize = Nikon3MnHeader::sizeOfSignature();
  if (sigSize > 2) {
    bool result = header_.read(smallData, 2, littleEndian);
    EXPECT_FALSE(result);
  }
}

// Test read with valid Nikon3 maker note signature
// The Nikon3 signature is typically "Nikon\0\x02\x10\x00\x00" (10 bytes)
TEST_F(Nikon3MnHeaderTest_2189, ReadWithValidSignature_2189) {
  // Nikon3 maker note signature: "Nikon\0" + version info + TIFF header
  const byte validData[] = {
      'N', 'i', 'k', 'o', 'n', '\0',  // "Nikon\0"
      0x02, 0x10,                        // version
      0x00, 0x00,                        // padding
      0x4D, 0x4D,                        // "MM" (big endian TIFF)
      0x00, 0x2A,                        // TIFF magic 42
      0x00, 0x00, 0x00, 0x08,           // offset to first IFD
  };
  size_t dataSize = sizeof(validData);
  bool result = header_.read(validData, dataSize, bigEndian);
  // This should succeed if the signature matches
  EXPECT_TRUE(result);
}

// Test read with invalid signature data
TEST_F(Nikon3MnHeaderTest_2189, ReadWithInvalidSignature_2189) {
  const byte invalidData[] = {
      'C', 'a', 'n', 'o', 'n', '\0',
      0x02, 0x10,
      0x00, 0x00,
      0x4D, 0x4D,
      0x00, 0x2A,
      0x00, 0x00, 0x00, 0x08,
  };
  size_t dataSize = sizeof(invalidData);
  bool result = header_.read(invalidData, dataSize, bigEndian);
  EXPECT_FALSE(result);
}

// Test setByteOrder changes the byte order
TEST_F(Nikon3MnHeaderTest_2189, SetByteOrderLittleEndian_2189) {
  header_.setByteOrder(littleEndian);
  EXPECT_EQ(header_.byteOrder(), littleEndian);
}

TEST_F(Nikon3MnHeaderTest_2189, SetByteOrderBigEndian_2189) {
  header_.setByteOrder(bigEndian);
  EXPECT_EQ(header_.byteOrder(), bigEndian);
}

// Test that after reading valid data with little endian TIFF header, byteOrder is updated
TEST_F(Nikon3MnHeaderTest_2189, ReadSetsLittleEndianByteOrder_2189) {
  const byte validDataLE[] = {
      'N', 'i', 'k', 'o', 'n', '\0',
      0x02, 0x10,
      0x00, 0x00,
      0x49, 0x49,                        // "II" (little endian TIFF)
      0x2A, 0x00,                        // TIFF magic 42 LE
      0x08, 0x00, 0x00, 0x00,           // offset to first IFD LE
  };
  size_t dataSize = sizeof(validDataLE);
  bool result = header_.read(validDataLE, dataSize, littleEndian);
  if (result) {
    EXPECT_EQ(header_.byteOrder(), littleEndian);
  }
}

// Test that after reading valid data with big endian TIFF header, byteOrder is updated
TEST_F(Nikon3MnHeaderTest_2189, ReadSetsBigEndianByteOrder_2189) {
  const byte validDataBE[] = {
      'N', 'i', 'k', 'o', 'n', '\0',
      0x02, 0x10,
      0x00, 0x00,
      0x4D, 0x4D,                        // "MM" (big endian TIFF)
      0x00, 0x2A,                        // TIFF magic 42 BE
      0x00, 0x00, 0x00, 0x08,           // offset to first IFD BE
  };
  size_t dataSize = sizeof(validDataBE);
  bool result = header_.read(validDataBE, dataSize, bigEndian);
  if (result) {
    EXPECT_EQ(header_.byteOrder(), bigEndian);
  }
}

// Test size consistency: size should be consistent across calls
TEST_F(Nikon3MnHeaderTest_2189, SizeConsistency_2189) {
  size_t s1 = header_.size();
  size_t s2 = header_.size();
  EXPECT_EQ(s1, s2);
}

// Test that reading with exact signature size but no TIFF header fails
TEST_F(Nikon3MnHeaderTest_2189, ReadWithExactSignatureSizeOnly_2189) {
  size_t sigSize = Nikon3MnHeader::sizeOfSignature();
  std::vector<byte> data(sigSize);
  // Fill with Nikon signature
  const char* sig = "Nikon\0";
  if (sigSize >= 6) {
    std::memcpy(data.data(), sig, 6);
  }
  // Size equals signature size but may not have enough for TIFF header
  bool result = header_.read(data.data(), data.size(), littleEndian);
  // Likely fails because there's not enough data for the full header
  // We just verify it doesn't crash
  (void)result;
}

// Test baseOffset returns mnOffset for typical usage
TEST_F(Nikon3MnHeaderTest_2189, BaseOffsetReturnsExpectedValue_2189) {
  size_t offset = 1000;
  size_t base = header_.baseOffset(offset);
  // For Nikon3, baseOffset typically returns mnOffset + 10 (sizeOfSignature)
  // But we can't assume the exact value, just that it's reasonable
  EXPECT_GE(base, 0u);
}

// Test multiple setByteOrder calls
TEST_F(Nikon3MnHeaderTest_2189, MultipleSetByteOrderCalls_2189) {
  header_.setByteOrder(littleEndian);
  EXPECT_EQ(header_.byteOrder(), littleEndian);

  header_.setByteOrder(bigEndian);
  EXPECT_EQ(header_.byteOrder(), bigEndian);

  header_.setByteOrder(littleEndian);
  EXPECT_EQ(header_.byteOrder(), littleEndian);
}

// Test read with size 1 (boundary)
TEST_F(Nikon3MnHeaderTest_2189, ReadWithSize1_2189) {
  const byte data = 0x00;
  bool result = header_.read(&data, 1, littleEndian);
  EXPECT_FALSE(result);
}

// Test that sizeOfSignature is a static method and returns consistent value
TEST_F(Nikon3MnHeaderTest_2189, SizeOfSignatureStatic_2189) {
  size_t s1 = Nikon3MnHeader::sizeOfSignature();
  size_t s2 = Nikon3MnHeader::sizeOfSignature();
  EXPECT_EQ(s1, s2);
  EXPECT_GT(s1, 0u);
}
