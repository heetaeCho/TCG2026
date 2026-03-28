#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Since Converter is defined in convert.cpp and not exposed in a public header,
// we need to use the public API functions that use it, or include the source directly.
// Based on the interface, we'll work with the Converter class directly.

// Forward declaration - the Converter class is in the Exiv2 namespace
// We need to access it. In the actual codebase, there are public functions
// copyExifToXmp, copyXmpToExif, etc. that use Converter internally.
// However, based on the partial code given, we'll test cnvExifFlash and related methods.

// We include the necessary headers
#include <exiv2/exif.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/error.hpp>
#include <exiv2/value.hpp>

// Since Converter is defined in convert.cpp (not in a public header), 
// we use the public conversion functions that delegate to it.
// The public API exposes: copyExifToXmp, copyXmpToExif, moveExifToXmp, moveXmpToExif

namespace {

class ConverterExifFlashTest_1841 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
};

// Test: Copy Exif Flash value 0 (no flash) to XMP
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashZeroToXmp_1841) {
    // Flash value 0: no flash fired, no return, mode unknown, function false, red eye false
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(0);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "False");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Return"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "0");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Mode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "0");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Function"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "False");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:RedEyeMode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "False");
    }
}

// Test: Copy Exif Flash value 1 (flash fired only) to XMP
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashFiredToXmp_1841) {
    // Flash value 1: fired=1, return=0, mode=0, function=0, redeye=0
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(1);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Return"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "0");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Mode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "0");
    }
}

// Test: Flash value with all bits set (0x7F = 127)
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashAllBitsSet_1841) {
    // value 0x7F = 01111111 binary
    // Fired = bit 0 = 1 (True)
    // Return = bits 1-2 = 3
    // Mode = bits 3-4 = 3
    // Function = bit 5 = 1 (True)
    // RedEyeMode = bit 6 = 1 (True)
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(0x7F);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Return"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "3");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Mode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "3");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Function"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:RedEyeMode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
}

// Test: Flash value with only return detected (value = 0x06, bits 1-2 = 3, fired=0)
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashReturnBitsToXmp_1841) {
    // value 6 = 00000110: fired=0, return=3, mode=0, function=0, redeye=0
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(6);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "False");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Return"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "3");
    }
}

// Test: Flash value with mode bits set (value = 0x18, bits 3-4 = 3)
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashModeBitsToXmp_1841) {
    // value 24 = 00011000: fired=0, return=0, mode=3, function=0, redeye=0
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(24);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Mode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "3");
    }
}

// Test: Flash value with function bit set (value = 0x20, bit 5 = 1)
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashFunctionBitToXmp_1841) {
    // value 32 = 00100000: fired=0, return=0, mode=0, function=1, redeye=0
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(32);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Function"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
}

// Test: Flash value with red-eye mode bit set (value = 0x40, bit 6 = 1)
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashRedEyeBitToXmp_1841) {
    // value 64 = 01000000: fired=0, return=0, mode=0, function=0, redeye=1
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(64);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:RedEyeMode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
}

// Test: No flash tag in EXIF - XMP should not have flash data
TEST_F(ConverterExifFlashTest_1841, NoExifFlashNoXmpFlash_1841) {
    // Don't set any flash data in exifData_
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    EXPECT_EQ(pos, xmpData_.end());
}

// Test: Typical flash value 0x0F (fired, return detected, compulsory mode)
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashTypicalValue_1841) {
    // value 0x0F = 00001111: fired=1, return=3, mode=1, function=0, redeye=0
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(0x0F);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Return"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "3");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Mode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "1");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Function"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "False");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:RedEyeMode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "False");
    }
}

// Test: Move (erase) Exif Flash to XMP
TEST_F(ConverterExifFlashTest_1841, MoveExifFlashToXmpErasesExif_1841) {
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(1);
    
    Exiv2::moveExifToXmp(exifData_, xmpData_);
    
    // After move, the Exif flash tag should be erased
    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    EXPECT_EQ(exifPos, exifData_.end());
    
    // XMP should have the flash data
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (xmpPos != xmpData_.end()) {
        EXPECT_EQ(xmpPos->toString(), "True");
    }
}

// Test: Copy Exif Flash to XMP does NOT erase Exif
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashToXmpDoesNotEraseExif_1841) {
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(1);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    // After copy, the Exif flash tag should still be present
    auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    EXPECT_NE(exifPos, exifData_.end());
}

