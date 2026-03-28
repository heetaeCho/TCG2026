#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function isRubyAlignName which is defined in StructElement.cc.
// Since it's a static function (file-local linkage), we cannot directly call it from a test file.
// We need to either:
// 1. Include the .cc file (not ideal but necessary for testing static functions)
// 2. Or replicate the function signature for testing purposes.
//
// Since the function is static and we're told to treat it as a black box, we'll include
// the source to get access to the static function. We wrap it to avoid ODR issues.

// We define a wrapper to access the static function
namespace {
// Replicate the static function signature - we include the source file to get access
// Since it's static, we include the .cc file in this translation unit
}

// Include the implementation file to access the static function
// This is a common technique for testing static (file-scope) functions
#include "StructElement.cc"

class IsRubyAlignNameTest_1763 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that "Start" is recognized as a valid RubyAlign name
TEST_F(IsRubyAlignNameTest_1763, StartIsValid_1763) {
    Object obj(objName, "Start");
    EXPECT_TRUE(isRubyAlignName(&obj));
}

// Test that "End" is recognized as a valid RubyAlign name
TEST_F(IsRubyAlignNameTest_1763, EndIsValid_1763) {
    Object obj(objName, "End");
    EXPECT_TRUE(isRubyAlignName(&obj));
}

// Test that "Center" is recognized as a valid RubyAlign name
TEST_F(IsRubyAlignNameTest_1763, CenterIsValid_1763) {
    Object obj(objName, "Center");
    EXPECT_TRUE(isRubyAlignName(&obj));
}

// Test that "Justify" is recognized as a valid RubyAlign name
TEST_F(IsRubyAlignNameTest_1763, JustifyIsValid_1763) {
    Object obj(objName, "Justify");
    EXPECT_TRUE(isRubyAlignName(&obj));
}

// Test that "Distribute" is recognized as a valid RubyAlign name
TEST_F(IsRubyAlignNameTest_1763, DistributeIsValid_1763) {
    Object obj(objName, "Distribute");
    EXPECT_TRUE(isRubyAlignName(&obj));
}

// Test that an unrecognized name returns false
TEST_F(IsRubyAlignNameTest_1763, UnrecognizedNameReturnsFalse_1763) {
    Object obj(objName, "Unknown");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test that an empty name returns false
TEST_F(IsRubyAlignNameTest_1763, EmptyNameReturnsFalse_1763) {
    Object obj(objName, "");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test that a non-name object returns false (e.g., an integer)
TEST_F(IsRubyAlignNameTest_1763, NonNameObjectReturnsFalse_1763) {
    Object obj(42);
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test that a string object (not a name) returns false even with valid content
TEST_F(IsRubyAlignNameTest_1763, StringObjectWithValidContentReturnsFalse_1763) {
    Object obj(std::string("Start"));
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test that a null object returns false
TEST_F(IsRubyAlignNameTest_1763, NullObjectReturnsFalse_1763) {
    Object obj = Object::null();
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test that a boolean object returns false
TEST_F(IsRubyAlignNameTest_1763, BoolObjectReturnsFalse_1763) {
    Object obj(true);
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test that a real/double object returns false
TEST_F(IsRubyAlignNameTest_1763, RealObjectReturnsFalse_1763) {
    Object obj(3.14);
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test case sensitivity - lowercase "start" should not match
TEST_F(IsRubyAlignNameTest_1763, LowercaseStartReturnsFalse_1763) {
    Object obj(objName, "start");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test case sensitivity - lowercase "end" should not match
TEST_F(IsRubyAlignNameTest_1763, LowercaseEndReturnsFalse_1763) {
    Object obj(objName, "end");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test case sensitivity - lowercase "center" should not match
TEST_F(IsRubyAlignNameTest_1763, LowercaseCenterReturnsFalse_1763) {
    Object obj(objName, "center");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test case sensitivity - lowercase "justify" should not match
TEST_F(IsRubyAlignNameTest_1763, LowercaseJustifyReturnsFalse_1763) {
    Object obj(objName, "justify");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test case sensitivity - lowercase "distribute" should not match
TEST_F(IsRubyAlignNameTest_1763, LowercaseDistributeReturnsFalse_1763) {
    Object obj(objName, "distribute");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test that a similar but different name doesn't match
TEST_F(IsRubyAlignNameTest_1763, SimilarNameStartExtraCharsReturnsFalse_1763) {
    Object obj(objName, "StartX");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test with all uppercase
TEST_F(IsRubyAlignNameTest_1763, AllUppercaseStartReturnsFalse_1763) {
    Object obj(objName, "START");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test with a name that has leading whitespace
TEST_F(IsRubyAlignNameTest_1763, LeadingWhitespaceReturnsFalse_1763) {
    Object obj(objName, " Start");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test with a name that has trailing whitespace
TEST_F(IsRubyAlignNameTest_1763, TrailingWhitespaceReturnsFalse_1763) {
    Object obj(objName, "Start ");
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test error object returns false
TEST_F(IsRubyAlignNameTest_1763, ErrorObjectReturnsFalse_1763) {
    Object obj = Object::error();
    EXPECT_FALSE(isRubyAlignName(&obj));
}

// Test EOF object returns false
TEST_F(IsRubyAlignNameTest_1763, EofObjectReturnsFalse_1763) {
    Object obj = Object::eof();
    EXPECT_FALSE(isRubyAlignName(&obj));
}
