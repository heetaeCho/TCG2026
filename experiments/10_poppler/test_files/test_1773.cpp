#include <gtest/gtest.h>

#include "Object.h"



// Assuming Object class is defined in Object.h



TEST(isNumberOrAutoTest_1773, IsNumber_ReturnsTrue_1773) {

    Object numberObj(42);

    EXPECT_TRUE(isNumberOrAuto(&numberObj));

}



TEST(isNumberOrAutoTest_1773, IsAutoName_ReturnsTrue_1773) {

    Object autoObj("Auto");

    EXPECT_TRUE(isNumberOrAuto(&autoObj));

}



TEST(isNumberOrAutoTest_1773, IsNotNumberNorAuto_ReturnsFalse_1773) {

    Object stringObj("NotAuto");

    EXPECT_FALSE(isNumberOrAuto(&stringObj));

}



TEST(isNumberOrAutoTest_1773, IsRealNumber_ReturnsTrue_1773) {

    Object realObj(42.0);

    EXPECT_TRUE(isNumberOrAuto(&realObj));

}



TEST(isNumberOrAutoTest_1773, IsInt64Number_ReturnsTrue_1773) {

    Object int64Obj(42LL);

    EXPECT_TRUE(isNumberOrAuto(&int64Obj));

}



TEST(isNumberOrAutoTest_1773, IsNullObject_ReturnsFalse_1773) {

    Object nullObj = Object::null();

    EXPECT_FALSE(isNumberOrAuto(&nullObj));

}
