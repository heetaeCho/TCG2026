#include <gtest/gtest.h>

#include "re2/sparse_array.h"



namespace {



class SparseArrayTest_79 : public ::testing::Test {

protected:

    re2::SparseArray<int> sparse_array;



    void SetUp() override {

        sparse_array.resize(10);

    }

};



TEST_F(SparseArrayTest_79, ResizeIncreasesMaxSize_79) {

    int initial_max_size = sparse_array.max_size();

    sparse_array.resize(20);

    EXPECT_GT(sparse_array.max_size(), initial_max_size);

}



TEST_F(SparseArrayTest_79, HasIndexReturnsFalseForUnsetIndex_79) {

    EXPECT_FALSE(sparse_array.has_index(5));

}



TEST_F(SparseArrayTest_79, SetNewAddsIndex_79) {

    sparse_array.set_new(5, 10);

    EXPECT_TRUE(sparse_array.has_index(5));

}



TEST_F(SparseArrayTest_79, GetExistingThrowsAssertionForNonexistentIndex_79) {

    EXPECT_DEATH({ sparse_array.get_existing(5); }, ".*");

}



TEST_F(SparseArrayTest_79, SetExistingUpdatesValue_79) {

    sparse_array.set_new(5, 10);

    sparse_array.set_existing(5, 20);

    EXPECT_EQ(sparse_array.get_existing(5), 20);

}



TEST_F(SparseArrayTest_79, ClearRemovesAllIndices_79) {

    sparse_array.set_new(5, 10);

    sparse_array.clear();

    EXPECT_FALSE(sparse_array.has_index(5));

    EXPECT_EQ(sparse_array.size(), 0);

}



TEST_F(SparseArrayTest_79, SizeReflectsNumberOfSetIndices_79) {

    sparse_array.set_new(3, 30);

    sparse_array.set_new(7, 70);

    EXPECT_EQ(sparse_array.size(), 2);

}



TEST_F(SparseArrayTest_79, BeginEndIterateOverSetIndices_79) {

    sparse_array.set_new(3, 30);

    sparse_array.set_new(7, 70);

    int count = 0;

    for (auto it = sparse_array.begin(); it != sparse_array.end(); ++it) {

        ++count;

    }

    EXPECT_EQ(count, 2);

}



TEST_F(SparseArrayTest_79, MaxSizeIsCorrectAfterInitialization_79) {

    re2::SparseArray<int> another_sparse_array(50);

    EXPECT_EQ(another_sparse_array.max_size(), 50);

}



TEST_F(SparseArrayTest_79, AssignmentOperatorCopiesData_79) {

    sparse_array.set_new(3, 30);

    re2::SparseArray<int> copied_array = sparse_array;

    EXPECT_TRUE(copied_array.has_index(3));

    EXPECT_EQ(copied_array.get_existing(3), 30);

}



TEST_F(SparseArrayTest_79, MoveConstructorTransfersData_79) {

    sparse_array.set_new(3, 30);

    re2::SparseArray<int> moved_array = std::move(sparse_array);

    EXPECT_TRUE(moved_array.has_index(3));

    EXPECT_EQ(moved_array.get_existing(3), 30);

}



TEST_F(SparseArrayTest_79, MoveAssignmentOperatorTransfersData_79) {

    sparse_array.set_new(3, 30);

    re2::SparseArray<int> moved_array;

    moved_array = std::move(sparse_array);

    EXPECT_TRUE(moved_array.has_index(3));

    EXPECT_EQ(moved_array.get_existing(3), 30);

}



TEST_F(SparseArrayTest_79, EmptyReturnsTrueForNoIndices_79) {

    EXPECT_TRUE(sparse_array.empty());

}



TEST_F(SparseArrayTest_79, EmptyReturnsFalseAfterSettingIndex_79) {

    sparse_array.set_new(5, 10);

    EXPECT_FALSE(sparse_array.empty());

}



} // namespace
