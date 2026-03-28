#include <gtest/gtest.h>
#include <glib-object.h>

// Include the necessary headers
extern "C" {
#include "poppler.h"
}

class PopplerAnnotMappingTest_2497 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_annot_mapping_free handles NULL gracefully
TEST_F(PopplerAnnotMappingTest_2497, FreeNullMapping_2497)
{
    // Should not crash when passed NULL
    poppler_annot_mapping_free(nullptr);
}

// Test that poppler_annot_mapping_new creates a valid mapping
TEST_F(PopplerAnnotMappingTest_2497, NewMappingIsValid_2497)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);
    // A newly created mapping should have NULL annot
    EXPECT_EQ(mapping->annot, nullptr);
    poppler_annot_mapping_free(mapping);
}

// Test that freeing a mapping with NULL annot does not crash
TEST_F(PopplerAnnotMappingTest_2497, FreeMappingWithNullAnnot_2497)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);
    mapping->annot = nullptr;
    // Should not crash
    poppler_annot_mapping_free(mapping);
}

// Test that poppler_annot_mapping_copy creates a proper copy
TEST_F(PopplerAnnotMappingTest_2497, CopyMappingNullAnnot_2497)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);
    mapping->annot = nullptr;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->annot, nullptr);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(mapping);
}

// Test copy of NULL returns NULL (or handles gracefully)
TEST_F(PopplerAnnotMappingTest_2497, CopyNullMapping_2497)
{
    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test the area field in the mapping
TEST_F(PopplerAnnotMappingTest_2497, MappingAreaInitialization_2497)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);

    // Set area coordinates
    mapping->area.x1 = 10.0;
    mapping->area.y1 = 20.0;
    mapping->area.x2 = 100.0;
    mapping->area.y2 = 200.0;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 20.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 100.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 200.0);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(mapping);
}

// Test multiple allocations and frees to check for leaks/crashes
TEST_F(PopplerAnnotMappingTest_2497, MultipleAllocFree_2497)
{
    for (int i = 0; i < 100; i++) {
        PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
        ASSERT_NE(mapping, nullptr);
        mapping->annot = nullptr;
        poppler_annot_mapping_free(mapping);
    }
}
