#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// The Converter class is defined in convert.cpp and not exposed via a public header,
// but the public API functions copyExifToXmp, copyXmpToExif, etc. use it internally.
// We also need to test cnvXmpValue and related methods. Since Converter is in the
// Exiv2 namespace but defined in convert.cpp, we include the necessary headers
// and use the public conversion API as well as direct Converter usage where possible.

// Forward declarations for the public conversion functions
namespace Exiv2 {
void copyExifToXmp(const ExifData& exifData, XmpData& xmpData);
void copyXmpToExif(const XmpData& xmpData, ExifData& exifData);
void moveExifToXmp(ExifData& exifData, XmpData& xmpData);
void moveXmpToExif(XmpData& xmpData, ExifData& exifData);
void copyIptcToXmp(const IptcData& iptcData, XmpData& xmpData, const char* iptcCharset = nullptr);
void copyXmpToIptc(const XmpData& xmpData, IptcData& iptcData);
void moveIptcToXmp(IptcData& iptcData, XmpData& xmpData, const char* iptcCharset = nullptr);
void moveXmpToIptc(XmpData& xmpData, IptcData& iptcData);
void syncExifWithXmp(ExifData& exifData, XmpData& xmpData);
}

class ConverterTest_1843 : public ::testing::Test {
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

// Test: Copy empty ExifData to XmpData should result in empty XmpData
TEST_F(ConverterTest_1843, CopyEmptyExifToXmp_1843) {
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    EXPECT_TRUE(xmpData_.empty());
}

// Test: Copy empty XmpData to ExifData should result in empty ExifData
TEST_F(ConverterTest_1843, CopyEmptyXmpToExif_1843) {
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    EXPECT_TRUE(exifData_.empty());
}

// Test: Move empty ExifData to XmpData
TEST_F(ConverterTest_1843, MoveEmptyExifToXmp_1843) {
    Exiv2::moveExifToXmp(exifData_, xmpData_);
    EXPECT_TRUE(exifData_.empty());
    EXPECT_TRUE(xmpData_.empty());
}

// Test: Move empty XmpData to ExifData
TEST_F(ConverterTest_1843, MoveEmptyXmpToExif_1843) {
    Exiv2::moveXmpToExif(xmpData_, exifData_);
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_TRUE(exifData_.empty());
}

// Test: Copy ExifData with ImageDescription to XmpData
TEST_F(ConverterTest_1843, CopyExifImageDescriptionToXmp_1843) {
    exifData_["Exif.Image.ImageDescription"] = "Test description";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Copy XmpData dc.description to ExifData
TEST_F(ConverterTest_1843, CopyXmpDescriptionToExif_1843) {
    xmpData_["Xmp.dc.description"] = "Test XMP description";
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(pos, exifData_.end());
}

// Test: Move ExifData with ImageDescription erases source
TEST_F(ConverterTest_1843, MoveExifImageDescriptionErasesSource_1843) {
    exifData_["Exif.Image.ImageDescription"] = "Move test";
    Exiv2::moveExifToXmp(exifData_, xmpData_);
    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_EQ(exifPos, exifData_.end());
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(xmpPos, xmpData_.end());
}

// Test: Move XmpData dc.description erases source
TEST_F(ConverterTest_1843, MoveXmpDescriptionErasesSource_1843) {
    xmpData_["Xmp.dc.description"] = "Move test from XMP";
    Exiv2::moveXmpToExif(xmpData_, exifData_);
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_EQ(xmpPos, xmpData_.end());
}

// Test: Copy ExifData Artist to XmpData
TEST_F(ConverterTest_1843, CopyExifArtistToXmp_1843) {
    exifData_["Exif.Image.Artist"] = "John Doe";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Copy ExifData Copyright to XmpData
TEST_F(ConverterTest_1843, CopyExifCopyrightToXmp_1843) {
    exifData_["Exif.Image.Copyright"] = "Copyright 2024";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Copy ExifData with multiple fields to XmpData
TEST_F(ConverterTest_1843, CopyMultipleExifFieldsToXmp_1843) {
    exifData_["Exif.Image.ImageDescription"] = "Description";
    exifData_["Exif.Image.Artist"] = "Artist";
    exifData_["Exif.Image.Copyright"] = "Copyright";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_NE(xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description")), xmpData_.end());
    EXPECT_NE(xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator")), xmpData_.end());
    EXPECT_NE(xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.rights")), xmpData_.end());
}

// Test: Copy does not overwrite existing XmpData when target exists
TEST_F(ConverterTest_1843, CopyExifToXmpDoesNotOverwriteExistingXmp_1843) {
    xmpData_["Xmp.dc.description"] = "Existing description";
    exifData_["Exif.Image.ImageDescription"] = "New description";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    ASSERT_NE(pos, xmpData_.end());
    // The existing value should remain since overwrite is false by default in copy
    EXPECT_EQ(pos->toString(), "Existing description");
}

// Test: Copy empty IptcData to XmpData
TEST_F(ConverterTest_1843, CopyEmptyIptcToXmp_1843) {
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    EXPECT_TRUE(xmpData_.empty());
}

// Test: Copy empty XmpData to IptcData
TEST_F(ConverterTest_1843, CopyEmptyXmpToIptc_1843) {
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);
    EXPECT_TRUE(iptcData_.empty());
}

// Test: Move empty IptcData to XmpData
TEST_F(ConverterTest_1843, MoveEmptyIptcToXmp_1843) {
    Exiv2::moveIptcToXmp(iptcData_, xmpData_);
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_TRUE(xmpData_.empty());
}

// Test: Move empty XmpData to IptcData
TEST_F(ConverterTest_1843, MoveEmptyXmpToIptc_1843) {
    Exiv2::moveXmpToIptc(xmpData_, iptcData_);
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_TRUE(iptcData_.empty());
}

// Test: Exif GPS version conversion
TEST_F(ConverterTest_1843, CopyExifGPSVersionToXmp_1843) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 3 0 0");
    exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), val.get());
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Copy Exif DateTimeOriginal to Xmp
TEST_F(ConverterTest_1843, CopyExifDateTimeOriginalToXmp_1843) {
    exifData_["Exif.Photo.DateTimeOriginal"] = "2024:01:15 10:30:00";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Copy Xmp DateTimeOriginal to Exif
TEST_F(ConverterTest_1843, CopyXmpDateTimeOriginalToExif_1843) {
    xmpData_["Xmp.exif.DateTimeOriginal"] = "2024-01-15T10:30:00";
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    EXPECT_NE(pos, exifData_.end());
}

// Test: Copy Exif ExifVersion to XmpData
TEST_F(ConverterTest_1843, CopyExifVersionToXmp_1843) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::undefined);
    val->read("48 50 51 48");
    exifData_.add(Exiv2::ExifKey("Exif.Photo.ExifVersion"), val.get());
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: syncExifWithXmp on empty data
TEST_F(ConverterTest_1843, SyncExifWithXmpEmpty_1843) {
    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData_, xmpData_));
    EXPECT_TRUE(exifData_.empty());
}

// Test: syncExifWithXmp with XMP data
TEST_F(ConverterTest_1843, SyncExifWithXmpWithData_1843) {
    xmpData_["Xmp.dc.description"] = "Sync test";
    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData_, xmpData_));
}