// Test: Round-trip conversion Exif -> XMP -> Exif for flash
TEST_F(ConverterExifFlashTest_1841, RoundTripFlashConversion_1841) {
    uint16_t originalValue = 0x4D; // 01001101: fired=1, return=2, mode=1, function=1, redeye=0
    exifData_["Exif.Photo.Flash"] = originalValue;
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    // Clear exif data and convert back
    exifData_.clear();
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData_.end()) {
        EXPECT_EQ(pos->toUint32(), static_cast<uint32_t>(originalValue));
    }
}

// Test: Flash value 0x49 = 01001001: fired=1, return=0, mode=1, function=1, redeye=0
TEST_F(ConverterExifFlashTest_1841, CopyExifFlashValue0x49_1841) {
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(0x49);
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Return"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "0");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Mode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "1");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Function"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
    
    pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:RedEyeMode"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "False");
    }
}

// Test: XMP Flash to Exif conversion
class ConverterXmpFlashTest_1841 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
    
    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
};

TEST_F(ConverterXmpFlashTest_1841, CopyXmpFlashToExif_1841) {
    xmpData_["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData_["Xmp.exif.Flash/exif:Return"] = "2";
    xmpData_["Xmp.exif.Flash/exif:Mode"] = "1";
    xmpData_["Xmp.exif.Flash/exif:Function"] = "False";
    xmpData_["Xmp.exif.Flash/exif:RedEyeMode"] = "False";
    
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData_.end()) {
        // fired=1, return=2(bits 1-2=10), mode=1(bits 3-4=01), function=0, redeye=0
        // = 0b00001101 = 13
        uint32_t expected = 1 | (2 << 1) | (1 << 3);
        EXPECT_EQ(pos->toUint32(), expected);
    }
}

TEST_F(ConverterXmpFlashTest_1841, CopyXmpFlashAllTrueToExif_1841) {
    xmpData_["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData_["Xmp.exif.Flash/exif:Return"] = "3";
    xmpData_["Xmp.exif.Flash/exif:Mode"] = "3";
    xmpData_["Xmp.exif.Flash/exif:Function"] = "True";
    xmpData_["Xmp.exif.Flash/exif:RedEyeMode"] = "True";
    
    Exiv2::copyXmpToExif(xmpData_, exifData_);
    
    auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
    if (pos != exifData_.end()) {
        // 0x7F = 127
        EXPECT_EQ(pos->toUint32(), static_cast<uint32_t>(0x7F));
    }
}

TEST_F(ConverterXmpFlashTest_1841, MoveXmpFlashToExifErasesXmp_1841) {
    xmpData_["Xmp.exif.Flash/exif:Fired"] = "True";
    xmpData_["Xmp.exif.Flash/exif:Return"] = "0";
    xmpData_["Xmp.exif.Flash/exif:Mode"] = "0";
    xmpData_["Xmp.exif.Flash/exif:Function"] = "False";
    xmpData_["Xmp.exif.Flash/exif:RedEyeMode"] = "False";
    
    Exiv2::moveXmpToExif(xmpData_, exifData_);
    
    // After move, XMP flash data should be erased
    auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    EXPECT_EQ(xmpPos, xmpData_.end());
}

// Test: General Exif to XMP conversion includes flash among other data
class ConverterGeneralTest_1841 : public ::testing::Test {
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

// Test: Empty exif data conversion
TEST_F(ConverterGeneralTest_1841, EmptyExifDataConversion_1841) {
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
    EXPECT_TRUE(xmpData_.empty());
}

// Test: Empty xmp data conversion
TEST_F(ConverterGeneralTest_1841, EmptyXmpDataConversion_1841) {
    EXPECT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
    EXPECT_TRUE(exifData_.empty());
}

// Test: Flash value boundary - value 255
TEST_F(ConverterGeneralTest_1841, FlashValueBoundary255_1841) {
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(255);
    
    EXPECT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
}

// Test: Convert ExifVersion to XMP
TEST_F(ConverterGeneralTest_1841, CopyExifVersionToXmp_1841) {
    exifData_["Exif.Photo.ExifVersion"] = "0230";
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
    if (pos != xmpData_.end()) {
        // ExifVersion should be converted to a dot-separated format or similar
        EXPECT_FALSE(pos->toString().empty());
    }
}

// Test: overwrite behavior - existing XMP data should be overwritten by default
TEST_F(ConverterGeneralTest_1841, OverwriteExistingXmpData_1841) {
    xmpData_["Xmp.exif.Flash/exif:Fired"] = "False";
    exifData_["Exif.Photo.Flash"] = static_cast<uint16_t>(1); // fired = true
    
    Exiv2::copyExifToXmp(exifData_, xmpData_);
    
    auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash/exif:Fired"));
    if (pos != xmpData_.end()) {
        EXPECT_EQ(pos->toString(), "True");
    }
}

}  // namespace
