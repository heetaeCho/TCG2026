#include <gtest/gtest.h>

#include "leveldb/slice.h"



class SliceTest_6 : public ::testing::Test {

protected:

    leveldb::Slice emptySlice;

    leveldb::Slice stringSlice;

    leveldb::Slice charArraySlice;



    void SetUp() override {

        emptySlice = leveldb::Slice();

        stringSlice = leveldb::Slice("hello");

        charArraySlice = leveldb::Slice("world", 5);

    }

};



TEST_F(SliceTest_6, DefaultConstructorCreatesEmptySlice_6) {

    EXPECT_TRUE(emptySlice.empty());

    EXPECT_EQ(emptySlice.size(), 0);

}



TEST_F(SliceTest_6, StringConstructorInitializesCorrectly_6) {

    EXPECT_FALSE(stringSlice.empty());

    EXPECT_EQ(stringSlice.size(), 5);

    EXPECT_STREQ(stringSlice.data(), "hello");

}



TEST_F(SliceTest_6, CharArrayConstructorInitializesCorrectly_6) {

    EXPECT_FALSE(charArraySlice.empty());

    EXPECT_EQ(charArraySlice.size(), 5);

    EXPECT_STREQ(charArraySlice.data(), "world");

}



TEST_F(SliceTest_6, OperatorBracketAccessesCorrectCharacter_6) {

    EXPECT_EQ(stringSlice[0], 'h');

    EXPECT_EQ(stringSlice[4], 'o');

}



TEST_F(SliceTest_6, OperatorBracketBoundaryCondition_6) {

    EXPECT_THROW({ stringSlice[stringSlice.size()]; }, std::exception);

}



TEST_F(SliceTest_6, CompareFunctionReturnsZeroForEqualSlices_6) {

    leveldb::Slice anotherHello("hello");

    EXPECT_EQ(stringSlice.compare(anotherHello), 0);

}



TEST_F(SliceTest_6, CompareFunctionReturnsNegativeForSmallerSlice_6) {

    leveldb::Slice hi("hi");

    EXPECT_LT(hi.compare(stringSlice), 0);

}



TEST_F(SliceTest_6, CompareFunctionReturnsPositiveForLargerSlice_6) {

    leveldb::Slice helloworld("helloworld");

    EXPECT_GT(helloworld.compare(stringSlice), 0);

}



TEST_F(SliceTest_6, ClearFunctionSetsSizeToZero_6) {

    stringSlice.clear();

    EXPECT_TRUE(stringSlice.empty());

    EXPECT_EQ(stringSlice.size(), 0);

}



TEST_F(SliceTest_6, RemovePrefixReducesSize_6) {

    size_t originalSize = stringSlice.size();

    stringSlice.remove_prefix(2);

    EXPECT_EQ(stringSlice.size(), originalSize - 2);

    EXPECT_STREQ(stringSlice.data(), "llo");

}



TEST_F(SliceTest_6, RemovePrefixWithZeroDoesNothing_6) {

    size_t originalSize = stringSlice.size();

    stringSlice.remove_prefix(0);

    EXPECT_EQ(stringSlice.size(), originalSize);

    EXPECT_STREQ(stringSlice.data(), "hello");

}



TEST_F(SliceTest_6, ToStringReturnsCorrectString_6) {

    EXPECT_EQ(stringSlice.ToString(), "hello");

}



TEST_F(SliceTest_6, StartsWithReturnsTrueForPrefix_6) {

    leveldb::Slice prefix("he");

    EXPECT_TRUE(stringSlice.starts_with(prefix));

}



TEST_F(SliceTest_6, StartsWithReturnsFalseForNonPrefix_6) {

    leveldb::Slice nonPrefix("lo");

    EXPECT_FALSE(stringSlice.starts_with(nonPrefix));

}
