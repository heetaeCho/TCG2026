#include <gtest/gtest.h>

#include "re2/sparse_array.h"



namespace re2 {



class SparseArrayTest_74 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_74, DefaultConstructorMaxSizeZero_74) {

    EXPECT_EQ(sparseArray.max_size(), 0);

}



TEST_F(SparseArrayTest_74, ConstructorWithMaxSize_74) {

    SparseArray<int> array(10);

    EXPECT_EQ(array.max_size(), 10);

}



TEST_F(SparseArrayTest_74, ResizeIncreasesMaxSize_74) {

    sparseArray.resize(5);

    EXPECT_EQ(sparseArray.max_size(), 5);

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_74, ResizeDecreasesMaxSize_74) {

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

    sparseArray.resize(5);

    EXPECT_EQ(sparseArray.max_size(), 5);

}



TEST_F(SparseArrayTest_74, ResizeToSameMaxSizeNoChange_74) {

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_74, CopyConstructorPreservesMaxSize_74) {

    SparseArray<int> original(10);

    SparseArray<int> copy(original);

    EXPECT_EQ(copy.max_size(), 10);

}



TEST_F(SparseArrayTest_74, MoveConstructorTransfersMaxSize_74) {

    SparseArray<int> original(10);

    SparseArray<int> moved(std::move(original));

    EXPECT_EQ(moved.max_size(), 10);

}



TEST_F(SparseArrayTest_74, CopyAssignmentPreservesMaxSize_74) {

    SparseArray<int> original(10);

    sparseArray = original;

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_74, MoveAssignmentTransfersMaxSize_74) {

    SparseArray<int> original(10);

    sparseArray = std::move(original);

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_74, ClearDoesNotChangeMaxSize_74) {

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

    sparseArray.clear();

    EXPECT_EQ(sparseArray.max_size(), 10);

}



} // namespace re2
