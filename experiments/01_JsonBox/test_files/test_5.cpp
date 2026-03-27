#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "JsonBox/IndentCanceller.h"

#include "JsonBox/Grammar.h"



using namespace JsonBox;

using ::testing::_;

using ::testing::Return;



class IndentCancellerTest_5 : public ::testing::Test {

protected:

    std::ostringstream output;

    std::streambuf* originalBuffer;

    IndentCanceller canceller;



    void SetUp() override {

        originalBuffer = output.rdbuf();

    }



    void TearDown() override {

        output.rdbuf(originalBuffer);

    }

};



TEST_F(IndentCancellerTest_5, NormalCharacterPassesThrough_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, 'a');

    EXPECT_EQ(output.str(), "a");

}



TEST_F(IndentCancellerTest_5, SpaceInStringPassesThrough_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '"');  // Enter string

    canceller(dest, ' ');

    canceller(dest, '"');  // Exit string

    EXPECT_EQ(output.str(), "\" \"");

}



TEST_F(IndentCancellerTest_5, SpaceOutsideStringSkipped_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, ' ');

    EXPECT_EQ(output.str(), "");

}



TEST_F(IndentCancellerTest_5, TabInStringPassesThrough_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '"');  // Enter string

    canceller(dest, '\t');

    canceller(dest, '"');  // Exit string

    EXPECT_EQ(output.str(), "\"\t\"");

}



TEST_F(IndentCancellerTest_5, TabOutsideStringSkipped_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '\t');

    EXPECT_EQ(output.str(), "");

}



TEST_F(IndentCancellerTest_5, NewLineInStringPassesThrough_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '"');  // Enter string

    canceller(dest, '\n');

    canceller(dest, '"');  // Exit string

    EXPECT_EQ(output.str(), "\"\n\"");

}



TEST_F(IndentCancellerTest_5, NewLineOutsideStringSkipped_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '\n');

    EXPECT_EQ(output.str(), "");

}



TEST_F(IndentCancellerTest_5, CarriageReturnInStringPassesThrough_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '"');  // Enter string

    canceller(dest, '\r');

    canceller(dest, '"');  // Exit string

    EXPECT_EQ(output.str(), "\"\r\"");

}



TEST_F(IndentCancellerTest_5, CarriageReturnOutsideStringSkipped_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '\r');

    EXPECT_EQ(output.str(), "");

}



TEST_F(IndentCancellerTest_5, EscapeCharacterInStringPassesThrough_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '"');  // Enter string

    canceller(dest, '\\');

    canceller(dest, 'n');

    canceller(dest, '"');  // Exit string

    EXPECT_EQ(output.str(), "\"\\n\"");

}



TEST_F(IndentCancellerTest_5, EscapeCharacterOutsideStringSkipped_5) {

    std::streambuf& dest = *output.rdbuf();

    canceller(dest, '\\');

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
