#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_2749 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_2749, Constructor_ObjTypeStringView_Valid_2749) {

    Object obj(ObjType::objName, "test");

    EXPECT_STREQ(obj.getName(), "test");

}



TEST_F(ObjectTest_2749, Constructor_ObjTypeStringView_EmptyString_2749) {

    Object obj(ObjType::objName, "");

    EXPECT_STREQ(obj.getName(), "");

}



TEST_F(ObjectTest_2749, Constructor_ObjTypeCString_Valid_2749) {

    Object obj(ObjType::objName, "test");

    EXPECT_STREQ(obj.getName(), "test");

}



TEST_F(ObjectTest_2749, GetType_ReturnsCorrectType_Name_2749) {

    Object obj(ObjType::objName, "test");

    EXPECT_EQ(obj.getType(), ObjType::objName);

}



TEST_F(ObjectTest_2749, GetType_ReturnsCorrectType_String_2749) {

    Object obj(ObjType::objString, std::string("test"));

    EXPECT_EQ(obj.getType(), ObjType::objString);

}



TEST_F(ObjectTest_2749, IsName_ValidName_ReturnsTrue_2749) {

    Object obj(ObjType::objName, "test");

    EXPECT_TRUE(obj.isName("test"));

}



TEST_F(ObjectTest_2749, IsName_InvalidName_ReturnsFalse_2749) {

    Object obj(ObjType::objName, "test");

    EXPECT_FALSE(obj.isName("invalid"));

}



TEST_F(ObjectTest_2749, IsString_ValidString_ReturnsTrue_2749) {

    Object obj(ObjType::objString, std::string("test"));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_2749, IsString_NotAString_ReturnsFalse_2749) {

    Object obj(ObjType::objName, "test");

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_2749, GetNum_NonNumericType_ReturnsDefaultValue_2749) {

    Object obj(ObjType::objName, "test");

    double defaultValue = 3.14;

    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(defaultValue), defaultValue);

}



TEST_F(ObjectTest_2749, GetBool_NonBooleanType_ReturnsDefaultValue_2749) {

    Object obj(ObjType::objName, "test");

    bool defaultValue = true;

    EXPECT_EQ(obj.getBoolWithDefaultValue(defaultValue), defaultValue);

}
