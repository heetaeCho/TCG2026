#include <gtest/gtest.h>

#include "sparse_set.h"



namespace re2 {



class SparseSetTest_91 : public ::testing::Test {

protected:

    SparseSet sparse_set;



    void SetUp() override {

        // Initialize any necessary state before each test

        sparse_set.clear();

    }



    void TearDown() override {

        // Clean up any resources after each test

    }

};



TEST_F(SparseSetTest_91, ClearEmptiesSet_91) {

    sparse_set.insert(42);

    EXPECT_FALSE(sparse_set.empty());

    sparse_set.clear();

    EXPECT_TRUE(sparse_set.empty());

}



TEST_F(SparseSetTest_91, InsertIncreasesSize_91) {

    int initial_size = sparse_set.size();

    sparse_set.insert(42);

    EXPECT_EQ(sparse_set.size(), initial_size + 1);

}



TEST_F(SparseSetTest_91, InsertNewIncreasesSize_91) {

    int initial_size = sparse_set.size();

    sparse_set.insert_new(42);

    EXPECT_EQ(sparse_set.size(), initial_size + 1);

}



TEST_F(SparseSetTest_91, InsertSameElementDoesNotIncreaseSize_91) {

    sparse_set.insert(42);

    int size_after_first_insert = sparse_set.size();

    sparse_set.insert(42);

    EXPECT_EQ(sparse_set.size(), size_after_first_insert);

}



TEST_F(SparseSetTest_91, ContainsReturnsTrueForInsertedElement_91) {

    sparse_set.insert(42);

    EXPECT_TRUE(sparse_set.contains(42));

}



TEST_F(SparseSetTest_91, ContainsReturnsFalseForNonInsertedElement_91) {

    EXPECT_FALSE(sparse_set.contains(42));

}



TEST_F(SparseSetTest_91, EmptyInitially_91) {

    EXPECT_TRUE(sparse_set.empty());

}



TEST_F(SparseSetTest_91, SizeInitiallyZero_91) {

    EXPECT_EQ(sparse_set.size(), 0);

}



TEST_F(SparseSetTest_91, ResizeIncreasesMaxSize_91) {

    int initial_max_size = sparse_set.max_size();

    sparse_set.resize(initial_max_size + 10);

    EXPECT_GT(sparse_set.max_size(), initial_max_size);

}



TEST_F(SparseSetTest_91, LessComparisonWorksCorrectly_91) {

    EXPECT_TRUE(SparseSet::less(3, 5));

    EXPECT_FALSE(SparseSet::less(5, 3));

    EXPECT_FALSE(SparseSet::less(3, 3));

}



}  // namespace re2
