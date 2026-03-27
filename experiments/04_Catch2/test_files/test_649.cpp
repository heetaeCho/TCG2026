#include <gtest/gtest.h>

#include "catch2/internal/catch_reusable_string_stream.hpp"



using namespace Catch;



class ReusableStringStreamTest_649 : public ::testing::Test {

protected:

    ReusableStringStream rss;

};



TEST_F(ReusableStringStreamTest_649, InitialStringIsEmpty_649) {

    EXPECT_EQ(rss.str(), "");

}



TEST_F(ReusableStringStreamTest_649, SetStringAndGetSame_649) {

    std::string testString = "Hello, World!";

    rss.str(testString);

    EXPECT_EQ(rss.str(), testString);

}



TEST_F(ReusableStringStreamTest_649, StreamOperatorSetsCorrectly_649) {

    int number = 123;

    rss << number;

    EXPECT_EQ(rss.str(), "123");

}



TEST_F(ReusableStringStreamTest_649, StreamMultipleTypes_649) {

    std::string text = "The answer is ";

    int number = 42;

    rss << text << number;

    EXPECT_EQ(rss.str(), "The answer is 42");

}



TEST_F(ReusableStringStreamTest_649, ClearStringBySettingEmpty_649) {

    rss.str("Non-empty string");

    rss.str("");

    EXPECT_EQ(rss.str(), "");

}
