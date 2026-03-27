#include <gtest/gtest.h>

#include "sparse_array.h"



using namespace re2;



class SparseArrayTest_85 : public ::testing::Test {

protected:

    void SetUp() override {

        sparseArray = std::make_unique<SparseArray<int>>(10);

    }



    std::unique_ptr<SparseArray<int>> sparseArray;

};



TEST_F(SparseArrayTest_85, HasIndex_ReturnsFalseForNegativeIndex_85) {

    EXPECT_FALSE(sparseArray->has_index(-1));

}



TEST_F(SparseArrayTest_85, HasIndex_ReturnsFalseForIndexEqualToMaxSize_85) {

    EXPECT_FALSE(sparseArray->has_index(10));

}



TEST_F(SparseArrayTest_85, HasIndex_ReturnsTrueAfterSet_85) {

    sparseArray->set(5, 42);

    EXPECT_TRUE(sparseArray->has_index(5));

}



TEST_F(SparseArrayTest_85, HasIndex_ReturnsFalseForUnsetIndex_85) {

    EXPECT_FALSE(sparseArray->has_index(3));

}



TEST_F(SparseArrayTest_85, Resize_IncreasesMaxSize_85) {

    sparseArray->resize(20);

    EXPECT_TRUE(sparseArray->max_size() == 20);

}



TEST_F(SparseArrayTest_85, Size_ReturnsCorrectCountAfterSet_85) {

    sparseArray->set(1, 10);

    sparseArray->set(3, 20);

    EXPECT_EQ(sparseArray->size(), 2);

}



TEST_F(SparseArrayTest_85, Clear_ResetsSizeToZero_85) {

    sparseArray->set(1, 10);

    sparseArray->clear();

    EXPECT_EQ(sparseArray->size(), 0);

}



TEST_F(SparseArrayTest_85, SetNew_ReturnsIteratorToInsertedElement_85) {

    auto it = sparseArray->set_new(2, 30);

    EXPECT_EQ(it->index_, 2);

    EXPECT_EQ(*it->value_, 30);

}



TEST_F(SparseArrayTest_85, GetExisting_ReturnsCorrectValue_85) {

    sparseArray->set(4, 50);

    EXPECT_EQ(sparseArray->get_existing(4), 50);

}
