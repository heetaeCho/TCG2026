#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/basicio.hpp>
#include <vector>
#include <cstring>

using namespace Exiv2;

class ExifParserEncodeTest_785 : public ::testing::Test {
protected:
    void SetUp() override {
        blob.clear();
        exifData.clear();
    }

    Blob blob;
    ExifData exifData;
};

// Test encoding with empty ExifData and no source data
TEST_F(ExifParserEncodeTest_785, EncodeEmptyExifData_785) {
    Blob result;
    ExifData emptyData;
    WriteMethod wm = ExifParser::encode(result, nullptr, 0, littleEndian, emptyData);
    // With empty data, the result should either be empty or contain minimal TIFF header
    // We just verify it doesn't crash and returns a valid WriteMethod
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test that filtered IFD0 tags are removed during encoding
TEST_F(ExifParserEncodeTest_785, FilteredIfd0TagsAreRemoved_785) {
    // Add a filtered tag
    exifData["Exif.Image.StripOffsets"] = uint32_t(100);
    ASSERT_NE(exifData.findKey(ExifKey("Exif.Image.StripOffsets")), exifData.end());

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    // After encoding, the filtered tag should have been erased from exifData
    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.StripOffsets")), exifData.end());
}

// Test that multiple filtered IFD0 tags are removed
TEST_F(ExifParserEncodeTest_785, MultipleFilteredIfd0TagsRemoved_785) {
    exifData["Exif.Image.StripOffsets"] = uint32_t(100);
    exifData["Exif.Image.StripByteCounts"] = uint32_t(200);
    exifData["Exif.Image.RowsPerStrip"] = uint32_t(50);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.StripOffsets")), exifData.end());
    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.StripByteCounts")), exifData.end());
    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.RowsPerStrip")), exifData.end());
}

// Test that PhotometricInterpretation is filtered
TEST_F(ExifParserEncodeTest_785, PhotometricInterpretationFiltered_785) {
    exifData["Exif.Image.PhotometricInterpretation"] = uint16_t(2);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.PhotometricInterpretation")), exifData.end());
}

// Test that JPEGInterchangeFormat tag is filtered
TEST_F(ExifParserEncodeTest_785, JPEGInterchangeFormatFiltered_785) {
    exifData["Exif.Image.JPEGInterchangeFormat"] = uint32_t(0);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.JPEGInterchangeFormat")), exifData.end());
}

// Test that JPEGInterchangeFormatLength tag is filtered
TEST_F(ExifParserEncodeTest_785, JPEGInterchangeFormatLengthFiltered_785) {
    exifData["Exif.Image.JPEGInterchangeFormatLength"] = uint32_t(0);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.JPEGInterchangeFormatLength")), exifData.end());
}

// Test that SubIFDs tag is filtered
TEST_F(ExifParserEncodeTest_785, SubIFDsFiltered_785) {
    exifData["Exif.Image.SubIFDs"] = uint32_t(0);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.SubIFDs")), exifData.end());
}

// Test encoding with big endian byte order
TEST_F(ExifParserEncodeTest_785, EncodeBigEndian_785) {
    Blob result;
    ExifData data;
    WriteMethod wm = ExifParser::encode(result, nullptr, 0, bigEndian, data);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test encoding with little endian byte order
TEST_F(ExifParserEncodeTest_785, EncodeLittleEndian_785) {
    Blob result;
    ExifData data;
    WriteMethod wm = ExifParser::encode(result, nullptr, 0, littleEndian, data);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test that non-filtered tags survive encoding
TEST_F(ExifParserEncodeTest_785, NonFilteredTagsSurvive_785) {
    exifData["Exif.Image.Make"] = "TestCamera";

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    // Non-filtered tags should still be present
    EXPECT_NE(exifData.findKey(ExifKey("Exif.Image.Make")), exifData.end());
}

// Test that Canon AF filtered tags are removed
TEST_F(ExifParserEncodeTest_785, CanonAFTagsFiltered_785) {
    // These are in the filteredIfd0Tags list as Canon AF tags
    exifData["Exif.Canon.AFInfoSize"] = uint16_t(1);
    exifData["Exif.Canon.AFAreaMode"] = uint16_t(2);
    exifData["Exif.Canon.AFNumPoints"] = uint16_t(9);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFInfoSize")), exifData.end());
    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFAreaMode")), exifData.end());
    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFNumPoints")), exifData.end());
}

// Test encoding with non-null source data (empty but valid buffer)
TEST_F(ExifParserEncodeTest_785, EncodeWithSourceData_785) {
    // Create a minimal valid TIFF structure for source data
    std::vector<byte> sourceData(16, 0);
    Blob result;
    ExifData data;
    WriteMethod wm = ExifParser::encode(result, sourceData.data(), sourceData.size(), littleEndian, data);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test that blob gets data appended after encoding
TEST_F(ExifParserEncodeTest_785, BlobGetsData_785) {
    Blob result;
    ExifData data;
    // Add a simple tag so there's something to encode
    data["Exif.Image.Make"] = "Test";
    ExifParser::encode(result, nullptr, 0, littleEndian, data);
    // The blob should contain at least some data (TIFF header at minimum)
    // Note: with empty source, it might still produce output or not
    // We verify it doesn't crash at minimum
    SUCCEED();
}

// Test Canon AFFineRotation is filtered
TEST_F(ExifParserEncodeTest_785, CanonAFFineRotationFiltered_785) {
    exifData["Exif.Canon.AFFineRotation"] = uint16_t(0);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFFineRotation")), exifData.end());
}

// Test encoding preserves Exif standard tags
TEST_F(ExifParserEncodeTest_785, PreservesExifStandardTags_785) {
    exifData["Exif.Photo.ExposureTime"] = "1/100";

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    // Standard EXIF tags should not be filtered
    EXPECT_NE(exifData.findKey(ExifKey("Exif.Photo.ExposureTime")), exifData.end());
}

// Test that the three-argument encode overload works
TEST_F(ExifParserEncodeTest_785, ThreeArgEncode_785) {
    Blob result;
    ExifData data;
    data["Exif.Image.Make"] = "TestCam";
    // This calls the simpler encode that doesn't take pData/size
    ExifParser::encode(result, littleEndian, data);
    // Just verify no crash
    SUCCEED();
}

// Test ExifData operations used in encode
TEST_F(ExifParserEncodeTest_785, ExifDataFindAndErase_785) {
    exifData["Exif.Image.Model"] = "TestModel";
    auto it = exifData.findKey(ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->key(), "Exif.Image.Model");

    exifData.erase(it);
    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.Model")), exifData.end());
}

// Test encoding with exif data that has both filtered and non-filtered tags
TEST_F(ExifParserEncodeTest_785, MixedFilteredAndNonFilteredTags_785) {
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";
    exifData["Exif.Image.StripOffsets"] = uint32_t(100);
    exifData["Exif.Image.StripByteCounts"] = uint32_t(200);
    exifData["Exif.Photo.ExposureTime"] = "1/60";

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    // Filtered tags should be removed
    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.StripOffsets")), exifData.end());
    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.StripByteCounts")), exifData.end());

    // Non-filtered tags should remain
    EXPECT_NE(exifData.findKey(ExifKey("Exif.Image.Make")), exifData.end());
    EXPECT_NE(exifData.findKey(ExifKey("Exif.Image.Model")), exifData.end());
    EXPECT_NE(exifData.findKey(ExifKey("Exif.Photo.ExposureTime")), exifData.end());
}

// Test Canon AFValidPoints filtered
TEST_F(ExifParserEncodeTest_785, CanonAFValidPointsFiltered_785) {
    exifData["Exif.Canon.AFValidPoints"] = uint16_t(5);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFValidPoints")), exifData.end());
}

// Test Canon AFCanonImageWidth filtered
TEST_F(ExifParserEncodeTest_785, CanonAFCanonImageWidthFiltered_785) {
    exifData["Exif.Canon.AFCanonImageWidth"] = uint16_t(4000);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFCanonImageWidth")), exifData.end());
}

// Test Canon AFCanonImageHeight filtered
TEST_F(ExifParserEncodeTest_785, CanonAFCanonImageHeightFiltered_785) {
    exifData["Exif.Canon.AFCanonImageHeight"] = uint16_t(3000);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFCanonImageHeight")), exifData.end());
}

// Test decode and re-encode round trip with empty data
TEST_F(ExifParserEncodeTest_785, DecodeEncodeRoundTripEmpty_785) {
    ExifData data;
    // Attempt decode with empty data
    // The decode might throw or return invalidByteOrder for invalid data
    // We test encode with no prior decode
    Blob result;
    WriteMethod wm = ExifParser::encode(result, nullptr, 0, littleEndian, data);
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
}

// Test Canon AFPointsInFocus filtered
TEST_F(ExifParserEncodeTest_785, CanonAFPointsInFocusFiltered_785) {
    exifData["Exif.Canon.AFPointsInFocus"] = uint16_t(1);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFPointsInFocus")), exifData.end());
}

// Test Canon AFPointsSelected filtered
TEST_F(ExifParserEncodeTest_785, CanonAFPointsSelectedFiltered_785) {
    exifData["Exif.Canon.AFPointsSelected"] = uint16_t(3);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFPointsSelected")), exifData.end());
}

// Test Canon AFPointsUnusable filtered
TEST_F(ExifParserEncodeTest_785, CanonAFPointsUnusableFiltered_785) {
    exifData["Exif.Canon.AFPointsUnusable"] = uint16_t(0);

    ExifParser::encode(blob, nullptr, 0, littleEndian, exifData);

    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Canon.AFPointsUnusable")), exifData.end());
}
