#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <cstring>

#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;

// A concrete Image subclass for testing, since Image is abstract
class TestImage : public Image {
 public:
  TestImage(std::unique_ptr<BasicIo> io)
      : Image(ImageType::none, 0, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
  std::string mimeType() const override { return "application/octet-stream"; }
};

// Helper to create a minimal valid IFD structure in memory
// Layout:
//   [start]: uint16 dirLength (number of entries)
//   For each entry (12 bytes):
//     uint16 tag
//     uint16 type
//     uint32 count
//     uint32 value/offset
//   After entries: uint32 next_ifd_offset (0 = no more)
static std::vector<byte> buildSimpleIFD(
    uint16_t numEntries,
    const std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>>& entries,
    uint32_t nextIfd = 0,
    bool bigEndian = false) {
  // We'll build in little-endian by default
  std::vector<byte> data;

  auto pushU16 = [&](uint16_t val) {
    if (bigEndian) {
      data.push_back(static_cast<byte>((val >> 8) & 0xFF));
      data.push_back(static_cast<byte>(val & 0xFF));
    } else {
      data.push_back(static_cast<byte>(val & 0xFF));
      data.push_back(static_cast<byte>((val >> 8) & 0xFF));
    }
  };

  auto pushU32 = [&](uint32_t val) {
    if (bigEndian) {
      data.push_back(static_cast<byte>((val >> 24) & 0xFF));
      data.push_back(static_cast<byte>((val >> 16) & 0xFF));
      data.push_back(static_cast<byte>((val >> 8) & 0xFF));
      data.push_back(static_cast<byte>(val & 0xFF));
    } else {
      data.push_back(static_cast<byte>(val & 0xFF));
      data.push_back(static_cast<byte>((val >> 8) & 0xFF));
      data.push_back(static_cast<byte>((val >> 16) & 0xFF));
      data.push_back(static_cast<byte>((val >> 24) & 0xFF));
    }
  };

  pushU16(numEntries);
  for (auto& [tag, type, count, offset] : entries) {
    pushU16(tag);
    pushU16(type);
    pushU32(count);
    pushU32(offset);
  }
  pushU32(nextIfd);

  return data;
}

class PrintIFDStructureTest_1065 : public ::testing::Test {
 protected:
  std::unique_ptr<TestImage> createTestImage(const byte* data, size_t size) {
    auto memIo = std::make_unique<MemIo>(data, size);
    return std::make_unique<TestImage>(std::move(memIo));
  }
};

// Test: Single IFD entry with unsignedShort type, kpsBasic option
TEST_F(PrintIFDStructureTest_1065, BasicPrintSingleShortEntry_1065) {
  // Build IFD with 1 entry: tag=0x0100 (ImageWidth), type=unsignedShort(3), count=1, value=640
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0100, unsignedShort, 1, 640}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  // Need a dummy Image to call printIFDStructure
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  // bSwap=false for little-endian, c='I' for Intel byte order, depth=1
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));

  std::string output = out.str();
  // Should contain "STRUCTURE OF TIFF FILE"
  EXPECT_NE(output.find("STRUCTURE OF TIFF FILE"), std::string::npos);
  // Should contain the tag 0x0100
  EXPECT_NE(output.find("0x0100"), std::string::npos);
  // Should contain END
  EXPECT_NE(output.find("END"), std::string::npos);
}

// Test: Single IFD entry with unsignedLong type
TEST_F(PrintIFDStructureTest_1065, BasicPrintSingleLongEntry_1065) {
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0101, unsignedLong, 1, 480}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("0x0101"), std::string::npos);
}

// Test: ASCII string entry (short, fits in 4 bytes)
TEST_F(PrintIFDStructureTest_1065, BasicPrintAsciiStringEntry_1065) {
  // tag=0x010e (ImageDescription), type=asciiString(2), count=4, value="Hi\0\0" packed in offset field
  uint32_t strValue = 0;
  std::memcpy(&strValue, "Hi\0\0", 4);
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x010e, asciiString, 4, strValue}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("0x010e"), std::string::npos);
}

