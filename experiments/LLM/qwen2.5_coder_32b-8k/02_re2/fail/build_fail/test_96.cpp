#include <gtest/gtest.h>

#include "sparse_set.h"



namespace re2 {



class SparseSetTest_96 : public ::testing::Test {

protected:

    SparseSet set;

    SparseSet* setPtr;



    void SetUp() override {

        set = SparseSet();

        setPtr = &set;

    }



    void TearDown() override {

        // Cleanup if necessary

    }

};



TEST_F(SparseSetTest_96, DefaultConstructorInitializesEmpty_96) {

    EXPECT_EQ(set.size(), 0);

    EXPECT_TRUE(set.empty());

}



TEST_F(SparseSetTest_96, ConstructorWithMaxSizeInitializesCorrectly_96) {

    SparseSet setWithMax(10);

    EXPECT_EQ(setWithMax.max_size(), 10);

    EXPECT_EQ(setWithMax.size(), 0);

    EXPECT_TRUE(setWithMax.empty());

}



TEST_F(SparseSetTest_96, ResizeIncreasesCapacity_96) {

    set.resize(20);

    EXPECT_EQ(set.max_size(), 20);

}



TEST_F(SparseSetTest_96, InsertAddsElement_96) {

    auto it = set.insert(5);

    EXPECT_TRUE(set.contains(5));

    EXPECT_NE(it, set.end());

}



TEST_F(SparseSetTest_96, InsertNewAddsUniqueElement_96) {

    auto it = set.insert_new(10);

    EXPECT_TRUE(set.contains(10));

    EXPECT_NE(it, set.end());



    auto it2 = set.insert_new(10);

    EXPECT_EQ(it, it2); // Should return the same iterator for the existing element

}



TEST_F(SparseSetTest_96, InsertNewFailsForExistingElement_96) {

    set.insert(7);

    auto it = set.insert_new(7);

    EXPECT_NE(it, set.end());

    EXPECT_EQ(set.size(), 1); // Size should not increase as the element already exists

}



TEST_F(SparseSetTest_96, ClearEmptiesTheSet_96) {

    set.insert(3);

    set.clear();

    EXPECT_TRUE(set.empty());

    EXPECT_EQ(set.size(), 0);

}



TEST_F(SparseSetTest_96, ContainsReturnsFalseForNonexistentElement_96) {

    EXPECT_FALSE(set.contains(42));

}



TEST_F(SparseSetTest_96, BeginAndEndIterateOverElements_96) {

    set.insert(1);

    set.insert(3);

    set.insert(5);



    std::vector<int> expected = {1, 3, 5};

    int index = 0;

    for (auto it = set.begin(); it != set.end(); ++it) {

        EXPECT_EQ(expected[index++], *it);

    }

}



TEST_F(SparseSetTest_96, BoundaryConditionMaxSizeInsertion_96) {

    SparseSet boundarySet(1);

    boundarySet.insert(0);

    EXPECT_TRUE(boundarySet.contains(0));

    EXPECT_EQ(boundarySet.size(), 1);



    // Attempt to insert another element should not increase size

    boundarySet.insert(1);

    EXPECT_FALSE(boundarySet.contains(1));

    EXPECT_EQ(boundarySet.size(), 1);

}



TEST_F(SparseSetTest_96, BoundaryConditionResizeToSmallerSize_96) {

    set.resize(5);

    set.insert(0);

    set.insert(1);

    set.insert(2);



    set.resize(2);

    EXPECT_FALSE(set.contains(2));

    EXPECT_TRUE(set.contains(0));

    EXPECT_TRUE(set.contains(1));

    EXPECT_EQ(set.size(), 2);

}



} // namespace re2
