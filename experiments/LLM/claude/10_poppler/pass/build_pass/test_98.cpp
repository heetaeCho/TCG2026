#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"

// Test fixture for Object::getHexString() tests
class ObjectGetHexStringTest_98 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that creating an Object with ObjType objHexString and a string
// allows getHexString() to return the correct GooString pointer
TEST_F(ObjectGetHexStringTest_98, GetHexStringReturnsCorrectValue_98) {
    Object obj(ObjType::objHexString, std::string_view("48656C6C6F"));
    ASSERT_TRUE(obj.isHexString());
    const GooString *result = obj.getHexString();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->toStr(), "48656C6C6F");
}

// Test that isHexString() returns true for hex string objects
TEST_F(ObjectGetHexStringTest_98, IsHexStringReturnsTrueForHexString_98) {
    Object obj(ObjType::objHexString, std::string_view("AABB"));
    EXPECT_TRUE(obj.isHexString());
}

// Test that isHexString() returns false for regular string objects
TEST_F(ObjectGetHexStringTest_98, IsHexStringReturnsFalseForRegularString_98) {
    Object obj(ObjType::objString, std::string_view("hello"));
    EXPECT_FALSE(obj.isHexString());
}

// Test that isHexString() returns false for non-string types
TEST_F(ObjectGetHexStringTest_98, IsHexStringReturnsFalseForInt_98) {
    Object obj(42);
    EXPECT_FALSE(obj.isHexString());
}

// Test that isHexString() returns false for null object
TEST_F(ObjectGetHexStringTest_98, IsHexStringReturnsFalseForNull_98) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isHexString());
}

// Test that isHexString() returns false for bool object
TEST_F(ObjectGetHexStringTest_98, IsHexStringReturnsFalseForBool_98) {
    Object obj(true);
    EXPECT_FALSE(obj.isHexString());
}

// Test that isHexString() returns false for real object
TEST_F(ObjectGetHexStringTest_98, IsHexStringReturnsFalseForReal_98) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isHexString());
}

// Test getHexString with an empty hex string
TEST_F(ObjectGetHexStringTest_98, GetHexStringWithEmptyString_98) {
    Object obj(ObjType::objHexString, std::string_view(""));
    ASSERT_TRUE(obj.isHexString());
    const GooString *result = obj.getHexString();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->toStr(), "");
}

// Test getHexString with a longer hex string
TEST_F(ObjectGetHexStringTest_98, GetHexStringWithLongString_98) {
    std::string longHex = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
    Object obj(ObjType::objHexString, std::string_view(longHex));
    ASSERT_TRUE(obj.isHexString());
    const GooString *result = obj.getHexString();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->toStr(), longHex);
}

// Test that getType() returns objHexString for hex string objects
TEST_F(ObjectGetHexStringTest_98, GetTypeReturnsHexString_98) {
    Object obj(ObjType::objHexString, std::string_view("FF"));
    EXPECT_EQ(obj.getType(), ObjType::objHexString);
}

// Test that a hex string object is not considered a regular string
TEST_F(ObjectGetHexStringTest_98, HexStringIsNotString_98) {
    Object obj(ObjType::objHexString, std::string_view("CAFE"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_FALSE(obj.isString());
}

// Test that a regular string object is not considered a hex string
TEST_F(ObjectGetHexStringTest_98, StringIsNotHexString_98) {
    Object obj(ObjType::objString, std::string_view("CAFE"));
    EXPECT_TRUE(obj.isString());
    EXPECT_FALSE(obj.isHexString());
}

// Test move constructor preserves hex string
TEST_F(ObjectGetHexStringTest_98, MoveConstructorPreservesHexString_98) {
    Object obj1(ObjType::objHexString, std::string_view("DEADBEEF"));
    ASSERT_TRUE(obj1.isHexString());
    
    Object obj2(std::move(obj1));
    ASSERT_TRUE(obj2.isHexString());
    const GooString *result = obj2.getHexString();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->toStr(), "DEADBEEF");
}

// Test move assignment preserves hex string
TEST_F(ObjectGetHexStringTest_98, MoveAssignmentPreservesHexString_98) {
    Object obj1(ObjType::objHexString, std::string_view("BABE"));
    Object obj2 = Object::null();
    
    obj2 = std::move(obj1);
    ASSERT_TRUE(obj2.isHexString());
    const GooString *result = obj2.getHexString();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->toStr(), "BABE");
}

// Test copy() on a hex string object
TEST_F(ObjectGetHexStringTest_98, CopyPreservesHexString_98) {
    Object obj1(ObjType::objHexString, std::string_view("FACE"));
    Object obj2 = obj1.copy();
    
    ASSERT_TRUE(obj2.isHexString());
    const GooString *result = obj2.getHexString();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->toStr(), "FACE");
}

// Test that getTypeName returns something reasonable for hex string
TEST_F(ObjectGetHexStringTest_98, GetTypeNameForHexString_98) {
    Object obj(ObjType::objHexString, std::string_view("AB"));
    const char *typeName = obj.getTypeName();
    ASSERT_NE(typeName, nullptr);
}

// Test that isNone returns false for hex string
TEST_F(ObjectGetHexStringTest_98, IsNoneReturnsFalseForHexString_98) {
    Object obj(ObjType::objHexString, std::string_view("00"));
    EXPECT_FALSE(obj.isNone());
}

// Test that isError returns false for hex string
TEST_F(ObjectGetHexStringTest_98, IsErrorReturnsFalseForHexString_98) {
    Object obj(ObjType::objHexString, std::string_view("FF"));
    EXPECT_FALSE(obj.isError());
}

// Test that isEOF returns false for hex string
TEST_F(ObjectGetHexStringTest_98, IsEOFReturnsFalseForHexString_98) {
    Object obj(ObjType::objHexString, std::string_view("FF"));
    EXPECT_FALSE(obj.isEOF());
}

// Test hex string with special characters
TEST_F(ObjectGetHexStringTest_98, GetHexStringWithSpecialChars_98) {
    std::string special = "\x00\x01\x02\xFF";
    // Use string_view that can handle embedded nulls
    Object obj(ObjType::objHexString, std::string_view(special.data(), special.size()));
    ASSERT_TRUE(obj.isHexString());
    const GooString *result = obj.getHexString();
    ASSERT_NE(result, nullptr);
}

// Test creating hex string with const char* constructor
TEST_F(ObjectGetHexStringTest_98, GetHexStringFromConstChar_98) {
    Object obj(ObjType::objHexString, "ABCDEF");
    ASSERT_TRUE(obj.isHexString());
    const GooString *result = obj.getHexString();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->toStr(), "ABCDEF");
}

// Test setToNull on hex string object
TEST_F(ObjectGetHexStringTest_98, SetToNullClearsHexString_98) {
    Object obj(ObjType::objHexString, std::string_view("AA"));
    ASSERT_TRUE(obj.isHexString());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isHexString());
}
