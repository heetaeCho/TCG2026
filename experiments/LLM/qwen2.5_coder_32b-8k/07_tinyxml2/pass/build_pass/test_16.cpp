#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_16 : public ::testing::Test {

protected:

    void SetUp() override {

        dynArray = new DynArray<int, 5>;

    }



    void TearDown() override {

        delete dynArray;

    }



    DynArray<int, 5>* dynArray;

};



TEST_F(DynArrayTest_16, InitialState_16) {

    EXPECT_EQ(dynArray->Size(), 0);

    EXPECT_EQ(dynArray->Capacity(), 5);

    EXPECT_TRUE(dynArray->Empty());

}



TEST_F(DynArrayTest_16, PushIncreasesSize_16) {

    dynArray->Push(42);

    EXPECT_EQ(dynArray->Size(), 1);

    EXPECT_FALSE(dynArray->Empty());

}



TEST_F(DynArrayTest_16, PopDecreasesSize_16) {

    dynArray->Push(42);

    dynArray->Pop();

    EXPECT_EQ(dynArray->Size(), 0);

    EXPECT_TRUE(dynArray->Empty());

}



TEST_F(DynArrayTest_16, PushAndPopValuesMatch_16) {

    int value = 42;

    dynArray->Push(value);

    EXPECT_EQ(dynArray->Pop(), value);

}



TEST_F(DynArrayTest_16, PeekTopReturnsLastElement_16) {

    int value = 42;

    dynArray->Push(value);

    EXPECT_EQ(dynArray->PeekTop(), value);

}



TEST_F(DynArrayTest_16, ClearEmptiesArray_16) {

    dynArray->Push(42);

    dynArray->Clear();

    EXPECT_EQ(dynArray->Size(), 0);

    EXPECT_TRUE(dynArray->Empty());

}



TEST_F(DynArrayTest_16, OperatorBracketAccess_16) {

    int value = 42;

    dynArray->Push(value);

    EXPECT_EQ((*dynArray)[0], value);

}



TEST_F(DynArrayTest_16, PushArrIncreasesSize_16) {

    size_t count = 3;

    dynArray->PushArr(count);

    EXPECT_EQ(dynArray->Size(), count);

}



TEST_F(DynArrayTest_16, PopArrDecreasesSize_16) {

    size_t initialCount = 5;

    for (size_t i = 0; i < initialCount; ++i) {

        dynArray->Push(i);

    }

    size_t popCount = 3;

    dynArray->PopArr(popCount);

    EXPECT_EQ(dynArray->Size(), initialCount - popCount);

}



TEST_F(DynArrayTest_16, SwapRemoveMaintainsOrder_16) {

    for (int i = 0; i < 5; ++i) {

        dynArray->Push(i);

    }

    dynArray->SwapRemove(2); // Remove element '2'

    EXPECT_EQ((*dynArray)[2], 4); // Last element moved to the removed position

}



TEST_F(DynArrayTest_16, CapacityGrowsWhenNeeded_16) {

    for (int i = 0; i < 5; ++i) {

        dynArray->Push(i);

    }

    EXPECT_EQ(dynArray->Capacity(), 5);



    dynArray->Push(5); // This should trigger a capacity increase

    EXPECT_GE(dynArray->Capacity(), 6);

}
