#include "gtest/gtest.h"

#include "leveldb/slice.h"



using namespace leveldb;



class SliceTest_13 : public ::testing::Test {

protected:

    Slice emptySlice;

    Slice sliceA;

    Slice sliceB;

    Slice sliceC;



    SliceTest_13() 

        : emptySlice(""), 

          sliceA("apple"), 

          sliceB("banana"), 

          sliceC("apple") {}

};



TEST_F(SliceTest_13, CompareEqualStrings_13) {

    EXPECT_EQ(0, sliceA.compare(sliceC));

}



TEST_F(SliceTest_13, CompareDifferentStrings_13) {

    EXPECT_LT(sliceA.compare(sliceB), 0);

    EXPECT_GT(sliceB.compare(sliceA), 0);

}



TEST_F(SliceTest_13, CompareEmptyStringWithNonEmpty_13) {

    EXPECT_LT(emptySlice.compare(sliceA), 0);

    EXPECT_GT(sliceA.compare(emptySlice), 0);

}



TEST_F(SliceTest_13, CompareSamePrefixDifferentLengths_13) {

    Slice prefixA("appl");

    Slice prefixB("applepie");



    EXPECT_LT(prefixA.compare(sliceA), 0);

    EXPECT_GT(sliceA.compare(prefixA), 0);



    EXPECT_LT(prefixA.compare(prefixB), 0);

    EXPECT_GT(prefixB.compare(prefixA), 0);

}



TEST_F(SliceTest_13, CompareIdenticalStringsDifferentInstances_13) {

    Slice anotherA("apple");

    EXPECT_EQ(0, sliceA.compare(anotherA));

}



TEST_F(SliceTest_13, EmptyStringComparison_13) {

    EXPECT_EQ(0, emptySlice.compare(emptySlice));

}
