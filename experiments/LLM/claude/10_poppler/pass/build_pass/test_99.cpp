#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"

// Test fixture for Object::getName() tests
class ObjectGetNameTest_99 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getName returns the correct name string for a Name object
TEST_F(ObjectGetNameTest_99, GetNameReturnsCorrectValue_99) {
    Object obj(objName, "TestName");
    ASSERT_TRUE(obj.isName());
    const char* name = obj.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "TestName");
}

// Test that getName works with an empty name string
TEST_F(ObjectGetNameTest_99, GetNameEmptyString_99) {
    Object obj(objName, "");
    ASSERT_TRUE(obj.isName());
    const char* name = obj.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "");
}

// Test that getName works with a single character name
TEST_F(ObjectGetNameTest_99, GetNameSingleChar_99) {
    Object obj(objName, "X");
    ASSERT_TRUE(obj.isName());
    const char* name = obj.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "X");
}

// Test that getName works with a long name string
TEST_F(ObjectGetNameTest_99, GetNameLongString_99) {
    std::string longName(256, 'A');
    Object obj(objName, longName);
    ASSERT_TRUE(obj.isName());
    const char* name = obj.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, longName.c_str());
}

// Test that getName works with special characters in the name
TEST_F(ObjectGetNameTest_99, GetNameSpecialCharacters_99) {
    Object obj(objName, "Name/With#Special.Chars");
    ASSERT_TRUE(obj.isName());
    const char* name = obj.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Name/With#Special.Chars");
}

// Test isName() returns true for objName type
TEST_F(ObjectGetNameTest_99, IsNameReturnsTrueForNameObject_99) {
    Object obj(objName, "SomeName");
    EXPECT_TRUE(obj.isName());
}

// Test isName(string_view) returns true when names match
TEST_F(ObjectGetNameTest_99, IsNameWithMatchingString_99) {
    Object obj(objName, "TargetName");
    EXPECT_TRUE(obj.isName("TargetName"));
}

// Test isName(string_view) returns false when names don't match
TEST_F(ObjectGetNameTest_99, IsNameWithNonMatchingString_99) {
    Object obj(objName, "TargetName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

// Test that isName returns false for non-Name objects
TEST_F(ObjectGetNameTest_99, IsNameReturnsFalseForNonNameObject_99) {
    Object obj(42);
    EXPECT_FALSE(obj.isName());
}

// Test getType returns objName for Name objects
TEST_F(ObjectGetNameTest_99, GetTypeReturnsObjNameForNameObject_99) {
    Object obj(objName, "TestName");
    EXPECT_EQ(obj.getType(), objName);
}

// Test getNameString returns a proper std::string
TEST_F(ObjectGetNameTest_99, GetNameStringReturnsStdString_99) {
    Object obj(objName, "StringName");
    ASSERT_TRUE(obj.isName());
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "StringName");
}

// Test that getName works after move construction
TEST_F(ObjectGetNameTest_99, GetNameAfterMoveConstruction_99) {
    Object obj1(objName, "MovedName");
    Object obj2(std::move(obj1));
    ASSERT_TRUE(obj2.isName());
    const char* name = obj2.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "MovedName");
}

// Test that getName works after move assignment
TEST_F(ObjectGetNameTest_99, GetNameAfterMoveAssignment_99) {
    Object obj1(objName, "AssignedName");
    Object obj2;
    obj2 = std::move(obj1);
    ASSERT_TRUE(obj2.isName());
    const char* name = obj2.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "AssignedName");
}

// Test that copy() preserves the name
TEST_F(ObjectGetNameTest_99, CopyPreservesName_99) {
    Object obj(objName, "CopyName");
    Object copied = obj.copy();
    ASSERT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyName");
}

// Test getTypeName for a Name object
TEST_F(ObjectGetNameTest_99, GetTypeNameForNameObject_99) {
    Object obj(objName, "TestName");
    const char* typeName = obj.getTypeName();
    ASSERT_NE(typeName, nullptr);
    // The type name should indicate it's a name object
    EXPECT_STREQ(typeName, "name");
}

// Test getName with string_view constructor
TEST_F(ObjectGetNameTest_99, GetNameFromStringView_99) {
    std::string_view sv = "ViewName";
    Object obj(objName, sv);
    ASSERT_TRUE(obj.isName());
    const char* name = obj.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "ViewName");
}

// Test that other object types are not Name
TEST_F(ObjectGetNameTest_99, BoolObjectIsNotName_99) {
    Object obj(true);
    EXPECT_FALSE(obj.isName());
    EXPECT_TRUE(obj.isBool());
}

TEST_F(ObjectGetNameTest_99, IntObjectIsNotName_99) {
    Object obj(42);
    EXPECT_FALSE(obj.isName());
    EXPECT_TRUE(obj.isInt());
}

TEST_F(ObjectGetNameTest_99, RealObjectIsNotName_99) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isName());
    EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectGetNameTest_99, NullObjectIsNotName_99) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isName());
    EXPECT_TRUE(obj.isNull());
}

// Test getName with name containing spaces
TEST_F(ObjectGetNameTest_99, GetNameWithSpaces_99) {
    Object obj(objName, "Name With Spaces");
    ASSERT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Name With Spaces");
}

// Test getName with numeric name
TEST_F(ObjectGetNameTest_99, GetNameWithNumericContent_99) {
    Object obj(objName, "12345");
    ASSERT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "12345");
}

// Test deepCopy preserves name
TEST_F(ObjectGetNameTest_99, DeepCopyPreservesName_99) {
    Object obj(objName, "DeepName");
    Object deepCopied = obj.deepCopy();
    ASSERT_TRUE(deepCopied.isName());
    EXPECT_STREQ(deepCopied.getName(), "DeepName");
}

// Test setToNull changes a Name object to null
TEST_F(ObjectGetNameTest_99, SetToNullChangesNameToNull_99) {
    Object obj(objName, "WillBeNull");
    ASSERT_TRUE(obj.isName());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isName());
}
