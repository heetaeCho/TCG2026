#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"
#include "basicio.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::AtLeast;

// Test fixture for Nikon3MnHeader
class Nikon3MnHeaderTest_1471 : public ::testing::Test {
 protected:
  void SetUp() override {
    header_ = std::make_unique<Nikon3MnHeader>();
  }

  std::unique_ptr<Nikon3MnHeader> header_;
};

// Test default construction - size should equal sizeOfSignature + TiffHeader size
TEST_F(Nikon3MnHeaderTest_1471, DefaultConstruction_1471) {
  EXPECT_GT(header_->size(), 0u);
}

// Test sizeOfSignature is consistent
TEST_F(Nikon3MnHeaderTest_1471, SizeOfSignature_1471) {
  size_t sigSize = Nikon3MnHeader::sizeOfSignature();
  EXPECT_GT(sigSize, 0u);
}

// Test size() returns expected value
TEST_F(Nikon3MnHeaderTest_1471, SizeReturnsExpectedValue_1471) {
  // The size should be the signature size plus the TIFF header size (8 bytes)
  size_t expectedSize = Nikon3MnHeader::sizeOfSignature() + 8;
  EXPECT_EQ(header_->size(), expectedSize);
}

// Test ifdOffset returns expected value
TEST_F(Nikon3MnHeaderTest_1471, IfdOffsetReturnsExpectedValue_1471) {
  size_t offset = header_->ifdOffset();
  // ifdOffset should be at least the signature size
  EXPECT_GE(offset, Nikon3MnHeader::sizeOfSignature());
}

// Test byteOrder returns a valid byte order after default construction
TEST_F(Nikon3MnHeaderTest_1471, DefaultByteOrder_1471) {
  ByteOrder bo = header_->byteOrder();
  // Should be one of the valid byte orders
  EXPECT_TRUE(bo == littleEndian || bo == bigEndian || bo == invalidByteOrder);
}

// Test setByteOrder changes the byte order
TEST_F(Nikon3MnHeaderTest_1471, SetByteOrderLittleEndian_1471) {
  header_->setByteOrder(littleEndian);
  EXPECT_EQ(header_->byteOrder(), littleEndian);
}

TEST_F(Nikon3MnHeaderTest_1471, SetByteOrderBigEndian_1471) {
  header_->setByteOrder(bigEndian);
  EXPECT_EQ(header_->byteOrder(), bigEndian);
}

// Test baseOffset
TEST_F(Nikon3MnHeaderTest_1471, BaseOffsetWithZeroMnOffset_1471) {
  size_t baseOff = header_->baseOffset(0);
  EXPECT_EQ(baseOff, 0u);
}

TEST_F(Nikon3MnHeaderTest_1471, BaseOffsetWithNonZeroMnOffset_1471) {
  size_t mnOffset = 100;
  size_t baseOff = header_->baseOffset(mnOffset);
  // baseOffset should return mnOffset + start_ (which is sizeOfSignature)
  EXPECT_EQ(baseOff, mnOffset + Nikon3MnHeader::sizeOfSignature());
}

// Test read with valid Nikon3 makernote signature
TEST_F(Nikon3MnHeaderTest_1471, ReadValidSignature_1471) {
  // Nikon3 signature: "Nikon\0\2\x10\0\0" (10 bytes) followed by TIFF header
  // The signature is "Nikon\0" + version bytes
  const byte nikon3Sig[] = {
    'N', 'i', 'k', 'o', 'n', '\0', 0x02, 0x10, 0x00, 0x00,  // 10 bytes signature
    'M', 'M',  // Big endian marker
    0x00, 0x2a, // TIFF magic 42
    0x00, 0x00, 0x00, 0x08  // Offset
  };
  
  bool result = header_->read(nikon3Sig, sizeof(nikon3Sig), bigEndian);
  EXPECT_TRUE(result);
}

// Test read with too small data
TEST_F(Nikon3MnHeaderTest_1471, ReadTooSmallData_1471) {
  const byte smallData[] = {'N', 'i', 'k'};
  bool result = header_->read(smallData, sizeof(smallData), bigEndian);
  EXPECT_FALSE(result);
}

// Test read with invalid signature
TEST_F(Nikon3MnHeaderTest_1471, ReadInvalidSignature_1471) {
  const byte invalidSig[] = {
    'C', 'a', 'n', 'o', 'n', '\0', 0x02, 0x10, 0x00, 0x00,
    'M', 'M',
    0x00, 0x2a,
    0x00, 0x00, 0x00, 0x08
  };
  bool result = header_->read(invalidSig, sizeof(invalidSig), bigEndian);
  EXPECT_FALSE(result);
}

