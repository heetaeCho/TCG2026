#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

// Test that JsonValueWriter can be constructed with just an ostream
TEST(JsonValueWriterTest_535, ConstructWithOstream_535) {
    std::stringstream ss;
    EXPECT_NO_THROW(JsonValueWriter writer(ss));
}

// Test that JsonValueWriter can be constructed with ostream and indent level
TEST(JsonValueWriterTest_535, ConstructWithOstreamAndIndentLevel_535) {
    std::stringstream ss;
    EXPECT_NO_THROW(JsonValueWriter writer(ss, 0));
}

// Test that JsonValueWriter can be constructed with a non-zero indent level
TEST(JsonValueWriterTest_535, ConstructWithNonZeroIndentLevel_535) {
    std::stringstream ss;
    EXPECT_NO_THROW(JsonValueWriter writer(ss, 5));
}

// Test writing a string value
TEST(JsonValueWriterTest_535, WriteStringValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(StringRef("hello"));
    std::string output = ss.str();
    // A JSON string should be quoted
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// Test writing an empty string value
TEST(JsonValueWriterTest_535, WriteEmptyStringValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(StringRef(""));
    std::string output = ss.str();
    // Should contain empty quoted string
    EXPECT_NE(output.find("\"\""), std::string::npos);
}

// Test writing a boolean true value
TEST(JsonValueWriterTest_535, WriteBoolTrueValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(true);
    std::string output = ss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

// Test writing a boolean false value
TEST(JsonValueWriterTest_535, WriteBoolFalseValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(false);
    std::string output = ss.str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

// Test writing an integer value
TEST(JsonValueWriterTest_535, WriteIntegerValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(42);
    std::string output = ss.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test writing a negative integer value
TEST(JsonValueWriterTest_535, WriteNegativeIntegerValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(-1);
    std::string output = ss.str();
    EXPECT_NE(output.find("-1"), std::string::npos);
}

// Test writing zero
TEST(JsonValueWriterTest_535, WriteZeroValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(0);
    std::string output = ss.str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// Test writeObject returns a JsonObjectWriter
TEST(JsonValueWriterTest_535, WriteObjectReturnsObjectWriter_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    {
        auto obj = std::move(writer).writeObject();
        // Object writer should exist and produce valid JSON object syntax
    }
    std::string output = ss.str();
    // An empty object should contain braces
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test writeArray returns a JsonArrayWriter
TEST(JsonValueWriterTest_535, WriteArrayReturnsArrayWriter_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    {
        auto arr = std::move(writer).writeArray();
        // Array writer should exist and produce valid JSON array syntax
    }
    std::string output = ss.str();
    // An empty array should contain brackets
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test writeObject with indent level
TEST(JsonValueWriterTest_535, WriteObjectWithIndentLevel_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss, 2);
    {
        auto obj = std::move(writer).writeObject();
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test writeArray with indent level
TEST(JsonValueWriterTest_535, WriteArrayWithIndentLevel_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss, 2);
    {
        auto arr = std::move(writer).writeArray();
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test writing a string with special characters
TEST(JsonValueWriterTest_535, WriteStringWithSpecialChars_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(StringRef("hello\"world"));
    std::string output = ss.str();
    // The string should be in the output, possibly with escaping
    EXPECT_FALSE(output.empty());
}

// Test writing a string with newline
TEST(JsonValueWriterTest_535, WriteStringWithNewline_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(StringRef("line1\nline2"));
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// Test writing a large integer value
TEST(JsonValueWriterTest_535, WriteLargeIntegerValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(999999999);
    std::string output = ss.str();
    EXPECT_NE(output.find("999999999"), std::string::npos);
}

// Test writing a double/float value
TEST(JsonValueWriterTest_535, WriteDoubleValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(3.14);
    std::string output = ss.str();
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// Test writing unsigned integer
TEST(JsonValueWriterTest_535, WriteUnsignedIntValue_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(static_cast<unsigned int>(100));
    std::string output = ss.str();
    EXPECT_NE(output.find("100"), std::string::npos);
}

// Test that indent level 0 produces output
TEST(JsonValueWriterTest_535, IndentLevelZeroProducesOutput_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss, 0);
    std::move(writer).write(StringRef("test"));
    std::string output = ss.str();
    EXPECT_NE(output.find("\"test\""), std::string::npos);
}

// Test writing a uint64_t value
TEST(JsonValueWriterTest_535, WriteUint64Value_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    std::move(writer).write(static_cast<std::uint64_t>(18446744073709551615ULL));
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// Test that object writer can have entries added
TEST(JsonValueWriterTest_535, ObjectWriterWithEntries_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    {
        auto obj = std::move(writer).writeObject();
        obj.write("key").write("value");
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// Test that array writer can have elements added
TEST(JsonValueWriterTest_535, ArrayWriterWithElements_535) {
    std::stringstream ss;
    JsonValueWriter writer(ss);
    {
        auto arr = std::move(writer).writeArray();
        arr.write().write(1);
        arr.write().write(2);
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
}

// Test writing a long string value
TEST(JsonValueWriterTest_535, WriteLongStringValue_535) {
    std::stringstream ss;
    std::string longStr(1000, 'a');
    JsonValueWriter writer(ss);
    std::move(writer).write(StringRef(longStr));
    std::string output = ss.str();
    EXPECT_NE(output.find(longStr), std::string::npos);
}
