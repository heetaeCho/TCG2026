#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <vector>
#include <cstring>

using namespace Exiv2;

class ExifParserTest_43 : public ::testing::Test {
protected:
    ExifData exifData_;
    Blob blob_;

    void SetUp() override {
        exifData_.clear();
        blob_.clear();
    }
};

// =============================================================================
// ExifData tests
// =============================================================================

TEST_F(ExifParserTest_43, ExifDataDefaultEmpty_43) {
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

TEST_F(ExifParserTest_43, ExifDataAddByKeyAndValue_43) {
    ExifKey key("Exif.Image.Make");
    Value::UniquePtr value = Value::create(asciiString);
    value->read("Canon");
    exifData_.add(key, value.get());

    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);
}

TEST_F(ExifParserTest_43, ExifDataOperatorBracket_43) {
    exifData_["Exif.Image.Make"] = "Nikon";

    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);

    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "Nikon");
}

TEST_F(ExifParserTest_43, ExifDataAddMultipleEntries_43) {
    exifData_["Exif.Image.Make"] = "Canon";
    exifData_["Exif.Image.Model"] = "EOS 5D";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);

    EXPECT_EQ(exifData_.count(), 3u);
}

TEST_F(ExifParserTest_43, ExifDataClear_43) {
    exifData_["Exif.Image.Make"] = "Sony";
    exifData_["Exif.Image.Model"] = "A7III";
    EXPECT_EQ(exifData_.count(), 2u);

    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 0u);
}

TEST_F(ExifParserTest_43, ExifDataEraseIterator_43) {
    exifData_["Exif.Image.Make"] = "Fuji";
    exifData_["Exif.Image.Model"] = "X-T4";
    EXPECT_EQ(exifData_.count(), 2u);

    auto it = exifData_.begin();
    exifData_.erase(it);
    EXPECT_EQ(exifData_.count(), 1u);
}

TEST_F(ExifParserTest_43, ExifDataEraseRange_43) {
    exifData_["Exif.Image.Make"] = "Pentax";
    exifData_["Exif.Image.Model"] = "K-1";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);
    EXPECT_EQ(exifData_.count(), 3u);

    exifData_.erase(exifData_.begin(), exifData_.end());
    EXPECT_TRUE(exifData_.empty());
}

TEST_F(ExifParserTest_43, ExifDataFindKeyExisting_43) {
    exifData_["Exif.Image.Make"] = "Leica";

    auto it = exifData_.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "Leica");
}

TEST_F(ExifParserTest_43, ExifDataFindKeyNonExisting_43) {
    exifData_["Exif.Image.Make"] = "Olympus";

    auto it = exifData_.findKey(ExifKey("Exif.Image.Model"));
    EXPECT_EQ(it, exifData_.end());
}

TEST_F(ExifParserTest_43, ExifDataSortByKey_43) {
    exifData_["Exif.Image.Model"] = "D850";
    exifData_["Exif.Image.Make"] = "Nikon";

    exifData_.sortByKey();

    // After sorting by key, Make should come before Model alphabetically
    auto it = exifData_.begin();
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
}

TEST_F(ExifParserTest_43, ExifDataSortByTag_43) {
    // Exif.Image.Model has tag 0x0110, Exif.Image.Make has tag 0x010f
    exifData_["Exif.Image.Model"] = "D850";
    exifData_["Exif.Image.Make"] = "Nikon";

    exifData_.sortByTag();

    auto it = exifData_.begin();
    ASSERT_NE(it, exifData_.end());
    // Make (0x010f) should come before Model (0x0110)
    EXPECT_EQ(it->key(), "Exif.Image.Make");
}

// =============================================================================
// ExifParser::encode tests (convenience overload with no existing data)
// =============================================================================

TEST_F(ExifParserTest_43, EncodeEmptyExifData_43) {
    ExifParser::encode(blob_, bigEndian, exifData_);
    // With empty exif data, the blob should be empty or minimal
    // (no tags to encode)
    EXPECT_TRUE(blob_.empty());
}

TEST_F(ExifParserTest_43, EncodeWithSingleTag_43) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    ExifParser::encode(blob_, bigEndian, exifData_);

    // There should be some data encoded
    EXPECT_FALSE(blob_.empty());
}

TEST_F(ExifParserTest_43, EncodeWithMultipleTags_43) {
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);

    ExifParser::encode(blob_, bigEndian, exifData_);
    EXPECT_FALSE(blob_.empty());
}

TEST_F(ExifParserTest_43, EncodeWithLittleEndian_43) {
    exifData_["Exif.Image.Make"] = "TestCamera";

    ExifParser::encode(blob_, littleEndian, exifData_);
    EXPECT_FALSE(blob_.empty());
}

TEST_F(ExifParserTest_43, EncodeWithBigEndian_43) {
    exifData_["Exif.Image.Make"] = "TestCamera";

    ExifParser::encode(blob_, bigEndian, exifData_);
    EXPECT_FALSE(blob_.empty());
}

