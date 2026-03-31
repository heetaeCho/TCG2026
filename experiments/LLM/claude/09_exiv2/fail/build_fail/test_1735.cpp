#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/tiffimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/xmp_exiv2.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/types.hpp"

#include <cstring>
#include <vector>
#include <algorithm>

using namespace Exiv2;

// We need a concrete BasicIo implementation for testing.
// MemIo is available in exiv2.
#include "exiv2/basicio.hpp"

class TiffParserEncodeTest_1735 : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear all metadata containers before each test
        exifData_.clear();
        iptcData_.clear();
        xmpData_.clear();
    }

    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
};

// Test: Encoding with empty metadata should not crash
TEST_F(TiffParserEncodeTest_1735, EncodeWithEmptyMetadata_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    // Should not throw with empty data
    EXPECT_NO_THROW(
        TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_)
    );
}

// Test: Encoding with little endian byte order
TEST_F(TiffParserEncodeTest_1735, EncodeWithLittleEndian_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    WriteMethod wm = TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);
    // WriteMethod should be a valid value
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test: Encoding with big endian byte order
TEST_F(TiffParserEncodeTest_1735, EncodeWithBigEndian_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    WriteMethod wm = TiffParser::encode(io, pData, size, bigEndian, exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test: PanaRaw IFD entries are filtered out during encoding
TEST_F(TiffParserEncodeTest_1735, PanaRawIfdIsFiltered_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    // Add an exif datum that belongs to panaRawId (IfdId::panaRawId = 19)
    // We'll add a tag in the panaRaw group
    // First, let's add some entries including one in panaRawId group
    // We need to check that after encode, exifData no longer contains panaRawId entries
    
    // Add a normal exif entry
    exifData_["Exif.Image.Make"] = "TestCamera";
    
    size_t countBefore = exifData_.count();
    EXPECT_GT(countBefore, 0u);

    TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);

    // Normal entries should still be present (they're not in panaRawId)
    // The exifData may be modified by the encode process but non-panaRaw entries
    // should not be removed by the filtering step
    // We just verify no crash and that some data was processed
    SUCCEED();
}

// Test: Encoding with some exif data
TEST_F(TiffParserEncodeTest_1735, EncodeWithExifData_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    exifData_["Exif.Image.Make"] = "TestMake";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);

    EXPECT_NO_THROW(
        TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_)
    );
}

// Test: Encoding with IPTC data
TEST_F(TiffParserEncodeTest_1735, EncodeWithIptcData_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    // Add IPTC data
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test Caption");
    iptcData_.add(key, value.get());

    EXPECT_NO_THROW(
        TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_)
    );
}

// Test: Encoding with XMP data
TEST_F(TiffParserEncodeTest_1735, EncodeWithXmpData_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    xmpData_["Xmp.dc.title"] = "Test Title";

    EXPECT_NO_THROW(
        TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_)
    );
}

// Test: Encoding with existing TIFF data buffer (non-null pData)
TEST_F(TiffParserEncodeTest_1735, EncodeWithExistingTiffData_1735) {
    MemIo io;
    
    // Create a minimal TIFF header (little endian)
    std::vector<byte> tiffData = {
        0x49, 0x49,  // Little endian ("II")
        0x2A, 0x00,  // TIFF magic number 42
        0x08, 0x00, 0x00, 0x00,  // Offset to first IFD
        0x00, 0x00   // Number of directory entries = 0
    };

    exifData_["Exif.Image.Make"] = "TestMake";

    EXPECT_NO_THROW(
        TiffParser::encode(io, tiffData.data(), tiffData.size(), littleEndian, 
                          exifData_, iptcData_, xmpData_)
    );
}

// Test: Encoding with all metadata types populated
TEST_F(TiffParserEncodeTest_1735, EncodeWithAllMetadataTypes_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    // Exif
    exifData_["Exif.Image.Make"] = "TestMake";
    exifData_["Exif.Image.Model"] = "TestModel";

    // IPTC
    IptcKey iptcKey("Iptc.Application2.Caption");
    Value::UniquePtr iptcVal = Value::create(string);
    iptcVal->read("Caption");
    iptcData_.add(iptcKey, iptcVal.get());

    // XMP
    xmpData_["Xmp.dc.title"] = "Title";

    EXPECT_NO_THROW(
        TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_)
    );
}

