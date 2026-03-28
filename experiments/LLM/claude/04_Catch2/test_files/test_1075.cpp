#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the header for JsonObjectWriter
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonObjectWriterTest_1075 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that constructing a JsonObjectWriter with just an ostream outputs '{'
TEST_F(JsonObjectWriterTest_1075, ConstructorWithOstreamOutputsOpenBrace_1075) {
    {
        JsonObjectWriter writer(oss);
    }
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], '{');
}

// Test that constructing with ostream and indent_level outputs '{'
TEST_F(JsonObjectWriterTest_1075, ConstructorWithIndentLevelOutputsOpenBrace_1075) {
    {
        JsonObjectWriter writer(oss, 0);
    }
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], '{');
}

// Test that destructor outputs closing '}'
TEST_F(JsonObjectWriterTest_1075, DestructorOutputsClosingBrace_1075) {
    {
        JsonObjectWriter writer(oss);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test that an empty object produces "{}" (possibly with whitespace/newlines)
TEST_F(JsonObjectWriterTest_1075, EmptyObjectProducesEmptyJson_1075) {
    {
        JsonObjectWriter writer(oss);
    }
    std::string result = oss.str();
    // Should start with '{' and contain '}'
    EXPECT_EQ(result.front(), '{');
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test with indent_level 0
TEST_F(JsonObjectWriterTest_1075, IndentLevelZero_1075) {
    {
        JsonObjectWriter writer(oss, 0);
    }
    std::string result = oss.str();
    EXPECT_EQ(result.front(), '{');
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test with a higher indent level
TEST_F(JsonObjectWriterTest_1075, HigherIndentLevel_1075) {
    {
        JsonObjectWriter writer(oss, 5);
    }
    std::string result = oss.str();
    EXPECT_EQ(result.front(), '{');
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test move constructor - source should become inactive
TEST_F(JsonObjectWriterTest_1075, MoveConstructor_1075) {
    {
        JsonObjectWriter writer1(oss);
        JsonObjectWriter writer2(std::move(writer1));
    }
    std::string result = oss.str();
    // Only one complete object should be written (moved-from should not write closing brace)
    EXPECT_EQ(result.front(), '{');
    // Count closing braces - should be exactly 1 since the moved-from object shouldn't close
    size_t closingBraceCount = 0;
    for (char c : result) {
        if (c == '}') closingBraceCount++;
    }
    EXPECT_EQ(closingBraceCount, 1u);
}

// Test writing a single key-value pair
TEST_F(JsonObjectWriterTest_1075, WriteSingleKey_1075) {
    {
        JsonObjectWriter writer(oss);
        writer.write("key");
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("key"), std::string::npos);
}

// Test writing multiple keys produces commas between entries
TEST_F(JsonObjectWriterTest_1075, WriteMultipleKeysProducesCommas_1075) {
    {
        JsonObjectWriter writer(oss);
        writer.write("key1");
        writer.write("key2");
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("key1"), std::string::npos);
    EXPECT_NE(result.find("key2"), std::string::npos);
    // There should be a comma somewhere between the two keys
    EXPECT_NE(result.find(','), std::string::npos);
}

// Test that first write does not produce a leading comma
TEST_F(JsonObjectWriterTest_1075, FirstWriteNoLeadingComma_1075) {
    {
        JsonObjectWriter writer(oss);
        writer.write("first");
    }
    std::string result = oss.str();
    // Between '{' and the key "first", there should be no comma
    size_t openBrace = result.find('{');
    size_t firstKey = result.find("first");
    ASSERT_NE(openBrace, std::string::npos);
    ASSERT_NE(firstKey, std::string::npos);
    std::string between = result.substr(openBrace + 1, firstKey - openBrace - 1);
    EXPECT_EQ(between.find(','), std::string::npos);
}

// Test that the key is quoted in the output
TEST_F(JsonObjectWriterTest_1075, KeyIsQuotedInOutput_1075) {
    {
        JsonObjectWriter writer(oss);
        writer.write("mykey");
    }
    std::string result = oss.str();
    // The key should appear with quotes around it
    EXPECT_NE(result.find("\"mykey\""), std::string::npos);
}

// Test with a large indent level
TEST_F(JsonObjectWriterTest_1075, LargeIndentLevel_1075) {
    {
        JsonObjectWriter writer(oss, 100);
    }
    std::string result = oss.str();
    EXPECT_EQ(result.front(), '{');
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test writing with empty string key
TEST_F(JsonObjectWriterTest_1075, WriteEmptyStringKey_1075) {
    {
        JsonObjectWriter writer(oss);
        writer.write("");
    }
    std::string result = oss.str();
    // Should still produce valid output with empty key
    EXPECT_EQ(result.front(), '{');
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test that write returns a JsonValueWriter (compile test - if it compiles, it returns the right type)
TEST_F(JsonObjectWriterTest_1075, WriteReturnsJsonValueWriter_1075) {
    {
        JsonObjectWriter writer(oss);
        auto valueWriter = writer.write("test");
        // The fact that this compiles and runs is the test
        (void)valueWriter;
    }
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}
