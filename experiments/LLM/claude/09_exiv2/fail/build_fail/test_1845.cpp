#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Since Converter is defined in convert.cpp and not directly exposed via a public header,
// we need to use the public conversion functions or access the Converter class.
// Based on the provided interface, we'll work with the Converter class directly.
// In practice, exiv2 exposes copyExifToXmp/copyXmpToExif functions that use Converter internally.
// We'll include the necessary headers and test cnvXmpArray through the Converter interface.

// Forward declaration - Converter is in Exiv2 namespace but defined in convert.cpp
// We need to access it. In the actual codebase, it may be accessible through internal headers.
// For testing purposes, we include the source or rely on linkage.

namespace {

class ConverterCnvXmpArrayTest_1845 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;

    void SetUp() override {
        // Ensure XMP parser is initialized
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test: When XMP source key does not exist, exifData should remain unchanged
TEST_F(ConverterCnvXmpArrayTest_1845, XmpKeyNotFound_ExifDataUnchanged_1845) {
    // xmpData_ is empty, so findKey should return end()
    Exiv2::Converter converter(exifData_, xmpData_);

    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.XPKeywords");

    // ExifData should remain empty since XMP key was not found
    EXPECT_TRUE(exifData_.empty());
}

// Test: When XMP source has a single value, it should be converted to exif target
TEST_F(ConverterCnvXmpArrayTest_1845, SingleValueArray_ConvertsToExif_1845) {
    // Add a single XMP value - use dc.subject which is a bag (array type)
    xmpData_["Xmp.dc.subject"] = "keyword1";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.ImageDescription");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        EXPECT_EQ(pos->toString(), "keyword1");
    }
}

// Test: When XMP source has multiple values, they should be joined with spaces
TEST_F(ConverterCnvXmpArrayTest_1845, MultipleValueArray_JoinedWithSpaces_1845) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto value = Exiv2::Value::create(Exiv2::xmpBag);
    value->read("val1");
    value->read("val2");
    value->read("val3");
    xmpData_.add(key, value.get());

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.ImageDescription");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        std::string result = pos->toString();
        EXPECT_EQ(result, "val1 val2 val3");
    }
}

// Test: Erase mode - when erase is set, XMP source should be erased after conversion
TEST_F(ConverterCnvXmpArrayTest_1845, EraseMode_XmpSourceErased_1845) {
    xmpData_["Xmp.dc.subject"] = "keyword1";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setErase(true);
    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.ImageDescription");

    // XMP data should be erased
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_EQ(xmpPos, xmpData_.end());

    // Exif data should have the value
    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(exifPos, exifData_.end());
}

// Test: Without erase mode, XMP source should remain after conversion
TEST_F(ConverterCnvXmpArrayTest_1845, NoEraseMode_XmpSourceRemains_1845) {
    xmpData_["Xmp.dc.subject"] = "keyword1";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setErase(false);
    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.ImageDescription");

    // XMP data should still exist
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(xmpPos, xmpData_.end());
}

// Test: Overwrite disabled - if exif target already exists, it should not be overwritten
TEST_F(ConverterCnvXmpArrayTest_1845, OverwriteDisabled_ExistingExifNotOverwritten_1845) {
    // Set existing EXIF value
    exifData_["Exif.Image.ImageDescription"] = "original";

    // Set XMP value
    xmpData_["Xmp.dc.subject"] = "newvalue";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setOverwrite(false);
    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.ImageDescription");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        // Should remain as original since overwrite is disabled
        EXPECT_EQ(pos->toString(), "original");
    }
}

// Test: Overwrite enabled - if exif target already exists, it should be overwritten
TEST_F(ConverterCnvXmpArrayTest_1845, OverwriteEnabled_ExistingExifOverwritten_1845) {
    // Set existing EXIF value
    exifData_["Exif.Image.ImageDescription"] = "original";

    // Set XMP value
    xmpData_["Xmp.dc.subject"] = "newvalue";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setOverwrite(true);
    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.ImageDescription");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        EXPECT_EQ(pos->toString(), "newvalue");
    }
}

// Test: Two-value array should be joined with single space
TEST_F(ConverterCnvXmpArrayTest_1845, TwoValueArray_JoinedCorrectly_1845) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto value = Exiv2::Value::create(Exiv2::xmpBag);
    value->read("alpha");
    value->read("beta");
    xmpData_.add(key, value.get());

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.ImageDescription");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        EXPECT_EQ(pos->toString(), "alpha beta");
    }
}

// Test: Default erase setting should be false
TEST_F(ConverterCnvXmpArrayTest_1845, DefaultEraseIsFalse_1845) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_FALSE(converter.erase());
}

// Test: setErase changes erase state
TEST_F(ConverterCnvXmpArrayTest_1845, SetEraseChangesState_1845) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setErase(true);
    EXPECT_TRUE(converter.erase());
    converter.setErase(false);
    EXPECT_FALSE(converter.erase());
}

// Test: Empty XMP data - cnvXmpArray should do nothing
TEST_F(ConverterCnvXmpArrayTest_1845, EmptyXmpData_NoEffect_1845) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvXmpArray("Xmp.dc.subject", "Exif.Image.ImageDescription");

    EXPECT_TRUE(exifData_.empty());
    EXPECT_TRUE(xmpData_.empty());
}

// Test: XMP seq type array conversion
TEST_F(ConverterCnvXmpArrayTest_1845, XmpSeqArray_ConvertsToExif_1845) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    auto value = Exiv2::Value::create(Exiv2::xmpSeq);
    value->read("author1");
    value->read("author2");
    xmpData_.add(key, value.get());

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvXmpArray("Xmp.dc.creator", "Exif.Image.Artist");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
    EXPECT_NE(pos, exifData_.end());
    if (pos != exifData_.end()) {
        EXPECT_EQ(pos->toString(), "author1 author2");
    }
}

}  // namespace
