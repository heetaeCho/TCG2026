#include <gtest/gtest.h>

#include "sparse_array.h"



using namespace re2;



class SparseArrayTest_81 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_81, DefaultConstructorInitializesSizeToZero_81) {

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_81, ParameterizedConstructorSetsMaxSizeCorrectly_81) {

    SparseArray<int> sparseArrayWithSize(10);

    EXPECT_EQ(sparseArrayWithSize.max_size(), 10);

}



TEST_F(SparseArrayTest_81, CopyConstructorCreatesIdenticalSparseArray_81) {

    sparseArray.set(5, 42);

    SparseArray<int> copiedArray = sparseArray;

    EXPECT_TRUE(copiedArray.has_index(5));

    EXPECT_EQ(copiedArray.get_existing(5), 42);

}



TEST_F(SparseArrayTest_81, MoveConstructorTransfersDataCorrectly_81) {

    sparseArray.set(5, 42);

    SparseArray<int> movedArray = std::move(sparseArray);

    EXPECT_TRUE(movedArray.has_index(5));

    EXPECT_EQ(movedArray.get_existing(5), 42);

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_81, AssignmentOperatorCopiesDataCorrectly_81) {

    sparseArray.set(5, 42);

    SparseArray<int> assignedArray;

    assignedArray = sparseArray;

    EXPECT_TRUE(assignedArray.has_index(5));

    EXPECT_EQ(assignedArray.get_existing(5), 42);

}



TEST_F(SparseArrayTest_81, MoveAssignmentOperatorTransfersDataCorrectly_81) {

    sparseArray.set(5, 42);

    SparseArray<int> movedArray;

    movedArray = std::move(sparseArray);

    EXPECT_TRUE(movedArray.has_index(5));

    EXPECT_EQ(movedArray.get_existing(5), 42);

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_81, ResizeIncreasesMaxSizeCorrectly_81) {

    sparseArray.resize(20);

    EXPECT_EQ(sparseArray.max_size(), 20);

}



TEST_F(SparseArrayTest_81, HasIndexReturnsFalseForNonexistentIndex_81) {

    EXPECT_FALSE(sparseArray.has_index(5));

}



TEST_F(SparseArrayTest_81, SetNewInsertsValueCorrectly_81) {

    auto it = sparseArray.set_new(5, 42);

    EXPECT_TRUE(sparseArray.has_index(5));

    EXPECT_EQ(sparseArray.get_existing(5), 42);

    EXPECT_EQ(it->value, 42);

}



TEST_F(SparseArrayTest_81, SetExistingUpdatesValueCorrectly_81) {

    sparseArray.set_new(5, 42);

    auto it = sparseArray.set_existing(5, 99);

    EXPECT_TRUE(sparseArray.has_index(5));

    EXPECT_EQ(sparseArray.get_existing(5), 99);

    EXPECT_EQ(it->value, 99);

}



TEST_F(SparseArrayTest_81, SetInsertsValueCorrectly_81) {

    auto it = sparseArray.set(5, 42);

    EXPECT_TRUE(sparseArray.has_index(5));

    EXPECT_EQ(sparseArray.get_existing(5), 42);

    EXPECT_EQ(it->value, 42);



    it = sparseArray.set(5, 99);

    EXPECT_TRUE(sparseArray.has_index(5));

    EXPECT_EQ(sparseArray.get_existing(5), 99);

    EXPECT_EQ(it->value, 99);

}



TEST_F(SparseArrayTest_81, ClearRemovesAllEntries_81) {

    sparseArray.set_new(5, 42);

    sparseArray.clear();

    EXPECT_FALSE(sparseArray.has_index(5));

    EXPECT_EQ(sparseArray.size(), 0);

}
