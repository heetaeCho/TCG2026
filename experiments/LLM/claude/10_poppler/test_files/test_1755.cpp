#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function isWritingModeName from StructElement.cc
// Since it's a static function in a .cc file, we need to either:
// 1. Include the source file directly, or
// 2. Recreate the function signature for testing purposes
// Since we're testing the interface behavior, we'll define the function here
// matching its exact signature to test it.

// The function under test (extracted from StructElement.cc)
static bool isWritingModeName(Object *value) {
    return value->isName("LrTb") || value->isName("RlTb") || value->isName("TbRl");
}

class IsWritingModeNameTest_1755 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with valid writing mode "LrTb" (Left-to-right, Top-to-bottom)
TEST_F(IsWritingModeNameTest_1755, LrTbReturnsTrue_1755) {
    Object obj(objName, "LrTb");
    EXPECT_TRUE(isWritingModeName(&obj));
}

// Test with valid writing mode "RlTb" (Right-to-left, Top-to-bottom)
TEST_F(IsWritingModeNameTest_1755, RlTbReturnsTrue_1755) {
    Object obj(objName, "RlTb");
    EXPECT_TRUE(isWritingModeName(&obj));
}

// Test with valid writing mode "TbRl" (Top-to-bottom, Right-to-left)
TEST_F(IsWritingModeNameTest_1755, TbRlReturnsTrue_1755) {
    Object obj(objName, "TbRl");
    EXPECT_TRUE(isWritingModeName(&obj));
}

// Test with an invalid writing mode name
TEST_F(IsWritingModeNameTest_1755, InvalidNameReturnsFalse_1755) {
    Object obj(objName, "Invalid");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with empty name
TEST_F(IsWritingModeNameTest_1755, EmptyNameReturnsFalse_1755) {
    Object obj(objName, "");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a name that is a prefix of a valid writing mode
TEST_F(IsWritingModeNameTest_1755, PartialNameLrReturnsFalse_1755) {
    Object obj(objName, "Lr");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a name that is a prefix of a valid writing mode
TEST_F(IsWritingModeNameTest_1755, PartialNameTbReturnsFalse_1755) {
    Object obj(objName, "Tb");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with case sensitivity - lowercase
TEST_F(IsWritingModeNameTest_1755, LowercaseLrtbReturnsFalse_1755) {
    Object obj(objName, "lrtb");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with case sensitivity - all uppercase
TEST_F(IsWritingModeNameTest_1755, UppercaseLRTBReturnsFalse_1755) {
    Object obj(objName, "LRTB");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with case sensitivity - mixed case variant
TEST_F(IsWritingModeNameTest_1755, MixedCaseRltbReturnsFalse_1755) {
    Object obj(objName, "rltb");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with case sensitivity - TbRl variant
TEST_F(IsWritingModeNameTest_1755, MixedCaseTbrlReturnsFalse_1755) {
    Object obj(objName, "tbrl");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a non-name object type (integer)
TEST_F(IsWritingModeNameTest_1755, IntegerObjectReturnsFalse_1755) {
    Object obj(42);
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a non-name object type (boolean)
TEST_F(IsWritingModeNameTest_1755, BoolObjectReturnsFalse_1755) {
    Object obj(true);
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a null object
TEST_F(IsWritingModeNameTest_1755, NullObjectReturnsFalse_1755) {
    Object obj = Object::null();
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a name that has extra characters appended
TEST_F(IsWritingModeNameTest_1755, LrTbExtraCharsReturnsFalse_1755) {
    Object obj(objName, "LrTbX");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a name that has extra characters appended
TEST_F(IsWritingModeNameTest_1755, RlTbExtraCharsReturnsFalse_1755) {
    Object obj(objName, "RlTbX");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a name that has extra characters appended
TEST_F(IsWritingModeNameTest_1755, TbRlExtraCharsReturnsFalse_1755) {
    Object obj(objName, "TbRlX");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a name that has leading space
TEST_F(IsWritingModeNameTest_1755, LeadingSpaceLrTbReturnsFalse_1755) {
    Object obj(objName, " LrTb");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a name that has trailing space
TEST_F(IsWritingModeNameTest_1755, TrailingSpaceLrTbReturnsFalse_1755) {
    Object obj(objName, "LrTb ");
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a real number object
TEST_F(IsWritingModeNameTest_1755, RealObjectReturnsFalse_1755) {
    Object obj(3.14);
    EXPECT_FALSE(isWritingModeName(&obj));
}

// Test with a default-constructed (none) object
TEST_F(IsWritingModeNameTest_1755, NoneObjectReturnsFalse_1755) {
    Object obj;
    EXPECT_FALSE(isWritingModeName(&obj));
}
