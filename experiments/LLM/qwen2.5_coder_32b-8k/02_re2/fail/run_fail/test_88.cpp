#include <gtest/gtest.h>

#include "TestProjects/re2/re2/sparse_set.h"



using namespace re2;



class SparseSetTest_88 : public ::testing::Test {

protected:

    SparseSet set;

};



TEST_F(SparseSetTest_88, InitialSizeIsZero_88) {

    EXPECT_EQ(set.size(), 0);

}



TEST_F(SparseSetTest_88, ResizeIncreasesCapacity_88) {

    int new_max_size = 10;

    set.resize(new_max_size);

    EXPECT_GE(set.max_size(), new_max_size);

}



TEST_F(SparseSetTest_88, InsertNewElementIncreasesSize_88) {

    set.insert_new(5);

    EXPECT_EQ(set.size(), 1);

}



TEST_F(SparseSetTest_88, InsertExistingElementDoesNotIncreaseSize_88) {

    set.insert_new(5);

    set.insert(5);

    EXPECT_EQ(set.size(), 1);

}



TEST_F(SparseSetTest_88, ContainsReturnsTrueForInsertedElement_88) {

    set.insert_new(5);

    EXPECT_TRUE(set.contains(5));

}



TEST_F(SparseSetTest_88, ContainsReturnsFalseForNonInsertedElement_88) {

    EXPECT_FALSE(set.contains(5));

}



TEST_F(SparseSetTest_88, ClearEmptiesTheSet_88) {

    set.insert_new(5);

    set.clear();

    EXPECT_EQ(set.size(), 0);

}



TEST_F(SparseSetTest_88, BeginEndIteratorsCorrectForEmptySet_88) {

    EXPECT_EQ(set.begin(), set.end());

}



TEST_F(SparseSetTest_88, BeginEndIteratorsCorrectAfterInsertion_88) {

    set.insert_new(5);

    EXPECT_NE(set.begin(), set.end());

}



TEST_F(SparseSetTest_88, IteratorPointsToInsertedElement_88) {

    set.insert_new(5);

    auto it = set.begin();

    EXPECT_EQ(*it, 5);

}
