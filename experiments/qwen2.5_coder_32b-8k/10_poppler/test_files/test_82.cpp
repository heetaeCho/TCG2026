#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_82 : public ::testing::Test {

protected:

    ObjectTest_82() {}

};



TEST_F(ObjectTest_82, IsRef_ReturnsTrueForRefType_82) {

    Object obj(ObjType::objRef);

    EXPECT_TRUE(obj.isRef());

}



TEST_F(ObjectTest_82, IsRef_ReturnsFalseForNonRefType_82) {

    Object obj(ObjType::objInt);

    EXPECT_FALSE(obj.isRef());

}



TEST_F(ObjectTest_82, IsRef_DefaultConstructorReturnsFalse_82) {

    Object obj;

    EXPECT_FALSE(obj.isRef());

}



TEST_F(ObjectTest_82, GetType_ReturnsCorrectTypeForConstructedObject_82) {

    Object obj(ObjType::objDict);

    EXPECT_EQ(obj.getType(), ObjType::objDict);

}



TEST_F(ObjectTest_82, IsBool_ReturnsTrueForBoolType_82) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

}



TEST_F(ObjectTest_82, IsBool_ReturnsFalseForNonBoolType_82) {

    Object obj(ObjType::objInt);

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_82, IsInt_ReturnsTrueForIntType_82) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

}



TEST_F(ObjectTest_82, IsInt_ReturnsFalseForNonIntType_82) {

    Object obj(ObjType::objReal);

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_82, IsReal_ReturnsTrueForRealType_82) {

    Object obj(42.0);

    EXPECT_TRUE(obj.isReal());

}



TEST_F(ObjectTest_82, IsReal_ReturnsFalseForNonRealType_82) {

    Object obj(ObjType::objString);

    EXPECT_FALSE(obj.isReal());

}



TEST_F(ObjectTest_82, IsString_ReturnsTrueForStringType_82) {

    Object obj(std::string("test"));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_82, IsString_ReturnsFalseForNonStringType_82) {

    Object obj(ObjType::objName);

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_82, IsNone_ReturnsTrueForNoneType_82) {

    Object obj;

    EXPECT_TRUE(obj.isNone());

}



TEST_F(ObjectTest_82, IsNone_ReturnsFalseForNonNoneType_82) {

    Object obj(ObjType::objNull);

    EXPECT_FALSE(obj.isNone());

}
