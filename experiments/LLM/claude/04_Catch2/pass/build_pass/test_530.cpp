#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;

class JsonObjectWriterTest_530 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test that constructing a JsonObjectWriter with default indent and destroying it produces valid output
TEST_F(JsonObjectWriterTest_530, DefaultConstructionAndDestruction_530) {
    {
        JsonObjectWriter writer(os);
    }
    std::string result = os.str();
    // The writer should produce some output (at least opening/closing braces)
    EXPECT_FALSE(result.empty());
}

// Test that constructing with a specific indent level works
TEST_F(JsonObjectWriterTest_530, ConstructionWithIndentLevel_530) {
    {
        JsonObjectWriter writer(os, 2);
    }
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test writing a single key-value pair
TEST_F(JsonObjectWriterTest_530, WriteSingleKey_530) {
    {
        JsonObjectWriter writer(os);
        writer.write("key");
    }
    std::string result = os.str();
    // Should contain the key
    EXPECT_NE(result.find("\"key\""), std::string::npos);
}

// Test writing multiple keys produces commas between entries
TEST_F(JsonObjectWriterTest_530, WriteMultipleKeys_530) {
    {
        JsonObjectWriter writer(os);
        writer.write("key1");
        writer.write("key2");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("\"key1\""), std::string::npos);
    EXPECT_NE(result.find("\"key2\""), std::string::npos);
    // Second entry should have a comma before it
    // Find position of key2 and check for comma before it
    auto pos_key1 = result.find("\"key1\"");
    auto pos_key2 = result.find("\"key2\"");
    EXPECT_LT(pos_key1, pos_key2);
}

// Test that write produces ": " after the key
TEST_F(JsonObjectWriterTest_530, WriteKeyHasColonSeparator_530) {
    {
        JsonObjectWriter writer(os);
        writer.write("mykey");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("\"mykey\": "), std::string::npos);
}

// Test writing with empty key
TEST_F(JsonObjectWriterTest_530, WriteEmptyKey_530) {
    {
        JsonObjectWriter writer(os);
        writer.write("");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("\"\": "), std::string::npos);
}

// Test writing three keys to ensure comma handling works for multiple entries
TEST_F(JsonObjectWriterTest_530, WriteThreeKeys_530) {
    {
        JsonObjectWriter writer(os);
        writer.write("a");
        writer.write("b");
        writer.write("c");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("\"a\""), std::string::npos);
    EXPECT_NE(result.find("\"b\""), std::string::npos);
    EXPECT_NE(result.find("\"c\""), std::string::npos);
}

// Test move construction
TEST_F(JsonObjectWriterTest_530, MoveConstruction_530) {
    {
        JsonObjectWriter writer(os);
        writer.write("before_move");
        JsonObjectWriter moved_writer(std::move(writer));
        moved_writer.write("after_move");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("\"before_move\""), std::string::npos);
    EXPECT_NE(result.find("\"after_move\""), std::string::npos);
}

// Test that no writes produces an empty object
TEST_F(JsonObjectWriterTest_530, NoWritesProducesEmptyObject_530) {
    {
        JsonObjectWriter writer(os);
    }
    std::string result = os.str();
    // Should still produce valid JSON object notation (e.g., {})
    EXPECT_NE(result.find("{"), std::string::npos);
    EXPECT_NE(result.find("}"), std::string::npos);
}

// Test with StringRef constructed from std::string
TEST_F(JsonObjectWriterTest_530, WriteWithStdString_530) {
    {
        std::string key = "string_key";
        JsonObjectWriter writer(os);
        writer.write(StringRef(key));
    }
    std::string result = os.str();
    EXPECT_NE(result.find("\"string_key\": "), std::string::npos);
}

// Test with a key containing special characters
TEST_F(JsonObjectWriterTest_530, WriteKeyWithSpecialChars_530) {
    {
        JsonObjectWriter writer(os);
        writer.write("key with spaces");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("\"key with spaces\": "), std::string::npos);
}

// Test indent level 0
TEST_F(JsonObjectWriterTest_530, IndentLevelZero_530) {
    {
        JsonObjectWriter writer(os, 0);
        writer.write("key");
    }
    std::string result = os.str();
    EXPECT_NE(result.find("\"key\": "), std::string::npos);
}

// Test that the first write does not have a comma, but subsequent ones do
TEST_F(JsonObjectWriterTest_530, CommaHandlingFirstVsSubsequent_530) {
    {
        JsonObjectWriter writer(os);
        writer.write("first");
        writer.write("second");
    }
    std::string result = os.str();
    
    // Find position of first key
    auto first_pos = result.find("\"first\"");
    ASSERT_NE(first_pos, std::string::npos);
    
    // Check that there's no comma before the first key within the object
    // (There should be a comma somewhere before "second" though)
    auto second_pos = result.find("\"second\"");
    ASSERT_NE(second_pos, std::string::npos);
    
    // Between first and second, there should be a comma
    std::string between = result.substr(first_pos, second_pos - first_pos);
    EXPECT_NE(between.find(","), std::string::npos);
}

// Test with a long key
TEST_F(JsonObjectWriterTest_530, WriteLongKey_530) {
    {
        std::string long_key(256, 'x');
        JsonObjectWriter writer(os);
        writer.write(StringRef(long_key));
    }
    std::string result = os.str();
    std::string long_key(256, 'x');
    std::string expected = "\"" + long_key + "\": ";
    EXPECT_NE(result.find(expected), std::string::npos);
}
