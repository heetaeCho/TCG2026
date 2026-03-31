#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonObjectWriterTest_529 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that default constructor creates a valid object that outputs braces on destruction
TEST_F(JsonObjectWriterTest_529, DefaultConstructorOutputsBraces_529) {
    {
        JsonObjectWriter writer(oss);
    }
    std::string result = oss.str();
    // Should contain closing brace
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test that constructor with indent level works
TEST_F(JsonObjectWriterTest_529, ConstructorWithIndentLevel_529) {
    {
        JsonObjectWriter writer(oss, 0);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test with a non-zero indent level
TEST_F(JsonObjectWriterTest_529, ConstructorWithNonZeroIndentLevel_529) {
    {
        JsonObjectWriter writer(oss, 2);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test that move constructor transfers ownership and prevents double output
TEST_F(JsonObjectWriterTest_529, MoveConstructorTransfersOwnership_529) {
    {
        JsonObjectWriter writer1(oss);
        JsonObjectWriter writer2(std::move(writer1));
    }
    std::string result = oss.str();
    // There should be exactly one closing brace from the moved-to object
    size_t count = 0;
    for (char c : result) {
        if (c == '}') count++;
    }
    EXPECT_EQ(count, 1u);
}

// Test writing a key-value pair
TEST_F(JsonObjectWriterTest_529, WriteKeyProducesOutput_529) {
    {
        JsonObjectWriter writer(oss);
        writer.write("key");
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("key"), std::string::npos);
}

// Test writing multiple key-value pairs produces commas between them
TEST_F(JsonObjectWriterTest_529, MultipleWritesProduceCommas_529) {
    {
        JsonObjectWriter writer(oss);
        writer.write("key1");
        writer.write("key2");
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("key1"), std::string::npos);
    EXPECT_NE(result.find("key2"), std::string::npos);
    // Should contain a comma separating elements
    EXPECT_NE(result.find(','), std::string::npos);
}

// Test that destructor outputs newline before closing brace
TEST_F(JsonObjectWriterTest_529, DestructorOutputsNewlineBeforeClosingBrace_529) {
    {
        JsonObjectWriter writer(oss);
    }
    std::string result = oss.str();
    // Should contain newline followed (potentially with spaces) by closing brace
    EXPECT_NE(result.find('\n'), std::string::npos);
}

// Test empty object with zero indent
TEST_F(JsonObjectWriterTest_529, EmptyObjectZeroIndent_529) {
    {
        JsonObjectWriter writer(oss, 0);
    }
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test that moved-from object does not produce output on destruction
TEST_F(JsonObjectWriterTest_529, MovedFromObjectDoesNotOutput_529) {
    std::ostringstream oss1;
    std::ostringstream oss2;
    {
        JsonObjectWriter writer1(oss1);
        // After move, writer1 should be inactive
        JsonObjectWriter writer2(std::move(writer1));
    }
    // oss1 should not have a closing brace from writer1's destructor
    // (writer1 was moved from, so m_active should be false)
    std::string result1 = oss1.str();
    size_t braceCount = 0;
    for (char c : result1) {
        if (c == '}') braceCount++;
    }
    // Only one closing brace should exist total (from writer2 which writes to oss1's stream)
    EXPECT_EQ(braceCount, 1u);
}

// Test writing with an empty key string
TEST_F(JsonObjectWriterTest_529, WriteEmptyKey_529) {
    {
        JsonObjectWriter writer(oss);
        writer.write("");
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test large indent level
TEST_F(JsonObjectWriterTest_529, LargeIndentLevel_529) {
    {
        JsonObjectWriter writer(oss, 10);
    }
    std::string result = oss.str();
    EXPECT_NE(result.find('}'), std::string::npos);
}

// Test that write returns a JsonValueWriter (compiles and can be used)
TEST_F(JsonObjectWriterTest_529, WriteReturnsJsonValueWriter_529) {
    {
        JsonObjectWriter writer(oss);
        auto valueWriter = writer.write("testKey");
        // The returned JsonValueWriter should be usable
        // Just verifying it compiles and doesn't crash
    }
    std::string result = oss.str();
    EXPECT_NE(result.find("testKey"), std::string::npos);
}
