#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <vector>
#include <cstring>

namespace {

class ExifParserTest_784 : public ::testing::Test {
 protected:
  void SetUp() override {
    exifData_.clear();
  }

  void TearDown() override {
    exifData_.clear();
  }

  Exiv2::ExifData exifData_;
};

// Test decoding with null pointer and zero size
TEST_F(ExifParserTest_784, DecodeNullDataReturnsInvalidByteOrder_784) {
  // Passing nullptr with size 0 should not crash and should return some byte order
  // (likely invalidByteOrder since there's no valid TIFF data)
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, nullptr, 0);
  EXPECT_EQ(bo, Exiv2::invalidByteOrder);
  EXPECT_TRUE(exifData_.empty());
}

// Test decoding with empty data (zero size but non-null pointer)
TEST_F(ExifParserTest_784, DecodeEmptyDataReturnsInvalidByteOrder_784) {
  const Exiv2::byte data[] = {0};
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, data, 0);
  EXPECT_EQ(bo, Exiv2::invalidByteOrder);
  EXPECT_TRUE(exifData_.empty());
}

// Test decoding with garbage/invalid data
TEST_F(ExifParserTest_784, DecodeGarbageDataReturnsInvalidByteOrder_784) {
  const Exiv2::byte garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, garbage, sizeof(garbage));
  EXPECT_EQ(bo, Exiv2::invalidByteOrder);
}

// Test decoding with data too small to be valid TIFF
TEST_F(ExifParserTest_784, DecodeTooSmallDataReturnsInvalidByteOrder_784) {
  const Exiv2::byte smallData[] = {0x49, 0x49};  // Just "II" - too small for TIFF
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, smallData, sizeof(smallData));
  EXPECT_EQ(bo, Exiv2::invalidByteOrder);
}

// Test decoding with a minimal valid TIFF header (Little Endian)
TEST_F(ExifParserTest_784, DecodeMinimalLittleEndianTiff_784) {
  // Minimal TIFF: "II" + 0x002A (42) + offset to IFD0 (8) + IFD with 0 entries + next IFD offset 0
  const Exiv2::byte tiffLE[] = {
    0x49, 0x49,       // "II" - little endian
    0x2A, 0x00,       // TIFF magic number 42
    0x08, 0x00, 0x00, 0x00,  // Offset to IFD0 = 8
    0x00, 0x00,       // Number of IFD entries = 0
    0x00, 0x00, 0x00, 0x00   // Next IFD offset = 0
  };
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, tiffLE, sizeof(tiffLE));
  EXPECT_EQ(bo, Exiv2::littleEndian);
}

// Test decoding with a minimal valid TIFF header (Big Endian)
TEST_F(ExifParserTest_784, DecodeMinimalBigEndianTiff_784) {
  // Minimal TIFF: "MM" + 0x002A (42) + offset to IFD0 (8) + IFD with 0 entries + next IFD offset 0
  const Exiv2::byte tiffBE[] = {
    0x4D, 0x4D,       // "MM" - big endian
    0x00, 0x2A,       // TIFF magic number 42
    0x00, 0x00, 0x00, 0x08,  // Offset to IFD0 = 8
    0x00, 0x00,       // Number of IFD entries = 0
    0x00, 0x00, 0x00, 0x00   // Next IFD offset = 0
  };
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, tiffBE, sizeof(tiffBE));
  EXPECT_EQ(bo, Exiv2::bigEndian);
}

// Test that ExifData is cleared/populated after decode with valid TIFF containing an entry
TEST_F(ExifParserTest_784, DecodeValidTiffPopulatesExifData_784) {
  // Build a minimal TIFF with one IFD entry (ImageWidth = 100)
  // Little endian
  std::vector<Exiv2::byte> tiff;

  // Header
  tiff.push_back(0x49); tiff.push_back(0x49); // "II"
  tiff.push_back(0x2A); tiff.push_back(0x00); // Magic 42
  tiff.push_back(0x08); tiff.push_back(0x00); tiff.push_back(0x00); tiff.push_back(0x00); // IFD offset = 8

  // IFD0
  tiff.push_back(0x01); tiff.push_back(0x00); // 1 entry

  // Entry: Tag=0x0100 (ImageWidth), Type=3 (SHORT), Count=1, Value=100
  tiff.push_back(0x00); tiff.push_back(0x01); // Tag 0x0100
  tiff.push_back(0x03); tiff.push_back(0x00); // Type SHORT
  tiff.push_back(0x01); tiff.push_back(0x00); tiff.push_back(0x00); tiff.push_back(0x00); // Count = 1
  tiff.push_back(0x64); tiff.push_back(0x00); tiff.push_back(0x00); tiff.push_back(0x00); // Value = 100

  // Next IFD offset = 0
  tiff.push_back(0x00); tiff.push_back(0x00); tiff.push_back(0x00); tiff.push_back(0x00);

  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, tiff.data(), tiff.size());
  EXPECT_EQ(bo, Exiv2::littleEndian);
  // Should have at least one entry
  EXPECT_FALSE(exifData_.empty());
}

