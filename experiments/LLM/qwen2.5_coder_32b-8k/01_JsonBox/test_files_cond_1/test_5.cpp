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
        output.str("");  // Clear the output stream for each test
    }
};

TEST_F(IndentCancellerTest_5, NormalCharacterPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    EXPECT_EQ(canceller(dest, 'a'), 'a');
    EXPECT_EQ(output.str(), "a");
}

TEST_F(IndentCancellerTest_5, SpaceInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    EXPECT_EQ(canceller(dest, ' '), ' ');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\" \"");
}

TEST_F(IndentCancellerTest_5, SpaceOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    EXPECT_EQ(canceller(dest, ' '), 0);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, TabInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    EXPECT_EQ(canceller(dest, '\t'), '\t');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"\t\"");
}

TEST_F(IndentCancellerTest_5, TabOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    EXPECT_EQ(canceller(dest, '\t'), 0);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, NewLineInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    EXPECT_EQ(canceller(dest, '\n'), '\n');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"\n\"");
}

TEST_F(IndentCancellerTest_5, NewLineOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    EXPECT_EQ(canceller(dest, '\n'), 0);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, CarriageReturnInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    EXPECT_EQ(canceller(dest, '\r'), '\r');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"\r\"");
}

TEST_F(IndentCancellerTest_5, CarriageReturnOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    EXPECT_EQ(canceller(dest, '\r'), 0);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, EscapeCharacterInStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    EXPECT_EQ(canceller(dest, '\\'), '\\');
    canceller(dest, 'n');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"\\n\"");
}

TEST_F(IndentCancellerTest_5, EscapeCharacterOutsideStringSkipped_5) {
    std::streambuf& dest = *output.rdbuf();
    EXPECT_EQ(canceller(dest, '\\'), 0);
    EXPECT_EQ(output.str(), "");
}

TEST_F(IndentCancellerTest_5, ToggleStringWithDoubleQuote_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    canceller(dest, 'a');
    canceller(dest, '"');  // Exit string
    canceller(dest, 'b');
    EXPECT_EQ(output.str(), "\"a\"b");
}

TEST_F(IndentCancellerTest_5, ToggleStringWithEscapedDoubleQuote_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    canceller(dest, '\\');
    canceller(dest, '"');
    canceller(dest, 'a');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"\\\"a\"");
}

TEST_F(IndentCancellerTest_5, ToggleStringWithEscapedBackslash_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    canceller(dest, '\\');
    canceller(dest, '\\');
    canceller(dest, 'a');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"\\\\a\"");
}

TEST_F(IndentCancellerTest_5, EmptyStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"\"");
}

TEST_F(IndentCancellerTest_5, SingleCharacterStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    canceller(dest, 'a');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"a\"");
}

TEST_F(IndentCancellerTest_5, MultiCharacterStringPassesThrough_5) {
    std::streambuf& dest = *output.rdbuf();
    canceller(dest, '"');  // Enter string
    canceller(dest, 'h');
    canceller(dest, 'e');
    canceller(dest, 'l');
    canceller(dest, 'l');
    canceller(dest, 'o');
    canceller(dest, '"');  // Exit string
    EXPECT_EQ(output.str(), "\"hello\"");
}