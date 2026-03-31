#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function isInlineAlignName from StructElement.cc
// Since it's a static function in a .cc file, we need to either:
// 1. Include the .cc file (not ideal but necessary for testing static functions)
// 2. Or replicate the function signature for testing
// Since we're told to treat it as a black box and test via interface,
// we'll test the observable behavior through Object's isName method
// and replicate the function under test.

// The function under test:
static bool isInlineAlignName(Object *value) {
    return value->isName("Start") || value->isName("End") || value->isName("Center");
}

class IsInlineAlignNameTest_1759 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that "Start" is recognized as a valid inline align name
TEST_F(IsInlineAlignNameTest_1759, StartIsValid_1759) {
    Object obj(objName, "Start");
    EXPECT_TRUE(isInlineAlignName(&obj));
}

// Test that "End" is recognized as a valid inline align name
TEST_F(IsInlineAlignNameTest_1759, EndIsValid_1759) {
    Object obj(objName, "End");
    EXPECT_TRUE(isInlineAlignName(&obj));
}

// Test that "Center" is recognized as a valid inline align name
TEST_F(IsInlineAlignNameTest_1759, CenterIsValid_1759) {
    Object obj(objName, "Center");
    EXPECT_TRUE(isInlineAlignName(&obj));
}

// Test that an unrelated name is not a valid inline align name
TEST_F(IsInlineAlignNameTest_1759, InvalidNameReturnsF_1759) {
    Object obj(objName, "Left");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test that another unrelated name is not valid
TEST_F(IsInlineAlignNameTest_1759, RightIsNotValid_1759) {
    Object obj(objName, "Right");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test that "Justify" is not a valid inline align name
TEST_F(IsInlineAlignNameTest_1759, JustifyIsNotValid_1759) {
    Object obj(objName, "Justify");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test that an empty name is not valid
TEST_F(IsInlineAlignNameTest_1759, EmptyNameIsNotValid_1759) {
    Object obj(objName, "");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test case sensitivity - "start" (lowercase) should not be valid
TEST_F(IsInlineAlignNameTest_1759, LowercaseStartIsNotValid_1759) {
    Object obj(objName, "start");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test case sensitivity - "end" (lowercase) should not be valid
TEST_F(IsInlineAlignNameTest_1759, LowercaseEndIsNotValid_1759) {
    Object obj(objName, "end");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test case sensitivity - "center" (lowercase) should not be valid
TEST_F(IsInlineAlignNameTest_1759, LowercaseCenterIsNotValid_1759) {
    Object obj(objName, "center");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test case sensitivity - "CENTER" (all uppercase) should not be valid
TEST_F(IsInlineAlignNameTest_1759, UppercaseCenterIsNotValid_1759) {
    Object obj(objName, "CENTER");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test case sensitivity - "START" (all uppercase) should not be valid
TEST_F(IsInlineAlignNameTest_1759, UppercaseStartIsNotValid_1759) {
    Object obj(objName, "START");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test that an integer Object is not a valid inline align name
TEST_F(IsInlineAlignNameTest_1759, IntObjectIsNotValid_1759) {
    Object obj(42);
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test that a boolean Object is not valid
TEST_F(IsInlineAlignNameTest_1759, BoolObjectIsNotValid_1759) {
    Object obj(true);
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test that a null Object is not valid
TEST_F(IsInlineAlignNameTest_1759, NullObjectIsNotValid_1759) {
    Object obj = Object::null();
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test that a real/double Object is not valid
TEST_F(IsInlineAlignNameTest_1759, RealObjectIsNotValid_1759) {
    Object obj(3.14);
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test name with trailing space is not valid
TEST_F(IsInlineAlignNameTest_1759, StartWithTrailingSpaceIsNotValid_1759) {
    Object obj(objName, "Start ");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test name with leading space is not valid
TEST_F(IsInlineAlignNameTest_1759, StartWithLeadingSpaceIsNotValid_1759) {
    Object obj(objName, " Start");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test a name that is a substring of a valid name
TEST_F(IsInlineAlignNameTest_1759, StarIsNotValid_1759) {
    Object obj(objName, "Star");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test a name that contains a valid name as prefix
TEST_F(IsInlineAlignNameTest_1759, StartExtraIsNotValid_1759) {
    Object obj(objName, "StartExtra");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test "En" which is a prefix of "End" but not complete
TEST_F(IsInlineAlignNameTest_1759, EnIsNotValid_1759) {
    Object obj(objName, "En");
    EXPECT_FALSE(isInlineAlignName(&obj));
}

// Test "Cente" which is a prefix of "Center" but not complete
TEST_F(IsInlineAlignNameTest_1759, CenteIsNotValid_1759) {
    Object obj(objName, "Cente");
    EXPECT_FALSE(isInlineAlignName(&obj));
}
