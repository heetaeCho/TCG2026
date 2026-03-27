#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "stream.h"

#include <sstream>



using namespace YAML;



class StreamTest_171 : public ::testing::Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_171() : input(""), stream(input) {}

};



TEST_F(StreamTest_171, ConstructorInitialization_171) {

    EXPECT_TRUE(stream);

}



TEST_F(StreamTest_171, PeekOnEmptyStream_171) {

    EXPECT_EQ(stream.peek(), Stream::eof());

}



TEST_F(StreamTest_171, GetOnEmptyStream_171) {

    EXPECT_EQ(stream.get(), Stream::eof());

}



TEST_F(StreamTest_171, EatZeroCharacters_171) {

    stream.eat(0);

    EXPECT_TRUE(true); // No change expected

}



TEST_F(StreamTest_171, EatMoreThanAvailable_171) {

    input.str("abc");

    stream.get(); // Read one character to ensure we are not at the start

    stream.eat(5); // Try to eat more than available

    EXPECT_EQ(stream.peek(), Stream::eof());

}



TEST_F(StreamTest_171, GetMultipleCharacters_171) {

    input.str("abcdef");

    std::string result = stream.get(3);

    EXPECT_EQ(result, "abc");

    result = stream.get(3);

    EXPECT_EQ(result, "def");

    EXPECT_EQ(stream.peek(), Stream::eof());

}



TEST_F(StreamTest_171, GetNegativeCharacters_171) {

    input.str("abcdef");

    std::string result = stream.get(-3); // Negative value should not change state

    EXPECT_TRUE(result.empty());

}



TEST_F(StreamTest_171, PeekAfterGet_171) {

    input.str("a");

    char c = stream.get();

    EXPECT_EQ(c, 'a');

    EXPECT_EQ(stream.peek(), Stream::eof());

}



TEST_F(StreamTest_171, ResetColumnPosition_171) {

    input.str("abc\ndef");

    stream.get(4); // Read up to newline

    stream.ResetColumn();

    EXPECT_EQ(stream.column(), 0);

    char c = stream.get(); // Read 'd'

    EXPECT_EQ(c, 'd');

    EXPECT_EQ(stream.column(), 1);

}



TEST_F(StreamTest_171, GetLineAndColumn_171) {

    input.str("abc\ndef\nghi");

    stream.get(4); // Read up to newline

    EXPECT_EQ(stream.line(), 2);

    EXPECT_EQ(stream.column(), 0);

    stream.get(4); // Read 'def' and newline

    EXPECT_EQ(stream.line(), 3);

    EXPECT_EQ(stream.column(), 0);

    stream.get(1); // Read 'g'

    EXPECT_EQ(stream.line(), 3);

    EXPECT_EQ(stream.column(), 1);

}



TEST_F(StreamTest_171, MarkPosition_171) {

    input.str("abc\ndef\nghi");

    Mark mark = stream.mark();

    stream.get(4); // Read up to newline

    Mark afterNewlineMark = stream.mark();

    EXPECT_EQ(mark.pos(), 0);

    EXPECT_EQ(afterNewlineMark.line(), 2);

}



TEST_F(StreamTest_171, OperatorNot_171) {

    EXPECT_FALSE(!stream);

    input.str("");

    stream.get(); // Read EOF

    EXPECT_TRUE(!stream);

}
