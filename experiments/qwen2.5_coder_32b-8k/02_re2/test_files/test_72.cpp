#include <gtest/gtest.h>

#include "re2/sparse_array.h"



namespace re2 {



class SparseArrayTest_72 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;



    void SetUp() override {

        sparseArray.resize(10);

    }

};



TEST_F(SparseArrayTest_72, DefaultConstructorCreatesEmptyArray_72) {

    SparseArray<int> defaultSparseArray;

    EXPECT_EQ(defaultSparseArray.size(), 0);

    EXPECT_TRUE(defaultSparseArray.empty());

}



TEST_F(SparseArrayTest_72, ResizeIncreasesMaxSize_72) {

    sparseArray.resize(20);

    EXPECT_EQ(sparseArray.max_size(), 20);

}



TEST_F(SparseArrayTest_72, SetNewAddsElement_72) {

    auto it = sparseArray.set_new(3, 42);

    EXPECT_TRUE(sparseArray.has_index(3));

    EXPECT_EQ(*it, 42);

}



TEST_F(SparseArrayTest_72, SetExistingUpdatesElement_72) {

    sparseArray.set_new(3, 42);

    auto it = sparseArray.set_existing(3, 99);

    EXPECT_TRUE(sparseArray.has_index(3));

    EXPECT_EQ(*it, 99);

}



TEST_F(SparseArrayTest_72, SetAddsElementIfNotExists_72) {

    auto it = sparseArray.set(3, 42);

    EXPECT_TRUE(sparseArray.has_index(3));

    EXPECT_EQ(*it, 42);



    it = sparseArray.set(3, 99);

    EXPECT_TRUE(sparseArray.has_index(3));

    EXPECT_EQ(*it, 99);

}



TEST_F(SparseArrayTest_72, GetExistingThrowsIfIndexNotFound_72) {

    sparseArray.set_new(3, 42);

    EXPECT_THROW(sparseArray.get_existing(5), std::exception);

}



TEST_F(SparseArrayTest_72, BeginAndEndIterateOverElements_72) {

    sparseArray.set_new(1, 10);

    sparseArray.set_new(3, 30);

    sparseArray.set_new(5, 50);



    auto it = sparseArray.begin();

    EXPECT_EQ(*it, 10);

    ++it;

    EXPECT_EQ(*it, 30);

    ++it;

    EXPECT_EQ(*it, 50);

    ++it;

    EXPECT_EQ(it, sparseArray.end());

}



TEST_F(SparseArrayTest_72, ClearRemovesAllElements_72) {

    sparseArray.set_new(1, 10);

    sparseArray.set_new(3, 30);

    sparseArray.clear();

    EXPECT_TRUE(sparseArray.empty());

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_72, HasIndexReturnsTrueIfElementExists_72) {

    sparseArray.set_new(1, 10);

    EXPECT_TRUE(sparseArray.has_index(1));

}



TEST_F(SparseArrayTest_72, HasIndexReturnsFalseIfElementDoesNotExist_72) {

    EXPECT_FALSE(sparseArray.has_index(1));

}



}  // namespace re2
