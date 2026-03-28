#include <gtest/gtest.h>
#include <glib-object.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler.h"
}

class PopplerFormFieldMappingTest_2494 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL does not crash (handles NULL gracefully)
TEST_F(PopplerFormFieldMappingTest_2494, FreeNullMapping_2494) {
    // Should not crash or cause any issues when passed NULL
    poppler_form_field_mapping_free(nullptr);
}

// Test that a valid mapping with a NULL field can be freed without crash
TEST_F(PopplerFormFieldMappingTest_2494, FreeValidMappingWithNullField_2494) {
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    
    // Ensure field is NULL (poppler_form_field_mapping_new should initialize it)
    mapping->field = nullptr;
    
    // Should free the mapping without issues even when field is NULL
    poppler_form_field_mapping_free(mapping);
}

// Test that poppler_form_field_mapping_new returns a non-null mapping
TEST_F(PopplerFormFieldMappingTest_2494, NewMappingReturnsNonNull_2494) {
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    
    // Clean up
    poppler_form_field_mapping_free(mapping);
}

// Test that poppler_form_field_mapping_copy works for a mapping with null field
TEST_F(PopplerFormFieldMappingTest_2494, CopyMappingWithNullField_2494) {
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    mapping->field = nullptr;
    mapping->area.x1 = 10.0;
    mapping->area.y1 = 20.0;
    mapping->area.x2 = 30.0;
    mapping->area.y2 = 40.0;
    
    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    
    EXPECT_DOUBLE_EQ(copy->area.x1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 20.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 30.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 40.0);
    EXPECT_EQ(copy->field, nullptr);
    
    poppler_form_field_mapping_free(copy);
    poppler_form_field_mapping_free(mapping);
}

// Test that freeing a newly created mapping (default state) works
TEST_F(PopplerFormFieldMappingTest_2494, FreeNewlyCreatedMapping_2494) {
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    
    // Free immediately after creation - should not crash
    poppler_form_field_mapping_free(mapping);
}

// Test copy of NULL returns NULL
TEST_F(PopplerFormFieldMappingTest_2494, CopyNullReturnsNull_2494) {
    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test area coordinates are preserved in new mapping
TEST_F(PopplerFormFieldMappingTest_2494, AreaCoordinatesPreserved_2494) {
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    
    mapping->area.x1 = 100.5;
    mapping->area.y1 = 200.5;
    mapping->area.x2 = 300.5;
    mapping->area.y2 = 400.5;
    
    EXPECT_DOUBLE_EQ(mapping->area.x1, 100.5);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 200.5);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 300.5);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 400.5);
    
    poppler_form_field_mapping_free(mapping);
}

// Test multiple allocations and frees (stress test for memory)
TEST_F(PopplerFormFieldMappingTest_2494, MultipleAllocAndFree_2494) {
    for (int i = 0; i < 100; i++) {
        PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
        ASSERT_NE(mapping, nullptr);
        mapping->field = nullptr;
        mapping->area.x1 = static_cast<double>(i);
        poppler_form_field_mapping_free(mapping);
    }
}
