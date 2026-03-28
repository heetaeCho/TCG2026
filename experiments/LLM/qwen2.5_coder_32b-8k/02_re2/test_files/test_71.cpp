#include <gtest/gtest.h>

#include "sparse_array.h"



using namespace re2;



class SparseArrayTest_71 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_71, InitialStateIsEmpty_71) {

    EXPECT_TRUE(sparseArray.empty());

}



TEST_F(SparseArrayTest_71, ResizeIncreasesMaxSize_71) {

    int initialMaxSize = sparseArray.max_size();

    sparseArray.resize(initialMaxSize + 1);

    EXPECT_GT(sparseArray.max_size(), initialMaxSize);

}



TEST_F(SparseArrayTest_71, SetNewElementIncreasesSize_71) {

    sparseArray.set_new(0, 42);

    EXPECT_FALSE(sparseArray.empty());

    EXPECT_EQ(sparseArray.size(), 1);

}



TEST_F(SparseArrayTest_71, SetExistingElementDoesNotChangeSize_71) {

    sparseArray.set_new(0, 42);

    sparseArray.set_existing(0, 84);

    EXPECT_FALSE(sparseArray.empty());

    EXPECT_EQ(sparseArray.size(), 1);

}



TEST_F(SparseArrayTest_71, ClearEmptiesArray_71) {

    sparseArray.set_new(0, 42);

    sparseArray.clear();

    EXPECT_TRUE(sparseArray.empty());

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_71, HasIndexReturnsFalseForNonexistentIndex_71) {

    EXPECT_FALSE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_71, HasIndexReturnsTrueForExistingIndex_71) {

    sparseArray.set_new(0, 42);

    EXPECT_TRUE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_71, GetExistingThrowsForNonexistentIndex_71) {

    EXPECT_THROW(sparseArray.get_existing(0), std::exception);

}



TEST_F(SparseArrayTest_71, BoundaryConditionSetNewMaxSizeZero_71) {

    SparseArray<int> smallArray(0);

    EXPECT_TRUE(smallArray.empty());

    EXPECT_EQ(smallArray.max_size(), 0);

    EXPECT_THROW(smallArray.set_new(0, 42), std::exception);

}



TEST_F(SparseArrayTest_71, BoundaryConditionSetExistingMaxSizeZero_71) {

    SparseArray<int> smallArray(0);

    EXPECT_TRUE(smallArray.empty());

    EXPECT_EQ(smallArray.max_size(), 0);

    EXPECT_THROW(smallArray.set_existing(0, 42), std::exception);

}
