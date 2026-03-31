#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>
#include <string>

// Include the header for the class under test
#include "catch2/internal/catch_jsonwriter.hpp"

namespace {

// ============================================================
// Tests for JsonUtils::indent
// ============================================================

class JsonUtilsIndentTest_527 : public ::testing::Test {
protected:
    std::ostringstream os;
};

TEST_F(JsonUtilsIndentTest_527, IndentLevelZeroProducesNoOutput_527) {
    Catch::JsonUtils::indent(os, 0);
    EXPECT_EQ(os.str(), "");
}

TEST_F(JsonUtilsIndentTest_527, IndentLevelOneProducesTwoSpaces_527) {
    Catch::JsonUtils::indent(os, 1);
    EXPECT_EQ(os.str(), "  ");
}

TEST_F(JsonUtilsIndentTest_527, IndentLevelTwoProducesFourSpaces_527) {
    Catch::JsonUtils::indent(os, 2);
    EXPECT_EQ(os.str(), "    ");
}

TEST_F(JsonUtilsIndentTest_527, IndentLevelThreeProducesSixSpaces_527) {
    Catch::JsonUtils::indent(os, 3);
    EXPECT_EQ(os.str(), "      ");
}

TEST_F(JsonUtilsIndentTest_527, IndentLevelFiveProducesTenSpaces_527) {
    Catch::JsonUtils::indent(os, 5);
    std::string expected(10, ' ');
    EXPECT_EQ(os.str(), expected);
}

TEST_F(JsonUtilsIndentTest_527, IndentLevelTenProducesTwentySpaces_527) {
    Catch::JsonUtils::indent(os, 10);
    std::string expected(20, ' ');
    EXPECT_EQ(os.str(), expected);
}

TEST_F(JsonUtilsIndentTest_527, IndentAppendsToExistingContent_527) {
    os << "prefix";
    Catch::JsonUtils::indent(os, 2);
    EXPECT_EQ(os.str(), "prefix    ");
}

TEST_F(JsonUtilsIndentTest_527, MultipleIndentCallsAccumulate_527) {
    Catch::JsonUtils::indent(os, 1);
    Catch::JsonUtils::indent(os, 2);
    EXPECT_EQ(os.str(), "      ");  // 2 + 4 = 6 spaces
}

// ============================================================
// Tests for JsonUtils::appendCommaNewline
// ============================================================

class JsonUtilsAppendCommaNewlineTest_527 : public ::testing::Test {
protected:
    std::ostringstream os;
};

TEST_F(JsonUtilsAppendCommaNewlineTest_527, FirstCallShouldCommaFalse_SetsToTrue_527) {
    bool should_comma = false;
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 0);
    EXPECT_TRUE(should_comma);
}

TEST_F(JsonUtilsAppendCommaNewlineTest_527, FirstCallShouldCommaFalse_NoCommaInOutput_527) {
    bool should_comma = false;
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 0);
    std::string result = os.str();
    // When should_comma is false initially, no comma should be written
    EXPECT_EQ(result.find(','), std::string::npos);
}

TEST_F(JsonUtilsAppendCommaNewlineTest_527, SecondCallShouldCommaTrue_ProducesComma_527) {
    bool should_comma = true;
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 0);
    std::string result = os.str();
    // When should_comma is true, a comma should appear
    EXPECT_NE(result.find(','), std::string::npos);
}

TEST_F(JsonUtilsAppendCommaNewlineTest_527, SecondCallShouldCommaTrue_StillTrue_527) {
    bool should_comma = true;
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 0);
    EXPECT_TRUE(should_comma);
}

TEST_F(JsonUtilsAppendCommaNewlineTest_527, AppendCommaNewlineWithIndentLevel_527) {
    bool should_comma = true;
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 2);
    std::string result = os.str();
    // Should contain a comma somewhere
    EXPECT_NE(result.find(','), std::string::npos);
}

TEST_F(JsonUtilsAppendCommaNewlineTest_527, AppendCommaNewlineContainsNewline_527) {
    bool should_comma = true;
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 0);
    std::string result = os.str();
    // Should contain a newline
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST_F(JsonUtilsAppendCommaNewlineTest_527, FirstCallThenSecondCall_527) {
    bool should_comma = false;
    // First call - no comma
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 1);
    std::string after_first = os.str();

    // Second call - should have comma
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 1);
    std::string after_second = os.str();

    // The second portion should contain a comma
    std::string second_portion = after_second.substr(after_first.length());
    EXPECT_NE(second_portion.find(','), std::string::npos);
}

TEST_F(JsonUtilsAppendCommaNewlineTest_527, ZeroIndentLevelWithComma_527) {
    bool should_comma = true;
    Catch::JsonUtils::appendCommaNewline(os, should_comma, 0);
    std::string result = os.str();
    EXPECT_NE(result.find(','), std::string::npos);
    EXPECT_NE(result.find('\n'), std::string::npos);
}

}  // namespace
