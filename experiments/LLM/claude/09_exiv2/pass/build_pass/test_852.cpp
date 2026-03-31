#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <sstream>

namespace {

class LangAltValueTest_852 : public ::testing::Test {
protected:
    Exiv2::LangAltValue value_;
};

// Normal operation tests

TEST_F(LangAltValueTest_852, ReadPlainTextUsesXDefault_852) {
    int result = value_.read("Hello World");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello World", value_.toString("x-default"));
}

TEST_F(LangAltValueTest_852, ReadWithLangTag_852) {
    int result = value_.read("lang=en Hello English");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello English", value_.toString("en"));
}

TEST_F(LangAltValueTest_852, ReadWithLangTagFrench_852) {
    int result = value_.read("lang=fr Bonjour le monde");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Bonjour le monde", value_.toString("fr"));
}

TEST_F(LangAltValueTest_852, ReadWithQuotedLangTag_852) {
    int result = value_.read("lang=\"en\" Hello English");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello English", value_.toString("en"));
}

TEST_F(LangAltValueTest_852, ReadWithHyphenatedLangTag_852) {
    int result = value_.read("lang=en-US Hello US English");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello US English", value_.toString("en-US"));
}

TEST_F(LangAltValueTest_852, ReadWithQuotedHyphenatedLangTag_852) {
    int result = value_.read("lang=\"en-US\" Hello US English");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello US English", value_.toString("en-US"));
}

TEST_F(LangAltValueTest_852, ReadMultipleValues_852) {
    value_.read("lang=en English text");
    value_.read("lang=fr French text");
    EXPECT_EQ("English text", value_.toString("en"));
    EXPECT_EQ("French text", value_.toString("fr"));
}

TEST_F(LangAltValueTest_852, ReadReturnsZero_852) {
    EXPECT_EQ(0, value_.read("some text"));
}

TEST_F(LangAltValueTest_852, ReadLangTagNoSpaceNoText_852) {
    int result = value_.read("lang=en");
    EXPECT_EQ(0, result);
    EXPECT_EQ("", value_.toString("en"));
}

TEST_F(LangAltValueTest_852, ReadLangWithSubtagNumbers_852) {
    int result = value_.read("lang=en-US123 text");
    EXPECT_EQ(0, result);
    EXPECT_EQ("text", value_.toString("en-US123"));
}

// Count and other accessors

TEST_F(LangAltValueTest_852, CountAfterReads_852) {
    value_.read("lang=en English");
    value_.read("lang=fr French");
    EXPECT_EQ(2u, value_.count());
}

TEST_F(LangAltValueTest_852, CountInitiallyZero_852) {
    EXPECT_EQ(0u, value_.count());
}

TEST_F(LangAltValueTest_852, CountAfterSingleRead_852) {
    value_.read("Hello");
    EXPECT_EQ(1u, value_.count());
}

// toString tests

TEST_F(LangAltValueTest_852, ToStringDefaultIndex_852) {
    value_.read("lang=x-default Default text");
    std::string result = value_.toString(0);
    EXPECT_FALSE(result.empty());
}

TEST_F(LangAltValueTest_852, ToStringWithQualifierNotFound_852) {
    value_.read("lang=en English");
    std::string result = value_.toString("de");
    EXPECT_TRUE(result.empty());
}

// Write test

TEST_F(LangAltValueTest_852, WriteOutputsValues_852) {
    value_.read("lang=en English text");
    std::ostringstream os;
    value_.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Clone test

TEST_F(LangAltValueTest_852, CloneCreatesIndependentCopy_852) {
    value_.read("lang=en English");
    auto cloned = value_.clone();
    ASSERT_NE(nullptr, cloned);
    EXPECT_EQ(1u, cloned->count());
}

// Error / Exception tests

TEST_F(LangAltValueTest_852, ReadEmptyLangTagThrows_852) {
    EXPECT_THROW(value_.read("lang= text"), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadEmptyQuotedLangTagThrows_852) {
    EXPECT_THROW(value_.read("lang=\"\" text"), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadMismatchedQuoteThrows_852) {
    EXPECT_THROW(value_.read("lang=\"en text"), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadLangWithInvalidCharsThrows_852) {
    EXPECT_THROW(value_.read("lang=en_US text"), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadLangWithNumbersOnlyInFirstPartThrows_852) {
    // First part before hyphen must be alpha only
    EXPECT_THROW(value_.read("lang=123 text"), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadLangWithSpecialCharsThrows_852) {
    EXPECT_THROW(value_.read("lang=en@US text"), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadLangWithDotThrows_852) {
    EXPECT_THROW(value_.read("lang=en.US text"), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadEmptyLangNoSpaceThrows_852) {
    EXPECT_THROW(value_.read("lang="), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadLangTrailingHyphenThrows_852) {
    // "en-" has hyphen at a position, but nothing valid after
    EXPECT_THROW(value_.read("lang=en- text"), Exiv2::Error);
}

TEST_F(LangAltValueTest_852, ReadLangDoubleHyphenThrows_852) {
    EXPECT_THROW(value_.read("lang=en--US text"), Exiv2::Error);
}

// Boundary condition tests

TEST_F(LangAltValueTest_852, ReadEmptyString_852) {
    int result = value_.read("");
    EXPECT_EQ(0, result);
    EXPECT_EQ("", value_.toString("x-default"));
}

TEST_F(LangAltValueTest_852, ReadSingleCharacter_852) {
    int result = value_.read("a");
    EXPECT_EQ(0, result);
    EXPECT_EQ("a", value_.toString("x-default"));
}

TEST_F(LangAltValueTest_852, ReadOverwritesSameLang_852) {
    value_.read("lang=en First");
    value_.read("lang=en Second");
    EXPECT_EQ("Second", value_.toString("en"));
    EXPECT_EQ(1u, value_.count());
}

TEST_F(LangAltValueTest_852, ReadLangWithSpaceAfterAndEmptyValue_852) {
    int result = value_.read("lang=en ");
    EXPECT_EQ(0, result);
    EXPECT_EQ("", value_.toString("en"));
}

TEST_F(LangAltValueTest_852, ReadLangWithMultipleSpaces_852) {
    int result = value_.read("lang=en  text with spaces");
    EXPECT_EQ(0, result);
    EXPECT_EQ(" text with spaces", value_.toString("en"));
}

TEST_F(LangAltValueTest_852, ReadPlainTextStartingWithLa_852) {
    // "la" doesn't match "lang=" prefix
    int result = value_.read("language is fun");
    EXPECT_EQ(0, result);
    EXPECT_EQ("language is fun", value_.toString("x-default"));
}

TEST_F(LangAltValueTest_852, ReadQuotedLangWithHyphen_852) {
    int result = value_.read("lang=\"zh-CN\" Chinese text");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Chinese text", value_.toString("zh-CN"));
}

// Numeric conversion tests

TEST_F(LangAltValueTest_852, ToInt64ReturnsValue_852) {
    value_.read("42");
    int64_t val = value_.toInt64(0);
    EXPECT_EQ(42, val);
}

TEST_F(LangAltValueTest_852, ToUint32ReturnsValue_852) {
    value_.read("42");
    uint32_t val = value_.toUint32(0);
    EXPECT_EQ(42u, val);
}

TEST_F(LangAltValueTest_852, ToFloatReturnsValue_852) {
    value_.read("3.14");
    float val = value_.toFloat(0);
    EXPECT_NEAR(3.14f, val, 0.01f);
}

// Constructor with string test

TEST(LangAltValueConstructorTest_852, ConstructWithString_852) {
    Exiv2::LangAltValue value("Hello");
    EXPECT_EQ(1u, value.count());
    EXPECT_EQ("Hello", value.toString("x-default"));
}

TEST(LangAltValueConstructorTest_852, ConstructWithLangString_852) {
    Exiv2::LangAltValue value("lang=de Hallo");
    EXPECT_EQ(1u, value.count());
    EXPECT_EQ("Hallo", value.toString("de"));
}

// Default constructor test

TEST(LangAltValueDefaultConstructorTest_852, DefaultConstructor_852) {
    Exiv2::LangAltValue value;
    EXPECT_EQ(0u, value.count());
}

} // anonymous namespace
