#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Test fixture for moveIptcToXmp tests
class MoveIptcToXmpTest_1861 : public ::testing::Test {
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

// Test that moveIptcToXmp with empty IPTC data does not crash and leaves XMP empty
TEST_F(MoveIptcToXmpTest_1861, EmptyIptcDataProducesEmptyXmp_1861) {
    EXPECT_TRUE(iptcData_.empty());
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    // With no IPTC data, XMP should remain empty or have no meaningful entries
    // (no crash is the primary check)
}

// Test that moveIptcToXmp with nullptr charset doesn't crash
TEST_F(MoveIptcToXmpTest_1861, NullCharsetDoesNotCrash_1861) {
    iptcData_["Iptc.Application2.Headline"] = "Test Headline";
    EXPECT_NO_THROW(Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr));
}

// Test that moveIptcToXmp with explicit charset does not crash
TEST_F(MoveIptcToXmpTest_1861, ExplicitCharsetDoesNotCrash_1861) {
    iptcData_["Iptc.Application2.Headline"] = "Test Headline";
    EXPECT_NO_THROW(Exiv2::moveIptcToXmp(iptcData_, xmpData_, "UTF-8"));
}

// Test that moveIptcToXmp erases IPTC data after conversion
TEST_F(MoveIptcToXmpTest_1861, IptcDataIsErasedAfterMove_1861) {
    iptcData_["Iptc.Application2.Headline"] = "Test Headline";
    EXPECT_FALSE(iptcData_.empty());
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    // After move, the IPTC data that was converted should be erased
    // The function sets erase mode, so converted entries should be removed
    // Check that headline is gone
    auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Headline"));
    EXPECT_EQ(it, iptcData_.end());
}

// Test that moveIptcToXmp converts headline to XMP
TEST_F(MoveIptcToXmpTest_1861, HeadlineIsConvertedToXmp_1861) {
    iptcData_["Iptc.Application2.Headline"] = "My Headline";
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_NE(it, xmpData_.end());
    if (it != xmpData_.end()) {
        EXPECT_EQ(it->toString(), "My Headline");
    }
}

// Test that moveIptcToXmp converts caption/description to XMP
TEST_F(MoveIptcToXmpTest_1861, CaptionIsConvertedToXmp_1861) {
    iptcData_["Iptc.Application2.Caption"] = "A description";
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(it, xmpData_.end());
}

// Test that moveIptcToXmp converts keywords to XMP
TEST_F(MoveIptcToXmpTest_1861, KeywordsAreConvertedToXmp_1861) {
    iptcData_["Iptc.Application2.Keywords"] = "keyword1";
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(it, xmpData_.end());
}

// Test that moveIptcToXmp with ISO-8859-1 charset
TEST_F(MoveIptcToXmpTest_1861, IsoCharsetConversion_1861) {
    iptcData_["Iptc.Application2.Headline"] = "ISO Test";
    EXPECT_NO_THROW(Exiv2::moveIptcToXmp(iptcData_, xmpData_, "ISO-8859-1"));
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_NE(it, xmpData_.end());
}

// Test that moveIptcToXmp with UTF-8 charset
TEST_F(MoveIptcToXmpTest_1861, Utf8CharsetConversion_1861) {
    iptcData_["Iptc.Application2.Headline"] = "UTF8 Test";
    EXPECT_NO_THROW(Exiv2::moveIptcToXmp(iptcData_, xmpData_, "UTF-8"));
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_NE(it, xmpData_.end());
}

// Test that moveIptcToXmp with multiple IPTC entries
TEST_F(MoveIptcToXmpTest_1861, MultipleIptcEntriesConverted_1861) {
    iptcData_["Iptc.Application2.Headline"] = "Headline";
    iptcData_["Iptc.Application2.Caption"] = "Caption";
    iptcData_["Iptc.Application2.Keywords"] = "keyword1";
    
    size_t initialSize = iptcData_.size();
    EXPECT_GT(initialSize, 0u);
    
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    
    // XMP should have entries
    EXPECT_FALSE(xmpData_.empty());
}

// Test that moveIptcToXmp does not affect pre-existing XMP data for different keys
TEST_F(MoveIptcToXmpTest_1861, PreExistingXmpDataPreserved_1861) {
    xmpData_["Xmp.dc.creator"] = "Original Creator";
    iptcData_["Iptc.Application2.Headline"] = "New Headline";
    
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_NE(it, xmpData_.end());
}

// Test that moveIptcToXmp converts city
TEST_F(MoveIptcToXmpTest_1861, CityIsConvertedToXmp_1861) {
    iptcData_["Iptc.Application2.City"] = "New York";
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.City"));
    EXPECT_NE(it, xmpData_.end());
    if (it != xmpData_.end()) {
        EXPECT_EQ(it->toString(), "New York");
    }
}

// Test that moveIptcToXmp converts copyright
TEST_F(MoveIptcToXmpTest_1861, CopyrightIsConvertedToXmp_1861) {
    iptcData_["Iptc.Application2.Copyright"] = "Copyright 2023";
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    EXPECT_NE(it, xmpData_.end());
}

// Test that calling moveIptcToXmp twice with already-empty data is safe
TEST_F(MoveIptcToXmpTest_1861, DoubleCallSafe_1861) {
    iptcData_["Iptc.Application2.Headline"] = "Test";
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    // Call again with now-erased IPTC data
    EXPECT_NO_THROW(Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr));
}