// Test: Empty IFD (dirLength=0) should throw
TEST_F(PrintIFDStructureTest_1065, ZeroDirLengthThrows_1065) {
  // dirLength = 0
  std::vector<byte> data = {0x00, 0x00};

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1),
      Error);
}

// Test: dirLength > 500 should throw kerTiffDirectoryTooLarge
TEST_F(PrintIFDStructureTest_1065, TooLargeDirLengthThrows_1065) {
  // dirLength = 501 in little-endian
  std::vector<byte> data = {0xF5, 0x01};  // 501

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1),
      Error);
}

// Test: Invalid type in entry should throw
TEST_F(PrintIFDStructureTest_1065, InvalidTypeThrows_1065) {
  // type=0 is invalid
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0100, 0, 1, 100}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1),
      Error);
}

// Test: kpsNone option should not print structure header
TEST_F(PrintIFDStructureTest_1065, NoneOptionNoPrint_1065) {
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0100, unsignedShort, 1, 640}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsNone, 0, false, 'I', 1));

  std::string output = out.str();
  // Should NOT contain "STRUCTURE OF TIFF FILE" since option is kpsNone
  EXPECT_EQ(output.find("STRUCTURE OF TIFF FILE"), std::string::npos);
}

// Test: Multiple IFD entries
TEST_F(PrintIFDStructureTest_1065, MultipleEntries_1065) {
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0100, unsignedShort, 1, 640},
      {0x0101, unsignedShort, 1, 480},
      {0x0102, unsignedShort, 1, 8}
  };
  auto ifdData = buildSimpleIFD(3, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("0x0100"), std::string::npos);
  EXPECT_NE(output.find("0x0101"), std::string::npos);
  EXPECT_NE(output.find("0x0102"), std::string::npos);
}

// Test: Big-endian byte swap
TEST_F(PrintIFDStructureTest_1065, BigEndianSwap_1065) {
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0100, unsignedShort, 1, 640}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, true);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, true, 'M', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("STRUCTURE OF TIFF FILE"), std::string::npos);
  EXPECT_NE(output.find("0x0100"), std::string::npos);
}

// Test: Insufficient data for reading IFD entry should throw
TEST_F(PrintIFDStructureTest_1065, InsufficientDataForEntry_1065) {
  // Only 2 bytes for dirLength = 1, but no actual entry data
  std::vector<byte> data = {0x01, 0x00};

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1),
      Error);
}

// Test: Rational type entry
TEST_F(PrintIFDStructureTest_1065, RationalTypeEntry_1065) {
  // unsignedRational, count=1, data is 8 bytes so needs pointer
  // We need to place the rational data somewhere in the buffer
  // Build manually: dirLength=1, tag=0x011a, type=5(unsignedRational), count=1, offset=18 (points past dir)
  std::vector<byte> data;
  auto pushU16LE = [&](uint16_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
  };
  auto pushU32LE = [&](uint32_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
    data.push_back(static_cast<byte>((val >> 16) & 0xFF));
    data.push_back(static_cast<byte>((val >> 24) & 0xFF));
  };

  // dirLength = 1
  pushU16LE(1);
  // Entry: tag=0x011a, type=unsignedRational(5), count=1, offset=18
  pushU16LE(0x011a);
  pushU16LE(unsignedRational);
  pushU32LE(1);
  pushU32LE(18);  // offset to rational data
  // next IFD = 0
  pushU32LE(0);
  // Rational data at offset 18: numerator=72, denominator=1
  pushU32LE(72);
  pushU32LE(1);

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("0x011a"), std::string::npos);
  EXPECT_NE(output.find("72/1"), std::string::npos);
}

// Test: Count that causes allocation larger than io size should throw
TEST_F(PrintIFDStructureTest_1065, InvalidMallocThrows_1065) {
  // type=unsignedLong(4), count=very large -> allocate64 > io.size()
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0100, unsignedLong, 100000, 0}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1),
      Error);
}

// Test: Start offset beyond data should throw
TEST_F(PrintIFDStructureTest_1065, StartBeyondDataThrows_1065) {
  std::vector<byte> data = {0x01, 0x00, 0x00, 0x00};

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 1000, false, 'I', 1),
      Error);
}

