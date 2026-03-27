#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "stream.h"



namespace YAML {



class StreamTest_177 : public ::testing::Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_177() : input(""), stream(input) {}

};



TEST_F(StreamTest_177, EatZeroCharacters_177) {

    // Test eating zero characters

    stream.eat(0);

    EXPECT_EQ(stream.peek(), '\0'); // Assuming peek returns null if no more characters

}



TEST_F(StreamTest_177, EatOneCharacter_177) {

    // Test eating one character

    input.str("a");

    stream.eat(1);

    EXPECT_EQ(stream.peek(), '\0'); // Assuming peek returns null if no more characters

}



TEST_F(StreamTest_177, EatMultipleCharacters_177) {

    // Test eating multiple characters

    input.str("abc");

    stream.eat(2);

    EXPECT_EQ(stream.get(), 'c');

}



TEST_F(StreamTest_177, EatMoreThanAvailable_177) {

    // Test eating more characters than available in the stream

    input.str("ab");

    stream.eat(5);

    EXPECT_EQ(stream.peek(), '\0'); // Assuming peek returns null if no more characters

}



TEST_F(StreamTest_177, EatBoundaryCondition_177) {

    // Test eating up to the boundary condition (empty string)

    input.str("");

    stream.eat(0);

    EXPECT_EQ(stream.peek(), '\0'); // Assuming peek returns null if no more characters

}



TEST_F(StreamTest_177, EatNegativeCharacters_177) {

    // Test eating a negative number of characters (should have no effect)

    input.str("abc");

    stream.eat(-1);

    EXPECT_EQ(stream.get(), 'a');

}



} // namespace YAML
