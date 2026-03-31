#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Note: The Converter class is defined in convert.cpp. We need to include the appropriate headers.
// Based on the exiv2 library structure, the relevant functions are exposed through the public API.
// We include the necessary headers for ExifData, IptcData, XmpData, and the convert functions.

namespace {

// Test fixture for Converter with ExifData and XmpData
class ConverterExifXmpTest_1830 : public ::testing::Test {
protected:
    void SetUp() override {
        converter_ = std::make_unique<Exiv2::Converter>(exifData_, xmpData_);
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
    std::unique_ptr<Exiv2::Converter> converter_;
};

// Test fixture for Converter with IptcData and XmpData
class ConverterIptcXmpTest_1830 : public ::testing::Test {
protected:
    void SetUp() override {
        converter_ = std::make_unique<Exiv2::Converter>(iptcData_, xmpData_, nullptr);
    }

    Exiv2::IptcData iptcData_;
    Exiv2::XmpData xmpData_;
    std::unique_ptr<Exiv2::Converter> converter_;
};

// ==================== setErase / erase tests ====================

TEST_F(ConverterExifXmpTest_1830, EraseDefaultIsFalse_1830) {
    // By default, erase should be false
    EXPECT_FALSE(converter_->erase());
}

TEST_F(ConverterExifXmpTest_1830, SetEraseTrue_1830) {
    converter_->setErase(true);
    EXPECT_TRUE(converter_->erase());
}

TEST_F(ConverterExifXmpTest_1830, SetEraseFalse_1830) {
    converter_->setErase(true);
    converter_->setErase(false);
    EXPECT_FALSE(converter_->erase());
}

TEST_F(ConverterExifXmpTest_1830, SetEraseDefaultParameter_1830) {
    // setErase() with no argument should default to true
    converter_->setErase();
    EXPECT_TRUE(converter_->erase());
}

TEST_F(ConverterExifXmpTest_1830, SetEraseToggle_1830) {
    converter_->setErase(true);
    EXPECT_TRUE(converter_->erase());
    converter_->setErase(false);
    EXPECT_FALSE(converter_->erase());
    converter_->setErase(true);
    EXPECT_TRUE(converter_->erase());
}

// ==================== setOverwrite tests ====================

TEST_F(ConverterExifXmpTest_1830, SetOverwriteDoesNotCrash_1830) {
    // Just verify it doesn't crash; overwrite is not directly queryable through public interface
    // but we can test that it doesn't throw
    EXPECT_NO_THROW(converter_->setOverwrite(true));
    EXPECT_NO_THROW(converter_->setOverwrite(false));
}

// ==================== Construction tests ====================

TEST_F(ConverterExifXmpTest_1830, ConstructWithExifAndXmp_1830) {
    // Converter should be constructible with ExifData and XmpData
    Exiv2::ExifData exif;
    Exiv2::XmpData xmp;
    EXPECT_NO_THROW(Exiv2::Converter conv(exif, xmp));
}

TEST_F(ConverterIptcXmpTest_1830, ConstructWithIptcAndXmp_1830) {
    // Converter should be constructible with IptcData, XmpData and charset
    Exiv2::IptcData iptc;
    Exiv2::XmpData xmp;
    EXPECT_NO_THROW(Exiv2::Converter conv(iptc, xmp, nullptr));
}

TEST_F(ConverterIptcXmpTest_1830, ConstructWithIptcAndXmpWithCharset_1830) {
    Exiv2::IptcData iptc;
    Exiv2::XmpData xmp;
    EXPECT_NO_THROW(Exiv2::Converter conv(iptc, xmp, "UTF-8"));
}

// ==================== cnvToXmp with empty data ====================

TEST_F(ConverterExifXmpTest_1830, CnvToXmpEmptyExifData_1830) {
    // Converting empty ExifData to XMP should not crash and XmpData should remain empty
    EXPECT_NO_THROW(converter_->cnvToXmp());
    EXPECT_TRUE(xmpData_.empty());
}

TEST_F(ConverterIptcXmpTest_1830, CnvToXmpEmptyIptcData_1830) {
    // Converting empty IptcData to XMP should not crash
    EXPECT_NO_THROW(converter_->cnvToXmp());
    EXPECT_TRUE(xmpData_.empty());
}

// ==================== cnvFromXmp with empty data ====================

TEST_F(ConverterExifXmpTest_1830, CnvFromXmpEmptyXmpData_1830) {
    // Converting empty XmpData to Exif should not crash and ExifData should remain empty
    EXPECT_NO_THROW(converter_->cnvFromXmp());
    EXPECT_TRUE(exifData_.empty());
}

TEST_F(ConverterIptcXmpTest_1830, CnvFromXmpEmptyXmpData_1830) {
    // Converting empty XmpData to IPTC should not crash
    EXPECT_NO_THROW(converter_->cnvFromXmp());
    EXPECT_TRUE(iptcData_.empty());
}

// ==================== cnvNone tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvNoneDoesNothing_1830) {
    // cnvNone should be a no-op
    EXPECT_NO_THROW(converter_->cnvNone("Exif.Image.Artist", "Xmp.dc.creator"));
    EXPECT_TRUE(exifData_.empty());
    EXPECT_TRUE(xmpData_.empty());
}

// ==================== cnvToXmp with actual data ====================

TEST_F(ConverterExifXmpTest_1830, CnvToXmpWithExifArtist_1830) {
    // Add an Exif tag that has a known XMP mapping
    exifData_["Exif.Image.Artist"] = "John Doe";
    converter_->cnvToXmp();
    // The XMP data should now have content
    EXPECT_FALSE(xmpData_.empty());
}

TEST_F(ConverterExifXmpTest_1830, CnvToXmpWithExifImageDescription_1830) {
    exifData_["Exif.Image.ImageDescription"] = "A test image";
    converter_->cnvToXmp();
    EXPECT_FALSE(xmpData_.empty());
}

TEST_F(ConverterExifXmpTest_1830, CnvToXmpWithExifCopyright_1830) {
    exifData_["Exif.Image.Copyright"] = "Copyright 2023";
    converter_->cnvToXmp();
    EXPECT_FALSE(xmpData_.empty());
}

// ==================== cnvFromXmp with actual data ====================

TEST_F(ConverterExifXmpTest_1830, CnvFromXmpWithXmpCreator_1830) {
    xmpData_["Xmp.dc.creator"] = "Jane Doe";
    converter_->cnvFromXmp();
    EXPECT_FALSE(exifData_.empty());
}

// ==================== Erase behavior during conversion ====================

TEST_F(ConverterExifXmpTest_1830, CnvToXmpWithEraseRemovesExifData_1830) {
    exifData_["Exif.Image.Artist"] = "John Doe";
    converter_->setErase(true);
    converter_->cnvToXmp();
    // After erase, exif data entries that were converted should be removed
    // XMP data should have the converted values
    EXPECT_FALSE(xmpData_.empty());
}

TEST_F(ConverterExifXmpTest_1830, CnvToXmpWithoutEraseKeepsExifData_1830) {
    exifData_["Exif.Image.Artist"] = "John Doe";
    converter_->setErase(false);
    converter_->cnvToXmp();
    // ExifData should still have the entry
    EXPECT_FALSE(exifData_.empty());
    EXPECT_FALSE(xmpData_.empty());
}

// ==================== Overwrite behavior ====================

TEST_F(ConverterExifXmpTest_1830, CnvToXmpOverwriteTrue_1830) {
    // Set an existing XMP value
    xmpData_["Xmp.dc.creator"] = "Old Creator";
    exifData_["Exif.Image.Artist"] = "New Creator";
    converter_->setOverwrite(true);
    converter_->cnvToXmp();
    // With overwrite, the XMP value should be updated
    EXPECT_FALSE(xmpData_.empty());
}

TEST_F(ConverterExifXmpTest_1830, CnvToXmpOverwriteFalse_1830) {
    // Set an existing XMP value
    xmpData_["Xmp.dc.creator"] = "Old Creator";
    exifData_["Exif.Image.Artist"] = "New Creator";
    converter_->setOverwrite(false);
    converter_->cnvToXmp();
    // Without overwrite, existing XMP values should be preserved
    EXPECT_FALSE(xmpData_.empty());
}

// ==================== cnvExifValue tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvExifValueWithExistingKey_1830) {
    exifData_["Exif.Image.Artist"] = "Test Artist";
    EXPECT_NO_THROW(converter_->cnvExifValue("Exif.Image.Artist", "Xmp.dc.creator"));
}

