#include <gtest/gtest.h>

#include "sparse_array.h"



using namespace re2;



// Test Fixture for SparseArray

template <typename T>

class SparseArrayTest : public ::testing::Test {

protected:

    SparseArray<T> sparseArray;

    SparseArray<T> sparseArrayWithSize;



    SparseArrayTest() : sparseArray(), sparseArrayWithSize(10) {}

};



using MyTypes = ::testing::Types<int, std::string>;

TYPED_TEST_SUITE(SparseArrayTest, MyTypes);



// Test normal operation of the constructor

TYPED_TEST(SparseArrayTest_87, DefaultConstructor_87) {

    EXPECT_EQ(this->sparseArray.size(), 0);

}



// Test normal operation of the constructor with max_size

TYPED_TEST(SparseArrayTest_87, ConstructorWithMaxSize_87) {

    EXPECT_EQ(this->sparseArrayWithSize.max_size(), 10);

}



// Test normal operation of the resize method

TYPED_TEST(SparseArrayTest_87, ResizeIncreasesCapacity_87) {

    this->sparseArray.resize(20);

    EXPECT_EQ(this->sparseArray.max_size(), 20);

}



// Test boundary condition of resize method with zero size

TYPED_TEST(SparseArrayTest_87, ResizeToZero_87) {

    this->sparseArrayWithSize.resize(0);

    EXPECT_EQ(this->sparseArrayWithSize.max_size(), 0);

}



// Test normal operation of the has_index method

TYPED_TEST(SparseArrayTest_87, HasIndexAfterSet_87) {

    this->sparseArray.set(5, TypeParam{});

    EXPECT_TRUE(this->sparseArray.has_index(5));

}



// Test boundary condition of has_index method with out-of-range index

TYPED_TEST(SparseArrayTest_87, HasIndexOutOfRange_87) {

    EXPECT_FALSE(this->sparseArrayWithSize.has_index(20));

}



// Test normal operation of the set_new method

TYPED_TEST(SparseArrayTest_87, SetNewIncreasesSize_87) {

    this->sparseArray.set_new(3, TypeParam{});

    EXPECT_EQ(this->sparseArray.size(), 1);

}



// Test exceptional case of set_new method with existing index

TYPED_TEST(SparseArrayTest_87, SetNewOnExistingIndex_87) {

    this->sparseArray.set_new(3, TypeParam{});

    EXPECT_THROW(this->sparseArray.set_new(3, TypeParam{}), std::exception);

}



// Test normal operation of the set_existing method

TYPED_TEST(SparseArrayTest_87, SetExistingUpdatesValue_87) {

    this->sparseArray.set_new(4, TypeParam{});

    this->sparseArray.set_existing(4, TypeParam{});

    EXPECT_TRUE(this->sparseArray.has_index(4));

}



// Test exceptional case of set_existing method with non-existing index

TYPED_TEST(SparseArrayTest_87, SetExistingOnNonExistingIndex_87) {

    EXPECT_THROW(this->sparseArray.set_existing(4, TypeParam{}), std::exception);

}



// Test normal operation of the get_existing method

TYPED_TEST(SparseArrayTest_87, GetExistingReturnsValue_87) {

    this->sparseArray.set_new(6, TypeParam{});

    EXPECT_NO_THROW(this->sparseArray.get_existing(6));

}



// Test exceptional case of get_existing method with non-existing index

TYPED_TEST(SparseArrayTest_87, GetExistingOnNonExistingIndex_87) {

    EXPECT_THROW(this->sparseArray.get_existing(6), std::exception);

}



// Test normal operation of the clear method

TYPED_TEST(SparseArrayTest_87, ClearRemovesAllElements_87) {

    this->sparseArray.set_new(1, TypeParam{});

    this->sparseArray.clear();

    EXPECT_EQ(this->sparseArray.size(), 0);

}



// Test boundary condition of begin and end iterators

TYPED_TEST(SparseArrayTest_87, IteratorsEmptyArray_87) {

    auto it = this->sparseArray.begin();

    auto end = this->sparseArray.end();

    EXPECT_EQ(it, end);

}
