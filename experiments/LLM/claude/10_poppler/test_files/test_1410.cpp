#include <gtest/gtest.h>
#include <QString>

// We need to access the function under test. Since it's in the Poppler namespace
// but declared static in the .cc file, we need to include the source or
// replicate the declaration. Since we're testing based on the interface and
// the function is static (internal linkage), we'll need to include the source file
// or use a workaround.

// For testing purposes, we include the relevant headers and re-declare the 
// enum and function signature as they appear in the Poppler public API.
#include "poppler-annotation.h"

// Since caretSymbolToString is a static function in the .cc file (internal linkage),
// we need to include the .cc file to access it for testing.
// This is a common pattern for testing static/file-scope functions.
#include "poppler-annotation.cc"

using namespace Poppler;

class CaretSymbolToStringTest_1410 : public ::testing::Test {
protected:
    // Nothing special needed for setup/teardown
};

// Test that CaretAnnotation::None maps to "None"
TEST_F(CaretSymbolToStringTest_1410, NoneSymbolReturnsNoneString_1410) {
    QString result = caretSymbolToString(CaretAnnotation::None);
    EXPECT_EQ(result, QStringLiteral("None"));
}

// Test that CaretAnnotation::P maps to "P"
TEST_F(CaretSymbolToStringTest_1410, PSymbolReturnsPString_1410) {
    QString result = caretSymbolToString(CaretAnnotation::P);
    EXPECT_EQ(result, QStringLiteral("P"));
}

// Test that an unrecognized/invalid enum value returns an empty QString
TEST_F(CaretSymbolToStringTest_1410, InvalidSymbolReturnsEmptyString_1410) {
    // Cast an invalid integer to CaretSymbol to test the default case
    CaretAnnotation::CaretSymbol invalidSymbol = static_cast<CaretAnnotation::CaretSymbol>(999);
    QString result = caretSymbolToString(invalidSymbol);
    EXPECT_TRUE(result.isEmpty());
    EXPECT_EQ(result, QString());
}

// Test that None result is not empty
TEST_F(CaretSymbolToStringTest_1410, NoneSymbolResultIsNotEmpty_1410) {
    QString result = caretSymbolToString(CaretAnnotation::None);
    EXPECT_FALSE(result.isEmpty());
}

// Test that P result is not empty
TEST_F(CaretSymbolToStringTest_1410, PSymbolResultIsNotEmpty_1410) {
    QString result = caretSymbolToString(CaretAnnotation::P);
    EXPECT_FALSE(result.isEmpty());
}

// Test that None and P return different strings
TEST_F(CaretSymbolToStringTest_1410, NoneAndPReturnDifferentStrings_1410) {
    QString noneResult = caretSymbolToString(CaretAnnotation::None);
    QString pResult = caretSymbolToString(CaretAnnotation::P);
    EXPECT_NE(noneResult, pResult);
}

// Test another invalid value (negative) returns empty string
TEST_F(CaretSymbolToStringTest_1410, NegativeInvalidSymbolReturnsEmptyString_1410) {
    CaretAnnotation::CaretSymbol invalidSymbol = static_cast<CaretAnnotation::CaretSymbol>(-1);
    QString result = caretSymbolToString(invalidSymbol);
    EXPECT_TRUE(result.isEmpty());
}

// Test boundary: value just beyond valid enum range
TEST_F(CaretSymbolToStringTest_1410, BoundaryInvalidSymbolReturnsEmptyString_1410) {
    CaretAnnotation::CaretSymbol invalidSymbol = static_cast<CaretAnnotation::CaretSymbol>(2);
    QString result = caretSymbolToString(invalidSymbol);
    EXPECT_TRUE(result.isEmpty());
}

// Test that the returned string for None has correct length
TEST_F(CaretSymbolToStringTest_1410, NoneStringHasCorrectLength_1410) {
    QString result = caretSymbolToString(CaretAnnotation::None);
    EXPECT_EQ(result.length(), 4);  // "None" has 4 characters
}

// Test that the returned string for P has correct length
TEST_F(CaretSymbolToStringTest_1410, PStringHasCorrectLength_1410) {
    QString result = caretSymbolToString(CaretAnnotation::P);
    EXPECT_EQ(result.length(), 1);  // "P" has 1 character
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
