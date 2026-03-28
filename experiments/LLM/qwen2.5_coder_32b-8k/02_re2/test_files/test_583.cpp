#include <gtest/gtest.h>

#include "re2/sparse_array.h"



namespace re2 {



class SparseArrayTest : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

    SparseArray<int> sparseArrayWithSize;



    void SetUp() override {

        sparseArray = SparseArray<int>();

        sparseArrayWithSize = SparseArray<int>(10);

    }

};



TEST_F(SparseArrayTest_583, DefaultConstructorInitializesEmpty_583) {

    EXPECT_EQ(sparseArray.size(), 0);

    EXPECT_TRUE(sparseArray.empty());

}



TEST_F(SparseArrayTest_583, ParameterizedConstructorSetsMaxSize_583) {

    EXPECT_EQ(sparseArrayWithSize.max_size(), 10);

    EXPECT_EQ(sparseArrayWithSize.size(), 0);

    EXPECT_TRUE(sparseArrayWithSize.empty());

}



TEST_F(SparseArrayTest_583, CopyConstructorCreatesIdenticalSparseArray_583) {

    sparseArrayWithSize.set(0, 42);

    SparseArray<int> copiedArray = sparseArrayWithSize;

    EXPECT_EQ(copiedArray.size(), 1);

    EXPECT_TRUE(copiedArray.has_index(0));

    EXPECT_EQ(copiedArray.get_existing(0), 42);

}



TEST_F(SparseArrayTest_583, MoveConstructorTransfersOwnership_583) {

    sparseArrayWithSize.set(0, 42);

    SparseArray<int> movedArray = std::move(sparseArrayWithSize);

    EXPECT_EQ(movedArray.size(), 1);

    EXPECT_TRUE(movedArray.has_index(0));

    EXPECT_EQ(movedArray.get_existing(0), 42);

    EXPECT_EQ(sparseArrayWithSize.size(), 0);

    EXPECT_TRUE(sparseArrayWithSize.empty());

}



TEST_F(SparseArrayTest_583, AssignmentOperatorCopiesContents_583) {

    sparseArrayWithSize.set(0, 42);

    SparseArray<int> anotherArray;

    anotherArray = sparseArrayWithSize;

    EXPECT_EQ(anotherArray.size(), 1);

    EXPECT_TRUE(anotherArray.has_index(0));

    EXPECT_EQ(anotherArray.get_existing(0), 42);

}



TEST_F(SparseArrayTest_583, MoveAssignmentOperatorTransfersOwnership_583) {

    sparseArrayWithSize.set(0, 42);

    SparseArray<int> anotherArray;

    anotherArray = std::move(sparseArrayWithSize);

    EXPECT_EQ(anotherArray.size(), 1);

    EXPECT_TRUE(anotherArray.has_index(0));

    EXPECT_EQ(anotherArray.get_existing(0), 42);

    EXPECT_EQ(sparseArrayWithSize.size(), 0);

    EXPECT_TRUE(sparseArrayWithSize.empty());

}



TEST_F(SparseArrayTest_583, ResizeIncreasesMaxSize_583) {

    sparseArray.resize(10);

    EXPECT_EQ(sparseArray.max_size(), 10);

}



TEST_F(SparseArrayTest_583, HasIndexReturnsTrueForExistingIndex_583) {

    sparseArray.set(0, 42);

    EXPECT_TRUE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_583, HasIndexReturnsFalseForNonexistentIndex_583) {

    EXPECT_FALSE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_583, SetInsertsNewValue_583) {

    sparseArray.set(0, 42);

    EXPECT_EQ(sparseArray.size(), 1);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(sparseArray.get_existing(0), 42);

}



TEST_F(SparseArrayTest_583, SetUpdatesExistingValue_583) {

    sparseArray.set(0, 42);

    sparseArray.set(0, 84);

    EXPECT_EQ(sparseArray.size(), 1);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(sparseArray.get_existing(0), 84);

}



TEST_F(SparseArrayTest_583, SetNewInsertsValue_583) {

    sparseArray.set_new(0, 42);

    EXPECT_EQ(sparseArray.size(), 1);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(sparseArray.get_existing(0), 42);

}



TEST_F(SparseArrayTest_583, SetExistingUpdatesValue_583) {

    sparseArray.set(0, 42);

    sparseArray.set_existing(0, 84);

    EXPECT_EQ(sparseArray.size(), 1);

    EXPECT_TRUE(sparseArray.has_index(0));

    EXPECT_EQ(sparseArray.get_existing(0), 84);

}



TEST_F(SparseArrayTest_583, ClearRemovesAllValues_583) {

    sparseArray.set(0, 42);

    sparseArray.clear();

    EXPECT_EQ(sparseArray.size(), 0);

    EXPECT_TRUE(sparseArray.empty());

    EXPECT_FALSE(sparseArray.has_index(0));

}



TEST_F(SparseArrayTest_583, BeginAndEndIterateOverValues_583) {

    sparseArray.set(0, 42);

    sparseArray.set(1, 84);

    auto it = sparseArray.begin();

    EXPECT_EQ(it->value, 42);

    ++it;

    EXPECT_EQ(it->value, 84);

    ++it;

    EXPECT_EQ(it, sparseArray.end());

}



TEST_F(SparseArrayTest_583, SizeReflectsNumberOfElements_583) {

    sparseArray.set(0, 42);

    sparseArray.set(1, 84);

    EXPECT_EQ(sparseArray.size(), 2);

}



TEST_F(SparseArrayTest_583, EmptyReturnsTrueForNoElements_583) {

    EXPECT_TRUE(sparseArray.empty());

}



TEST_F(SparseArrayTest_583, EmptyReturnsFalseForNonEmptyArray_583) {

    sparseArray.set(0, 42);

    EXPECT_FALSE(sparseArray.empty());

}



} // namespace re2
