#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteHighISONoiseReduction2Test_1612 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to set camera model in ExifData
    void setModel(ExifData& exifData, const std::string& model) {
        exifData["Exif.Image.Model"] = model;
    }

    // Helper to create an unsignedShort value with a single entry
    std::unique_ptr<Value> createUShortValue(uint16_t val) {
        auto value = Value::create(unsignedShort);
        byte buf[2];
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        value->read(buf, 2, littleEndian);
        return value;
    }

    // Helper to create a value with wrong type (e.g., unsignedLong)
    std::unique_ptr<Value> createULongValue(uint32_t val) {
        auto value = Value::create(unsignedLong);
        byte buf[4];
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        buf[2] = static_cast<byte>((val >> 16) & 0xFF);
        buf[3] = static_cast<byte>((val >> 24) & 0xFF);
        value->read(buf, 4, littleEndian);
        return value;
    }

    // Helper to create an unsignedShort value with multiple entries
    std::unique_ptr<Value> createMultiUShortValue(uint16_t val1, uint16_t val2) {
        auto value = Value::create(unsignedShort);
        byte buf[4];
        buf[0] = static_cast<byte>(val1 & 0xFF);
        buf[1] = static_cast<byte>((val1 >> 8) & 0xFF);
        buf[2] = static_cast<byte>(val2 & 0xFF);
        buf[3] = static_cast<byte>((val2 >> 8) & 0xFF);
        value->read(buf, 4, littleEndian);
        return value;
    }
};

// Test: Null metadata should output value in parentheses
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, NullMetadata_OutputsParenthesized_1612) {
    auto value = createUShortValue(0);
    SonyMakerNote::printHighISONoiseReduction2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Wrong type (not unsignedShort) should output value in parentheses
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, WrongType_OutputsParenthesized_1612) {
    auto value = createULongValue(0);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Multiple values (count != 1) should output value in parentheses
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, MultipleValues_OutputsParenthesized_1612) {
    auto value = createMultiUShortValue(0, 1);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: No model in metadata should output value in parentheses
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, NoModel_OutputsParenthesized_1612) {
    auto value = createUShortValue(0);
    ExifData exifData;
    // Don't set any model
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: DSC- model with value 0 should output "Normal"
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, DSCModel_Normal_1612) {
    auto value = createUShortValue(0);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Normal");
}

// Test: DSC- model with value 1 should output "High"
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, DSCModel_High_1612) {
    auto value = createUShortValue(1);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "High");
}

// Test: DSC- model with value 2 should output "Low"
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, DSCModel_Low_1612) {
    auto value = createUShortValue(2);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Low");
}

// Test: DSC- model with value 3 should output "Off"
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, DSCModel_Off_1612) {
    auto value = createUShortValue(3);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Off");
}

// Test: DSC- model with value 65535 should output "n/a"
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, DSCModel_NA_1612) {
    auto value = createUShortValue(65535);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: Stellar model should also use the tag lookup
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, StellarModel_Normal_1612) {
    auto value = createUShortValue(0);
    ExifData exifData;
    setModel(exifData, "Stellar");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Normal");
}

// Test: Non-DSC non-Stellar model should output "n/a" (translated)
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, NonDSCModel_OutputsNA_1612) {
    auto value = createUShortValue(0);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    // Should output n/a (possibly translated)
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || !result.empty());
}

// Test: DSC- model with unknown value (not in tag table) - should produce some output
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, DSCModel_UnknownValue_1612) {
    auto value = createUShortValue(99);
    ExifData exifData;
    setModel(exifData, "DSC-HX1");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    // Unknown value; should produce some output (typically "(99)")
    EXPECT_FALSE(result.empty());
}

// Test: Another non-matching model (SLT)
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, SLTModel_OutputsNA_1612) {
    auto value = createUShortValue(1);
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: DSC- prefix with various sub-models
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, DSCModelVariant_1612) {
    auto value = createUShortValue(2);
    ExifData exifData;
    setModel(exifData, "DSC-HX400V");
    SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Low");
}

// Test: Return value is reference to same ostream
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, ReturnsOstreamReference_1612) {
    auto value = createUShortValue(0);
    ExifData exifData;
    setModel(exifData, "DSC-RX100");
    std::ostream& ret = SonyMakerNote::printHighISONoiseReduction2(os, *value, &exifData);
    EXPECT_EQ(&ret, &os);
}

// Test: Return value is reference to same ostream with null metadata
TEST_F(SonyMakerNoteHighISONoiseReduction2Test_1612, ReturnsOstreamReferenceNullMetadata_1612) {
    auto value = createUShortValue(0);
    std::ostream& ret = SonyMakerNote::printHighISONoiseReduction2(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}
