#include <gtest/gtest.h>

#include "Object.h"



using namespace std;



TEST(isFieldRoleNameTest_1767, NormalOperation_Rb_1767) {

    Object obj("rb");

    EXPECT_TRUE(isFieldRoleName(&obj));

}



TEST(isFieldRoleNameTest_1767, NormalOperation_Cb_1767) {

    Object obj("cb");

    EXPECT_TRUE(isFieldRoleName(&obj));

}



TEST(isFieldRoleNameTest_1767, NormalOperation_Pb_1767) {

    Object obj("pb");

    EXPECT_TRUE(isFieldRoleName(&obj));

}



TEST(isFieldRoleNameTest_1767, NormalOperation_Tv_1767) {

    Object obj("tv");

    EXPECT_TRUE(isFieldRoleName(&obj));

}



TEST(isFieldRoleNameTest_1767, BoundaryCondition_EmptyString_1767) {

    Object obj("");

    EXPECT_FALSE(isFieldRoleName(&obj));

}



TEST(isFieldRoleNameTest_1767, BoundaryCondition_OtherNames_1767) {

    Object obj("other");

    EXPECT_FALSE(isFieldRoleName(&obj));

}



TEST(isFieldRoleNameTest_1767, ExceptionalCase_NullObject_1767) {

    Object* nullObj = nullptr;

    EXPECT_FALSE(isFieldRoleName(nullObj));

}
