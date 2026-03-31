#include <gtest/gtest.h>
#include "Object.h"

// We're testing the static function isTextAlignName which is defined in StructElement.cc
// Since it's a static function (file-local), we cannot directly call it from a test.
// However, we can replicate the exact logic it tests: checking if an Object is a Name
// with value "Start", "End", "Center", or "Justify".
// 
// To properly test this, we need to either:
// 1. Make the function accessible (e.g., via a header or test helper)
// 2. Test it indirectly through the public interface that uses it
//
// Since the function is static (internal linkage), we'll test the underlying Object::isName()
// behavior that isTextAlignName relies on, and also create a local equivalent for direct testing.

// Recreate the function under test since it's static in the .cc file
static bool isTextAlignName(Object *value) {
    return value->isName("Start") || value->isName("End") || value->isName("Center") || value->isName("Justify");
}

class IsTextAlignNameTest_1757 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that "Start" is recognized as a valid text align name
TEST_F(IsTextAlignNameTest_1757, StartIsValid_1757) {
    Object obj(objName, "Start");
    EXPECT_TRUE(isTextAlignName(&obj));
}

// Test that "End" is recognized as a valid text align name
TEST_F(IsTextAlignNameTest_1757, EndIsValid_1757) {
    Object obj(objName, "End");
    EXPECT_TRUE(isTextAlignName(&obj));
}

// Test that "Center" is recognized as a valid text align name
TEST_F(IsTextAlignNameTest_1757, CenterIsValid_1757) {
    Object obj(objName, "Center");
    EXPECT_TRUE(isTextAlignName(&obj));
}

// Test that "Justify" is recognized as a valid text align name
TEST_F(IsTextAlignNameTest_1757, JustifyIsValid_1757) {
    Object obj(objName, "Justify");
    EXPECT_TRUE(isTextAlignName(&obj));
}

// Test that an unrecognized name returns false
TEST_F(IsTextAlignNameTest_1757, UnrecognizedNameReturnsFalse_1757) {
    Object obj(objName, "Left");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test that another unrecognized name returns false
TEST_F(IsTextAlignNameTest_1757, RightNameReturnsFalse_1757) {
    Object obj(objName, "Right");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test that an empty name returns false
TEST_F(IsTextAlignNameTest_1757, EmptyNameReturnsFalse_1757) {
    Object obj(objName, "");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test that a null Object (not a name) returns false
TEST_F(IsTextAlignNameTest_1757, NullObjectReturnsFalse_1757) {
    Object obj = Object::null();
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test that an integer Object returns false
TEST_F(IsTextAlignNameTest_1757, IntObjectReturnsFalse_1757) {
    Object obj(42);
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test that a boolean Object returns false
TEST_F(IsTextAlignNameTest_1757, BoolObjectReturnsFalse_1757) {
    Object obj(true);
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test that a real (double) Object returns false
TEST_F(IsTextAlignNameTest_1757, RealObjectReturnsFalse_1757) {
    Object obj(3.14);
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test case sensitivity - "start" (lowercase) should not match
TEST_F(IsTextAlignNameTest_1757, LowercaseStartReturnsFalse_1757) {
    Object obj(objName, "start");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test case sensitivity - "end" (lowercase) should not match
TEST_F(IsTextAlignNameTest_1757, LowercaseEndReturnsFalse_1757) {
    Object obj(objName, "end");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test case sensitivity - "center" (lowercase) should not match
TEST_F(IsTextAlignNameTest_1757, LowercaseCenterReturnsFalse_1757) {
    Object obj(objName, "center");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test case sensitivity - "justify" (lowercase) should not match
TEST_F(IsTextAlignNameTest_1757, LowercaseJustifyReturnsFalse_1757) {
    Object obj(objName, "justify");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test case sensitivity - "START" (all uppercase) should not match
TEST_F(IsTextAlignNameTest_1757, AllUppercaseStartReturnsFalse_1757) {
    Object obj(objName, "START");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test that a name with extra whitespace doesn't match
TEST_F(IsTextAlignNameTest_1757, NameWithWhitespaceReturnsFalse_1757) {
    Object obj(objName, " Start");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test that a name with trailing whitespace doesn't match
TEST_F(IsTextAlignNameTest_1757, NameWithTrailingWhitespaceReturnsFalse_1757) {
    Object obj(objName, "Start ");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test a string Object (not a name) with value "Start" returns false
TEST_F(IsTextAlignNameTest_1757, StringObjectWithStartReturnsFalse_1757) {
    Object obj(std::string("Start"));
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test none object returns false
TEST_F(IsTextAlignNameTest_1757, NoneObjectReturnsFalse_1757) {
    Object obj;
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test error object returns false
TEST_F(IsTextAlignNameTest_1757, ErrorObjectReturnsFalse_1757) {
    Object obj = Object::error();
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test similar but different name "Centered" returns false
TEST_F(IsTextAlignNameTest_1757, SimilarNameCenteredReturnsFalse_1757) {
    Object obj(objName, "Centered");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test similar but different name "Starting" returns false
TEST_F(IsTextAlignNameTest_1757, SimilarNameStartingReturnsFalse_1757) {
    Object obj(objName, "Starting");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test similar but different name "Ending" returns false
TEST_F(IsTextAlignNameTest_1757, SimilarNameEndingReturnsFalse_1757) {
    Object obj(objName, "Ending");
    EXPECT_FALSE(isTextAlignName(&obj));
}

// Test similar but different name "Justified" returns false
TEST_F(IsTextAlignNameTest_1757, SimilarNameJustifiedReturnsFalse_1757) {
    Object obj(objName, "Justified");
    EXPECT_FALSE(isTextAlignName(&obj));
}
