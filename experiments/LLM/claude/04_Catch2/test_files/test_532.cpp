#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonArrayWriterTest_532 : public ::testing::Test {
protected:
    std::ostringstream os;
};

TEST_F(JsonArrayWriterTest_532, ConstructorWithOutputStream_532) {
    JsonArrayWriter writer(os);
    // Writer should be constructible with just an ostream
    // Destructor will be called, which should close the array
}

TEST_F(JsonArrayWriterTest_532, ConstructorWithIndentLevel_532) {
    JsonArrayWriter writer(os, 2);
    // Writer should be constructible with ostream and indent level
}

TEST_F(JsonArrayWriterTest_532, DestructorClosesArray_532) {
    {
        JsonArrayWriter writer(os);
    }
    std::string result = os.str();
    // The destructor should produce closing bracket
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteObjectReturnsJsonObjectWriter_532) {
    {
        JsonArrayWriter writer(os);
        auto obj = writer.writeObject();
        // obj is a JsonObjectWriter, its destructor should close the object
    }
    std::string result = os.str();
    // Should contain object braces within array
    EXPECT_NE(result.find('{'), std::string::npos);
    EXPECT_NE(result.find('}'), std::string::npos);
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteArrayReturnsJsonArrayWriter_532) {
    {
        JsonArrayWriter writer(os);
        {
            auto arr = writer.writeArray();
        }
    }
    std::string result = os.str();
    // Should contain nested array brackets
    // At least two opening and two closing brackets
    size_t openCount = 0, closeCount = 0;
    for (char c : result) {
        if (c == '[') openCount++;
        if (c == ']') closeCount++;
    }
    EXPECT_GE(openCount, 2u);
    EXPECT_GE(closeCount, 2u);
}

TEST_F(JsonArrayWriterTest_532, WriteBoolTrue_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(true);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteBoolFalse_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(false);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteIntegerValue_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(42);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteStringValue_532) {
    {
        JsonArrayWriter writer(os);
        writer.write("hello");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteMultipleValues_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(1);
        writer.write(2);
        writer.write(3);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
    // Multiple values should have commas between them
    EXPECT_NE(result.find(","), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteChaining_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(1).write(2).write(3);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, EmptyArray_532) {
    {
        JsonArrayWriter writer(os);
    }
    std::string result = os.str();
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, MoveConstructor_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(1);
        JsonArrayWriter moved(std::move(writer));
        moved.write(2);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteObjectThenValue_532) {
    {
        JsonArrayWriter writer(os);
        {
            auto obj = writer.writeObject();
        }
        writer.write(42);
    }
    std::string result = os.str();
    EXPECT_NE(result.find('{'), std::string::npos);
    EXPECT_NE(result.find('}'), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, MultipleObjectWrites_532) {
    {
        JsonArrayWriter writer(os);
        {
            auto obj1 = writer.writeObject();
        }
        {
            auto obj2 = writer.writeObject();
        }
    }
    std::string result = os.str();
    // Should have comma separating two objects
    EXPECT_NE(result.find(","), std::string::npos);
    // Count opening braces - should be at least 2
    size_t braceCount = 0;
    for (char c : result) {
        if (c == '{') braceCount++;
    }
    EXPECT_GE(braceCount, 2u);
}

TEST_F(JsonArrayWriterTest_532, WriteWithZeroIndentLevel_532) {
    {
        JsonArrayWriter writer(os, 0);
        writer.write(1);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteWithHighIndentLevel_532) {
    {
        JsonArrayWriter writer(os, 10);
        writer.write(1);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("1"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteNegativeInteger_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(-5);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("-5"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, WriteDoubleValue_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(3.14);
    }
    std::string result = os.str();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, NestedArrayWriteValues_532) {
    {
        JsonArrayWriter writer(os);
        {
            auto inner = writer.writeArray();
            inner.write(1);
            inner.write(2);
        }
    }
    std::string result = os.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_532, SingleValueNoComma_532) {
    {
        JsonArrayWriter writer(os);
        writer.write(42);
    }
    std::string result = os.str();
    // Find the position of 42 - there should be no comma before the first element
    size_t pos42 = result.find("42");
    EXPECT_NE(pos42, std::string::npos);
    // Check that there's no comma before the first value (between [ and 42)
    std::string beforeValue = result.substr(0, pos42);
    EXPECT_EQ(beforeValue.find(","), std::string::npos);
}
