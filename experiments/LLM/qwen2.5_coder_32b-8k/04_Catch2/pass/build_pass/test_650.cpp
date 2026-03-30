#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reusable_string_stream.hpp"



using namespace Catch;



class ReusableStringStreamTest_650 : public ::testing::Test {

protected:

    ReusableStringStream stream;

};



TEST_F(ReusableStringStreamTest_650, SetAndGetString_650) {

    std::string input = "Hello, World!";

    stream.str(input);

    EXPECT_EQ(stream.str(), input);

}



TEST_F(ReusableStringStreamTest_650, EmptyString_650) {

    std::string empty = "";

    stream.str(empty);

    EXPECT_EQ(stream.str(), empty);

}



TEST_F(ReusableStringStreamTest_650, OverwriteString_650) {

    std::string first = "First";

    std::string second = "Second";

    stream.str(first);

    stream.str(second);

    EXPECT_EQ(stream.str(), second);

}



TEST_F(ReusableStringStreamTest_650, LargeString_650) {

    std::string large = std::string(1024, 'a');

    stream.str(large);

    EXPECT_EQ(stream.str(), large);

}