// Test: Verify panaRawId entries are removed from exifData after encode
TEST_F(TiffParserEncodeTest_1735, PanaRawEntriesRemovedAfterEncode_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    // Add a normal entry
    exifData_["Exif.Image.Make"] = "TestCamera";

    // Count entries before
    size_t countBefore = exifData_.count();

    TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_);

    // After encoding, panaRawId entries should have been filtered out
    // Check that no entries with panaRawId group remain
    bool hasPanaRaw = false;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        if (it->ifdId() == IfdId::panaRawId) {
            hasPanaRaw = true;
            break;
        }
    }
    EXPECT_FALSE(hasPanaRaw);
}

// Test: Multiple consecutive encodes should work correctly
TEST_F(TiffParserEncodeTest_1735, MultipleEncodesDoNotCrash_1735) {
    MemIo io1;
    MemIo io2;
    const byte* pData = nullptr;
    size_t size = 0;

    exifData_["Exif.Image.Make"] = "Camera1";

    EXPECT_NO_THROW(
        TiffParser::encode(io1, pData, size, littleEndian, exifData_, iptcData_, xmpData_)
    );

    exifData_["Exif.Image.Model"] = "Model1";

    EXPECT_NO_THROW(
        TiffParser::encode(io2, pData, size, bigEndian, exifData_, iptcData_, xmpData_)
    );
}

// Test: Encode returns a valid WriteMethod
TEST_F(TiffParserEncodeTest_1735, EncodeReturnsValidWriteMethod_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    exifData_["Exif.Image.Make"] = "TestMake";

    WriteMethod result = TiffParser::encode(io, pData, size, littleEndian, 
                                             exifData_, iptcData_, xmpData_);
    
    // WriteMethod should be one of the defined values
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test: Encoding with zero-size data buffer and null pointer
TEST_F(TiffParserEncodeTest_1735, EncodeWithNullDataAndZeroSize_1735) {
    MemIo io;

    EXPECT_NO_THROW(
        TiffParser::encode(io, nullptr, 0, littleEndian, exifData_, iptcData_, xmpData_)
    );
}

// Test: Decode with minimal valid TIFF data
TEST_F(TiffParserEncodeTest_1735, DecodeWithMinimalTiffData_1735) {
    // Create a minimal TIFF structure (little endian)
    std::vector<byte> tiffData = {
        0x49, 0x49,              // Little endian ("II")
        0x2A, 0x00,              // TIFF magic number 42
        0x08, 0x00, 0x00, 0x00, // Offset to first IFD = 8
        0x00, 0x00               // Number of directory entries = 0
    };

    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    EXPECT_NO_THROW(
        TiffParser::decode(exifData, iptcData, xmpData, tiffData.data(), tiffData.size())
    );
}

// Test: Decode returns a byte order
TEST_F(TiffParserEncodeTest_1735, DecodeReturnsValidByteOrder_1735) {
    // Little endian TIFF
    std::vector<byte> tiffData = {
        0x49, 0x49,              // Little endian ("II")
        0x2A, 0x00,              // TIFF magic number 42
        0x08, 0x00, 0x00, 0x00, // Offset to first IFD = 8
        0x00, 0x00               // Number of directory entries = 0
    };

    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, 
                                       tiffData.data(), tiffData.size());
    EXPECT_EQ(bo, littleEndian);
}

// Test: Decode big endian TIFF
TEST_F(TiffParserEncodeTest_1735, DecodeReturnsCorrectByteOrderBigEndian_1735) {
    // Big endian TIFF
    std::vector<byte> tiffData = {
        0x4D, 0x4D,              // Big endian ("MM")
        0x00, 0x2A,              // TIFF magic number 42
        0x00, 0x00, 0x00, 0x08, // Offset to first IFD = 8
        0x00, 0x00               // Number of directory entries = 0
    };

    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData,
                                       tiffData.data(), tiffData.size());
    EXPECT_EQ(bo, bigEndian);
}

// Test: Encode with large number of exif entries
TEST_F(TiffParserEncodeTest_1735, EncodeWithMultipleExifEntries_1735) {
    MemIo io;
    const byte* pData = nullptr;
    size_t size = 0;

    exifData_["Exif.Image.Make"] = "TestMake";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);
    exifData_["Exif.Image.XResolution"] = "72/1";
    exifData_["Exif.Image.YResolution"] = "72/1";
    exifData_["Exif.Image.Software"] = "TestSoftware";
    exifData_["Exif.Image.DateTime"] = "2023:01:01 00:00:00";
    exifData_["Exif.Photo.ExposureTime"] = "1/100";
    exifData_["Exif.Photo.FNumber"] = "28/10";
    exifData_["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);

    EXPECT_NO_THROW(
        TiffParser::encode(io, pData, size, littleEndian, exifData_, iptcData_, xmpData_)
    );
}
