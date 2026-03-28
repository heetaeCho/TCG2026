#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// The Converter class is defined in convert.cpp and not directly exposed via a public header.
// We need to use the public conversion functions that wrap it, or access it through
// the functions declared in convert.hpp
#include <exiv2/convert.hpp>

namespace {

// Helper to set up XmpData with flash struct fields
void setXmpFlashField(Exiv2::XmpData& xmpData, const std::string& base, const std::string& field, const std::string& value) {
    xmpData[base + "/" + field] = value;
}

class CnvXmpFlashTest_1849 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData;
    Exiv2::XmpData xmpData;

    void SetUp() override {
        exifData.clear();
        xmpData.clear();
    }
};

// Test: When exif:Fired is not present in XmpData, no conversion happens
TEST_F(CnvXmpFlashTest_1849, NoFiredField_NoConversion_1849) {
    // Don't add any flash fields
    // Use the high-level conversion which internally calls cnvXmpFlash
    // We test by converting from XMP to Exif
    Exiv2::copyXmpToExif(xmpData, exifData);

    // Flash tag (Exif.Photo.Flash = 0x9209) should not be set
    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    EXPECT_EQ(pos, exifData.end());
}

// Test: When only Fired=1 is set, value should be 1
TEST_F(CnvXmpFlashTest_1849, OnlyFiredSet_1849) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "True";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        // Fired bit is bit 0
        EXPECT_EQ(val & 1, 1u);
    }
}

// Test: When Fired=0, value should have bit 0 clear
TEST_F(CnvXmpFlashTest_1849, FiredFalse_1849) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "False";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        EXPECT_EQ(val & 1, 0u);
    }
}

// Test: All flash fields set - comprehensive test
TEST_F(CnvXmpFlashTest_1849, AllFieldsSet_1849) {
    // Fired = 1 (bit 0)
    xmpData["Xmp.exif.Flash/exif:Fired"] = "True";
    // Return = 2 (bits 1-2)
    xmpData["Xmp.exif.Flash/exif:Return"] = "2";
    // Mode = 1 (bits 3-4)
    xmpData["Xmp.exif.Flash/exif:Mode"] = "1";
    // Function = 1 (bit 5)
    xmpData["Xmp.exif.Flash/exif:Function"] = "1";
    // RedEyeMode = 1 (bit 6)
    xmpData["Xmp.exif.Flash/exif:RedEyeMode"] = "True";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        // Expected: bit0=1, bits1-2=2(0b10), bits3-4=1(0b01), bit5=1, bit6=1
        // = 1 | (2<<1) | (1<<3) | (1<<5) | (1<<6)
        // = 1 | 4 | 8 | 32 | 64 = 109
        EXPECT_EQ(val, 109u);
    }
}

// Test: Return field with value 3 (max for 2-bit mask)
TEST_F(CnvXmpFlashTest_1849, ReturnMaxValue_1849) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "False";
    xmpData["Xmp.exif.Flash/exif:Return"] = "3";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        // Return = 3, shifted left 1 = 6
        EXPECT_EQ(val & 0x06, 6u);
    }
}

// Test: Mode field with value 3 (max for 2-bit mask)
TEST_F(CnvXmpFlashTest_1849, ModeMaxValue_1849) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "False";
    xmpData["Xmp.exif.Flash/exif:Mode"] = "3";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        // Mode = 3, shifted left 3 = 24
        EXPECT_EQ(val & 0x18, 24u);
    }
}

// Test: Only partial fields - Fired and RedEyeMode
TEST_F(CnvXmpFlashTest_1849, PartialFields_FiredAndRedEye_1849) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData["Xmp.exif.Flash/exif:RedEyeMode"] = "True";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        // bit0=1, bit6=1 => 1 + 64 = 65
        EXPECT_EQ(val, 65u);
    }
}

