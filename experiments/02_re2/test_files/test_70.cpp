#include <gtest/gtest.h>

#include "sparse_array.h"



using namespace re2;



class SparseArrayTest_70 : public ::testing::Test {

protected:

    SparseArray<int> sparseArray;

};



TEST_F(SparseArrayTest_70, DefaultConstructorInitializesSizeToZero_70) {

    EXPECT_EQ(sparseArray.size(), 0);

}



TEST_F(SparseArrayTest_70, ParameterizedConstructorSetsCorrectMaxSize_70) {

    SparseArray<int> sparseArrayWithSize(10);

    EXPECT_EQ(sparseArrayWithSize.max_size(), 10);

}



TEST_F(SparseArrayTest_70, ResizeIncreasesMaxSize_70) {

    sparseArray.resize(20);

    EXPECT_GE(sparseArray.max_size(), 20);

}



TEST_F(SparseArrayTest_70, SetNewAddsElementAndIncreasesSize_70) {

    sparseArray.set_new(5, 10);

    EXPECT_TRUE(sparseArray.has_index(5));

    EXPECT_EQ(sparseArray.size(), 1);

}



TEST_F(SparseArrayTest_70, SetExistingUpdatesElementWithoutChangingSize_70) {

    sparseArray.set_new(5, 10);

    sparseArray.set_existing(5, 20);

    EXPECT_TRUE(sparseArray.has_index(5));

    EXPECT_EQ(sparseArray.size(), 1);

}



TEST_F(SparseArrayTest_70, GetExistingReturnsCorrectValue_70) {

    sparseArray.set_new(5, 10);

    EXPECT_EQ(sparseArray.get_existing(5), 10);

}



TEST_F(SparseArrayTest_70, ClearRemovesAllElementsAndResetsSize_70) {

    sparseArray.set_new(5, 10);

    sparseArray.clear();

    EXPECT_EQ(sparseArray.size(), 0);

    EXPECT_FALSE(sparseArray.has_index(5));

}



TEST_F(SparseArrayTest_70, HasIndexReturnsFalseForNonExistentIndex_70) {

    EXPECT_FALSE(sparseArray.has_index(5));

}



TEST_F(SparseArrayTest_70, SetThrowsErrorWhenSettingExistingWithoutAllowingIt_70) {

    sparseArray.set_new(5, 10);

    EXPECT_THROW(sparseArray.set_existing(5, 20), std::exception);

}



TEST_F(SparseArrayTest_70, BeginAndEndIterateOverAllElements_70) {

    sparseArray.set_new(5, 10);

    sparseArray.set_new(6, 20);

    int count = 0;

    for (auto it = sparseArray.begin(); it != sparseArray.end(); ++it) {

        count++;

    }

    EXPECT_EQ(count, 2);

}
