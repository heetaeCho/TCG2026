#include "catch2/internal/catch_jsonwriter.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstdint>

class JsonValueWriterTest_525 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test writing an integer value
TEST_F(JsonValueWriterTest_525, WriteInteger_525) {
    Catch::JsonValueWriter(oss).write(42);
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test writing a negative integer value
TEST_F(JsonValueWriterTest_525, WriteNegativeInteger_525) {
    Catch::JsonValueWriter(oss).write(-1);
    std::string result = oss.str();
    EXPECT_NE(result.find("-1"), std::string::npos);
}

// Test writing zero
TEST_F(JsonValueWriterTest_525, WriteZero_525) {
    Catch::JsonValueWriter(oss).write(0);
    std::string result = oss.str();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test writing a boolean true value
TEST_F(JsonValueWriterTest_525, WriteBoolTrue_525) {
    Catch::JsonValueWriter(oss).write(true);
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

// Test writing a boolean false value
TEST_F(JsonValueWriterTest_525, WriteBoolFalse_525) {
    Catch::JsonValueWriter(oss).write(false);
    std::string result = oss.str();
    EXPECT_NE(result.find("false"), std::string::npos);
}

// Test writing a string value (StringRef)
TEST_F(JsonValueWriterTest_525, WriteStringValue_525) {
    Catch::JsonValueWriter(oss).write(Catch::StringRef("hello"));
    std::string result = oss.str();
    // Strings should be quoted in JSON
    EXPECT_NE(result.find("\"hello\""), std::string::npos);
}

// Test writing an empty string
TEST_F(JsonValueWriterTest_525, WriteEmptyString_525) {
    Catch::JsonValueWriter(oss).write(Catch::StringRef(""));
    std::string result = oss.str();
    EXPECT_NE(result.find("\"\""), std::string::npos);
}

// Test writing a floating point value
TEST_F(JsonValueWriterTest_525, WriteDouble_525) {
    Catch::JsonValueWriter(oss).write(3.14);
    std::string result = oss.str();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test writing a large integer value
TEST_F(JsonValueWriterTest_525, WriteLargeInteger_525) {
    Catch::JsonValueWriter(oss).write(static_cast<std::int64_t>(9999999999LL));
    std::string result = oss.str();
    EXPECT_NE(result.find("9999999999"), std::string::npos);
}

// Test writing an unsigned integer
TEST_F(JsonValueWriterTest_525, WriteUnsignedInteger_525) {
    Catch::JsonValueWriter(oss).write(static_cast<unsigned int>(100));
    std::string result = oss.str();
    EXPECT_NE(result.find("100"), std::string::npos);
}

// Test construction with indent level
TEST_F(JsonValueWriterTest_525, ConstructWithIndentLevel_525) {
    Catch::JsonValueWriter(oss, 2).write(42);
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test construction with indent level zero
TEST_F(JsonValueWriterTest_525, ConstructWithIndentLevelZero_525) {
    Catch::JsonValueWriter(oss, 0).write(42);
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test writeObject returns a JsonObjectWriter
TEST_F(JsonValueWriterTest_525, WriteObjectProducesOutput_525) {
    {
        auto obj = Catch::JsonValueWriter(oss).writeObject();
        // Object writer goes out of scope, should close the object
    }
    std::string result = oss.str();
    // JSON object should have braces
    EXPECT_NE(result.find("{"), std::string::npos);
    EXPECT_NE(result.find("}"), std::string::npos);
}

// Test writeArray returns a JsonArrayWriter
TEST_F(JsonValueWriterTest_525, WriteArrayProducesOutput_525) {
    {
        auto arr = Catch::JsonValueWriter(oss).writeArray();
        // Array writer goes out of scope, should close the array
    }
    std::string result = oss.str();
    // JSON array should have brackets
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

// Test writing a string with special characters
TEST_F(JsonValueWriterTest_525, WriteStringWithSpecialChars_525) {
    Catch::JsonValueWriter(oss).write(Catch::StringRef("hello\"world"));
    std::string result = oss.str();
    // The string should be in the output and properly escaped
    EXPECT_FALSE(result.empty());
}

// Test that arithmetic types are not quoted
TEST_F(JsonValueWriterTest_525, ArithmeticNotQuoted_525) {
    Catch::JsonValueWriter(oss).write(42);
    std::string result = oss.str();
    // Should not be quoted: no "42" with surrounding quotes
    EXPECT_EQ(result.find("\"42\""), std::string::npos);
}

// Test that string types are quoted
TEST_F(JsonValueWriterTest_525, StringIsQuoted_525) {
    Catch::JsonValueWriter(oss).write(Catch::StringRef("test"));
    std::string result = oss.str();
    EXPECT_NE(result.find("\"test\""), std::string::npos);
}

// Test writing float value
TEST_F(JsonValueWriterTest_525, WriteFloat_525) {
    Catch::JsonValueWriter(oss).write(1.0f);
    std::string result = oss.str();
    EXPECT_NE(result.find("1"), std::string::npos);
}

// Test that the output stream receives data
TEST_F(JsonValueWriterTest_525, OutputStreamReceivesData_525) {
    EXPECT_TRUE(oss.str().empty());
    Catch::JsonValueWriter(oss).write(123);
    EXPECT_FALSE(oss.str().empty());
}
