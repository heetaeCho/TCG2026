#include <gtest/gtest.h>

#include "Object.h"



TEST(isLineHeightTest_1761, NormalOperation_NameNormal_1761) {

    Object obj("Normal");

    EXPECT_TRUE(isLineHeight(&obj));

}



TEST(isLineHeightTest_1761, NormalOperation_NameAuto_1761) {

    Object obj("Auto");

    EXPECT_TRUE(isLineHeight(&obj));

}



TEST(isLineHeightTest_1761, NormalOperation_Number_1761) {

    Object obj(42);

    EXPECT_TRUE(isLineHeight(&obj));

}



TEST(isLineHeightTest_1761, BoundaryCondition_NameEmptyString_1761) {

    Object obj("");

    EXPECT_FALSE(isLineHeight(&obj));

}



TEST(isLineHeightTest_1761, BoundaryCondition_NameOtherString_1761) {

    Object obj("Other");

    EXPECT_FALSE(isLineHeight(&obj));

}



TEST(isLineHeightTest_1761, ExceptionalCase_NullObject_1761) {

    Object* obj = nullptr;

    EXPECT_FALSE(isLineHeight(obj));

}
