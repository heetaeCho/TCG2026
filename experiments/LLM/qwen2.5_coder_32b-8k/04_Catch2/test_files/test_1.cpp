#include <gtest/gtest.h>

#include "catch2/internal/catch_reusable_string_stream.hpp"



class ReusableStringStreamTest_1 : public ::testing::Test {

protected:

    Catch::ReusableStringStream rss;

};



TEST_F(ReusableStringStreamTest_1, InitializationDoesNotThrow_1) {

    EXPECT_NO_THROW(Catch::ReusableStringStream());

}



TEST_F(ReusableStringStreamTest_1, PutIncreasesCount_1) {

    const int initialSize = rss.str().size();

    rss << "test";

    const int newSize = rss.str().size();

    EXPECT_GT(newSize, initialSize);

}



TEST_F(ReusableStringStreamTest_1, OutputCorrectAfterPut_1) {

    rss << "Hello" << " " << "World";

    EXPECT_EQ(rss.str(), "Hello World");

}



TEST_F(ReusableStringStreamTest_1, SetAndGetConsistent_1) {

    const std::string testStr = "Sample text";

    rss.str(testStr);

    EXPECT_EQ(rss.str(), testStr);

}



TEST_F(ReusableStringStreamTest_1, ResetStringToEmpty_1) {

    rss << "Some data";

    rss.str("");

    EXPECT_TRUE(rss.str().empty());

}



TEST_F(ReusableStringStreamTest_1, SetStringWithOperator_1) {

    const std::string testStr = "Another sample text";

    rss << testStr;

    EXPECT_EQ(rss.str(), testStr);

}



TEST_F(ReusableStringStreamTest_1, HandleMultipleTypes_1) {

    int num = 42;

    double pi = 3.14;

    rss << "Number: " << num << ", Pi: " << pi;

    EXPECT_EQ(rss.str(), "Number: 42, Pi: 3.14");

}



TEST_F(ReusableStringStreamTest_1, BoundaryConditionEmptyInput_1) {

    rss << "";

    EXPECT_TRUE(rss.str().empty());

}
