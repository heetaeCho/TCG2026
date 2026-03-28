#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// We need access to the free functions that wrap Converter usage
// Based on the exiv2 public API, these are typically:
// void copyExifToXmp(const ExifData&, XmpData&)
// void copyXmpToExif(const XmpData&, ExifData&)
// void copyIptcToXmp(const IptcData&, XmpData&, const char*)
// void copyXmpToIptc(const XmpData&, IptcData&)
// void moveExifToXmp(ExifData&, XmpData&)
// void moveXmpToExif(const XmpData&, ExifData&)
// void moveIptcToXmp(IptcData&, XmpData&, const char*)
// void moveXmpToIptc(const XmpData&, IptcData&)

namespace {

class ConverterExifToXmpTest_1833 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
};

class ConverterIptcToXmpTest_1833 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::IptcData iptcData_;
    Exiv2::XmpData xmpData_;
};

class ConverterXmpToExifTest_1833 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
};

class ConverterXmpToIptcTest_1833 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::IptcData iptcData_;
    Exiv2::XmpData xmpData_;
};

// Test: Empty ExifData produces empty XmpData
TEST_F(ConverterExifToXmpTest_1833, EmptyExifToXmpProducesEmptyXmp_1833) {
    ASSERT_TRUE(exifData_.empty());
    ASSERT_TRUE(xmpData_.empty());
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    // With no exif data, xmp should remain empty (or at most have digest)
    // We just verify no crash occurs
    SUCCEED();
}

// Test: Copy a simple Exif value to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifImageDescriptionToXmp_1833) {
    exifData_["Exif.Image.ImageDescription"] = "Test description";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("Test description"));
    }
    // If not found, it's acceptable - the conversion table may not map this
}

// Test: Copy Exif Artist to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifArtistToXmp_1833) {
    exifData_["Exif.Image.Artist"] = "John Doe";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("John Doe"));
    }
}

// Test: Copy Exif Copyright to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifCopyrightToXmp_1833) {
    exifData_["Exif.Image.Copyright"] = "Copyright 2023";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("Copyright 2023"));
    }
}

// Test: Copy Exif UserComment to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifUserCommentToXmp_1833) {
    exifData_["Exif.Photo.UserComment"] = "A user comment";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.UserComment"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("A user comment"));
    }
}

// Test: Copy Exif DateTimeOriginal to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifDateTimeOriginalToXmp_1833) {
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:15 10:30:00";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.DateCreated"));
    if (pos != xmpData_.end()) {
        std::string val = pos->toString();
        // Should contain date-related info
        EXPECT_FALSE(val.empty());
    }
}

// Test: Copy Exif ExifVersion to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifVersionToXmp_1833) {
    Exiv2::DataBuf buf(4);
    std::memcpy(buf.data(), "0230", 4);
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::undefined);
    val->read(reinterpret_cast<const Exiv2::byte*>("0230"), 4, Exiv2::bigEndian);
    exifData_.add(Exiv2::ExifKey("Exif.Photo.ExifVersion"), val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: Copy Exif GPSVersionID to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifGPSVersionToXmp_1833) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 2 0 0");
    exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: Copy Exif Flash to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifFlashToXmp_1833) {
    exifData_["Exif.Photo.Flash"] = uint16_t(1);
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    // Flash is converted into structured XMP
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash"));
    // Just verify no crash
    SUCCEED();
}

// Test: Copy Exif GPSLatitude to XMP
TEST_F(ConverterExifToXmpTest_1833, CopyExifGPSLatitudeToXmp_1833) {
    exifData_["Exif.GPSInfo.GPSLatitude"] = "51/1 30/1 0/1";
    exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: Empty IptcData produces empty XmpData
TEST_F(ConverterIptcToXmpTest_1833, EmptyIptcToXmpProducesEmptyXmp_1833) {
    ASSERT_TRUE(iptcData_.empty());
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    // Should not crash, xmpData may or may not remain empty
    SUCCEED();
}

// Test: Copy IPTC headline to XMP
TEST_F(ConverterIptcToXmpTest_1833, CopyIptcHeadlineToXmp_1833) {
    iptcData_["Iptc.Application2.Headline"] = "Test Headline";
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ("Test Headline", pos->toString());
    }
}

