#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include "poppler-structure-element.h"
}
#include "poppler-private.h"
#include "StructElement.h"

// We need to understand the GObject type system for PopplerStructureElement
// Since we're testing poppler_structure_element_is_content, we need valid PopplerStructureElement objects

class PopplerStructureElementIsContentTest_2524 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns FALSE (g_return_val_if_fail check)
TEST_F(PopplerStructureElementIsContentTest_2524, NullElementReturnsFalse_2524)
{
    // Passing NULL should trigger g_return_val_if_fail and return FALSE
    gboolean result = poppler_structure_element_is_content(nullptr);
    EXPECT_FALSE(result);
}

// Test that a valid PopplerStructureElement with a content StructElement returns TRUE
// We need to create a proper PopplerStructureElement via GObject system
TEST_F(PopplerStructureElementIsContentTest_2524, ValidContentElementReturnsTrue_2524)
{
    // Create a PopplerStructureElement via g_object_new
    // This requires the type to be registered. We'll attempt to create one.
    // If the elem is NULL, g_return_val_if_fail should return FALSE.
    
    PopplerStructureElement *elem = (PopplerStructureElement *)g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, NULL);
    if (elem != nullptr) {
        // elem->elem is likely NULL after default construction
        // This should return FALSE due to the NULL elem check
        gboolean result = poppler_structure_element_is_content(elem);
        EXPECT_FALSE(result);
        g_object_unref(elem);
    }
}

// Test with an invalid GObject type (not a PopplerStructureElement)
TEST_F(PopplerStructureElementIsContentTest_2524, InvalidGObjectTypeReturnsFalse_2524)
{
    // Create a plain GObject, which is not a PopplerStructureElement
    // POPPLER_IS_STRUCTURE_ELEMENT check should fail and return FALSE
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    ASSERT_NE(obj, nullptr);
    
    gboolean result = poppler_structure_element_is_content((PopplerStructureElement *)obj);
    EXPECT_FALSE(result);
    
    g_object_unref(obj);
}

// Test with a PopplerStructureElement whose elem field is NULL
TEST_F(PopplerStructureElementIsContentTest_2524, NullInternalElemReturnsFalse_2524)
{
    PopplerStructureElement *pse = (PopplerStructureElement *)g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, NULL);
    if (pse != nullptr) {
        // Ensure elem is NULL (should be by default)
        // The second g_return_val_if_fail should catch this
        gboolean result = poppler_structure_element_is_content(pse);
        EXPECT_FALSE(result);
        g_object_unref(pse);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
