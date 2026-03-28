// StructElement_isGlyphOrientationName_1765_test.cc

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Include Object definition.
#include "Object.h"

// Include the implementation file so we can directly call the file-local (static) helper.
// This keeps the test black-box w.r.t. other internal state while still allowing us to
// exercise the observable behavior of this helper function.
#include "StructElement.cc"

namespace {

class StructElementTest_1765 : public ::testing::Test
{
};

// Normal operation: all allowed glyph orientation names should return true.
TEST_F(StructElementTest_1765, ReturnsTrueForAllowedNames_1765)
{
    const std::vector<const char *> allowed = {
        "Auto", "90", "180", "270", "360", "-90", "-180",
    };

    for (const char *name : allowed) {
        Object o(objName, name);
        EXPECT_TRUE(isGlyphOrientationName(&o)) << "Expected true for name: " << name;
    }
}

// Normal operation / negative cases: other names should return false.
TEST_F(StructElementTest_1765, ReturnsFalseForOtherNames_1765)
{
    const std::vector<const char *> disallowed = {
        "",        "0",      "45",     "-270",  "540",   "AUTO",
        "auto",    "Auto ",  " 90",    "+90",   "--90",  "NaN",
        "random",  "Glyph",  "Orientation",
    };

    for (const char *name : disallowed) {
        Object o(objName, name);
        EXPECT_FALSE(isGlyphOrientationName(&o)) << "Expected false for name: " << name;
    }
}

// Boundary / type-safety: non-name Objects should return false (observable via return value).
TEST_F(StructElementTest_1765, ReturnsFalseForNonNameObjects_1765)
{
    // Null object
    Object nullObj = Object::null();
    EXPECT_FALSE(isGlyphOrientationName(&nullObj));

    // Integer
    Object intObj(90);
    EXPECT_FALSE(isGlyphOrientationName(&intObj));

    // Boolean
    Object boolObj(true);
    EXPECT_FALSE(isGlyphOrientationName(&boolObj));

    // Real/number
    Object realObj(90.0);
    EXPECT_FALSE(isGlyphOrientationName(&realObj));

    // String object (not a Name object) even if contents match an allowed token.
    Object stringObj(std::string("Auto"));
    EXPECT_FALSE(isGlyphOrientationName(&stringObj));
}

// Boundary: very long name should still be handled and return false if not an exact match.
TEST_F(StructElementTest_1765, ReturnsFalseForVeryLongName_1765)
{
    std::string longName(4096, 'A'); // "AAAA...."
    Object o(objName, longName);
    EXPECT_FALSE(isGlyphOrientationName(&o));
}

} // namespace