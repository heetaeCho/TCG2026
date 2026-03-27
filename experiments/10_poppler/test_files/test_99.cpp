#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_99 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Cleanup if necessary

    }

};



TEST_F(ObjectTest_99, IsBool_ReturnsTrueForBooleanObject_99) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

}



TEST_F(ObjectTest_99, GetBool_ReturnsCorrectValueForBooleanObject_99) {

    bool testValue = true;

    Object obj(testValue);

    EXPECT_EQ(testValue, obj.getBool());

}



TEST_F(ObjectTest_99, IsInt_ReturnsTrueForIntegerObject_99) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

}



TEST_F(ObjectTest_99, GetInt_ReturnsCorrectValueForIntegerObject_99) {

    int testValue = 42;

    Object obj(testValue);

    EXPECT_EQ(testValue, obj.getInt());

}



TEST_F(ObjectTest_99, IsReal_ReturnsTrueForRealObject_99) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isReal());

}



TEST_F(ObjectTest_99, GetReal_ReturnsCorrectValueForRealObject_99) {

    double testValue = 3.14;

    Object obj(testValue);

    EXPECT_DOUBLE_EQ(testValue, obj.getReal());

}



TEST_F(ObjectTest_99, IsString_ReturnsTrueForStringObject_99) {

    std::unique_ptr<GooString> strPtr(new GooString("test"));

    Object obj(std::move(strPtr));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_99, GetString_ReturnsCorrectValueForStringObject_99) {

    const char* testValue = "test";

    std::unique_ptr<GooString> strPtr(new GooString(testValue));

    Object obj(std::move(strPtr));

    EXPECT_STREQ(testValue, obj.getString()->c_str());

}



TEST_F(ObjectTest_99, IsName_ReturnsTrueForNameObject_99) {

    Object obj(ObjType::objName, "testName");

    EXPECT_TRUE(obj.isName("testName"));

}



TEST_F(ObjectTest_99, GetName_ReturnsCorrectValueForNameObject_99) {

    const char* testValue = "testName";

    Object obj(ObjType::objName, testValue);

    EXPECT_STREQ(testValue, obj.getName());

}



TEST_F(ObjectTest_99, IsNull_ReturnsTrueForNullObject_99) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_99, IsArray_ReturnsFalseForNonArrayObject_99) {

    Object obj(42);

    EXPECT_FALSE(obj.isArray());

}



TEST_F(ObjectTest_99, IsDict_ReturnsFalseForNonDictObject_99) {

    Object obj(42);

    EXPECT_FALSE(obj.isDict());

}



TEST_F(ObjectTest_99, IsStream_ReturnsFalseForNonStreamObject_99) {

    Object obj(42);

    EXPECT_FALSE(obj.isStream());

}



TEST_F(ObjectTest_99, GetType_ReturnsCorrectTypeForObject_99) {

    Object obj(3.14);

    EXPECT_EQ(ObjType::objReal, obj.getType());

}
