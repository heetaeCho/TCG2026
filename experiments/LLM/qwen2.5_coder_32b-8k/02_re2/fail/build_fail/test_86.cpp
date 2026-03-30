#include <gtest/gtest.h>

#include "re2/sparse_array.h"



namespace re2 {



class SparseArrayTest_86 : public ::testing::Test {

protected:

    using ValueType = int;

    SparseArray<ValueType> sparseArray;



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(SparseArrayTest_86, Constructor_Default_86) {

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_86, Constructor_MaxSize_86) {

    SparseArray<int> array(10);

    EXPECT_EQ(array.max_size(), 10);

}



TEST_F(SparseArrayTest_86, Constructor_Copy_86) {

    sparseArray.set(2, 42);

    SparseArray<int> copy(sparseArray);

    EXPECT_EQ(copy.get_existing(2), 42);

}



TEST_F(SparseArrayTest_86, Constructor_Move_86) {

    sparseArray.set(3, 50);

    SparseArray<int> moved(std::move(sparseArray));

    EXPECT_EQ(moved.get_existing(3), 50);

}



TEST_F(SparseArrayTest_86, Operator_Assignment_Copy_86) {

    sparseArray.set(1, 100);

    SparseArray<int> other;

    other = sparseArray;

    EXPECT_EQ(other.get_existing(1), 100);

}



TEST_F(SparseArrayTest_86, Operator_Assignment_Move_86) {

    sparseArray.set(4, 200);

    SparseArray<int> other;

    other = std::move(sparseArray);

    EXPECT_EQ(other.get_existing(4), 200);

}



TEST_F(SparseArrayTest_86, Resize_IncreaseSize_86) {

    sparseArray.resize(5);

    EXPECT_EQ(sparseArray.max_size(), 5);

}



TEST_F(SparseArrayTest_86, Resize_DecreaseSize_86) {

    SparseArray<int> array(10);

    array.resize(5);

    EXPECT_EQ(array.max_size(), 5);

}



TEST_F(SparseArrayTest_86, HasIndex_Exists_86) {

    sparseArray.set(2, 42);

    EXPECT_TRUE(sparseArray.has_index(2));

}



TEST_F(SparseArrayTest_86, HasIndex_NotExists_86) {

    EXPECT_FALSE(sparseArray.has_index(3));

}



TEST_F(SparseArrayTest_86, Size_Empty_86) {

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_86, Size_AfterSet_86) {

    sparseArray.set(2, 42);

    EXPECT_EQ(sparseArray.size(), 1);

}



TEST_F(SparseArrayTest_86, Clear_AllElements_86) {

    sparseArray.set(2, 42);

    sparseArray.set(3, 50);

    sparseArray.clear();

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_86, Set_NewIndex_86) {

    auto it = sparseArray.set_new(1, 75);

    EXPECT_EQ(*it, 75);

    EXPECT_TRUE(sparseArray.has_index(1));

}



TEST_F(SparseArrayTest_86, Set_ExistingIndex_86) {

    sparseArray.set(2, 42);

    auto it = sparseArray.set_existing(2, 90);

    EXPECT_EQ(*it, 90);

}



TEST_F(SparseArrayTest_86, Get_ExistingIndex_86) {

    sparseArray.set(3, 50);

    EXPECT_EQ(sparseArray.get_existing(3), 50);

}



} // namespace re2
