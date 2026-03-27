#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_106 : public ::testing::Test {

protected:

    Ref validRef;

    Ref invalidRef;



    void SetUp() override {

        validRef = {42, 7};

        invalidRef = Ref::INVALID();

    }

};



TEST_F(ObjectTest_106, GetRefGen_ValidRef_106) {

    Object obj(validRef);

    EXPECT_EQ(obj.getRefGen(), 7);

}



TEST_F(ObjectTest_106, GetRefGen_InvalidRef_106) {

    Object obj(invalidRef);

    EXPECT_NE(obj.getRefGen(), 0); // Assuming getRefGen() returns a non-zero value for invalid refs

}



TEST_F(ObjectTest_106, IsRef_ValidRef_106) {

    Object obj(validRef);

    EXPECT_TRUE(obj.isRef());

}



TEST_F(ObjectTest_106, IsRef_InvalidRef_106) {

    Object obj(invalidRef);

    EXPECT_FALSE(obj.isRef());

}



TEST_F(ObjectTest_106, GetTypeName_ValidRef_106) {

    Object obj(validRef);

    EXPECT_STREQ(obj.getTypeName(), "ref");

}



TEST_F(ObjectTest_106, GetTypeName_InvalidRef_106) {

    Object obj(invalidRef);

    EXPECT_STRNE(obj.getTypeName(), "ref"); // Assuming getTypeName() does not return "ref" for invalid refs

}



TEST_F(ObjectTest_106, IsDict_NonDictObject_106) {

    Object obj(validRef);

    EXPECT_FALSE(obj.isDict("someDictType"));

}



TEST_F(ObjectTest_106, ArrayGetLength_EmptyArray_106) {

    Object obj(new Array());

    EXPECT_EQ(obj.arrayGetLength(), 0);

}



TEST_F(ObjectTest_106, DictGetLength_EmptyDict_106) {

    Object obj(new Dict());

    EXPECT_EQ(obj.dictGetLength(), 0);

}



TEST_F(ObjectTest_106, GetNum_NonNumericObject_106) {

    Object obj(validRef);

    bool ok;

    double num = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_DOUBLE_EQ(num, 0.0); // Assuming getNum() returns 0.0 when !ok

}



TEST_F(ObjectTest_106, GetBool_NonBooleanObject_106) {

    Object obj(validRef);

    bool ok;

    bool value = obj.getBoolWithDefaultValue(false);

    EXPECT_FALSE(ok);

    EXPECT_EQ(value, false); // Assuming getBoolWithDefaultValue() returns defaultValue when !ok

}



TEST_F(ObjectTest_106, GetInt_NonIntegerObject_106) {

    Object obj(validRef);

    bool ok;

    int value = obj.getInt();

    EXPECT_NE(ok, true); // Assuming getInt() sets ok to false for non-integer objects

    EXPECT_EQ(value, 0); // Assuming getInt() returns 0 when !ok

}



TEST_F(ObjectTest_106, GetIntOrInt64_NonIntegerObject_106) {

    Object obj(validRef);

    long long value = obj.getIntOrInt64();

    EXPECT_NE(value, 0); // Assuming getIntOrInt64() returns a non-zero value for non-integer objects

}



TEST_F(ObjectTest_106, GetNumWithDefaultValue_NonNumericObject_106) {

    Object obj(validRef);

    double defaultValue = 42.0;

    double num = obj.getNumWithDefaultValue(defaultValue);

    EXPECT_DOUBLE_EQ(num, defaultValue);

}



TEST_F(ObjectTest_106, GetBoolWithDefaultValue_NonBooleanObject_106) {

    Object obj(validRef);

    bool defaultValue = true;

    bool value = obj.getBoolWithDefaultValue(defaultValue);

    EXPECT_EQ(value, defaultValue);

}
