#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "stream.h"

#include <sstream>



using namespace YAML;

using ::testing::Test;



class StreamTest_176 : public Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_176() : input(""), stream(input) {}

};



TEST_F(StreamTest_176, GetZeroCharacters_176) {

    EXPECT_EQ(stream.get(0), "");

}



TEST_F(StreamTest_176, GetOneCharacter_176) {

    input.str("A");

    EXPECT_EQ(stream.get(1), "A");

}



TEST_F(StreamTest_176, GetMultipleCharacters_176) {

    input.str("Hello");

    EXPECT_EQ(stream.get(3), "Hel");

}



TEST_F(StreamTest_176, GetMoreCharactersThanAvailable_176) {

    input.str("Hi");

    EXPECT_EQ(stream.get(5), "Hi");

}



TEST_F(StreamTest_176, GetNegativeNumber_176) {

    input.str("Hello");

    EXPECT_EQ(stream.get(-3), "");

}



TEST_F(StreamTest_176, GetUntilEndOfStream_176) {

    input.str("World");

    EXPECT_EQ(stream.get(5), "World");

}



TEST_F(StreamTest_176, GetEmptyString_176) {

    input.str("");

    EXPECT_EQ(stream.get(10), "");

}
