#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/stream.h"

#include <sstream>



using namespace YAML;

using ::testing::Eq;



class StreamTest_76 : public ::testing::Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_76() : input(""), stream(input) {}

};



TEST_F(StreamTest_76, LineInitiallyZero_76) {

    EXPECT_EQ(stream.line(), 0);

}



TEST_F(StreamTest_76, PosInitiallyZero_76) {

    EXPECT_EQ(stream.pos(), 0);

}



TEST_F(StreamTest_76, ColumnInitiallyZero_76) {

    EXPECT_EQ(stream.column(), 0);

}



TEST_F(StreamTest_76, GetIncreasesPosAndLine_76) {

    input.str("Hello\nWorld");

    stream.get(); // 'H'

    EXPECT_EQ(stream.pos(), 1);

    EXPECT_EQ(stream.line(), 0);



    stream.get(); // 'e'

    EXPECT_EQ(stream.pos(), 2);

    EXPECT_EQ(stream.line(), 0);



    stream.get(); // 'l'

    EXPECT_EQ(stream.pos(), 3);

    EXPECT_EQ(stream.line(), 0);



    stream.get(); // 'l'

    EXPECT_EQ(stream.pos(), 4);

    EXPECT_EQ(stream.line(), 0);



    stream.get(); // 'o'

    EXPECT_EQ(stream.pos(), 5);

    EXPECT_EQ(stream.line(), 0);



    stream.get(); // '\n'

    EXPECT_EQ(stream.pos(), 6);

    EXPECT_EQ(stream.line(), 1);



    stream.get(); // 'W'

    EXPECT_EQ(stream.pos(), 7);

    EXPECT_EQ(stream.line(), 1);

}



TEST_F(StreamTest_76, PeekDoesNotChangePosOrLine_76) {

    input.str("Hello");

    stream.peek();

    EXPECT_EQ(stream.pos(), 0);

    EXPECT_EQ(stream.line(), 0);

}



TEST_F(StreamTest_76, EatIncreasesPosAndLine_76) {

    input.str("Hello\nWorld");

    stream.eat(5); // "Hello"

    EXPECT_EQ(stream.pos(), 5);

    EXPECT_EQ(stream.line(), 0);



    stream.eat(1); // "\n"

    EXPECT_EQ(stream.pos(), 6);

    EXPECT_EQ(stream.line(), 1);

}



TEST_F(StreamTest_76, ResetColumnResetsColumn_76) {

    input.str("Hello\nWorld");

    stream.get(); // 'H'

    stream.get(); // 'e'

    stream.ResetColumn();

    EXPECT_EQ(stream.column(), 0);



    stream.eat(3); // "llo"

    EXPECT_EQ(stream.column(), 3);

}



TEST_F(StreamTest_76, GetWithNegativeNThrowsInvalidArgument_76) {

    EXPECT_THROW(stream.get(-1), std::invalid_argument);

}



TEST_F(StreamTest_76, EatWithNegativeNThrowsInvalidArgument_76) {

    EXPECT_THROW(stream.eat(-1), std::invalid_argument);

}



TEST_F(StreamTest_76, GetAtEofReturnsEmptyString_76) {

    input.str("");

    EXPECT_EQ(stream.get(5), "");

}



TEST_F(StreamTest_76, EatAtEofDoesNothing_76) {

    input.str("");

    stream.eat(5);

    EXPECT_TRUE(true); // No exception or change in state expected

}
