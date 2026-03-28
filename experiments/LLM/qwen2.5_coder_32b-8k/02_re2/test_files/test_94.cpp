#include <gtest/gtest.h>

#include "sparse_set.h"



using namespace re2;



class SparseSetTest_94 : public ::testing::Test {

protected:

    SparseSet sparse_set;

    SparseSet sparse_set_with_initial_size;



    SparseSetTest_94() : sparse_set(), sparse_set_with_initial_size(10) {}

};



TEST_F(SparseSetTest_94, ResizeIncreasesCapacity_94) {

    int initial_max_size = sparse_set.max_size();

    sparse_set.resize(initial_max_size + 5);

    EXPECT_GE(sparse_set.max_size(), initial_max_size + 5);

}



TEST_F(SparseSetTest_94, ResizeDecreasesSizeIfNewMaxIsSmallerThanCurrentSize_94) {

    int new_max_size = 3;

    for (int i = 0; i < new_max_size + 2; ++i) {

        sparse_set.insert_new(i);

    }

    sparse_set.resize(new_max_size);

    EXPECT_EQ(sparse_set.size(), new_max_size);

}



TEST_F(SparseSetTest_94, ResizeDoesNotChangeCapacityIfNewMaxIsSmallerThanOrEqualToCurrentSize_94) {

    int initial_max_size = sparse_set_with_initial_size.max_size();

    sparse_set_with_initial_size.resize(initial_max_size - 1);

    EXPECT_EQ(sparse_set_with_initial_size.max_size(), initial_max_size);

}



TEST_F(SparseSetTest_94, ContainsReturnsTrueForInsertedElements_94) {

    int element = 5;

    sparse_set.insert_new(element);

    EXPECT_TRUE(sparse_set.contains(element));

}



TEST_F(SparseSetTest_94, ContainsReturnsFalseForNonInsertedElements_94) {

    int element = 10;

    EXPECT_FALSE(sparse_set.contains(element));

}



TEST_F(SparseSetTest_94, InsertNewIncreasesSize_94) {

    int initial_size = sparse_set.size();

    sparse_set.insert_new(5);

    EXPECT_EQ(sparse_set.size(), initial_size + 1);

}



TEST_F(SparseSetTest_94, InsertNewDoesNotIncreaseSizeIfElementAlreadyExists_94) {

    int element = 5;

    sparse_set.insert_new(element);

    int size_after_first_insert = sparse_set.size();

    sparse_set.insert_new(element);

    EXPECT_EQ(sparse_set.size(), size_after_first_insert);

}



TEST_F(SparseSetTest_94, InsertNewResizesIfMaxSizeIsReached_94) {

    for (int i = 0; i < sparse_set_with_initial_size.max_size(); ++i) {

        sparse_set_with_initial_size.insert_new(i);

    }

    int initial_max_size = sparse_set_with_initial_size.max_size();

    sparse_set_with_initial_size.insert_new(initial_max_size);

    EXPECT_GE(sparse_set_with_initial_size.max_size(), initial_max_size + 1);

}



TEST_F(SparseSetTest_94, ClearResetsSizeToZero_94) {

    for (int i = 0; i < 5; ++i) {

        sparse_set.insert_new(i);

    }

    sparse_set.clear();

    EXPECT_EQ(sparse_set.size(), 0);

}



TEST_F(SparseSetTest_94, BeginAndEndIterateOverInsertedElements_94) {

    std::vector<int> inserted_elements = {1, 3, 5};

    for (int element : inserted_elements) {

        sparse_set.insert_new(element);

    }

    std::vector<int> iterated_elements(sparse_set.begin(), sparse_set.end());

    EXPECT_EQ(iterated_elements, inserted_elements);

}



TEST_F(SparseSetTest_94, LessComparesTwoIntegers_94) {

    EXPECT_TRUE(SparseSet::less(3, 5));

    EXPECT_FALSE(SparseSet::less(5, 3));

    EXPECT_FALSE(SparseSet::less(5, 5));

}
