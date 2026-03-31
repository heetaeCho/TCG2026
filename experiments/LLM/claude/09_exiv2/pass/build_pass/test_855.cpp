#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/value.hpp"

using namespace Exiv2;

class LangAltValueTest_855 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction
TEST_F(LangAltValueTest_855, DefaultConstruction_855) {
    LangAltValue val;
    EXPECT_EQ(val.count(), 0u);
}

// Test construction with a string buffer
TEST_F(LangAltValueTest_855, ConstructionWithString_855) {
    LangAltValue val("Hello World");
    EXPECT_GT(val.count(), 0u);
}

// Test read method with simple string (no lang qualifier)
TEST_F(LangAltValueTest_855, ReadSimpleString_855) {
    LangAltValue val;
    int result = val.read("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.count(), 1u);
}

// Test read method with lang qualifier
TEST_F(LangAltValueTest_855, ReadWithLangQualifier_855) {
    LangAltValue val;
    int result = val.read("lang=\"x-default\" Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_GE(val.count(), 1u);
}

// Test write with empty value
TEST_F(LangAltValueTest_855, WriteEmpty_855) {
    LangAltValue val;
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "");
}

// Test write with x-default only
TEST_F(LangAltValueTest_855, WriteXDefaultOnly_855) {
    LangAltValue val;
    val.read("lang=\"x-default\" Hello World");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_NE(output.find("x-default"), std::string::npos);
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

// Test write with simple string (defaults to x-default)
TEST_F(LangAltValueTest_855, WriteSimpleString_855) {
    LangAltValue val;
    val.read("Hello World");
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

// Test write with x-default appears first
TEST_F(LangAltValueTest_855, WriteXDefaultAppearsFirst_855) {
    LangAltValue val;
    // Populate the value map with x-default
    val.value_["x-default"] = "Default Text";
    val.value_["en"] = "English Text";
    val.value_["fr"] = "French Text";

    std::ostringstream os;
    val.write(os);
    std::string output = os.str();

    // x-default should appear before other languages
    auto posDefault = output.find("x-default");
    auto posEn = output.find("lang=\"en\"");
    auto posFr = output.find("lang=\"fr\"");

    EXPECT_NE(posDefault, std::string::npos);
    EXPECT_NE(posEn, std::string::npos);
    EXPECT_NE(posFr, std::string::npos);
    EXPECT_LT(posDefault, posEn);
    EXPECT_LT(posDefault, posFr);
}

// Test write with multiple languages includes commas
TEST_F(LangAltValueTest_855, WriteMultipleLanguagesHasCommas_855) {
    LangAltValue val;
    val.value_["x-default"] = "Default";
    val.value_["en"] = "English";

    std::ostringstream os;
    val.write(os);
    std::string output = os.str();

    EXPECT_NE(output.find(", "), std::string::npos);
}

// Test write with only non-default language
TEST_F(LangAltValueTest_855, WriteNonDefaultLanguageOnly_855) {
    LangAltValue val;
    val.value_["en"] = "English Text";

    std::ostringstream os;
    val.write(os);
    std::string output = os.str();

    EXPECT_NE(output.find("lang=\"en\""), std::string::npos);
    EXPECT_NE(output.find("English Text"), std::string::npos);
    // Should not contain a comma since there's only one entry
    EXPECT_EQ(output.find(", "), std::string::npos);
}

// Test write format includes lang= with quotes
TEST_F(LangAltValueTest_855, WriteFormatIncludesLangQuotes_855) {
    LangAltValue val;
    val.value_["x-default"] = "Test";

    std::ostringstream os;
    val.write(os);
    std::string output = os.str();

    EXPECT_NE(output.find("lang=\"x-default\""), std::string::npos);
}

// Test toString
TEST_F(LangAltValueTest_855, ToStringDefault_855) {
    LangAltValue val;
    val.read("Hello World");
    std::string result = val.toString(0);
    EXPECT_FALSE(result.empty());
}

// Test toString with qualifier
TEST_F(LangAltValueTest_855, ToStringWithQualifier_855) {
    LangAltValue val;
    val.value_["x-default"] = "Default Text";
    std::string result = val.toString("x-default");
    EXPECT_EQ(result, "Default Text");
}

// Test toString with nonexistent qualifier
TEST_F(LangAltValueTest_855, ToStringWithNonexistentQualifier_855) {
    LangAltValue val;
    val.value_["x-default"] = "Default Text";
    std::string result = val.toString("nonexistent");
    EXPECT_TRUE(result.empty());
}

// Test clone
TEST_F(LangAltValueTest_855, Clone_855) {
    LangAltValue val;
    val.read("Hello World");
    auto cloned = val.clone();
    EXPECT_NE(cloned, nullptr);

    std::ostringstream os1, os2;
    val.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test count with multiple entries
TEST_F(LangAltValueTest_855, CountMultipleEntries_855) {
    LangAltValue val;
    val.value_["x-default"] = "Default";
    val.value_["en"] = "English";
    val.value_["fr"] = "French";

    EXPECT_EQ(val.count(), 3u);
}

// Test toInt64
TEST_F(LangAltValueTest_855, ToInt64_855) {
    LangAltValue val;
    val.read("42");
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 42);
}

// Test toUint32
TEST_F(LangAltValueTest_855, ToUint32_855) {
    LangAltValue val;
    val.read("42");
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(result, 42u);
}

// Test toFloat
TEST_F(LangAltValueTest_855, ToFloat_855) {
    LangAltValue val;
    val.read("3.14");
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

// Test write returns the same ostream reference
TEST_F(LangAltValueTest_855, WriteReturnsOstream_855) {
    LangAltValue val;
    std::ostringstream os;
    std::ostream& returned = val.write(os);
    EXPECT_EQ(&returned, &os);
}

// Test write with multiple non-default languages (no x-default)
TEST_F(LangAltValueTest_855, WriteMultipleNonDefaultLanguages_855) {
    LangAltValue val;
    val.value_["en"] = "English";
    val.value_["fr"] = "French";
    val.value_["de"] = "German";

    std::ostringstream os;
    val.write(os);
    std::string output = os.str();

    // All should be present
    EXPECT_NE(output.find("English"), std::string::npos);
    EXPECT_NE(output.find("French"), std::string::npos);
    EXPECT_NE(output.find("German"), std::string::npos);
    // Should have commas between entries
    EXPECT_NE(output.find(", "), std::string::npos);
}

// Test read with empty string
TEST_F(LangAltValueTest_855, ReadEmptyString_855) {
    LangAltValue val;
    int result = val.read("");
    // Should handle empty string gracefully
    EXPECT_EQ(result, 0);
}

// Test write with special characters in values
TEST_F(LangAltValueTest_855, WriteSpecialCharacters_855) {
    LangAltValue val;
    val.value_["x-default"] = "Hello, \"World\"!";

    std::ostringstream os;
    val.write(os);
    std::string output = os.str();

    EXPECT_NE(output.find("Hello, \"World\"!"), std::string::npos);
}

// Test write with empty value string
TEST_F(LangAltValueTest_855, WriteEmptyValueString_855) {
    LangAltValue val;
    val.value_["x-default"] = "";

    std::ostringstream os;
    val.write(os);
    std::string output = os.str();

    EXPECT_NE(output.find("lang=\"x-default\""), std::string::npos);
}
