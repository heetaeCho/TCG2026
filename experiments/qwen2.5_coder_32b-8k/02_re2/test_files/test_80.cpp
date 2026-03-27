#include <gtest/gtest.h>

#include "sparse_array.h"



namespace re2 {



class SparseArrayTest_80 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_80, DefaultConstructorInitializesEmpty_80) {

    EXPECT_EQ(sparseArray.size(), 0);

    EXPECT_TRUE(sparseArray.empty());

}



TEST_F(SparseArrayTest_80, ConstructorWithMaxSizeCreatesCorrectlySizedArrays_80) {

    SparseArray<int> array(10);

    EXPECT_EQ(array.max_size(), 10);

    EXPECT_EQ(array.size(), 0);

}



TEST_F(SparseArrayTest_80, CopyConstructorCopiesData_80) {

    SparseArray<int> original(5);

    for (int i = 0; i < 5; ++i) {

        original.set(i, i * 10);

    }

    SparseArray<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());

    EXPECT_EQ(copy.max_size(), original.max_size());

    for (int i = 0; i < 5; ++i) {

        EXPECT_TRUE(copy.has_index(i));

        EXPECT_EQ(copy.get_existing(i), original.get_existing(i));

    }

}



TEST_F(SparseArrayTest_80, MoveConstructorTransfersData_80) {

    SparseArray<int> original(5);

    for (int i = 0; i < 5; ++i) {

        original.set(i, i * 10);

    }

    SparseArray<int> moved(std::move(original));

    EXPECT_EQ(moved.size(), 5);

    EXPECT_TRUE(original.empty()); // Original should be empty after move

    for (int i = 0; i < 5; ++i) {

        EXPECT_TRUE(moved.has_index(i));

        EXPECT_EQ(moved.get_existing(i), i * 10);

    }

}



TEST_F(SparseArrayTest_80, AssignmentOperatorCopiesData_80) {

    SparseArray<int> original(5);

    for (int i = 0; i < 5; ++i) {

        original.set(i, i * 10);

    }

    SparseArray<int> copy;

    copy = original;

    EXPECT_EQ(copy.size(), original.size());

    EXPECT_EQ(copy.max_size(), original.max_size());

    for (int i = 0; i < 5; ++i) {

        EXPECT_TRUE(copy.has_index(i));

        EXPECT_EQ(copy.get_existing(i), original.get_existing(i));

    }

}



TEST_F(SparseArrayTest_80, MoveAssignmentOperatorTransfersData_80) {

    SparseArray<int> original(5);

    for (int i = 0; i < 5; ++i) {

        original.set(i, i * 10);

    }

    SparseArray<int> moved;

    moved = std::move(original);

    EXPECT_EQ(moved.size(), 5);

    EXPECT_TRUE(original.empty()); // Original should be empty after move

    for (int i = 0; i < 5; ++i) {

        EXPECT_TRUE(moved.has_index(i));

        EXPECT_EQ(moved.get_existing(i), i * 10);

    }

}



TEST_F(SparseArrayTest_80, ResizeIncreasesMaxSize_80) {

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_80, SetAddsNewElements_80) {

    auto it = sparseArray.set(0, 100);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(sparseArray.get_existing(0), 100);

    EXPECT_EQ(*it, 100);

}



TEST_F(SparseArrayTest_80, SetUpdatesExistingElements_80) {

    sparseArray.set(0, 100);

    auto it = sparseArray.set(0, 200);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(sparseArray.get_existing(0), 200);

    EXPECT_EQ(*it, 200);

}



TEST_F(SparseArrayTest_80, ClearRemovesAllElements_80) {

    sparseArray.set(0, 100);

    sparseArray.clear();

    EXPECT_TRUE(sparseArray.empty());

    EXPECT_EQ(sparseArray.size(), 0);

    EXPECT_FALSE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_80, HasIndexReturnsTrueForExistingElements_80) {

    sparseArray.set(0, 100);

    EXPECT_TRUE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_80, HasIndexReturnsFalseForNonexistentElements_80) {

    EXPECT_FALSE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_80, IteratorsIterateOverAllElements_80) {

    for (int i = 0; i < 5; ++i) {

        sparseArray.set(i, i * 10);

    }

    int count = 0;

    for (auto it = sparseArray.begin(); it != sparseArray.end(); ++it) {

        EXPECT_EQ(*it, count * 10);

        ++count;

    }

    EXPECT_EQ(count, 5);

}



TEST_F(SparseArrayTest_80, SetNewAddsElements_80) {

    auto it = sparseArray.set_new(0, 100);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(*it, 100);

}



TEST_F(SparseArrayTest_80, SetExistingUpdatesElements_80) {

    sparseArray.set(0, 100);

    auto it = sparseArray.set_existing(0, 200);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(*it, 200);

}



TEST_F(SparseArrayTest_80, GetExistingThrowsForNonexistentElements_80) {

    EXPECT_THROW(sparseArray.get_existing(0), std::exception);

}



} // namespace re2
