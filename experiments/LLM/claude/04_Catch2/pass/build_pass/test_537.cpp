#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

class JsonValueWriterTest_537 : public ::testing::Test {
protected:
    std::stringstream ss;
};

// Test writing a simple string value
TEST_F(JsonValueWriterTest_537, WriteStringValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef("hello"));
    std::string result = ss.str();
    // String values should be quoted in JSON
    EXPECT_NE(result.find("\"hello\""), std::string::npos);
}

// Test writing an empty string value
TEST_F(JsonValueWriterTest_537, WriteEmptyStringValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef(""));
    std::string result = ss.str();
    // Empty string should still produce quoted output
    EXPECT_NE(result.find("\"\""), std::string::npos);
}

// Test writing a boolean true value
TEST_F(JsonValueWriterTest_537, WriteBoolTrueValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(true);
    std::string result = ss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

// Test writing a boolean false value
TEST_F(JsonValueWriterTest_537, WriteBoolFalseValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(false);
    std::string result = ss.str();
    EXPECT_NE(result.find("false"), std::string::npos);
}

// Test writing an integer value
TEST_F(JsonValueWriterTest_537, WriteIntegerValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(42);
    std::string result = ss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test writing a negative integer value
TEST_F(JsonValueWriterTest_537, WriteNegativeIntegerValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(-1);
    std::string result = ss.str();
    EXPECT_NE(result.find("-1"), std::string::npos);
}

// Test writing a floating point value
TEST_F(JsonValueWriterTest_537, WriteDoubleValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(3.14);
    std::string result = ss.str();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test writing a zero value
TEST_F(JsonValueWriterTest_537, WriteZeroValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(0);
    std::string result = ss.str();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test writing a string with special characters
TEST_F(JsonValueWriterTest_537, WriteStringWithSpecialChars_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef("hello world"));
    std::string result = ss.str();
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// Test writing with indent level
TEST_F(JsonValueWriterTest_537, WriteWithIndentLevel_537) {
    Catch::JsonValueWriter writer(ss, 2);
    std::move(writer).write(Catch::StringRef("test"));
    std::string result = ss.str();
    EXPECT_NE(result.find("\"test\""), std::string::npos);
}

// Test writing with zero indent level
TEST_F(JsonValueWriterTest_537, WriteWithZeroIndentLevel_537) {
    Catch::JsonValueWriter writer(ss, 0);
    std::move(writer).write(Catch::StringRef("value"));
    std::string result = ss.str();
    EXPECT_NE(result.find("\"value\""), std::string::npos);
}

// Test writeObject returns a valid JsonObjectWriter
TEST_F(JsonValueWriterTest_537, WriteObjectProducesValidJson_537) {
    {
        Catch::JsonValueWriter writer(ss);
        auto obj = std::move(writer).writeObject();
        // JsonObjectWriter should produce valid JSON object syntax when destroyed
    }
    std::string result = ss.str();
    EXPECT_NE(result.find("{"), std::string::npos);
    EXPECT_NE(result.find("}"), std::string::npos);
}

// Test writeArray returns a valid JsonArrayWriter
TEST_F(JsonValueWriterTest_537, WriteArrayProducesValidJson_537) {
    {
        Catch::JsonValueWriter writer(ss);
        auto arr = std::move(writer).writeArray();
        // JsonArrayWriter should produce valid JSON array syntax when destroyed
    }
    std::string result = ss.str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

// Test writing a large integer value
TEST_F(JsonValueWriterTest_537, WriteLargeIntegerValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(999999999);
    std::string result = ss.str();
    EXPECT_NE(result.find("999999999"), std::string::npos);
}

// Test writing a string constructed from std::string
TEST_F(JsonValueWriterTest_537, WriteStdStringValue_537) {
    std::string input = "from_std_string";
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef(input));
    std::string result = ss.str();
    EXPECT_NE(result.find("\"from_std_string\""), std::string::npos);
}

// Test writing a string with quotes that might need escaping
TEST_F(JsonValueWriterTest_537, WriteStringWithQuotes_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef("he said \"hi\""));
    std::string result = ss.str();
    // The output should contain the string, possibly with escaped quotes
    EXPECT_FALSE(result.empty());
}

// Test writing a string with newline characters
TEST_F(JsonValueWriterTest_537, WriteStringWithNewline_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef("line1\nline2"));
    std::string result = ss.str();
    EXPECT_FALSE(result.empty());
}

// Test writing a string with backslash
TEST_F(JsonValueWriterTest_537, WriteStringWithBackslash_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef("path\\to\\file"));
    std::string result = ss.str();
    EXPECT_FALSE(result.empty());
}

// Test default constructor produces output to given stream
TEST_F(JsonValueWriterTest_537, ConstructorWithOutputStream_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef("test"));
    EXPECT_FALSE(ss.str().empty());
}

// Test writing unsigned integer
TEST_F(JsonValueWriterTest_537, WriteUnsignedIntValue_537) {
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(static_cast<unsigned int>(100));
    std::string result = ss.str();
    EXPECT_NE(result.find("100"), std::string::npos);
}

// Test writing a long string
TEST_F(JsonValueWriterTest_537, WriteLongStringValue_537) {
    std::string longStr(1000, 'a');
    Catch::JsonValueWriter writer(ss);
    std::move(writer).write(Catch::StringRef(longStr));
    std::string result = ss.str();
    EXPECT_NE(result.find(std::string(1000, 'a')), std::string::npos);
}
