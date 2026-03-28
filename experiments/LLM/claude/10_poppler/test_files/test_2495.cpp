#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

typedef struct _PopplerAnnotMapping PopplerAnnotMapping;

// Forward declaration of the function under test
PopplerAnnotMapping *poppler_annot_mapping_new(void);

// We also need the free function to avoid memory leaks
void poppler_annot_mapping_free(PopplerAnnotMapping *mapping);

// PopplerAnnotMapping is a public struct in poppler-glib
// It contains area (PopplerRectangle) and annot (PopplerAnnot*)
typedef struct {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

}

// Since PopplerAnnotMapping is defined in poppler headers, we need to include them
// For testing purposes, we work with the actual poppler-glib headers
#include <poppler.h>

class PopplerAnnotMappingTest_2495 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated mappings
    }
};

TEST_F(PopplerAnnotMappingTest_2495, NewReturnsNonNull_2495)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);
    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingTest_2495, NewReturnsZeroInitialized_2495)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);

    // Since g_slice_new0 is used, the struct should be zero-initialized
    // Check that the area rectangle is zero-initialized
    EXPECT_DOUBLE_EQ(mapping->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 0.0);

    // Check that the annot pointer is NULL (zero-initialized)
    EXPECT_EQ(mapping->annot, nullptr);

    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingTest_2495, MultipleAllocationsReturnDistinctPointers_2495)
{
    PopplerAnnotMapping *mapping1 = poppler_annot_mapping_new();
    PopplerAnnotMapping *mapping2 = poppler_annot_mapping_new();

    ASSERT_NE(mapping1, nullptr);
    ASSERT_NE(mapping2, nullptr);
    EXPECT_NE(mapping1, mapping2);

    poppler_annot_mapping_free(mapping1);
    poppler_annot_mapping_free(mapping2);
}

TEST_F(PopplerAnnotMappingTest_2495, CanModifyAreaAfterCreation_2495)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 10.0;
    mapping->area.y1 = 20.0;
    mapping->area.x2 = 100.0;
    mapping->area.y2 = 200.0;

    EXPECT_DOUBLE_EQ(mapping->area.x1, 10.0);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 20.0);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 100.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 200.0);

    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingTest_2495, CopyProducesIndependentCopy_2495)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 5.0;
    mapping->area.y1 = 10.0;
    mapping->area.x2 = 50.0;
    mapping->area.y2 = 100.0;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, mapping);

    EXPECT_DOUBLE_EQ(copy->area.x1, 5.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 50.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 100.0);

    poppler_annot_mapping_free(mapping);
    poppler_annot_mapping_free(copy);
}

TEST_F(PopplerAnnotMappingTest_2495, ManyAllocationsSucceed_2495)
{
    const int count = 100;
    PopplerAnnotMapping *mappings[count];

    for (int i = 0; i < count; i++) {
        mappings[i] = poppler_annot_mapping_new();
        ASSERT_NE(mappings[i], nullptr);
    }

    for (int i = 0; i < count; i++) {
        poppler_annot_mapping_free(mappings[i]);
    }
}