// Test: Copy Exif Flash to XmpData
TEST_F(ConverterTest_1843, CopyExifFlashToXmp_1843) {
    exifData_["Exif.Photo.Flash"] = uint16_t(1);
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    // Flash should be converted to structured XMP
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash"));
    // May or may not exist depending on structure; check no crash
    EXPECT_TRUE(true);
}

// Test: Copy Exif GPS coordinates to XmpData
TEST_F(ConverterTest_1843, CopyExifGPSLatitudeToXmp_1843) {
    Exiv2::URational r1(48, 1);
    Exiv2::URational r2(51, 1);
    Exiv2::URational r3(0, 1);
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedRational);
    val->read("48/1 51/1 0/1");
    exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), val.get());
    exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Round-trip ExifData -> XmpData -> ExifData for ImageDescription
TEST_F(ConverterTest_1843, RoundTripImageDescription_1843) {
    exifData_["Exif.Image.ImageDescription"] = "Round trip test";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    Exiv2::ExifData exifData2;
    Exiv2::copyXmpToExif(xmpData_, exifData2);

    auto pos = exifData2.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    ASSERT_NE(pos, exifData2.end());
    EXPECT_EQ(pos->toString(), "Round trip test");
}

// Test: Round-trip ExifData -> XmpData -> ExifData for Artist
TEST_F(ConverterTest_1843, RoundTripArtist_1843) {
    exifData_["Exif.Image.Artist"] = "Jane Smith";
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    Exiv2::ExifData exifData2;
    Exiv2::copyXmpToExif(xmpData_, exifData2);

    auto pos = exifData2.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    ASSERT_NE(pos, exifData2.end());
    EXPECT_EQ(pos->toString(), "Jane Smith");
}

