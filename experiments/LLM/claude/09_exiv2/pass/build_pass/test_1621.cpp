#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMisc3cQuality2Test_1621 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to set the model in ExifData
    void setModel(ExifData& exifData, const std::string& model) {
        exifData["Exif.Image.Model"] = model;
    }

    // Helper to create a Value of unsignedByte type with a single byte
    std::unique_ptr<Value> createUnsignedByteValue(uint8_t val) {
        auto v = Value::create(unsignedByte);
        v->read(reinterpret_cast<const byte*>(&val), 1, littleEndian);
        return v;
    }

    // Helper to create a Value of unsignedShort type with a single value
    std::unique_ptr<Value> createUnsignedShortValue(uint16_t val) {
        auto v = Value::create(unsignedShort);
        v->read(reinterpret_cast<const byte*>(&val), 2, littleEndian);
        return v;
    }

    // Helper to create a multi-byte unsignedByte value (count > 1)
    std::unique_ptr<Value> createMultiByteValue(const std::vector<uint8_t>& vals) {
        auto v = Value::create(unsignedByte);
        v->read(reinterpret_cast<const byte*>(vals.data()), vals.size(), littleEndian);
        return v;
    }
};

// Test: null metadata should output parenthesized value
TEST_F(SonyMisc3cQuality2Test_1621, NullMetadata_OutputsParenthesizedValue_1621) {
    auto value = createUnsignedByteValue(1);
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: wrong type (not unsignedByte) should output parenthesized value
TEST_F(SonyMisc3cQuality2Test_1621, WrongType_OutputsParenthesizedValue_1621) {
    auto value = createUnsignedShortValue(1);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: count > 1 should output parenthesized value
TEST_F(SonyMisc3cQuality2Test_1621, MultipleValues_OutputsParenthesizedValue_1621) {
    auto value = createMultiByteValue({1, 2});
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: no model in metadata should output parenthesized value
TEST_F(SonyMisc3cQuality2Test_1621, NoModel_OutputsParenthesizedValue_1621) {
    auto value = createUnsignedByteValue(1);
    ExifData exifData;
    // Don't set any model
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: ILCE-1 model with value 1 should use sonyMisc3cQuality2a table -> "JPEG"
TEST_F(SonyMisc3cQuality2Test_1621, ILCE1_Value1_JPEG_1621) {
    auto value = createUnsignedByteValue(1);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "JPEG");
}

// Test: ILCE-1 model with value 2 should output "Raw"
TEST_F(SonyMisc3cQuality2Test_1621, ILCE1_Value2_Raw_1621) {
    auto value = createUnsignedByteValue(2);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Raw");
}

// Test: ILCE-1 model with value 3 should output "Raw + JPEG"
TEST_F(SonyMisc3cQuality2Test_1621, ILCE1_Value3_RawJPEG_1621) {
    auto value = createUnsignedByteValue(3);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Raw + JPEG");
}

// Test: ILCE-1 model with value 4 should output "HEIF"
TEST_F(SonyMisc3cQuality2Test_1621, ILCE1_Value4_HEIF_1621) {
    auto value = createUnsignedByteValue(4);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "HEIF");
}

// Test: ILCE-1 model with value 6 should output "Raw + HEIF"
TEST_F(SonyMisc3cQuality2Test_1621, ILCE1_Value6_RawHEIF_1621) {
    auto value = createUnsignedByteValue(6);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Raw + HEIF");
}

// Test: ILCE-7M4 model with value 1 should use table a -> "JPEG"
TEST_F(SonyMisc3cQuality2Test_1621, ILCE7M4_Value1_JPEG_1621) {
    auto value = createUnsignedByteValue(1);
    ExifData exifData;
    setModel(exifData, "ILCE-7M4");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "JPEG");
}

// Test: ILCE-7RM5 model with value 4 -> "HEIF"
TEST_F(SonyMisc3cQuality2Test_1621, ILCE7RM5_Value4_HEIF_1621) {
    auto value = createUnsignedByteValue(4);
    ExifData exifData;
    setModel(exifData, "ILCE-7RM5");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "HEIF");
}

