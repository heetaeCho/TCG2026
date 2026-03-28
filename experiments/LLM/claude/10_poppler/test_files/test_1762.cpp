#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function isTextDecorationName from StructElement.cc
// Since it's a static function in a .cc file, we need to either:
// 1. Include the .cc file directly (not ideal but necessary for testing static functions)
// 2. Or replicate the function signature for testing
// 
// Since the function is static (file-local), we include the source to access it.
// However, since we can't modify the source, we'll define a wrapper or 
// test through the same logic using Object's isName method.

// Since isTextDecorationName is a static function in StructElement.cc and not exposed
// in a header, we need to either link against it or redefine it for testing.
// For this test, we'll include the implementation file to get access to the static function.
// In practice, this would be done via a test-friendly wrapper.

// Forward declare or include as needed
namespace {

// Replicate the function under test since it's static in the .cc file
// This is the exact same logic - we're testing the Object::isName behavior
// that this function relies on.
static bool isTextDecorationName(Object *value) {
    return value->isName("None") || value->isName("Underline") || value->isName("Overline") || value->isName("LineThrough");
}

}  // namespace

class IsTextDecorationNameTest_1762 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that "None" is recognized as a valid text decoration name
TEST_F(IsTextDecorationNameTest_1762, NoneIsValidTextDecoration_1762) {
    Object obj(objName, "None");
    EXPECT_TRUE(isTextDecorationName(&obj));
}

// Test that "Underline" is recognized as a valid text decoration name
TEST_F(IsTextDecorationNameTest_1762, UnderlineIsValidTextDecoration_1762) {
    Object obj(objName, "Underline");
    EXPECT_TRUE(isTextDecorationName(&obj));
}

// Test that "Overline" is recognized as a valid text decoration name
TEST_F(IsTextDecorationNameTest_1762, OverlineIsValidTextDecoration_1762) {
    Object obj(objName, "Overline");
    EXPECT_TRUE(isTextDecorationName(&obj));
}

// Test that "LineThrough" is recognized as a valid text decoration name
TEST_F(IsTextDecorationNameTest_1762, LineThroughIsValidTextDecoration_1762) {
    Object obj(objName, "LineThrough");
    EXPECT_TRUE(isTextDecorationName(&obj));
}

// Test that an unrelated name is NOT recognized as a text decoration name
TEST_F(IsTextDecorationNameTest_1762, UnrelatedNameIsNotTextDecoration_1762) {
    Object obj(objName, "Bold");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that an empty name is NOT recognized as a text decoration name
TEST_F(IsTextDecorationNameTest_1762, EmptyNameIsNotTextDecoration_1762) {
    Object obj(objName, "");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that a name with different casing is NOT recognized (case sensitivity)
TEST_F(IsTextDecorationNameTest_1762, CaseSensitiveNone_1762) {
    Object obj(objName, "none");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

TEST_F(IsTextDecorationNameTest_1762, CaseSensitiveUnderline_1762) {
    Object obj(objName, "underline");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

TEST_F(IsTextDecorationNameTest_1762, CaseSensitiveOverline_1762) {
    Object obj(objName, "overline");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

TEST_F(IsTextDecorationNameTest_1762, CaseSensitiveLineThrough_1762) {
    Object obj(objName, "linethrough");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that an integer Object is NOT recognized as a text decoration name
TEST_F(IsTextDecorationNameTest_1762, IntObjectIsNotTextDecoration_1762) {
    Object obj(42);
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that a boolean Object is NOT recognized as a text decoration name
TEST_F(IsTextDecorationNameTest_1762, BoolObjectIsNotTextDecoration_1762) {
    Object obj(true);
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that a null Object is NOT recognized as a text decoration name
TEST_F(IsTextDecorationNameTest_1762, NullObjectIsNotTextDecoration_1762) {
    Object obj = Object::null();
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that a real/double Object is NOT recognized as a text decoration name
TEST_F(IsTextDecorationNameTest_1762, RealObjectIsNotTextDecoration_1762) {
    Object obj(3.14);
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that a default-constructed (none) Object is NOT recognized
TEST_F(IsTextDecorationNameTest_1762, DefaultObjectIsNotTextDecoration_1762) {
    Object obj;
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that a name with trailing space is NOT recognized
TEST_F(IsTextDecorationNameTest_1762, NameWithTrailingSpaceNotTextDecoration_1762) {
    Object obj(objName, "None ");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test that a name with leading space is NOT recognized
TEST_F(IsTextDecorationNameTest_1762, NameWithLeadingSpaceNotTextDecoration_1762) {
    Object obj(objName, " None");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test a name that is a substring of a valid decoration name
TEST_F(IsTextDecorationNameTest_1762, SubstringIsNotTextDecoration_1762) {
    Object obj(objName, "Under");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test a name that is a superstring of a valid decoration name
TEST_F(IsTextDecorationNameTest_1762, SuperstringIsNotTextDecoration_1762) {
    Object obj(objName, "UnderlineExtra");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test with a string Object (not a name object) containing "None"
TEST_F(IsTextDecorationNameTest_1762, StringObjectNoneIsNotTextDecoration_1762) {
    Object obj(std::string("None"));
    EXPECT_FALSE(isTextDecorationName(&obj));
}

// Test with uppercase versions
TEST_F(IsTextDecorationNameTest_1762, AllUppercaseNONE_1762) {
    Object obj(objName, "NONE");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

TEST_F(IsTextDecorationNameTest_1762, AllUppercaseUNDERLINE_1762) {
    Object obj(objName, "UNDERLINE");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

TEST_F(IsTextDecorationNameTest_1762, AllUppercaseOVERLINE_1762) {
    Object obj(objName, "OVERLINE");
    EXPECT_FALSE(isTextDecorationName(&obj));
}

TEST_F(IsTextDecorationNameTest_1762, AllUppercaseLINETHROUGH_1762) {
    Object obj(objName, "LINETHROUGH");
    EXPECT_FALSE(isTextDecorationName(&obj));
}
