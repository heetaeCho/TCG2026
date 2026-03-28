#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string_view>
#include <memory>
#include "./TestProjects/poppler/poppler/Object.h"

class ObjectTest_1237 : public ::testing::Test {
protected:
    // Create objects to be used in the tests
    Object objInt{42};  // Integer type object
    Object objBool{true};  // Boolean type object
    Object objReal{3.14};  // Real type object
    Object objString{"Test String"};  // String type object
    Object objName{objName, "TestName"};  // Name type object
    Object objNull{objNull};  // Null type object
    Object objArray{objArray, std::make_unique<Array>()};  // Array type object
    Object objDict{objDict, std::make_unique<Dict>()};  // Dictionary type object
};

TEST_F(ObjectTest_1237, IsNameTest_1237) {
    // Test if the object is a Name with the correct string value
    EXPECT_TRUE(objName.isName("TestName"));
    EXPECT_FALSE(objName.isName("OtherName"));
}

TEST_F(ObjectTest_1237, IsIntTest_1237) {
    // Test if the object is an Integer
    EXPECT_TRUE(objInt.isInt());
    EXPECT_FALSE(objReal.isInt());
}

TEST_F(ObjectTest_1237, IsBoolTest_1237) {
    // Test if the object is a Boolean
    EXPECT_TRUE(objBool.isBool());
    EXPECT_FALSE(objInt.isBool());
}

TEST_F(ObjectTest_1237, IsRealTest_1237) {
    // Test if the object is a Real number
    EXPECT_TRUE(objReal.isReal());
    EXPECT_FALSE(objInt.isReal());
}

TEST_F(ObjectTest_1237, IsNullTest_1237) {
    // Test if the object is Null
    EXPECT_TRUE(objNull.isNull());
    EXPECT_FALSE(objInt.isNull());
}

TEST_F(ObjectTest_1237, IsArrayTest_1237) {
    // Test if the object is an Array
    EXPECT_TRUE(objArray.isArray());
    EXPECT_FALSE(objInt.isArray());
}

TEST_F(ObjectTest_1237, IsDictTest_1237) {
    // Test if the object is a Dictionary
    EXPECT_TRUE(objDict.isDict());
    EXPECT_FALSE(objInt.isDict());
}

TEST_F(ObjectTest_1237, GetNameStringTest_1237) {
    // Test getting the name string of the object
    EXPECT_EQ(objName.getNameString(), "TestName");
}

TEST_F(ObjectTest_1237, GetIntTest_1237) {
    // Test getting the integer value from the object
    EXPECT_EQ(objInt.getInt(), 42);
}

TEST_F(ObjectTest_1237, GetRealTest_1237) {
    // Test getting the real value from the object
    EXPECT_DOUBLE_EQ(objReal.getReal(), 3.14);
}

TEST_F(ObjectTest_1237, GetBoolTest_1237) {
    // Test getting the boolean value from the object
    EXPECT_TRUE(objBool.getBool());
}

TEST_F(ObjectTest_1237, GetNumWithDefaultValueTest_1237) {
    // Test getting the numeric value with default value
    EXPECT_DOUBLE_EQ(objReal.getNumWithDefaultValue(2.0), 3.14);
    EXPECT_DOUBLE_EQ(objNull.getNumWithDefaultValue(2.0), 2.0);
}

TEST_F(ObjectTest_1237, StreamRewindTest_1237) {
    // Assuming stream-related methods are tested via mocks
    // If the object type is a stream, ensure streamRewind is called
    MockStream mockStream;
    EXPECT_CALL(mockStream, rewind()).Times(1);
    objStream.streamRewind();
}

TEST_F(ObjectTest_1237, ExceptionHandlingTest_1237) {
    // Test if exception or error cases are handled correctly
    EXPECT_NO_THROW(objInt.getInt());
    EXPECT_NO_THROW(objBool.getBool());
    EXPECT_THROW(objDict.getInt(), std::runtime_error);
}

TEST_F(ObjectTest_1237, DictGetLengthTest_1237) {
    // Test dictionary length retrieval
    EXPECT_EQ(objDict.dictGetLength(), 0);
    objDict.dictAdd("key", Object(42));
    EXPECT_EQ(objDict.dictGetLength(), 1);
}

TEST_F(ObjectTest_1237, ArrayAddTest_1237) {
    // Test adding elements to an array
    EXPECT_EQ(objArray.arrayGetLength(), 0);
    objArray.arrayAdd(Object(42));
    EXPECT_EQ(objArray.arrayGetLength(), 1);
}

TEST_F(ObjectTest_1237, BoundaryTest_1237) {
    // Boundary test for types, check what happens when no valid value is set
    Object emptyObj;
    EXPECT_FALSE(emptyObj.isInt());
    EXPECT_FALSE(emptyObj.isString());
    EXPECT_FALSE(emptyObj.isArray());
}