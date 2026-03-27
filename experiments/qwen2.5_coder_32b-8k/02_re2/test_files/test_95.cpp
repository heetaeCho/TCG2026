#include <gtest/gtest.h>

#include "re2/sparse_set.h"



using namespace re2;



class SparseSetTest_95 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any common objects here if needed

    }



    SparseSet sparseSet;

    SparseSet sparseSetWithMaxSize;

    

    SparseSetTest_95() : sparseSet(), sparseSetWithMaxSize(10) {}

};



TEST_F(SparseSetTest_95, DefaultConstructorInitializesCorrectly_95) {

    EXPECT_EQ(sparseSet.max_size(), 0);

    EXPECT_EQ(sparseSet.size(), 0);

}



TEST_F(SparseSetTest_95, ConstructorWithMaxSizeInitializesCorrectly_95) {

    EXPECT_EQ(sparseSetWithMaxSize.max_size(), 10);

    EXPECT_EQ(sparseSetWithMaxSize.size(), 0);

}



TEST_F(SparseSetTest_95, ResizeIncreasesMaxSizeAndClearsContents_95) {

    sparseSet.resize(5);

    EXPECT_EQ(sparseSet.max_size(), 5);

    EXPECT_EQ(sparseSet.size(), 0);



    sparseSet.insert(2);

    EXPECT_TRUE(sparseSet.contains(2));



    sparseSet.resize(10);

    EXPECT_EQ(sparseSet.max_size(), 10);

    EXPECT_FALSE(sparseSet.contains(2)); // Contents should be cleared

}



TEST_F(SparseSetTest_95, InsertAddsElementProperly_95) {

    sparseSetWithMaxSize.insert(3);

    EXPECT_TRUE(sparseSetWithMaxSize.contains(3));

    EXPECT_EQ(sparseSetWithMaxSize.size(), 1);



    sparseSetWithMaxSize.insert(7);

    EXPECT_TRUE(sparseSetWithMaxSize.contains(7));

    EXPECT_EQ(sparseSetWithMaxSize.size(), 2);

}



TEST_F(SparseSetTest_95, InsertNewAddsElementProperly_95) {

    auto it = sparseSetWithMaxSize.insert_new(3);

    EXPECT_TRUE(sparseSetWithMaxSize.contains(3));

    EXPECT_EQ(*it, 3);



    it = sparseSetWithMaxSize.insert_new(7);

    EXPECT_TRUE(sparseSetWithMaxSize.contains(7));

    EXPECT_EQ(*it, 7);

}



TEST_F(SparseSetTest_95, InsertNewDoesNotAddDuplicateElements_95) {

    auto it = sparseSetWithMaxSize.insert_new(3);

    EXPECT_TRUE(sparseSetWithMaxSize.contains(3));



    it = sparseSetWithMaxSize.insert_new(3); // Attempt to insert the same element again

    EXPECT_EQ(it, nullptr);

}



TEST_F(SparseSetTest_95, ContainsReturnsFalseForNonExistentElement_95) {

    EXPECT_FALSE(sparseSetWithMaxSize.contains(3));

}



TEST_F(SparseSetTest_95, ContainsReturnsTrueForExistingElement_95) {

    sparseSetWithMaxSize.insert(3);

    EXPECT_TRUE(sparseSetWithMaxSize.contains(3));

}



TEST_F(SparseSetTest_95, ClearRemovesAllElements_95) {

    sparseSetWithMaxSize.insert(2);

    sparseSetWithMaxSize.insert(4);

    sparseSetWithMaxSize.clear();



    EXPECT_EQ(sparseSetWithMaxSize.size(), 0);

    EXPECT_FALSE(sparseSetWithMaxSize.contains(2));

    EXPECT_FALSE(sparseSetWithMaxSize.contains(4));

}



TEST_F(SparseSetTest_95, BoundaryConditionsForInsert_95) {

    sparseSetWithMaxSize.insert(0);

    sparseSetWithMaxSize.insert(9);



    EXPECT_TRUE(sparseSetWithMaxSize.contains(0));

    EXPECT_TRUE(sparseSetWithMaxSize.contains(9));

}



TEST_F(SparseSetTest_95, InsertOutsideBoundsThrowsAssertionFailure_95) {

    ASSERT_DEATH({ sparseSetWithMaxSize.insert(10); }, "assertion failed");

    ASSERT_DEATH({ sparseSetWithMaxSize.insert(-1); }, "assertion failed");

}
