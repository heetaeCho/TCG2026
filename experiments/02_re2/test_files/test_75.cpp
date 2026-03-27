#include <gtest/gtest.h>

#include "re2/sparse_array.h"



using namespace re2;



class SparseArrayTest_75 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_75, DefaultConstructorInitializesSizeToZero_75) {

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_75, IntConstructorSetsMaxSize_75) {

    SparseArray<int> array(10);

    EXPECT_EQ(array.max_size(), 10);

}



TEST_F(SparseArrayTest_75, CopyConstructorCreatesEqualObject_75) {

    sparseArray.set(0, 42);

    SparseArray<int> copy(sparseArray);

    EXPECT_EQ(copy.size(), sparseArray.size());

    EXPECT_TRUE(copy.has_index(0));

    EXPECT_EQ(copy.get_existing(0), sparseArray.get_existing(0));

}



TEST_F(SparseArrayTest_75, MoveConstructorTransfersOwnership_75) {

    sparseArray.set(0, 42);

    SparseArray<int> moved(std::move(sparseArray));

    EXPECT_EQ(moved.size(), 1);

    EXPECT_TRUE(moved.has_index(0));

    EXPECT_EQ(moved.get_existing(0), 42);

}



TEST_F(SparseArrayTest_75, CopyAssignmentOperatorCreatesEqualObject_75) {

    sparseArray.set(0, 42);

    SparseArray<int> copy;

    copy = sparseArray;

    EXPECT_EQ(copy.size(), sparseArray.size());

    EXPECT_TRUE(copy.has_index(0));

    EXPECT_EQ(copy.get_existing(0), sparseArray.get_existing(0));

}



TEST_F(SparseArrayTest_75, MoveAssignmentOperatorTransfersOwnership_75) {

    sparseArray.set(0, 42);

    SparseArray<int> moved;

    moved = std::move(sparseArray);

    EXPECT_EQ(moved.size(), 1);

    EXPECT_TRUE(moved.has_index(0));

    EXPECT_EQ(moved.get_existing(0), 42);

}



TEST_F(SparseArrayTest_75, ResizeIncreasesMaxSize_75) {

    sparseArray.resize(20);

    EXPECT_GE(sparseArray.max_size(), 20);

}



TEST_F(SparseArrayTest_75, HasIndexReturnsFalseForNonexistentIndex_75) {

    EXPECT_FALSE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_75, SetIncreasesSize_75) {

    sparseArray.set(0, 42);

    EXPECT_EQ(sparseArray.size(), 1);

}



TEST_F(SparseArrayTest_75, SetNewAddsNewIndex_75) {

    sparseArray.set_new(0, 42);

    EXPECT_TRUE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_75, SetExistingUpdatesExistingIndex_75) {

    sparseArray.set(0, 42);

    sparseArray.set_existing(0, 84);

    EXPECT_EQ(sparseArray.get_existing(0), 84);

}



TEST_F(SparseArrayTest_75, GetExistingReturnsCorrectValue_75) {

    sparseArray.set(0, 42);

    EXPECT_EQ(sparseArray.get_existing(0), 42);

}



TEST_F(SparseArrayTest_75, ClearResetsSizeToZero_75) {

    sparseArray.set(0, 42);

    sparseArray.clear();

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_75, BeginAndEndIterateOverElements_75) {

    sparseArray.set(0, 42);

    sparseArray.set(1, 84);

    int count = 0;

    for (auto it = sparseArray.begin(); it != sparseArray.end(); ++it) {

        count++;

    }

    EXPECT_EQ(count, 2);

}



TEST_F(SparseArrayTest_75, EmptyReturnsTrueWhenSizeIsZero_75) {

    EXPECT_TRUE(sparseArray.empty());

    sparseArray.set(0, 42);

    EXPECT_FALSE(sparseArray.empty());

}