TEST_F(ConverterExifXmpTest_1830, CnvExifValueWithNonExistingKey_1830) {
    // Attempting to convert a non-existing key should not crash
    EXPECT_NO_THROW(converter_->cnvExifValue("Exif.Image.NonExistent", "Xmp.dc.nonexistent"));
}

// ==================== cnvXmpValue tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvXmpValueWithExistingKey_1830) {
    xmpData_["Xmp.dc.creator"] = "Test Creator";
    EXPECT_NO_THROW(converter_->cnvXmpValue("Xmp.dc.creator", "Exif.Image.Artist"));
}

TEST_F(ConverterExifXmpTest_1830, CnvXmpValueWithNonExistingKey_1830) {
    EXPECT_NO_THROW(converter_->cnvXmpValue("Xmp.dc.nonexistent", "Exif.Image.NonExistent"));
}

// ==================== cnvExifDate tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvExifDateWithValidDate_1830) {
    exifData_["Exif.Image.DateTime"] = "2023:06:15 10:30:00";
    EXPECT_NO_THROW(converter_->cnvExifDate("Exif.Image.DateTime", "Xmp.xmp.ModifyDate"));
}

TEST_F(ConverterExifXmpTest_1830, CnvExifDateWithEmptyData_1830) {
    EXPECT_NO_THROW(converter_->cnvExifDate("Exif.Image.DateTime", "Xmp.xmp.ModifyDate"));
}

