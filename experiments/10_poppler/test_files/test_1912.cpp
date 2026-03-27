#include <gtest/gtest.h>

#include "Function.cc"  // Assuming the class definition is in this file



class PSStackTest : public ::testing::Test {

protected:

    PSStack stack;

};



TEST_F(PSStackTest_1912, PopNum_ReturnsZeroOnUnderflow_1912) {

    EXPECT_EQ(stack.popNum(), 0);

}



TEST_F(PSStackTest_1912, PopNum_ReturnsIntAsDouble_1912) {

    stack.pushInt(42);

    EXPECT_DOUBLE_EQ(stack.popNum(), 42.0);

}



TEST_F(PSStackTest_1912, PopNum_ReturnsRealDirectly_1912) {

    stack.pushReal(3.14);

    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);

}



TEST_F(PSStackTest_1912, PopNum_DecrementsStackPointer_1912) {

    stack.pushInt(42);

    stack.popNum();

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1912, PopNum_MixedTypesReturnCorrectly_1912) {

    stack.pushReal(3.14);

    stack.pushInt(42);

    EXPECT_DOUBLE_EQ(stack.popNum(), 42.0);

    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);

}



TEST_F(PSStackTest_1912, PopNum_TypeMismatch_ReturnsZero_1912) {

    stack.pushBool(true);  // Assuming pushBool is implemented

    EXPECT_EQ(stack.popNum(), 0);

}
