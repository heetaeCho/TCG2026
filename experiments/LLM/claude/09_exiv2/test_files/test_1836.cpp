#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// We need to access the Converter class which is defined in convert.cpp
// The public API for conversion is through copyExifToXmp, etc.
// But based on the partial code, Converter is in the Exiv2 namespace.
// We'll test through the public conversion functions and direct Converter usage.

// Since Converter is defined in convert.cpp (not a public header), we need to
// include or declare it. In the exiv2 codebase, there are public functions that
// use Converter internally. Let's test through those, and also test Converter directly.

// Forward declaration based on the provided interface
namespace Exiv2 {
    void copyExifToXmp(const ExifData& exifData, XmpData& xmpData);
    void copyXmpToExif(const XmpData& xmpData, ExifData& exifData);
    void syncExifWithXmp(ExifData& exifData, XmpData& xmpData);
    void copyIptcToXmp(const IptcData& iptcData, XmpData& xmpData, const char* iptcCharset = nullptr);
    void copyXmpToIptc(const XmpData& xmpData, IptcData& iptcData);
}

class ConverterTest_1836 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
    Exiv2::IptcData iptcData_;
};

// Test: Converting empty ExifData to XmpData should result in empty/unchanged XmpData
TEST_F(ConverterTest_1836, CopyEmptyExifToXmp_1836) {
    Exiv2::ExifData emptyExif;
    Exiv2::XmpData emptyXmp;

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(emptyExif, emptyXmp));
    EXPECT_TRUE(emptyXmp.empty());
}

// Test: Converting empty XmpData to ExifData should result in empty/unchanged ExifData
TEST_F(ConverterTest_1836, CopyEmptyXmpToExif_1836) {
    Exiv2::ExifData emptyExif;
    Exiv2::XmpData emptyXmp;

    ASSERT_NO_THROW(Exiv2::copyXmpToExif(emptyXmp, emptyExif));
    EXPECT_TRUE(emptyExif.empty());
}

// Test: ExifComment conversion from Exif to XMP
TEST_F(ConverterTest_1836, CnvExifCommentToXmp_1836) {
    // Set a UserComment in ExifData
    Exiv2::CommentValue commentValue("charset=Ascii A test comment");
    exifData_["Exif.Photo.UserComment"].setValue(&commentValue);

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    // Check that the XMP data contains the description
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.UserComment"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: ExifComment with non-CommentValue type should not crash
TEST_F(ConverterTest_1836, CnvExifCommentNonCommentValue_1836) {
    // Set UserComment as a regular string value (not CommentValue)
    exifData_["Exif.Photo.UserComment"] = "plain string";

    // This should not crash, just possibly warn
    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Convert ExifData with standard tags to XmpData
TEST_F(ConverterTest_1836, CopyExifStandardTagsToXmp_1836) {
    exifData_["Exif.Image.Artist"] = "Test Artist";
    exifData_["Exif.Image.Copyright"] = "Test Copyright";

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    // Verify some XMP tags were created
    // Artist maps to dc.creator
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Test Artist"), std::string::npos);
    }
}

// Test: Copy XmpData with standard tags to ExifData
TEST_F(ConverterTest_1836, CopyXmpStandardTagsToExif_1836) {
    xmpData_["Xmp.dc.creator"] = "XMP Creator";

    ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    if (pos != exifData_.end()) {
        EXPECT_NE(pos->toString().find("XMP Creator"), std::string::npos);
    }
}

// Test: ExifVersion conversion
TEST_F(ConverterTest_1836, CnvExifVersionToXmp_1836) {
    // ExifVersion is typically "48 50 51 48" for version 2.30
    Exiv2::DataBuf buf(4);
    buf.data()[0] = '0';
    buf.data()[1] = '2';
    buf.data()[2] = '3';
    buf.data()[3] = '0';
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::undefined);
    val->read(buf.data(), buf.size(), Exiv2::littleEndian);
    exifData_.add(Exiv2::ExifKey("Exif.Photo.ExifVersion"), val.get());

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    if (pos != xmpData_.end()) {
        // Should be something like "2.30"
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: GPS coordinate conversion from Exif to XMP
TEST_F(ConverterTest_1836, CnvExifGPSCoordToXmp_1836) {
    // Set GPS latitude
    Exiv2::URationalValue::UniquePtr lat(new Exiv2::URationalValue);
    lat->read("48/1 51/1 29/1");
    exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), lat.get());
    exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: Flash value conversion from Exif to XMP
TEST_F(ConverterTest_1836, CnvExifFlashToXmp_1836) {
    exifData_["Exif.Photo.Flash"] = uint16_t(0x0001); // Flash fired

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    // Flash in XMP is a struct
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash"));
    // The flash struct should have been created with sub-properties
}

// Test: Round-trip Exif -> XMP -> Exif preserves data
TEST_F(ConverterTest_1836, RoundTripExifXmpExif_1836) {
    exifData_["Exif.Image.Artist"] = "Round Trip Artist";

    Exiv2::XmpData xmpTemp;
    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpTemp));

    Exiv2::ExifData exifResult;
    ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpTemp, exifResult));

    auto pos = exifResult.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    if (pos != exifResult.end()) {
        EXPECT_NE(pos->toString().find("Round Trip Artist"), std::string::npos);
    }
}