// Test: Static helper methods - isStringType
TEST_F(PrintIFDStructureTest_1065, IsStringType_1065) {
  EXPECT_TRUE(Image::isStringType(asciiString));
  EXPECT_FALSE(Image::isStringType(unsignedShort));
  EXPECT_FALSE(Image::isStringType(unsignedLong));
}

// Test: Static helper methods - isShortType
TEST_F(PrintIFDStructureTest_1065, IsShortType_1065) {
  EXPECT_TRUE(Image::isShortType(unsignedShort));
  EXPECT_TRUE(Image::isShortType(signedShort));
  EXPECT_FALSE(Image::isShortType(unsignedLong));
}

// Test: Static helper methods - isLongType
TEST_F(PrintIFDStructureTest_1065, IsLongType_1065) {
  EXPECT_TRUE(Image::isLongType(unsignedLong));
  EXPECT_TRUE(Image::isLongType(signedLong));
  EXPECT_FALSE(Image::isLongType(unsignedShort));
}

// Test: Static helper methods - isRationalType
TEST_F(PrintIFDStructureTest_1065, IsRationalType_1065) {
  EXPECT_TRUE(Image::isRationalType(unsignedRational));
  EXPECT_TRUE(Image::isRationalType(signedRational));
  EXPECT_FALSE(Image::isRationalType(unsignedLong));
}

// Test: Static helper methods - is2ByteType
TEST_F(PrintIFDStructureTest_1065, Is2ByteType_1065) {
  EXPECT_TRUE(Image::is2ByteType(unsignedShort));
  EXPECT_TRUE(Image::is2ByteType(signedShort));
  EXPECT_FALSE(Image::is2ByteType(unsignedLong));
}

// Test: Static helper methods - is4ByteType
TEST_F(PrintIFDStructureTest_1065, Is4ByteType_1065) {
  EXPECT_TRUE(Image::is4ByteType(unsignedLong));
  EXPECT_TRUE(Image::is4ByteType(signedLong));
  EXPECT_TRUE(Image::is4ByteType(tiffFloat));
  EXPECT_FALSE(Image::is4ByteType(unsignedShort));
}

// Test: Static helper methods - is8ByteType
TEST_F(PrintIFDStructureTest_1065, Is8ByteType_1065) {
  EXPECT_TRUE(Image::is8ByteType(unsignedRational));
  EXPECT_TRUE(Image::is8ByteType(signedRational));
  EXPECT_TRUE(Image::is8ByteType(tiffDouble));
  EXPECT_FALSE(Image::is8ByteType(unsignedShort));
}

// Test: byteSwap with bSwap=false returns same value
TEST_F(PrintIFDStructureTest_1065, ByteSwapNoSwap_1065) {
  uint16_t val16 = 0x1234;
  EXPECT_EQ(Image::byteSwap(val16, false), val16);

  uint32_t val32 = 0x12345678;
  EXPECT_EQ(Image::byteSwap(val32, false), val32);

  uint64_t val64 = 0x123456789ABCDEF0ULL;
  EXPECT_EQ(Image::byteSwap(val64, false), val64);
}

// Test: byteSwap with bSwap=true reverses bytes
TEST_F(PrintIFDStructureTest_1065, ByteSwapWithSwap_1065) {
  uint16_t val16 = 0x1234;
  EXPECT_EQ(Image::byteSwap(val16, true), static_cast<uint16_t>(0x3412));

  uint32_t val32 = 0x12345678;
  EXPECT_EQ(Image::byteSwap(val32, true), static_cast<uint32_t>(0x78563412));
}

// Test: byteSwap2 and byteSwap4 from DataBuf
TEST_F(PrintIFDStructureTest_1065, ByteSwapFromBuf_1065) {
  byte data[] = {0x34, 0x12, 0x78, 0x56};
  DataBuf buf(data, 4);

  EXPECT_EQ(Image::byteSwap2(buf, 0, false), static_cast<uint16_t>(0x1234));
  EXPECT_EQ(Image::byteSwap4(buf, 0, false), static_cast<uint32_t>(0x56781234));
}

