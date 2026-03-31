#include <gtest/gtest.h>
#include "Object.h"

// Since isListNumberingName is a static function in StructElement.cc,
// we cannot directly call it from outside the translation unit.
// We need to either:
// 1. Include the source file to get access to the static function, or
// 2. Test it indirectly through the public interface.
// 
// For testing purposes, we'll re-declare/include to access the static function.
// Since it's static, we include the .cc file directly to make it accessible in this TU.

// We need to forward declare or include necessary headers
#include "StructElement.cc"

class IsListNumberingNameTest_1766 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test valid list numbering name: "None"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForNone_1766) {
    Object obj(objName, "None");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test valid list numbering name: "Disc"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForDisc_1766) {
    Object obj(objName, "Disc");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test valid list numbering name: "Circle"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForCircle_1766) {
    Object obj(objName, "Circle");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test valid list numbering name: "Square"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForSquare_1766) {
    Object obj(objName, "Square");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test valid list numbering name: "Decimal"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForDecimal_1766) {
    Object obj(objName, "Decimal");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test valid list numbering name: "UpperRoman"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForUpperRoman_1766) {
    Object obj(objName, "UpperRoman");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test valid list numbering name: "LowerRoman"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForLowerRoman_1766) {
    Object obj(objName, "LowerRoman");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test valid list numbering name: "UpperAlpha"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForUpperAlpha_1766) {
    Object obj(objName, "UpperAlpha");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test valid list numbering name: "LowerAlpha"
TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForLowerAlpha_1766) {
    Object obj(objName, "LowerAlpha");
    EXPECT_TRUE(isListNumberingName(&obj));
}

// Test invalid name: random string
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForInvalidName_1766) {
    Object obj(objName, "InvalidName");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test invalid name: empty string
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForEmptyName_1766) {
    Object obj(objName, "");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test case sensitivity: "none" (lowercase) should not match "None"
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForLowercaseNone_1766) {
    Object obj(objName, "none");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test case sensitivity: "disc" (lowercase) should not match "Disc"
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForLowercaseDisc_1766) {
    Object obj(objName, "disc");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test case sensitivity: "NONE" (all uppercase) should not match "None"
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForAllUppercaseNONE_1766) {
    Object obj(objName, "NONE");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test case sensitivity: "upperroman" should not match "UpperRoman"
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForLowercaseUpperRoman_1766) {
    Object obj(objName, "upperroman");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test case sensitivity: "UPPERALPHA" should not match "UpperAlpha"
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForAllUppercaseUPPERALPHA_1766) {
    Object obj(objName, "UPPERALPHA");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test with a non-name Object type (e.g., integer)
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForNonNameObjectInt_1766) {
    Object obj(42);
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test with a non-name Object type (e.g., boolean)
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForNonNameObjectBool_1766) {
    Object obj(true);
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test with a null Object
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForNullObject_1766) {
    Object obj = Object::null();
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test with a string Object (not a name)
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForStringObject_1766) {
    Object obj(std::string("None"));
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test similar but incorrect names
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForPartialMatch_1766) {
    Object obj(objName, "Decima");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test name with trailing space
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForNameWithTrailingSpace_1766) {
    Object obj(objName, "None ");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test name with leading space
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForNameWithLeadingSpace_1766) {
    Object obj(objName, " None");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test a completely unrelated name
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForUnrelatedName_1766) {
    Object obj(objName, "Bullet");
    EXPECT_FALSE(isListNumberingName(&obj));
}

// Test with "Ordered" - not a valid numbering name
TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForOrdered_1766) {
    Object obj(objName, "Ordered");
    EXPECT_FALSE(isListNumberingName(&obj));
}