// Test: All fields zero
TEST_F(CnvXmpFlashTest_1849, AllFieldsZero_1849) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "False";
    xmpData["Xmp.exif.Flash/exif:Return"] = "0";
    xmpData["Xmp.exif.Flash/exif:Mode"] = "0";
    xmpData["Xmp.exif.Flash/exif:Function"] = "0";
    xmpData["Xmp.exif.Flash/exif:RedEyeMode"] = "False";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        EXPECT_EQ(val, 0u);
    }
}

// Test: Round-trip conversion Exif -> XMP -> Exif
TEST_F(CnvXmpFlashTest_1849, RoundTripConversion_1849) {
    // Set an Exif flash value
    exifData["Exif.Photo.Flash"] = static_cast<uint16_t>(0x4D); // 77 = fired + return 2 + mode 1 + redeye

    Exiv2::XmpData xmpData2;
    Exiv2::copyExifToXmp(exifData, xmpData2);

    Exiv2::ExifData exifData2;
    Exiv2::copyXmpToExif(xmpData2, exifData2);

    auto pos = exifData2.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData2.end()) {
        uint32_t val = pos->toUint32();
        EXPECT_EQ(val, 0x4Du);
    }
}

// Test: Function field set to 1
TEST_F(CnvXmpFlashTest_1849, FunctionFieldSet_1849) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "False";
    xmpData["Xmp.exif.Flash/exif:Function"] = "1";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        // Function = 1, shifted left 5 = 32
        EXPECT_EQ(val & 0x20, 32u);
    }
}

// Test: Exif to XMP flash conversion
TEST_F(CnvXmpFlashTest_1849, ExifToXmpFlash_1849) {
    // Flash value: Fired=1, Return=2, Mode=1, Function=0, RedEye=1
    // = 1 | (2<<1) | (1<<3) | (0<<5) | (1<<6) = 1+4+8+64 = 77 = 0x4D
    exifData["Exif.Photo.Flash"] = static_cast<uint16_t>(0x4D);

    Exiv2::copyExifToXmp(exifData, xmpData);

    // Verify XMP flash fields were created
    auto posFired = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    EXPECT_NE(posFired, xmpData.end());

    auto posReturn = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Return"));
    EXPECT_NE(posReturn, xmpData.end());

    auto posMode = xmpData.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Mode"));
    EXPECT_NE(posMode, xmpData.end());
}

// Test: When overwrite is not set and target already exists
TEST_F(CnvXmpFlashTest_1849, ExistingExifNotOverwritten_1849) {
    // Pre-set a flash value in exif
    exifData["Exif.Photo.Flash"] = static_cast<uint16_t>(0x00);

    // Set XMP flash fields
    xmpData["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData["Xmp.exif.Flash/exif:Return"] = "3";
    xmpData["Xmp.exif.Flash/exif:Mode"] = "3";
    xmpData["Xmp.exif.Flash/exif:Function"] = "1";
    xmpData["Xmp.exif.Flash/exif:RedEyeMode"] = "True";

    // Default overwrite is true, so it should overwrite
    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    ASSERT_NE(pos, exifData.end());
    // With overwrite=true (default), value should be updated
    uint32_t val = pos->toUint32();
    // Expected: 1 | (3<<1) | (3<<3) | (1<<5) | (1<<6) = 1+6+24+32+64 = 127
    EXPECT_EQ(val, 127u);
}

// Test: Empty XmpData conversion produces no exif flash
TEST_F(CnvXmpFlashTest_1849, EmptyXmpData_1849) {
    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    EXPECT_EQ(pos, exifData.end());
}

// Test: Only Fired field with no other flash fields
TEST_F(CnvXmpFlashTest_1849, OnlyFiredNoOtherFields_1849) {
    xmpData["Xmp.exif.Flash/exif:Fired"] = "True";

    Exiv2::copyXmpToExif(xmpData, exifData);

    auto pos = exifData.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData.end()) {
        uint32_t val = pos->toUint32();
        // Only fired bit should be set
        EXPECT_EQ(val, 1u);
    }
}

}  // namespace
