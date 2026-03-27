#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_7 : public ::testing::Test {

protected:

    void SetUp() override {

        dynArray = new DynArray<int, 5>();

    }



    void TearDown() override {

        delete dynArray;

    }



    DynArray<int, 5>* dynArray;

};



TEST_F(DynArrayTest_7, PushArr_IncreasesSize_7) {

    size_t initialSize = dynArray->Size();

    int count = 3;

    dynArray->PushArr(count);

    EXPECT_EQ(dynArray->Size(), initialSize + count);

}



TEST_F(DynArrayTest_7, PushArr_ReturnsCorrectPointer_7) {

    size_t initialSize = dynArray->Size();

    int count = 2;

    int* ptr = dynArray->PushArr(count);

    EXPECT_EQ(ptr, &(*dynArray)[initialSize]);

}



TEST_F(DynArrayTest_7, PushArr_BoundaryConditionFullCapacity_7) {

    // Fill the initial capacity

    size_t initialCapacity = dynArray->Capacity();

    dynArray->PushArr(initialCapacity);

    EXPECT_EQ(dynArray->Size(), initialCapacity);



    // Add one more element to trigger reallocation

    int* ptr = dynArray->PushArr(1);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(DynArrayTest_7, PushArr_ExceptionalCaseZeroCount_7) {

    size_t initialSize = dynArray->Size();

    dynArray->PushArr(0);

    EXPECT_EQ(dynArray->Size(), initialSize); // Size should not change

}



TEST_F(DynArrayTest_7, PushArr_ExceptionalCaseLargeCount_7) {

    size_t largeCount = 1000; // Large count that exceeds initial capacity and triggers multiple reallocations

    int* ptr = dynArray->PushArr(largeCount);

    EXPECT_NE(ptr, nullptr); // Pointer should not be null

    EXPECT_EQ(dynArray->Size(), largeCount); // Size should match the added elements

}