// Test read with exact minimum size
TEST_F(Nikon3MnHeaderTest_1471, ReadExactMinimumSize_1471) {
  size_t sigSize = Nikon3MnHeader::sizeOfSignature();
  // Data that is exactly the signature size but no TIFF header
  std::vector<byte> data(sigSize, 0);
  data[0] = 'N'; data[1] = 'i'; data[2] = 'k'; data[3] = 'o'; data[4] = 'n';
  data[5] = '\0'; data[6] = 0x02; data[7] = 0x10; data[8] = 0x00; data[9] = 0x00;
  
  bool result = header_->read(data.data(), data.size(), bigEndian);
  // Should fail because there's no TIFF header data after signature
  EXPECT_FALSE(result);
}

// Test write method with little endian
TEST_F(Nikon3MnHeaderTest_1471, WriteLittleEndian_1471) {
  MemIo memIo;
  byte headerData[] = {0};
  IoWrapper ioWrapper(memIo, headerData, 0, nullptr);
  
  size_t bytesWritten = header_->write(ioWrapper, littleEndian);
  // Should write 10 bytes of signature + 8 bytes of TiffHeader = 18 bytes
  EXPECT_EQ(bytesWritten, 10u + 8u);
}

// Test write method with big endian
TEST_F(Nikon3MnHeaderTest_1471, WriteBigEndian_1471) {
  MemIo memIo;
  byte headerData[] = {0};
  IoWrapper ioWrapper(memIo, headerData, 0, nullptr);
  
  size_t bytesWritten = header_->write(ioWrapper, bigEndian);
  EXPECT_EQ(bytesWritten, 10u + 8u);
}

// Test that read followed by byteOrder reflects the data's byte order
TEST_F(Nikon3MnHeaderTest_1471, ReadSetsCorrectByteOrderBigEndian_1471) {
  const byte nikon3Sig[] = {
    'N', 'i', 'k', 'o', 'n', '\0', 0x02, 0x10, 0x00, 0x00,
    'M', 'M',  // Big endian
    0x00, 0x2a,
    0x00, 0x00, 0x00, 0x08
  };
  
  bool result = header_->read(nikon3Sig, sizeof(nikon3Sig), bigEndian);
  if (result) {
    EXPECT_EQ(header_->byteOrder(), bigEndian);
  }
}

// Test that read followed by byteOrder reflects little endian
TEST_F(Nikon3MnHeaderTest_1471, ReadSetsCorrectByteOrderLittleEndian_1471) {
  const byte nikon3Sig[] = {
    'N', 'i', 'k', 'o', 'n', '\0', 0x02, 0x10, 0x00, 0x00,
    'I', 'I',  // Little endian
    0x2a, 0x00,
    0x08, 0x00, 0x00, 0x00
  };
  
  bool result = header_->read(nikon3Sig, sizeof(nikon3Sig), littleEndian);
  if (result) {
    EXPECT_EQ(header_->byteOrder(), littleEndian);
  }
}

// Test read with zero size
TEST_F(Nikon3MnHeaderTest_1471, ReadZeroSize_1471) {
  const byte data[] = {0};
  bool result = header_->read(data, 0, bigEndian);
  EXPECT_FALSE(result);
}

// Test that multiple setByteOrder calls work
TEST_F(Nikon3MnHeaderTest_1471, MultipleSetByteOrder_1471) {
  header_->setByteOrder(littleEndian);
  EXPECT_EQ(header_->byteOrder(), littleEndian);
  
  header_->setByteOrder(bigEndian);
  EXPECT_EQ(header_->byteOrder(), bigEndian);
  
  header_->setByteOrder(littleEndian);
  EXPECT_EQ(header_->byteOrder(), littleEndian);
}

// Test baseOffset with large mnOffset
TEST_F(Nikon3MnHeaderTest_1471, BaseOffsetLargeMnOffset_1471) {
  size_t largeMnOffset = 1000000;
  size_t baseOff = header_->baseOffset(largeMnOffset);
  EXPECT_EQ(baseOff, largeMnOffset + Nikon3MnHeader::sizeOfSignature());
}

// Test that sizeOfSignature is 10 (known from the write method which writes buf_ with 10 bytes)
TEST_F(Nikon3MnHeaderTest_1471, SizeOfSignatureIsTen_1471) {
  EXPECT_EQ(Nikon3MnHeader::sizeOfSignature(), 10u);
}

// Test write produces consistent output for same byte order
TEST_F(Nikon3MnHeaderTest_1471, WriteConsistentOutput_1471) {
  MemIo memIo1;
  byte headerData1[] = {0};
  IoWrapper ioWrapper1(memIo1, headerData1, 0, nullptr);
  size_t bytesWritten1 = header_->write(ioWrapper1, littleEndian);

  Nikon3MnHeader header2;
  MemIo memIo2;
  byte headerData2[] = {0};
  IoWrapper ioWrapper2(memIo2, headerData2, 0, nullptr);
  size_t bytesWritten2 = header2.write(ioWrapper2, littleEndian);

  EXPECT_EQ(bytesWritten1, bytesWritten2);
}

// Test ifdOffset relationship with size
TEST_F(Nikon3MnHeaderTest_1471, IfdOffsetLessThanOrEqualToSize_1471) {
  EXPECT_LE(header_->ifdOffset(), header_->size());
}
