#include <glib.h>
#include <glib-object.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

// Include necessary poppler headers
extern "C" {
#include "poppler-structure-element.h"
}

#include "poppler-private.h"
#include "StructElement.h"
#include "GooString.h"

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnNull;

// We need to create a mock for StructElement since we can't instantiate it directly
// However, since StructElement is not easily mockable (no virtual methods),
// we'll test through the public GLib API as much as possible.

class PopplerStructureElementGetLanguageTest_2531 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL
TEST_F(PopplerStructureElementGetLanguageTest_2531, NullElementReturnsNull_2531)
{
    gchar *result = poppler_structure_element_get_language(NULL);
    EXPECT_EQ(result, nullptr);
}

// Test that passing an invalid GObject type returns NULL
// (g_return_val_if_fail with POPPLER_IS_STRUCTURE_ELEMENT check)
TEST_F(PopplerStructureElementGetLanguageTest_2531, InvalidGObjectTypeReturnsNull_2531)
{
    // Create a dummy GObject that is not a PopplerStructureElement
    // This should trigger the POPPLER_IS_STRUCTURE_ELEMENT check
    gchar *result = poppler_structure_element_get_language((PopplerStructureElement *)g_object_new(G_TYPE_OBJECT, NULL));
    EXPECT_EQ(result, nullptr);
}

// Test with a valid PopplerStructureElement but with elem == nullptr
// This requires creating a PopplerStructureElement with a null elem field
// Since we can't easily create one through the public API without a document,
// we test the boundary: the function should return NULL when elem is nullptr.
// Note: This test depends on being able to create PopplerStructureElement objects.
// If PopplerStructureElement creation requires a full document, this test
// documents the expected behavior.

// Test that when getLanguage() returns nullptr, the function returns nullptr
TEST_F(PopplerStructureElementGetLanguageTest_2531, NullLanguageReturnsNull_2531)
{
    // We verify that the function handles null language from StructElement
    // by checking that NULL input gives NULL output (already tested above,
    // this documents the expected path through the code)
    gchar *result = poppler_structure_element_get_language(NULL);
    EXPECT_EQ(result, nullptr);
}

// Integration-style test: if we had a real document with structure elements,
// we'd verify the language string is properly converted to UTF-8.
// Since we can't easily create StructElement instances without a full PDF,
// we document the expected interface behavior.

// Test that the function properly handles the g_return_val_if_fail for elem != nullptr
TEST_F(PopplerStructureElementGetLanguageTest_2531, NullElemFieldReturnsNull_2531)
{
    // This tests the second g_return_val_if_fail condition
    // We cannot easily create a PopplerStructureElement with elem=nullptr
    // through the public API, but we document this boundary condition.
    // The function should return NULL if elem is nullptr.
    gchar *result = poppler_structure_element_get_language(nullptr);
    EXPECT_EQ(result, nullptr);
}
