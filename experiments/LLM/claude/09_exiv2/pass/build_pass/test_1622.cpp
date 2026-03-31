#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMisc3cSonyImageHeightTest_1622 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to set the camera model in ExifData
    void setModel(ExifData& exifData, const std::string& model) {
        exifData["Exif.Image.Model"] = model;
    }

    // Create an unsignedShort value with a single entry
    Value::UniquePtr createUShortValue(uint16_t val) {
        auto v = Value::create(unsignedShort);
        v->read(std::to_string(val));
        return v;
    }

    // Create a signedShort value with a single entry
    Value::UniquePtr createSignedShortValue(int16_t val) {
        auto v = Value::create(signedShort);
        v->read(std::to_string(val));
        return v;
    }

    // Create an unsignedLong value with a single entry
    Value::UniquePtr createULongValue(uint32_t val) {
        auto v = Value::create(unsignedLong);
        v->read(std::to_string(val));
        return v;
    }

    // Create an unsignedShort value with multiple entries
    Value::UniquePtr createMultiUShortValue(uint16_t val1, uint16_t val2) {
        auto v = Value::create(unsignedShort);
        v->read(std::to_string(val1) + " " + std::to_string(val2));
        return v;
    }
};

// Test: null metadata pointer should output parenthesized value
TEST_F(SonyMisc3cSonyImageHeightTest_1622, NullMetadata_1622) {
    auto value = createUShortValue(100);
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: wrong type (not unsignedShort) should output parenthesized value
TEST_F(SonyMisc3cSonyImageHeightTest_1622, WrongType_1622) {
    auto value = createULongValue(100);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: multiple values (count != 1) should output parenthesized value
TEST_F(SonyMisc3cSonyImageHeightTest_1622, MultipleValues_1622) {
    auto value = createMultiUShortValue(100, 200);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: no model in metadata should output parenthesized value
TEST_F(SonyMisc3cSonyImageHeightTest_1622, NoModelInMetadata_1622) {
    auto value = createUShortValue(100);
    ExifData exifData;
    // Don't set any model
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: model ILCE-1 should output "n/a"
TEST_F(SonyMisc3cSonyImageHeightTest_1622, ModelILCE1_ReturnsNA_1622) {
    auto value = createUShortValue(500);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: model ILCE-7M4 should output "n/a"
TEST_F(SonyMisc3cSonyImageHeightTest_1622, ModelILCE7M4_ReturnsNA_1622) {
    auto value = createUShortValue(500);
    ExifData exifData;
    setModel(exifData, "ILCE-7M4");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: model ILCE-7RM5 should output "n/a"
TEST_F(SonyMisc3cSonyImageHeightTest_1622, ModelILCE7RM5_ReturnsNA_1622) {
    auto value = createUShortValue(500);
    ExifData exifData;
    setModel(exifData, "ILCE-7RM5");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: model ILCE-7SM3 should output "n/a"
TEST_F(SonyMisc3cSonyImageHeightTest_1622, ModelILCE7SM3_ReturnsNA_1622) {
    auto value = createUShortValue(500);
    ExifData exifData;
    setModel(exifData, "ILCE-7SM3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: model ILME-FX3 should output "n/a"
TEST_F(SonyMisc3cSonyImageHeightTest_1622, ModelILMEFX3_ReturnsNA_1622) {
    auto value = createUShortValue(500);
    ExifData exifData;
    setModel(exifData, "ILME-FX3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: supported model with positive value should output 8 * value
TEST_F(SonyMisc3cSonyImageHeightTest_1622, PositiveValue_Multiplied_1622) {
    auto value = createUShortValue(500);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "4000");
}

// Test: supported model with value 1 should output 8
TEST_F(SonyMisc3cSonyImageHeightTest_1622, ValueOne_Returns8_1622) {
    auto value = createUShortValue(1);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "8");
}

// Test: supported model with value 0 should output "n/a"
TEST_F(SonyMisc3cSonyImageHeightTest_1622, ValueZero_ReturnsNA_1622) {
    auto value = createUShortValue(0);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: supported model with large value should output 8 * large_value
TEST_F(SonyMisc3cSonyImageHeightTest_1622, LargeValue_1622) {
    auto value = createUShortValue(8000);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "64000");
}

// Test: supported model with max unsigned short value
TEST_F(SonyMisc3cSonyImageHeightTest_1622, MaxUShortValue_1622) {
    auto value = createUShortValue(65535);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, std::to_string(8 * 65535));
}

// Test: unknown model with positive value should compute 8*val
TEST_F(SonyMisc3cSonyImageHeightTest_1622, UnknownModelPositiveValue_1622) {
    auto value = createUShortValue(100);
    ExifData exifData;
    setModel(exifData, "SLT-A99");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "800");
}

// Test: typical image height value for non-excluded model (e.g. 1080p = 135 * 8 = 1080)
TEST_F(SonyMisc3cSonyImageHeightTest_1622, TypicalImageHeight1080_1622) {
    auto value = createUShortValue(135);
    ExifData exifData;
    setModel(exifData, "ILCE-6000");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "1080");
}

// Test: signed short type should output parenthesized value (wrong type)
TEST_F(SonyMisc3cSonyImageHeightTest_1622, SignedShortType_1622) {
    auto value = createSignedShortValue(100);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printSonyMisc3cSonyImageHeight(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}
