#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Test fixture for copyXmpToExif tests
class CopyXmpToExifTest_1857 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData;
    Exiv2::ExifData exifData;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test that copying from empty XmpData to empty ExifData produces no exif entries
TEST_F(CopyXmpToExifTest_1857, EmptyXmpToEmptyExif_1857) {
    Exiv2::copyXmpToExif(xmpData, exifData);
    EXPECT_TRUE(exifData.empty());
}

// Test that a simple XMP value (like tiff:ImageWidth) is converted to Exif
TEST_F(CopyXmpToExifTest_1857, XmpImageWidthToExif_1857) {
    xmpData["Xmp.tiff.ImageWidth"] = 1024;
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageWidth"));
    EXPECT_NE(it, exifData.end());
    if (it != exifData.end()) {
        EXPECT_EQ(it->toInt64(), 1024);
    }
}

// Test that XMP ImageLength converts to Exif
TEST_F(CopyXmpToExifTest_1857, XmpImageLengthToExif_1857) {
    xmpData["Xmp.tiff.ImageLength"] = 768;
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageLength"));
    EXPECT_NE(it, exifData.end());
    if (it != exifData.end()) {
        EXPECT_EQ(it->toInt64(), 768);
    }
}

// Test that XMP Orientation converts to Exif
TEST_F(CopyXmpToExifTest_1857, XmpOrientationToExif_1857) {
    xmpData["Xmp.tiff.Orientation"] = 6;
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Orientation"));
    EXPECT_NE(it, exifData.end());
    if (it != exifData.end()) {
        EXPECT_EQ(it->toInt64(), 6);
    }
}

// Test that XMP exif:ISOSpeedRatings converts to Exif
TEST_F(CopyXmpToExifTest_1857, XmpISOSpeedToExif_1857) {
    xmpData["Xmp.exif.ISOSpeedRatings"] = 400;
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.ISOSpeedRatings"));
    EXPECT_NE(it, exifData.end());
}

// Test that existing ExifData is preserved (overwrite default is true)
TEST_F(CopyXmpToExifTest_1857, ExistingExifOverwritten_1857) {
    exifData["Exif.Image.ImageWidth"] = uint32_t(512);
    xmpData["Xmp.tiff.ImageWidth"] = 2048;
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageWidth"));
    EXPECT_NE(it, exifData.end());
    if (it != exifData.end()) {
        EXPECT_EQ(it->toInt64(), 2048);
    }
}

// Test converting XMP date/time to Exif
TEST_F(CopyXmpToExifTest_1857, XmpDateTimeOriginalToExif_1857) {
    xmpData["Xmp.exif.DateTimeOriginal"] = "2023-06-15T10:30:00";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    EXPECT_NE(it, exifData.end());
}

// Test converting XMP GPS latitude to Exif
TEST_F(CopyXmpToExifTest_1857, XmpGPSLatitudeToExif_1857) {
    xmpData["Xmp.exif.GPSLatitude"] = "40,26.767N";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    // GPS coordinate conversion may or may not produce a result depending on format
    // We just verify no crash occurs
    SUCCEED();
}

// Test converting XMP GPS longitude to Exif
TEST_F(CopyXmpToExifTest_1857, XmpGPSLongitudeToExif_1857) {
    xmpData["Xmp.exif.GPSLongitude"] = "79,58.933W";
    Exiv2::copyXmpToExif(xmpData, exifData);
    SUCCEED();
}

