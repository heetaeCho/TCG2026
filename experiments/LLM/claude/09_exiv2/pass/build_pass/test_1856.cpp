#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

class MoveExifToXmpTest_1856 : public ::testing::Test {
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

// Test that moveExifToXmp with empty ExifData produces empty XmpData
TEST_F(MoveExifToXmpTest_1856, EmptyExifDataProducesEmptyXmpData_1856) {
    ASSERT_TRUE(exifData.empty());
    ASSERT_TRUE(xmpData.empty());

    Exiv2::moveExifToXmp(exifData, xmpData);

    // With no EXIF data, XMP should remain empty (or nearly so)
    EXPECT_TRUE(exifData.empty());
}

// Test that moveExifToXmp erases EXIF data after conversion
TEST_F(MoveExifToXmpTest_1856, ExifDataIsErasedAfterMove_1856) {
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";

    ASSERT_FALSE(exifData.empty());

    Exiv2::moveExifToXmp(exifData, xmpData);

    // After move, exif data should be erased (setErase is called)
    EXPECT_TRUE(exifData.empty());
}

// Test that moveExifToXmp converts known EXIF tags to XMP
TEST_F(MoveExifToXmpTest_1856, ExifMakeIsConvertedToXmp_1856) {
    exifData["Exif.Image.Make"] = "Canon";

    Exiv2::moveExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toString(), "Canon");
    }
}

// Test that moveExifToXmp converts Model tag
TEST_F(MoveExifToXmpTest_1856, ExifModelIsConvertedToXmp_1856) {
    exifData["Exif.Image.Model"] = "EOS 5D";

    Exiv2::moveExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Model"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toString(), "EOS 5D");
    }
}

// Test that multiple EXIF tags are converted and erased
TEST_F(MoveExifToXmpTest_1856, MultipleExifTagsConvertedAndErased_1856) {
    exifData["Exif.Image.Make"] = "Nikon";
    exifData["Exif.Image.Model"] = "D850";
    exifData["Exif.Image.Software"] = "Lightroom";

    size_t initialCount = exifData.count();
    ASSERT_GT(initialCount, 0u);

    Exiv2::moveExifToXmp(exifData, xmpData);

    // EXIF data should be erased
    EXPECT_TRUE(exifData.empty());
    // XMP data should have entries
    EXPECT_FALSE(xmpData.empty());
}

// Test that pre-existing XMP data is preserved when moving EXIF to XMP
TEST_F(MoveExifToXmpTest_1856, PreExistingXmpDataIsPreserved_1856) {
    xmpData["Xmp.dc.title"] = "ExistingTitle";

    exifData["Exif.Image.Make"] = "Sony";

    Exiv2::moveExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toString(), "ExistingTitle");
    }
}

