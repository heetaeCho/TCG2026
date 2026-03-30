#include <gtest/gtest.h>

#include "re2/sparse_set.h"



using namespace re2;



class SparseSetTest_90 : public ::testing::Test {

protected:

    void SetUp() override {

        sparse_set = new SparseSetT();

    }



    void TearDown() override {

        delete sparse_set;

    }



    SparseSetT* sparse_set;

};



TEST_F(SparseSetTest_90, DefaultConstructorInitializesEmptySet_90) {

    EXPECT_EQ(sparse_set->max_size(), 0);

    EXPECT_TRUE(sparse_set->empty());

}



TEST_F(SparseSetTest_90, ConstructorWithMaxSizeInitializesCorrectly_90) {

    SparseSetT set(10);

    EXPECT_EQ(set.max_size(), 10);

    EXPECT_TRUE(set.empty());

}



TEST_F(SparseSetTest_90, ResizeIncreasesMaxSize_90) {

    sparse_set->resize(20);

    EXPECT_EQ(sparse_set->max_size(), 20);

}



TEST_F(SparseSetTest_90, ResizeDecreasesMaxSizePreservesContents_90) {

    sparse_set->resize(15);

    sparse_set->insert(5);

    sparse_set->resize(10);

    EXPECT_TRUE(sparse_set->contains(5));

}



TEST_F(SparseSetTest_90, InsertNewAddsElement_90) {

    sparse_set->resize(10);

    auto it = sparse_set->insert_new(3);

    EXPECT_EQ(*it, 3);

    EXPECT_TRUE(sparse_set->contains(3));

}



TEST_F(SparseSetTest_90, InsertDoesNotAddExistingElementTwice_90) {

    sparse_set->resize(10);

    sparse_set->insert_new(3);

    auto it = sparse_set->insert(3);

    EXPECT_EQ(*it, 3);

}



TEST_F(SparseSetTest_90, ClearRemovesAllElements_90) {

    sparse_set->resize(10);

    sparse_set->insert_new(3);

    sparse_set->clear();

    EXPECT_FALSE(sparse_set->contains(3));

    EXPECT_TRUE(sparse_set->empty());

}



TEST_F(SparseSetTest_90, ContainsReturnsTrueForInsertedElement_90) {

    sparse_set->resize(10);

    sparse_set->insert_new(7);

    EXPECT_TRUE(sparse_set->contains(7));

}



TEST_F(SparseSetTest_90, ContainsReturnsFalseForNonInsertedElement_90) {

    sparse_set->resize(10);

    EXPECT_FALSE(sparse_set->contains(7));

}



TEST_F(SparseSetTest_90, BeginEndIterateOverElements_90) {

    sparse_set->resize(10);

    sparse_set->insert_new(3);

    sparse_set->insert_new(5);

    int count = 0;

    for (auto it = sparse_set->begin(); it != sparse_set->end(); ++it) {

        EXPECT_TRUE(sparse_set->contains(*it));

        count++;

    }

    EXPECT_EQ(count, 2);

}



TEST_F(SparseSetTest_90, IteratorPointsToInsertedElements_90) {

    sparse_set->resize(10);

    auto it = sparse_set->insert_new(3);

    EXPECT_EQ(*it, 3);

}
