#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_15 : public ::testing::Test {

protected:

    void SetUp() override {

        dynArray = new DynArray<int, 10>;

    }



    void TearDown() override {

        delete dynArray;

    }



    DynArray<int, 10>* dynArray;

};



TEST_F(DynArrayTest_15, SwapRemove_NormalOperation_15) {

    dynArray->Push(1);

    dynArray->Push(2);

    dynArray->Push(3);



    dynArray->SwapRemove(1); // Remove element at index 1 (value 2), replace with last element (value 3)



    EXPECT_EQ(dynArray->Size(), 2);

    EXPECT_EQ((*dynArray)[0], 1);

    EXPECT_EQ((*dynArray)[1], 3);

}



TEST_F(DynArrayTest_15, SwapRemove_BoundaryCondition_Start_15) {

    dynArray->Push(1);

    dynArray->Push(2);



    dynArray->SwapRemove(0); // Remove element at index 0 (value 1), replace with last element (value 2)



    EXPECT_EQ(dynArray->Size(), 1);

    EXPECT_EQ((*dynArray)[0], 2);

}



TEST_F(DynArrayTest_15, SwapRemove_BoundaryCondition_End_15) {

    dynArray->Push(1);

    dynArray->Push(2);



    dynArray->SwapRemove(1); // Remove element at index 1 (value 2), replace with last element (value 2)



    EXPECT_EQ(dynArray->Size(), 1);

    EXPECT_EQ((*dynArray)[0], 1);

}



TEST_F(DynArrayTest_15, SwapRemove_Exceptional_OutOfBounds_15) {

    dynArray->Push(1);



    EXPECT_DEATH({ dynArray->SwapRemove(1); }, ""); // Attempt to remove out-of-bounds index

}



TEST_F(DynArrayTest_15, SwapRemove_Exceptional_EmptyArray_15) {

    EXPECT_DEATH({ dynArray->SwapRemove(0); }, ""); // Attempt to remove from empty array

}
