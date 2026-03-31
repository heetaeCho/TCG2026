#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Dict.h"
#include "Annot.h"

// We need to declare the function under test since it's static in Annot.cc
// We'll need to make it accessible for testing. Since it's a static function,
// we include the source file or use a wrapper approach.
// For testing purposes, we'll declare the function signature and link against it.

// Since parseAnnotExternalData is static, we need to include the .cc file
// or create a test wrapper. We'll use a common testing technique of
// including the source to access static functions.

// Forward declaration approach won't work for static functions.
// We need to either:
// 1. Include the .cc file
// 2. Or have a test helper that exposes it

// For this test, we'll include the implementation file to access the static function
#include "Annot.cc"

class ParseAnnotExternalDataTest_2017 : public ::testing::Test {
protected:
    void SetUp() override {
        // Dict requires an XRef, but for testing we can pass nullptr
        // if the Dict constructor and lookup don't actually dereference it
        // for our simple test cases (no indirect references)
        dict = new Dict(static_cast<XRef*>(nullptr));
    }

    void TearDown() override {
        delete dict;
    }

    Dict *dict;
};

// Test: When "Subtype" is "Markup3D", should return annotExternalDataMarkup3D
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsMarkup3DForMarkup3DSubtype_2017) {
    dict->add("Subtype", Object(objName, "Markup3D"));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkup3D);
}

// Test: When "Subtype" is an unknown name, should return annotExternalDataMarkupUnknown
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownForUnknownSubtype_2017) {
    dict->add("Subtype", Object(objName, "SomeOtherType"));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: When "Subtype" key is missing, should return annotExternalDataMarkupUnknown
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeMissing_2017) {
    // Don't add "Subtype" key at all
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: When "Subtype" is not a name (e.g., integer), should return annotExternalDataMarkupUnknown
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeIsNotName_2017) {
    dict->add("Subtype", Object(42));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: When "Subtype" is a string (not a name), should return annotExternalDataMarkupUnknown
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeIsString_2017) {
    dict->add("Subtype", Object(std::string("Markup3D")));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: When "Subtype" is a boolean, should return annotExternalDataMarkupUnknown
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeIsBool_2017) {
    dict->add("Subtype", Object(true));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: When "Subtype" is null, should return annotExternalDataMarkupUnknown
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeIsNull_2017) {
    dict->add("Subtype", Object::null());
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: When "Subtype" is an empty name, should return annotExternalDataMarkupUnknown
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeIsEmptyName_2017) {
    dict->add("Subtype", Object(objName, ""));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: Case sensitivity - "markup3d" should not match "Markup3D"
TEST_F(ParseAnnotExternalDataTest_2017, IsCaseSensitive_2017) {
    dict->add("Subtype", Object(objName, "markup3d"));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: Case sensitivity - "MARKUP3D" should not match "Markup3D"
TEST_F(ParseAnnotExternalDataTest_2017, IsCaseSensitiveUpperCase_2017) {
    dict->add("Subtype", Object(objName, "MARKUP3D"));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: Verify enum values are as expected
TEST_F(ParseAnnotExternalDataTest_2017, EnumValuesCorrect_2017) {
    EXPECT_EQ(annotExternalDataMarkupUnknown, 0);
    EXPECT_EQ(annotExternalDataMarkup3D, 1);
}

// Test: When "Subtype" is a real number, should return annotExternalDataMarkupUnknown
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeIsReal_2017) {
    dict->add("Subtype", Object(3.14));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: When "Subtype" name has trailing whitespace, should not match
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeHasTrailingSpace_2017) {
    dict->add("Subtype", Object(objName, "Markup3D "));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// Test: When "Subtype" name has leading whitespace, should not match
TEST_F(ParseAnnotExternalDataTest_2017, ReturnsUnknownWhenSubtypeHasLeadingSpace_2017) {
    dict->add("Subtype", Object(objName, " Markup3D"));
    AnnotExternalDataType result = parseAnnotExternalData(dict);
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}
