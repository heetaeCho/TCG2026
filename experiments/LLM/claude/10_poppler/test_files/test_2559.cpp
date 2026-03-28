#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>

extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
}

class PopplerStructureElementBorderColorTest_2559 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL for poppler_structure_element returns FALSE
TEST_F(PopplerStructureElementBorderColorTest_2559, NullElementReturnsFalse_2559)
{
    PopplerColor colors[4];
    // g_return_val_if_fail with NULL should return FALSE
    // This triggers the POPPLER_IS_STRUCTURE_ELEMENT check failure
    gboolean result = poppler_structure_element_get_border_color(nullptr, colors);
    EXPECT_FALSE(result);
}

// Test that passing NULL for colors returns FALSE
TEST_F(PopplerStructureElementBorderColorTest_2559, NullColorsReturnsFalse_2559)
{
    // Passing NULL for both should fail on the first check (element check)
    gboolean result = poppler_structure_element_get_border_color(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that passing an invalid GObject (not a PopplerStructureElement) returns FALSE
TEST_F(PopplerStructureElementBorderColorTest_2559, InvalidGObjectReturnsFalse_2559)
{
    PopplerColor colors[4];
    // Create a random GObject that is not a PopplerStructureElement
    // This should fail the POPPLER_IS_STRUCTURE_ELEMENT type check
    GObject *fake_obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    gboolean result = poppler_structure_element_get_border_color(
        reinterpret_cast<PopplerStructureElement *>(fake_obj), colors);
    EXPECT_FALSE(result);
    g_object_unref(fake_obj);
}

// Test that passing NULL element with valid colors array returns FALSE
TEST_F(PopplerStructureElementBorderColorTest_2559, NullElementValidColorsReturnsFalse_2559)
{
    PopplerColor colors[4] = {};
    gboolean result = poppler_structure_element_get_border_color(nullptr, colors);
    EXPECT_FALSE(result);
    // Colors should remain unchanged (zeroed)
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(colors[i].red, 0);
        EXPECT_EQ(colors[i].green, 0);
        EXPECT_EQ(colors[i].blue, 0);
    }
}

// Test with a non-structure-element type cast returns FALSE  
TEST_F(PopplerStructureElementBorderColorTest_2559, WrongTypeReturnsFalse_2559)
{
    PopplerColor colors[4] = {};
    // Using a completely bogus pointer should trigger the type check
    // We use NULL which is the safest invalid value
    PopplerStructureElement *invalid = nullptr;
    gboolean result = poppler_structure_element_get_border_color(invalid, colors);
    EXPECT_FALSE(result);
}

// Verify that the colors buffer is not modified when function returns FALSE
TEST_F(PopplerStructureElementBorderColorTest_2559, ColorsUnmodifiedOnFailure_2559)
{
    PopplerColor colors[4];
    // Set sentinel values
    for (int i = 0; i < 4; i++) {
        colors[i].red = 12345;
        colors[i].green = 67890;
        colors[i].blue = 11111;
    }

    gboolean result = poppler_structure_element_get_border_color(nullptr, colors);
    EXPECT_FALSE(result);

    // Verify colors were not modified
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(colors[i].red, 12345);
        EXPECT_EQ(colors[i].green, 67890);
        EXPECT_EQ(colors[i].blue, 11111);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