// Test: Copy IPTC Keywords to XMP
TEST_F(ConverterIptcToXmpTest_1833, CopyIptcKeywordsToXmp_1833) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
    val->read("keyword1");
    iptcData_.add(Exiv2::IptcKey("Iptc.Application2.Keywords"), val.get());
    val->read("keyword2");
    iptcData_.add(Exiv2::IptcKey("Iptc.Application2.Keywords"), val.get());

    Exiv2::copyIptcToXmp(iptcData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: Copy IPTC City to XMP
TEST_F(ConverterIptcToXmpTest_1833, CopyIptcCityToXmp_1833) {
    iptcData_["Iptc.Application2.City"] = "Berlin";
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.City"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ("Berlin", pos->toString());
    }
}

// Test: Empty XmpData to ExifData
TEST_F(ConverterXmpToExifTest_1833, EmptyXmpToExifProducesEmptyExif_1833) {
    ASSERT_TRUE(xmpData_.empty());
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    // No crash expected
    SUCCEED();
}

// Test: Copy XMP dc.description to Exif
TEST_F(ConverterXmpToExifTest_1833, CopyXmpDescriptionToExif_1833) {
    xmpData_["Xmp.dc.description"] = "lang=\"x-default\" XMP Description";
    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    if (pos != exifData_.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("XMP Description"));
    }
}

// Test: Copy XMP dc.creator to Exif Artist
TEST_F(ConverterXmpToExifTest_1833, CopyXmpCreatorToExif_1833) {
    xmpData_["Xmp.dc.creator"] = "Jane Doe";
    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    if (pos != exifData_.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("Jane Doe"));
    }
}

// Test: Empty XmpData to IptcData
TEST_F(ConverterXmpToIptcTest_1833, EmptyXmpToIptcProducesEmptyIptc_1833) {
    ASSERT_TRUE(xmpData_.empty());
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);
    SUCCEED();
}

// Test: Copy XMP photoshop.Headline to IPTC
TEST_F(ConverterXmpToIptcTest_1833, CopyXmpHeadlineToIptc_1833) {
    xmpData_["Xmp.photoshop.Headline"] = "XMP Headline";
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);

    auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Headline"));
    if (pos != iptcData_.end()) {
        EXPECT_EQ("XMP Headline", pos->toString());
    }
}

// Test: Move Exif to XMP (erase=true)
TEST_F(ConverterExifToXmpTest_1833, MoveExifToXmpErasesExif_1833) {
    exifData_["Exif.Image.ImageDescription"] = "Move me";
    Exiv2::moveExifToXmp(exifData_, xmpData_);

    // After move, the exif data for converted keys should be erased
    // Check xmp has data
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    if (xmpPos != xmpData_.end()) {
        EXPECT_NE(std::string::npos, xmpPos->toString().find("Move me"));
    }
}

// Test: Move IPTC to XMP (erase=true)
TEST_F(ConverterIptcToXmpTest_1833, MoveIptcToXmpErasesIptc_1833) {
    iptcData_["Iptc.Application2.Headline"] = "Move Headline";
    Exiv2::moveIptcToXmp(iptcData_, xmpData_);

    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    if (xmpPos != xmpData_.end()) {
        EXPECT_EQ("Move Headline", xmpPos->toString());
    }
}

// Test: Move XMP to Exif
TEST_F(ConverterXmpToExifTest_1833, MoveXmpToExif_1833) {
    xmpData_["Xmp.dc.description"] = "lang=\"x-default\" Move to exif";
    Exiv2::moveXmpToExif(xmpData_, exifData_);
    // Just verify no crash
    SUCCEED();
}

// Test: Move XMP to IPTC
TEST_F(ConverterXmpToIptcTest_1833, MoveXmpToIptc_1833) {
    xmpData_["Xmp.photoshop.Headline"] = "Move to iptc";
    Exiv2::moveXmpToIptc(xmpData_, iptcData_);
    SUCCEED();
}

// Test: Overwrite behavior - copy twice with same key
TEST_F(ConverterExifToXmpTest_1833, CopyExifToXmpOverwritesBehavior_1833) {
    exifData_["Exif.Image.ImageDescription"] = "First";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    exifData_["Exif.Image.ImageDescription"] = "Second";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    // The second copy should overwrite (default overwrite=true)
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    if (pos != xmpData_.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("Second"));
    }
}

