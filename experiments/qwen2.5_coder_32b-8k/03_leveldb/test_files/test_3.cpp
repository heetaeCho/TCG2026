#include <gtest/gtest.h>

#include "leveldb/slice.h"



using namespace leveldb;



class SliceTest_3 : public ::testing::Test {

protected:

    Slice emptySlice;

    Slice nonEmptySlice;

    Slice anotherNonEmptySlice;



    SliceTest_3()

        : emptySlice(),

          nonEmptySlice("test", 4),

          anotherNonEmptySlice("another_test") {}

};



TEST_F(SliceTest_3, Empty_ReturnsTrueForDefaultConstructedSlice_3) {

    EXPECT_TRUE(emptySlice.empty());

}



TEST_F(SliceTest_3, Empty_ReturnsFalseForNonEmptySlice_3) {

    EXPECT_FALSE(nonEmptySlice.empty());

}



TEST_F(SliceTest_3, Size_ReturnsCorrectSizeForExplicitlySizedSlice_3) {

    EXPECT_EQ(nonEmptySlice.size(), 4);

}



TEST_F(SliceTest_3, Size_ReturnsCorrectSizeForCStringConstructor_3) {

    EXPECT_EQ(anotherNonEmptySlice.size(), 12);

}



TEST_F(SliceTest_3, Data_ReturnsPointerToData_3) {

    EXPECT_STREQ(nonEmptySlice.data(), "test");

}



TEST_F(SliceTest_3, ToString_ReturnsCorrectString_3) {

    EXPECT_EQ(nonEmptySlice.ToString(), "test");

}



TEST_F(SliceTest_3, Compare_ReturnsZeroForEqualSlices_3) {

    Slice slice1("equal", 5);

    Slice slice2("equal", 5);

    EXPECT_EQ(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_3, Compare_ReturnsNegativeWhenFirstSliceIsLess_3) {

    Slice slice1("abc", 3);

    Slice slice2("def", 3);

    EXPECT_LT(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_3, Compare_ReturnsPositiveWhenFirstSliceIsGreater_3) {

    Slice slice1("xyz", 3);

    Slice slice2("uvw", 3);

    EXPECT_GT(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_3, OperatorEqual_CopiesDataAndSizeCorrectly_3) {

    Slice copiedSlice = nonEmptySlice;

    EXPECT_EQ(copiedSlice.size(), nonEmptySlice.size());

    EXPECT_STREQ(copiedSlice.data(), nonEmptySlice.data());

}



TEST_F(SliceTest_3, Clear_ResetsSizeToZero_3) {

    Slice slice("test", 4);

    slice.clear();

    EXPECT_TRUE(slice.empty());

}



TEST_F(SliceTest_3, RemovePrefix_ReducesSizeCorrectly_3) {

    Slice slice("prefix_test", 11);

    slice.remove_prefix(7);

    EXPECT_EQ(slice.size(), 4);

    EXPECT_STREQ(slice.data(), "test");

}



TEST_F(SliceTest_3, StartsWidth_ReturnsTrueForMatchingPrefix_3) {

    Slice prefix("prefix");

    Slice fullString("prefix_test", 11);

    EXPECT_TRUE(fullString.starts_with(prefix));

}



TEST_F(SliceTest_3, StartsWidth_ReturnsFalseForNonMatchingPrefix_3) {

    Slice prefix("non_match");

    Slice fullString("prefix_test", 11);

    EXPECT_FALSE(fullString.starts_with(prefix));

}



TEST_F(SliceTest_3, OperatorIndex_ReturnsCorrectCharacter_3) {

    EXPECT_EQ(nonEmptySlice[0], 't');

    EXPECT_EQ(nonEmptySlice[3], 't');

}



TEST_F(SliceTest_3, BeginAndEnd_ReturnPointersToDataRange_3) {

    const char* expectedBegin = "test";

    const char* expectedEnd = "test" + 4;

    EXPECT_EQ(nonEmptySlice.begin(), expectedBegin);

    EXPECT_EQ(nonEmptySlice.end(), expectedEnd);

}
