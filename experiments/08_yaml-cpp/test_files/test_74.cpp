#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "stream.h"



using namespace YAML;



class StreamTest_74 : public ::testing::Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_74() : input(""), stream(input) {}

};



TEST_F(StreamTest_74, DefaultConstructorInitializesMark_74) {

    Mark mark = stream.mark();

    EXPECT_EQ(mark.index, 0);

    EXPECT_EQ(mark.line, 1);

    EXPECT_EQ(mark.column, 1);

}



TEST_F(StreamTest_74, StreamWithEmptyInput_ReturnsEofOnGet_74) {

    EXPECT_EQ(stream.get(), Stream::eof());

}



TEST_F(StreamTest_74, StreamWithEmptyInput_PeekReturnsEof_74) {

    EXPECT_EQ(stream.peek(), Stream::eof());

}



TEST_F(StreamTest_74, StreamWithNonEmptyInput_ReturnsCorrectCharacters_74) {

    input.str("hello");

    EXPECT_EQ(stream.get(), 'h');

    EXPECT_EQ(stream.get(), 'e');

    EXPECT_EQ(stream.get(), 'l');

    EXPECT_EQ(stream.get(), 'l');

    EXPECT_EQ(stream.get(), 'o');

    EXPECT_EQ(stream.get(), Stream::eof());

}



TEST_F(StreamTest_74, StreamWithNonEmptyInput_PeekDoesNotAdvancePosition_74) {

    input.str("hello");

    EXPECT_EQ(stream.peek(), 'h');

    EXPECT_EQ(stream.peek(), 'h');

    EXPECT_EQ(stream.get(), 'h');

}



TEST_F(StreamTest_74, EatAdvancesStreamByNCharacters_74) {

    input.str("hello");

    stream.eat(3);

    EXPECT_EQ(stream.get(), 'l');

    EXPECT_EQ(stream.get(), 'o');

    EXPECT_EQ(stream.get(), Stream::eof());

}



TEST_F(StreamTest_74, EatWithNegativeValueDoesNothing_74) {

    input.str("hello");

    stream.eat(-1);

    EXPECT_EQ(stream.get(), 'h');

    EXPECT_EQ(stream.peek(), 'e');

}



TEST_F(StreamTest_74, GetNCharactersReturnsSubstring_74) {

    input.str("hello world");

    std::string result = stream.get(5);

    EXPECT_EQ(result, "hello");

    EXPECT_EQ(stream.peek(), ' ');

}



TEST_F(StreamTest_74, GetNCharactersWithNegativeNReturnsEmptyString_74) {

    input.str("hello");

    std::string result = stream.get(-1);

    EXPECT_EQ(result, "");

    EXPECT_EQ(stream.peek(), 'h');

}



TEST_F(StreamTest_74, PositionAndLineColumnTrackCorrectly_74) {

    input.str("hel\nlo world");

    EXPECT_EQ(stream.pos(), 0);

    EXPECT_EQ(stream.line(), 1);

    EXPECT_EQ(stream.column(), 1);



    stream.get(); // h

    EXPECT_EQ(stream.pos(), 1);

    EXPECT_EQ(stream.line(), 1);

    EXPECT_EQ(stream.column(), 2);



    stream.get(); // e

    EXPECT_EQ(stream.pos(), 2);

    EXPECT_EQ(stream.line(), 1);

    EXPECT_EQ(stream.column(), 3);



    stream.get(); // l

    EXPECT_EQ(stream.pos(), 3);

    EXPECT_EQ(stream.line(), 1);

    EXPECT_EQ(stream.column(), 4);



    stream.get(); // \n

    EXPECT_EQ(stream.pos(), 4);

    EXPECT_EQ(stream.line(), 2);

    EXPECT_EQ(stream.column(), 1);



    stream.get(); // l

    EXPECT_EQ(stream.pos(), 5);

    EXPECT_EQ(stream.line(), 2);

    EXPECT_EQ(stream.column(), 2);



    stream.ResetColumn();

    EXPECT_EQ(stream.pos(), 5);

    EXPECT_EQ(stream.line(), 2);

    EXPECT_EQ(stream.column(), 1);

}



TEST_F(StreamTest_74, BoolOperatorReturnsTrueForNonEmptyStream_74) {

    input.str("hello");

    EXPECT_TRUE(static_cast<bool>(stream));

}



TEST_F(StreamTest_74, BoolOperatorReturnsFalseForEmptyStream_74) {

    EXPECT_FALSE(static_cast<bool>(stream));

}



TEST_F(StreamTest_74, NegationOperatorReturnsFalseForNonEmptyStream_74) {

    input.str("hello");

    EXPECT_FALSE(!stream);

}



TEST_F(StreamTest_74, NegationOperatorReturnsTrueForEmptyStream_74) {

    EXPECT_TRUE(!stream);

}
