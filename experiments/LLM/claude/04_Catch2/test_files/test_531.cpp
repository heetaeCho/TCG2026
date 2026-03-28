#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstdint>

#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonArrayWriterTest_531 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that constructing and destroying an empty JsonArrayWriter produces valid JSON array
TEST_F(JsonArrayWriterTest_531, EmptyArrayProducesValidJson_531) {
    {
        JsonArrayWriter writer(oss);
    }
    std::string result = oss.str();
    // Should contain '[' and ']' for an empty array
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

// Test that constructing with indent level and destroying produces valid JSON
TEST_F(JsonArrayWriterTest_531, EmptyArrayWithIndentLevel_531) {
    {
        JsonArrayWriter writer(oss, 2);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

// Test writing a single boolean true value
TEST_F(JsonArrayWriterTest_531, WriteSingleBoolTrue_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

// Test writing a single boolean false value
TEST_F(JsonArrayWriterTest_531, WriteSingleBoolFalse_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(false);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("false"), std::string::npos);
}

// Test writing multiple boolean values
TEST_F(JsonArrayWriterTest_531, WriteMultipleBoolValues_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
        writer.write(false);
        writer.write(true);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find("false"), std::string::npos);
}

// Test writing integer values
TEST_F(JsonArrayWriterTest_531, WriteIntegerValue_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(42);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test writing string values
TEST_F(JsonArrayWriterTest_531, WriteStringValue_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(std::string("hello"));
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test writing a nested object
TEST_F(JsonArrayWriterTest_531, WriteNestedObject_531) {
    {
        JsonArrayWriter writer(oss);
        auto obj = writer.writeObject();
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('{'), std::string::npos);
    EXPECT_NE(result.find('}'), std::string::npos);
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

// Test writing a nested array
TEST_F(JsonArrayWriterTest_531, WriteNestedArray_531) {
    {
        JsonArrayWriter writer(oss);
        {
            auto innerArray = writer.writeArray();
        }
    }
    std::string result = oss.str();
    // Should have at least two '[' and two ']'
    size_t openCount = 0, closeCount = 0;
    for (char c : result) {
        if (c == '[') openCount++;
        if (c == ']') closeCount++;
    }
    EXPECT_GE(openCount, 2u);
    EXPECT_GE(closeCount, 2u);
}

// Test move constructor - source should become inactive
TEST_F(JsonArrayWriterTest_531, MoveConstructor_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1);
        JsonArrayWriter movedWriter(std::move(writer));
        movedWriter.write(2);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('1'), std::string::npos);
    EXPECT_NE(result.find('2'), std::string::npos);
    // Should only have one closing bracket pair (moved source should not write closing)
    size_t closeCount = 0;
    for (char c : result) {
        if (c == ']') closeCount++;
    }
    EXPECT_EQ(closeCount, 1u);
}

// Test zero indent level
TEST_F(JsonArrayWriterTest_531, ZeroIndentLevel_531) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(true);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
    EXPECT_NE(result.find("true"), std::string::npos);
}

// Test large indent level
TEST_F(JsonArrayWriterTest_531, LargeIndentLevel_531) {
    {
        JsonArrayWriter writer(oss, 10);
        writer.write(false);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
    EXPECT_NE(result.find("false"), std::string::npos);
}

// Test chaining writes
TEST_F(JsonArrayWriterTest_531, ChainingWrites_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1).write(2).write(3);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('1'), std::string::npos);
    EXPECT_NE(result.find('2'), std::string::npos);
    EXPECT_NE(result.find('3'), std::string::npos);
}

// Test that commas are properly placed between multiple values
TEST_F(JsonArrayWriterTest_531, CommasBetweenValues_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1);
        writer.write(2);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find(','), std::string::npos);
}

// Test writing negative integer
TEST_F(JsonArrayWriterTest_531, WriteNegativeInteger_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(-5);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("-5"), std::string::npos);
}

// Test writing mixed types
TEST_F(JsonArrayWriterTest_531, WriteMixedTypes_531) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
        writer.write(42);
        writer.write(std::string("test"));
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("test"), std::string::npos);
}

// Test that destructor writes newline before closing bracket
TEST_F(JsonArrayWriterTest_531, DestructorWritesNewlineBeforeClosingBracket_531) {
    {
        JsonArrayWriter writer(oss);
    }
    std::string result = oss.str();
    // The closing bracket should be preceded by a newline (possibly with indentation)
    size_t closingPos = result.rfind(']');
    ASSERT_NE(closingPos, std::string::npos);
    // There should be a newline somewhere before the closing bracket
    std::string beforeClose = result.substr(0, closingPos);
    EXPECT_NE(beforeClose.rfind('\n'), std::string::npos);
}

// Test default constructor uses indent level 0
TEST_F(JsonArrayWriterTest_531, DefaultConstructorUsesIndentZero_531) {
    std::ostringstream oss1, oss2;
    {
        JsonArrayWriter writer1(oss1);
    }
    {
        JsonArrayWriter writer2(oss2, 0);
    }
    EXPECT_EQ(oss1.str(), oss2.str());
}
