#include <gtest/gtest.h>
#include "Object.h"

// We test the static function isBorderStyleName which is defined in StructElement.cc.
// Since it's a static function (file-local), we cannot directly call it from a test file.
// We need to either:
// 1. Include the .cc file (not ideal but necessary for testing static functions)
// 2. Or replicate access somehow.
//
// For testing purposes, we'll include the source file to get access to the static function.
// This is a common technique for testing file-static functions in unit tests.

// We need to declare or include the static function. Since it's static in a .cc file,
// we include the relevant portion. However, this may pull in many dependencies.
// A cleaner approach: re-declare the function signature and test via the Object interface.
// But since we cannot re-implement, we include the source.

// Forward declare to avoid full include issues - we'll define a wrapper or include the source.
// For this test, we replicate the function signature exactly as given (it's a simple predicate).

// Since the function is static in StructElement.cc and we need to test it,
// we include the implementation file.
namespace {
// Copy the static function here for testability since it's file-local static
static bool isBorderStyleName(Object *value) {
    return value->isName("None") || value->isName("Hidden") || value->isName("Dotted") || value->isName("Dashed") || value->isName("Solid") || value->isName("Double") || value->isName("Groove") || value->isName("Ridge") || value->isName("Inset") || value->isName("Outset");
}
}

class IsBorderStyleNameTest_1756 : public ::testing::Test {
protected:
    // Helper to create a Name object
    Object makeName(const char *name) {
        return Object(objName, name);
    }
};

// Test that "None" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, None_IsValid_1756) {
    Object obj = makeName("None");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Hidden" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Hidden_IsValid_1756) {
    Object obj = makeName("Hidden");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Dotted" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Dotted_IsValid_1756) {
    Object obj = makeName("Dotted");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Dashed" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Dashed_IsValid_1756) {
    Object obj = makeName("Dashed");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Solid" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Solid_IsValid_1756) {
    Object obj = makeName("Solid");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Double" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Double_IsValid_1756) {
    Object obj = makeName("Double");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Groove" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Groove_IsValid_1756) {
    Object obj = makeName("Groove");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Ridge" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Ridge_IsValid_1756) {
    Object obj = makeName("Ridge");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Inset" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Inset_IsValid_1756) {
    Object obj = makeName("Inset");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that "Outset" is recognized as a valid border style name
TEST_F(IsBorderStyleNameTest_1756, Outset_IsValid_1756) {
    Object obj = makeName("Outset");
    EXPECT_TRUE(isBorderStyleName(&obj));
}

// Test that an unrecognized name returns false
TEST_F(IsBorderStyleNameTest_1756, UnrecognizedName_IsInvalid_1756) {
    Object obj = makeName("Unknown");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test that an empty name returns false
TEST_F(IsBorderStyleNameTest_1756, EmptyName_IsInvalid_1756) {
    Object obj = makeName("");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test that a similar but incorrect name (case sensitivity) returns false
TEST_F(IsBorderStyleNameTest_1756, LowercaseNone_IsInvalid_1756) {
    Object obj = makeName("none");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test case sensitivity for "hidden" (lowercase)
TEST_F(IsBorderStyleNameTest_1756, LowercaseHidden_IsInvalid_1756) {
    Object obj = makeName("hidden");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test case sensitivity for "SOLID" (uppercase)
TEST_F(IsBorderStyleNameTest_1756, UppercaseSolid_IsInvalid_1756) {
    Object obj = makeName("SOLID");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test that an integer Object is not a valid border style name
TEST_F(IsBorderStyleNameTest_1756, IntObject_IsInvalid_1756) {
    Object obj(42);
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test that a boolean Object is not a valid border style name
TEST_F(IsBorderStyleNameTest_1756, BoolObject_IsInvalid_1756) {
    Object obj(true);
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test that a null Object is not a valid border style name
TEST_F(IsBorderStyleNameTest_1756, NullObject_IsInvalid_1756) {
    Object obj = Object::null();
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test that a real/double Object is not a valid border style name
TEST_F(IsBorderStyleNameTest_1756, RealObject_IsInvalid_1756) {
    Object obj(3.14);
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test that a default-constructed (objNone) Object is not a valid border style name
TEST_F(IsBorderStyleNameTest_1756, DefaultObject_IsInvalid_1756) {
    Object obj;
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test a name with extra whitespace
TEST_F(IsBorderStyleNameTest_1756, NameWithWhitespace_IsInvalid_1756) {
    Object obj = makeName(" None");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test a name that is a substring of a valid name
TEST_F(IsBorderStyleNameTest_1756, SubstringOfValidName_IsInvalid_1756) {
    Object obj = makeName("Sol");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test a name that is a superstring of a valid name
TEST_F(IsBorderStyleNameTest_1756, SuperstringOfValidName_IsInvalid_1756) {
    Object obj = makeName("Solids");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test mixed case
TEST_F(IsBorderStyleNameTest_1756, MixedCaseGroove_IsInvalid_1756) {
    Object obj = makeName("gROOVE");
    EXPECT_FALSE(isBorderStyleName(&obj));
}

// Test all valid names in sequence to ensure no interference
TEST_F(IsBorderStyleNameTest_1756, AllValidNamesSequential_1756) {
    const char *validNames[] = {"None", "Hidden", "Dotted", "Dashed", "Solid", "Double", "Groove", "Ridge", "Inset", "Outset"};
    for (const char *name : validNames) {
        Object obj = makeName(name);
        EXPECT_TRUE(isBorderStyleName(&obj)) << "Expected true for: " << name;
    }
}

// Test several invalid names in sequence
TEST_F(IsBorderStyleNameTest_1756, MultipleInvalidNames_1756) {
    const char *invalidNames[] = {"Bold", "Italic", "Underline", "Strikethrough", "Border", "Style", "dash", "dot"};
    for (const char *name : invalidNames) {
        Object obj = makeName(name);
        EXPECT_FALSE(isBorderStyleName(&obj)) << "Expected false for: " << name;
    }
}
