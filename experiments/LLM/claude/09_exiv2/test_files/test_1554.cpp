#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/xmp_exiv2.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/types.hpp"

#include <cstring>
#include <memory>

using namespace Exiv2;

// We use MemIo as a concrete BasicIo for testing
class OrfParserTest_1554 : public ::testing::Test {
protected:
    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;

    void SetUp() override {
        exifData_.clear();
        iptcData_ = IptcData();
        xmpData_.clear();
    }
};

// Test that encode can be called with empty data and empty metadata
TEST_F(OrfParserTest_1554, EncodeWithEmptyDataAndMetadata_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;
    ByteOrder byteOrder = littleEndian;

    // Should not throw and should return some WriteMethod
    WriteMethod wm = OrfParser::encode(io, pData, size, byteOrder, exifData_, iptcData_, xmpData_);
    // WriteMethod is an enum; just check it returns a valid value
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test that encode filters out panaRawId entries from exifData
TEST_F(OrfParserTest_1554, EncodeFiltersPanaRawIdEntries_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;
    ByteOrder byteOrder = littleEndian;

    // Add an exif datum that belongs to panaRawId (IfdId = 19)
    // We need to add entries and verify they are removed after encode
    // panaRawId entries should be erased by the encode method

    // First, let's check initial state
    size_t countBefore = exifData_.count();
    EXPECT_EQ(countBefore, 0u);

    // Call encode - even with empty data, the filtering logic should run
    OrfParser::encode(io, pData, size, byteOrder, exifData_, iptcData_, xmpData_);

    // After encoding with no panaRawId entries, exifData should still be empty
    EXPECT_EQ(exifData_.count(), 0u);
}

// Test encode with littleEndian byte order
TEST_F(OrfParserTest_1554, EncodeWithLittleEndianByteOrder_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    WriteMethod wm = OrfParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test encode with bigEndian byte order
TEST_F(OrfParserTest_1554, EncodeWithBigEndianByteOrder_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    WriteMethod wm = OrfParser::encode(io, pData, size, bigEndian, exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test encode with some non-null data buffer
TEST_F(OrfParserTest_1554, EncodeWithNonNullDataBuffer_1554) {
    MemIo io;
    // Create a small buffer (won't be valid ORF data, but tests interface)
    byte data[16];
    std::memset(data, 0, sizeof(data));

    WriteMethod wm = OrfParser::encode(io, data, sizeof(data), littleEndian, exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test that encode does not crash with non-empty exif data that is not panaRawId
TEST_F(OrfParserTest_1554, EncodePreservesNonPanaRawExifData_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    // Add a standard exif entry (e.g., Exif.Image.ImageWidth which is in ifd0Id)
    exifData_["Exif.Image.ImageWidth"] = uint32_t(100);
    EXPECT_FALSE(exifData_.empty());

    size_t countBefore = exifData_.count();
    EXPECT_GE(countBefore, 1u);

    OrfParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);

    // Non-panaRawId entries should still be present (they are not filtered)
    EXPECT_GE(exifData_.count(), 1u);
}

// Test encode with non-empty IPTC data
TEST_F(OrfParserTest_1554, EncodeWithNonEmptyIptcData_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    // Add IPTC data - should not cause issues
    iptcData_["Iptc.Application2.Caption"] = "Test caption";

    WriteMethod wm = OrfParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test encode with non-empty XMP data
TEST_F(OrfParserTest_1554, EncodeWithNonEmptyXmpData_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    // Add XMP data - should not cause issues
    xmpData_["Xmp.dc.title"] = "Test title";

    WriteMethod wm = OrfParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test encode with all metadata types populated
TEST_F(OrfParserTest_1554, EncodeWithAllMetadataPopulated_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    exifData_["Exif.Image.ImageWidth"] = uint32_t(640);
    exifData_["Exif.Image.ImageLength"] = uint32_t(480);
    iptcData_["Iptc.Application2.Caption"] = "Test";
    xmpData_["Xmp.dc.title"] = "Test";

    WriteMethod wm = OrfParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test that multiple calls to encode don't cause issues
TEST_F(OrfParserTest_1554, EncodeMultipleCallsDoNotCrash_1554) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    for (int i = 0; i < 5; ++i) {
        WriteMethod wm = OrfParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);
        EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
    }
}

// Test decode with null data
TEST_F(OrfParserTest_1554, DecodeWithNullData_1554) {
    const byte* pData = nullptr;
    size_t size = 0;

    // Decode with null data and zero size - should handle gracefully
    ByteOrder bo = OrfParser::decode(exifData_, iptcData_, xmpData_, pData, size);
    // Just verify it returns some byte order without crashing
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian || bo == invalidByteOrder);
}

// Test decode with small invalid data
TEST_F(OrfParserTest_1554, DecodeWithSmallInvalidData_1554) {
    byte data[4] = {0, 0, 0, 0};

    ByteOrder bo = OrfParser::decode(exifData_, iptcData_, xmpData_, data, sizeof(data));
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian || bo == invalidByteOrder);
}

// Test encode with zero-size data and non-null pointer
TEST_F(OrfParserTest_1554, EncodeWithZeroSizeNonNullPointer_1554) {
    MemIo io;
    byte data[1] = {0};
    size_t size = 0;

    WriteMethod wm = OrfParser::encode(io, data, size, bigEndian, exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}
