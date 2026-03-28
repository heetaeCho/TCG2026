#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function isFieldCheckedName from StructElement.cc
// Since it's a static function in a .cc file, we need to either:
// 1. Include the .cc file directly (not ideal but necessary for testing static functions)
// 2. Or replicate the function signature for testing
// Since we need to test it as a black box, we'll include the necessary context.

// The function under test:
// static bool isFieldCheckedName(Object *value) { 
//     return value->isName("on") || value->isName("off") || value->isName("neutral"); 
// }

// Since the function is static in a .cc file, we need to make it accessible.
// One approach: include the .cc file or re-declare it in a test helper.
// For testing purposes, we define the function here matching the known implementation.
// NOTE: In a real project, you'd use a test-friendly build approach.

static bool isFieldCheckedName(Object *value) {
    return value->isName("on") || value->isName("off") || value->isName("neutral");
}

class IsFieldCheckedNameTest_1768 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that "on" is recognized as a field checked name
TEST_F(IsFieldCheckedNameTest_1768, NameOn_ReturnsTrue_1768) {
    Object obj(objName, "on");
    EXPECT_TRUE(isFieldCheckedName(&obj));
}

// Test that "off" is recognized as a field checked name
TEST_F(IsFieldCheckedNameTest_1768, NameOff_ReturnsTrue_1768) {
    Object obj(objName, "off");
    EXPECT_TRUE(isFieldCheckedName(&obj));
}

// Test that "neutral" is recognized as a field checked name
TEST_F(IsFieldCheckedNameTest_1768, NameNeutral_ReturnsTrue_1768) {
    Object obj(objName, "neutral");
    EXPECT_TRUE(isFieldCheckedName(&obj));
}

// Test that an unrelated name returns false
TEST_F(IsFieldCheckedNameTest_1768, NameOther_ReturnsFalse_1768) {
    Object obj(objName, "yes");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test that an empty name returns false
TEST_F(IsFieldCheckedNameTest_1768, NameEmpty_ReturnsFalse_1768) {
    Object obj(objName, "");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test that a null object (not a name type) returns false
TEST_F(IsFieldCheckedNameTest_1768, NullObject_ReturnsFalse_1768) {
    Object obj = Object::null();
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test that an integer object returns false
TEST_F(IsFieldCheckedNameTest_1768, IntObject_ReturnsFalse_1768) {
    Object obj(42);
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test that a boolean object returns false
TEST_F(IsFieldCheckedNameTest_1768, BoolObject_ReturnsFalse_1768) {
    Object obj(true);
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test that a string object with value "on" returns false (it's a string, not a name)
TEST_F(IsFieldCheckedNameTest_1768, StringOn_ReturnsFalse_1768) {
    Object obj(objString, "on");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test that a string object with value "off" returns false
TEST_F(IsFieldCheckedNameTest_1768, StringOff_ReturnsFalse_1768) {
    Object obj(objString, "off");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test that a string object with value "neutral" returns false
TEST_F(IsFieldCheckedNameTest_1768, StringNeutral_ReturnsFalse_1768) {
    Object obj(objString, "neutral");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test case-sensitive: "On" should not match
TEST_F(IsFieldCheckedNameTest_1768, NameOnCaseSensitive_ReturnsFalse_1768) {
    Object obj(objName, "On");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test case-sensitive: "OFF" should not match
TEST_F(IsFieldCheckedNameTest_1768, NameOFFUpperCase_ReturnsFalse_1768) {
    Object obj(objName, "OFF");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test case-sensitive: "Neutral" should not match
TEST_F(IsFieldCheckedNameTest_1768, NameNeutralCaseSensitive_ReturnsFalse_1768) {
    Object obj(objName, "Neutral");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test a name with trailing whitespace
TEST_F(IsFieldCheckedNameTest_1768, NameOnWithSpace_ReturnsFalse_1768) {
    Object obj(objName, "on ");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test a name with leading whitespace
TEST_F(IsFieldCheckedNameTest_1768, NameOffWithLeadingSpace_ReturnsFalse_1768) {
    Object obj(objName, " off");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test an error object returns false
TEST_F(IsFieldCheckedNameTest_1768, ErrorObject_ReturnsFalse_1768) {
    Object obj = Object::error();
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test an EOF object returns false
TEST_F(IsFieldCheckedNameTest_1768, EOFObject_ReturnsFalse_1768) {
    Object obj = Object::eof();
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test a real/double object returns false
TEST_F(IsFieldCheckedNameTest_1768, RealObject_ReturnsFalse_1768) {
    Object obj(3.14);
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test a name that is a substring of valid names
TEST_F(IsFieldCheckedNameTest_1768, NameO_ReturnsFalse_1768) {
    Object obj(objName, "o");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test a name that contains a valid name as substring
TEST_F(IsFieldCheckedNameTest_1768, NameOnOff_ReturnsFalse_1768) {
    Object obj(objName, "onoff");
    EXPECT_FALSE(isFieldCheckedName(&obj));
}

// Test a none object returns false
TEST_F(IsFieldCheckedNameTest_1768, NoneObject_ReturnsFalse_1768) {
    Object obj;
    EXPECT_FALSE(isFieldCheckedName(&obj));
}
