#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_111 : public ::testing::Test {

protected:

    Object boolObject;

    Object nonBoolObject;



    ObjectTest_111() : boolObject(true), nonBoolObject(42) {}

};



TEST_F(ObjectTest_111, GetBoolWithDefaultValue_ReturnsTrueWhenBoolType_111) {

    EXPECT_TRUE(boolObject.getBoolWithDefaultValue(false));

}



TEST_F(ObjectTest_111, GetBoolWithDefaultValue_ReturnsFalseWhenNonBoolType_111) {

    EXPECT_FALSE(nonBoolObject.getBoolWithDefaultValue(true));

}



TEST_F(ObjectTest_111, GetBoolWithDefaultValue_ReturnsDefaultValueForDefaultConstructedObject_111) {

    Object defaultConstructedObject;

    EXPECT_TRUE(defaultConstructedObject.getBoolWithDefaultValue(true));

    EXPECT_FALSE(defaultConstructedObject.getBoolWithDefaultValue(false));

}