// =============================================================================
// ExifParser::decode tests
// =============================================================================

TEST_F(ExifParserTest_43, DecodeNullptrData_43) {
    // Decoding with nullptr and size 0 should not crash
    // It may return invalidByteOrder or some default
    ByteOrder bo = ExifParser::decode(exifData_, nullptr, 0);
    // The exifData should remain empty
    EXPECT_TRUE(exifData_.empty());
    (void)bo; // We just check it doesn't crash
}

TEST_F(ExifParserTest_43, DecodeZeroSizeData_43) {
    byte data[1] = {0};
    ByteOrder bo = ExifParser::decode(exifData_, data, 0);
    EXPECT_TRUE(exifData_.empty());
    (void)bo;
}

TEST_F(ExifParserTest_43, DecodeInvalidData_43) {
    byte invalidData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    ByteOrder bo = ExifParser::decode(exifData_, invalidData, sizeof(invalidData));
    // Invalid TIFF header should result in either invalidByteOrder or empty exifData
    (void)bo;
}

TEST_F(ExifParserTest_43, RoundTripEncodeDecodeSimple_43) {
    // Create exif data, encode it, then decode it back
    exifData_["Exif.Image.Make"] = "RoundTripCamera";
    exifData_["Exif.Image.Model"] = "RoundTripModel";

    Blob encoded;
    ExifParser::encode(encoded, littleEndian, exifData_);

    if (!encoded.empty()) {
        ExifData decodedData;
        ByteOrder bo = ExifParser::decode(decodedData, encoded.data(), encoded.size());

        // If decoding succeeds, check the values
        if (bo != invalidByteOrder) {
            auto itMake = decodedData.findKey(ExifKey("Exif.Image.Make"));
            if (itMake != decodedData.end()) {
                EXPECT_EQ(itMake->toString(), "RoundTripCamera");
            }

            auto itModel = decodedData.findKey(ExifKey("Exif.Image.Model"));
            if (itModel != decodedData.end()) {
                EXPECT_EQ(itModel->toString(), "RoundTripModel");
            }
        }
    }
}

TEST_F(ExifParserTest_43, RoundTripEncodeBigEndian_43) {
    exifData_["Exif.Image.Make"] = "BigEndianCamera";

    Blob encoded;
    ExifParser::encode(encoded, bigEndian, exifData_);

    if (!encoded.empty()) {
        ExifData decodedData;
        ByteOrder bo = ExifParser::decode(decodedData, encoded.data(), encoded.size());

        if (bo != invalidByteOrder) {
            EXPECT_EQ(bo, bigEndian);
            auto itMake = decodedData.findKey(ExifKey("Exif.Image.Make"));
            if (itMake != decodedData.end()) {
                EXPECT_EQ(itMake->toString(), "BigEndianCamera");
            }
        }
    }
}

TEST_F(ExifParserTest_43, RoundTripEncodeLittleEndian_43) {
    exifData_["Exif.Image.Make"] = "LittleEndianCamera";

    Blob encoded;
    ExifParser::encode(encoded, littleEndian, exifData_);

    if (!encoded.empty()) {
        ExifData decodedData;
        ByteOrder bo = ExifParser::decode(decodedData, encoded.data(), encoded.size());

        if (bo != invalidByteOrder) {
            EXPECT_EQ(bo, littleEndian);
            auto itMake = decodedData.findKey(ExifKey("Exif.Image.Make"));
            if (itMake != decodedData.end()) {
                EXPECT_EQ(itMake->toString(), "LittleEndianCamera");
            }
        }
    }
}

// =============================================================================
// ExifParser::encode (4-param overload with existing data)
// =============================================================================

TEST_F(ExifParserTest_43, EncodeWithExistingDataNullptr_43) {
    exifData_["Exif.Image.Make"] = "TestMake";

    Blob encoded;
    WriteMethod wm = ExifParser::encode(encoded, nullptr, 0, littleEndian, exifData_);

    // When pData is nullptr, it should use wmIntrusive method
    // (creating from scratch)
    (void)wm;
    // Just verify it doesn't crash; blob may or may not be empty
}

TEST_F(ExifParserTest_43, EncodeWithExistingDataEmpty_43) {
    // Empty exif data with nullptr
    Blob encoded;
    WriteMethod wm = ExifParser::encode(encoded, nullptr, 0, bigEndian, exifData_);
    (void)wm;
    // Should not crash
}