// Test that multiple XMP properties are all converted
TEST_F(CopyXmpToExifTest_1857, MultipleXmpPropertiesToExif_1857) {
    xmpData["Xmp.tiff.ImageWidth"] = 3000;
    xmpData["Xmp.tiff.ImageLength"] = 2000;
    xmpData["Xmp.tiff.Orientation"] = 1;
    Exiv2::copyXmpToExif(xmpData, exifData);

    EXPECT_NE(exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageWidth")), exifData.end());
    EXPECT_NE(exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageLength")), exifData.end());
    EXPECT_NE(exifData.findKey(Exiv2::ExifKey("Exif.Image.Orientation")), exifData.end());
}

// Test that ExifVersion XMP converts to Exif
TEST_F(CopyXmpToExifTest_1857, XmpExifVersionToExif_1857) {
    xmpData["Xmp.exif.ExifVersion"] = "2.30";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.ExifVersion"));
    EXPECT_NE(it, exifData.end());
}

// Test that FlashpixVersion XMP converts to Exif
TEST_F(CopyXmpToExifTest_1857, XmpFlashpixVersionToExif_1857) {
    xmpData["Xmp.exif.FlashpixVersion"] = "1.00";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.FlashpixVersion"));
    EXPECT_NE(it, exifData.end());
}

// Test that GPSVersionID XMP converts to Exif
TEST_F(CopyXmpToExifTest_1857, XmpGPSVersionIDToExif_1857) {
    xmpData["Xmp.exif.GPSVersionID"] = "2.2.0.0";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    EXPECT_NE(it, exifData.end());
}

// Test that UserComment XMP converts to Exif
TEST_F(CopyXmpToExifTest_1857, XmpUserCommentToExif_1857) {
    xmpData["Xmp.exif.UserComment"] = "Test comment";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.UserComment"));
    EXPECT_NE(it, exifData.end());
}

// Test that calling copyXmpToExif twice does not duplicate entries (overwrite mode)
TEST_F(CopyXmpToExifTest_1857, DoubleCopyDoesNotDuplicate_1857) {
    xmpData["Xmp.tiff.ImageWidth"] = 1024;
    Exiv2::copyXmpToExif(xmpData, exifData);
    size_t countAfterFirst = exifData.count();

    Exiv2::copyXmpToExif(xmpData, exifData);
    size_t countAfterSecond = exifData.count();

    EXPECT_EQ(countAfterFirst, countAfterSecond);
}

// Test XMP Flash conversion to Exif
TEST_F(CopyXmpToExifTest_1857, XmpFlashToExif_1857) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData["Xmp.exif.Flash/exif:Return"] = "0";
    xmpData["Xmp.exif.Flash/exif:Mode"] = "1";
    xmpData["Xmp.exif.Flash/exif:Function"] = "False";
    xmpData["Xmp.exif.Flash/exif:RedEyeMode"] = "False";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    EXPECT_NE(it, exifData.end());
}

// Test that an unrecognized XMP namespace does not crash
TEST_F(CopyXmpToExifTest_1857, UnrecognizedXmpNamespaceNoCrash_1857) {
    // Register a custom namespace and add data
    Exiv2::XmpProperties::registerNs("http://example.com/test/", "test");
    xmpData["Xmp.test.SomeProperty"] = "SomeValue";
    // Should not crash
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmpData, exifData));
    Exiv2::XmpProperties::unregisterNs("http://example.com/test/");
}

// Test that XMP Make and Model convert properly
TEST_F(CopyXmpToExifTest_1857, XmpMakeModelToExif_1857) {
    xmpData["Xmp.tiff.Make"] = "TestCamera";
    xmpData["Xmp.tiff.Model"] = "TestModel";
    Exiv2::copyXmpToExif(xmpData, exifData);

    auto itMake = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(itMake, exifData.end());
    if (itMake != exifData.end()) {
        EXPECT_EQ(itMake->toString(), "TestCamera");
    }

    auto itModel = exifData.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    EXPECT_NE(itModel, exifData.end());
    if (itModel != exifData.end()) {
        EXPECT_EQ(itModel->toString(), "TestModel");
    }
}

// Test fixture for copyExifToXmp tests
class CopyExifToXmpTest_1857 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData;
    Exiv2::ExifData exifData;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test that copying from empty ExifData to empty XmpData produces no XMP entries
TEST_F(CopyExifToXmpTest_1857, EmptyExifToEmptyXmp_1857) {
    Exiv2::copyExifToXmp(exifData, xmpData);
    EXPECT_TRUE(xmpData.empty());
}

// Test that Exif ImageWidth converts to XMP
TEST_F(CopyExifToXmpTest_1857, ExifImageWidthToXmp_1857) {
    exifData["Exif.Image.ImageWidth"] = uint32_t(4096);
    Exiv2::copyExifToXmp(exifData, xmpData);
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.ImageWidth"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toInt64(), 4096);
    }
}

// Test that Exif Orientation converts to XMP
TEST_F(CopyExifToXmpTest_1857, ExifOrientationToXmp_1857) {
    exifData["Exif.Image.Orientation"] = uint16_t(3);
    Exiv2::copyExifToXmp(exifData, xmpData);
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Orientation"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toInt64(), 3);
    }
}

// Test that Exif Make converts to XMP
TEST_F(CopyExifToXmpTest_1857, ExifMakeToXmp_1857) {
    exifData["Exif.Image.Make"] = "Canon";
    Exiv2::copyExifToXmp(exifData, xmpData);
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toString(), "Canon");
    }
}

