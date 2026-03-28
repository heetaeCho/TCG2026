#include <gtest/gtest.h>

#include "sparse_set.h"



using namespace re2;



class SparseSetTest_585 : public ::testing::Test {

protected:

    void SetUp() override {

        sparseSet = new SparseSet(10);

    }



    void TearDown() override {

        delete sparseSet;

    }



    SparseSet* sparseSet;

};



TEST_F(SparseSetTest_585, DefaultConstructorInitializesCorrectly_585) {

    SparseSet defaultConstructedSet;

    EXPECT_EQ(defaultConstructedSet.max_size(), 0);

}



TEST_F(SparseSetTest_585, ConstructorWithMaxSizeInitializesCorrectly_585) {

    EXPECT_EQ(sparseSet->max_size(), 10);

}



TEST_F(SparseSetTest_585, ResizeIncreasesCapacity_585) {

    sparseSet->resize(20);

    EXPECT_EQ(sparseSet->max_size(), 20);

}



TEST_F(SparseSetTest_585, InsertAddsElementCorrectly_585) {

    auto it = sparseSet->insert(5);

    EXPECT_TRUE(sparseSet->contains(5));

}



TEST_F(SparseSetTest_585, InsertNewAddsUniqueElement_585) {

    sparseSet->insert_new(3);

    auto it = sparseSet->insert_new(3);

    EXPECT_EQ(it, sparseSet->end()); // Should return end if element already exists

}



TEST_F(SparseSetTest_585, ContainsReturnsTrueForExistingElement_585) {

    sparseSet->insert(7);

    EXPECT_TRUE(sparseSet->contains(7));

}



TEST_F(SparseSetTest_585, ContainsReturnsFalseForNonexistentElement_585) {

    EXPECT_FALSE(sparseSet->contains(12));

}



TEST_F(SparseSetTest_585, ClearRemovesAllElements_585) {

    sparseSet->insert(4);

    sparseSet->clear();

    EXPECT_EQ(sparseSet->size(), 0);

    EXPECT_TRUE(sparseSet->empty());

}



TEST_F(SparseSetTest_585, BeginEndIterateCorrectly_585) {

    sparseSet->insert(1);

    sparseSet->insert(2);

    auto it = sparseSet->begin();

    EXPECT_NE(it, sparseSet->end());

    ++it;

    EXPECT_NE(it, sparseSet->end());

    ++it;

    EXPECT_EQ(it, sparseSet->end());

}



TEST_F(SparseSetTest_585, MaxSizeReturnsCorrectValue_585) {

    EXPECT_EQ(sparseSet->max_size(), 10);

}



TEST_F(SparseSetTest_585, SizeReflectsNumberOfElements_585) {

    sparseSet->insert(6);

    EXPECT_EQ(sparseSet->size(), 1);

    sparseSet->clear();

    EXPECT_EQ(sparseSet->size(), 0);

}



TEST_F(SparseSetTest_585, EmptyReturnsTrueWhenNoElements_585) {

    EXPECT_TRUE(sparseSet->empty());

    sparseSet->insert(9);

    EXPECT_FALSE(sparseSet->empty());

}
