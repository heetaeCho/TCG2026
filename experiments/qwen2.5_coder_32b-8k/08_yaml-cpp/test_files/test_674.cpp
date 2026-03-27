#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>



using ::testing::StrEq;



TEST(ReadStreamTest_674, NormalOperation_674) {

    std::istringstream stream("Hello, World!");

    EXPECT_EQ(read_stream(stream), "Hello, World!");

}



TEST(ReadStreamTest_674, EmptyStream_674) {

    std::istringstream stream("");

    EXPECT_EQ(read_stream(stream), "");

}



TEST(ReadStreamTest_674, SingleCharacter_674) {

    std::istringstream stream("A");

    EXPECT_EQ(read_stream(stream), "A");

}



TEST(ReadStreamTest_674, MultipleLines_674) {

    std::istringstream stream("Line 1\nLine 2\nLine 3");

    EXPECT_EQ(read_stream(stream), "Line 1\nLine 2\nLine 3");

}



TEST(ReadStreamTest_674, LargeInput_674) {

    std::string large_input(10000, 'a');

    std::istringstream stream(large_input);

    EXPECT_EQ(read_stream(stream), large_input);

}