// Test: ILCE-7SM3 model with value 2 -> "Raw"
TEST_F(SonyMisc3cQuality2Test_1621, ILCE7SM3_Value2_Raw_1621) {
    auto value = createUnsignedByteValue(2);
    ExifData exifData;
    setModel(exifData, "ILCE-7SM3");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Raw");
}

// Test: ILME-FX3 model with value 3 -> "Raw + JPEG"
TEST_F(SonyMisc3cQuality2Test_1621, ILMEFX3_Value3_RawJPEG_1621) {
    auto value = createUnsignedByteValue(3);
    ExifData exifData;
    setModel(exifData, "ILME-FX3");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Raw + JPEG");
}

// Test: Non-matching model should use table b. Value 0 -> "JPEG"
TEST_F(SonyMisc3cQuality2Test_1621, OtherModel_Value0_JPEG_1621) {
    auto value = createUnsignedByteValue(0);
    ExifData exifData;
    setModel(exifData, "ILCE-6000");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "JPEG");
}

// Test: Non-matching model, value 1 -> "Raw" (table b)
TEST_F(SonyMisc3cQuality2Test_1621, OtherModel_Value1_Raw_1621) {
    auto value = createUnsignedByteValue(1);
    ExifData exifData;
    setModel(exifData, "ILCE-6000");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Raw");
}

// Test: Non-matching model, value 2 -> "Raw + JPEG" (table b)
TEST_F(SonyMisc3cQuality2Test_1621, OtherModel_Value2_RawJPEG_1621) {
    auto value = createUnsignedByteValue(2);
    ExifData exifData;
    setModel(exifData, "ILCE-6000");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Raw + JPEG");
}

// Test: Non-matching model, value 3 -> "Raw + MPO" (table b)
TEST_F(SonyMisc3cQuality2Test_1621, OtherModel_Value3_RawMPO_1621) {
    auto value = createUnsignedByteValue(3);
    ExifData exifData;
    setModel(exifData, "ILCE-6000");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Raw + MPO");
}

// Test: ILCE-1 model with unknown value (e.g., 5) — should output something (possibly unknown tag notation)
TEST_F(SonyMisc3cQuality2Test_1621, ILCE1_UnknownValue5_1621) {
    auto value = createUnsignedByteValue(5);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    // Value 5 is not in table a, so it should produce some output (likely "(5)")
    EXPECT_FALSE(result.empty());
}

// Test: Non-matching model with unknown value (e.g., 10) — should output something
TEST_F(SonyMisc3cQuality2Test_1621, OtherModel_UnknownValue10_1621) {
    auto value = createUnsignedByteValue(10);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Value 0 with table a model — 0 is not in table a, should produce output
TEST_F(SonyMisc3cQuality2Test_1621, ILCE1_Value0_NotInTableA_1621) {
    auto value = createUnsignedByteValue(0);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    std::string result = os.str();
    // 0 is not in sonyMisc3cQuality2a, should produce some fallback output
    EXPECT_FALSE(result.empty());
}

// Test: Return value is the same ostream reference
TEST_F(SonyMisc3cQuality2Test_1621, ReturnsOstreamReference_1621) {
    auto value = createUnsignedByteValue(1);
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    std::ostream& ret = SonyMakerNote::printSonyMisc3cQuality2(os, *value, &exifData);
    EXPECT_EQ(&ret, &os);
}

// Test: Return value is the same ostream reference even for error case
TEST_F(SonyMisc3cQuality2Test_1621, ReturnsOstreamReferenceOnError_1621) {
    auto value = createUnsignedByteValue(1);
    std::ostream& ret = SonyMakerNote::printSonyMisc3cQuality2(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}
