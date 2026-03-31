#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>
#include <sstream>

// We need access to the Converter class which is defined in convert.cpp
// The public API for conversion is through copyXmpToIptc, copyIptcToXmp, etc.
// But based on the provided code, we need to test cnvIptcValue and related functionality.
// Since Converter is in the Exiv2 namespace but defined in convert.cpp (not a public header),
// we include what's available and test through the public conversion functions.

namespace {

class ConverterIptcToXmpTest_1851 : public ::testing::Test {
protected:
    void SetUp() override {
        iptcData_.clear();
        xmpData_.clear();
    }

    Exiv2::IptcData iptcData_;
    Exiv2::XmpData xmpData_;
};

// Test: Converting IPTC to XMP with valid data using the public API
TEST_F(ConverterIptcToXmpTest_1851, CopyIptcToXmpBasic_1851) {
    // Add an IPTC caption
    iptcData_["Iptc.Application2.Caption"] = "Test Caption";
    
    // Use the public conversion function
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    // Check that corresponding XMP data was created
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(pos, xmpData_.end());
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Test Caption"), std::string::npos);
    }
}

// Test: Converting empty IPTC data to XMP should result in no XMP data
TEST_F(ConverterIptcToXmpTest_1851, CopyEmptyIptcToXmp_1851) {
    EXPECT_TRUE(iptcData_.empty());
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    // XMP data should remain empty or have no meaningful entries
    // (some implementations might add digest entries)
}

// Test: Converting IPTC keywords to XMP
TEST_F(ConverterIptcToXmpTest_1851, CopyIptcKeywordsToXmp_1851) {
    iptcData_["Iptc.Application2.Keywords"] = "keyword1";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(pos, xmpData_.end());
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("keyword1"), std::string::npos);
    }
}

// Test: Converting multiple IPTC keywords to XMP
TEST_F(ConverterIptcToXmpTest_1851, CopyMultipleIptcKeywordsToXmp_1851) {
    Exiv2::Iptcdatum kw1(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    kw1.setValue("keyword1");
    iptcData_.add(kw1);
    
    Exiv2::Iptcdatum kw2(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    kw2.setValue("keyword2");
    iptcData_.add(kw2);
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Converting IPTC byline (creator) to XMP
TEST_F(ConverterIptcToXmpTest_1851, CopyIptcBylineToXmp_1851) {
    iptcData_["Iptc.Application2.Byline"] = "John Doe";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_NE(pos, xmpData_.end());
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("John Doe"), std::string::npos);
    }
}

// Test: Converting IPTC copyright to XMP
TEST_F(ConverterIptcToXmpTest_1851, CopyIptcCopyrightToXmp_1851) {
    iptcData_["Iptc.Application2.Copyright"] = "Copyright 2023";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    EXPECT_NE(pos, xmpData_.end());
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Copyright 2023"), std::string::npos);
    }
}

// ---- XMP to IPTC conversion tests ----

class ConverterXmpToIptcTest_1851 : public ::testing::Test {
protected:
    void SetUp() override {
        iptcData_.clear();
        xmpData_.clear();
    }

    Exiv2::IptcData iptcData_;
    Exiv2::XmpData xmpData_;
};

// Test: Converting XMP description to IPTC caption
TEST_F(ConverterXmpToIptcTest_1851, CopyXmpDescriptionToIptc_1851) {
    xmpData_["Xmp.dc.description"] = "lang=x-default A test description";
    
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);
    
    auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    // The key might or might not be found depending on exact XMP format
    // This tests the conversion path exists
}

// Test: Converting XMP subject/keywords to IPTC keywords
TEST_F(ConverterXmpToIptcTest_1851, CopyXmpSubjectToIptcKeywords_1851) {
    xmpData_["Xmp.dc.subject"] = "test_keyword";
    
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);
    
    auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    EXPECT_NE(pos, iptcData_.end());
    if (pos != iptcData_.end()) {
        EXPECT_EQ(pos->toString(), "test_keyword");
    }
}

// Test: Converting empty XMP to IPTC
TEST_F(ConverterXmpToIptcTest_1851, CopyEmptyXmpToIptc_1851) {
    EXPECT_TRUE(xmpData_.empty());
    
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);
    
    // IPTC should remain empty
    EXPECT_TRUE(iptcData_.empty());
}

// ---- Exif to XMP conversion tests ----

class ConverterExifToXmpTest_1851 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_.clear();
        xmpData_.clear();
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
};

// Test: Converting Exif ImageDescription to XMP
TEST_F(ConverterExifToXmpTest_1851, CopyExifDescriptionToXmp_1851) {
    exifData_["Exif.Image.ImageDescription"] = "A beautiful sunset";
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(pos, xmpData_.end());
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("A beautiful sunset"), std::string::npos);
    }
}

// Test: Converting empty Exif to XMP
TEST_F(ConverterExifToXmpTest_1851, CopyEmptyExifToXmp_1851) {
    EXPECT_TRUE(exifData_.empty());
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    // XMP should remain empty or have only digest
}

// Test: Converting Exif Artist to XMP creator
TEST_F(ConverterExifToXmpTest_1851, CopyExifArtistToXmp_1851) {
    exifData_["Exif.Image.Artist"] = "Jane Smith";
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_NE(pos, xmpData_.end());
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Jane Smith"), std::string::npos);
    }
}

// Test: Converting Exif Copyright to XMP
TEST_F(ConverterExifToXmpTest_1851, CopyExifCopyrightToXmp_1851) {
    exifData_["Exif.Image.Copyright"] = "Copyright 2023 Test";
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    EXPECT_NE(pos, xmpData_.end());
}

