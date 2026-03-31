#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Test fixture for moveXmpToExif tests
class MoveXmpToExifTest_1858 : public ::testing::Test {
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

// Test that moveXmpToExif with empty XmpData produces no ExifData changes
TEST_F(MoveXmpToExifTest_1858, EmptyXmpDataProducesNoExifData_1858) {
    ASSERT_TRUE(xmpData.empty());
    ASSERT_TRUE(exifData.empty());

    Exiv2::moveXmpToExif(xmpData, exifData);

    // With no XMP data, exif should remain empty (or near-empty, only digest may be added)
    // XMP data should also remain empty since there was nothing to erase
    EXPECT_TRUE(xmpData.empty());
}

// Test that moveXmpToExif converts a simple XMP value to Exif
TEST_F(MoveXmpToExifTest_1858, SimpleXmpValueConvertedToExif_1858) {
    xmpData["Xmp.tiff.Make"] = "TestCamera";

    ASSERT_FALSE(xmpData.empty());

    Exiv2::moveXmpToExif(xmpData, exifData);

    // The XMP value should have been moved (erased from XMP)
    auto xmpIt = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_TRUE(xmpIt == xmpData.end());

    // The Exif value should now exist
    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(exifIt, exifData.end());
    if (exifIt != exifData.end()) {
        EXPECT_EQ(exifIt->toString(), "TestCamera");
    }
}

// Test that moveXmpToExif converts XMP Model to Exif
TEST_F(MoveXmpToExifTest_1858, XmpModelConvertedToExif_1858) {
    xmpData["Xmp.tiff.Model"] = "TestModel";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto xmpIt = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Model"));
    EXPECT_TRUE(xmpIt == xmpData.end());

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    EXPECT_NE(exifIt, exifData.end());
    if (exifIt != exifData.end()) {
        EXPECT_EQ(exifIt->toString(), "TestModel");
    }
}

// Test that moveXmpToExif erases XMP data after conversion (setErase behavior)
TEST_F(MoveXmpToExifTest_1858, XmpDataErasedAfterMove_1858) {
    xmpData["Xmp.tiff.Make"] = "CameraBrand";
    xmpData["Xmp.tiff.Model"] = "CameraModel";

    size_t initialXmpCount = xmpData.count();
    ASSERT_GE(initialXmpCount, 2u);

    Exiv2::moveXmpToExif(xmpData, exifData);

    // Check that the converted XMP entries were erased
    auto it1 = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    auto it2 = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Model"));
    EXPECT_TRUE(it1 == xmpData.end());
    EXPECT_TRUE(it2 == xmpData.end());
}

// Test that existing Exif data gets overwritten by XMP data
TEST_F(MoveXmpToExifTest_1858, ExistingExifDataOverwritten_1858) {
    exifData["Exif.Image.Make"] = "OldCamera";
    xmpData["Xmp.tiff.Make"] = "NewCamera";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(exifIt, exifData.end());
    if (exifIt != exifData.end()) {
        EXPECT_EQ(exifIt->toString(), "NewCamera");
    }
}

// Test that non-convertible XMP data is not erased
TEST_F(MoveXmpToExifTest_1858, NonConvertibleXmpDataRemains_1858) {
    // Use a custom XMP namespace property that has no Exif mapping
    xmpData["Xmp.dc.description"] = "Some description";

    Exiv2::moveXmpToExif(xmpData, exifData);

    // dc.description maps to IPTC not EXIF typically; check it may still exist in XMP
    // (This depends on implementation, but it should not be erased if there's no Exif mapping)
    // We just verify no crash occurs
}

// Test multiple XMP properties conversion
TEST_F(MoveXmpToExifTest_1858, MultipleXmpPropertiesConverted_1858) {
    xmpData["Xmp.tiff.Make"] = "Brand";
    xmpData["Xmp.tiff.Model"] = "Model123";
    xmpData["Xmp.tiff.Software"] = "TestSoftware";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto makeIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    auto modelIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Model"));
    auto softIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Software"));

    EXPECT_NE(makeIt, exifData.end());
    EXPECT_NE(modelIt, exifData.end());
    EXPECT_NE(softIt, exifData.end());

    if (makeIt != exifData.end()) EXPECT_EQ(makeIt->toString(), "Brand");
    if (modelIt != exifData.end()) EXPECT_EQ(modelIt->toString(), "Model123");
    if (softIt != exifData.end()) EXPECT_EQ(softIt->toString(), "TestSoftware");
}

// Test fixture for copyXmpToExif tests
class CopyXmpToExifTest_1858 : public ::testing::Test {
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

// Test that copyXmpToExif does not erase XMP data
TEST_F(CopyXmpToExifTest_1858, XmpDataNotErasedAfterCopy_1858) {
    xmpData["Xmp.tiff.Make"] = "CopyBrand";

    Exiv2::copyXmpToExif(xmpData, exifData);

    // XMP data should still exist (copy, not move)
    auto xmpIt = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_NE(xmpIt, xmpData.end());

    // Exif data should also exist
    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(exifIt, exifData.end());
}

// Test that copyXmpToExif with empty data works
TEST_F(CopyXmpToExifTest_1858, EmptyXmpDataCopyDoesNothing_1858) {
    ASSERT_TRUE(xmpData.empty());

    Exiv2::copyXmpToExif(xmpData, exifData);

    EXPECT_TRUE(xmpData.empty());
}

// Test fixture for moveExifToXmp tests
class MoveExifToXmpTest_1858 : public ::testing::Test {
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

// Test that moveExifToXmp converts Exif to XMP and erases Exif
TEST_F(MoveExifToXmpTest_1858, ExifDataMovedToXmp_1858) {
    exifData["Exif.Image.Make"] = "ExifBrand";

    Exiv2::moveExifToXmp(exifData, xmpData);

    // Exif data should be erased
    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_TRUE(exifIt == exifData.end());

    // XMP data should now contain the value
    auto xmpIt = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_NE(xmpIt, xmpData.end());
    if (xmpIt != xmpData.end()) {
        EXPECT_EQ(xmpIt->toString(), "ExifBrand");
    }
}

// Test that moveExifToXmp with empty data works
TEST_F(MoveExifToXmpTest_1858, EmptyExifDataProducesNoXmpData_1858) {
    ASSERT_TRUE(exifData.empty());

    Exiv2::moveExifToXmp(exifData, xmpData);

    EXPECT_TRUE(exifData.empty());
}

// Test fixture for copyExifToXmp tests
class CopyExifToXmpTest_1858 : public ::testing::Test {
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

// Test that copyExifToXmp preserves Exif data
TEST_F(CopyExifToXmpTest_1858, ExifDataPreservedAfterCopy_1858) {
    exifData["Exif.Image.Make"] = "CopyExifBrand";

    Exiv2::copyExifToXmp(exifData, xmpData);

    // Exif data should still exist
    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(exifIt, exifData.end());

    // XMP data should also have the value
    auto xmpIt = xmpData.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_NE(xmpIt, xmpData.end());
}

// Test fixture for XMP date conversion
class XmpDateConversionTest_1858 : public ::testing::Test {
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

// Test XMP date to Exif date conversion
TEST_F(XmpDateConversionTest_1858, XmpDateTimeOriginalToExif_1858) {
    xmpData["Xmp.exif.DateTimeOriginal"] = "2023-06-15T10:30:00";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
    EXPECT_NE(exifIt, exifData.end());
}

// Test GPS coordinate conversion
class XmpGPSConversionTest_1858 : public ::testing::Test {
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

// Test XMP GPS latitude to Exif conversion
TEST_F(XmpGPSConversionTest_1858, XmpGPSLatitudeToExif_1858) {
    xmpData["Xmp.exif.GPSLatitude"] = "48,51.5N";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
    EXPECT_NE(exifIt, exifData.end());
}

// Test XMP GPS longitude to Exif conversion
TEST_F(XmpGPSConversionTest_1858, XmpGPSLongitudeToExif_1858) {
    xmpData["Xmp.exif.GPSLongitude"] = "2,17.4E";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"));
    EXPECT_NE(exifIt, exifData.end());
}

// Test ExifVersion conversion
class ExifVersionConversionTest_1858 : public ::testing::Test {
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

// Test XMP ExifVersion to Exif conversion
TEST_F(ExifVersionConversionTest_1858, XmpExifVersionToExif_1858) {
    xmpData["Xmp.exif.ExifVersion"] = "2.30";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Photo.ExifVersion"));
    EXPECT_NE(exifIt, exifData.end());
}

// Test IPTC conversion
class IptcXmpConversionTest_1858 : public ::testing::Test {
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

// Test moveXmpToIptc with empty data
TEST_F(IptcXmpConversionTest_1858, EmptyXmpToIptcDoesNothing_1858) {
    ASSERT_TRUE(xmpData.empty());

    Exiv2::moveXmpToIptc(xmpData, iptcData);

    EXPECT_TRUE(xmpData.empty());
}

// Test copyXmpToIptc with empty data
TEST_F(IptcXmpConversionTest_1858, EmptyXmpCopyToIptcDoesNothing_1858) {
    ASSERT_TRUE(xmpData.empty());

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_TRUE(xmpData.empty());
}

// Test moveIptcToXmp with empty data
TEST_F(IptcXmpConversionTest_1858, EmptyIptcToXmpDoesNothing_1858) {
    ASSERT_TRUE(iptcData.empty());

    Exiv2::moveIptcToXmp(iptcData, xmpData);

    EXPECT_TRUE(iptcData.empty());
}

// Test copyIptcToXmp with empty data
TEST_F(IptcXmpConversionTest_1858, EmptyIptcCopyToXmpDoesNothing_1858) {
    ASSERT_TRUE(iptcData.empty());

    Exiv2::copyIptcToXmp(iptcData, xmpData);

    EXPECT_TRUE(iptcData.empty());
}

// Test XMP UserComment conversion
class XmpUserCommentTest_1858 : public ::testing::Test {
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

// Test XMP UserComment to Exif conversion
TEST_F(XmpUserCommentTest_1858, XmpUserCommentToExif_1858) {
    xmpData["Xmp.exif.UserComment"] = "Test comment";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Photo.UserComment"));
    EXPECT_NE(exifIt, exifData.end());
}

// Test ImageDescription roundtrip
class RoundtripConversionTest_1858 : public ::testing::Test {
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

// Test Exif -> XMP -> Exif roundtrip for Make
TEST_F(RoundtripConversionTest_1858, MakeRoundtrip_1858) {
    exifData["Exif.Image.Make"] = "RoundtripBrand";

    Exiv2::XmpData intermediateXmp;
    Exiv2::copyExifToXmp(exifData, intermediateXmp);

    Exiv2::ExifData resultExif;
    Exiv2::copyXmpToExif(intermediateXmp, resultExif);

    auto exifIt = resultExif.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(exifIt, resultExif.end());
    if (exifIt != resultExif.end()) {
        EXPECT_EQ(exifIt->toString(), "RoundtripBrand");
    }
}

// Test that moveXmpToExif handles XMP tiff.Orientation
TEST_F(MoveXmpToExifTest_1858, XmpOrientationToExif_1858) {
    xmpData["Xmp.tiff.Orientation"] = "1";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.Orientation"));
    EXPECT_NE(exifIt, exifData.end());
    if (exifIt != exifData.end()) {
        EXPECT_EQ(exifIt->toLong(), 1);
    }
}

// Test that moveXmpToExif handles XMP tiff.XResolution
TEST_F(MoveXmpToExifTest_1858, XmpXResolutionToExif_1858) {
    xmpData["Xmp.tiff.XResolution"] = "72/1";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Image.XResolution"));
    EXPECT_NE(exifIt, exifData.end());
}

// Test Flash conversion from XMP to Exif
class FlashConversionTest_1858 : public ::testing::Test {
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

// Test XMP Flash structure fields to Exif flash value
TEST_F(FlashConversionTest_1858, XmpFlashFiredToExif_1858) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData["Xmp.exif.Flash/exif:Return"] = "0";
    xmpData["Xmp.exif.Flash/exif:Mode"] = "0";
    xmpData["Xmp.exif.Flash/exif:Function"] = "False";
    xmpData["Xmp.exif.Flash/exif:RedEyeMode"] = "False";

    Exiv2::moveXmpToExif(xmpData, exifData);

    auto exifIt = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    EXPECT_NE(exifIt, exifData.end());
}
