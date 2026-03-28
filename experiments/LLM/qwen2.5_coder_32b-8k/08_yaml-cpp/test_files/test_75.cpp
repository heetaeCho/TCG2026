#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "yaml-cpp/src/stream.h"



using namespace YAML;

using ::testing::Test;



class StreamTest_75 : public Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_75() : input(""), stream(input) {}

};



TEST_F(StreamTest_75, DefaultPositionIsZero_75) {

    EXPECT_EQ(stream.pos(), 0);

}



TEST_F(StreamTest_75, PeekOnEmptyStreamReturnsEof_75) {

    EXPECT_EQ(stream.peek(), Stream::eof());

}



TEST_F(StreamTest_75, GetOnEmptyStreamReturnsEof_75) {

    EXPECT_EQ(stream.get(), Stream::eof());

}



TEST_F(StreamTest_75, PositionDoesNotChangeOnPeek_75) {

    int initialPos = stream.pos();

    stream.peek();

    EXPECT_EQ(initialPos, stream.pos());

}



TEST_F(StreamTest_75, PositionIncrementsAfterGet_75) {

    input.str("a");

    stream.get();

    EXPECT_EQ(stream.pos(), 1);

}



TEST_F(StreamTest_75, GetMultipleCharactersUpdatesPositionCorrectly_75) {

    input.str("abc");

    stream.get(2);

    EXPECT_EQ(stream.pos(), 2);

}



TEST_F(StreamTest_75, EatDoesNotChangePositionOnEmptyStream_75) {

    int initialPos = stream.pos();

    stream.eat(10);

    EXPECT_EQ(initialPos, stream.pos());

}



TEST_F(StreamTest_75, EatReducesAvailableCharacters_75) {

    input.str("abc");

    stream.eat(2);

    EXPECT_EQ(stream.get(), 'c');

}



TEST_F(StreamTest_75, GetMultipleCharactersWithBoundaryConditions_75) {

    input.str("a");

    EXPECT_EQ(stream.get(10), "a");

    EXPECT_EQ(stream.pos(), 1);

    EXPECT_EQ(stream.get(), Stream::eof());

}



TEST_F(StreamTest_75, PeekReturnsFirstCharacterWithoutConsumingIt_75) {

    input.str("abc");

    EXPECT_EQ(stream.peek(), 'a');

    EXPECT_EQ(stream.get(), 'a');

}



TEST_F(StreamTest_75, GetWithZeroLengthDoesNothing_75) {

    input.str("abc");

    stream.get(0);

    EXPECT_EQ(stream.pos(), 0);

}
