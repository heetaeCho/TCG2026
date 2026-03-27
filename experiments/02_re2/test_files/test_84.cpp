#include <gtest/gtest.h>

#include "re2/sparse_array.h"



using namespace re2;



TEST_F(SparseArrayTest_84, ResizeIncreasesMaxSize_84) {

    SparseArray<int> sparseArray(10);

    sparseArray.resize(20);

    EXPECT_EQ(sparseArray.max_size(), 20);

}



TEST_F(SparseArrayTest_84, ResizeDecreasesSizeIfNecessary_84) {

    SparseArray<int> sparseArray;

    for (int i = 0; i < 15; ++i) {

        sparseArray.set(i, i);

    }

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.size(), 10);

}



TEST_F(SparseArrayTest_84, ResizeDoesNotChangeSizeIfNewMaxIsLarger_84) {

    SparseArray<int> sparseArray;

    for (int i = 0; i < 5; ++i) {

        sparseArray.set(i, i);

    }

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.size(), 5);

}



TEST_F(SparseArrayTest_84, ResizeHandlesZeroMaxSize_84) {

    SparseArray<int> sparseArray(10);

    for (int i = 0; i < 5; ++i) {

        sparseArray.set(i, i);

    }

    sparseArray.resize(0);

    EXPECT_EQ(sparseArray.size(), 0);

    EXPECT_EQ(sparseArray.max_size(), 0);

}



TEST_F(SparseArrayTest_84, ResizeHandlesSameMaxSize_84) {

    SparseArray<int> sparseArray(10);

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_84, SetIncreasesSize_84) {

    SparseArray<int> sparseArray;

    sparseArray.set(5, 5);

    EXPECT_EQ(sparseArray.size(), 1);

}



TEST_F(SparseArrayTest_84, HasIndexReturnsTrueForExistingIndex_84) {

    SparseArray<int> sparseArray;

    sparseArray.set(5, 5);

    EXPECT_TRUE(sparseArray.has_index(5));

}



TEST_F(SparseArrayTest_84, HasIndexReturnsFalseForNonExistingIndex_84) {

    SparseArray<int> sparseArray;

    EXPECT_FALSE(sparseArray.has_index(5));

}



TEST_F(SparseArrayTest_84, ClearResetsSize_84) {

    SparseArray<int> sparseArray;

    for (int i = 0; i < 10; ++i) {

        sparseArray.set(i, i);

    }

    sparseArray.clear();

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_84, GetExistingThrowsForNonExistingIndex_84) {

    SparseArray<int> sparseArray;

    EXPECT_THROW(sparseArray.get_existing(5), std::out_of_range);

}
