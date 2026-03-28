#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

// Forward declarations for poppler types
typedef struct _PopplerFormFieldMapping PopplerFormFieldMapping;
typedef struct _PopplerRectangle PopplerRectangle;

// The struct definition based on poppler's public API
struct _PopplerRectangle
{
    double x1;
    double y1;
    double x2;
    double y2;
};

struct _PopplerFormFieldMapping
{
    PopplerRectangle area;
    void *field; // PopplerFormField*
};

// Function under test
PopplerFormFieldMapping *poppler_form_field_mapping_new(void);
PopplerFormFieldMapping *poppler_form_field_mapping_copy(PopplerFormFieldMapping *mapping);
void poppler_form_field_mapping_free(PopplerFormFieldMapping *mapping);
}

class PopplerFormFieldMappingTest_2492 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup is handled in individual tests
    }
};

// Test that poppler_form_field_mapping_new returns a non-null pointer
TEST_F(PopplerFormFieldMappingTest_2492, NewReturnsNonNull_2492)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    poppler_form_field_mapping_free(mapping);
}

// Test that newly created mapping is zero-initialized
TEST_F(PopplerFormFieldMappingTest_2492, NewIsZeroInitialized_2492)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);

    // g_slice_new0 should zero-initialize all fields
    EXPECT_DOUBLE_EQ(mapping->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 0.0);
    EXPECT_EQ(mapping->field, nullptr);

    poppler_form_field_mapping_free(mapping);
}

// Test that multiple allocations return distinct pointers
TEST_F(PopplerFormFieldMappingTest_2492, MultipleAllocationsReturnDistinctPointers_2492)
{
    PopplerFormFieldMapping *mapping1 = poppler_form_field_mapping_new();
    PopplerFormFieldMapping *mapping2 = poppler_form_field_mapping_new();

    ASSERT_NE(mapping1, nullptr);
    ASSERT_NE(mapping2, nullptr);
    EXPECT_NE(mapping1, mapping2);

    poppler_form_field_mapping_free(mapping1);
    poppler_form_field_mapping_free(mapping2);
}

// Test that we can write to the returned mapping's fields without crashing
TEST_F(PopplerFormFieldMappingTest_2492, CanWriteToFields_2492)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 10.5;
    mapping->area.y1 = 20.5;
    mapping->area.x2 = 100.0;
    mapping->area.y2 = 200.0;

    EXPECT_DOUBLE_EQ(mapping->area.x1, 10.5);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 20.5);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 100.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 200.0);

    poppler_form_field_mapping_free(mapping);
}

// Test allocation and free of many mappings (stress/boundary test)
TEST_F(PopplerFormFieldMappingTest_2492, AllocateAndFreeMany_2492)
{
    const int count = 100;
    PopplerFormFieldMapping *mappings[count];

    for (int i = 0; i < count; i++) {
        mappings[i] = poppler_form_field_mapping_new();
        ASSERT_NE(mappings[i], nullptr);
    }

    for (int i = 0; i < count; i++) {
        poppler_form_field_mapping_free(mappings[i]);
    }
}

// Test that free with NULL does not crash (if supported)
TEST_F(PopplerFormFieldMappingTest_2492, FreeNullDoesNotCrash_2492)
{
    // poppler_form_field_mapping_free should handle NULL gracefully
    poppler_form_field_mapping_free(nullptr);
}
