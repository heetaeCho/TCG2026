#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "stream.h"



using namespace YAML;

using testing::Test;



class StreamTest_172 : public Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_172() : input(""), stream(input) {}



    void SetUp() override {

        input.clear();

        input.str("");

    }

};



TEST_F(StreamTest_172, DefaultConstructorAndGet_172) {

    input.str("Hello");

    ASSERT_EQ('H', stream.get());

    ASSERT_EQ('e', stream.get());

}



TEST_F(StreamTest_172, PeekAndEat_172) {

    input.str("World");

    EXPECT_EQ('W', stream.peek());

    EXPECT_EQ('W', stream.peek()); // peek does not consume

    stream.eat(1);

    EXPECT_EQ('o', stream.peek());

}



TEST_F(StreamTest_172, GetMultipleCharacters_172) {

    input.str("YAML");

    EXPECT_EQ("YAM", stream.get(3));

    EXPECT_EQ('L', stream.get());

}



TEST_F(StreamTest_172, EatBoundaryCondition_172) {

    input.str("Test");

    stream.eat(4);

    EXPECT_EQ('\0', stream.peek()); // End of string

}



TEST_F(StreamTest_172, EatMoreThanAvailable_172) {

    input.str("Foo");

    stream.eat(5); // Eating more than available

    EXPECT_EQ('\0', stream.peek()); // Should be at end

}



TEST_F(StreamTest_172, GetEmptyString_172) {

    input.clear();

    input.str("");

    EXPECT_EQ("", stream.get(3));

}



TEST_F(StreamTest_172, OperatorBoolTrue_172) {

    input.str("Data");

    EXPECT_TRUE(stream.operator bool());

}



TEST_F(StreamTest_172, OperatorBoolFalse_172) {

    input.clear();

    input.setstate(std::ios_base::eofbit);

    EXPECT_FALSE(stream.operator bool());

}



TEST_F(StreamTest_172, MarkAndPosition_172) {

    input.str("Sample");

    stream.get(3); // Move to position 3

    EXPECT_EQ(3, stream.pos());

    stream.eat(2); // Move to position 5

    EXPECT_EQ(5, stream.pos());

}



TEST_F(StreamTest_172, LineAndColumn_172) {

    input.str("Line\nOne\nTwo");

    stream.get(4); // "Line"

    EXPECT_EQ(0, stream.column()); // At start of next line

    EXPECT_EQ(1, stream.line());



    stream.get(3); // "\nOne"

    EXPECT_EQ(2, stream.line());

    EXPECT_EQ(0, stream.column());



    stream.eat(4); // "One\n"

    EXPECT_EQ(2, stream.column()); // At start of next line

    EXPECT_EQ(2, stream.line());



    stream.get(3); // "\nTwo"

    EXPECT_EQ(2, stream.line());

    EXPECT_EQ(0, stream.column());

}



TEST_F(StreamTest_172, ResetColumn_172) {

    input.str("Line\nOne");

    stream.get(5); // "Line\n"

    EXPECT_EQ(0, stream.column()); // Reset to start of line



    stream.eat(3); // "One"

    EXPECT_EQ(3, stream.column());



    stream.ResetColumn();

    EXPECT_EQ(0, stream.column());

}



TEST_F(StreamTest_172, EofCharacter_172) {

    input.clear();

    input.setstate(std::ios_base::eofbit);

    EXPECT_EQ('\0', stream.get());

}
