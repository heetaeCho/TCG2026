#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// The Converter class is defined in convert.cpp and not exposed in a public header.
// We need to access it. Based on the provided code, it's in the Exiv2 namespace.
// We'll use the public conversion functions that wrap the Converter class,
// or we need to include the internal header.

// Since the Converter class is internal, we'll test through the public API
// functions: copyExifToXmp, copyXmpToExif, etc. or access Converter directly.

// Based on the code provided, Converter is in Exiv2 namespace in convert.cpp.
// We need to declare it or include appropriate headers.

namespace Exiv2 {

// Forward declaration based on the provided interface
class Converter {
public:
    Converter(ExifData& exifData, XmpData& xmpData);
    Converter(IptcData& iptcData, XmpData& xmpData, const char* iptcCharset = nullptr);

    void cnvToXmp();
    void cnvFromXmp();
    void cnvNone(const char*, const char*);
    void cnvExifValue(const char* from, const char* to);
    void cnvExifComment(const char* from, const char* to);
    void cnvExifArray(const char* from, const char* to);
    void cnvExifDate(const char* from, const char* to);
    void cnvExifVersion(const char* from, const char* to);
    void cnvExifGPSVersion(const char* from, const char* to);
    void cnvExifFlash(const char* from, const char* to);
    void cnvExifGPSCoord(const char* from, const char* to);
    void cnvXmpValue(const char* from, const char* to);
    void cnvXmpComment(const char* from, const char* to);
    void cnvXmpArray(const char* from, const char* to);
    void cnvXmpDate(const char* from, const char* to);
    void cnvXmpVersion(const char* from, const char* to);
    void cnvXmpGPSVersion(const char* from, const char* to);
    void cnvXmpFlash(const char* from, const char* to);
    void cnvXmpGPSCoord(const char* from, const char* to);
    void cnvIptcValue(const char* from, const char* to);
    void cnvXmpValueToIptc(const char* from, const char* to);
    void writeExifDigest();
    void syncExifWithXmp();
    void setErase(bool onoff = true);
    void setOverwrite(bool onoff = true);
    bool erase() const;
};

} // namespace Exiv2

class ConverterTest_1848 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
    Exiv2::IptcData iptcData_;

    void SetUp() override {
        // Initialize XMP parser
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test: cnvXmpGPSVersion converts dots to spaces when XMP key exists
TEST_F(ConverterTest_1848, CnvXmpGPSVersion_NormalConversion_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    // Set the XMP GPS version with dots
    xmpData_["Xmp.exif.GPSVersionID"] = "2.2.0.0";

    converter.cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID");

    // Check that the Exif value has spaces instead of dots
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    ASSERT_NE(pos, exifData_.end());
    std::string result = pos->toString();
    // Dots should be replaced with spaces
    EXPECT_EQ(result.find('.'), std::string::npos);
    EXPECT_NE(result.find(' '), std::string::npos);
}

// Test: cnvXmpGPSVersion does nothing when XMP key does not exist
TEST_F(ConverterTest_1848, CnvXmpGPSVersion_KeyNotFound_NoConversion_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    // Don't add any XMP data
    converter.cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID");

    // Exif data should remain empty
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    EXPECT_EQ(pos, exifData_.end());
}

// Test: cnvXmpGPSVersion with erase flag removes the XMP source
TEST_F(ConverterTest_1848, CnvXmpGPSVersion_EraseEnabled_RemovesSource_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setErase(true);

    xmpData_["Xmp.exif.GPSVersionID"] = "2.2.0.0";

    converter.cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID");

    // XMP data should be erased
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    EXPECT_EQ(xmpPos, xmpData_.end());

    // Exif data should exist
    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    EXPECT_NE(exifPos, exifData_.end());
}

// Test: cnvXmpGPSVersion with erase flag disabled does not remove the XMP source
TEST_F(ConverterTest_1848, CnvXmpGPSVersion_EraseDisabled_KeepsSource_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setErase(false);

    xmpData_["Xmp.exif.GPSVersionID"] = "2.2.0.0";

    converter.cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID");

    // XMP data should still exist
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    EXPECT_NE(xmpPos, xmpData_.end());
}

// Test: cnvXmpGPSVersion with value containing no dots
TEST_F(ConverterTest_1848, CnvXmpGPSVersion_NoDots_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.exif.GPSVersionID"] = "2 2 0 0";

    converter.cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    ASSERT_NE(pos, exifData_.end());
    std::string result = pos->toString();
    // Should remain unchanged since no dots to replace
    EXPECT_NE(result.find(' '), std::string::npos);
}

// Test: cnvXmpGPSVersion with overwrite disabled and existing target
TEST_F(ConverterTest_1848, CnvXmpGPSVersion_OverwriteDisabled_ExistingTarget_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setOverwrite(false);

    // Pre-populate the exif target
    exifData_["Exif.GPSInfo.GPSVersionID"] = "1 0 0 0";

    xmpData_["Xmp.exif.GPSVersionID"] = "2.2.0.0";

    converter.cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID");

    // With overwrite disabled, existing target should not be overwritten
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    ASSERT_NE(pos, exifData_.end());
}

// Test: Converter setErase and erase getter
TEST_F(ConverterTest_1848, SetEraseAndGetErase_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    // Default should be false
    EXPECT_FALSE(converter.erase());

    converter.setErase(true);
    EXPECT_TRUE(converter.erase());

    converter.setErase(false);
    EXPECT_FALSE(converter.erase());
}

// Test: Converter with ExifData and XmpData constructor
TEST_F(ConverterTest_1848, ExifXmpConstructor_1848) {
    EXPECT_NO_THROW({
        Exiv2::Converter converter(exifData_, xmpData_);
    });
}

// Test: Converter with IptcData and XmpData constructor
TEST_F(ConverterTest_1848, IptcXmpConstructor_1848) {
    EXPECT_NO_THROW({
        Exiv2::Converter converter(iptcData_, xmpData_, nullptr);
    });
}

// Test: cnvToXmp and cnvFromXmp basic functionality (no crash)
TEST_F(ConverterTest_1848, CnvToXmpNoCrashOnEmpty_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvToXmp());
}

