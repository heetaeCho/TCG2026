#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstdint>

#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonArrayWriterTest_534 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

TEST_F(JsonArrayWriterTest_534, DefaultConstructorCreatesValidWriter_534) {
    JsonArrayWriter writer(oss);
    // Destructor should write closing bracket
}

TEST_F(JsonArrayWriterTest_534, ConstructorWithIndentLevel_534) {
    JsonArrayWriter writer(oss, 2);
    // Should construct without error
}

TEST_F(JsonArrayWriterTest_534, WriteBoolTrue_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteBoolFalse_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(false);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteMultipleBoolValues_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
        writer.write(false);
        writer.write(true);
    }
    std::string result = oss.str();
    // Should contain opening and closing brackets
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, EmptyArrayProducesValidJson_534) {
    {
        JsonArrayWriter writer(oss);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteIntegerValue_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(42);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteStringValue_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write("hello");
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteStdStringValue_534) {
    {
        JsonArrayWriter writer(oss);
        std::string val = "test_string";
        writer.write(val);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("test_string"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteChainingReturnsSelf_534) {
    {
        JsonArrayWriter writer(oss);
        JsonArrayWriter& ref = writer.write(true);
        EXPECT_EQ(&ref, &writer);
    }
}

TEST_F(JsonArrayWriterTest_534, WriteChainingMultipleValues_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true).write(false).write(42);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find("false"), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteNestedObject_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
        { auto obj = writer.writeObject(); }
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("{"), std::string::npos);
    EXPECT_NE(result.find("}"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteNestedArray_534) {
    {
        JsonArrayWriter writer(oss);
        { auto arr = writer.writeArray(); }
    }
    std::string result = oss.str();
    // Should have nested array brackets
    // At minimum two opening and two closing brackets
    size_t openCount = 0, closeCount = 0;
    for (char c : result) {
        if (c == '[') openCount++;
        if (c == ']') closeCount++;
    }
    EXPECT_GE(openCount, 2u);
    EXPECT_GE(closeCount, 2u);
}

TEST_F(JsonArrayWriterTest_534, MoveConstructor_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(1);
        JsonArrayWriter moved(std::move(writer));
        moved.write(2);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteZero_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(0);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteNegativeNumber_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(-1);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("-1"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteLargeNumber_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(999999999);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("999999999"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteObjectReturnsMoveableObject_534) {
    {
        JsonArrayWriter writer(oss);
        auto obj = writer.writeObject();
        // obj should be a valid JsonObjectWriter - destructor writes closing brace
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("{"), std::string::npos);
    EXPECT_NE(result.find("}"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, WriteArrayReturnsMoveableArray_534) {
    {
        JsonArrayWriter writer(oss);
        auto arr = writer.writeArray();
        arr.write(true);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, IndentLevelZero_534) {
    {
        JsonArrayWriter writer(oss, 0);
        writer.write(true);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, MultipleMixedTypes_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
        writer.write(false);
        writer.write(42);
        writer.write("hello");
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
    EXPECT_NE(result.find("true"), std::string::npos);
    EXPECT_NE(result.find("false"), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, SingleBoolTrueArray_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(true);
    }
    std::string result = oss.str();
    // Should be a valid JSON array with single true value
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(JsonArrayWriterTest_534, SingleBoolFalseArray_534) {
    {
        JsonArrayWriter writer(oss);
        writer.write(false);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
    EXPECT_NE(result.find("false"), std::string::npos);
}
