#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function isBlockAlignName from StructElement.cc
// Since it's a static function in a .cc file, we need to either:
// 1. Include the .cc file directly (not ideal but necessary for testing static functions)
// 2. Or replicate the function signature for testing
// 
// For this test, we'll define the function as it appears in the source,
// since it's a static function we need to test through its behavior.
// We include the source file to access the static function.

// Forward declare or include the static function
// Since isBlockAlignName is static in StructElement.cc, we need to include it
// or redefine access. We'll include the cc file in a namespace to avoid conflicts.

namespace test_block_align {
#include "StructElement.cc"
}

using test_block_align::isBlockAlignName;

class IsBlockAlignNameTest_1758 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that "Before" is recognized as a valid block align name
TEST_F(IsBlockAlignNameTest_1758, BeforeIsValid_1758) {
    Object obj(objName, "Before");
    EXPECT_TRUE(isBlockAlignName(&obj));
}

// Test that "Middle" is recognized as a valid block align name
TEST_F(IsBlockAlignNameTest_1758, MiddleIsValid_1758) {
    Object obj(objName, "Middle");
    EXPECT_TRUE(isBlockAlignName(&obj));
}

// Test that "After" is recognized as a valid block align name
TEST_F(IsBlockAlignNameTest_1758, AfterIsValid_1758) {
    Object obj(objName, "After");
    EXPECT_TRUE(isBlockAlignName(&obj));
}

// Test that "Justify" is recognized as a valid block align name
TEST_F(IsBlockAlignNameTest_1758, JustifyIsValid_1758) {
    Object obj(objName, "Justify");
    EXPECT_TRUE(isBlockAlignName(&obj));
}

// Test that an unrelated name is not recognized
TEST_F(IsBlockAlignNameTest_1758, InvalidNameReturnsFlase_1758) {
    Object obj(objName, "Center");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test that an empty name is not recognized
TEST_F(IsBlockAlignNameTest_1758, EmptyNameReturnsFalse_1758) {
    Object obj(objName, "");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test that a non-name object (integer) returns false
TEST_F(IsBlockAlignNameTest_1758, IntObjectReturnsFalse_1758) {
    Object obj(42);
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test that a non-name object (bool) returns false
TEST_F(IsBlockAlignNameTest_1758, BoolObjectReturnsFalse_1758) {
    Object obj(true);
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test that a null object returns false
TEST_F(IsBlockAlignNameTest_1758, NullObjectReturnsFalse_1758) {
    Object obj = Object::null();
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test that a string object with value "Before" returns false (not a name)
TEST_F(IsBlockAlignNameTest_1758, StringBeforeReturnsFalse_1758) {
    Object obj(std::string("Before"));
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test case sensitivity - "before" (lowercase) should not match
TEST_F(IsBlockAlignNameTest_1758, LowercaseBeforeReturnsFalse_1758) {
    Object obj(objName, "before");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test case sensitivity - "BEFORE" (uppercase) should not match
TEST_F(IsBlockAlignNameTest_1758, UppercaseBeforeReturnsFalse_1758) {
    Object obj(objName, "BEFORE");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test case sensitivity - "middle" (lowercase) should not match
TEST_F(IsBlockAlignNameTest_1758, LowercaseMiddleReturnsFalse_1758) {
    Object obj(objName, "middle");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test case sensitivity - "after" (lowercase) should not match
TEST_F(IsBlockAlignNameTest_1758, LowercaseAfterReturnsFalse_1758) {
    Object obj(objName, "after");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test case sensitivity - "justify" (lowercase) should not match
TEST_F(IsBlockAlignNameTest_1758, LowercaseJustifyReturnsFalse_1758) {
    Object obj(objName, "justify");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test with a name that is a prefix of a valid name
TEST_F(IsBlockAlignNameTest_1758, PrefixBeforReturnsFalse_1758) {
    Object obj(objName, "Befor");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test with a name that is a valid name with extra characters
TEST_F(IsBlockAlignNameTest_1758, BeforeExtraCharsReturnsFalse_1758) {
    Object obj(objName, "BeforeX");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test with a real (double) object
TEST_F(IsBlockAlignNameTest_1758, RealObjectReturnsFalse_1758) {
    Object obj(3.14);
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test with a none object
TEST_F(IsBlockAlignNameTest_1758, NoneObjectReturnsFalse_1758) {
    Object obj;
    EXPECT_FALSE(isBlockAlignName(&obj));
}

// Test with other common alignment-like names that are not valid
TEST_F(IsBlockAlignNameTest_1758, StartNameReturnsFalse_1758) {
    Object obj(objName, "Start");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

TEST_F(IsBlockAlignNameTest_1758, EndNameReturnsFalse_1758) {
    Object obj(objName, "End");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

TEST_F(IsBlockAlignNameTest_1758, LeftNameReturnsFalse_1758) {
    Object obj(objName, "Left");
    EXPECT_FALSE(isBlockAlignName(&obj));
}

TEST_F(IsBlockAlignNameTest_1758, RightNameReturnsFalse_1758) {
    Object obj(objName, "Right");
    EXPECT_FALSE(isBlockAlignName(&obj));
}
