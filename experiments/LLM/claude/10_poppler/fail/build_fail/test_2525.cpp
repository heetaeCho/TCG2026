#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include "poppler-structure-element.h"
}

#include "poppler-private.h"
#include "StructElement.h"

// We need to mock StructElement since we can't construct real PDF structure elements easily
// However, since StructElement is a concrete class, we'll work with the GObject interface

class PopplerStructureElementIsInlineTest_2525 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns FALSE (g_return_val_if_fail check)
TEST_F(PopplerStructureElementIsInlineTest_2525, NullElementReturnsFalse_2525)
{
    // Passing NULL should trigger g_return_val_if_fail and return FALSE
    // Note: This will produce a GLib warning, which is expected behavior
    gboolean result = poppler_structure_element_is_inline(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test that passing an invalid GObject (not a PopplerStructureElement) returns FALSE
TEST_F(PopplerStructureElementIsInlineTest_2525, InvalidGObjectReturnsFalse_2525)
{
    // Create some other GObject that is NOT a PopplerStructureElement
    // g_return_val_if_fail(POPPLER_IS_STRUCTURE_ELEMENT(...)) should fail
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    gboolean result = poppler_structure_element_is_inline((PopplerStructureElement *)obj);
    EXPECT_EQ(result, FALSE);
    g_object_unref(obj);
}

// Test that a PopplerStructureElement with elem == nullptr returns FALSE
TEST_F(PopplerStructureElementIsInlineTest_2525, NullElemFieldReturnsFalse_2525)
{
    // We need to create a valid PopplerStructureElement GObject but with elem = nullptr
    // This requires the GType to be registered
    GType type = poppler_structure_element_get_type();
    if (type == G_TYPE_INVALID) {
        GTEST_SKIP() << "PopplerStructureElement GType not available";
    }

    PopplerStructureElement *pse = (PopplerStructureElement *)g_object_new(type, nullptr);
    if (pse == nullptr) {
        GTEST_SKIP() << "Could not create PopplerStructureElement instance";
    }

    // Ensure elem is NULL (it should be by default after construction)
    pse->elem = nullptr;

    gboolean result = poppler_structure_element_is_inline(pse);
    EXPECT_EQ(result, FALSE);

    g_object_unref(pse);
}
