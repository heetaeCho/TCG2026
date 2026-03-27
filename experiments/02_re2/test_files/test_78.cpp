#include <gtest/gtest.h>

#include "re2/sparse_array.h"



using namespace re2;



class SparseArrayTest_78 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_78, SetExisting_ValidIndex_ReturnsIterator_78) {

    sparseArray.set_new(0, 42);

    auto it = sparseArray.set_existing(0, 100);

    EXPECT_NE(it, sparseArray.end());

}



TEST_F(SparseArrayTest_78, SetExisting_IndexNotFound_ReturnsEnd_78) {

    auto it = sparseArray.set_existing(0, 100);

    EXPECT_EQ(it, sparseArray.end());

}



TEST_F(SparseArrayTest_78, SetExisting_UpdateValue_CheckGetValue_78) {

    sparseArray.set_new(0, 42);

    sparseArray.set_existing(0, 100);

    EXPECT_EQ(sparseArray.get_existing(0), 100);

}



TEST_F(SparseArrayTest_78, SetExisting_BoundaryCondition_MaxSize_78) {

    SparseArray<int> largeSparseArray(100);

    largeSparseArray.set_new(99, 42);

    auto it = largeSparseArray.set_existing(99, 100);

    EXPECT_NE(it, largeSparseArray.end());

}



TEST_F(SparseArrayTest_78, SetExisting_OutOfBounds_ReturnsEnd_78) {

    SparseArray<int> smallSparseArray(5);

    auto it = smallSparseArray.set_existing(10, 100);

    EXPECT_EQ(it, smallSparseArray.end());

}
