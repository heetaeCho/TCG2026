#include <gtest/gtest.h>

#include "sparse_array.h"



using namespace re2;



class SparseArrayTest_73 : public ::testing::Test {

protected:

    SparseArray<int> sparse_array;

};



TEST_F(SparseArrayTest_73, DefaultConstructorInitializesSizeToZero_73) {

    EXPECT_EQ(sparse_array.size(), 0);

}



TEST_F(SparseArrayTest_73, ResizeIncreasesMaxSize_73) {

    int new_max_size = 10;

    sparse_array.resize(new_max_size);

    EXPECT_EQ(sparse_array.max_size(), new_max_size);

}



TEST_F(SparseArrayTest_73, SetNewAddsElement_73) {

    int index = 5;

    int value = 42;

    auto it = sparse_array.set_new(index, value);

    EXPECT_TRUE(sparse_array.has_index(index));

    EXPECT_EQ(*it, value);

}



TEST_F(SparseArrayTest_73, SetExistingUpdatesElement_73) {

    int index = 5;

    int initial_value = 42;

    sparse_array.set_new(index, initial_value);

    

    int updated_value = 100;

    auto it = sparse_array.set_existing(index, updated_value);

    EXPECT_TRUE(sparse_array.has_index(index));

    EXPECT_EQ(*it, updated_value);

}



TEST_F(SparseArrayTest_73, SetUpdatesElementIfPresentOrAddsIfNot_73) {

    int index = 5;

    int value = 42;

    auto it = sparse_array.set(index, value);

    EXPECT_TRUE(sparse_array.has_index(index));

    EXPECT_EQ(*it, value);



    int updated_value = 100;

    it = sparse_array.set(index, updated_value);

    EXPECT_TRUE(sparse_array.has_index(index));

    EXPECT_EQ(*it, updated_value);

}



TEST_F(SparseArrayTest_73, ClearRemovesAllElements_73) {

    sparse_array.set_new(5, 42);

    sparse_array.set_new(10, 84);



    sparse_array.clear();

    EXPECT_EQ(sparse_array.size(), 0);

}



TEST_F(SparseArrayTest_73, EndReturnsIteratorPastLastElement_73) {

    auto it = sparse_array.end();

    EXPECT_EQ(it, sparse_array.dense_.data() + sparse_array.size_);

}