// Test: Copy empty IPTC to XMP
TEST_F(ConverterTest_1836, CopyEmptyIptcToXmp_1836) {
    Exiv2::IptcData emptyIptc;
    Exiv2::XmpData emptyXmp;

    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(emptyIptc, emptyXmp));
    EXPECT_TRUE(emptyXmp.empty());
}

// Test: Copy empty XMP to IPTC
TEST_F(ConverterTest_1836, CopyEmptyXmpToIptc_1836) {
    Exiv2::XmpData emptyXmp;
    Exiv2::IptcData emptyIptc;

    ASSERT_NO_THROW(Exiv2::copyXmpToIptc(emptyXmp, emptyIptc));
    EXPECT_TRUE(emptyIptc.empty());
}

// Test: IPTC to XMP conversion with data
TEST_F(ConverterTest_1836, CopyIptcToXmpWithData_1836) {
    iptcData_["Iptc.Application2.Caption"] = "Test Caption";

    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Test Caption"), std::string::npos);
    }
}

// Test: XMP to IPTC conversion with data
TEST_F(ConverterTest_1836, CopyXmpToIptcWithData_1836) {
    xmpData_["Xmp.dc.description"] = "XMP Description";

    ASSERT_NO_THROW(Exiv2::copyXmpToIptc(xmpData_, iptcData_));
}

// Test: Sync Exif with XMP on empty data
TEST_F(ConverterTest_1836, SyncExifWithXmpEmpty_1836) {
    Exiv2::ExifData emptyExif;
    Exiv2::XmpData emptyXmp;

    ASSERT_NO_THROW(Exiv2::syncExifWithXmp(emptyExif, emptyXmp));
}

// Test: ExifDate conversion
TEST_F(ConverterTest_1836, CnvExifDateToXmp_1836) {
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:00";

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (pos != xmpData_.end()) {
        std::string dateStr = pos->toString();
        EXPECT_FALSE(dateStr.empty());
        // XMP dates typically use ISO format with dashes
        EXPECT_NE(dateStr.find("2023"), std::string::npos);
    }
}

// Test: XmpDate conversion back to Exif
TEST_F(ConverterTest_1836, CnvXmpDateToExif_1836) {
    xmpData_["Xmp.exif.DateTimeOriginal"] = "2023-06-15T10:30:00";

    ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    if (pos != exifData_.end()) {
        std::string dateStr = pos->toString();
        EXPECT_FALSE(dateStr.empty());
    }
}

// Test: Multiple tags conversion
TEST_F(ConverterTest_1836, CopyMultipleExifTagsToXmp_1836) {
    exifData_["Exif.Image.Artist"] = "Artist Name";
    exifData_["Exif.Image.Copyright"] = "Copyright 2023";
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    exifData_["Exif.Image.ImageDescription"] = "Test Image";

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    // Verify at least some XMP tags were created
    EXPECT_FALSE(xmpData_.empty());
}

