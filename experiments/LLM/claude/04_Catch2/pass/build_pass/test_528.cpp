#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// Include the header for the class under test
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

// ============================================================
// Tests for JsonUtils::appendCommaNewline
// ============================================================

class JsonUtilsAppendCommaNewlineTest_528 : public ::testing::Test {
protected:
    std::ostringstream os;
    JsonUtils utils;
};

// Test that when should_comma is false, no comma is prepended, but newline and indent are added
TEST_F(JsonUtilsAppendCommaNewlineTest_528, NoCommaOnFirstCall_528) {
    bool should_comma = false;
    utils.appendCommaNewline(os, should_comma, 0);
    std::string result = os.str();
    // Should not start with a comma
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result[0], ',');
    // Should contain a newline
    EXPECT_NE(result.find('\n'), std::string::npos);
    // should_comma should now be true
    EXPECT_TRUE(should_comma);
}

// Test that when should_comma is true, a comma is prepended
TEST_F(JsonUtilsAppendCommaNewlineTest_528, CommaOnSubsequentCall_528) {
    bool should_comma = true;
    utils.appendCommaNewline(os, should_comma, 0);
    std::string result = os.str();
    // Should start with a comma
    EXPECT_EQ(result[0], ',');
    // Should contain a newline
    EXPECT_NE(result.find('\n'), std::string::npos);
    // should_comma should remain true
    EXPECT_TRUE(should_comma);
}

// Test that should_comma is set to true after the call (initially false)
TEST_F(JsonUtilsAppendCommaNewlineTest_528, ShouldCommaSetToTrue_528) {
    bool should_comma = false;
    utils.appendCommaNewline(os, should_comma, 0);
    EXPECT_TRUE(should_comma);
}

// Test that calling twice produces comma on second call
TEST_F(JsonUtilsAppendCommaNewlineTest_528, SecondCallProducesComma_528) {
    bool should_comma = false;
    utils.appendCommaNewline(os, should_comma, 0);
    std::string first_result = os.str();
    
    // Reset stream
    os.str("");
    os.clear();
    
    utils.appendCommaNewline(os, should_comma, 0);
    std::string second_result = os.str();
    EXPECT_EQ(second_result[0], ',');
}

// Test indentation with level 0
TEST_F(JsonUtilsAppendCommaNewlineTest_528, IndentLevel0_528) {
    bool should_comma = false;
    utils.appendCommaNewline(os, should_comma, 0);
    std::string result = os.str();
    // At level 0, after newline there should be no (or minimal) indentation
    // Just verify the output contains a newline
    EXPECT_NE(result.find('\n'), std::string::npos);
}

// Test indentation with level 1
TEST_F(JsonUtilsAppendCommaNewlineTest_528, IndentLevel1_528) {
    bool should_comma = false;
    utils.appendCommaNewline(os, should_comma, 1);
    std::string result = os.str();
    EXPECT_NE(result.find('\n'), std::string::npos);
    // After the newline, there should be some indentation (more than level 0)
    std::ostringstream os0;
    bool sc0 = false;
    utils.appendCommaNewline(os0, sc0, 0);
    EXPECT_GE(result.size(), os0.str().size());
}

// Test indentation with higher level
TEST_F(JsonUtilsAppendCommaNewlineTest_528, IndentLevel3_528) {
    bool should_comma = false;
    utils.appendCommaNewline(os, should_comma, 3);
    std::string result = os.str();
    
    std::ostringstream os1;
    bool sc1 = false;
    utils.appendCommaNewline(os1, sc1, 1);
    std::string result1 = os1.str();
    
    // Higher level should produce more output (more indentation)
    EXPECT_GT(result.size(), result1.size());
}

// Test with comma and indentation combined
TEST_F(JsonUtilsAppendCommaNewlineTest_528, CommaWithIndentation_528) {
    bool should_comma = true;
    utils.appendCommaNewline(os, should_comma, 2);
    std::string result = os.str();
    EXPECT_EQ(result[0], ',');
    EXPECT_NE(result.find('\n'), std::string::npos);
}

// ============================================================
// Tests for JsonUtils::indent
// ============================================================

class JsonUtilsIndentTest_528 : public ::testing::Test {
protected:
    std::ostringstream os;
    JsonUtils utils;
};

// Test indent with level 0 produces no (or empty) indentation
TEST_F(JsonUtilsIndentTest_528, IndentLevel0_528) {
    utils.indent(os, 0);
    std::string result = os.str();
    // Level 0 should produce empty or no indentation
    EXPECT_TRUE(result.empty() || result.find_first_not_of(' ') == std::string::npos);
}

// Test indent with level 1 produces some whitespace
TEST_F(JsonUtilsIndentTest_528, IndentLevel1_528) {
    utils.indent(os, 1);
    std::string result = os.str();
    // Should have some spaces
    if (!result.empty()) {
        EXPECT_EQ(result.find_first_not_of(' '), std::string::npos);
    }
}

// Test that higher indent level produces more whitespace
TEST_F(JsonUtilsIndentTest_528, HigherLevelMoreIndent_528) {
    std::ostringstream os1, os2;
    utils.indent(os1, 1);
    utils.indent(os2, 3);
    EXPECT_GT(os2.str().size(), os1.str().size());
}

// Test indent proportionality: level 2 should be twice level 1
TEST_F(JsonUtilsIndentTest_528, IndentProportional_528) {
    std::ostringstream os1, os2;
    utils.indent(os1, 1);
    utils.indent(os2, 2);
    std::string r1 = os1.str();
    std::string r2 = os2.str();
    if (!r1.empty()) {
        EXPECT_EQ(r2.size(), r1.size() * 2);
    }
}

// Test indent with a large level
TEST_F(JsonUtilsIndentTest_528, IndentLargeLevel_528) {
    utils.indent(os, 10);
    std::string result = os.str();
    // Should produce substantial whitespace
    if (!result.empty()) {
        EXPECT_EQ(result.find_first_not_of(' '), std::string::npos);
    }
    // Should be 10 times the unit indent
    std::ostringstream os1;
    utils.indent(os1, 1);
    if (!os1.str().empty()) {
        EXPECT_EQ(result.size(), os1.str().size() * 10);
    }
}
