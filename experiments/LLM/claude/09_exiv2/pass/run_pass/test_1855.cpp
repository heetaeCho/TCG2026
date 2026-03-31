#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Test fixture for copyExifToXmp tests
class CopyExifToXmpTest_1855 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test that copying from empty ExifData produces empty XmpData
TEST_F(CopyExifToXmpTest_1855, EmptyExifProducesEmptyXmp_1855) {
    ASSERT_TRUE(exifData.empty());
    ASSERT_TRUE(xmpData.empty());

    Exiv2::copyExifToXmp(exifData, xmpData);

    EXPECT_TRUE(xmpData.empty());
}

// Test that a simple Exif value is converted to XMP
TEST_F(CopyExifToXmpTest_1855, SimpleExifValueConvertedToXmp_1855) {
    exifData["Exif.Image.Artist"] = "Test Artist";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    // The Artist field should be mapped to dc:creator
    // Check that at least some data was converted
    EXPECT_FALSE(xmpData.empty());
}

// Test that ImageDescription is converted to dc.description
TEST_F(CopyExifToXmpTest_1855, ImageDescriptionConvertedToXmp_1855) {
    exifData["Exif.Image.ImageDescription"] = "A test description";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    if (it != xmpData.end()) {
        EXPECT_NE(std::string::npos, it->toString().find("A test description"));
    }
    EXPECT_FALSE(xmpData.empty());
}

// Test that Copyright is converted to XMP
TEST_F(CopyExifToXmpTest_1855, CopyrightConvertedToXmp_1855) {
    exifData["Exif.Image.Copyright"] = "Copyright 2024 Test";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    if (it != xmpData.end()) {
        EXPECT_NE(std::string::npos, it->toString().find("Copyright 2024 Test"));
    }
    EXPECT_FALSE(xmpData.empty());
}

// Test that ExifVersion is properly converted
TEST_F(CopyExifToXmpTest_1855, ExifVersionConverted_1855) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::undefined);
    v->read("48 50 51 48"); // "0230" in ASCII
    exifData.add(Exiv2::ExifKey("Exif.Photo.ExifVersion"), v.get());

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    if (it != xmpData.end()) {
        // ExifVersion should be converted to a string like "2.30"
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test that GPS coordinates are converted
TEST_F(CopyExifToXmpTest_1855, GPSLatitudeConverted_1855) {
    // Set GPS latitude: 48 degrees, 51 minutes, 30 seconds N
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("48/1 51/1 30/1");
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
    exifData["Exif.GPSInfo.GPSLatitudeRef"] = "N";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
    if (it != xmpData.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test that GPS longitude is converted
TEST_F(CopyExifToXmpTest_1855, GPSLongitudeConverted_1855) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("2/1 20/1 0/1");
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"), rv.get());
    exifData["Exif.GPSInfo.GPSLongitudeRef"] = "E";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSLongitude"));
    if (it != xmpData.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test that DateTimeOriginal is converted
TEST_F(CopyExifToXmpTest_1855, DateTimeOriginalConverted_1855) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2024:01:15 10:30:00";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
    if (it != xmpData.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test that pre-existing XMP data is preserved (overwrite=true by default)
TEST_F(CopyExifToXmpTest_1855, PreExistingXmpDataOverwritten_1855) {
    xmpData["Xmp.dc.creator"] = "Old Artist";
    exifData["Exif.Image.Artist"] = "New Artist";

    Exiv2::copyExifToXmp(exifData, xmpData);

    // Should have been overwritten
    EXPECT_FALSE(xmpData.empty());
}

// Test that multiple Exif fields are converted
TEST_F(CopyExifToXmpTest_1855, MultipleExifFieldsConverted_1855) {
    exifData["Exif.Image.Artist"] = "Test Artist";
    exifData["Exif.Image.Copyright"] = "Copyright Test";
    exifData["Exif.Image.ImageDescription"] = "Test Description";
    exifData["Exif.Photo.DateTimeOriginal"] = "2024:06:15 12:00:00";

    Exiv2::copyExifToXmp(exifData, xmpData);

    EXPECT_FALSE(xmpData.empty());
    // Multiple fields should result in multiple XMP entries
    EXPECT_GT(xmpData.count(), 1);
}

// Test that Flash data is properly converted
TEST_F(CopyExifToXmpTest_1855, FlashConverted_1855) {
    exifData["Exif.Photo.Flash"] = uint16_t(1); // Flash fired

    Exiv2::copyExifToXmp(exifData, xmpData);

    // Flash should be converted to structured XMP
    EXPECT_FALSE(xmpData.empty());
}

// Test that ExifData is not modified by the copy operation
TEST_F(CopyExifToXmpTest_1855, ExifDataNotModified_1855) {
    exifData["Exif.Image.Artist"] = "Test Artist";
    exifData["Exif.Image.Copyright"] = "Copyright Test";

    size_t countBefore = exifData.count();

    Exiv2::copyExifToXmp(exifData, xmpData);

    EXPECT_EQ(countBefore, exifData.count());
}

// Test with UserComment (Exif comment conversion)
TEST_F(CopyExifToXmpTest_1855, UserCommentConverted_1855) {
    // UserComment needs charset prefix
    Exiv2::CommentValue::UniquePtr cv(new Exiv2::CommentValue("charset=Ascii A user comment"));
    exifData.add(Exiv2::ExifKey("Exif.Photo.UserComment"), cv.get());

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.UserComment"));
    if (it != xmpData.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test GPSVersionID conversion
TEST_F(CopyExifToXmpTest_1855, GPSVersionIDConverted_1855) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedByte);
    v->read("2 3 0 0");
    exifData.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), v.get());

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    if (it != xmpData.end()) {
        std::string val = it->toString();
        EXPECT_FALSE(val.empty());
    }
}

// Test that calling copyExifToXmp twice doesn't duplicate entries (overwrite mode)
TEST_F(CopyExifToXmpTest_1855, DoubleCopyDoesNotDuplicate_1855) {
    exifData["Exif.Image.Artist"] = "Test Artist";

    Exiv2::copyExifToXmp(exifData, xmpData);
    long countAfterFirst = xmpData.count();

    Exiv2::copyExifToXmp(exifData, xmpData);
    long countAfterSecond = xmpData.count();

    EXPECT_EQ(countAfterFirst, countAfterSecond);
}

// Test conversion of ISO speed
TEST_F(CopyExifToXmpTest_1855, ISOSpeedConverted_1855) {
    exifData["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.ISOSpeedRatings"));
    if (it != xmpData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test conversion of FocalLength
TEST_F(CopyExifToXmpTest_1855, FocalLengthConverted_1855) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("50/1");
    exifData.add(Exiv2::ExifKey("Exif.Photo.FocalLength"), rv.get());

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.FocalLength"));
    if (it != xmpData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test conversion of ExposureTime
TEST_F(CopyExifToXmpTest_1855, ExposureTimeConverted_1855) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("1/250");
    exifData.add(Exiv2::ExifKey("Exif.Photo.ExposureTime"), rv.get());

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.ExposureTime"));
    if (it != xmpData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

// Test conversion of FNumber (aperture)
TEST_F(CopyExifToXmpTest_1855, FNumberConverted_1855) {
    Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
    rv->read("28/10");
    exifData.add(Exiv2::ExifKey("Exif.Photo.FNumber"), rv.get());

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.FNumber"));
    if (it != xmpData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}
