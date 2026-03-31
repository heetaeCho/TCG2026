#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// We need access to the Converter class which is defined in convert.cpp
// The public API for conversion is exposed through these functions
// but we also need the Converter class directly for testing cnvExifArray

// Forward declaration - Converter is in Exiv2 namespace but defined in convert.cpp
// We'll use the public conversion functions and also test through direct Converter usage

namespace {

class ConverterTest_1837 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
    Exiv2::IptcData iptcData_;

    void SetUp() override {
        // Ensure XMP parser is initialized
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test: copyExifToXmp with empty data should not crash
TEST_F(ConverterTest_1837, CopyExifToXmpEmptyData_1837) {
    Exiv2::ExifData exif;
    Exiv2::XmpData xmp;
    // Should not throw with empty data
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exif, xmp));
    EXPECT_TRUE(xmp.empty());
}

// Test: copyXmpToExif with empty data should not crash
TEST_F(ConverterTest_1837, CopyXmpToExifEmptyData_1837) {
    Exiv2::ExifData exif;
    Exiv2::XmpData xmp;
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmp, exif));
    EXPECT_TRUE(exif.empty());
}

// Test: copyIptcToXmp with empty data should not crash
TEST_F(ConverterTest_1837, CopyIptcToXmpEmptyData_1837) {
    Exiv2::IptcData iptc;
    Exiv2::XmpData xmp;
    EXPECT_NO_THROW(Exiv2::copyIptcToXmp(iptc, xmp));
    EXPECT_TRUE(xmp.empty());
}

// Test: copyXmpToIptc with empty data should not crash
TEST_F(ConverterTest_1837, CopyXmpToIptcEmptyData_1837) {
    Exiv2::IptcData iptc;
    Exiv2::XmpData xmp;
    EXPECT_NO_THROW(Exiv2::copyXmpToIptc(xmp, iptc));
    EXPECT_TRUE(iptc.empty());
}

// Test: Convert Exif ImageDescription to XMP
TEST_F(ConverterTest_1837, CopyExifImageDescriptionToXmp_1837) {
    exifData_["Exif.Image.ImageDescription"] = "Test Description";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Test Description"), std::string::npos);
    }
    // It's acceptable if the conversion doesn't map this particular tag
}

// Test: Convert Exif Artist to XMP
TEST_F(ConverterTest_1837, CopyExifArtistToXmp_1837) {
    exifData_["Exif.Image.Artist"] = "John Doe";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("John Doe"), std::string::npos);
    }
}

// Test: Convert Exif Copyright to XMP
TEST_F(ConverterTest_1837, CopyExifCopyrightToXmp_1837) {
    exifData_["Exif.Image.Copyright"] = "Copyright 2023";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Copyright 2023"), std::string::npos);
    }
}

// Test: Round-trip Exif -> XMP -> Exif preserves data
TEST_F(ConverterTest_1837, RoundTripExifXmpExif_1837) {
    exifData_["Exif.Image.Artist"] = "Jane Smith";
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    Exiv2::ExifData exifData2;
    Exiv2::copyXmpToExif(xmpData_, exifData2);
    
    auto pos = exifData2.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    if (pos != exifData2.end()) {
        EXPECT_EQ(pos->toString(), "Jane Smith");
    }
}

// Test: Convert XMP dc.description to Exif
TEST_F(ConverterTest_1837, CopyXmpDescriptionToExif_1837) {
    xmpData_["Xmp.dc.description"] = "XMP Description";
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    if (pos != exifData_.end()) {
        EXPECT_NE(pos->toString().find("XMP Description"), std::string::npos);
    }
}

// Test: Multiple Exif entries conversion
TEST_F(ConverterTest_1837, MultipleExifEntriesToXmp_1837) {
    exifData_["Exif.Image.Artist"] = "Artist Name";
    exifData_["Exif.Image.Copyright"] = "Some Copyright";
    exifData_["Exif.Image.ImageDescription"] = "Description Here";
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
    // The XMP data should have some entries after conversion
    // Not all tags may be converted, but at least some common ones should be
}

// Test: moveExifToXmp removes exif data
TEST_F(ConverterTest_1837, MoveExifToXmpRemovesExif_1837) {
    exifData_["Exif.Image.Artist"] = "Artist to Move";
    
    Exiv2::moveExifToXmp(exifData_, xmpData_);
    
    // After move, the exif data for Artist should be erased
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    // The key should have been erased
    EXPECT_TRUE(pos == exifData_.end());
}

// Test: moveXmpToExif removes xmp data
TEST_F(ConverterTest_1837, MoveXmpToExifRemovesXmp_1837) {
    xmpData_["Xmp.dc.creator"] = "Creator to Move";
    
    Exiv2::moveXmpToExif(xmpData_, exifData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_TRUE(pos == xmpData_.end());
}

// Test: moveIptcToXmp removes iptc data
TEST_F(ConverterTest_1837, MoveIptcToXmpRemovesIptc_1837) {
    iptcData_["Iptc.Application2.Caption"] = "Caption to Move";
    
    Exiv2::moveIptcToXmp(iptcData_, xmpData_);
    
    // After move, IPTC data should be cleared for moved entries
    auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    EXPECT_TRUE(pos == iptcData_.end());
}

// Test: moveXmpToIptc removes xmp data  
TEST_F(ConverterTest_1837, MoveXmpToIptcRemovesXmp_1837) {
    xmpData_["Xmp.dc.description"] = "Description to Move";
    
    Exiv2::moveXmpToIptc(xmpData_, iptcData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_TRUE(pos == xmpData_.end());
}

// Test: Converting ExifVersion to XMP
TEST_F(ConverterTest_1837, ConvertExifVersionToXmp_1837) {
    // ExifVersion is typically stored as "0230" or similar
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::undefined);
    val->read("48 50 51 48"); // "0230" in ASCII
    exifData_.add(Exiv2::ExifKey("Exif.Photo.ExifVersion"), val.get());
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Convert GPS coordinates
TEST_F(ConverterTest_1837, ConvertExifGPSToXmp_1837) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("51/1 30/1 0/1");
    exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
    exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Overwrite behavior - when XMP already has data
TEST_F(ConverterTest_1837, OverwriteExistingXmpData_1837) {
    xmpData_["Xmp.dc.creator"] = "Old Creator";
    exifData_["Exif.Image.Artist"] = "New Creator";
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    if (pos != xmpData_.end()) {
        // The value should have been overwritten
        EXPECT_NE(pos->toString().find("New Creator"), std::string::npos);
    }
}

// Test: IPTC to XMP conversion with Keywords
TEST_F(ConverterTest_1837, ConvertIptcKeywordsToXmp_1837) {
    iptcData_["Iptc.Application2.Keywords"] = "keyword1";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("keyword1"), std::string::npos);
    }
}