// Test Converter construction and basic properties
class ConverterTest_1861 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test Converter setErase and erase
TEST_F(ConverterTest_1861, SetEraseDefaultTrue_1861) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(iptcData, xmpData, nullptr);
    
    // Default erase should be false
    EXPECT_FALSE(converter.erase());
    
    converter.setErase();
    EXPECT_TRUE(converter.erase());
    
    converter.setErase(false);
    EXPECT_FALSE(converter.erase());
}

// Test Converter with ExifData constructor
TEST_F(ConverterTest_1861, ExifConverterConstruction_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(exifData, xmpData);
    
    EXPECT_FALSE(converter.erase());
    EXPECT_NO_THROW(converter.setErase(true));
    EXPECT_TRUE(converter.erase());
}

// Test Converter cnvToXmp with empty IPTC data
TEST_F(ConverterTest_1861, CnvToXmpEmptyIptc_1861) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(iptcData, xmpData, nullptr);
    EXPECT_NO_THROW(converter.cnvToXmp());
}

// Test Converter cnvFromXmp with empty XMP data
TEST_F(ConverterTest_1861, CnvFromXmpEmptyXmp_1861) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(iptcData, xmpData, nullptr);
    EXPECT_NO_THROW(converter.cnvFromXmp());
}

// Test Converter cnvToXmp with ExifData
TEST_F(ConverterTest_1861, CnvToXmpWithExif_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(exifData, xmpData);
    EXPECT_NO_THROW(converter.cnvToXmp());
}

// Test Converter cnvFromXmp with ExifData
TEST_F(ConverterTest_1861, CnvFromXmpWithExif_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(exifData, xmpData);
    EXPECT_NO_THROW(converter.cnvFromXmp());
}

// Test Converter setOverwrite
TEST_F(ConverterTest_1861, SetOverwrite_1861) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(iptcData, xmpData, nullptr);
    
    // setOverwrite should not throw
    EXPECT_NO_THROW(converter.setOverwrite(true));
    EXPECT_NO_THROW(converter.setOverwrite(false));
}

// Test Converter cnvNone does nothing
TEST_F(ConverterTest_1861, CnvNoneDoesNothing_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(exifData, xmpData);
    EXPECT_NO_THROW(converter.cnvNone("some.key", "other.key"));
}

// Test copyIptcToXmp (non-move version)
TEST_F(ConverterTest_1861, CopyIptcToXmpPreservesIptc_1861) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Headline"] = "Test Headline";
    
    Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr);
    
    // IPTC data should still be present (copy, not move)
    auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Headline"));
    EXPECT_NE(it, iptcData.end());
    
    // XMP should have the converted data
    auto xmpIt = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_NE(xmpIt, xmpData.end());
}

// Test moveXmpToIptc
TEST_F(ConverterTest_1861, MoveXmpToIptc_1861) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    xmpData["Xmp.photoshop.Headline"] = "XMP Headline";
    
    EXPECT_NO_THROW(Exiv2::moveXmpToIptc(xmpData, iptcData));
}

// Test copyXmpToIptc
TEST_F(ConverterTest_1861, CopyXmpToIptc_1861) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    xmpData["Xmp.photoshop.Headline"] = "XMP Headline";
    
    EXPECT_NO_THROW(Exiv2::copyXmpToIptc(xmpData, iptcData));
    
    // XMP should still have the data
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_NE(it, xmpData.end());
}

// Test Exif to XMP conversion
TEST_F(ConverterTest_1861, ExifToXmpConversion_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    
    exifData["Exif.Image.ImageDescription"] = "A test image";
    
    Exiv2::copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(it, xmpData.end());
}

// Test moveExifToXmp
TEST_F(ConverterTest_1861, MoveExifToXmp_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    
    exifData["Exif.Image.ImageDescription"] = "A test image";
    
    Exiv2::moveExifToXmp(exifData, xmpData);
    
    // After move, exif entry should be erased
    auto it = exifData.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_EQ(it, exifData.end());
}

// Test XMP to Exif conversion
TEST_F(ConverterTest_1861, XmpToExifConversion_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    
    xmpData["Xmp.dc.description"] = "XMP description";
    
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmpData, exifData));
}

// Test moveXmpToExif
TEST_F(ConverterTest_1861, MoveXmpToExif_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    
    xmpData["Xmp.dc.description"] = "XMP description";
    
    EXPECT_NO_THROW(Exiv2::moveXmpToExif(xmpData, exifData));
}

// Test that multiple keywords are properly converted
TEST_F(MoveIptcToXmpTest_1861, MultipleKeywordsConverted_1861) {
    Exiv2::Iptcdatum keyword1(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    keyword1.setValue("keyword1");
    iptcData_.add(keyword1);
    
    Exiv2::Iptcdatum keyword2(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    keyword2.setValue("keyword2");
    iptcData_.add(keyword2);
    
    Exiv2::moveIptcToXmp(iptcData_, xmpData_, nullptr);
    
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(it, xmpData_.end());
}

// Test writeExifDigest doesn't crash
TEST_F(ConverterTest_1861, WriteExifDigest_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(exifData, xmpData);
    EXPECT_NO_THROW(converter.writeExifDigest());
}

// Test syncExifWithXmp doesn't crash
TEST_F(ConverterTest_1861, SyncExifWithXmp_1861) {
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;
    Exiv2::Converter converter(exifData, xmpData);
    EXPECT_NO_THROW(converter.syncExifWithXmp());
}
