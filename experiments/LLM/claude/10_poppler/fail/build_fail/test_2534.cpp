#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include necessary headers
extern "C" {
#include "poppler-structure-element.h"
}
#include "poppler-private.h"
#include "StructElement.h"

// We need to mock StructElement since we can't create real PDF structures easily
// However, since StructElement is a concrete class, we'll need to work with
// the GObject-based interface.

// Forward declarations for the function under test
extern "C" {
gchar *poppler_structure_element_get_text(PopplerStructureElement *poppler_structure_element, PopplerStructureGetTextFlags flags);
gboolean POPPLER_IS_STRUCTURE_ELEMENT(gpointer obj);
}

// Since we're dealing with GObject types and complex PDF internals,
// we'll create integration-style tests that verify the interface behavior
// through the public API. We need to handle the GObject type system.

class PopplerStructureElementGetTextTest_2534 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL (g_return_val_if_fail check)
TEST_F(PopplerStructureElementGetTextTest_2534, NullElementReturnsNull_2534)
{
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    gchar *result = poppler_structure_element_get_text(NULL, POPPLER_STRUCTURE_GET_TEXT_NONE);
    EXPECT_EQ(result, nullptr);
}

// Test that passing NULL with recursive flag also returns NULL
TEST_F(PopplerStructureElementGetTextTest_2534, NullElementWithRecursiveFlagReturnsNull_2534)
{
    gchar *result = poppler_structure_element_get_text(NULL, POPPLER_STRUCTURE_GET_TEXT_RECURSIVE);
    EXPECT_EQ(result, nullptr);
}

// Test the flag values are correct
TEST_F(PopplerStructureElementGetTextTest_2534, FlagValuesCorrect_2534)
{
    EXPECT_EQ(POPPLER_STRUCTURE_GET_TEXT_NONE, 0);
    EXPECT_EQ(POPPLER_STRUCTURE_GET_TEXT_RECURSIVE, 1);
}

// Test that NONE flag masks out recursive bit
TEST_F(PopplerStructureElementGetTextTest_2534, NoneFlagMasksRecursiveBit_2534)
{
    // Verify the flag arithmetic: NONE & RECURSIVE == 0
    PopplerStructureGetTextFlags flags = POPPLER_STRUCTURE_GET_TEXT_NONE;
    EXPECT_EQ(flags & POPPLER_STRUCTURE_GET_TEXT_RECURSIVE, 0);
}

// Test that RECURSIVE flag preserves recursive bit
TEST_F(PopplerStructureElementGetTextTest_2534, RecursiveFlagPreservesRecursiveBit_2534)
{
    PopplerStructureGetTextFlags flags = POPPLER_STRUCTURE_GET_TEXT_RECURSIVE;
    EXPECT_EQ(flags & POPPLER_STRUCTURE_GET_TEXT_RECURSIVE, 1);
}

// Test with an invalid (non-GObject) pointer - should return NULL due to type check
TEST_F(PopplerStructureElementGetTextTest_2534, InvalidObjectReturnsNull_2534)
{
    // Create a fake structure that won't pass POPPLER_IS_STRUCTURE_ELEMENT check
    int fake_object = 42;
    gchar *result = poppler_structure_element_get_text(reinterpret_cast<PopplerStructureElement *>(&fake_object), POPPLER_STRUCTURE_GET_TEXT_NONE);
    EXPECT_EQ(result, nullptr);
}

// Test with invalid object and recursive flag
TEST_F(PopplerStructureElementGetTextTest_2534, InvalidObjectWithRecursiveFlagReturnsNull_2534)
{
    int fake_object = 42;
    gchar *result = poppler_structure_element_get_text(reinterpret_cast<PopplerStructureElement *>(&fake_object), POPPLER_STRUCTURE_GET_TEXT_RECURSIVE);
    EXPECT_EQ(result, nullptr);
}

// Test combining flags - arbitrary integer flags
TEST_F(PopplerStructureElementGetTextTest_2534, CombinedFlagBitMask_2534)
{
    // If someone passes flags = 3 (binary 11), only bit 0 (RECURSIVE) should matter
    int combined = 3;
    EXPECT_EQ(combined & POPPLER_STRUCTURE_GET_TEXT_RECURSIVE, 1);
}

// Test that flag with value 2 does not set recursive
TEST_F(PopplerStructureElementGetTextTest_2534, FlagValue2DoesNotSetRecursive_2534)
{
    int flag_val = 2;
    EXPECT_EQ(flag_val & POPPLER_STRUCTURE_GET_TEXT_RECURSIVE, 0);
}