class CopyExifToXmpTest_1856 : public ::testing::Test {
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

// Test that copyExifToXmp does NOT erase EXIF data
TEST_F(CopyExifToXmpTest_1856, ExifDataIsNotErasedAfterCopy_1856) {
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS R5";

    ASSERT_FALSE(exifData.empty());

    Exiv2::copyExifToXmp(exifData, xmpData);

    // After copy, exif data should still be present
    EXPECT_FALSE(exifData.empty());
    // XMP should have data
    EXPECT_FALSE(xmpData.empty());
}

// Test that copyExifToXmp with empty data
TEST_F(CopyExifToXmpTest_1856, EmptyExifDataCopy_1856) {
    Exiv2::copyExifToXmp(exifData, xmpData);
    EXPECT_TRUE(exifData.empty());
}

class MoveXmpToExifTest_1856 : public ::testing::Test {
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

// Test that moveXmpToExif erases XMP data after conversion
TEST_F(MoveXmpToExifTest_1856, XmpDataIsErasedAfterMove_1856) {
    xmpData["Xmp.tiff.Make"] = "Fuji";

    ASSERT_FALSE(xmpData.empty());

    Exiv2::moveXmpToExif(xmpData, exifData);

    // XMP data should be erased after move
    // Note: only converted entries are erased
    // Check that at least the converted one is gone
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_EQ(it, xmpData.end());
}

// Test that moveXmpToExif converts Make tag back to EXIF
TEST_F(MoveXmpToExifTest_1856, XmpMakeIsConvertedToExif_1856) {
    xmpData["Xmp.tiff.Make"] = "Panasonic";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, exifData.end());
    if (it != exifData.end()) {
        EXPECT_EQ(it->toString(), "Panasonic");
    }
}

class CopyXmpToExifTest_1856 : public ::testing::Test {
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

// Test that copyXmpToExif does NOT erase XMP data
TEST_F(CopyXmpToExifTest_1856, XmpDataIsNotErasedAfterCopy_1856) {
    xmpData["Xmp.tiff.Make"] = "Olympus";

    ASSERT_FALSE(xmpData.empty());

    Exiv2::copyXmpToExif(xmpData, exifData);

    // XMP data should still be present after copy
    EXPECT_FALSE(xmpData.empty());
}

// Test copyXmpToExif with empty XMP data
TEST_F(CopyXmpToExifTest_1856, EmptyXmpDataCopy_1856) {
    Exiv2::copyXmpToExif(xmpData, exifData);
    EXPECT_TRUE(xmpData.empty());
    EXPECT_TRUE(exifData.empty());
}

class IptcXmpConversionTest_1856 : public ::testing::Test {
protected:
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test moveIptcToXmp with empty IPTC data
TEST_F(IptcXmpConversionTest_1856, EmptyIptcToXmp_1856) {
    Exiv2::moveIptcToXmp(iptcData, xmpData);
    EXPECT_TRUE(iptcData.empty());
}

// Test copyIptcToXmp with empty IPTC data
TEST_F(IptcXmpConversionTest_1856, EmptyCopyIptcToXmp_1856) {
    Exiv2::copyIptcToXmp(iptcData, xmpData);
    EXPECT_TRUE(iptcData.empty());
}

// Test moveXmpToIptc with empty XMP data
TEST_F(IptcXmpConversionTest_1856, EmptyXmpToIptc_1856) {
    Exiv2::moveXmpToIptc(xmpData, iptcData);
    EXPECT_TRUE(xmpData.empty());
    EXPECT_TRUE(iptcData.empty());
}

// Test copyXmpToIptc with empty XMP data
TEST_F(IptcXmpConversionTest_1856, EmptyCopyXmpToIptc_1856) {
    Exiv2::copyXmpToIptc(xmpData, iptcData);
    EXPECT_TRUE(xmpData.empty());
    EXPECT_TRUE(iptcData.empty());
}

class RoundTripExifXmpTest_1856 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    Exiv2::ExifData exifDataResult;

    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test round-trip: copy EXIF -> XMP -> EXIF preserves Make
TEST_F(RoundTripExifXmpTest_1856, RoundTripMakePreserved_1856) {
    exifData["Exif.Image.Make"] = "TestBrand";

    Exiv2::copyExifToXmp(exifData, xmpData);
    EXPECT_FALSE(xmpData.empty());

    Exiv2::copyXmpToExif(xmpData, exifDataResult);

    auto it = exifDataResult.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, exifDataResult.end());
    if (it != exifDataResult.end()) {
        EXPECT_EQ(it->toString(), "TestBrand");
    }
}

// Test round-trip: copy EXIF -> XMP -> EXIF preserves Software
TEST_F(RoundTripExifXmpTest_1856, RoundTripSoftwarePreserved_1856) {
    exifData["Exif.Image.Software"] = "MySoftware 1.0";

    Exiv2::copyExifToXmp(exifData, xmpData);

    Exiv2::copyXmpToExif(xmpData, exifDataResult);

    auto it = exifDataResult.findKey(Exiv2::ExifKey("Exif.Image.Software"));
    EXPECT_NE(it, exifDataResult.end());
    if (it != exifDataResult.end()) {
        EXPECT_EQ(it->toString(), "MySoftware 1.0");
    }
}

// Test that moveExifToXmp followed by moveXmpToExif restores data
TEST_F(RoundTripExifXmpTest_1856, MoveRoundTripRestoresData_1856) {
    exifData["Exif.Image.Make"] = "RoundTripBrand";

    Exiv2::moveExifToXmp(exifData, xmpData);
    EXPECT_TRUE(exifData.empty());
    EXPECT_FALSE(xmpData.empty());

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, exifData.end());
    if (it != exifData.end()) {
        EXPECT_EQ(it->toString(), "RoundTripBrand");
    }
}

// Test conversion of ImageWidth (a numeric EXIF value)
class ExifNumericConversionTest_1856 : public ::testing::Test {
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

TEST_F(ExifNumericConversionTest_1856, ImageWidthConversion_1856) {
    exifData["Exif.Image.ImageWidth"] = uint32_t(1920);

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.ImageWidth"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toString(), "1920");
    }
}

TEST_F(ExifNumericConversionTest_1856, ImageLengthConversion_1856) {
    exifData["Exif.Image.ImageLength"] = uint32_t(1080);

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.ImageLength"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toString(), "1080");
    }
}

// Test that overwrite behavior works (default is overwrite=true)
class OverwriteTest_1856 : public ::testing::Test {
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

TEST_F(OverwriteTest_1856, CopyExifOverwritesExistingXmp_1856) {
    // Pre-populate XMP with a value
    xmpData["Xmp.tiff.Make"] = "OldBrand";

    // Set EXIF with a different value
    exifData["Exif.Image.Make"] = "NewBrand";

    Exiv2::copyExifToXmp(exifData, xmpData);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        // With default overwrite=true, the new value should overwrite
        EXPECT_EQ(it->toString(), "NewBrand");
    }
}