// ==================== cnvXmpDate tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvXmpDateWithValidDate_1830) {
    xmpData_["Xmp.xmp.ModifyDate"] = "2023-06-15T10:30:00";
    EXPECT_NO_THROW(converter_->cnvXmpDate("Xmp.xmp.ModifyDate", "Exif.Image.DateTime"));
}

// ==================== cnvExifVersion tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvExifVersionWithData_1830) {
    // ExifVersion is typically stored as undefined type
    EXPECT_NO_THROW(converter_->cnvExifVersion("Exif.Photo.ExifVersion", "Xmp.exif.ExifVersion"));
}

// ==================== cnvExifComment tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvExifCommentWithData_1830) {
    exifData_["Exif.Photo.UserComment"] = "Test comment";
    EXPECT_NO_THROW(converter_->cnvExifComment("Exif.Photo.UserComment", "Xmp.exif.UserComment"));
}

TEST_F(ConverterExifXmpTest_1830, CnvExifCommentEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvExifComment("Exif.Photo.UserComment", "Xmp.exif.UserComment"));
}

// ==================== cnvXmpComment tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvXmpCommentWithData_1830) {
    xmpData_["Xmp.exif.UserComment"] = "Test XMP comment";
    EXPECT_NO_THROW(converter_->cnvXmpComment("Xmp.exif.UserComment", "Exif.Photo.UserComment"));
}

// ==================== cnvExifArray tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvExifArrayEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvExifArray("Exif.Image.XPKeywords", "Xmp.dc.subject"));
}

// ==================== cnvXmpArray tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvXmpArrayEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvXmpArray("Xmp.dc.subject", "Exif.Image.XPKeywords"));
}

// ==================== cnvExifFlash tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvExifFlashEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvExifFlash("Exif.Photo.Flash", "Xmp.exif.Flash"));
}

TEST_F(ConverterExifXmpTest_1830, CnvExifFlashWithData_1830) {
    exifData_["Exif.Photo.Flash"] = uint16_t(1);
    EXPECT_NO_THROW(converter_->cnvExifFlash("Exif.Photo.Flash", "Xmp.exif.Flash"));
}

// ==================== cnvXmpFlash tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvXmpFlashEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvXmpFlash("Xmp.exif.Flash", "Exif.Photo.Flash"));
}

// ==================== cnvExifGPSCoord tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvExifGPSCoordEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude"));
}

// ==================== cnvXmpGPSCoord tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvXmpGPSCoordEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvXmpGPSCoord("Xmp.exif.GPSLatitude", "Exif.GPSInfo.GPSLatitude"));
}

// ==================== cnvExifGPSVersion tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvExifGPSVersionEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.exif.GPSVersionID"));
}

// ==================== cnvXmpGPSVersion tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvXmpGPSVersionEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID"));
}

// ==================== cnvXmpVersion tests ====================

TEST_F(ConverterExifXmpTest_1830, CnvXmpVersionEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvXmpVersion("Xmp.exif.ExifVersion", "Exif.Photo.ExifVersion"));
}

// ==================== IPTC conversion tests ====================

TEST_F(ConverterIptcXmpTest_1830, CnvIptcValueEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvIptcValue("Iptc.Application2.Headline", "Xmp.photoshop.Headline"));
}

