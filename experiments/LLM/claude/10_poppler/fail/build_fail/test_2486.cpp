#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

typedef struct {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

typedef struct {
    PopplerRectangle area;
    gint image_id;
} PopplerImageMapping;

PopplerImageMapping *poppler_image_mapping_new(void);
PopplerImageMapping *poppler_image_mapping_copy(PopplerImageMapping *mapping);
void poppler_image_mapping_free(PopplerImageMapping *mapping);
}

class PopplerImageMappingTest_2486 : public ::testing::Test {
protected:
    void TearDown() override {}
};

TEST_F(PopplerImageMappingTest_2486, NewReturnsNonNull_2486)
{
    PopplerImageMapping *mapping = poppler_image_mapping_new();
    ASSERT_NE(mapping, nullptr);
    g_slice_free(PopplerImageMapping, mapping);
}

TEST_F(PopplerImageMappingTest_2486, NewReturnsZeroInitialized_2486)
{
    PopplerImageMapping *mapping = poppler_image_mapping_new();
    ASSERT_NE(mapping, nullptr);

    // g_slice_new0 zero-initializes the memory
    EXPECT_DOUBLE_EQ(mapping->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 0.0);
    EXPECT_EQ(mapping->image_id, 0);

    g_slice_free(PopplerImageMapping, mapping);
}

TEST_F(PopplerImageMappingTest_2486, MultipleAllocationsReturnDistinctPointers_2486)
{
    PopplerImageMapping *mapping1 = poppler_image_mapping_new();
    PopplerImageMapping *mapping2 = poppler_image_mapping_new();

    ASSERT_NE(mapping1, nullptr);
    ASSERT_NE(mapping2, nullptr);
    EXPECT_NE(mapping1, mapping2);

    g_slice_free(PopplerImageMapping, mapping1);
    g_slice_free(PopplerImageMapping, mapping2);
}

TEST_F(PopplerImageMappingTest_2486, NewMappingFieldsAreWritable_2486)
{
    PopplerImageMapping *mapping = poppler_image_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 10.5;
    mapping->area.y1 = 20.5;
    mapping->area.x2 = 30.5;
    mapping->area.y2 = 40.5;
    mapping->image_id = 42;

    EXPECT_DOUBLE_EQ(mapping->area.x1, 10.5);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 20.5);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 30.5);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 40.5);
    EXPECT_EQ(mapping->image_id, 42);

    g_slice_free(PopplerImageMapping, mapping);
}

TEST_F(PopplerImageMappingTest_2486, AllocateManyMappings_2486)
{
    const int count = 100;
    PopplerImageMapping *mappings[count];

    for (int i = 0; i < count; i++) {
        mappings[i] = poppler_image_mapping_new();
        ASSERT_NE(mappings[i], nullptr);
        EXPECT_EQ(mappings[i]->image_id, 0);
    }

    for (int i = 0; i < count; i++) {
        g_slice_free(PopplerImageMapping, mappings[i]);
    }
}
