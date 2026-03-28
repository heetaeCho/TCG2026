#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "stream.h"

#include <sstream>



using namespace YAML;



class StreamTest_73 : public ::testing::Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_73() : input(""), stream(input) {}

};



TEST_F(StreamTest_73, EofReturnsCorrectValue_73) {

    EXPECT_EQ('\x04', Stream::eof());

}



TEST_F(StreamTest_73, PeekOnEmptyStreamReturnsEof_73) {

    EXPECT_EQ(Stream::eof(), stream.peek());

}



TEST_F(StreamTest_73, GetOnEmptyStreamReturnsEof_73) {

    EXPECT_EQ(Stream::eof(), stream.get());

}



TEST_F(StreamTest_73, EatZeroCharactersDoesNothing_73) {

    input.str("abc");

    stream.eat(0);

    EXPECT_EQ('a', stream.peek());

}



TEST_F(StreamTest_73, EatMoreCharactersThanAvailableReturnsEof_73) {

    input.str("ab");

    stream.eat(5);

    EXPECT_EQ(Stream::eof(), stream.get());

}



TEST_F(StreamTest_73, GetSingleCharacterFromStream_73) {

    input.str("a");

    EXPECT_EQ('a', stream.get());

}



TEST_F(StreamTest_73, PeekMultipleTimesReturnsSameCharacter_73) {

    input.str("b");

    EXPECT_EQ('b', stream.peek());

    EXPECT_EQ('b', stream.peek());

}



TEST_F(StreamTest_73, GetMultipleCharactersFromStream_73) {

    input.str("abc");

    std::string result = stream.get(3);

    EXPECT_EQ("abc", result);

}



TEST_F(StreamTest_73, EatSpecificNumberOfCharacters_73) {

    input.str("abcdef");

    stream.eat(2);

    EXPECT_EQ('c', stream.peek());

}



TEST_F(StreamTest_73, GetWithNegativeNumberReturnsEmptyString_73) {

    input.str("xyz");

    std::string result = stream.get(-1);

    EXPECT_TRUE(result.empty());

}



TEST_F(StreamTest_73, StreamBoolOperatorOnNonEmptyStream_73) {

    input.str("nonempty");

    EXPECT_TRUE(static_cast<bool>(stream));

}



TEST_F(StreamTest_73, StreamBoolOperatorOnEmptyStreamAfterEat_73) {

    input.str("a");

    stream.eat(1);

    EXPECT_FALSE(static_cast<bool>(stream));

}