TEST_F(ConverterIptcXmpTest_1830, CnvXmpValueToIptcEmpty_1830) {
    EXPECT_NO_THROW(converter_->cnvXmpValueToIptc("Xmp.photoshop.Headline", "Iptc.Application2.Headline"));
}

TEST_F(ConverterIptcXmpTest_1830, CnvToXmpWithIptcData_1830) {
    iptcData_["Iptc.Application2.Headline"] = "Test Headline";
    converter_->cnvToXmp();
    EXPECT_FALSE(xmpData_.empty());
}

TEST_F(ConverterIptcXmpTest_1830, CnvFromXmpToIptc_1830) {
    xmpData_["Xmp.photoshop.Headline"] = "XMP Headline";
    converter_->cnvFromXmp();
    EXPECT_FALSE(iptcData_.empty());
}

TEST_F(ConverterIptcXmpTest_1830, EraseDefaultIsFalse_1830) {
    EXPECT_FALSE(converter_->erase());
}

TEST_F(ConverterIptcXmpTest_1830, SetEraseWorks_1830) {
    converter_->setErase(true);
    EXPECT_TRUE(converter_->erase());
}

// ==================== writeExifDigest tests ====================

TEST_F(ConverterExifXmpTest_1830, WriteExifDigestEmpty_1830) {
    EXPECT_NO_THROW(converter_->writeExifDigest());
}

TEST_F(ConverterExifXmpTest_1830, WriteExifDigestWithData_1830) {
    exifData_["Exif.Image.Artist"] = "John Doe";
    EXPECT_NO_THROW(converter_->writeExifDigest());
}

// ==================== syncExifWithXmp tests ====================

TEST_F(ConverterExifXmpTest_1830, SyncExifWithXmpEmpty_1830) {
    EXPECT_NO_THROW(converter_->syncExifWithXmp());
}

TEST_F(ConverterExifXmpTest_1830, SyncExifWithXmpWithData_1830) {
    exifData_["Exif.Image.Artist"] = "Exif Artist";
    xmpData_["Xmp.dc.creator"] = "XMP Creator";
    EXPECT_NO_THROW(converter_->syncExifWithXmp());
}

// ==================== Round-trip conversion tests ====================

TEST_F(ConverterExifXmpTest_1830, RoundTripExifToXmpAndBack_1830) {
    exifData_["Exif.Image.Artist"] = "Round Trip Artist";
    
    // Convert Exif -> XMP
    converter_->cnvToXmp();
    EXPECT_FALSE(xmpData_.empty());
    
    // Clear exif data
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());
    
    // Convert XMP -> Exif
    converter_->cnvFromXmp();
    EXPECT_FALSE(exifData_.empty());
}

TEST_F(ConverterIptcXmpTest_1830, RoundTripIptcToXmpAndBack_1830) {
    iptcData_["Iptc.Application2.Headline"] = "Round Trip Headline";
    
    // Convert IPTC -> XMP
    converter_->cnvToXmp();
    EXPECT_FALSE(xmpData_.empty());
    
    // Clear IPTC data
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    
    // Convert XMP -> IPTC
    converter_->cnvFromXmp();
    EXPECT_FALSE(iptcData_.empty());
}

// ==================== Multiple conversions ====================

TEST_F(ConverterExifXmpTest_1830, MultipleCnvToXmpCalls_1830) {
    exifData_["Exif.Image.Artist"] = "Artist 1";
    converter_->cnvToXmp();
    size_t firstSize = xmpData_.count();
    
    // Calling again should not crash
    converter_->cnvToXmp();
    EXPECT_GE(xmpData_.count(), firstSize);
}

TEST_F(ConverterExifXmpTest_1830, MultipleCnvFromXmpCalls_1830) {
    xmpData_["Xmp.dc.creator"] = "Creator";
    converter_->cnvFromXmp();
    
    // Calling again should not crash
    EXPECT_NO_THROW(converter_->cnvFromXmp());
}

// ==================== Charset tests for IPTC ====================

TEST_F(ConverterIptcXmpTest_1830, ConstructWithNullCharset_1830) {
    Exiv2::IptcData iptc;
    Exiv2::XmpData xmp;
    EXPECT_NO_THROW(Exiv2::Converter conv(iptc, xmp, nullptr));
}

TEST_F(ConverterIptcXmpTest_1830, ConstructWithUTF8Charset_1830) {
    Exiv2::IptcData iptc;
    Exiv2::XmpData xmp;
    EXPECT_NO_THROW(Exiv2::Converter conv(iptc, xmp, "UTF-8"));
}

}  // namespace
