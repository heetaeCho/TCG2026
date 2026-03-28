#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
#include "poppler-structure-element.h"
}

#include "poppler-private.h"
#include "StructElement.h"

// We need to mock the StructElement to control isBlock() behavior
// Since we can't modify the actual class, we'll work with the GLib wrapper

// Forward declarations for GObject type system
// We need the actual type registration to use POPPLER_IS_STRUCTURE_ELEMENT

class PopplerStructureElementIsBlockTest_2526 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns FALSE (g_return_val_if_fail check)
TEST_F(PopplerStructureElementIsBlockTest_2526, NullElementReturnsFalse_2526)
{
    // Passing NULL should trigger g_return_val_if_fail and return FALSE
    gboolean result = poppler_structure_element_is_block(NULL);
    EXPECT_FALSE(result);
}

// Test that a non-GObject pointer is rejected by the type check
TEST_F(PopplerStructureElementIsBlockTest_2526, InvalidGObjectReturnsFalse_2526)
{
    // Create something that is not a PopplerStructureElement
    // This should fail the POPPLER_IS_STRUCTURE_ELEMENT check
    gboolean result = poppler_structure_element_is_block((PopplerStructureElement *)0x1);
    EXPECT_FALSE(result);
}

// Since we cannot easily construct a valid PopplerStructureElement without
// the full PDF infrastructure, we test the guard clauses which are the
// observable behavior through the public interface when given invalid inputs.

// Test with a GObject that is not a PopplerStructureElement
TEST_F(PopplerStructureElementIsBlockTest_2526, WrongGObjectTypeReturnsFalse_2526)
{
    // Create a generic GObject - it should fail the type check
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    gboolean result = poppler_structure_element_is_block((PopplerStructureElement *)obj);
    EXPECT_FALSE(result);
    g_object_unref(obj);
}
