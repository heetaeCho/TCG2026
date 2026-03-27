#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util.cc"  // Assuming the SpellcheckStringV function is in this file



using namespace std;



class SpellcheckStringTest_143 : public ::testing::Test {

protected:

    vector<const char*> words;

};



TEST_F(SpellcheckStringTest_143, EmptyText_ReturnsNull_143) {

    const char* result = SpellcheckStringV("", words);

    EXPECT_EQ(result, nullptr);

}



TEST_F(SpellcheckStringTest_143, NoMatchingWords_ReturnsNull_143) {

    words = {"apple", "banana", "cherry"};

    const char* result = SpellcheckStringV("xyz", words);

    EXPECT_EQ(result, nullptr);

}



TEST_F(SpellcheckStringTest_143, ExactMatch_ReturnsWord_143) {

    words = {"apple", "banana", "cherry"};

    const char* result = SpellcheckStringV("banana", words);

    EXPECT_STREQ(result, "banana");

}



TEST_F(SpellcheckStringTest_143, ClosestMatchWithinThreshold_ReturnsClosestWord_143) {

    words = {"apple", "banana", "cherry"};

    const char* result = SpellcheckStringV("bananx", words);

    EXPECT_STREQ(result, "banana");

}



TEST_F(SpellcheckStringTest_143, MultipleWordsWithinThreshold_ReturnsClosestWord_143) {

    words = {"apple", "applf", "appla"};

    const char* result = SpellcheckStringV("apple", words);

    EXPECT_STREQ(result, "apple");

}



TEST_F(SpellcheckStringTest_143, AllWordsBeyondThreshold_ReturnsNull_143) {

    words = {"abcde", "fghij", "klmno"};

    const char* result = SpellcheckStringV("xyz", words);

    EXPECT_EQ(result, nullptr);

}



TEST_F(SpellcheckStringTest_143, SingleWordExactMatch_ReturnsWord_143) {

    words = {"apple"};

    const char* result = SpellcheckStringV("apple", words);

    EXPECT_STREQ(result, "apple");

}



TEST_F(SpellcheckStringTest_143, SingleWordNoMatch_ReturnsNull_143) {

    words = {"apple"};

    const char* result = SpellcheckStringV("xyz", words);

    EXPECT_EQ(result, nullptr);

}
