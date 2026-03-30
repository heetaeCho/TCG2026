#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_76 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_76, IsHexString_ReturnsFalse_ForNonHexStringType_76) {

    Object obj(objInt);

    EXPECT_FALSE(obj.isHexString());

}



TEST_F(ObjectTest_76, IsHexString_ReturnsTrue_ForHexStringType_76) {

    Object obj(objHexString);

    EXPECT_TRUE(obj.isHexString());

}



TEST_F(ObjectTest_76, DefaultConstructor_SetsNoneType_76) {

    Object obj;

    EXPECT_FALSE(obj.isHexString());

}



TEST_F(ObjectTest_76, ExplicitConstructors_SetCorrectTypes_76) {

    Object boolObj(true);

    Object intObj(42);

    Object realObj(3.14);

    Object stringObj("test");

    Object int64Obj(9223372036854775807LL);



    EXPECT_FALSE(boolObj.isHexString());

    EXPECT_FALSE(intObj.isHexString());

    EXPECT_FALSE(realObj.isHexString());

    EXPECT_FALSE(stringObj.isHexString());

    EXPECT_FALSE(int64Obj.isHexString());



    Object hexStringObj(objHexString, "hex");

    EXPECT_TRUE(hexStringObj.isHexString());

}



TEST_F(ObjectTest_76, CopyConstructor_PreservesType_76) {

    Object original(objHexString);

    Object copy = original.copy();



    EXPECT_EQ(original.isHexString(), copy.isHexString());

}



TEST_F(ObjectTest_76, DeepCopy_PreservesType_76) {

    Object original(objHexString);

    Object deepCopy = original.deepCopy();



    EXPECT_EQ(original.isHexString(), deepCopy.isHexString());

}
