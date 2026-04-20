#include <gtest/gtest.h>
#include <sstream>
#include "JsonBox/IndentCanceller.h"
#include "JsonBox/Grammar.h"

using namespace JsonBox;

class IndentCancellerTest_5 : public ::testing::Test {
protected:
    std::ostringstream output;
    IndentCanceller canceller;

    void SetUp() override {
        output.str("");
    }
};

TEST_F(IndentCancellerTest_5, NormalCharacterPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, 'a');
    EXPECT_EQ(output.str(), "a");
}

TEST_F(IndentCancellerTest_5, SpaceInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, Whitespace::SPACE);
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\" \"");
}

TEST_F(IndentCancellerTest_5, SpaceOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Whitespace::SPACE);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, TabInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, Whitespace::HORIZONTAL_TAB);
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"\t\"");
}

TEST_F(IndentCancellerTest_5, TabOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Whitespace::HORIZONTAL_TAB);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, NewLineInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, Whitespace::NEW_LINE);
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"\n\"");
}

TEST_F(IndentCancellerTest_5, NewLineOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Whitespace::NEW_LINE);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, CarriageReturnInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, Whitespace::CARRIAGE_RETURN);
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"\r\"");
}

TEST_F(IndentCancellerTest_5, CarriageReturnOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Whitespace::CARRIAGE_RETURN);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, EscapeCharacterInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, Strings::Json::Escape::BEGIN_ESCAPE);
    canceller.operator()(dest, 'n');
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"\\n\"");
}

TEST_F(IndentCancellerTest_5, EscapeCharacterOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Strings::Json::Escape::BEGIN_ESCAPE);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, ToggleStringWithDoubleQuote_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, 'a');
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    canceller.operator()(dest, 'b');
    EXPECT_EQ(output.str(), "\"a\"b");
}

TEST_F(IndentCancellerTest_5, ToggleStringWithEscapedDoubleQuote_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, Strings::Json::Escape::BEGIN_ESCAPE);
    canceller.operator()(dest, Structural::BEGIN_END_STRING);
    canceller.operator()(dest, 'a');
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"\\\"a\"");
}

TEST_F(IndentCancellerTest_5, ToggleStringWithEscapedBackslash_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, Strings::Json::Escape::BEGIN_ESCAPE);
    canceller.operator()(dest, Strings::Json::Escape::BEGIN_ESCAPE);
    canceller.operator()(dest, 'a');
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"\\\\a\"");
}

TEST_F(IndentCancellerTest_5, EmptyStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"\"");
}

TEST_F(IndentCancellerTest_5, SingleCharacterStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, 'a');
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"a\"");
}

TEST_F(IndentCancellerTest_5, MultiCharacterStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Enter string
    canceller.operator()(dest, 'h');
    canceller.operator()(dest, 'e');
    canceller.operator()(dest, 'l');
    canceller.operator()(dest, 'l');
    canceller.operator()(dest, 'o');
    canceller.operator()(dest, Structural::BEGIN_END_STRING);  // Exit string
    EXPECT_EQ(output.str(), "\"hello\"");
}