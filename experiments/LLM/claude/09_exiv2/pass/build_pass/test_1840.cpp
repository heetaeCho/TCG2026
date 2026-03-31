#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// We need access to the Converter class which is defined in convert.cpp
// The public API for conversion is through copyExifToXmp, copyXmpToExif, etc.
// But based on the partial code, we need to test the Converter class directly.
// Since Converter is in the Exiv2 namespace but may not be in a public header,
// we include the necessary headers and use the convert functions.

// The Converter class is internal to convert.cpp, so we test through the
// public API functions: copyExifToXmp, copyXmpToExif, moveExifToXmp, etc.
// However, looking at the interface, Converter is directly constructible.

// Since the class is defined in convert.cpp (not a header), we may need to
// access it through the public conversion API. Let's test using the public
// free functions that use Converter internally, and also test what we can
// construct directly if the header is available.

// Based on the exiv2 public API, the conversion functions are:
// void copyExifToXmp(const ExifData&, XmpData&);
// void moveExifToXmp(ExifData&, XmpData&);
// void copyXmpToExif(const XmpData&, ExifData&);
// void moveXmpToExif(XmpData&, ExifData&);

namespace {

class ConverterTest_1840 : public ::testing::Test {
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

// Test: GPSVersionID conversion from Exif to XMP with standard version 2.3.0.0
TEST_F(ConverterTest_1840, CnvExifGPSVersion_StandardVersion_1840) {
    // Set GPSVersionID to 2.3.0.0 (standard GPS IFD version)
    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 3 0 0");
    exifData_.add(key, val.get());

    // Convert Exif to XMP
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    // Check that GPSVersionID was converted
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(pos, xmpData_.end());
    EXPECT_EQ(pos->toString(), "2.3.0.0");
}

// Test: GPSVersionID conversion from Exif to XMP with version 2.2.0.0
TEST_F(ConverterTest_1840, CnvExifGPSVersion_Version2200_1840) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 2 0 0");
    exifData_.add(key, val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(pos, xmpData_.end());
    EXPECT_EQ(pos->toString(), "2.2.0.0");
}

// Test: When source key doesn't exist, XMP should not be modified
TEST_F(ConverterTest_1840, CnvExifGPSVersion_MissingSource_1840) {
    // Don't add any GPS version to exifData_
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    EXPECT_EQ(pos, xmpData_.end());
}

// Test: moveExifToXmp should erase the source Exif key
TEST_F(ConverterTest_1840, MoveExifGPSVersion_ErasesSource_1840) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 3 0 0");
    exifData_.add(key, val.get());

    Exiv2::moveExifToXmp(exifData_, xmpData_);

    // Source should be erased
    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    EXPECT_EQ(exifPos, exifData_.end());