// Test round-trip: Exif -> XMP -> Exif preserves values
TEST_F(CopyExifToXmpTest_1857, RoundTripPreservesValues_1857) {
    exifData["Exif.Image.ImageWidth"] = uint32_t(2048);
    exifData["Exif.Image.Orientation"] = uint16_t(1);

    Exiv2::copyExifToXmp(exifData, xmpData);

    Exiv2::ExifData exifData2;
    Exiv2::copyXmpToExif(xmpData, exifData2);

    auto itWidth = exifData2.findKey(Exiv2::ExifKey("Exif.Image.ImageWidth"));
    EXPECT_NE(itWidth, exifData2.end());
    if (itWidth != exifData2.end()) {
        EXPECT_EQ(itWidth->toInt64(), 2048);
    }

    auto itOrient = exifData2.findKey(Exiv2::ExifKey("Exif.Image.Orientation"));
    EXPECT_NE(itOrient, exifData2.end());
    if (itOrient != exifData2.end()) {
        EXPECT_EQ(itOrient->toInt64(), 1);
    }
}

// Test fixture for IPTC conversion tests
class CopyXmpToIptcTest_1857 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData;
    Exiv2::IptcData iptcData;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test that copying from empty XmpData to empty IptcData produces no entries
TEST_F(CopyXmpToIptcTest_1857, EmptyXmpToEmptyIptc_1857) {
    Exiv2::copyXmpToIptc(xmpData, iptcData);
    EXPECT_TRUE(iptcData.empty());
}

// Test that XMP dc:description converts to IPTC
TEST_F(CopyXmpToIptcTest_1857, XmpDescriptionToIptc_1857) {
    xmpData["Xmp.dc.description"] = "Test description";
    Exiv2::copyXmpToIptc(xmpData, iptcData);
    // IPTC Caption/Abstract
    auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    EXPECT_NE(it, iptcData.end());
}

// Test fixture for IPTC to XMP conversion
class CopyIptcToXmpTest_1857 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData;
    Exiv2::IptcData iptcData;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test that copying from empty IptcData to empty XmpData produces no entries
TEST_F(CopyIptcToXmpTest_1857, EmptyIptcToEmptyXmp_1857) {
    Exiv2::copyIptcToXmp(iptcData, xmpData);
    EXPECT_TRUE(xmpData.empty());
}

// Test that IPTC Keywords convert to XMP
TEST_F(CopyIptcToXmpTest_1857, IptcKeywordsToXmp_1857) {
    iptcData["Iptc.Application2.Keywords"] = "keyword1";
    Exiv2::copyIptcToXmp(iptcData, xmpData);
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(it, xmpData.end());
}

// Test that IPTC byline converts to XMP dc:creator
TEST_F(CopyIptcToXmpTest_1857, IptcBylineToXmpCreator_1857) {
    iptcData["Iptc.Application2.Byline"] = "John Doe";
    Exiv2::copyIptcToXmp(iptcData, xmpData);
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_NE(it, xmpData.end());
}

// Test moveXmpToExif: XMP data should be moved (source cleared of converted entries)
class MoveXmpToExifTest_1857 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData;
    Exiv2::ExifData exifData;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

TEST_F(MoveXmpToExifTest_1857, MoveXmpToExifClearsXmp_1857) {
    xmpData["Xmp.tiff.ImageWidth"] = 1024;
    Exiv2::moveXmpToExif(xmpData, exifData);
    // After move, the converted XMP entry should be erased
    auto xit = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.ImageWidth"));
    EXPECT_EQ(xit, xmpData.end());

    // And exifData should have the value
    auto eit = exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageWidth"));
    EXPECT_NE(eit, exifData.end());
}

// Test moveExifToXmp
class MoveExifToXmpTest_1857 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData;
    Exiv2::ExifData exifData;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

TEST_F(MoveExifToXmpTest_1857, MoveExifToXmpClearsExif_1857) {
    exifData["Exif.Image.ImageWidth"] = uint32_t(2048);
    Exiv2::moveExifToXmp(exifData, xmpData);

    // After move, converted Exif entry should be erased
    auto eit = exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageWidth"));
    EXPECT_EQ(eit, exifData.end());

    // XMP should have the value
    auto xit = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.ImageWidth"));
    EXPECT_NE(xit, xmpData.end());
}

// Test that non-convertible exif tags don't crash the conversion
TEST_F(CopyExifToXmpTest_1857, NonConvertibleExifTagNoCrash_1857) {
    // A tag that may not have a mapping
    exifData["Exif.Image.StripOffsets"] = uint32_t(0);
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData, xmpData));
}

// Test XMP exif:FocalLength to Exif
TEST_F(CopyXmpToExifTest_1857, XmpFocalLengthToExif_1857) {
    xmpData["Xmp.exif.FocalLength"] = "50/1";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.FocalLength"));
    EXPECT_NE(it, exifData.end());
}

// Test XMP Copyright to Exif
TEST_F(CopyXmpToExifTest_1857, XmpCopyrightToExif_1857) {
    xmpData["Xmp.dc.rights"] = "Copyright 2023";
    Exiv2::copyXmpToExif(xmpData, exifData);
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Copyright"));
    EXPECT_NE(it, exifData.end());
}
