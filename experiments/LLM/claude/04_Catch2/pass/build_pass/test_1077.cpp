#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstdint>

// Include the header for JsonArrayWriter
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonArrayWriterTest_1077 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that constructing with os and indent_level writes opening bracket
TEST_F(JsonArrayWriterTest_1077, ConstructorWithIndentWritesOpenBracket_1077) {
    {
        JsonArrayWriter writer(oss, 0);
    }
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], '[');
}

// Test that constructing with just os writes opening bracket
TEST_F(JsonArrayWriterTest_1077, ConstructorWithOsOnlyWritesOpenBracket_1077) {
    {
        JsonArrayWriter writer(oss);
    }
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], '[');
}

// Test that destructor writes closing bracket
TEST_F(JsonArrayWriterTest_1077, DestructorWritesClosingBracket_1077) {
    {
        JsonArrayWriter writer(oss, 0);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find(']'), std::string::npos);
}

// Test writing a boolean true value
TEST_F(JsonArrayWriterTest_1077, WriteBoolTrue_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(true);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

// Test writing a boolean false value
TEST_F(JsonArrayWriterTest_1077, WriteBoolFalse_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(false);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("false"), std::string::npos);
}

// Test writing an integer value
TEST_F(JsonArrayWriterTest_1077, WriteIntegerValue_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(42);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test writing a string value
TEST_F(JsonArrayWriterTest_1077, WriteStringValue_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write("hello");
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test writing multiple values produces valid JSON-like structure
TEST_F(JsonArrayWriterTest_1077, WriteMultipleValues_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(1);
        writer.write(2);
        writer.write(3);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
    // Should have commas separating values
    EXPECT_NE(result.find(","), std::string::npos);
}

// Test empty array produces []
TEST_F(JsonArrayWriterTest_1077, EmptyArrayProducesEmptyBrackets_1077) {
    {
        JsonArrayWriter writer(oss, 0);
    }
    std::string result = oss.str();
    // Should start with [ and end with ]
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

// Test writeObject returns a JsonObjectWriter and produces valid JSON
TEST_F(JsonArrayWriterTest_1077, WriteObjectProducesObject_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        {
            auto obj = writer.writeObject();
        }
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('{'), std::string::npos);
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test writeArray returns a nested JsonArrayWriter
TEST_F(JsonArrayWriterTest_1077, WriteNestedArray_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        {
            auto arr = writer.writeArray();
        }
    }
    std::string result = oss.str();
    // Should have at least two opening brackets (outer and inner)
    size_t count = 0;
    for (char c : result) {
        if (c == '[') count++;
    }
    EXPECT_GE(count, 2u);
}

// Test move constructor
TEST_F(JsonArrayWriterTest_1077, MoveConstructor_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        JsonArrayWriter moved(std::move(writer));
        moved.write(99);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("99"), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

// Test with different indent levels
TEST_F(JsonArrayWriterTest_1077, IndentLevelZero_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(1);
    }
    std::string result = oss.str();
    EXPECT_EQ(result[0], '[');
}

TEST_F(JsonArrayWriterTest_1077, IndentLevelNonZero_1077) {
    {
        JsonArrayWriter writer(oss, 3);
        writer.write(1);
    }
    std::string result = oss.str();
    EXPECT_EQ(result[0], '[');
}

// Test write returns reference to self for chaining
TEST_F(JsonArrayWriterTest_1077, WriteChainingReturnsReference_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        auto& ref = writer.write(1);
        ref.write(2);
        ref.write(3);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

// Test writing a single value followed by an object
TEST_F(JsonArrayWriterTest_1077, MixedValueAndObject_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(42);
        {
            auto obj = writer.writeObject();
        }
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find('{'), std::string::npos);
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test writing a single value followed by a nested array
TEST_F(JsonArrayWriterTest_1077, MixedValueAndArray_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(42);
        {
            auto arr = writer.writeArray();
            arr.write(99);
        }
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("99"), std::string::npos);
}

// Test large indent level doesn't crash
TEST_F(JsonArrayWriterTest_1077, LargeIndentLevel_1077) {
    {
        JsonArrayWriter writer(oss, 100);
        writer.write(1);
    }
    std::string result = oss.str();
    EXPECT_EQ(result[0], '[');
    EXPECT_EQ(result.back(), ']');
}

// Test writing a negative integer
TEST_F(JsonArrayWriterTest_1077, WriteNegativeInteger_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(-5);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("-5"), std::string::npos);
}

// Test writing zero
TEST_F(JsonArrayWriterTest_1077, WriteZero_1077) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(0);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("0"), std::string::npos);
}
