#include "catch2/internal/catch_jsonwriter.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace Catch {

class JsonValueWriterTest_538 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test writing boolean true
TEST_F(JsonValueWriterTest_538, WriteBoolTrue_538) {
    JsonValueWriter(os).write(true);
    EXPECT_EQ(os.str(), "true");
}

// Test writing boolean false
TEST_F(JsonValueWriterTest_538, WriteBoolFalse_538) {
    JsonValueWriter(os).write(false);
    EXPECT_EQ(os.str(), "false");
}

// Test writing a string value (StringRef)
TEST_F(JsonValueWriterTest_538, WriteStringValue_538) {
    JsonValueWriter(os).write("hello"_sr);
    std::string result = os.str();
    // String values should be quoted
    EXPECT_NE(result.find("\"hello\""), std::string::npos);
}

// Test writing an empty string
TEST_F(JsonValueWriterTest_538, WriteEmptyString_538) {
    JsonValueWriter(os).write(""_sr);
    std::string result = os.str();
    EXPECT_NE(result.find("\"\""), std::string::npos);
}

// Test writing an integer value via template
TEST_F(JsonValueWriterTest_538, WriteIntegerValue_538) {
    JsonValueWriter(os).write(42);
    std::string result = os.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test writing zero
TEST_F(JsonValueWriterTest_538, WriteZero_538) {
    JsonValueWriter(os).write(0);
    std::string result = os.str();
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test writing negative integer
TEST_F(JsonValueWriterTest_538, WriteNegativeInteger_538) {
    JsonValueWriter(os).write(-1);
    std::string result = os.str();
    EXPECT_NE(result.find("-1"), std::string::npos);
}

// Test writing a double/floating point value
TEST_F(JsonValueWriterTest_538, WriteDoubleValue_538) {
    JsonValueWriter(os).write(3.14);
    std::string result = os.str();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test constructor with indent level
TEST_F(JsonValueWriterTest_538, ConstructorWithIndentLevel_538) {
    JsonValueWriter(os, 2).write(true);
    EXPECT_EQ(os.str(), "true");
}

// Test writeObject returns a JsonObjectWriter
TEST_F(JsonValueWriterTest_538, WriteObjectProducesValidJson_538) {
    {
        auto obj = JsonValueWriter(os).writeObject();
    }
    std::string result = os.str();
    // An empty object should contain braces
    EXPECT_NE(result.find("{"), std::string::npos);
    EXPECT_NE(result.find("}"), std::string::npos);
}

// Test writeArray returns a JsonArrayWriter
TEST_F(JsonValueWriterTest_538, WriteArrayProducesValidJson_538) {
    {
        auto arr = JsonValueWriter(os).writeArray();
    }
    std::string result = os.str();
    // An empty array should contain brackets
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

// Test writing a large integer
TEST_F(JsonValueWriterTest_538, WriteLargeInteger_538) {
    JsonValueWriter(os).write(static_cast<std::int64_t>(9999999999LL));
    std::string result = os.str();
    EXPECT_NE(result.find("9999999999"), std::string::npos);
}

// Test writing unsigned integer
TEST_F(JsonValueWriterTest_538, WriteUnsignedInteger_538) {
    JsonValueWriter(os).write(static_cast<unsigned int>(100));
    std::string result = os.str();
    EXPECT_NE(result.find("100"), std::string::npos);
}

// Test that bool true does not produce quoted output
TEST_F(JsonValueWriterTest_538, WriteBoolTrueNotQuoted_538) {
    JsonValueWriter(os).write(true);
    std::string result = os.str();
    EXPECT_EQ(result.find("\""), std::string::npos);
}

// Test that bool false does not produce quoted output
TEST_F(JsonValueWriterTest_538, WriteBoolFalseNotQuoted_538) {
    JsonValueWriter(os).write(false);
    std::string result = os.str();
    EXPECT_EQ(result.find("\""), std::string::npos);
}

// Test writing string with special characters
TEST_F(JsonValueWriterTest_538, WriteStringWithSpecialChars_538) {
    JsonValueWriter(os).write("hello \"world\""_sr);
    std::string result = os.str();
    // The output should contain the string in some form
    EXPECT_FALSE(result.empty());
}

// Test indent level 0 constructor
TEST_F(JsonValueWriterTest_538, ConstructorWithZeroIndent_538) {
    JsonValueWriter(os, 0).write(false);
    EXPECT_EQ(os.str(), "false");
}

} // namespace Catch
