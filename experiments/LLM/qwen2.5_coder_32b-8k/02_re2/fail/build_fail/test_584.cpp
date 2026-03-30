#include <gtest/gtest.h>

#include "re2/sparse_array.h"



using namespace re2;



class SparseArrayTest_584 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects before each test.

        max_size = 10;

        sparse_array = std::make_unique<SparseArray<int>>(max_size);

    }



    int max_size;

    std::unique_ptr<SparseArray<int>> sparse_array;

};



TEST_F(SparseArrayTest_584, InitialSizeIsZero_584) {

    EXPECT_EQ(sparse_array->size(), 0);

}



TEST_F(SparseArrayTest_584, ResizeIncreasesMaxSize_584) {

    int new_max_size = 20;

    sparse_array->resize(new_max_size);

    EXPECT_GE(sparse_array->max_size(), new_max_size);

}



TEST_F(SparseArrayTest_584, SetNewAddsElement_584) {

    int index = 3;

    int value = 10;

    auto it = sparse_array->set_new(index, value);

    EXPECT_TRUE(sparse_array->has_index(index));

    EXPECT_EQ(*it, value);

    EXPECT_EQ(sparse_array->size(), 1);

}



TEST_F(SparseArrayTest_584, SetExistingUpdatesElement_584) {

    int index = 3;

    int initial_value = 10;

    sparse_array->set_new(index, initial_value);



    int updated_value = 20;

    auto it = sparse_array->set_existing(index, updated_value);

    EXPECT_EQ(*it, updated_value);

    EXPECT_EQ(sparse_array->size(), 1);

}



TEST_F(SparseArrayTest_584, GetExistingRetrievesCorrectValue_584) {

    int index = 3;

    int value = 10;

    sparse_array->set_new(index, value);



    EXPECT_EQ(sparse_array->get_existing(index), value);

}



TEST_F(SparseArrayTest_584, HasIndexReturnsTrueForExistingIndex_584) {

    int index = 3;

    sparse_array->set_new(index, 10);

    EXPECT_TRUE(sparse_array->has_index(index));

}



TEST_F(SparseArrayTest_584, HasIndexReturnsFalseForNonExistingIndex_584) {

    int non_existing_index = 15;

    EXPECT_FALSE(sparse_array->has_index(non_existing_index));

}



TEST_F(SparseArrayTest_584, ClearRemovesAllElements_584) {

    sparse_array->set_new(3, 10);

    sparse_array->clear();

    EXPECT_EQ(sparse_array->size(), 0);

    EXPECT_FALSE(sparse_array->has_index(3));

}



TEST_F(SparseArrayTest_584, IteratorTraversalWorksCorrectly_584) {

    sparse_array->set_new(3, 10);

    sparse_array->set_new(5, 20);



    int count = 0;

    for (auto it = sparse_array->begin(); it != sparse_array->end(); ++it) {

        count++;

    }

    EXPECT_EQ(count, 2);

}



TEST_F(SparseArrayTest_584, SetNewFailsOnExistingIndex_584) {

    int index = 3;

    sparse_array->set_new(index, 10);



    EXPECT_THROW(sparse_array->set_new(index, 20), std::exception); // Assuming set_new throws on existing index

}



TEST_F(SparseArrayTest_584, SetExistingFailsOnNonExistingIndex_584) {

    int non_existing_index = 3;

    EXPECT_THROW(sparse_array->set_existing(non_existing_index, 10), std::exception); // Assuming set_existing throws on non-existing index

}



TEST_F(SparseArrayTest_584, BoundaryConditionMaxSize_584) {

    sparse_array.reset(new SparseArray<int>(max_size));



    for (int i = 0; i < max_size; ++i) {

        sparse_array->set_new(i, i * 10);

    }

    EXPECT_EQ(sparse_array->size(), max_size);



    EXPECT_THROW(sparse_array->set_new(max_size, 10), std::exception); // Assuming set_new throws when exceeding max_size

}