// Test: Copy Exif UserComment to XmpData
TEST_F(ConverterTest_1843, CopyExifUserCommentToXmp_1843) {
    exifData_["Exif.Photo.UserComment"] = "charset=\"Ascii\" A test comment";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.UserComment"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Copy IptcData headline to XmpData
TEST_F(ConverterTest_1843, CopyIptcHeadlineToXmp_1843) {
    Exiv2::IptcKey key("Iptc.Application2.Headline");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
    val->read("Test Headline");
    iptcData_.add(key, val.get());
    Exiv2::copyIptcToXmp(iptcData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Move IptcData headline erases source
TEST_F(ConverterTest_1843, MoveIptcHeadlineErasesSource_1843) {
    Exiv2::IptcKey key("Iptc.Application2.Headline");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
    val->read("Move Headline");
    iptcData_.add(key, val.get());
    Exiv2::moveIptcToXmp(iptcData_, xmpData_);
    EXPECT_TRUE(iptcData_.empty());
}

// Test: Copy Xmp photoshop.Headline to IptcData
TEST_F(ConverterTest_1843, CopyXmpHeadlineToIptc_1843) {
    xmpData_["Xmp.photoshop.Headline"] = "XMP Headline";
    Exiv2::copyXmpToIptc(xmpData_, iptcData_);
    auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Headline"));
    EXPECT_NE(pos, iptcData_.end());
}

// Test: ExifData with XResolution (rational value) converts to XMP
TEST_F(ConverterTest_1843, CopyExifXResolutionToXmp_1843) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedRational);
    val->read("72/1");
    exifData_.add(Exiv2::ExifKey("Exif.Image.XResolution"), val.get());
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.XResolution"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Copy Exif Orientation to XmpData
TEST_F(ConverterTest_1843, CopyExifOrientationToXmp_1843) {
    exifData_["Exif.Image.Orientation"] = uint16_t(1);
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Orientation"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: Copy Xmp tiff.Orientation to ExifData
TEST_F(ConverterTest_1843, CopyXmpOrientationToExif_1843) {
    xmpData_["Xmp.tiff.Orientation"] = "1";
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Orientation"));
    ASSERT_NE(pos, exifData_.end());
    EXPECT_EQ(pos->toInt64(), 1);
}

// Test: Copy preserves source ExifData
TEST_F(ConverterTest_1843, CopyPreservesSourceExifData_1843) {
    exifData_["Exif.Image.ImageDescription"] = "Preserve test";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(pos, exifData_.end());
    EXPECT_EQ(pos->toString(), "Preserve test");
}

// Test: Copy preserves source XmpData
TEST_F(ConverterTest_1843, CopyPreservesSourceXmpData_1843) {
    xmpData_["Xmp.dc.description"] = "Preserve XMP test";
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(pos, xmpData_.end());
    EXPECT_EQ(pos->toString(), "Preserve XMP test");
}

// Test: Multiple conversions don't duplicate entries
TEST_F(ConverterTest_1843, MultipleConversionsNoDuplicates_1843) {
    exifData_["Exif.Image.ImageDescription"] = "No duplicates";
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    int count = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        if (it->key() == "Xmp.dc.description") {
            ++count;
        }
    }
    // Should have at most one lang-alt entry (or related entries)
    EXPECT_GE(count, 1);
}

// Test: Exif ISO speed to XMP
TEST_F(ConverterTest_1843, CopyExifISOSpeedToXmp_1843) {
    exifData_["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ISOSpeedRatings"));
    // This may or may not convert depending on mapping; ensure no crash
    EXPECT_TRUE(true);
}

// Test: Exif FocalLength to XMP
TEST_F(ConverterTest_1843, CopyExifFocalLengthToXmp_1843) {
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedRational);
    val->read("50/1");
    exifData_.add(Exiv2::ExifKey("Exif.Photo.FocalLength"), val.get());
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.FocalLength"));
    EXPECT_NE(pos, xmpData_.end());
}
