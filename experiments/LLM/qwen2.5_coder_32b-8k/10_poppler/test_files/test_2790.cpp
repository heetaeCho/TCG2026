#include <gtest/gtest.h>

#include "GfxFont.cc"  // Adjust the path as necessary



class FNVHashTest_2790 : public ::testing::Test {

protected:

    FNVHash hash;

};



TEST_F(FNVHashTest_2790, InitialHashValue_2790) {

    EXPECT_EQ(hash.get31(), 2166136261U & 0x7FFFFFFF);

}



TEST_F(FNVHashTest_2790, HashSingleChar_2790) {

    hash.hash('a');

    // FNV-1a hash for 'a' starting from 2166136261

    unsigned int expected = (2166136261U ^ static_cast<unsigned char>('a')) * 16777619U;

    EXPECT_EQ(hash.get31(), expected & 0x7FFFFFFF);

}



TEST_F(FNVHashTest_2790, HashString_2790) {

    hash.hash("abc", 3);

    // FNV-1a hash for "abc" starting from 2166136261

    unsigned int h = 2166136261U;

    h = (h ^ static_cast<unsigned char>('a')) * 16777619U;

    h = (h ^ static_cast<unsigned char>('b')) * 16777619U;

    h = (h ^ static_cast<unsigned char>('c')) * 16777619U;

    EXPECT_EQ(hash.get31(), h & 0x7FFFFFFF);

}



TEST_F(FNVHashTest_2790, HashEmptyString_2790) {

    hash.hash("", 0);

    EXPECT_EQ(hash.get31(), 2166136261U & 0x7FFFFFFF);

}



TEST_F(FNVHashTest_2790, HashMultipleChars_2790) {

    hash.hash("abc");

    hash.hash("def");

    // FNV-1a hash for "abcdef" starting from 2166136261

    unsigned int h = 2166136261U;

    for (char c : "abcdef") {

        h = (h ^ static_cast<unsigned char>(c)) * 16777619U;

    }

    EXPECT_EQ(hash.get31(), h & 0x7FFFFFFF);

}



TEST_F(FNVHashTest_2790, HashLargeValue_2790) {

    hash.hash("a");

    hash.hash("b");

    hash.hash("c");

    // FNV-1a hash for "abc" starting from 2166136261

    unsigned int h = 2166136261U;

    h = (h ^ static_cast<unsigned char>('a')) * 16777619U;

    h = (h ^ static_cast<unsigned char>('b')) * 16777619U;

    h = (h ^ static_cast<unsigned char>('c')) * 16777619U;

    EXPECT_EQ(hash.get31(), h & 0x7FFFFFFF);

}
