#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/http.cpp"



using namespace Exiv2;



class StringToDictTest_1351 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(StringToDictTest_1351, NormalOperation_1351) {

    std::string input = "key1,key2,key3";

    Dictionary expected = {{"key1", "key1"}, {"key2", "key2"}, {"key3", "key3"}};

    EXPECT_EQ(stringToDict(input), expected);

}



TEST_F(StringToDictTest_1351, SingleKey_1351) {

    std::string input = "single";

    Dictionary expected = {{"single", "single"}};

    EXPECT_EQ(stringToDict(input), expected);

}



TEST_F(StringToDictTest_1351, EmptyString_1351) {

    std::string input = "";

    Dictionary expected = {};

    EXPECT_EQ(stringToDict(input), expected);

}



TEST_F(StringToDictTest_1351, TrailingComma_1351) {

    std::string input = "key1,key2,";

    Dictionary expected = {{"key1", "key1"}, {"key2", "key2"}};

    EXPECT_EQ(stringToDict(input), expected);

}



TEST_F(StringToDictTest_1351, LeadingComma_1351) {

    std::string input = ",key1,key2";

    Dictionary expected = {{"", ""}, {"key1", "key1"}, {"key2", "key2"}};

    EXPECT_EQ(stringToDict(input), expected);

}



TEST_F(StringToDictTest_1351, MultipleSpacesBetweenKeys_1351) {

    std::string input = "key1  , key2,key3";

    Dictionary expected = {{"key1", "key1"}, {"key2", "key2"}, {"key3", "key3"}};

    EXPECT_EQ(stringToDict(input), expected);

}



TEST_F(StringToDictTest_1351, NoCommas_1351) {

    std::string input = "key1 key2 key3";

    Dictionary expected = {{"key1key2key3", "key1key2key3"}};

    EXPECT_EQ(stringToDict(input), expected);

}