// Test: Endian platform detection (just ensuring they return bool and are complementary)
TEST_F(PrintIFDStructureTest_1065, EndianPlatformDetection_1065) {
  bool big = Image::isBigEndianPlatform();
  bool little = Image::isLittleEndianPlatform();
  // One must be true and the other false (on any standard platform)
  EXPECT_NE(big, little);
}

// Test: Chained IFDs (next IFD pointer)
TEST_F(PrintIFDStructureTest_1065, ChainedIFDs_1065) {
  // Build two IFDs: first at offset 0 points to second
  std::vector<byte> data;
  auto pushU16LE = [&](uint16_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
  };
  auto pushU32LE = [&](uint32_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
    data.push_back(static_cast<byte>((val >> 16) & 0xFF));
    data.push_back(static_cast<byte>((val >> 24) & 0xFF));
  };

  // First IFD at offset 0:
  // dirLength = 1
  pushU16LE(1);
  // Entry: tag=0x0100, type=unsignedShort(3), count=1, value=640
  pushU16LE(0x0100);
  pushU16LE(unsignedShort);
  pushU32LE(1);
  pushU32LE(640);
  // next IFD offset = 18 (start of second IFD)
  pushU32LE(18);

  // Second IFD at offset 18:
  // dirLength = 1
  pushU16LE(1);
  // Entry: tag=0x0101, type=unsignedShort(3), count=1, value=480
  pushU16LE(0x0101);
  pushU16LE(unsignedShort);
  pushU32LE(1);
  pushU32LE(480);
  // next IFD = 0
  pushU32LE(0);

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("0x0100"), std::string::npos);
  EXPECT_NE(output.find("0x0101"), std::string::npos);
}

// Test: Recursive option with ExifTag (0x8769)
TEST_F(PrintIFDStructureTest_1065, RecursiveExifTag_1065) {
  std::vector<byte> data;
  auto pushU16LE = [&](uint16_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
  };
  auto pushU32LE = [&](uint32_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
    data.push_back(static_cast<byte>((val >> 16) & 0xFF));
    data.push_back(static_cast<byte>((val >> 24) & 0xFF));
  };

  // Main IFD at offset 0:
  // dirLength = 1
  pushU16LE(1);
  // Entry: tag=0x8769 (ExifTag), type=unsignedLong(4), count=1, offset=18 (sub-IFD)
  pushU16LE(0x8769);
  pushU16LE(unsignedLong);
  pushU32LE(1);
  pushU32LE(18);  // points to sub-IFD
  // next IFD = 0
  pushU32LE(0);

  // Sub IFD at offset 18:
  // dirLength = 1
  pushU16LE(1);
  // Entry: tag=0x9000, type=unsignedShort(3), count=1, value=1
  pushU16LE(0x9000);
  pushU16LE(unsignedShort);
  pushU32LE(1);
  pushU32LE(1);
  // next IFD = 0
  pushU32LE(0);

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsRecursive, 0, false, 'I', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("0x8769"), std::string::npos);
  EXPECT_NE(output.find("0x9000"), std::string::npos);
}

// Test: Duplicate visit detection should throw (circular reference)
TEST_F(PrintIFDStructureTest_1065, CircularReferenceThrows_1065) {
  std::vector<byte> data;
  auto pushU16LE = [&](uint16_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
  };
  auto pushU32LE = [&](uint32_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
    data.push_back(static_cast<byte>((val >> 16) & 0xFF));
    data.push_back(static_cast<byte>((val >> 24) & 0xFF));
  };

  // Main IFD at offset 0: dirLength=1, ExifTag pointing to offset 0 (self)
  pushU16LE(1);
  pushU16LE(0x8769);
  pushU16LE(unsignedLong);
  pushU32LE(1);
  pushU32LE(0);  // points back to offset 0 - circular!
  pushU32LE(0);

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  // The recursive call will re-enter the same IFD, causing a duplicate visit
  EXPECT_THROW(
      img.printIFDStructure(memIo, out, kpsRecursive, 0, false, 'I', 1),
      Error);
}

