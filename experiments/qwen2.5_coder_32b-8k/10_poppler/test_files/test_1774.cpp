#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/Object.h"



TEST(isTextStringTest_1774, NormalOperation_StringObject_1774) {

    Object stringObj(std::string("test"));

    EXPECT_TRUE(isTextString(&stringObj));

}



TEST(isTextStringTest_1774, NormalOperation_NonStringObject_1774) {

    Object intObj(42);

    EXPECT_FALSE(isTextString(&intObj));

}



TEST(isTextStringTest_1774, BoundaryCondition_EmptyString_1774) {

    Object emptyStringObj(std::string(""));

    EXPECT_TRUE(isTextString(&emptyStringObj));

}



TEST(isTextStringTest_1774, ExceptionalCase_NullPointer_1774) {

    EXPECT_FALSE(isTextString(nullptr));

}
