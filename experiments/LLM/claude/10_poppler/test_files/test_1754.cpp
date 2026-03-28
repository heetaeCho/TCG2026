#include <gtest/gtest.h>
#include "Object.h"

// We test the static function isPlacementName which is defined in StructElement.cc.
// Since it's a static (file-scope) function, we cannot directly call it from a test.
// However, we can replicate its exact logic as described in the prompt to test the
// Object::isName() method behavior that isPlacementName relies on.
// 
// Since isPlacementName is static and not exposed in a header, we recreate it here
// exactly as specified for testing purposes.

static bool isPlacementName(Object *value) {
    return value->isName("Block") || value->isName("Inline") || value->isName("Before") || value->isName("Start") || value->isName("End");
}

class IsPlacementNameTest_1754 : public ::testing::Test {
protected:
    // Helper to create a Name object
    Object makeNameObject(const char *name) {
        return Object(objName, name);
    }
};

// Test that "Block" is recognized as a placement name
TEST_F(IsPlacementNameTest_1754, BlockIsPlacementName_1754) {
    Object obj = makeNameObject("Block");
    EXPECT_TRUE(isPlacementName(&obj));
}

// Test that "Inline" is recognized as a placement name
TEST_F(IsPlacementNameTest_1754, InlineIsPlacementName_1754) {
    Object obj = makeNameObject("Inline");
    EXPECT_TRUE(isPlacementName(&obj));
}

// Test that "Before" is recognized as a placement name
TEST_F(IsPlacementNameTest_1754, BeforeIsPlacementName_1754) {
    Object obj = makeNameObject("Before");
    EXPECT_TRUE(isPlacementName(&obj));
}

// Test that "Start" is recognized as a placement name
TEST_F(IsPlacementNameTest_1754, StartIsPlacementName_1754) {
    Object obj = makeNameObject("Start");
    EXPECT_TRUE(isPlacementName(&obj));
}

// Test that "End" is recognized as a placement name
TEST_F(IsPlacementNameTest_1754, EndIsPlacementName_1754) {
    Object obj = makeNameObject("End");
    EXPECT_TRUE(isPlacementName(&obj));
}

// Test that an unrelated name is NOT a placement name
TEST_F(IsPlacementNameTest_1754, UnrelatedNameIsNotPlacementName_1754) {
    Object obj = makeNameObject("Table");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test that an empty name is NOT a placement name
TEST_F(IsPlacementNameTest_1754, EmptyNameIsNotPlacementName_1754) {
    Object obj = makeNameObject("");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test that a case-sensitive mismatch is NOT a placement name ("block" vs "Block")
TEST_F(IsPlacementNameTest_1754, LowercaseBlockIsNotPlacementName_1754) {
    Object obj = makeNameObject("block");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test that a case-sensitive mismatch is NOT a placement name ("inline" vs "Inline")
TEST_F(IsPlacementNameTest_1754, LowercaseInlineIsNotPlacementName_1754) {
    Object obj = makeNameObject("inline");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test that a case-sensitive mismatch is NOT a placement name ("before" vs "Before")
TEST_F(IsPlacementNameTest_1754, LowercaseBeforeIsNotPlacementName_1754) {
    Object obj = makeNameObject("before");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test that a case-sensitive mismatch is NOT a placement name ("start" vs "Start")
TEST_F(IsPlacementNameTest_1754, LowercaseStartIsNotPlacementName_1754) {
    Object obj = makeNameObject("start");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test that a case-sensitive mismatch is NOT a placement name ("end" vs "End")
TEST_F(IsPlacementNameTest_1754, LowercaseEndIsNotPlacementName_1754) {
    Object obj = makeNameObject("end");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with a null object (not a name type)
TEST_F(IsPlacementNameTest_1754, NullObjectIsNotPlacementName_1754) {
    Object obj = Object::null();
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with an integer object (not a name type)
TEST_F(IsPlacementNameTest_1754, IntObjectIsNotPlacementName_1754) {
    Object obj(42);
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with a boolean object (not a name type)
TEST_F(IsPlacementNameTest_1754, BoolObjectIsNotPlacementName_1754) {
    Object obj(true);
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with a real/double object (not a name type)
TEST_F(IsPlacementNameTest_1754, RealObjectIsNotPlacementName_1754) {
    Object obj(3.14);
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with a name that has extra whitespace
TEST_F(IsPlacementNameTest_1754, NameWithTrailingSpaceIsNotPlacementName_1754) {
    Object obj = makeNameObject("Block ");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with a name that has a prefix match but is longer
TEST_F(IsPlacementNameTest_1754, NameBlockExtraCharsIsNotPlacementName_1754) {
    Object obj = makeNameObject("BlockQuote");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with a partial match
TEST_F(IsPlacementNameTest_1754, PartialNameIsNotPlacementName_1754) {
    Object obj = makeNameObject("Bloc");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with all-uppercase variant
TEST_F(IsPlacementNameTest_1754, AllUppercaseBLOCKIsNotPlacementName_1754) {
    Object obj = makeNameObject("BLOCK");
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with "None" object type
TEST_F(IsPlacementNameTest_1754, NoneObjectIsNotPlacementName_1754) {
    Object obj;
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with error object
TEST_F(IsPlacementNameTest_1754, ErrorObjectIsNotPlacementName_1754) {
    Object obj = Object::error();
    EXPECT_FALSE(isPlacementName(&obj));
}

// Test with EOF object
TEST_F(IsPlacementNameTest_1754, EofObjectIsNotPlacementName_1754) {
    Object obj = Object::eof();
    EXPECT_FALSE(isPlacementName(&obj));
}
