#include <gtest/gtest.h>
#include "Annot.h"
#include "Object.h"

// Forward declaration of the function under test (it's static in the .cc file,
// so we need to either include the .cc or declare it extern for testing purposes)
// Since it's static, we include the .cc file to make it accessible in this translation unit.
#include "Annot.cc"

class ParseAnnotLineEndingStyleTest_2015 : public ::testing::Test {
protected:
};

// Test that a Name object "Square" returns annotLineEndingSquare
TEST_F(ParseAnnotLineEndingStyleTest_2015, SquareName_ReturnsSquare_2015) {
    Object obj(objName, "Square");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingSquare);
}

// Test that a Name object "Circle" returns annotLineEndingCircle
TEST_F(ParseAnnotLineEndingStyleTest_2015, CircleName_ReturnsCircle_2015) {
    Object obj(objName, "Circle");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingCircle);
}

// Test that a Name object "Diamond" returns annotLineEndingDiamond
TEST_F(ParseAnnotLineEndingStyleTest_2015, DiamondName_ReturnsDiamond_2015) {
    Object obj(objName, "Diamond");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingDiamond);
}

// Test that a Name object "OpenArrow" returns annotLineEndingOpenArrow
TEST_F(ParseAnnotLineEndingStyleTest_2015, OpenArrowName_ReturnsOpenArrow_2015) {
    Object obj(objName, "OpenArrow");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingOpenArrow);
}

// Test that a Name object "ClosedArrow" returns annotLineEndingClosedArrow
TEST_F(ParseAnnotLineEndingStyleTest_2015, ClosedArrowName_ReturnsClosedArrow_2015) {
    Object obj(objName, "ClosedArrow");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingClosedArrow);
}

// Test that a Name object "Butt" returns annotLineEndingButt
TEST_F(ParseAnnotLineEndingStyleTest_2015, ButtName_ReturnsButt_2015) {
    Object obj(objName, "Butt");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingButt);
}

// Test that a Name object "ROpenArrow" returns annotLineEndingROpenArrow
TEST_F(ParseAnnotLineEndingStyleTest_2015, ROpenArrowName_ReturnsROpenArrow_2015) {
    Object obj(objName, "ROpenArrow");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingROpenArrow);
}

// Test that a Name object "RClosedArrow" returns annotLineEndingRClosedArrow
TEST_F(ParseAnnotLineEndingStyleTest_2015, RClosedArrowName_ReturnsRClosedArrow_2015) {
    Object obj(objName, "RClosedArrow");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingRClosedArrow);
}

// Test that a Name object "Slash" returns annotLineEndingSlash
TEST_F(ParseAnnotLineEndingStyleTest_2015, SlashName_ReturnsSlash_2015) {
    Object obj(objName, "Slash");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingSlash);
}

// Test that a Name object "None" (explicitly) returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, NoneName_ReturnsNone_2015) {
    Object obj(objName, "None");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test that an unrecognized Name returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, UnrecognizedName_ReturnsNone_2015) {
    Object obj(objName, "UnknownStyle");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test that an empty Name returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, EmptyName_ReturnsNone_2015) {
    Object obj(objName, "");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test that a non-Name object (e.g., null) returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, NullObject_ReturnsNone_2015) {
    Object obj = Object::null();
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test that a non-Name object (integer) returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, IntObject_ReturnsNone_2015) {
    Object obj(42);
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test that a non-Name object (bool) returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, BoolObject_ReturnsNone_2015) {
    Object obj(true);
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test that a non-Name object (real/double) returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, RealObject_ReturnsNone_2015) {
    Object obj(3.14);
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test that a default-constructed (objNone) Object returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, NoneObject_ReturnsNone_2015) {
    Object obj;
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test case sensitivity - "square" (lowercase) should not match "Square"
TEST_F(ParseAnnotLineEndingStyleTest_2015, LowercaseSquare_ReturnsNone_2015) {
    Object obj(objName, "square");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test case sensitivity - "SQUARE" (uppercase) should not match "Square"
TEST_F(ParseAnnotLineEndingStyleTest_2015, UppercaseSquare_ReturnsNone_2015) {
    Object obj(objName, "SQUARE");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test a Name with trailing whitespace should not match
TEST_F(ParseAnnotLineEndingStyleTest_2015, NameWithTrailingSpace_ReturnsNone_2015) {
    Object obj(objName, "Square ");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test a Name with leading whitespace should not match
TEST_F(ParseAnnotLineEndingStyleTest_2015, NameWithLeadingSpace_ReturnsNone_2015) {
    Object obj(objName, " Square");
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test error object returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, ErrorObject_ReturnsNone_2015) {
    Object obj = Object::error();
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}

// Test EOF object returns annotLineEndingNone
TEST_F(ParseAnnotLineEndingStyleTest_2015, EofObject_ReturnsNone_2015) {
    Object obj = Object::eof();
    EXPECT_EQ(parseAnnotLineEndingStyle(obj), annotLineEndingNone);
}
