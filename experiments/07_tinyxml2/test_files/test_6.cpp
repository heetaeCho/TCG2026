#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_6 : public ::testing::Test {

protected:

    void SetUp() override {

        dynArray = new DynArray<int>;

    }



    void TearDown() override {

        delete dynArray;

    }



    DynArray<int>* dynArray;

};



TEST_F(DynArrayTest_6, PushIncreasesCount_6) {

    EXPECT_EQ(dynArray->Size(), 0);

    dynArray->Push(1);

    EXPECT_EQ(dynArray->Size(), 1);

}



TEST_F(DynArrayTest_6, PopDecreasesCount_6) {

    dynArray->Push(1);

    dynArray->Pop();

    EXPECT_EQ(dynArray->Size(), 0);

}



TEST_F(DynArrayTest_6, PushMultipleElements_6) {

    for (int i = 0; i < 10; ++i) {

        dynArray->Push(i);

    }

    EXPECT_EQ(dynArray->Size(), 10);

}



TEST_F(DynArrayTest_6, PopMultipleElements_6) {

    for (int i = 0; i < 10; ++i) {

        dynArray->Push(i);

    }

    dynArray->PopArr(5);

    EXPECT_EQ(dynArray->Size(), 5);

}



TEST_F(DynArrayTest_6, PeekTopReturnsLastElement_6) {

    dynArray->Push(42);

    EXPECT_EQ(dynArray->PeekTop(), 42);

}



TEST_F(DynArrayTest_6, EmptyCheckInitiallyTrue_6) {

    EXPECT_TRUE(dynArray->Empty());

}



TEST_F(DynArrayTest_6, EmptyCheckFalseAfterPush_6) {

    dynArray->Push(1);

    EXPECT_FALSE(dynArray->Empty());

}



TEST_F(DynArrayTest_6, ClearResetsSize_6) {

    for (int i = 0; i < 5; ++i) {

        dynArray->Push(i);

    }

    dynArray->Clear();

    EXPECT_EQ(dynArray->Size(), 0);

}



TEST_F(DynArrayTest_6, BoundaryConditionInitialCapacity_6) {

    for (size_t i = 0; i < DynArray<int>::INITIAL_SIZE; ++i) {

        dynArray->Push(i);

    }

    EXPECT_FALSE(dynArray->Empty());

    EXPECT_EQ(dynArray->Size(), DynArray<int>::INITIAL_SIZE);

}



TEST_F(DynArrayTest_6, BoundaryConditionExceedInitialCapacity_6) {

    for (size_t i = 0; i < DynArray<int>::INITIAL_SIZE + 5; ++i) {

        dynArray->Push(i);

    }

    EXPECT_EQ(dynArray->Size(), DynArray<int>::INITIAL_SIZE + 5);

}



TEST_F(DynArrayTest_6, BoundaryConditionPopAllElements_6) {

    for (size_t i = 0; i < DynArray<int>::INITIAL_SIZE + 5; ++i) {

        dynArray->Push(i);

    }

    dynArray->PopArr(dynArray->Size());

    EXPECT_EQ(dynArray->Size(), 0);

}
