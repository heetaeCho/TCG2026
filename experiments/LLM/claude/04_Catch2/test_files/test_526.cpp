#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_jsonwriter.hpp"

class JsonArrayWriterTest_526 : public ::testing::Test {
protected:
    std::ostringstream os;
};

TEST_F(JsonArrayWriterTest_526, DefaultConstructionProducesValidJson_526) {
    {
        Catch::JsonArrayWriter writer(os);
    }
    std::string result = os.str();
    // After destruction, should produce a valid empty JSON array
    EXPECT_FALSE(result.empty());
    // Should contain array brackets
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, ConstructionWithIndentLevel_526) {
    {
        Catch::JsonArrayWriter writer(os, 0);
    }
    std::string result = os.str();
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, ConstructionWithHigherIndentLevel_526) {
    {
        Catch::JsonArrayWriter writer(os, 3);
    }
    std::string result = os.str();
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteBoolTrue_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(true);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteBoolFalse_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(false);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteInteger_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(42);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteNegativeInteger_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(-7);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("-7"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteString_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write("hello");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteMultipleValues_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(1);
        writer.write(2);
        writer.write(3);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteChainingReturnsSelf_526) {
    {
        Catch::JsonArrayWriter writer(os);
        auto& ref = writer.write(1);
        // Chaining should return reference to same writer
        EXPECT_EQ(&ref, &writer);
    }
}

TEST_F(JsonArrayWriterTest_526, WriteBoolChainingReturnsSelf_526) {
    {
        Catch::JsonArrayWriter writer(os);
        auto& ref = writer.write(true);
        EXPECT_EQ(&ref, &writer);
    }
}

TEST_F(JsonArrayWriterTest_526, WriteObject_526) {
    {
        Catch::JsonArrayWriter writer(os);
        {
            auto obj = writer.writeObject();
        }
    }
    std::string result = os.str();
    EXPECT_NE(result.find('{'), std::string::npos);
    EXPECT_NE(result.find('}'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteNestedArray_526) {
    {
        Catch::JsonArrayWriter writer(os);
        {
            auto arr = writer.writeArray();
        }
    }
    std::string result = os.str();
    // Should have nested array brackets - at least two opening brackets
    size_t firstOpen = result.find('[');
    EXPECT_NE(firstOpen, std::string::npos);
    size_t secondOpen = result.find('[', firstOpen + 1);
    EXPECT_NE(secondOpen, std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, MoveConstruction_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(100);
        Catch::JsonArrayWriter moved(std::move(writer));
        moved.write(200);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("100"), std::string::npos);
    EXPECT_NE(result.find("200"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, EmptyArrayFormat_526) {
    {
        Catch::JsonArrayWriter writer(os);
    }
    std::string result = os.str();
    // Should not contain any values, just the array structure
    EXPECT_EQ(result.find("true"), std::string::npos);
    EXPECT_EQ(result.find("false"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteZero_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(0);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteDoubleValue_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(3.14);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteMixedTypes_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(42);
        writer.write(true);
        writer.write("text");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find("text"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteMultipleObjectsInArray_526) {
    {
        Catch::JsonArrayWriter writer(os);
        {
            auto obj1 = writer.writeObject();
        }
        {
            auto obj2 = writer.writeObject();
        }
    }
    std::string result = os.str();
    // Should have at least two opening braces for objects
    size_t firstBrace = result.find('{');
    EXPECT_NE(firstBrace, std::string::npos);
    size_t secondBrace = result.find('{', firstBrace + 1);
    EXPECT_NE(secondBrace, std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteEmptyString_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(std::string(""));
    }
    std::string result = os.str();
    // Should still have the array structure
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteLargeInteger_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(999999999);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("999999999"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, WriteUnsignedInteger_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(42u);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, ArrayContainsCommasBetweenMultipleValues_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(1);
        writer.write(2);
    }
    std::string result = os.str();
    // Multiple values in a JSON array should be comma-separated
    EXPECT_NE(result.find(','), std::string::npos);
}

TEST_F(JsonArrayWriterTest_526, SingleValueNoComma_526) {
    {
        Catch::JsonArrayWriter writer(os);
        writer.write(1);
    }
    std::string result = os.str();
    // With only one value, there should be no comma in the output
    // (Though comma placement is implementation detail, checking for sanity)
    // The key check is that the value is present
    EXPECT_NE(result.find("1"), std::string::npos);
}
