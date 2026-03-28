#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"
#include "poppler/GfxFont.h"

// We need access to the static function testForNumericNames
// Since it's static in GfxFont.cc, we include it to get access
// This is a common technique for testing static functions
#include "poppler/GfxFont.cc"

class TestForNumericNamesTest_1969 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = nullptr; // Many Dict operations work with nullptr xref for basic tests
    }

    XRef *xref;
};

// Test: fontDict has no "Encoding" key - should return false
TEST_F(TestForNumericNamesTest_1969, NoEncodingKey_ReturnsFlase_1969) {
    Dict fontDict(xref);
    // No "Encoding" entry added
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: fontDict has "Encoding" but it's not a dict (e.g., an int)
TEST_F(TestForNumericNamesTest_1969, EncodingNotDict_ReturnsFalse_1969) {
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(42));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: Encoding is a dict but has no "Differences" key
TEST_F(TestForNumericNamesTest_1969, NoDifferencesKey_ReturnsFalse_1969) {
    Dict *encDict = new Dict(xref);
    // Don't add "Differences"
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: Differences is not an array
TEST_F(TestForNumericNamesTest_1969, DifferencesNotArray_ReturnsFalse_1969) {
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(42));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: Differences is an empty array - should return true (numeric stays true)
TEST_F(TestForNumericNamesTest_1969, EmptyDifferencesArray_ReturnsTrue_1969) {
    Array *diffArray = new Array(xref);
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_TRUE(result);
}

// Test: Differences array with int <= 5 should return true
TEST_F(TestForNumericNamesTest_1969, IntLessThanOrEqual5_ReturnsTrue_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(0));
    diffArray->add(Object(3));
    diffArray->add(Object(5));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_TRUE(result);
}

// Test: Differences array with int > 5 should return false
TEST_F(TestForNumericNamesTest_1969, IntGreaterThan5_ReturnsFalse_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(6));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: Differences array with int exactly 5 - boundary
TEST_F(TestForNumericNamesTest_1969, IntExactly5_ReturnsTrue_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(5));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_TRUE(result);
}

// Test: Differences array with int exactly 6 - boundary
TEST_F(TestForNumericNamesTest_1969, IntExactly6_ReturnsFalse_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(6));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: Differences array with non-int, non-name object (e.g., real) should return false
TEST_F(TestForNumericNamesTest_1969, RealInDifferences_ReturnsFalse_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(3.14));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: Differences array with valid int followed by invalid int
TEST_F(TestForNumericNamesTest_1969, ValidThenInvalidInt_ReturnsFalse_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(3));
    diffArray->add(Object(10));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: Differences array with negative int (<=5) should return true
TEST_F(TestForNumericNamesTest_1969, NegativeInt_ReturnsTrue_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(-1));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_TRUE(result);
}

// Test: Differences array with zero
TEST_F(TestForNumericNamesTest_1969, ZeroInt_ReturnsTrue_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(0));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_TRUE(result);
}

// Test: Bool object in differences array should return false (not int, not name)
TEST_F(TestForNumericNamesTest_1969, BoolInDifferences_ReturnsFalse_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(true));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}

// Test: hex parameter with false
TEST_F(TestForNumericNamesTest_1969, HexFalseWithValidInts_ReturnsTrue_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(2));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_TRUE(result);
}

// Test: hex parameter with true
TEST_F(TestForNumericNamesTest_1969, HexTrueWithValidInts_ReturnsTrue_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(2));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, true);
    EXPECT_TRUE(result);
}

// Test: Multiple valid ints all <= 5
TEST_F(TestForNumericNamesTest_1969, MultipleValidInts_ReturnsTrue_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(0));
    diffArray->add(Object(1));
    diffArray->add(Object(2));
    diffArray->add(Object(3));
    diffArray->add(Object(4));
    diffArray->add(Object(5));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_TRUE(result);
}

// Test: String object in differences should return false
TEST_F(TestForNumericNamesTest_1969, StringInDifferences_ReturnsFalse_1969) {
    Array *diffArray = new Array(xref);
    diffArray->add(Object(std::string("test")));
    Dict *encDict = new Dict(xref);
    encDict->add("Differences", Object(diffArray));
    Dict fontDict(xref);
    fontDict.add("Encoding", Object(encDict));
    bool result = testForNumericNames(&fontDict, false);
    EXPECT_FALSE(result);
}
