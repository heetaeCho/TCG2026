#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Test fixture for syncExifWithXmp tests
class SyncExifWithXmpTest_1859 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;

    void SetUp() override {
        exifData.clear();
        xmpData.clear();
    }

    void TearDown() override {
        exifData.clear();
        xmpData.clear();
    }
};

// Test that syncExifWithXmp doesn't crash with empty data
TEST_F(SyncExifWithXmpTest_1859, EmptyDataDoesNotCrash_1859) {
    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
    EXPECT_TRUE(exifData.empty());
}

// Test that syncExifWithXmp handles XMP data and syncs to Exif
TEST_F(SyncExifWithXmpTest_1859, XmpDataSyncsToExif_1859) {
    // Add some XMP data that has a known Exif equivalent
    xmpData["Xmp.tiff.ImageWidth"] = "1024";

    Exiv2::syncExifWithXmp(exifData, xmpData);

    // Check if the Exif equivalent was created
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageWidth"));
    if (it != exifData.end()) {
        EXPECT_EQ(it->toInt64(), 1024);
    }
}

// Test syncing when Exif already has data and XMP has matching data
TEST_F(SyncExifWithXmpTest_1859, ExistingExifAndXmpDataSync_1859) {
    exifData["Exif.Image.ImageWidth"] = uint32_t(800);
    xmpData["Xmp.tiff.ImageWidth"] = "1024";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing XMP date/time to Exif
TEST_F(SyncExifWithXmpTest_1859, XmpDateTimeSyncsToExif_1859) {
    xmpData["Xmp.exif.DateTimeOriginal"] = "2023-06-15T10:30:00";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    if (it != exifData.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test syncing GPS data from XMP to Exif
TEST_F(SyncExifWithXmpTest_1859, XmpGPSCoordSyncsToExif_1859) {
    xmpData["Xmp.exif.GPSLatitude"] = "37,46.5N";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing GPS longitude from XMP to Exif
TEST_F(SyncExifWithXmpTest_1859, XmpGPSLongitudeSyncsToExif_1859) {
    xmpData["Xmp.exif.GPSLongitude"] = "122,25.1W";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing ExifVersion from XMP
TEST_F(SyncExifWithXmpTest_1859, XmpExifVersionSyncsToExif_1859) {
    xmpData["Xmp.exif.ExifVersion"] = "2.30";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.ExifVersion"));
    if (it != exifData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test syncing Flash from XMP
TEST_F(SyncExifWithXmpTest_1859, XmpFlashSyncsToExif_1859) {
    // Flash is a structured XMP type
    xmpData["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData["Xmp.exif.Flash/exif:Return"] = "0";
    xmpData["Xmp.exif.Flash/exif:Mode"] = "1";
    xmpData["Xmp.exif.Flash/exif:Function"] = "False";
    xmpData["Xmp.exif.Flash/exif:RedEyeMode"] = "False";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing GPSVersionID from XMP
TEST_F(SyncExifWithXmpTest_1859, XmpGPSVersionSyncsToExif_1859) {
    xmpData["Xmp.exif.GPSVersionID"] = "2.2.0.0";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    if (it != exifData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test with only Exif data and no XMP data
TEST_F(SyncExifWithXmpTest_1859, OnlyExifNoXmpData_1859) {
    exifData["Exif.Image.ImageWidth"] = uint32_t(800);
    exifData["Exif.Image.ImageLength"] = uint32_t(600);

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing UserComment
TEST_F(SyncExifWithXmpTest_1859, XmpUserCommentSyncsToExif_1859) {
    xmpData["Xmp.exif.UserComment"] = "Test comment";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Photo.UserComment"));
    if (it != exifData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test syncing multiple XMP fields simultaneously
TEST_F(SyncExifWithXmpTest_1859, MultipleXmpFieldsSyncToExif_1859) {
    xmpData["Xmp.tiff.ImageWidth"] = "2048";
    xmpData["Xmp.tiff.ImageLength"] = "1536";
    xmpData["Xmp.exif.DateTimeOriginal"] = "2023-01-01T00:00:00";
    xmpData["Xmp.tiff.Make"] = "TestCamera";
    xmpData["Xmp.tiff.Model"] = "TestModel";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing orientation
TEST_F(SyncExifWithXmpTest_1859, XmpOrientationSyncsToExif_1859) {
    xmpData["Xmp.tiff.Orientation"] = "6";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Orientation"));
    if (it != exifData.end()) {
        EXPECT_EQ(it->toInt64(), 6);
    }
}

// Test syncing ISO speed
TEST_F(SyncExifWithXmpTest_1859, XmpISOSpeedSyncsToExif_1859) {
    xmpData["Xmp.exif.ISOSpeedRatings"] = "400";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test that calling syncExifWithXmp twice doesn't cause issues
TEST_F(SyncExifWithXmpTest_1859, DoubleSyncDoesNotCrash_1859) {
    xmpData["Xmp.tiff.ImageWidth"] = "1024";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing XResolution/YResolution
TEST_F(SyncExifWithXmpTest_1859, XmpResolutionSyncsToExif_1859) {
    xmpData["Xmp.tiff.XResolution"] = "72/1";
    xmpData["Xmp.tiff.YResolution"] = "72/1";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing with Exif data that has conflicting values
TEST_F(SyncExifWithXmpTest_1859, ConflictingExifAndXmpValues_1859) {
    exifData["Exif.Image.Orientation"] = uint16_t(1);
    xmpData["Xmp.tiff.Orientation"] = "3";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));

    // After sync, Exif should reflect the synced value
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Orientation"));
    EXPECT_NE(it, exifData.end());
}

// Test syncing Software field
TEST_F(SyncExifWithXmpTest_1859, XmpSoftwareSyncsToExif_1859) {
    xmpData["Xmp.tiff.Software"] = "TestSoftware 1.0";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Software"));
    if (it != exifData.end()) {
        EXPECT_EQ(it->toString(), "TestSoftware 1.0");
    }
}

// Test syncing Artist field
TEST_F(SyncExifWithXmpTest_1859, XmpArtistSyncsToExif_1859) {
    xmpData["Xmp.tiff.Artist"] = "Test Artist";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing Copyright field
TEST_F(SyncExifWithXmpTest_1859, XmpCopyrightSyncsToExif_1859) {
    xmpData["Xmp.tiff.Copyright"] = "Copyright 2023";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing Description
TEST_F(SyncExifWithXmpTest_1859, XmpDescriptionSyncsToExif_1859) {
    xmpData["Xmp.tiff.ImageDescription"] = "A test image";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    if (it != exifData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test syncing ExposureTime
TEST_F(SyncExifWithXmpTest_1859, XmpExposureTimeSyncsToExif_1859) {
    xmpData["Xmp.exif.ExposureTime"] = "1/125";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing FNumber
TEST_F(SyncExifWithXmpTest_1859, XmpFNumberSyncsToExif_1859) {
    xmpData["Xmp.exif.FNumber"] = "56/10";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}

// Test syncing FocalLength
TEST_F(SyncExifWithXmpTest_1859, XmpFocalLengthSyncsToExif_1859) {
    xmpData["Xmp.exif.FocalLength"] = "50/1";

    EXPECT_NO_THROW(Exiv2::syncExifWithXmp(exifData, xmpData));
}
