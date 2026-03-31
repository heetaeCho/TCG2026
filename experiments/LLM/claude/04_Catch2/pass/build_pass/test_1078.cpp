#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the header for JsonArrayWriter
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonArrayWriterTest_1078 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test: Default construction with just ostream
TEST_F(JsonArrayWriterTest_1078, ConstructWithOstream_1078) {
    {
        JsonArrayWriter writer(oss);
    }
    std::string output = oss.str();
    // After construction and destruction, should produce valid JSON array syntax
    EXPECT_FALSE(output.empty());
}

// Test: Construction with ostream and indent level
TEST_F(JsonArrayWriterTest_1078, ConstructWithOstreamAndIndentLevel_1078) {
    {
        JsonArrayWriter writer(oss, 0);
    }
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test: Construction with non-zero indent level
TEST_F(JsonArrayWriterTest_1078, ConstructWithNonZeroIndentLevel_1078) {
    {
        JsonArrayWriter writer(oss, 3);
    }
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test: Move constructor transfers ownership
TEST_F(JsonArrayWriterTest_1078, MoveConstructor_1078) {
    {
        JsonArrayWriter writer1(oss);
        JsonArrayWriter writer2(std::move(writer1));
        // writer2 should now be active, writer1 should be inactive
    }
    std::string output = oss.str();
    // Should still produce valid output - only one closing bracket
    EXPECT_FALSE(output.empty());
}

// Test: Write boolean true value
TEST_F(JsonArrayWriterTest_1078, WriteBoolTrue_1078) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

// Test: Write boolean false value
TEST_F(JsonArrayWriterTest_1078, WriteBoolFalse_1078) {
    {
        JsonArrayWriter writer(oss);
        writer.write(false);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

// Test: Write integer value
TEST_F(JsonArrayWriterTest_1078, WriteInteger_1078) {
    {
        JsonArrayWriter writer(oss);
        writer.write(42);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test: Write string value
TEST_F(JsonArrayWriterTest_1078, WriteString_1078) {
    {
        JsonArrayWriter writer(oss);
        writer.write("hello");
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test: Write multiple values produces commas
TEST_F(JsonArrayWriterTest_1078, WriteMultipleValues_1078) {
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
    // Multiple values should have commas between them
    EXPECT_NE(output.find(","), std::string::npos);
}

// Test: Write chaining returns reference to same writer
TEST_F(JsonArrayWriterTest_1078, WriteChainingReturnsSelf_1078) {
    {
        JsonArrayWriter writer(oss);
        JsonArrayWriter& ref = writer.write(1);
        EXPECT_EQ(&ref, &writer);
    }
}

// Test: Write bool chaining returns reference to same writer
TEST_F(JsonArrayWriterTest_1078, WriteBoolChainingReturnsSelf_1078) {
    {
        JsonArrayWriter writer(oss);
        JsonArrayWriter& ref = writer.write(true);
        EXPECT_EQ(&ref, &writer);
    }
}

// Test: Empty array produces brackets
TEST_F(JsonArrayWriterTest_1078, EmptyArrayProducesBrackets_1078) {
    {
        JsonArrayWriter writer(oss);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test: writeObject returns a JsonObjectWriter
TEST_F(JsonArrayWriterTest_1078, WriteObjectReturnsObjectWriter_1078) {
    {
        JsonArrayWriter writer(oss);
        {
            auto objWriter = writer.writeObject();
            // objWriter goes out of scope, closing the object
        }
    }
    std::string output = oss.str();
    // Should contain object delimiters
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test: writeArray returns a nested JsonArrayWriter
TEST_F(JsonArrayWriterTest_1078, WriteArrayReturnsNestedArrayWriter_1078) {
    {
        JsonArrayWriter writer(oss);
        {
            auto nestedWriter = writer.writeArray();
            // nestedWriter goes out of scope, closing the nested array
        }
    }
    std::string output = oss.str();
    // Should contain nested array brackets - at least two opening and closing brackets
    size_t openCount = 0, closeCount = 0;
    for (char c : output) {
        if (c == '[') openCount++;
        if (c == ']') closeCount++;
    }
    EXPECT_GE(openCount, 2u);
    EXPECT_GE(closeCount, 2u);
}

// Test: Move constructed writer still produces valid output
TEST_F(JsonArrayWriterTest_1078, MoveConstructedWriterProducesValidOutput_1078) {
    {
        JsonArrayWriter writer1(oss);
        JsonArrayWriter writer2(std::move(writer1));
        writer2.write(99);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("99"), std::string::npos);
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test: Write mixed types in array
TEST_F(JsonArrayWriterTest_1078, WriteMixedTypes_1078) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
        writer.write(42);
        writer.write("text");
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
    EXPECT_NE(output.find("text"), std::string::npos);
}

// Test: Nested array and object together
TEST_F(JsonArrayWriterTest_1078, NestedArrayAndObject_1078) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1);
        {
            auto nested = writer.writeArray();
            nested.write(2);
        }
        {
            auto obj = writer.writeObject();
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test: Destruction of moved-from writer does not double-close
TEST_F(JsonArrayWriterTest_1078, MovedFromWriterDestructionSafe_1078) {
    {
        JsonArrayWriter writer1(oss);
        writer1.write(1);
        JsonArrayWriter writer2(std::move(writer1));
        writer2.write(2);
        // Both destructors run, but only writer2 should close the array
    }
    std::string output = oss.str();
    // Count closing brackets - should be exactly one
    size_t closeCount = 0;
    for (char c : output) {
        if (c == ']') closeCount++;
    }
    EXPECT_EQ(closeCount, 1u);
}

// Test: Write negative integer
TEST_F(JsonArrayWriterTest_1078, WriteNegativeInteger_1078) {
    {
        JsonArrayWriter writer(oss);
        writer.write(-5);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("-5"), std::string::npos);
}

// Test: Write zero
TEST_F(JsonArrayWriterTest_1078, WriteZero_1078) {
    {
        JsonArrayWriter writer(oss);
        writer.write(0);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// Test: Large indent level
TEST_F(JsonArrayWriterTest_1078, LargeIndentLevel_1078) {
    {
        JsonArrayWriter writer(oss, 100);
        writer.write(1);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
}
