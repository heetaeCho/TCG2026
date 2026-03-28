#include <gtest/gtest.h>

#include "sparse_set.h"



using namespace re2;



class SparseSetTest_92 : public ::testing::Test {

protected:

    void SetUp() override {

        sparse_set = new SparseSet(10);

    }



    void TearDown() override {

        delete sparse_set;

    }



    SparseSet* sparse_set;

};



TEST_F(SparseSetTest_92, InsertNewElement_92) {

    int value = 5;

    auto it = sparse_set->insert(value);

    EXPECT_TRUE(sparse_set->contains(value));

    EXPECT_EQ(*it, value);

}



TEST_F(SparseSetTest_92, InsertExistingElement_92) {

    int value = 5;

    sparse_set->insert_new(value);

    auto it = sparse_set->insert(value);

    EXPECT_TRUE(sparse_set->contains(value));

    EXPECT_EQ(*it, value);

}



TEST_F(SparseSetTest_92, ContainsAfterInsert_92) {

    int value = 3;

    sparse_set->insert(value);

    EXPECT_TRUE(sparse_set->contains(value));

}



TEST_F(SparseSetTest_92, DoesNotContainInitially_92) {

    int value = 7;

    EXPECT_FALSE(sparse_set->contains(value));

}



TEST_F(SparseSetTest_92, SizeAfterInsert_92) {

    sparse_set->insert(1);

    sparse_set->insert(2);

    EXPECT_EQ(sparse_set->size(), 2);

}



TEST_F(SparseSetTest_92, EmptyInitially_92) {

    EXPECT_TRUE(sparse_set->empty());

}



TEST_F(SparseSetTest_92, NotEmptyAfterInsert_92) {

    sparse_set->insert(1);

    EXPECT_FALSE(sparse_set->empty());

}



TEST_F(SparseSetTest_92, ResizeIncreasesCapacity_92) {

    int new_size = 20;

    sparse_set->resize(new_size);

    EXPECT_EQ(sparse_set->max_size(), new_size);

}



TEST_F(SparseSetTest_92, ClearRemovesAllElements_92) {

    sparse_set->insert(1);

    sparse_set->clear();

    EXPECT_TRUE(sparse_set->empty());

    EXPECT_EQ(sparse_set->size(), 0);

}



TEST_F(SparseSetTest_92, IteratorBeginEnd_92) {

    sparse_set->insert(1);

    sparse_set->insert(2);

    auto it = sparse_set->begin();

    int count = 0;

    for (; it != sparse_set->end(); ++it) {

        EXPECT_TRUE(sparse_set->contains(*it));

        count++;

    }

    EXPECT_EQ(count, 2);

}



TEST_F(SparseSetTest_92, InsertBoundaryCondition_92) {

    int max_size = sparse_set->max_size();

    for (int i = 0; i < max_size; ++i) {

        sparse_set->insert(i);

    }

    EXPECT_EQ(sparse_set->size(), max_size);

}



TEST_F(SparseSetTest_92, InsertBeyondMaxSize_92) {

    int max_size = sparse_set->max_size();

    for (int i = 0; i <= max_size; ++i) {

        sparse_set->insert(i);

    }

    EXPECT_EQ(sparse_set->size(), max_size + 1); // Assuming dynamic resizing

}
