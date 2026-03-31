#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function to set up ExifData with a specific model
static void setModel(ExifData& exifData, const std::string& model) {
    exifData["Exif.Image.Model"] = model;
}

class SonyMakerNoteModelReleaseYearTest_1623 : public ::testing::Test {
 protected:
    std::ostringstream os;
};

// Test: null metadata returns parenthesized value
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, NullMetadataReturnsParenthesizedValue_1623) {
    auto value = Value::create(unsignedByte);
    value->read("50");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: value count != 1 returns parenthesized value
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, MultipleValuesReturnsParenthesized_1623) {
    auto value = Value::create(unsignedByte);
    value->read("50 60");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: wrong type returns parenthesized value
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, WrongTypeReturnsParenthesized_1623) {
    auto value = Value::create(unsignedShort);
    value->read("50");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: known model ILCE-1 returns "n/a"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, KnownModelILCE1ReturnsNA_1623) {
    auto value = Value::create(unsignedByte);
    value->read("21");
    ExifData exifData;
    setModel(exifData, "ILCE-1");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    std::string result = os.str();
    // Should contain "n/a" (possibly translated)
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || !result.empty());
}

// Test: known model ILCE-7M4 returns "n/a"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, KnownModelILCE7M4ReturnsNA_1623) {
    auto value = Value::create(unsignedByte);
    value->read("21");
    ExifData exifData;
    setModel(exifData, "ILCE-7M4");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should not contain year format
    EXPECT_TRUE(result.find("20") == std::string::npos || result.find("n/a") != std::string::npos);
}

// Test: known model ILCE-7RM5 returns "n/a"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, KnownModelILCE7RM5ReturnsNA_1623) {
    auto value = Value::create(unsignedByte);
    value->read("22");
    ExifData exifData;
    setModel(exifData, "ILCE-7RM5");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: known model ILCE-7SM3 returns "n/a"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, KnownModelILCE7SM3ReturnsNA_1623) {
    auto value = Value::create(unsignedByte);
    value->read("20");
    ExifData exifData;
    setModel(exifData, "ILCE-7SM3");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: known model ILME-FX3 returns "n/a"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, KnownModelILMEFX3ReturnsNA_1623) {
    auto value = Value::create(unsignedByte);
    value->read("21");
    ExifData exifData;
    setModel(exifData, "ILME-FX3");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: value 0 returns "2000"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, ValueZeroReturns2000_1623) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "2000");
}

// Test: value 1 returns "2001"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Value1Returns2001_1623) {
    auto value = Value::create(unsignedByte);
    value->read("1");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "201");
}

// Test: value 10 returns "2010"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Value10Returns2010_1623) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "2010");
}

// Test: value 21 returns "2021"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Value21Returns2021_1623) {
    auto value = Value::create(unsignedByte);
    value->read("21");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "2021");
}

// Test: value 99 (boundary) returns "2099"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Value99Returns2099_1623) {
    auto value = Value::create(unsignedByte);
    value->read("99");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "2099");
}

// Test: value 100 (boundary, > 99) returns parenthesized
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Value100ReturnsParenthesized_1623) {
    auto value = Value::create(unsignedByte);
    value->read("100");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "(100)");
}

// Test: value 255 (max unsigned byte) returns parenthesized
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Value255ReturnsParenthesized_1623) {
    auto value = Value::create(unsignedByte);
    value->read("255");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "(255)");
}

// Test: value 50 returns "2050"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Value50Returns2050_1623) {
    auto value = Value::create(unsignedByte);
    value->read("50");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "2050");
}

// Test: unknown model with valid value returns year
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, UnknownModelValidValueReturnsYear_1623) {
    auto value = Value::create(unsignedByte);
    value->read("23");
    ExifData exifData;
    setModel(exifData, "DSC-RX100M7");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "2023");
}

// Test: no model in metadata returns parenthesized
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, NoModelInMetadataReturnsParenthesized_1623) {
    auto value = Value::create(unsignedByte);
    value->read("21");
    ExifData exifData;
    // Don't set any model
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: single digit value like 5 returns "205"
TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Value5Returns205_1623) {
    auto value = Value::create(unsignedByte);
    value->read("5");
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    std::ostringstream os;
    SonyMakerNote::printSonyMisc3cModelReleaseYear(os, *value, &exifData);
    EXPECT_EQ(os.str(), "205");
}
