#include <gtest/gtest.h>
#include "Object.h"
#include <string>
#include <memory>

// Test constructing Object with ObjType objHexString and std::string&&
TEST(ObjectHexStringConstructorTest_2748, ConstructWithHexStringType_2748) {
    std::string hexStr = "48656C6C6F";
    Object obj(objHexString, std::move(hexStr));
    
    EXPECT_EQ(obj.getType(), objHexString);
    EXPECT_TRUE(obj.isHexString());
}

TEST(ObjectHexStringConstructorTest_2748, HexStringContentIsPreserved_2748) {
    std::string hexStr = "AABBCCDD";
    Object obj(objHexString, std::move(hexStr));
    
    ASSERT_TRUE(obj.isHexString());
    const GooString *gs = obj.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "AABBCCDD");
}

TEST(ObjectHexStringConstructorTest_2748, EmptyHexString_2748) {
    std::string hexStr = "";
    Object obj(objHexString, std::move(hexStr));
    
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    const GooString *gs = obj.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "");
}

TEST(ObjectHexStringConstructorTest_2748, IsNotOtherTypes_2748) {
    std::string hexStr = "FF";
    Object obj(objHexString, std::move(hexStr));
    
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
}

TEST(ObjectHexStringConstructorTest_2748, LongHexString_2748) {
    std::string hexStr(10000, 'A');
    Object obj(objHexString, std::move(hexStr));
    
    EXPECT_TRUE(obj.isHexString());
    const GooString *gs = obj.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->getLength(), 10000);
}

TEST(ObjectHexStringConstructorTest_2748, MoveSemantics_2748) {
    std::string hexStr = "DEADBEEF";
    Object obj(objHexString, std::move(hexStr));
    
    // After move, the original string should be in a valid but unspecified state
    // We just verify the object was constructed correctly
    EXPECT_TRUE(obj.isHexString());
    const GooString *gs = obj.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "DEADBEEF");
}

TEST(ObjectHexStringConstructorTest_2748, GetTypeName_2748) {
    std::string hexStr = "01";
    Object obj(objHexString, std::move(hexStr));
    
    const char *typeName = obj.getTypeName();
    ASSERT_NE(typeName, nullptr);
}

TEST(ObjectHexStringConstructorTest_2748, CopyObject_2748) {
    std::string hexStr = "CAFE";
    Object obj(objHexString, std::move(hexStr));
    
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isHexString());
    const GooString *gs = copied.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "CAFE");
}

TEST(ObjectHexStringConstructorTest_2748, MoveAssignment_2748) {
    std::string hexStr = "BABE";
    Object obj(objHexString, std::move(hexStr));
    
    Object obj2 = std::move(obj);
    EXPECT_TRUE(obj2.isHexString());
    const GooString *gs = obj2.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "BABE");
}

TEST(ObjectHexStringConstructorTest_2748, MoveConstructor_2748) {
    std::string hexStr = "F00D";
    Object obj(objHexString, std::move(hexStr));
    
    Object obj2(std::move(obj));
    EXPECT_TRUE(obj2.isHexString());
    const GooString *gs = obj2.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "F00D");
}

TEST(ObjectHexStringConstructorTest_2748, SetToNull_2748) {
    std::string hexStr = "1234";
    Object obj(objHexString, std::move(hexStr));
    
    EXPECT_TRUE(obj.isHexString());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isHexString());
}

TEST(ObjectHexStringConstructorTest_2748, SpecialCharactersInHexString_2748) {
    std::string hexStr = "\x00\x01\x02\xFF";
    hexStr.resize(4); // Ensure null byte is included
    Object obj(objHexString, std::move(hexStr));
    
    EXPECT_TRUE(obj.isHexString());
    const GooString *gs = obj.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->getLength(), 4);
}

// Test with string_view constructor variant for objHexString
TEST(ObjectHexStringConstructorTest_2748, ConstructWithStringView_2748) {
    Object obj(objHexString, std::string_view("ABCDEF"));
    
    EXPECT_TRUE(obj.isHexString());
    const GooString *gs = obj.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "ABCDEF");
}

// Test with const char* constructor variant for objHexString
TEST(ObjectHexStringConstructorTest_2748, ConstructWithCString_2748) {
    Object obj(objHexString, "123456");
    
    EXPECT_TRUE(obj.isHexString());
    const GooString *gs = obj.getHexString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "123456");
}

// Additional tests for other Object constructors and static methods for completeness
TEST(ObjectStaticMethodsTest_2748, NullObject_2748) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST(ObjectStaticMethodsTest_2748, EofObject_2748) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST(ObjectStaticMethodsTest_2748, ErrorObject_2748) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

TEST(ObjectDefaultConstructorTest_2748, DefaultIsNone_2748) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST(ObjectBoolConstructorTest_2748, BoolTrue_2748) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

TEST(ObjectBoolConstructorTest_2748, BoolFalse_2748) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST(ObjectIntConstructorTest_2748, IntValue_2748) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
    EXPECT_TRUE(obj.isNum());
}

TEST(ObjectRealConstructorTest_2748, RealValue_2748) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST(ObjectInt64ConstructorTest_2748, Int64Value_2748) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST(ObjectNumTest_2748, GetNumFromInt_2748) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNum(), 10.0);
}

TEST(ObjectNumTest_2748, GetNumFromReal_2748) {
    Object obj(2.5);
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.5);
}

TEST(ObjectNumTest_2748, GetNumWithDefaultValue_2748) {
    Object obj;
    double val = obj.getNumWithDefaultValue(99.0);
    EXPECT_DOUBLE_EQ(val, 99.0);
}

TEST(ObjectBoolTest_2748, GetBoolWithDefaultValue_2748) {
    Object obj;
    bool val = obj.getBoolWithDefaultValue(true);
    EXPECT_TRUE(val);
}

TEST(ObjectStringConstructorTest_2748, StringFromStdString_2748) {
    std::string str = "hello";
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    const GooString *gs = obj.getString();
    ASSERT_NE(gs, nullptr);
    EXPECT_EQ(gs->toStr(), "hello");
}