// Test decoding with wrong magic number
TEST_F(ExifParserTest_784, DecodeWrongMagicNumberReturnsInvalid_784) {
  const Exiv2::byte badMagic[] = {
    0x49, 0x49,       // "II"
    0x00, 0x00,       // Wrong magic (should be 0x002A)
    0x08, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, badMagic, sizeof(badMagic));
  EXPECT_EQ(bo, Exiv2::invalidByteOrder);
}

// Test that decode does not crash with truncated TIFF header
TEST_F(ExifParserTest_784, DecodeTruncatedTiffHeader_784) {
  // Valid start but truncated before IFD offset is complete
  const Exiv2::byte truncated[] = {
    0x49, 0x49,       // "II"
    0x2A, 0x00,       // Magic 42
    0x08, 0x00        // Truncated offset
  };
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, truncated, sizeof(truncated));
  // The result could be invalidByteOrder or littleEndian depending on implementation
  // but it should not crash
  (void)bo;
}

// Test ExifData operations used alongside decode
TEST_F(ExifParserTest_784, ExifDataClearAfterDecode_784) {
  // Minimal valid TIFF
  const Exiv2::byte tiffLE[] = {
    0x49, 0x49,
    0x2A, 0x00,
    0x08, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  Exiv2::ExifParser::decode(exifData_, tiffLE, sizeof(tiffLE));
  exifData_.clear();
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
}

// Test encode with empty ExifData produces some output (or empty blob)
TEST_F(ExifParserTest_784, EncodeEmptyExifData_784) {
  Exiv2::Blob blob;
  Exiv2::ExifParser::encode(blob, Exiv2::bigEndian, exifData_);
  // With empty exif data, the blob might be empty or contain minimal header
  // Just verify no crash
  SUCCEED();
}

// Test encode with pData overload
TEST_F(ExifParserTest_784, EncodeWithOriginalData_784) {
  // Minimal valid TIFF
  const Exiv2::byte tiffLE[] = {
    0x49, 0x49,
    0x2A, 0x00,
    0x08, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };

  Exiv2::ExifParser::decode(exifData_, tiffLE, sizeof(tiffLE));

  Exiv2::Blob blob;
  Exiv2::WriteMethod wm = Exiv2::ExifParser::encode(blob, tiffLE, sizeof(tiffLE),
                                                      Exiv2::littleEndian, exifData_);
  // Just verify it returns a valid WriteMethod and doesn't crash
  EXPECT_TRUE(wm == Exiv2::wmIntrusive || wm == Exiv2::wmNonIntrusive);
}

// Test decoding twice into the same ExifData object
TEST_F(ExifParserTest_784, DecodeCalledTwice_784) {
  const Exiv2::byte tiffLE[] = {
    0x49, 0x49,
    0x2A, 0x00,
    0x08, 0x00, 0x00, 0x00,
    0x01, 0x00,
    0x00, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };

  Exiv2::ByteOrder bo1 = Exiv2::ExifParser::decode(exifData_, tiffLE, sizeof(tiffLE));
  size_t count1 = exifData_.count();

  // Decode again - should not crash
  Exiv2::ByteOrder bo2 = Exiv2::ExifParser::decode(exifData_, tiffLE, sizeof(tiffLE));
  EXPECT_EQ(bo1, bo2);
  // Count might have doubled or been replaced depending on implementation
  (void)count1;
}

// Test with only the byte order marker and nothing else valid
TEST_F(ExifParserTest_784, DecodeOnlyByteOrderMarker_784) {
  const Exiv2::byte data[] = {0x4D, 0x4D}; // "MM" only
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, data, sizeof(data));
  EXPECT_EQ(bo, Exiv2::invalidByteOrder);
}

// Test ExifData basic operations independent of parser
TEST_F(ExifParserTest_784, ExifDataEmptyInitially_784) {
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
  EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test large invalid data doesn't cause issues
TEST_F(ExifParserTest_784, DecodeLargeInvalidData_784) {
  std::vector<Exiv2::byte> largeData(10000, 0xFF);
  Exiv2::ByteOrder bo = Exiv2::ExifParser::decode(exifData_, largeData.data(), largeData.size());
  EXPECT_EQ(bo, Exiv2::invalidByteOrder);
}

}  // namespace
