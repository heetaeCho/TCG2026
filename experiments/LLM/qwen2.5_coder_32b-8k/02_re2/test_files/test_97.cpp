#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sparse_set.h"



namespace re2 {



class SparseSetTest_97 : public ::testing::Test {

protected:

    SparseSet set;

};



TEST_F(SparseSetTest_97, DefaultConstructorCreatesEmptySet_97) {

    EXPECT_EQ(set.size(), 0);

    EXPECT_TRUE(set.empty());

}



TEST_F(SparseSetTest_97, ResizeIncreasesMaxSize_97) {

    int new_max_size = 10;

    set.resize(new_max_size);

    EXPECT_GE(set.max_size(), new_max_size);

}



TEST_F(SparseSetTest_97, InsertAddsElementToSet_97) {

    int element = 5;

    auto it = set.insert(element);

    EXPECT_EQ(*it, element);

    EXPECT_TRUE(set.contains(element));

}



TEST_F(SparseSetTest_97, InsertNewAddsUniqueElement_97) {

    int element = 5;

    auto it = set.insert_new(element);

    EXPECT_EQ(*it, element);

    EXPECT_TRUE(set.contains(element));



    // Attempting to insert the same element again should not add it

    it = set.insert_new(element);

    EXPECT_EQ(it, set.end());

}



TEST_F(SparseSetTest_97, ContainsReturnsTrueForExistingElement_97) {

    int element = 5;

    set.insert(element);

    EXPECT_TRUE(set.contains(element));

}



TEST_F(SparseSetTest_97, ContainsReturnsFalseForNonexistentElement_97) {

    EXPECT_FALSE(set.contains(5));

}



TEST_F(SparseSetTest_97, ClearRemovesAllElements_97) {

    int element1 = 5;

    int element2 = 10;

    set.insert(element1);

    set.insert(element2);

    set.clear();

    EXPECT_EQ(set.size(), 0);

    EXPECT_FALSE(set.contains(element1));

    EXPECT_FALSE(set.contains(element2));

}



TEST_F(SparseSetTest_97, BeginAndEndIterateOverElements_97) {

    int element1 = 5;

    int element2 = 10;

    set.insert(element1);

    set.insert(element2);



    std::vector<int> elements;

    for (auto it = set.begin(); it != set.end(); ++it) {

        elements.push_back(*it);

    }

    EXPECT_EQ(elements.size(), 2);

    EXPECT_TRUE(std::find(elements.begin(), elements.end(), element1) != elements.end());

    EXPECT_TRUE(std::find(elements.begin(), elements.end(), element2) != elements.end());

}



TEST_F(SparseSetTest_97, LessFunctionComparesIntegersCorrectly_97) {

    EXPECT_TRUE(SparseSet::less(3, 5));

    EXPECT_FALSE(SparseSet::less(5, 3));

    EXPECT_FALSE(SparseSet::less(3, 3));

}



} // namespace re2
