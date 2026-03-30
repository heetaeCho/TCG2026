#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_91 : public ::testing::Test {

protected:

    Object boolObject;

    Object intObject;

    Object realObject;

    Object stringObject;

    Object nullObject;



    void SetUp() override {

        boolObject = Object(true);

        intObject = Object(42);

        realObject = Object(3.14);

        stringObject = Object(std::unique_ptr<GooString>(new GooString("test")));

        nullObject = Object::null();

    }

};



TEST_F(ObjectTest_91, IsBool_ReturnsTrueForBooleanObject_91) {

    EXPECT_TRUE(boolObject.isBool());

}



TEST_F(ObjectTest_91, IsInt_ReturnsTrueForIntegerObject_91) {

    EXPECT_TRUE(intObject.isInt());

}



TEST_F(ObjectTest_91, IsReal_ReturnsTrueForRealObject_91) {

    EXPECT_TRUE(realObject.isReal());

}



TEST_F(ObjectTest_91, IsString_ReturnsTrueForStringObject_91) {

    EXPECT_TRUE(stringObject.isString());

}



TEST_F(ObjectTest_91, IsNull_ReturnsTrueForNullObject_91) {

    EXPECT_TRUE(nullObject.isNull());

}



TEST_F(ObjectTest_91, GetBool_ReturnsCorrectValueForBooleanObject_91) {

    EXPECT_EQ(boolObject.getBool(), true);

}



TEST_F(ObjectTest_91, GetInt_ReturnsCorrectValueForIntegerObject_91) {

    EXPECT_EQ(intObject.getInt(), 42);

}



TEST_F(ObjectTest_91, GetReal_ReturnsCorrectValueForRealObject_91) {

    EXPECT_DOUBLE_EQ(realObject.getReal(), 3.14);

}



TEST_F(ObjectTest_91, GetString_ReturnsCorrectValueForStringObject_91) {

    EXPECT_STREQ(stringObject.getString()->c_str(), "test");

}



TEST_F(ObjectTest_91, GetBoolWithDefaultValue_ReturnsTrueForBooleanObject_91) {

    EXPECT_EQ(boolObject.getBoolWithDefaultValue(false), true);

}



TEST_F(ObjectTest_91, GetBoolWithDefaultValue_ReturnsDefaultForNullObject_91) {

    EXPECT_EQ(nullObject.getBoolWithDefaultValue(true), true);

}