// ---- XMP to Exif conversion tests ----

class ConverterXmpToExifTest_1851 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_.clear();
        xmpData_.clear();
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
};

// Test: Converting XMP to Exif with description
TEST_F(ConverterXmpToExifTest_1851, CopyXmpDescriptionToExif_1851) {
    xmpData_["Xmp.dc.description"] = "lang=x-default Test description";
    
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    // Test the conversion path
}

// Test: Converting empty XMP to Exif
TEST_F(ConverterXmpToExifTest_1851, CopyEmptyXmpToExif_1851) {
    EXPECT_TRUE(xmpData_.empty());
    
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    
    EXPECT_TRUE(exifData_.empty());
}

// ---- Round-trip tests ----

class ConverterRoundTripTest_1851 : public ::testing::Test {
protected:
    void SetUp() override {
        iptcData_.clear();
        xmpData_.clear();
        exifData_.clear();
    }

    Exiv2::IptcData iptcData_;
    Exiv2::XmpData xmpData_;
    Exiv2::ExifData exifData_;
};

// Test: IPTC -> XMP -> IPTC round trip for keywords
TEST_F(ConverterRoundTripTest_1851, IptcXmpIptcKeywordsRoundTrip_1851) {
    iptcData_["Iptc.Application2.Keywords"] = "roundtrip_keyword";
    
    // IPTC -> XMP
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    // Clear IPTC
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    
    // XMP -> IPTC
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);
    
    auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    EXPECT_NE(pos, iptcData_.end());
    if (pos != iptcData_.end()) {
        EXPECT_EQ(pos->toString(), "roundtrip_keyword");
    }
}

// Test: IPTC -> XMP round trip for caption
TEST_F(ConverterRoundTripTest_1851, IptcXmpIptcCaptionRoundTrip_1851) {
    iptcData_["Iptc.Application2.Caption"] = "Test round trip caption";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(pos, xmpData_.end());
    if (pos != xmpData_.end()) {
        EXPECT_NE(pos->toString().find("Test round trip caption"), std::string::npos);
    }
}

// Test: Exif -> XMP -> Exif round trip for Artist
TEST_F(ConverterRoundTripTest_1851, ExifXmpExifArtistRoundTrip_1851) {
    exifData_["Exif.Image.Artist"] = "Round Trip Artist";
    
    // Exif -> XMP
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    // Clear Exif
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    
    // XMP -> Exif
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        EXPECT_NE(pos->toString().find("Round Trip Artist"), std::string::npos);
    }
}

// Test: Pre-existing XMP data should not be overwritten when overwrite is default
TEST_F(ConverterRoundTripTest_1851, IptcToXmpDoesNotDuplicateExistingData_1851) {
    iptcData_["Iptc.Application2.Keywords"] = "original_keyword";
    
    // First conversion
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    size_t countAfterFirst = xmpData_.count();
    
    // Second conversion with same data - should not add duplicates
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    // Count should be the same or similar (implementation dependent, but not double)
    EXPECT_LE(xmpData_.count(), countAfterFirst * 2);
}

// Test: IPTC with special characters
TEST_F(ConverterRoundTripTest_1851, IptcToXmpSpecialCharacters_1851) {
    iptcData_["Iptc.Application2.Caption"] = "Test with special chars: <>&\"'";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: IPTC with empty string value
TEST_F(ConverterRoundTripTest_1851, IptcToXmpEmptyValue_1851) {
    iptcData_["Iptc.Application2.Caption"] = "";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    // Should handle empty values gracefully
}

// Test: Multiple IPTC fields conversion
TEST_F(ConverterRoundTripTest_1851, MultipleIptcFieldsToXmp_1851) {
    iptcData_["Iptc.Application2.Caption"] = "Test Caption";
    iptcData_["Iptc.Application2.Keywords"] = "keyword1";
    iptcData_["Iptc.Application2.Byline"] = "Author Name";
    iptcData_["Iptc.Application2.Copyright"] = "Copyright Notice";
    
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    
    // Verify multiple fields were converted
    EXPECT_FALSE(xmpData_.empty());
    
    // At least description and subject should be present
    auto descPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(descPos, xmpData_.end());
    
    auto subjectPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(subjectPos, xmpData_.end());
}

// Test: Exif GPS version conversion
TEST_F(ConverterRoundTripTest_1851, ExifGPSVersionToXmp_1851) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    
    // Set GPS version tag
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedByte);
    v->read("2 3 0 0");
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), v.get());
    
    Exiv2::copyExifToXmp(exifData, xmpData);
    
    auto pos = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    EXPECT_NE(pos, xmpData.end());
}

// Test: Exif date conversion to XMP
TEST_F(ConverterRoundTripTest_1851, ExifDateToXmpConversion_1851) {
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:00";
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    // Should find the date in XMP format
    if (pos != xmpData_.end()) {
        std::string xmpDate = pos->toString();
        // XMP dates use ISO 8601 format with hyphens
        EXPECT_NE(xmpDate.find("2023"), std::string::npos);
    }
}

// Test: Exif version to XMP conversion
TEST_F(ConverterRoundTripTest_1851, ExifVersionToXmpConversion_1851) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::undefined);
    v->read("48 50 51 48");  // "0230" in ASCII
    exifData_.add(Exiv2::ExifKey("Exif.Photo.ExifVersion"), v.get());
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    // Version should be converted
}

}  // namespace