// Test: dirLength exactly 500 should not throw (boundary)
TEST_F(PrintIFDStructureTest_1065, DirLength500Boundary_1065) {
  // We need at least 2 + 500*12 + 4 = 6006 bytes
  // This is a large buffer but tests the boundary
  std::vector<byte> data;
  auto pushU16LE = [&](uint16_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
  };
  auto pushU32LE = [&](uint32_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
    data.push_back(static_cast<byte>((val >> 16) & 0xFF));
    data.push_back(static_cast<byte>((val >> 24) & 0xFF));
  };

  pushU16LE(500);
  for (int i = 0; i < 500; i++) {
    pushU16LE(0x0100);       // tag
    pushU16LE(unsignedShort); // type
    pushU32LE(1);             // count
    pushU32LE(640);           // value
  }
  pushU32LE(0);  // no next IFD

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  // Should not throw for dirLength=500
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));
}

// Test: dirLength exactly 501 should throw (boundary)
TEST_F(PrintIFDStructureTest_1065, DirLength501ThrowsBoundary_1065) {
  std::vector<byte> data;
  auto pushU16LE = [&](uint16_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
  };

  pushU16LE(501);
  // Don't need actual entries since it should throw before reading them
  // But provide enough bytes to read the dirLength
  for (int i = 0; i < 501 * 12 + 4; i++) {
    data.push_back(0);
  }

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1),
      Error);
}

// Test: Long string entry with offset pointer
TEST_F(PrintIFDStructureTest_1065, LongStringWithOffset_1065) {
  std::vector<byte> data;
  auto pushU16LE = [&](uint16_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
  };
  auto pushU32LE = [&](uint32_t val) {
    data.push_back(static_cast<byte>(val & 0xFF));
    data.push_back(static_cast<byte>((val >> 8) & 0xFF));
    data.push_back(static_cast<byte>((val >> 16) & 0xFF));
    data.push_back(static_cast<byte>((val >> 24) & 0xFF));
  };

  // IFD at offset 0
  pushU16LE(1);
  // Entry: tag=0x010e, type=asciiString(2), count=10, offset=18
  pushU16LE(0x010e);
  pushU16LE(asciiString);
  pushU32LE(10);
  pushU32LE(18);  // points to string data
  // next IFD = 0
  pushU32LE(0);

  // String data at offset 18
  const char* str = "TestStr\0\0\0";
  for (int i = 0; i < 10; i++) {
    data.push_back(static_cast<byte>(str[i]));
  }

  MemIo memIo(data.data(), data.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("0x010e"), std::string::npos);
}

// Test: Verify output contains header line with column names
TEST_F(PrintIFDStructureTest_1065, OutputContainsHeaderColumns_1065) {
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0100, unsignedShort, 1, 640}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1);

  std::string output = out.str();
  EXPECT_NE(output.find("address"), std::string::npos);
  EXPECT_NE(output.find("tag"), std::string::npos);
  EXPECT_NE(output.find("type"), std::string::npos);
  EXPECT_NE(output.find("count"), std::string::npos);
  EXPECT_NE(output.find("offset"), std::string::npos);
  EXPECT_NE(output.find("value"), std::string::npos);
}

// Test: Multiple short values in single entry
TEST_F(PrintIFDStructureTest_1065, MultipleShortValues_1065) {
  // count=2 shorts fit in 4 bytes (offset field)
  // Two uint16 values: 100 and 200
  uint32_t packed = 100 | (200 << 16);
  std::vector<std::tuple<uint16_t, uint16_t, uint32_t, uint32_t>> entries = {
      {0x0102, unsignedShort, 2, packed}
  };
  auto ifdData = buildSimpleIFD(1, entries, 0, false);

  MemIo memIo(ifdData.data(), ifdData.size());
  auto dummyIo = std::make_unique<MemIo>();
  TestImage img(std::move(dummyIo));

  std::ostringstream out;
  EXPECT_NO_THROW(
      img.printIFDStructure(memIo, out, kpsBasic, 0, false, 'I', 1));

  std::string output = out.str();
  EXPECT_NE(output.find("100"), std::string::npos);
  EXPECT_NE(output.find("200"), std::string::npos);
}