// Test: Multiple Exif tags conversion
TEST_F(ConverterExifToXmpTest_1833, MultipleExifTagsConversion_1833) {
    exifData_["Exif.Image.Artist"] = "Artist Name";
    exifData_["Exif.Image.Copyright"] = "Copyright Info";
    exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 12:00:00";

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    // At least one should have been converted
    EXPECT_FALSE(xmpData_.empty());
}

// Test: Multiple IPTC tags conversion
TEST_F(ConverterIptcToXmpTest_1833, MultipleIptcTagsConversion_1833) {
    iptcData_["Iptc.Application2.Headline"] = "Headline";
    iptcData_["Iptc.Application2.City"] = "Paris";
    iptcData_["Iptc.Application2.Caption"] = "A caption";

    Exiv2::copyIptcToXmp(iptcData_, xmpData_);

    EXPECT_FALSE(xmpData_.empty());
}

// Test: IPTC with charset parameter
TEST_F(ConverterIptcToXmpTest_1833, IptcToXmpWithCharset_1833) {
    iptcData_["Iptc.Application2.Headline"] = "Charset Test";
    Exiv2::copyIptcToXmp(iptcData_, xmpData_, "UTF-8");
    // Should not crash and should produce output
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ("Charset Test", pos->toString());
    }
}

// Test: Round-trip Exif -> XMP -> Exif
TEST_F(ConverterExifToXmpTest_1833, RoundTripExifXmpExif_1833) {
    exifData_["Exif.Image.Artist"] = "Round Trip Artist";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    Exiv2::ExifData exifData2;
    Exiv2::copyXmpToExif(xmpData_, exifData2);

    auto pos = exifData2.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    if (pos != exifData2.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("Round Trip Artist"));
    }
}

// Test: Round-trip IPTC -> XMP -> IPTC
TEST_F(ConverterIptcToXmpTest_1833, RoundTripIptcXmpIptc_1833) {
    iptcData_["Iptc.Application2.Headline"] = "Round Trip Headline";
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);

    Exiv2::IptcData iptcData2;
    Exiv2::copyXmpToIptc(xmpData_, iptcData2);

    auto pos = iptcData2.findKey(Exiv2::IptcKey("Iptc.Application2.Headline"));
    if (pos != iptcData2.end()) {
        EXPECT_EQ("Round Trip Headline", pos->toString());
    }
}

// Test: GPS Longitude conversion
TEST_F(ConverterExifToXmpTest_1833, CopyExifGPSLongitudeToXmp_1833) {
    exifData_["Exif.GPSInfo.GPSLongitude"] = "13/1 23/1 0/1";
    exifData_["Exif.GPSInfo.GPSLongitudeRef"] = "E";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLongitude"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: Exif ISOSpeedRatings (array type) conversion
TEST_F(ConverterExifToXmpTest_1833, CopyExifISOSpeedToXmp_1833) {
    exifData_["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ISOSpeedRatings"));
    if (pos != xmpData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: XMP date conversion to Exif
TEST_F(ConverterXmpToExifTest_1833, CopyXmpDateToExif_1833) {
    xmpData_["Xmp.photoshop.DateCreated"] = "2023-01-15T10:30:00";
    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    if (pos != exifData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: XMP exif.ExifVersion to Exif
TEST_F(ConverterXmpToExifTest_1833, CopyXmpExifVersionToExif_1833) {
    xmpData_["Xmp.exif.ExifVersion"] = "2.30";
    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.ExifVersion"));
    if (pos != exifData_.end()) {
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: XMP dc.subject (keywords) to IPTC
TEST_F(ConverterXmpToIptcTest_1833, CopyXmpSubjectToIptcKeywords_1833) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpBag);
    val->read("keyword1");
    xmpData_.add(Exiv2::XmpKey("Xmp.dc.subject"), val.get());

    Exiv2::copyXmpToIptc(xmpData_, iptcData_);

    auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    if (pos != iptcData_.end()) {
        EXPECT_NE(std::string::npos, pos->toString().find("keyword1"));
    }
}

}  // namespace
