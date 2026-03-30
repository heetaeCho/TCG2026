#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "./TestProjects/yaml-cpp/src/stream.h"



namespace YAML {

    class StreamTest_173 : public ::testing::Test {

    protected:

        std::istringstream input;

        Stream stream;



        StreamTest_173() : input(""), stream(input) {}

    };



    TEST_F(StreamTest_173, PeekEmptyStream_ReturnsEof_173) {

        EXPECT_EQ(stream.peek(), Stream::eof());

    }



    TEST_F(StreamTest_173, PeekSingleCharacter_ReturnsCharacter_173) {

        input.str("a");

        EXPECT_EQ(stream.peek(), 'a');

        EXPECT_EQ(stream.peek(), 'a'); // Ensure peek does not consume the character

    }



    TEST_F(StreamTest_173, PeekMultipleCharacters_ReturnsFirstCharacter_173) {

        input.str("abc");

        EXPECT_EQ(stream.peek(), 'a');

        EXPECT_EQ(stream.peek(), 'a'); // Ensure peek does not consume the character

    }

}
