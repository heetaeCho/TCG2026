#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler glib headers
extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
#include "poppler.h"
}

class PopplerStructureElementTest_2518 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the PopplerStructureElement GType is registered and valid
TEST_F(PopplerStructureElementTest_2518, TypeIsRegistered_2518)
{
    GType type = poppler_structure_element_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that the type name is correct
TEST_F(PopplerStructureElementTest_2518, TypeNameIsCorrect_2518)
{
    GType type = poppler_structure_element_get_type();
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerStructureElement");
}

// Test that PopplerStructureElement is derived from GObject
TEST_F(PopplerStructureElementTest_2518, DerivedFromGObject_2518)
{
    GType type = poppler_structure_element_get_type();
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test that the type is not abstract (or check its fundamental properties)
TEST_F(PopplerStructureElementTest_2518, TypeFundamentalIsGObject_2518)
{
    GType type = poppler_structure_element_get_type();
    GType fundamental = g_type_fundamental(type);
    EXPECT_EQ(fundamental, G_TYPE_OBJECT);
}

// Test that the PopplerStructureElementType enum has expected values
TEST_F(PopplerStructureElementTest_2518, StructureElementTypeEnumExists_2518)
{
    // Verify some known enum values exist and are distinct
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_DOCUMENT, POPPLER_STRUCTURE_ELEMENT_TABLE);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_SPAN, POPPLER_STRUCTURE_ELEMENT_FIGURE);
}

// Test that calling get_type multiple times returns the same type
TEST_F(PopplerStructureElementTest_2518, GetTypeIsIdempotent_2518)
{
    GType type1 = poppler_structure_element_get_type();
    GType type2 = poppler_structure_element_get_type();
    EXPECT_EQ(type1, type2);
}

// Test parent type
TEST_F(PopplerStructureElementTest_2518, ParentTypeIsGObject_2518)
{
    GType type = poppler_structure_element_get_type();
    GType parent = g_type_parent(type);
    EXPECT_EQ(parent, G_TYPE_OBJECT);
}
