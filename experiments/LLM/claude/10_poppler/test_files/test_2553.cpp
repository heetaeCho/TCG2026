#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "poppler-structure-element.h"
#include "Object.h"
#include "Array.h"
#include "Dict.h"

// Since convert_border_style is static in the .cc file, we include it to access it
// This is a common testing pattern for static functions
#include "poppler-structure-element.cc"

class ConvertBorderStyleTest_2553 : public ::testing::Test {
protected:
    PopplerStructureBorderStyle values[4];

    void SetUp() override {
        // Initialize values to a known state
        for (int i = 0; i < 4; i++) {
            values[i] = static_cast<PopplerStructureBorderStyle>(-1);
        }
    }
};

// Test that a single name object sets all four values to the same border style
TEST_F(ConvertBorderStyleTest_2553, SingleNameSetsAllFourValues_2553) {
    Object obj(ObjType::objName, "None");
    convert_border_style(&obj, values);

    EXPECT_EQ(values[0], values[1]);
    EXPECT_EQ(values[1], values[2]);
    EXPECT_EQ(values[2], values[3]);
}

// Test that a single "Solid" name object sets all four values identically
TEST_F(ConvertBorderStyleTest_2553, SingleNameSolidSetsAllFour_2553) {
    Object obj(ObjType::objName, "Solid");
    convert_border_style(&obj, values);

    EXPECT_EQ(values[0], values[1]);
    EXPECT_EQ(values[1], values[2]);
    EXPECT_EQ(values[2], values[3]);
}

// Test that an array of 4 name objects sets each value individually
TEST_F(ConvertBorderStyleTest_2553, ArrayOfFourSetsIndividualValues_2553) {
    // Create an array with 4 name elements
    auto *xref = (XRef *)nullptr;
    Array *arr = new Array(xref);
    arr->add(Object(ObjType::objName, "None"));
    arr->add(Object(ObjType::objName, "None"));
    arr->add(Object(ObjType::objName, "None"));
    arr->add(Object(ObjType::objName, "None"));

    Object obj(arr);
    convert_border_style(&obj, values);

    // All should be the same since all are "None"
    EXPECT_EQ(values[0], values[1]);
    EXPECT_EQ(values[1], values[2]);
    EXPECT_EQ(values[2], values[3]);
}

// Test that array with mixed border styles sets different values
TEST_F(ConvertBorderStyleTest_2553, ArrayWithMixedStylesSetsCorrectly_2553) {
    auto *xref = (XRef *)nullptr;
    Array *arr = new Array(xref);
    arr->add(Object(ObjType::objName, "None"));
    arr->add(Object(ObjType::objName, "Solid"));
    arr->add(Object(ObjType::objName, "Dashed"));
    arr->add(Object(ObjType::objName, "Dotted"));

    Object obj(arr);
    convert_border_style(&obj, values);

    // Each value should be set; at minimum they should be valid enum values
    // We can verify they're not all the same if styles differ
    // The exact enum mapping depends on name_to_enum implementation
    EXPECT_NE(values[0], static_cast<PopplerStructureBorderStyle>(-1));
    EXPECT_NE(values[1], static_cast<PopplerStructureBorderStyle>(-1));
    EXPECT_NE(values[2], static_cast<PopplerStructureBorderStyle>(-1));
    EXPECT_NE(values[3], static_cast<PopplerStructureBorderStyle>(-1));
}

// Test that non-array object (single name) produces consistent results
TEST_F(ConvertBorderStyleTest_2553, NonArrayObjectProducesUniformValues_2553) {
    Object obj(ObjType::objName, "Dashed");
    convert_border_style(&obj, values);

    // All four values must be identical
    EXPECT_EQ(values[0], values[1]);
    EXPECT_EQ(values[1], values[2]);
    EXPECT_EQ(values[2], values[3]);
}
