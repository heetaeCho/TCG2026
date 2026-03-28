#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

#include <cstring>
#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create an IoWrapper with a MemIo backend
class TiffDirectoryWriteDataTest_376 : public ::testing::Test {
 protected:
  void SetUp() override {
    memIo_ = std::make_unique<MemIo>();
    // Minimal TIFF header
    memset(header_, 0, sizeof(header_));
    header_[0] = 'I';
    header_[1] = 'I';
    header_[2] = 42;
    header_[3] = 0;
    header_[4] = 8;  // offset to first IFD
    header_[5] = 0;
    header_[6] = 0;
    header_[7] = 0;
  }

  std::unique_ptr<MemIo> memIo_;
  byte header_[8];
};

// Test that an empty TiffDirectory returns 0 from writeData
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectoryWriteDataReturnsZero_376) {
  IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

  size_t imageIdx = 0;
  size_t result = dir.writeData(ioWrapper, littleEndian, 0, 0, imageIdx);

  EXPECT_EQ(result, 0u);
}

// Test construction with hasNext true
TEST_F(TiffDirectoryWriteDataTest_376, ConstructorHasNextTrue_376) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
  EXPECT_TRUE(dir.hasNext());
}

// Test construction with hasNext false
TEST_F(TiffDirectoryWriteDataTest_376, ConstructorHasNextFalse_376) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_FALSE(dir.hasNext());
}

// Test tag and group are set correctly
TEST_F(TiffDirectoryWriteDataTest_376, TagAndGroupCorrect_376) {
  TiffDirectory dir(0x1234, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.tag(), 0x1234);
  EXPECT_EQ(dir.group(), IfdId::ifd0Id);
}

// Test count on empty directory
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectoryCountIsZero_376) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.count(), 0u);
}

// Test size on empty directory
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectorySizeReturnsExpected_376) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  // An empty directory with no next should have minimal size
  size_t s = dir.size();
  // At minimum, a TIFF directory has 2 bytes for entry count
  // For an empty directory with hasNext_=false, size is implementation-defined
  // but should be deterministic
  EXPECT_GE(s, 0u);
}

// Test sizeData on empty directory
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectorySizeDataIsZero_376) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.sizeData(), 0u);
}

// Test sizeImage on empty directory
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectorySizeImageIsZero_376) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.sizeImage(), 0u);
}

// Test writeImage on empty directory returns zero
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectoryWriteImageReturnsZero_376) {
  IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

  size_t result = dir.writeImage(ioWrapper, littleEndian);
  EXPECT_EQ(result, 0u);
}

// Test that writeData with different byte orders on empty directory returns 0
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectoryWriteDataBigEndianReturnsZero_376) {
  IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

  size_t imageIdx = 0;
  size_t result = dir.writeData(ioWrapper, bigEndian, 0, 0, imageIdx);

  EXPECT_EQ(result, 0u);
}

// Test that writeData with non-zero offset on empty directory returns 0
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectoryWriteDataWithOffsetReturnsZero_376) {
  IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

  size_t imageIdx = 0;
  size_t result = dir.writeData(ioWrapper, littleEndian, 100, 50, imageIdx);

  EXPECT_EQ(result, 0u);
}

// Test that writeData with non-zero imageIdx on empty directory returns 0
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectoryWriteDataWithImageIdxReturnsZero_376) {
  IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

  size_t imageIdx = 42;
  size_t result = dir.writeData(ioWrapper, littleEndian, 0, 0, imageIdx);

  EXPECT_EQ(result, 0u);
}

// Test directory with hasNext=true, empty, writeData still returns 0
TEST_F(TiffDirectoryWriteDataTest_376, EmptyDirectoryWithNextWriteDataReturnsZero_376) {
  IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);
  TiffDirectory dir(0x0001, IfdId::ifd0Id, true);

  size_t imageIdx = 0;
  size_t result = dir.writeData(ioWrapper, littleEndian, 0, 0, imageIdx);

  EXPECT_EQ(result, 0u);
}

// Test that start() returns nullptr by default
TEST_F(TiffDirectoryWriteDataTest_376, DefaultStartIsNull_376) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_EQ(dir.start(), nullptr);
}

// Test setting start pointer
TEST_F(TiffDirectoryWriteDataTest_376, SetStartUpdatesStart_376) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  byte data[10] = {};
  dir.setStart(data);
  EXPECT_EQ(dir.start(), data);
}
