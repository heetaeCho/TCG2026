#include "catch2/internal/catch_jsonwriter.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace Catch {

class JsonValueWriterTest_536 : public ::testing::Test {
protected:
    std::stringstream ss;
};

// Test that writeArray returns a JsonArrayWriter and produces valid array output
TEST_F(JsonValueWriterTest_536, WriteArrayProducesArrayOutput_536) {
    {
        auto writer = JsonValueWriter(ss);
        auto arr = std::move(writer).writeArray();
        // JsonArrayWriter destructor should close the array
    }
    std::string output = ss.str();
    // Expect the output to contain array brackets
    EXPECT_NE(output.find('['), std::string::npos);
    EXPECT_NE(output.find(']'), std::string::npos);
}

// Test that writeObject returns a JsonObjectWriter and produces valid object output
TEST_F(JsonValueWriterTest_536, WriteObjectProducesObjectOutput_536) {
    {
        auto writer = JsonValueWriter(ss);
        auto obj = std::move(writer).writeObject();
        // JsonObjectWriter destructor should close the object
    }
    std::string output = ss.str();
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}

// Test writing a string value produces quoted output
TEST_F(JsonValueWriterTest_536, WriteStringValueProducesQuotedOutput_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(Catch::StringRef("hello"));
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// Test writing a boolean true value
TEST_F(JsonValueWriterTest_536, WriteBoolTrueValue_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(true);
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

// Test writing a boolean false value
TEST_F(JsonValueWriterTest_536, WriteBoolFalseValue_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(false);
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

// Test writing an integer value
TEST_F(JsonValueWriterTest_536, WriteIntegerValue_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(42);
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test writing a negative integer value
TEST_F(JsonValueWriterTest_536, WriteNegativeIntegerValue_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(-7);
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("-7"), std::string::npos);
}

// Test writing a floating point value
TEST_F(JsonValueWriterTest_536, WriteFloatingPointValue_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(3.14);
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// Test writing an empty string
TEST_F(JsonValueWriterTest_536, WriteEmptyString_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(Catch::StringRef(""));
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("\"\""), std::string::npos);
}

// Test writing zero value
TEST_F(JsonValueWriterTest_536, WriteZeroValue_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(0);
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// Test constructor with indent level
TEST_F(JsonValueWriterTest_536, ConstructorWithIndentLevel_536) {
    {
        auto writer = JsonValueWriter(ss, 2);
        std::move(writer).write(Catch::StringRef("indented"));
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("\"indented\""), std::string::npos);
}

// Test writeArray with indent level
TEST_F(JsonValueWriterTest_536, WriteArrayWithIndentLevel_536) {
    {
        auto writer = JsonValueWriter(ss, 1);
        auto arr = std::move(writer).writeArray();
    }
    std::string output = ss.str();
    EXPECT_NE(output.find('['), std::string::npos);
    EXPECT_NE(output.find(']'), std::string::npos);
}

// Test writeObject with indent level
TEST_F(JsonValueWriterTest_536, WriteObjectWithIndentLevel_536) {
    {
        auto writer = JsonValueWriter(ss, 1);
        auto obj = std::move(writer).writeObject();
    }
    std::string output = ss.str();
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}

// Test writing a large integer value
TEST_F(JsonValueWriterTest_536, WriteLargeIntegerValue_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(static_cast<std::int64_t>(9999999999LL));
    }
    std::string output = ss.str();
    EXPECT_NE(output.find("9999999999"), std::string::npos);
}

// Test writing a string with special characters
TEST_F(JsonValueWriterTest_536, WriteStringWithSpecialChars_536) {
    {
        auto writer = JsonValueWriter(ss);
        std::move(writer).write(Catch::StringRef("hello\nworld"));
    }
    std::string output = ss.str();
    // The output should contain some representation of the string
    EXPECT_FALSE(output.empty());
}

// Test default indent level produces valid output
TEST_F(JsonValueWriterTest_536, DefaultIndentLevelProducesValidOutput_536) {
    {
        auto writer = JsonValueWriter(ss);
        auto arr = std::move(writer).writeArray();
    }
    std::string output = ss.str();
    // Should start with '[' (possibly with whitespace)
    EXPECT_FALSE(output.empty());
}

// Test empty array output
TEST_F(JsonValueWriterTest_536, EmptyArrayOutput_536) {
    {
        auto writer = JsonValueWriter(ss);
        auto arr = std::move(writer).writeArray();
        // Do not add any elements
    }
    std::string output = ss.str();
    // Should produce an empty array representation
    EXPECT_NE(output.find('['), std::string::npos);
    EXPECT_NE(output.find(']'), std::string::npos);
}

// Test empty object output
TEST_F(JsonValueWriterTest_536, EmptyObjectOutput_536) {
    {
        auto writer = JsonValueWriter(ss);
        auto obj = std::move(writer).writeObject();
        // Do not add any key-value pairs
    }
    std::string output = ss.str();
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}

} // namespace Catch
