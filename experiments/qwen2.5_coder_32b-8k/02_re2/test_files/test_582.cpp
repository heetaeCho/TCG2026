#include <gtest/gtest.h>

#include "sparse_array.h"



namespace re2 {



class SparseArrayTest : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_582, DefaultConstructorInitializesSizeZero_582) {

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_582, ParameterizedConstructorSetsMaxSize_582) {

    SparseArray<int> sparseArray(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_582, CopyConstructorCopiesData_582) {

    SparseArray<int> original(10);

    for (int i = 0; i < 10; ++i) {

        original.set(i, i * 10);

    }

    SparseArray<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());

    for (int i = 0; i < 10; ++i) {

        EXPECT_TRUE(copy.has_index(i));

        EXPECT_EQ(copy.get_existing(i), original.get_existing(i));

    }

}



TEST_F(SparseArrayTest_582, MoveConstructorMovesData_582) {

    SparseArray<int> original(10);

    for (int i = 0; i < 10; ++i) {

        original.set(i, i * 10);

    }

    SparseArray<int> moved(std::move(original));

    EXPECT_EQ(moved.size(), 10);

    for (int i = 0; i < 10; ++i) {

        EXPECT_TRUE(moved.has_index(i));

        EXPECT_EQ(moved.get_existing(i), i * 10);

    }

}



TEST_F(SparseArrayTest_582, ResizeIncreasesMaxSize_582) {

    sparseArray.resize(5);

    EXPECT_EQ(sparseArray.max_size(), 5);

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_582, SetNewAddsNewIndex_582) {

    auto it = sparseArray.set_new(3, 30);

    EXPECT_TRUE(sparseArray.has_index(3));

    EXPECT_EQ(*it, 30);

}



TEST_F(SparseArrayTest_582, GetExistingReturnsCorrectValue_582) {

    sparseArray.set(3, 30);

    EXPECT_EQ(sparseArray.get_existing(3), 30);

}



TEST_F(SparseArrayTest_582, SetExistingUpdatesExistingIndex_582) {

    sparseArray.set_new(3, 30);

    auto it = sparseArray.set_existing(3, 35);

    EXPECT_TRUE(sparseArray.has_index(3));

    EXPECT_EQ(*it, 35);

}



TEST_F(SparseArrayTest_582, ClearRemovesAllIndices_582) {

    for (int i = 0; i < 10; ++i) {

        sparseArray.set(i, i * 10);

    }

    sparseArray.clear();

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_582, BoundaryConditionSetIndexZero_582) {

    auto it = sparseArray.set_new(0, 0);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(*it, 0);

}



TEST_F(SparseArrayTest_582, BoundaryConditionSetMaxIndex_582) {

    SparseArray<int> array(10);

    auto it = array.set_new(9, 90);

    EXPECT_TRUE(array.has_index(9));

    EXPECT_EQ(*it, 90);

}



TEST_F(SparseArrayTest_582, ExceptionalCaseSetNegativeIndex_582) {

    // Assuming set method will handle negative indices appropriately

    auto it = sparseArray.set(-1, -10);

    EXPECT_FALSE(sparseArray.has_index(-1));

}



TEST_F(SparseArrayTest_582, ExceptionalCaseSetExceedMaxSize_582) {

    SparseArray<int> array(5);

    auto it = array.set_new(6, 60);

    EXPECT_FALSE(array.has_index(6));

}



} // namespace re2
