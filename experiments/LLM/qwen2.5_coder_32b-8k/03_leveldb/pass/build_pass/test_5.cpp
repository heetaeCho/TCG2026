#include <gtest/gtest.h>

#include "leveldb/slice.h"



using namespace leveldb;



// Test fixture for Slice tests with TEST_ID 5

class SliceTest_5 : public ::testing::Test {

protected:

    Slice emptySlice;

    Slice sampleSlice;

    Slice anotherSampleSlice;



    SliceTest_5()

        : emptySlice(),

          sampleSlice("hello"),

          anotherSampleSlice("world") {}

};



// Test normal operation of data() and size()

TEST_F(SliceTest_5, DataAndSize_ReturnCorrectValues_5) {

    EXPECT_STREQ(sampleSlice.data(), "hello");

    EXPECT_EQ(sampleSlice.size(), 5);

}



// Test boundary condition for empty slice

TEST_F(SliceTest_5, EmptySlice_HasZeroSize_5) {

    EXPECT_TRUE(emptySlice.empty());

    EXPECT_EQ(emptySlice.size(), 0);

}



// Test normal operation of begin() and end()

TEST_F(SliceTest_5, BeginAndEnd_ReturnCorrectPointers_5) {

    EXPECT_STREQ(sampleSlice.begin(), "hello");

    EXPECT_STREQ(sampleSlice.end(), sampleSlice.data() + sampleSlice.size());

}



// Test normal operation of operator[]

TEST_F(SliceTest_5, OperatorBrackets_ReturnsCorrectCharacter_5) {

    EXPECT_EQ(sampleSlice[0], 'h');

    EXPECT_EQ(sampleSlice[4], 'o');

}



// Test boundary condition for operator[] (last element)

TEST_F(SliceTest_5, OperatorBrackets_LastElement_ReturnsCorrectCharacter_5) {

    EXPECT_EQ(sampleSlice[sampleSlice.size() - 1], 'o');

}



// Test exceptional case for operator[] (out of bounds access is undefined behavior,

// but we can test the expected behavior within bounds)

TEST_F(SliceTest_5, OperatorBrackets_OutOfBounds_NoCrash_5) {

    // No crash when accessing last valid element

    EXPECT_EQ(sampleSlice[sampleSlice.size() - 1], 'o');

}



// Test normal operation of clear()

TEST_F(SliceTest_5, Clear_ResetsToEmpty_5) {

    sampleSlice.clear();

    EXPECT_TRUE(sampleSlice.empty());

    EXPECT_EQ(sampleSlice.size(), 0);

}



// Test normal operation of remove_prefix()

TEST_F(SliceTest_5, RemovePrefix_ReducesSizeAndAdjustsDataPointer_5) {

    sampleSlice.remove_prefix(2);

    EXPECT_STREQ(sampleSlice.data(), "llo");

    EXPECT_EQ(sampleSlice.size(), 3);

}



// Test boundary condition for remove_prefix() (remove all characters)

TEST_F(SliceTest_5, RemovePrefix_RemoveAllCharacters_ResetsToEmpty_5) {

    sampleSlice.remove_prefix(5);

    EXPECT_TRUE(sampleSlice.empty());

    EXPECT_EQ(sampleSlice.size(), 0);

}



// Test exceptional case for remove_prefix() (removing more than size is undefined behavior,

// but we can test the expected behavior within bounds)

TEST_F(SliceTest_5, RemovePrefix_RemoveMoreThanSize_NoCrash_5) {

    // No crash when removing all characters

    sampleSlice.remove_prefix(5);

    EXPECT_TRUE(sampleSlice.empty());

    EXPECT_EQ(sampleSlice.size(), 0);

}



// Test normal operation of ToString()

TEST_F(SliceTest_5, ToString_ReturnsCorrectString_5) {

    EXPECT_EQ(sampleSlice.ToString(), "hello");

}



// Test boundary condition for ToString() (empty slice)

TEST_F(SliceTest_5, ToString_EmptySlice_ReturnsEmptyString_5) {

    EXPECT_EQ(emptySlice.ToString(), "");

}



// Test normal operation of starts_with()

TEST_F(SliceTest_5, StartsWith_CorrectPrefix_ReturnsTrue_5) {

    EXPECT_TRUE(sampleSlice.starts_with("hel"));

}



// Test boundary condition for starts_with() (empty prefix)

TEST_F(SliceTest_5, StartsWith_EmptyPrefix_ReturnsTrue_5) {

    EXPECT_TRUE(sampleSlice.starts_with(""));

}



// Test exceptional case for starts_with() (incorrect prefix)

TEST_F(SliceTest_5, StartsWith_IncorrectPrefix_ReturnsFalse_5) {

    EXPECT_FALSE(sampleSlice.starts_with("world"));

}



// Test normal operation of compare()

TEST_F(SliceTest_5, Compare_EqualSlices_ReturnZero_5) {

    EXPECT_EQ(sampleSlice.compare(sampleSlice), 0);

}



// Test normal operation of compare() (first slice is less)

TEST_F(SliceTest_5, Compare_FirstLess_ReturnNegative_5) {

    EXPECT_LT(sampleSlice.compare(anotherSampleSlice), 0);

}



// Test normal operation of compare() (first slice is greater)

TEST_F(SliceTest_5, Compare_FirstGreater_ReturnPositive_5) {

    EXPECT_GT(anotherSampleSlice.compare(sampleSlice), 0);

}