    // XMP should have the value
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(xmpPos, xmpData_.end());
    EXPECT_EQ(xmpPos->toString(), "2.3.0.0");
}

// Test: copyExifToXmp should NOT erase the source Exif key
TEST_F(ConverterTest_1840, CopyExifGPSVersion_PreservesSource_1840) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 3 0 0");
    exifData_.add(key, val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    // Source should still exist
    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    EXPECT_NE(exifPos, exifData_.end());
}

// Test: XMP target already has a value - copyExifToXmp should overwrite by default
TEST_F(ConverterTest_1840, CnvExifGPSVersion_OverwriteExisting_1840) {
    // Pre-populate XMP with a different value
    xmpData_["Xmp.exif.GPSVersionID"] = "1.0.0.0";

    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 3 0 0");
    exifData_.add(key, val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(pos, xmpData_.end());
    EXPECT_EQ(pos->toString(), "2.3.0.0");
}

// Test: GPSVersionID with all zeros
TEST_F(ConverterTest_1840, CnvExifGPSVersion_AllZeros_1840) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("0 0 0 0");
    exifData_.add(key, val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(pos, xmpData_.end());
    EXPECT_EQ(pos->toString(), "0.0.0.0");
}

// Test: GPSVersionID with maximum byte values
TEST_F(ConverterTest_1840, CnvExifGPSVersion_MaxValues_1840) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("255 255 255 255");
    exifData_.add(key, val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(pos, xmpData_.end());
    EXPECT_EQ(pos->toString(), "255.255.255.255");
}

// Test: Reverse conversion - XMP GPSVersionID to Exif
TEST_F(ConverterTest_1840, CnvXmpGPSVersion_ToExif_1840) {
    xmpData_["Xmp.exif.GPSVersionID"] = "2.3.0.0";

    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    ASSERT_NE(pos, exifData_.end());
    // The GPS version should have 4 components
    EXPECT_EQ(pos->count(), 4u);
    EXPECT_EQ(pos->toInt64(0), 2);
    EXPECT_EQ(pos->toInt64(1), 3);
    EXPECT_EQ(pos->toInt64(2), 0);
    EXPECT_EQ(pos->toInt64(3), 0);
}

// Test: Reverse conversion - moveXmpToExif should erase XMP source
TEST_F(ConverterTest_1840, MoveXmpGPSVersion_ErasesXmpSource_1840) {
    xmpData_["Xmp.exif.GPSVersionID"] = "2.3.0.0";

    Exiv2::moveXmpToExif(xmpData_, exifData_);

    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    EXPECT_EQ(xmpPos, xmpData_.end());

    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    ASSERT_NE(exifPos, exifData_.end());
}

// Test: Empty ExifData and XmpData - conversion should not crash
TEST_F(ConverterTest_1840, CopyExifToXmp_EmptyData_1840) {
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
    EXPECT_TRUE(xmpData_.empty());
}

// Test: Empty XmpData to ExifData - conversion should not crash
TEST_F(ConverterTest_1840, CopyXmpToExif_EmptyData_1840) {
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
    EXPECT_TRUE(exifData_.empty());
}

// Test: ExifVersion conversion
TEST_F(ConverterTest_1840, CnvExifVersion_StandardVersion_1840) {
    Exiv2::ExifKey key("Exif.Photo.ExifVersion");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::undefined);
    val->read("48 50 51 48"); // "0230" in ASCII
    exifData_.add(key, val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    ASSERT_NE(pos, xmpData_.end());
}

// Test: Multiple conversions - both GPS version and other data
TEST_F(ConverterTest_1840, CopyExifToXmp_MultipleFields_1840) {
    // Add GPSVersionID
    {
        Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
        Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
        val->read("2 3 0 0");
        exifData_.add(key, val.get());
    }

    // Add a simple Exif value
    exifData_["Exif.Image.ImageWidth"] = uint32_t(1920);

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto gpsPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(gpsPos, xmpData_.end());
    EXPECT_EQ(gpsPos->toString(), "2.3.0.0");
}

// Test: GPSVersionID with single component value
TEST_F(ConverterTest_1840, CnvExifGPSVersion_SingleByte_1840) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2");
    exifData_.add(key, val.get());

    Exiv2::copyExifToXmp(exifData_, xmpData_);

    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
    ASSERT_NE(pos, xmpData_.end());
    EXPECT_EQ(pos->toString(), "2");
}

// Test: Round-trip conversion Exif -> XMP -> Exif
TEST_F(ConverterTest_1840, RoundTrip_GPSVersion_1840) {
    // Start with Exif
    Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
    val->read("2 3 0 0");
    exifData_.add(key, val.get());

    // Exif -> XMP
    Exiv2::copyExifToXmp(exifData_, xmpData_);

    // Clear Exif
    exifData_.clear();
    EXPECT_TRUE(exifData_.empty());

    // XMP -> Exif
    Exiv2::copyXmpToExif(xmpData_, exifData_);

    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
    ASSERT_NE(pos, exifData_.end());
    EXPECT_EQ(pos->count(), 4u);
    EXPECT_EQ(pos->toInt64(0), 2);
    EXPECT_EQ(pos->toInt64(1), 3);
    EXPECT_EQ(pos->toInt64(2), 0);
    EXPECT_EQ(pos->toInt64(3), 0);
}

// Test: IPTC to XMP conversion with empty data
TEST_F(ConverterTest_1840, CopyIptcToXmp_EmptyData_1840) {
    EXPECT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));
    EXPECT_TRUE(xmpData_.empty());
}

// Test: XMP to IPTC conversion with empty data
TEST_F(ConverterTest_1840, CopyXmpToIptc_EmptyData_1840) {
    EXPECT_NO_THROW(Exiv2::copyXmpToIptc(xmpData_, iptcData_));
    EXPECT_TRUE(iptcData_.empty());
}

// Test: Move IPTC to XMP with empty data
TEST_F(ConverterTest_1840, MoveIptcToXmp_EmptyData_1840) {
    EXPECT_NO_THROW(Exiv2::moveIptcToXmp(iptcData_, xmpData_));
}

// Test: Move XMP to IPTC with empty data
TEST_F(ConverterTest_1840, MoveXmpToIptc_EmptyData_1840) {
    EXPECT_NO_THROW(Exiv2::moveXmpToIptc(xmpData_, iptcData_));
}

}  // namespace