TEST_F(ConverterTest_1848, CnvFromXmpNoCrashOnEmpty_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvFromXmp());
}

// Test: cnvNone does nothing
TEST_F(ConverterTest_1848, CnvNone_DoesNothing_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvNone("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID"));
    EXPECT_TRUE(exifData_.empty());
}

// Test: cnvExifValue basic conversion
TEST_F(ConverterTest_1848, CnvExifValue_BasicConversion_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    exifData_["Exif.Image.Make"] = "TestCamera";

    converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: cnvExifValue when source key does not exist
TEST_F(ConverterTest_1848, CnvExifValue_SourceNotFound_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    EXPECT_EQ(pos, xmpData_.end());
}

// Test: cnvXmpValue basic conversion
TEST_F(ConverterTest_1848, CnvXmpValue_BasicConversion_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.tiff.Make"] = "TestCamera";

    converter.cnvXmpValue("Xmp.tiff.Make", "Exif.Image.Make");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(pos, exifData_.end());
}

// Test: cnvXmpValue when source key does not exist
TEST_F(ConverterTest_1848, CnvXmpValue_SourceNotFound_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    converter.cnvXmpValue("Xmp.tiff.Make", "Exif.Image.Make");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_EQ(pos, exifData_.end());
}

// Test: cnvXmpGPSVersion with multiple dots in version string
TEST_F(ConverterTest_1848, CnvXmpGPSVersion_MultipleDots_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    xmpData_["Xmp.exif.GPSVersionID"] = "2.3.0.0";

    converter.cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID");

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    ASSERT_NE(pos, exifData_.end());
    std::string result = pos->toString();
    // All dots should be replaced
    EXPECT_EQ(result.find('.'), std::string::npos);
}

// Test: Full round-trip conversion Exif -> XMP -> Exif for GPS version
TEST_F(ConverterTest_1848, RoundTrip_ExifToXmpToExif_GPSVersion_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    // Set Exif GPS version (space-separated)
    exifData_["Exif.GPSInfo.GPSVersionID"] = "2 2 0 0";

    // Convert Exif to XMP
    converter.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.exif.GPSVersionID");

    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(xmpPos, xmpData_.end());

    // Now clear exif data and convert back
    exifData_.clear();
    converter.cnvXmpGPSVersion("Xmp.exif.GPSVersionID", "Exif.GPSInfo.GPSVersionID");

    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    EXPECT_NE(exifPos, exifData_.end());
}

// Test: cnvExifVersion basic functionality
TEST_F(ConverterTest_1848, CnvExifVersion_Basic_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    exifData_["Exif.Photo.ExifVersion"] = "48 50 51 48";

    converter.cnvExifVersion("Exif.Photo.ExifVersion", "Xmp.exif.ExifVersion");

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    // May or may not exist depending on value format, but should not crash
}

// Test: cnvExifVersion source not found
TEST_F(ConverterTest_1848, CnvExifVersion_SourceNotFound_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    converter.cnvExifVersion("Exif.Photo.ExifVersion", "Xmp.exif.ExifVersion");

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    EXPECT_EQ(pos, xmpData_.end());
}

// Test: IptcData conversion - cnvIptcValue
TEST_F(ConverterTest_1848, CnvIptcValue_BasicConversion_1848) {
    Exiv2::Converter converter(iptcData_, xmpData_, nullptr);

    iptcData_["Iptc.Application2.Headline"] = "Test Headline";

    converter.cnvIptcValue("Iptc.Application2.Headline", "Xmp.photoshop.Headline");

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_NE(pos, xmpData_.end());
}

// Test: IptcData conversion - source not found
TEST_F(ConverterTest_1848, CnvIptcValue_SourceNotFound_1848) {
    Exiv2::Converter converter(iptcData_, xmpData_, nullptr);

    converter.cnvIptcValue("Iptc.Application2.Headline", "Xmp.photoshop.Headline");

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_EQ(pos, xmpData_.end());
}

// Test: setOverwrite functionality
TEST_F(ConverterTest_1848, SetOverwrite_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);

    // Should not throw
    EXPECT_NO_THROW(converter.setOverwrite(true));
    EXPECT_NO_THROW(converter.setOverwrite(false));
}

// Test: writeExifDigest does not crash on empty data
TEST_F(ConverterTest_1848, WriteExifDigest_EmptyData_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.writeExifDigest());
}

// Test: syncExifWithXmp does not crash on empty data
TEST_F(ConverterTest_1848, SyncExifWithXmp_EmptyData_1848) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.syncExifWithXmp());
}
