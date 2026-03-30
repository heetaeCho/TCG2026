#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/yaml-cpp/src/stream.h"



using namespace YAML;

using testing::Test;



class StreamTest_72 : public Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_72() : input(""), stream(input) {}

};



TEST_F(StreamTest_72, OperatorBool_ReturnsTrueForNonEmptyStream_72) {

    input.str("test");

    EXPECT_TRUE(static_cast<bool>(stream));

}



TEST_F(StreamTest_72, OperatorBool_ReturnsFalseForEmptyStream_72) {

    EXPECT_FALSE(static_cast<bool>(stream));

}



TEST_F(StreamTest_72, OperatorNot_ReturnsTrueForEmptyStream_72) {

    EXPECT_TRUE(!stream);

}



TEST_F(StreamTest_72, OperatorNot_ReturnsFalseForNonEmptyStream_72) {

    input.str("test");

    EXPECT_FALSE(!stream);

}



TEST_F(StreamTest_72, Peek_ReturnsFirstCharacterWithoutAdvancing_72) {

    input.str("abc");

    EXPECT_EQ('a', stream.peek());

    EXPECT_EQ('a', stream.peek()); // Ensure no advancement

}



TEST_F(StreamTest_72, Get_ReturnsNextCharacterAndAdvances_72) {

    input.str("abc");

    EXPECT_EQ('a', stream.get());

    EXPECT_EQ('b', stream.get());

}



TEST_F(StreamTest_72, GetN_ReturnsSpecifiedNumberOfCharacters_72) {

    input.str("abcdef");

    EXPECT_EQ("abc", stream.get(3));

}



TEST_F(StreamTest_72, Eat_AdvancesBySpecifiedNumberOfCharacters_72) {

    input.str("abcdef");

    stream.eat(3);

    EXPECT_EQ('d', stream.get());

}



TEST_F(StreamTest_72, Get_ReturnsEofForEmptyStream_72) {

    EXPECT_EQ(Stream::eof(), stream.get());

}



TEST_F(StreamTest_72, GetN_ReturnsPartialStringIfEndOfStreamReached_72) {

    input.str("ab");

    EXPECT_EQ("ab", stream.get(5));

}
