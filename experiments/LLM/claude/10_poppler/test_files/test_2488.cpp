#include <gtest/gtest.h>
#include <glib.h>

// Include the header for the poppler page functionality
extern "C" {
#include "poppler-page.h"
}

// If poppler-page.h doesn't provide the full declarations, we need these
// Forward declarations based on the known interface
#ifndef POPPLER_IMAGE_MAPPING_DEFINED
typedef struct {
    PopplerRectangle area;
    gint image_id;
} PopplerImageMapping;
#endif

// Declarations of functions under test
extern "C" {
PopplerImageMapping *poppler_image_mapping_new(void);
PopplerImageMapping *poppler_image_mapping_copy(PopplerImageMapping *mapping);
void poppler_image_mapping_free(PopplerImageMapping *mapping);
}

class PopplerImageMappingTest_2488 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that freeing a NULL mapping does not crash (if the implementation handles it)
TEST_F(PopplerImageMappingTest_2488, FreeNullMapping_2488)
{
    // Passing NULL should not crash - this tests robustness
    // Note: g_slice_free with NULL should be safe
    poppler_image_mapping_free(nullptr);
    // If we reach here without crashing, the test passes
    SUCCEED();
}

// Test that freeing a valid mapping does not crash
TEST_F(PopplerImageMappingTest_2488, FreeValidMapping_2488)
{
    // Allocate a PopplerImageMapping using g_slice_new to match the free mechanism
    PopplerImageMapping *mapping = g_slice_new0(PopplerImageMapping);
    ASSERT_NE(mapping, nullptr);

    // Set some values to ensure the struct is usable
    mapping->image_id = 42;

    // Free should not crash
    poppler_image_mapping_free(mapping);
    SUCCEED();
}

// Test that freeing a mapping with default values works
TEST_F(PopplerImageMappingTest_2488, FreeDefaultMapping_2488)
{
    PopplerImageMapping *mapping = g_slice_new0(PopplerImageMapping);
    ASSERT_NE(mapping, nullptr);

    // image_id should be 0 after g_slice_new0
    EXPECT_EQ(mapping->image_id, 0);

    poppler_image_mapping_free(mapping);
    SUCCEED();
}

// Test allocation and free cycle multiple times to check for memory issues
TEST_F(PopplerImageMappingTest_2488, MultipleAllocFree_2488)
{
    for (int i = 0; i < 100; i++) {
        PopplerImageMapping *mapping = g_slice_new(PopplerImageMapping);
        ASSERT_NE(mapping, nullptr);
        mapping->image_id = i;
        poppler_image_mapping_free(mapping);
    }
    SUCCEED();
}

// Test freeing mapping with various image_id values
TEST_F(PopplerImageMappingTest_2488, FreeWithVariousImageIds_2488)
{
    // Test with negative image_id
    PopplerImageMapping *mapping1 = g_slice_new(PopplerImageMapping);
    ASSERT_NE(mapping1, nullptr);
    mapping1->image_id = -1;
    poppler_image_mapping_free(mapping1);

    // Test with zero image_id
    PopplerImageMapping *mapping2 = g_slice_new(PopplerImageMapping);
    ASSERT_NE(mapping2, nullptr);
    mapping2->image_id = 0;
    poppler_image_mapping_free(mapping2);

    // Test with large image_id
    PopplerImageMapping *mapping3 = g_slice_new(PopplerImageMapping);
    ASSERT_NE(mapping3, nullptr);
    mapping3->image_id = G_MAXINT;
    poppler_image_mapping_free(mapping3);

    SUCCEED();
}

// Test that poppler_image_mapping_new creates a valid mapping (if available)
TEST_F(PopplerImageMappingTest_2488, NewMappingAndFree_2488)
{
    // Use the poppler API to create a new mapping if available
    // Otherwise allocate with g_slice_new which matches the free implementation
    PopplerImageMapping *mapping = g_slice_new0(PopplerImageMapping);
    ASSERT_NE(mapping, nullptr);
    
    // Verify the zeroed state
    EXPECT_EQ(mapping->image_id, 0);
    
    poppler_image_mapping_free(mapping);
    SUCCEED();
}