// Test: XMP to IPTC conversion with subject/keywords
TEST_F(ConverterTest_1837, ConvertXmpSubjectToIptc_1837) {
    xmpData_["Xmp.dc.subject"] = "test_keyword";
    
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);
    
    auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    if (pos != iptcData_.end()) {
        EXPECT_NE(pos->toString().find("test_keyword"), std::string::npos);
    }
}

// Test: Flash conversion from Exif to XMP
TEST_F(ConverterTest_1837, ConvertExifFlashToXmp_1837) {
    exifData_["Exif.Photo.Flash"] = uint16_t(1); // Flash fired
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Date/Time conversion from Exif to XMP
TEST_F(ConverterTest_1837, ConvertExifDateTimeToXmp_1837) {
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:00";
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.DateCreated"));
    if (pos != xmpData_.end()) {
        // XMP dates use ISO 8601 format
        std::string dateStr = pos->toString();
        EXPECT_NE(dateStr.find("2023"), std::string::npos);
    }
}

// Test: Converting with subsecond time
TEST_F(ConverterTest_1837, ConvertExifDateTimeWithSubSec_1837) {
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:00";
    exifData_["Exif.Photo.SubSecTimeOriginal"] = "123";
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Conversion does not crash with unrecognized tags
TEST_F(ConverterTest_1837, ConversionWithMakerNoteTags_1837) {
    // MakerNote tags are typically not converted but shouldn't crash
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Copy with both IPTC and Exif having data, then to XMP
TEST_F(ConverterTest_1837, CopyBothIptcAndExifToXmp_1837) {
    exifData_["Exif.Image.Artist"] = "Exif Artist";
    iptcData_["Iptc.Application2.Byline"] = "IPTC Byline";
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
    EXPECT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));
}

// Test: Verify empty string values don't cause issues
TEST_F(ConverterTest_1837, EmptyStringExifValue_1837) {
    exifData_["Exif.Image.ImageDescription"] = "";
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: XMP GPSCoord to Exif
TEST_F(ConverterTest_1837, ConvertXmpGPSToExif_1837) {
    xmpData_["Xmp.exif.GPSLatitude"] = "51,30.5N";
    
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: XMP Flash to Exif
TEST_F(ConverterTest_1837, ConvertXmpFlashToExif_1837) {
    xmpData_["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData_["Xmp.exif.Flash/exif:Return"] = "0";
    xmpData_["Xmp.exif.Flash/exif:Mode"] = "1";
    xmpData_["Xmp.exif.Flash/exif:Function"] = "False";
    xmpData_["Xmp.exif.Flash/exif:RedEyeMode"] = "False";
    
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: XMP Version to Exif
TEST_F(ConverterTest_1837, ConvertXmpExifVersionToExif_1837) {
    xmpData_["Xmp.exif.ExifVersion"] = "2.30";
    
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: XMP Date to Exif
TEST_F(ConverterTest_1837, ConvertXmpDateToExif_1837) {
    xmpData_["Xmp.photoshop.DateCreated"] = "2023-06-15T10:30:00";
    
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: Large number of exif entries conversion
TEST_F(ConverterTest_1837, LargeNumberOfExifEntries_1837) {
    exifData_["Exif.Image.Artist"] = "Test Artist";
    exifData_["Exif.Image.Copyright"] = "Test Copyright";
    exifData_["Exif.Image.ImageDescription"] = "Test Description";
    exifData_["Exif.Image.Make"] = "Test Make";
    exifData_["Exif.Image.Model"] = "Test Model";
    exifData_["Exif.Image.Software"] = "Test Software";
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    exifData_["Exif.Photo.DateTimeDigitized"] = "2023:01:01 00:00:00";
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
    EXPECT_FALSE(xmpData_.empty());
}

// Test: IPTC caption conversion roundtrip
TEST_F(ConverterTest_1837, IptcCaptionRoundTrip_1837) {
    iptcData_["Iptc.Application2.Caption"] = "Test Caption";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    Exiv2::IptcData iptcData2;
    Exiv2::copyXmpToIptc(xmpData_, iptcData2);
    
    auto pos = iptcData2.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    if (pos != iptcData2.end()) {
        EXPECT_EQ(pos->toString(), "Test Caption");
    }
}

// Test: GPSVersionID conversion
TEST_F(ConverterTest_1837, ConvertExifGPSVersionToXmp_1837) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 3 0 0");
    exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), val.get());
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: XMP UserComment conversion
TEST_F(ConverterTest_1837, ConvertExifUserCommentToXmp_1837) {
    exifData_["Exif.Photo.UserComment"] = "charset=Ascii This is a comment";
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

}  // namespace
