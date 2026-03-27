#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_86 : public ::testing::Test {

protected:

    Object defaultConstructedObject;

};



TEST_F(ObjectTest_86, DefaultConstructorIsNone_86) {

    EXPECT_TRUE(defaultConstructedObject.isNone());

}



TEST_F(ObjectTest_86, BoolConstructorNotNone_86) {

    Object boolObject(true);

    EXPECT_FALSE(boolObject.isNone());

}



TEST_F(ObjectTest_86, IntConstructorNotNone_86) {

    Object intObject(42);

    EXPECT_FALSE(intObject.isNone());

}



TEST_F(ObjectTest_86, DoubleConstructorNotNone_86) {

    Object doubleObject(3.14);

    EXPECT_FALSE(doubleObject.isNone());

}



TEST_F(ObjectTest_86, Int64ConstructorNotNone_86) {

    Object int64Object(static_cast<long long>(9223372036854775807));

    EXPECT_FALSE(int64Object.isNone());

}



TEST_F(ObjectTest_86, StringConstructorNotNone_86) {

    Object stringObject(std::string("test"));

    EXPECT_FALSE(stringObject.isNone());

}



TEST_F(ObjectTest_86, UniquePtrStringConstructorNotNone_86) {

    Object uniquePtrStringObject(std::make_unique<GooString>("unique_test"));

    EXPECT_FALSE(uniquePtrStringObject.isNone());

}



TEST_F(ObjectTest_86, TypeAndStringViewConstructorNotNone_86) {

    Object typeAndViewObject(ObjType::objName, std::string_view("name"));

    EXPECT_FALSE(typeAndViewObject.isNone());

}



TEST_F(ObjectTest_86, TypeAndViewConstructorNullTypeIsNone_86) {

    Object nullTypeObject(ObjType::objNone, std::string_view("test"));

    EXPECT_TRUE(nullTypeObject.isNone());

}



TEST_F(ObjectTest_86, MoveConstructorNotNone_86) {

    Object originalObject(true);

    Object movedObject(std::move(originalObject));

    EXPECT_FALSE(movedObject.isNone());

}



TEST_F(ObjectTest_86, CopyConstructorDeleted_86) {

    Object originalObject(true);

    // This line would cause a compile-time error if uncommented:

    // Object copiedObject = originalObject;

}



TEST_F(ObjectTest_86, MoveAssignmentNotNone_86) {

    Object originalObject(true);

    Object movedObject;

    movedObject = std::move(originalObject);

    EXPECT_FALSE(movedObject.isNone());

}



TEST_F(ObjectTest_86, CopyAssignmentDeleted_86) {

    Object originalObject(true);

    Object anotherObject;

    // This line would cause a compile-time error if uncommented:

    // anotherObject = originalObject;

}



TEST_F(ObjectTest_86, StaticNullMethodIsNone_86) {

    Object nullObject = Object::null();

    EXPECT_TRUE(nullObject.isNone());

}



TEST_F(ObjectTest_86, StaticEofMethodNotNone_86) {

    Object eofObject = Object::eof();

    EXPECT_FALSE(eofObject.isNone());

}



TEST_F(ObjectTest_86, StaticErrorMethodNotNone_86) {

    Object errorObject = Object::error();

    EXPECT_FALSE(errorObject.isNone());

}
