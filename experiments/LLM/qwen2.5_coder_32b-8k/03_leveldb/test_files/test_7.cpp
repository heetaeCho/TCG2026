#include <gtest/gtest.h>

#include "leveldb/slice.h"



using namespace leveldb;



class SliceTest_7 : public ::testing::Test {

protected:

    Slice emptySlice;

    Slice nonEmptySlice1;

    Slice nonEmptySlice2;



    SliceTest_7() 

        : emptySlice(),

          nonEmptySlice1("test"),

          nonEmptySlice2("another_test") {}

};



TEST_F(SliceTest_7, ClearEmptiesData_7) {

    nonEmptySlice1.clear();

    EXPECT_EQ(nonEmptySlice1.data(), "");

    EXPECT_EQ(nonEmptySlice1.size(), 0);

}



TEST_F(SliceTest_7, EmptyReturnsTrueForEmptySlice_7) {

    EXPECT_TRUE(emptySlice.empty());

}



TEST_F(SliceTest_7, EmptyReturnsFalseForNonEmptySlice_7) {

    EXPECT_FALSE(nonEmptySlice1.empty());

}



TEST_F(SliceTest_7, SizeReturnsCorrectLength_7) {

    EXPECT_EQ(nonEmptySlice1.size(), 4);

    EXPECT_EQ(nonEmptySlice2.size(), 12);

}



TEST_F(SliceTest_7, DataReturnsPointerToData_7) {

    EXPECT_STREQ(nonEmptySlice1.data(), "test");

    EXPECT_STREQ(nonEmptySlice2.data(), "another_test");

}



TEST_F(SliceTest_7, ToStringConvertsToStdString_7) {

    EXPECT_EQ(nonEmptySlice1.ToString(), "test");

    EXPECT_EQ(nonEmptySlice2.ToString(), "another_test");

}



TEST_F(SliceTest_7, BeginReturnsPointerToStart_7) {

    EXPECT_EQ(nonEmptySlice1.begin(), nonEmptySlice1.data());

}



TEST_F(SliceTest_7, EndReturnsPointerToEnd_7) {

    EXPECT_EQ(nonEmptySlice1.end(), nonEmptySlice1.data() + nonEmptySlice1.size());

}



TEST_F(SliceTest_7, OperatorSquareBracketAccessesCorrectCharacter_7) {

    EXPECT_EQ(nonEmptySlice1[0], 't');

    EXPECT_EQ(nonEmptySlice2[3], 'e');

}



TEST_F(SliceTest_7, RemovePrefixReducesSize_7) {

    nonEmptySlice1.remove_prefix(2);

    EXPECT_EQ(nonEmptySlice1.size(), 2);

    EXPECT_STREQ(nonEmptySlice1.data(), "st");

}



TEST_F(SliceTest_7, CompareReturnsZeroForEqualSlices_7) {

    Slice sliceCopy("test");

    EXPECT_EQ(nonEmptySlice1.compare(sliceCopy), 0);

}



TEST_F(SliceTest_7, CompareReturnsNonZeroForDifferentSlices_7) {

    EXPECT_NE(nonEmptySlice1.compare(nonEmptySlice2), 0);

}



TEST_F(SliceTest_7, StartsWithReturnsTrueWhenPrefixMatches_7) {

    Slice prefix("tes");

    EXPECT_TRUE(nonEmptySlice1.starts_with(prefix));

}



TEST_F(SliceTest_7, StartsWithReturnsFalseWhenPrefixDoesNotMatch_7) {

    Slice nonPrefix("best");

    EXPECT_FALSE(nonEmptySlice1.starts_with(nonPrefix));

}
