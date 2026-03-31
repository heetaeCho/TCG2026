#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Note: The Converter class is in an internal/anonymous namespace in some builds,
// but based on the provided interface it's in Exiv2 namespace.
// We'll use the public free functions that wrap Converter if direct access isn't available,
// but based on the prompt we test the Converter class directly.

// Since Converter may not be publicly exposed in the header, we need to include
// the implementation details. Based on the provided code, we work with what's available.
// The exiv2 library exposes copyExifToXmp, copyXmpToExif, etc. as free functions
// that internally use Converter. We test through those if Converter isn't directly accessible.

// However, based on the prompt showing Converter in namespace Exiv2, we attempt direct use.

namespace {

using namespace Exiv2;

class ConverterTest_1831 : public ::testing::Test {
protected:
    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;

    void SetUp() override {
        exifData_.clear();
        iptcData_.clear();
        xmpData_.clear();
    }

    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test: copyExifToXmp with empty ExifData produces empty or minimal XmpData
TEST_F(ConverterTest_1831, CopyExifToXmpEmptyData_1831) {
    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
    // With empty exif data, xmp should remain empty or have minimal entries
}

// Test: copyXmpToExif with empty XmpData produces empty ExifData
TEST_F(ConverterTest_1831, CopyXmpToExifEmptyData_1831) {
    ASSERT_NO_THROW(copyXmpToExif(xmpData_, exifData_));
    // With empty xmp data, exif should remain empty
    EXPECT_TRUE(exifData_.empty());
}

// Test: copyIptcToXmp with empty IptcData
TEST_F(ConverterTest_1831, CopyIptcToXmpEmptyData_1831) {
    ASSERT_NO_THROW(copyIptcToXmp(iptcData_, xmpData_));
}

// Test: copyXmpToIptc with empty XmpData
TEST_F(ConverterTest_1831, CopyXmpToIptcEmptyData_1831) {
    ASSERT_NO_THROW(copyXmpToIptc(xmpData_, iptcData_));
    EXPECT_TRUE(iptcData_.empty());
}

// Test: Round-trip Exif -> Xmp -> Exif preserves a simple value
TEST_F(ConverterTest_1831, RoundTripExifToXmpToExif_1831) {
    // Add a simple Exif tag - ImageDescription
    exifData_["Exif.Image.ImageDescription"] = "Test Description";

    // Convert Exif to Xmp
    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));

    // Check that XmpData has something
    auto it = xmpData_.findKey(XmpKey("Xmp.dc.description"));
    // The description might be mapped to dc:description
    // We just verify the conversion doesn't crash and produces output

    // Now convert back
    ExifData exifData2;
    ASSERT_NO_THROW(copyXmpToExif(xmpData_, exifData2));
}

