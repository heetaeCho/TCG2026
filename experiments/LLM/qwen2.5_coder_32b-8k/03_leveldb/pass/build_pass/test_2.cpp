#include <gtest/gtest.h>

#include "leveldb/slice.h"

#include <string>



class SliceTest_2 : public ::testing::Test {

protected:

    leveldb::Slice emptySlice;

    leveldb::Slice charSlice;

    leveldb::Slice stringSlice;

    leveldb::Slice cStringSlice;



    SliceTest_2()

        : emptySlice(),

          charSlice("abc", 3),

          stringSlice(std::string("def")),

          cStringSlice("ghi") {}

};



TEST_F(SliceTest_2, EmptySliceSizeIsZero_2) {

    EXPECT_EQ(emptySlice.size(), 0);

}



TEST_F(SliceTest_2, CharSliceSizeCorrect_2) {

    EXPECT_EQ(charSlice.size(), 3);

}



TEST_F(SliceTest_2, StringSliceSizeCorrect_2) {

    EXPECT_EQ(stringSlice.size(), 3);

}



TEST_F(SliceTest_2, CStringSliceSizeCorrect_2) {

    EXPECT_EQ(cStringSlice.size(), 3);

}



TEST_F(SliceTest_2, EmptySliceIsEmptyTrue_2) {

    EXPECT_TRUE(emptySlice.empty());

}



TEST_F(SliceTest_2, NonEmptySliceIsEmptyFalse_2) {

    EXPECT_FALSE(charSlice.empty());

}



TEST_F(SliceTest_2, SliceCompareEqualStrings_2) {

    leveldb::Slice slice1("abc");

    leveldb::Slice slice2("abc");

    EXPECT_EQ(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_2, SliceCompareLexicographicallySmaller_2) {

    leveldb::Slice slice1("abc");

    leveldb::Slice slice2("def");

    EXPECT_LT(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_2, SliceCompareLexicographicallyGreater_2) {

    leveldb::Slice slice1("xyz");

    leveldb::Slice slice2("uvw");

    EXPECT_GT(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_2, SliceDataReturnsCorrectPointer_2) {

    EXPECT_EQ(cStringSlice.data(), static_cast<const char*>("ghi"));

}



TEST_F(SliceTest_2, SliceBeginEndReturnCorrectPointers_2) {

    EXPECT_EQ(stringSlice.begin(), stringSlice.data());

    EXPECT_EQ(stringSlice.end(), stringSlice.data() + stringSlice.size());

}



TEST_F(SliceTest_2, SliceOperatorBracketReturnsCorrectCharacter_2) {

    EXPECT_EQ(cStringSlice[0], 'g');

    EXPECT_EQ(cStringSlice[1], 'h');

    EXPECT_EQ(cStringSlice[2], 'i');

}



TEST_F(SliceTest_2, SliceRemovePrefixReducesSize_2) {

    leveldb::Slice slice("abc");

    slice.remove_prefix(1);

    EXPECT_EQ(slice.size(), 2);

    EXPECT_EQ(slice.data()[0], 'b');

    EXPECT_EQ(slice.data()[1], 'c');

}



TEST_F(SliceTest_2, SliceRemovePrefixWithZeroDoesNotChange_2) {

    leveldb::Slice slice("abc");

    slice.remove_prefix(0);

    EXPECT_EQ(slice.size(), 3);

    EXPECT_EQ(slice.data()[0], 'a');

    EXPECT_EQ(slice.data()[1], 'b');

    EXPECT_EQ(slice.data()[2], 'c');

}



TEST_F(SliceTest_2, SliceRemovePrefixWithFullSizeResultsInEmpty_2) {

    leveldb::Slice slice("abc");

    slice.remove_prefix(3);

    EXPECT_TRUE(slice.empty());

}



TEST_F(SliceTest_2, SliceToStringReturnsCorrectString_2) {

    EXPECT_EQ(cStringSlice.ToString(), "ghi");

}



TEST_F(SliceTest_2, SliceStartsWithTrue_2) {

    leveldb::Slice slice("prefix_suffix");

    leveldb::Slice prefix("prefix");

    EXPECT_TRUE(slice.starts_with(prefix));

}



TEST_F(SliceTest_2, SliceStartsWithFalse_2) {

    leveldb::Slice slice("prefix_suffix");

    leveldb::Slice wrongPrefix("wrong");

    EXPECT_FALSE(slice.starts_with(wrongPrefix));

}
