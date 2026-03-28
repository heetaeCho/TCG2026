#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_9 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary variables or state before each test

        dynArray = new DynArray<int, 10>;

    }



    void TearDown() override {

        // Clean up after each test

        delete dynArray;

    }



    DynArray<int, 10>* dynArray;

};



TEST_F(DynArrayTest_9, InitialSizeIsZero_9) {

    EXPECT_EQ(dynArray->Size(), 0);

}



TEST_F(DynArrayTest_9, PushIncreasesCount_9) {

    dynArray->Push(42);

    EXPECT_EQ(dynArray->Size(), 1);

}



TEST_F(DynArrayTest_9, PopDecreasesCount_9) {

    dynArray->Push(42);

    dynArray->Pop();

    EXPECT_EQ(dynArray->Size(), 0);

}



TEST_F(DynArrayTest_9, ClearResetsCount_9) {

    dynArray->Push(42);

    dynArray->Clear();

    EXPECT_EQ(dynArray->Size(), 0);

}



TEST_F(DynArrayTest_9, PushArrIncreasesCount_9) {

    int* ptr = dynArray->PushArr(5);

    for (int i = 0; i < 5; ++i) {

        ptr[i] = i;

    }

    EXPECT_EQ(dynArray->Size(), 5);

}



TEST_F(DynArrayTest_9, PopArrDecreasesCount_9) {

    int* ptr = dynArray->PushArr(5);

    for (int i = 0; i < 5; ++i) {

        ptr[i] = i;

    }

    dynArray->PopArr(3);

    EXPECT_EQ(dynArray->Size(), 2);

}



TEST_F(DynArrayTest_9, PopArrWithZeroCountDoesNothing_9) {

    int* ptr = dynArray->PushArr(5);

    for (int i = 0; i < 5; ++i) {

        ptr[i] = i;

    }

    dynArray->PopArr(0);

    EXPECT_EQ(dynArray->Size(), 5);

}



TEST_F(DynArrayTest_9, PopArrWithExactCountEmptiesArray_9) {

    int* ptr = dynArray->PushArr(5);

    for (int i = 0; i < 5; ++i) {

        ptr[i] = i;

    }

    dynArray->PopArr(5);

    EXPECT_EQ(dynArray->Size(), 0);

}



TEST_F(DynArrayTest_9, PopArrWithMoreThanCountTriggersAssertion_9) {

    int* ptr = dynArray->PushArr(3);

    for (int i = 0; i < 3; ++i) {

        ptr[i] = i;

    }

    EXPECT_DEATH(dynArray->PopArr(4), "TIXMLASSERT");

}



TEST_F(DynArrayTest_9, EmptyReturnsTrueWhenNoElements_9) {

    EXPECT_TRUE(dynArray->Empty());

}



TEST_F(DynArrayTest_9, EmptyReturnsFalseWhenElementsPresent_9) {

    dynArray->Push(42);

    EXPECT_FALSE(dynArray->Empty());

}



TEST_F(DynArrayTest_9, PeekTopReturnsLastElement_9) {

    dynArray->Push(42);

    dynArray->Push(84);

    EXPECT_EQ(dynArray->PeekTop(), 84);

}



TEST_F(DynArrayTest_9, IndexOperatorAccessesElements_9) {

    dynArray->Push(10);

    dynArray->Push(20);

    EXPECT_EQ((*dynArray)[0], 10);

    EXPECT_EQ((*dynArray)[1], 20);

}



TEST_F(DynArrayTest_9, CapacityReturnsInitialCapacity_9) {

    EXPECT_EQ(dynArray->Capacity(), 10);

}