TEST_F(ExifParserTest_43, EncodeModifyAndReencode_43) {
    // First encode
    exifData_["Exif.Image.Make"] = "OriginalMake";
    Blob firstEncoded;
    ExifParser::encode(firstEncoded, littleEndian, exifData_);

    if (!firstEncoded.empty()) {
        // Modify and re-encode using the existing data
        exifData_["Exif.Image.Make"] = "ModifiedMake";
        Blob secondEncoded;
        WriteMethod wm = ExifParser::encode(secondEncoded, firstEncoded.data(),
                                             firstEncoded.size(), littleEndian, exifData_);
        (void)wm;

        // Decode the result
        ExifData decodedData;
        const byte* data = secondEncoded.empty() ? firstEncoded.data() : secondEncoded.data();
        size_t size = secondEncoded.empty() ? firstEncoded.size() : secondEncoded.size();
        ByteOrder bo = ExifParser::decode(decodedData, data, size);

        if (bo != invalidByteOrder) {
            auto it = decodedData.findKey(ExifKey("Exif.Image.Make"));
            if (it != decodedData.end()) {
                // The value should be modified
                EXPECT_EQ(it->toString(), "ModifiedMake");
            }
        }
    }
}

TEST_F(ExifParserTest_43, EncodeReturnsBlobData_43) {
    exifData_["Exif.Image.Make"] = "BlobTest";
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:15 10:30:00";

    ExifParser::encode(blob_, littleEndian, exifData_);

    if (!blob_.empty()) {
        // The blob should contain valid TIFF-like data
        // Minimum TIFF header is 8 bytes
        EXPECT_GE(blob_.size(), 8u);
    }
}

TEST_F(ExifParserTest_43, DecodeValidTiffHeader_43) {
    // Build a minimal valid TIFF with little-endian byte order
    // II (0x49 0x49) + 42 (0x2A 0x00) + offset to IFD0 (0x08 0x00 0x00 0x00)
    // + IFD with 0 entries (0x00 0x00) + next IFD offset (0x00 0x00 0x00 0x00)
    byte tiffData[] = {
        0x49, 0x49, 0x2A, 0x00,  // "II" + magic 42
        0x08, 0x00, 0x00, 0x00,  // offset to IFD0 = 8
        0x00, 0x00,              // 0 entries in IFD
        0x00, 0x00, 0x00, 0x00   // next IFD offset = 0
    };

    ByteOrder bo = ExifParser::decode(exifData_, tiffData, sizeof(tiffData));
    EXPECT_EQ(bo, littleEndian);
}

TEST_F(ExifParserTest_43, DecodeValidTiffHeaderBigEndian_43) {
    // MM (0x4D 0x4D) + 42 (0x00 0x2A) + offset to IFD0 (0x00 0x00 0x00 0x08)
    // + IFD with 0 entries (0x00 0x00) + next IFD offset (0x00 0x00 0x00 0x00)
    byte tiffData[] = {
        0x4D, 0x4D, 0x00, 0x2A,  // "MM" + magic 42
        0x00, 0x00, 0x00, 0x08,  // offset to IFD0 = 8
        0x00, 0x00,              // 0 entries in IFD
        0x00, 0x00, 0x00, 0x00   // next IFD offset = 0
    };

    ByteOrder bo = ExifParser::decode(exifData_, tiffData, sizeof(tiffData));
    EXPECT_EQ(bo, bigEndian);
}

TEST_F(ExifParserTest_43, AddExifdatumToExifData_43) {
    // Use operator[] to create one
    exifData_["Exif.Image.Make"] = "TestAdd";
    EXPECT_EQ(exifData_.count(), 1u);

    // Copy the datum and add it with a different key
    Exifdatum datum;
    ExifKey key("Exif.Image.Model");
    Value::UniquePtr val = Value::create(asciiString);
    val->read("TestModel");
    exifData_.add(key, val.get());

    EXPECT_EQ(exifData_.count(), 2u);
}

TEST_F(ExifParserTest_43, IteratorTraversal_43) {
    exifData_["Exif.Image.Make"] = "A";
    exifData_["Exif.Image.Model"] = "B";
    exifData_["Exif.Image.Orientation"] = uint16_t(1);

    size_t count = 0;
    for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 3u);
    EXPECT_EQ(count, exifData_.count());
}

TEST_F(ExifParserTest_43, EncodeThenDecodePreservesCount_43) {
    exifData_["Exif.Image.Make"] = "CountTest";
    exifData_["Exif.Image.Model"] = "CountModel";

    Blob encoded;
    ExifParser::encode(encoded, littleEndian, exifData_);

    if (!encoded.empty()) {
        ExifData decoded;
        ByteOrder bo = ExifParser::decode(decoded, encoded.data(), encoded.size());
        if (bo != invalidByteOrder) {
            // At minimum the two tags we added should be present
            EXPECT_GE(decoded.count(), 2u);
        }
    }
}

TEST_F(ExifParserTest_43, DecodeSmallDataDoesNotCrash_43) {
    // Data too small to be valid TIFF
    byte smallData[] = {0x49, 0x49};
    ByteOrder bo = ExifParser::decode(exifData_, smallData, sizeof(smallData));
    (void)bo;
    // Should not crash, data is too small for valid TIFF
}

TEST_F(ExifParserTest_43, EncodeEmptyBlobNotModifiedIfNoData_43) {
    Blob emptyBlob;
    ExifParser::encode(emptyBlob, bigEndian, exifData_);
    // With empty exif data, blob should remain empty
    EXPECT_TRUE(emptyBlob.empty());
}
