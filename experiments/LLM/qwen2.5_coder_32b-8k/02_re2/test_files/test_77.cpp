#include <gtest/gtest.h>

#include "sparse_array.h"



namespace re2 {



class SparseArrayTest_77 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_77, SetNew_IncreasesSize_77) {

    int sizeBefore = sparseArray.size();

    sparseArray.set_new(0, 42);

    EXPECT_EQ(sparseArray.size(), sizeBefore + 1);

}



TEST_F(SparseArrayTest_77, SetNew_ReturnsValidIterator_77) {

    auto it = sparseArray.set_new(0, 42);

    EXPECT_NE(it, sparseArray.end());

}



TEST_F(SparseArrayTest_77, SetNew_SetsValueCorrectly_77) {

    sparseArray.set_new(0, 42);

    EXPECT_EQ(sparseArray.get_existing(0), 42);

}



TEST_F(SparseArrayTest_77, SetNew_DoesNotOverwriteExisting_77) {

    sparseArray.set_new(0, 42);

    auto it = sparseArray.set_new(0, 84);

    EXPECT_EQ(sparseArray.get_existing(0), 42);

    EXPECT_NE(it, sparseArray.end());

}



TEST_F(SparseArrayTest_77, SetNew_BoundaryCondition_StartIndex_77) {

    sparseArray.set_new(0, 10);

    EXPECT_TRUE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_77, SetNew_BoundaryCondition_EndIndex_77) {

    sparseArray.resize(10);

    sparseArray.set_new(9, 20);

    EXPECT_TRUE(sparseArray.has_index(9));

}



TEST_F(SparseArrayTest_77, SetNew_OutOfBounds_NoEffect_77) {

    int sizeBefore = sparseArray.size();

    sparseArray.set_new(10, 30); // Assuming default max_size is less than 10

    EXPECT_EQ(sparseArray.size(), sizeBefore);

}



TEST_F(SparseArrayTest_77, HasIndex_ReturnsTrueForSetIndex_77) {

    sparseArray.set_new(5, 50);

    EXPECT_TRUE(sparseArray.has_index(5));

}



TEST_F(SparseArrayTest_77, HasIndex_ReturnsFalseForUnsetIndex_77) {

    EXPECT_FALSE(sparseArray.has_index(5));

}



TEST_F(SparseArrayTest_77, Size_IncreasesWithEachNewSet_77) {

    sparseArray.set_new(0, 1);

    sparseArray.set_new(1, 2);

    sparseArray.set_new(2, 3);

    EXPECT_EQ(sparseArray.size(), 3);

}



TEST_F(SparseArrayTest_77, Resize_IncreasesMaxSize_77) {

    int oldMaxSize = sparseArray.max_size();

    sparseArray.resize(oldMaxSize + 5);

    EXPECT_GE(sparseArray.max_size(), oldMaxSize + 5);

}



TEST_F(SparseArrayTest_77, Clear_ResetsSizeToZero_77) {

    sparseArray.set_new(0, 1);

    sparseArray.set_new(1, 2);

    sparseArray.clear();

    EXPECT_EQ(sparseArray.size(), 0);

}



} // namespace re2
