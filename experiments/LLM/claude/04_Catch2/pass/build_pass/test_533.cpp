#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonArrayWriterTest_533 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test: Default construction with just an ostream
TEST_F(JsonArrayWriterTest_533, DefaultConstruction_533) {
    {
        JsonArrayWriter writer(oss);
    }
    std::string output = oss.str();
    // Destructor should close the array, expect some form of "[]" or similar
    EXPECT_FALSE(output.empty());
}

// Test: Construction with ostream and indent level
TEST_F(JsonArrayWriterTest_533, ConstructionWithIndentLevel_533) {
    {
        JsonArrayWriter writer(oss, 2);
    }
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test: Writing a boolean true value
TEST_F(JsonArrayWriterTest_533, WriteBoolTrue_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

// Test: Writing a boolean false value
TEST_F(JsonArrayWriterTest_533, WriteBoolFalse_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(false);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

// Test: Writing an integer value
TEST_F(JsonArrayWriterTest_533, WriteIntValue_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(42);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test: Writing a string value
TEST_F(JsonArrayWriterTest_533, WriteStringValue_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write("hello");
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test: Writing multiple values adds commas
TEST_F(JsonArrayWriterTest_533, WriteMultipleValues_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1);
        writer.write(2);
        writer.write(3);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Test: writeArray returns a nested JsonArrayWriter
TEST_F(JsonArrayWriterTest_533, WriteNestedArray_533) {
    {
        JsonArrayWriter writer(oss);
        {
            JsonArrayWriter nested = writer.writeArray();
            nested.write(1);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    // Should have nested array brackets
    // Count opening brackets - at least 2
    size_t count = 0;
    for (char c : output) {
        if (c == '[') count++;
    }
    EXPECT_GE(count, 2u);
}

// Test: writeObject returns a JsonObjectWriter
TEST_F(JsonArrayWriterTest_533, WriteNestedObject_533) {
    {
        JsonArrayWriter writer(oss);
        {
            JsonObjectWriter obj = writer.writeObject();
        }
    }
    std::string output = oss.str();
    // Should contain object braces
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test: Empty array produces valid JSON array
TEST_F(JsonArrayWriterTest_533, EmptyArrayProducesValidJson_533) {
    {
        JsonArrayWriter writer(oss);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test: Move construction
TEST_F(JsonArrayWriterTest_533, MoveConstruction_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1);
        JsonArrayWriter moved(std::move(writer));
        moved.write(2);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
}

// Test: Chaining write calls
TEST_F(JsonArrayWriterTest_533, ChainingWriteCalls_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1).write(2).write(3);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Test: Indent level 0
TEST_F(JsonArrayWriterTest_533, IndentLevelZero_533) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(42);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test: writeArray within writeArray (deeply nested)
TEST_F(JsonArrayWriterTest_533, DeeplyNestedArrays_533) {
    {
        JsonArrayWriter writer(oss);
        {
            JsonArrayWriter level1 = writer.writeArray();
            {
                JsonArrayWriter level2 = level1.writeArray();
                level2.write(99);
            }
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("99"), std::string::npos);
    size_t count = 0;
    for (char c : output) {
        if (c == '[') count++;
    }
    EXPECT_GE(count, 3u);
}

// Test: Multiple objects in array
TEST_F(JsonArrayWriterTest_533, MultipleObjectsInArray_533) {
    {
        JsonArrayWriter writer(oss);
        {
            JsonObjectWriter obj1 = writer.writeObject();
        }
        {
            JsonObjectWriter obj2 = writer.writeObject();
        }
    }
    std::string output = oss.str();
    // Should have comma between objects
    size_t count = 0;
    for (char c : output) {
        if (c == '{') count++;
    }
    EXPECT_GE(count, 2u);
}

// Test: Mixed content - values, arrays, objects
TEST_F(JsonArrayWriterTest_533, MixedContent_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1);
        writer.write(true);
        {
            JsonArrayWriter nested = writer.writeArray();
            nested.write(2);
        }
        {
            JsonObjectWriter obj = writer.writeObject();
        }
        writer.write(false);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("true"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("false"), std::string::npos);
}

// Test: Large indent level
TEST_F(JsonArrayWriterTest_533, LargeIndentLevel_533) {
    {
        JsonArrayWriter writer(oss, 100);
        writer.write(1);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
}

// Test: Writing negative integer
TEST_F(JsonArrayWriterTest_533, WriteNegativeInt_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(-5);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("-5"), std::string::npos);
}

// Test: Writing zero
TEST_F(JsonArrayWriterTest_533, WriteZero_533) {
    {
        JsonArrayWriter writer(oss);
        writer.write(0);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("0"), std::string::npos);
}
