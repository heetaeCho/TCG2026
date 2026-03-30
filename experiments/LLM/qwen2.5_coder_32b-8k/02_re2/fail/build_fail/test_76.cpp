#include <gtest/gtest.h>

#include "sparse_array.h"



using namespace re2;



class SparseArrayTest_76 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_76, SetNewElement_76) {

    int index = 0;

    int value = 42;

    auto it = sparseArray.set(index, value);

    EXPECT_EQ(*it, value);

}



TEST_F(SparseArrayTest_76, SetExistingElement_76) {

    int index = 0;

    int initialValue = 42;

    int newValue = 100;

    sparseArray.set(index, initialValue);

    auto it = sparseArray.set(index, newValue);

    EXPECT_EQ(*it, newValue);

}



TEST_F(SparseArrayTest_76, SetMultipleElements_76) {

    int index1 = 0;

    int value1 = 42;

    int index2 = 1;

    int value2 = 100;



    sparseArray.set(index1, value1);

    sparseArray.set(index2, value2);



    EXPECT_EQ(*sparseArray.begin(), value1);

    EXPECT_EQ(*(sparseArray.begin() + 1), value2);

}



TEST_F(SparseArrayTest_76, SetBeyondCurrentSize_76) {

    int index = 5;

    int value = 42;

    sparseArray.resize(10); // Resize to ensure the index is within bounds

    auto it = sparseArray.set(index, value);

    EXPECT_EQ(*it, value);

}



TEST_F(SparseArrayTest_76, SetNegativeIndex_76) {

    int index = -1;

    int value = 42;

    EXPECT_THROW(sparseArray.set(index, value), std::exception);

}



TEST_F(SparseArrayTest_76, ResizeAndSetElement_76) {

    int newSize = 5;

    sparseArray.resize(newSize);

    int index = 3;

    int value = 100;

    auto it = sparseArray.set(index, value);

    EXPECT_EQ(*it, value);

}



TEST_F(SparseArrayTest_76, ResizeToSmallerAndSetElement_76) {

    int initialSize = 5;

    sparseArray.resize(initialSize);

    int smallerSize = 3;

    sparseArray.resize(smallerSize);



    int index = 2; // Valid within the new size

    int value = 100;



    EXPECT_THROW(sparseArray.set(index, value), std::exception);

}



TEST_F(SparseArrayTest_76, CheckHasIndexAfterSet_76) {

    int index = 0;

    int value = 42;

    sparseArray.set(index, value);

    EXPECT_TRUE(sparseArray.has_index(index));

}



TEST_F(SparseArrayTest_76, CheckHasIndexForNonExistingElement_76) {

    int index = 10; // Assuming initial size is less than 10

    EXPECT_FALSE(sparseArray.has_index(index));

}
