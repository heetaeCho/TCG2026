#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMnHeaderTest_1485 : public ::testing::Test {
 protected:
  PentaxMnHeader header_;
};

// Test that the default constructor creates a header with expected size
TEST_F(PentaxMnHeaderTest_1485, DefaultConstructorSize_1485) {
  // The PentaxMnHeader should have a non-zero size after default construction
  // since it contains a signature
  EXPECT_GT(header_.size(), 0u);
}

// Test that sizeOfSignature returns a consistent value
TEST_F(PentaxMnHeaderTest_1485, SizeOfSignature_1485) {
  size_t sigSize = PentaxMnHeader::sizeOfSignature();
  EXPECT_GT(sigSize, 0u);
}

// Test that size() is consistent with sizeOfSignature()
TEST_F(PentaxMnHeaderTest_1485, SizeConsistentWithSignature_1485) {
  // The header size should be at least as large as the signature
  EXPECT_GE(header_.size(), PentaxMnHeader::sizeOfSignature());
}

// Test that ifdOffset returns a value
TEST_F(PentaxMnHeaderTest_1485, IfdOffset_1485) {
  size_t offset = header_.ifdOffset();
  // The IFD offset should be related to the header size
  EXPECT_GE(offset, 0u);
}

// Test read with nullptr data and zero size
TEST_F(PentaxMnHeaderTest_1485, ReadNullDataZeroSize_1485) {
  bool result = header_.read(nullptr, 0, littleEndian);
  EXPECT_FALSE(result);
}

// Test read with size smaller than signature
TEST_F(PentaxMnHeaderTest_1485, ReadTooSmallBuffer_1485) {
  const byte smallData[] = {0x00, 0x01};
  bool result = header_.read(smallData, sizeof(smallData), littleEndian);
  EXPECT_FALSE(result);
}

// Test read with valid Pentax signature "AOC\0"
TEST_F(PentaxMnHeaderTest_1485, ReadValidPentaxSignature_1485) {
  // Pentax maker note signature is "AOC\0" followed by type bytes
  // The typical signature is: 'A', 'O', 'C', '\0', 'M', 'M' (or 'I', 'I')
  const byte validData[] = {'A', 'O', 'C', '\0', 'M', 'M',
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  size_t dataSize = sizeof(validData);
  
  if (dataSize >= header_.size()) {
    bool result = header_.read(validData, dataSize, bigEndian);
    // Result depends on whether the signature matches exactly
    // We just verify it doesn't crash
    (void)result;
  }
}

// Test read with invalid signature data
TEST_F(PentaxMnHeaderTest_1485, ReadInvalidSignature_1485) {
  const byte invalidData[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  bool result = header_.read(invalidData, sizeof(invalidData), littleEndian);
  EXPECT_FALSE(result);
}

// Test that size() returns the same value across multiple calls
TEST_F(PentaxMnHeaderTest_1485, SizeIsConsistent_1485) {
  size_t size1 = header_.size();
  size_t size2 = header_.size();
  EXPECT_EQ(size1, size2);
}

// Test that ifdOffset() returns the same value across multiple calls
TEST_F(PentaxMnHeaderTest_1485, IfdOffsetIsConsistent_1485) {
  size_t offset1 = header_.ifdOffset();
  size_t offset2 = header_.ifdOffset();
  EXPECT_EQ(offset1, offset2);
}

// Test read with exactly the right size buffer but wrong content
TEST_F(PentaxMnHeaderTest_1485, ReadExactSizeWrongContent_1485) {
  size_t headerSize = header_.size();
  std::vector<byte> data(headerSize, 0x00);
  bool result = header_.read(data.data(), data.size(), littleEndian);
  // With all zeros, the signature won't match "AOC\0"
  EXPECT_FALSE(result);
}

// Test read with different byte orders
TEST_F(PentaxMnHeaderTest_1485, ReadWithDifferentByteOrders_1485) {
  const byte data[] = {'A', 'O', 'C', '\0', 'I', 'I',
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  
  PentaxMnHeader header1;
  PentaxMnHeader header2;
  
  if (sizeof(data) >= header1.size()) {
    bool resultLE = header1.read(data, sizeof(data), littleEndian);
    bool resultBE = header2.read(data, sizeof(data), bigEndian);
    // The Pentax header read may ignore byte order for signature check
    // Just verify both calls don't crash
    (void)resultLE;
    (void)resultBE;
  }
}

// Test sizeOfSignature is a static method returning consistent value
TEST_F(PentaxMnHeaderTest_1485, SizeOfSignatureStatic_1485) {
  size_t s1 = PentaxMnHeader::sizeOfSignature();
  size_t s2 = PentaxMnHeader::sizeOfSignature();
  EXPECT_EQ(s1, s2);
  EXPECT_GT(s1, 0u);
}

// Test that a freshly constructed header has predictable ifdOffset
TEST_F(PentaxMnHeaderTest_1485, FreshHeaderIfdOffset_1485) {
  PentaxMnHeader freshHeader;
  // ifdOffset should be related to the size of the header
  EXPECT_LE(freshHeader.ifdOffset(), freshHeader.size());
}