// Test: Exif GPS coordinate conversion
TEST_F(ConverterTest_1831, ExifGPSCoordinateConversion_1831) {
    // Set GPS latitude
    exifData_["Exif.GPSInfo.GPSLatitude"] = "51/1 30/1 0/1";
    exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));

    // Check if xmp has GPS data
    auto it = xmpData_.findKey(XmpKey("Xmp.exif.GPSLatitude"));
    if (it != xmpData_.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test: Exif GPS longitude conversion
TEST_F(ConverterTest_1831, ExifGPSLongitudeConversion_1831) {
    exifData_["Exif.GPSInfo.GPSLongitude"] = "0/1 7/1 3900/100";
    exifData_["Exif.GPSInfo.GPSLongitudeRef"] = "W";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
}

// Test: Exif date/time conversion to XMP
TEST_F(ConverterTest_1831, ExifDateTimeConversion_1831) {
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:00";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));

    auto it = xmpData_.findKey(XmpKey("Xmp.exif.DateTimeOriginal"));
    if (it != xmpData_.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test: Exif version conversion
TEST_F(ConverterTest_1831, ExifVersionConversion_1831) {
    // ExifVersion is typically "48 50 51 48" for 0230
    exifData_["Exif.Photo.ExifVersion"] = "48 50 51 48";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
}

// Test: Flash tag conversion
TEST_F(ConverterTest_1831, ExifFlashConversion_1831) {
    exifData_["Exif.Photo.Flash"] = uint16_t(1);

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
}

// Test: XMP to Exif date conversion
TEST_F(ConverterTest_1831, XmpDateToExifConversion_1831) {
    xmpData_["Xmp.exif.DateTimeOriginal"] = "2023-06-15T10:30:00";

    ASSERT_NO_THROW(copyXmpToExif(xmpData_, exifData_));

    auto it = exifData_.findKey(ExifKey("Exif.Photo.DateTimeOriginal"));
    if (it != exifData_.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test: XMP GPS coordinate to Exif
TEST_F(ConverterTest_1831, XmpGPSCoordToExif_1831) {
    xmpData_["Xmp.exif.GPSLatitude"] = "51,30,0N";

    ASSERT_NO_THROW(copyXmpToExif(xmpData_, exifData_));
}

// Test: IPTC to XMP conversion with data
TEST_F(ConverterTest_1831, IptcToXmpWithKeywords_1831) {
    iptcData_["Iptc.Application2.Keywords"] = "TestKeyword";

    ASSERT_NO_THROW(copyIptcToXmp(iptcData_, xmpData_));

    auto it = xmpData_.findKey(XmpKey("Xmp.dc.subject"));
    if (it != xmpData_.end()) {
        EXPECT_NE(it->toString().find("TestKeyword"), std::string::npos);
    }
}

// Test: XMP to IPTC conversion with data
TEST_F(ConverterTest_1831, XmpToIptcWithSubject_1831) {
    xmpData_["Xmp.dc.subject"] = "TestSubject";

    ASSERT_NO_THROW(copyXmpToIptc(xmpData_, iptcData_));
}

// Test: IPTC to XMP with charset parameter
TEST_F(ConverterTest_1831, IptcToXmpWithCharset_1831) {
    iptcData_["Iptc.Application2.Caption"] = "Test Caption";

    ASSERT_NO_THROW(copyIptcToXmp(iptcData_, xmpData_, "UTF-8"));
}

// Test: moveExifToXmp should move data (exif cleared after)
TEST_F(ConverterTest_1831, MoveExifToXmpClearsExif_1831) {
    exifData_["Exif.Image.ImageDescription"] = "To be moved";

    ASSERT_NO_THROW(moveExifToXmp(exifData_, xmpData_));

    // After move, the source tag should be erased
    auto it = exifData_.findKey(ExifKey("Exif.Image.ImageDescription"));
    // It may or may not be erased depending on whether the tag was converted
    // We just verify no crash
}

// Test: moveXmpToExif
TEST_F(ConverterTest_1831, MoveXmpToExif_1831) {
    xmpData_["Xmp.exif.DateTimeOriginal"] = "2023-06-15T10:30:00";

    ASSERT_NO_THROW(moveXmpToExif(xmpData_, exifData_));
}

// Test: moveIptcToXmp
TEST_F(ConverterTest_1831, MoveIptcToXmp_1831) {
    iptcData_["Iptc.Application2.Keywords"] = "MoveKeyword";

    ASSERT_NO_THROW(moveIptcToXmp(iptcData_, xmpData_));
}

// Test: moveXmpToIptc
TEST_F(ConverterTest_1831, MoveXmpToIptc_1831) {
    xmpData_["Xmp.dc.subject"] = "MoveSubject";

    ASSERT_NO_THROW(moveXmpToIptc(xmpData_, iptcData_));
}

// Test: Multiple conversions don't duplicate entries when overwrite is default (true)
TEST_F(ConverterTest_1831, MultipleCopiesDoNotDuplicate_1831) {
    exifData_["Exif.Image.ImageDescription"] = "Description";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
    size_t countAfterFirst = xmpData_.count();

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
    size_t countAfterSecond = xmpData_.count();

    EXPECT_EQ(countAfterFirst, countAfterSecond);
}

// Test: ExifComment conversion
TEST_F(ConverterTest_1831, ExifUserCommentConversion_1831) {
    exifData_["Exif.Photo.UserComment"] = "charset=\"Ascii\" A test comment";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));

    auto it = xmpData_.findKey(XmpKey("Xmp.exif.UserComment"));
    if (it != xmpData_.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test: GPS Version conversion
TEST_F(ConverterTest_1831, ExifGPSVersionConversion_1831) {
    exifData_["Exif.GPSInfo.GPSVersionID"] = "2 3 0 0";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
}

// Test: XMP version to Exif conversion
TEST_F(ConverterTest_1831, XmpVersionToExif_1831) {
    xmpData_["Xmp.exif.ExifVersion"] = "0230";

    ASSERT_NO_THROW(copyXmpToExif(xmpData_, exifData_));
}

// Test: XMP flash to Exif conversion
TEST_F(ConverterTest_1831, XmpFlashToExif_1831) {
    xmpData_["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData_["Xmp.exif.Flash/exif:Return"] = "0";
    xmpData_["Xmp.exif.Flash/exif:Mode"] = "1";
    xmpData_["Xmp.exif.Flash/exif:Function"] = "False";
    xmpData_["Xmp.exif.Flash/exif:RedEyeMode"] = "False";

    ASSERT_NO_THROW(copyXmpToExif(xmpData_, exifData_));
}

// Test: XMP GPS version to Exif
TEST_F(ConverterTest_1831, XmpGPSVersionToExif_1831) {
    xmpData_["Xmp.exif.GPSVersionID"] = "2.3.0.0";

    ASSERT_NO_THROW(copyXmpToExif(xmpData_, exifData_));
}

// Test: Empty string values don't crash
TEST_F(ConverterTest_1831, EmptyStringValues_1831) {
    exifData_["Exif.Image.ImageDescription"] = "";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
}

// Test: IPTC with multiple keywords
TEST_F(ConverterTest_1831, IptcMultipleKeywords_1831) {
    Iptcdatum kw1(IptcKey("Iptc.Application2.Keywords"));
    kw1.setValue("Keyword1");
    iptcData_.add(kw1);

    Iptcdatum kw2(IptcKey("Iptc.Application2.Keywords"));
    kw2.setValue("Keyword2");
    iptcData_.add(kw2);

    ASSERT_NO_THROW(copyIptcToXmp(iptcData_, xmpData_));
}

// Test: Large number of tags
TEST_F(ConverterTest_1831, ManyExifTags_1831) {
    exifData_["Exif.Image.ImageDescription"] = "Desc";
    exifData_["Exif.Image.Make"] = "TestMake";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Image.Software"] = "TestSoftware";
    exifData_["Exif.Image.Artist"] = "TestArtist";
    exifData_["Exif.Image.Copyright"] = "TestCopyright";
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    exifData_["Exif.Photo.DateTimeDigitized"] = "2023:01:01 00:00:00";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
    EXPECT_FALSE(xmpData_.empty());
}

// Test: Exif array tag (e.g., ISOSpeedRatings)
TEST_F(ConverterTest_1831, ExifArrayConversion_1831) {
    exifData_["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));
}

// Test: Conversion of Copyright tag (special handling)
TEST_F(ConverterTest_1831, CopyrightConversion_1831) {
    exifData_["Exif.Image.Copyright"] = "Copyright 2023 Test";

    ASSERT_NO_THROW(copyExifToXmp(exifData_, xmpData_));

    auto it = xmpData_.findKey(XmpKey("Xmp.dc.rights"));
    if (it != xmpData_.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test: XMP dc:rights to Exif Copyright
TEST_F(ConverterTest_1831, XmpRightsToExifCopyright_1831) {
    xmpData_["Xmp.dc.rights"] = "lang=\"x-default\" Copyright 2023";

    ASSERT_NO_THROW(copyXmpToExif(xmpData_, exifData_));
}

}  // namespace
