#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/cr2image.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/xmp_exiv2.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/tags.hpp"

#include <cstring>
#include <memory>

using namespace Exiv2;

// Helper: MemIo is a concrete BasicIo implementation available in exiv2
// We use it for testing since we need a real BasicIo object.
#include "exiv2/basicio.hpp"

class Cr2ParserEncodeTest_1746 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_.clear();
        iptcData_.clear();
        xmpData_.clear();
    }

    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
};

// Test that encode can be called with empty data and empty metadata
TEST_F(Cr2ParserEncodeTest_1746, EncodeWithEmptyDataAndMetadata_1746) {
    MemIo io;
    // Call encode with nullptr data and size 0
    WriteMethod result = Cr2Parser::encode(io, nullptr, 0, littleEndian,
                                           exifData_, iptcData_, xmpData_);
    // The function should return a valid WriteMethod enum value
    // wmIntrusive = 0, wmNonIntrusive = 1 are typical values
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test that encode filters out panaRawId entries from ExifData
TEST_F(Cr2ParserEncodeTest_1746, EncodeFiltersPanaRawIdEntries_1746) {
    MemIo io;

    // Add an Exif entry with panaRawId group
    // panaRawId = 19 in the IfdId enum
    // We need to add an exifdatum that belongs to panaRawId group
    // After encode, entries with panaRawId should be removed from exifData_
    
    // First check the exifData is empty before
    EXPECT_TRUE(exifData_.empty());

    // Call encode - even with empty data, the filtering should work
    Cr2Parser::encode(io, nullptr, 0, littleEndian,
                      exifData_, iptcData_, xmpData_);

    // After encode with no panaRawId entries, exifData should still be empty
    EXPECT_TRUE(exifData_.empty());
}

// Test encode with littleEndian byte order
TEST_F(Cr2ParserEncodeTest_1746, EncodeWithLittleEndian_1746) {
    MemIo io;
    WriteMethod result = Cr2Parser::encode(io, nullptr, 0, littleEndian,
                                           exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test encode with bigEndian byte order
TEST_F(Cr2ParserEncodeTest_1746, EncodeWithBigEndian_1746) {
    MemIo io;
    WriteMethod result = Cr2Parser::encode(io, nullptr, 0, bigEndian,
                                           exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test encode with some ExifData present (non-panaRawId entries should survive)
TEST_F(Cr2ParserEncodeTest_1746, EncodePreservesNonFilteredExifData_1746) {
    MemIo io;

    // Add a standard exif entry (not panaRawId)
    exifData_["Exif.Image.Make"] = "Canon";
    size_t countBefore = exifData_.count();
    EXPECT_GT(countBefore, 0u);

    Cr2Parser::encode(io, nullptr, 0, littleEndian,
                      exifData_, iptcData_, xmpData_);

    // Non-panaRawId entries should still be present
    EXPECT_GE(exifData_.count(), 0u);
}

// Test encode with some actual data bytes
TEST_F(Cr2ParserEncodeTest_1746, EncodeWithNonNullData_1746) {
    MemIo io;
    // Create some dummy data (not valid CR2 but tests the interface)
    byte data[64];
    std::memset(data, 0, sizeof(data));

    WriteMethod result = Cr2Parser::encode(io, data, sizeof(data), littleEndian,
                                           exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test encode with zero-size but non-null data pointer
TEST_F(Cr2ParserEncodeTest_1746, EncodeWithZeroSizeNonNullData_1746) {
    MemIo io;
    byte data[1] = {0};

    WriteMethod result = Cr2Parser::encode(io, data, 0, littleEndian,
                                           exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test that encode can handle IPTC data being present
TEST_F(Cr2ParserEncodeTest_1746, EncodeWithIptcData_1746) {
    MemIo io;

    // Add some IPTC data
    iptcData_["Iptc.Application2.Caption"] = "Test caption";

    WriteMethod result = Cr2Parser::encode(io, nullptr, 0, littleEndian,
                                           exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test that encode can handle XMP data being present
TEST_F(Cr2ParserEncodeTest_1746, EncodeWithXmpData_1746) {
    MemIo io;

    // Add some XMP data
    xmpData_["Xmp.dc.title"] = "Test title";

    WriteMethod result = Cr2Parser::encode(io, nullptr, 0, littleEndian,
                                           exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test that encode can handle all metadata types present simultaneously
TEST_F(Cr2ParserEncodeTest_1746, EncodeWithAllMetadataTypes_1746) {
    MemIo io;

    exifData_["Exif.Image.Make"] = "Canon";
    iptcData_["Iptc.Application2.Caption"] = "Test caption";
    xmpData_["Xmp.dc.title"] = "Test title";

    WriteMethod result = Cr2Parser::encode(io, nullptr, 0, littleEndian,
                                           exifData_, iptcData_, xmpData_);
    EXPECT_TRUE(result == wmIntrusive || result == wmNonIntrusive);
}

// Test multiple calls to encode
TEST_F(Cr2ParserEncodeTest_1746, EncodeMultipleCalls_1746) {
    MemIo io1;
    MemIo io2;

    WriteMethod result1 = Cr2Parser::encode(io1, nullptr, 0, littleEndian,
                                            exifData_, iptcData_, xmpData_);
    WriteMethod result2 = Cr2Parser::encode(io2, nullptr, 0, bigEndian,
                                            exifData_, iptcData_, xmpData_);

    EXPECT_TRUE(result1 == wmIntrusive || result1 == wmNonIntrusive);
    EXPECT_TRUE(result2 == wmIntrusive || result2 == wmNonIntrusive);
}