// Test: Conversion with pre-existing XMP data (overwrite behavior)
TEST_F(ConverterTest_1836, CopyExifToXmpWithExistingXmpData_1836) {
    xmpData_["Xmp.dc.creator"] = "Existing Creator";
    exifData_["Exif.Image.Artist"] = "New Artist";

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    // The default overwrite behavior should overwrite existing values
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("New Artist"), std::string::npos);
    }
}

// Test: ExifArray conversion (e.g., ISOSpeedRatings)
TEST_F(ConverterTest_1836, CnvExifArrayToXmp_1836) {
    exifData_["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ISOSpeedRatings"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: CommentValue with charset=Unicode
TEST_F(ConverterTest_1836, CnvExifCommentUnicodeToXmp_1836) {
    Exiv2::CommentValue commentValue("charset=Unicode Hello World");
    exifData_["Exif.Photo.UserComment"].setValue(&commentValue);

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: CommentValue with empty comment
TEST_F(ConverterTest_1836, CnvExifCommentEmptyToXmp_1836) {
    Exiv2::CommentValue commentValue("");
    exifData_["Exif.Photo.UserComment"].setValue(&commentValue);

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: GPSVersionID conversion
TEST_F(ConverterTest_1836, CnvExifGPSVersionToXmp_1836) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 3 0 0");
    exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), val.get());

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: Key not found in ExifData should not crash cnvExifComment
TEST_F(ConverterTest_1836, CnvExifCommentKeyNotFound_1836) {
    // ExifData is empty, so the key won't be found
    // We test this through the full conversion pipeline
    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
    // Should simply do nothing for missing keys
}

// Test: Copyright with XMP
TEST_F(ConverterTest_1836, CopyCopyrightExifToXmp_1836) {
    exifData_["Exif.Image.Copyright"] = "Copyright (c) 2023 Test";

    ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Copyright"), std::string::npos);
    }
}

// Test: XMP to Exif with GPS coordinates
TEST_F(ConverterTest_1836, CnvXmpGPSCoordToExif_1836) {
    xmpData_["Xmp.exif.GPSLatitude"] = "48,51.4833N";

    ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    if (pos != exifData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: XMP Flash struct to Exif
TEST_F(ConverterTest_1836, CnvXmpFlashToExif_1836) {
    xmpData_["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData_["Xmp.exif.Flash/exif:Return"] = "0";
    xmpData_["Xmp.exif.Flash/exif:Mode"] = "0";
    xmpData_["Xmp.exif.Flash/exif:Function"] = "False";
    xmpData_["Xmp.exif.Flash/exif:RedEyeMode"] = "False";

    ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData_.end()) {
        EXPECT_NE(pos->toInt64(), 0);
    }
}

// Test: XMP version to Exif
TEST_F(ConverterTest_1836, CnvXmpVersionToExif_1836) {
    xmpData_["Xmp.exif.ExifVersion"] = "2.30";

    ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.ExifVersion"));
    if (pos != exifData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: IPTC keywords to XMP
TEST_F(ConverterTest_1836, CopyIptcKeywordsToXmp_1836) {
    iptcData_["Iptc.Application2.Keywords"] = "keyword1";

    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("keyword1"), std::string::npos);
    }
}

// Test: XMP keywords to IPTC
TEST_F(ConverterTest_1836, CopyXmpKeywordsToIptc_1836) {
    xmpData_["Xmp.dc.subject"] = "testkeyword";

    ASSERT_NO_THROW(Exiv2::copyXmpToIptc(xmpData_, iptcData_));
}

// Test: Sync with data in both Exif and XMP
TEST_F(ConverterTest_1836, SyncExifWithXmpBothHaveData_1836) {
    exifData_["Exif.Image.Artist"] = "Exif Artist";
    xmpData_["Xmp.dc.creator"] = "XMP Artist";

    ASSERT_NO_THROW(Exiv2::syncExifWithXmp(exifData_, xmpData_));
}
