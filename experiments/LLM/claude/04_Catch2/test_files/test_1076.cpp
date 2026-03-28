#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonObjectWriterTest_1076 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that constructing a JsonObjectWriter with just an ostream works
TEST_F(JsonObjectWriterTest_1076, ConstructWithOstream_1076) {
    {
        JsonObjectWriter writer(oss);
    }
    std::string output = oss.str();
    // After construction and destruction, we expect some JSON object output
    // At minimum, it should contain braces for an empty object
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}

// Test that constructing with an indent level works
TEST_F(JsonObjectWriterTest_1076, ConstructWithIndentLevel_1076) {
    {
        JsonObjectWriter writer(oss, 0);
    }
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}

// Test that constructing with a higher indent level produces indented output
TEST_F(JsonObjectWriterTest_1076, ConstructWithHigherIndentLevel_1076) {
    {
        JsonObjectWriter writer(oss, 3);
    }
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}

// Test move constructor transfers ownership
TEST_F(JsonObjectWriterTest_1076, MoveConstructor_1076) {
    {
        JsonObjectWriter writer1(oss);
        JsonObjectWriter writer2(std::move(writer1));
        // writer1 should now be inactive, writer2 should be active
        // On destruction, only writer2 should write the closing brace
    }
    std::string output = oss.str();
    // Should only have one pair of braces (not two closing braces)
    // Count closing braces
    size_t closingBraces = 0;
    for (char c : output) {
        if (c == '}') closingBraces++;
    }
    EXPECT_EQ(closingBraces, 1u);
}

// Test that write() produces key-value pairs in the output
TEST_F(JsonObjectWriterTest_1076, WriteProducesKeyInOutput_1076) {
    {
        JsonObjectWriter writer(oss);
        writer.write("testKey"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("testKey"), std::string::npos);
}

// Test that multiple writes produce comma-separated entries
TEST_F(JsonObjectWriterTest_1076, MultipleWritesProduceCommas_1076) {
    {
        JsonObjectWriter writer(oss);
        writer.write("key1"_catch_sr);
        writer.write("key2"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("key2"), std::string::npos);
    // There should be a comma between entries
    EXPECT_NE(output.find(','), std::string::npos);
}

// Test empty object (no writes)
TEST_F(JsonObjectWriterTest_1076, EmptyObjectOutput_1076) {
    {
        JsonObjectWriter writer(oss);
    }
    std::string output = oss.str();
    // Should produce an empty JSON object representation
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}

// Test that indent level 0 produces valid output
TEST_F(JsonObjectWriterTest_1076, ZeroIndentLevel_1076) {
    {
        JsonObjectWriter writer(oss, 0);
        writer.write("key"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}

// Test that move-constructed writer can still write
TEST_F(JsonObjectWriterTest_1076, MoveConstructedWriterCanWrite_1076) {
    {
        JsonObjectWriter writer1(oss);
        JsonObjectWriter writer2(std::move(writer1));
        writer2.write("movedKey"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("movedKey"), std::string::npos);
}

// Test move constructor with indent level
TEST_F(JsonObjectWriterTest_1076, MoveConstructorWithIndentLevel_1076) {
    {
        JsonObjectWriter writer1(oss, 2);
        JsonObjectWriter writer2(std::move(writer1));
        writer2.write("indentedKey"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("indentedKey"), std::string::npos);
    size_t closingBraces = 0;
    for (char c : output) {
        if (c == '}') closingBraces++;
    }
    EXPECT_EQ(closingBraces, 1u);
}

// Test that a single write does not produce a comma
TEST_F(JsonObjectWriterTest_1076, SingleWriteNoComma_1076) {
    {
        JsonObjectWriter writer(oss);
        writer.write("onlyKey"_catch_sr);
    }
    std::string output = oss.str();
    // With only one key, there should be no comma
    // Find positions of opening brace and the key
    size_t openBrace = output.find('{');
    size_t closeBrace = output.find('}');
    std::string content = output.substr(openBrace + 1, closeBrace - openBrace - 1);
    // The content between braces should not start with a comma
    // (first entry should not be preceded by a comma)
    size_t commaCount = 0;
    for (char c : content) {
        if (c == ',') commaCount++;
    }
    EXPECT_EQ(commaCount, 0u);
}

// Test boundary: large indent level
TEST_F(JsonObjectWriterTest_1076, LargeIndentLevel_1076) {
    {
        JsonObjectWriter writer(oss, 100);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find('{'), std::string::npos);
    EXPECT_NE(output.find('}'), std::string::npos);
}
