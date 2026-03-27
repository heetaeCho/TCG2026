#include <gtest/gtest.h>

#include "Object.h"



// Assuming Object class and isBlockAlignName function are in the same namespace or globally accessible



TEST(isBlockAlignNameTest_1758, NormalOperation_Before_1758) {

    Object obj("Before");

    EXPECT_TRUE(isBlockAlignName(&obj));

}



TEST(isBlockAlignNameTest_1758, NormalOperation_Middle_1758) {

    Object obj("Middle");

    EXPECT_TRUE(isBlockAlignName(&obj));

}



TEST(isBlockAlignNameTest_1758, NormalOperation_After_1758) {

    Object obj("After");

    EXPECT_TRUE(isBlockAlignName(&obj));

}



TEST(isBlockAlignNameTest_1758, NormalOperation_Justify_1758) {

    Object obj("Justify");

    EXPECT_TRUE(isBlockAlignName(&obj));

}



TEST(isBlockAlignNameTest_1758, BoundaryCondition_EmptyString_1758) {

    Object obj("");

    EXPECT_FALSE(isBlockAlignName(&obj));

}



TEST(isBlockAlignNameTest_1758, BoundaryCondition_NullObject_1758) {

    Object obj = Object::null();

    EXPECT_FALSE(isBlockAlignName(&obj));

}



TEST(isBlockAlignNameTest_1758, ExceptionalCase_OtherString_1758) {

    Object obj("Other");

    EXPECT_FALSE(isBlockAlignName(&obj));

}
