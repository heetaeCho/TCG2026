#include <glib.h>
#include <gtest/gtest.h>

// Include the necessary headers
extern "C" {
#include "poppler-page.h"
}

// Forward declaration of the function under test
extern "C" PopplerImageMapping *poppler_image_mapping_copy(PopplerImageMapping *mapping);

class PopplerImageMappingCopyTest_2487 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that copying a valid PopplerImageMapping returns a non-null pointer
TEST_F(PopplerImageMappingCopyTest_2487, CopyReturnsNonNull_2487)
{
    PopplerImageMapping mapping;
    mapping.area.x1 = 0.0;
    mapping.area.y1 = 0.0;
    mapping.area.x2 = 100.0;
    mapping.area.y2 = 100.0;
    mapping.image_id = 42;

    PopplerImageMapping *copy = poppler_image_mapping_copy(&mapping);
    ASSERT_NE(copy, nullptr);

    poppler_image_mapping_free(copy);
}

// Test that the copied mapping has the same image_id as the original
TEST_F(PopplerImageMappingCopyTest_2487, CopyPreservesImageId_2487)
{
    PopplerImageMapping mapping;
    mapping.area.x1 = 0.0;
    mapping.area.y1 = 0.0;
    mapping.area.x2 = 100.0;
    mapping.area.y2 = 100.0;
    mapping.image_id = 99;

    PopplerImageMapping *copy = poppler_image_mapping_copy(&mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->image_id, 99);

    poppler_image_mapping_free(copy);
}

// Test that the copied mapping has the same area as the original
TEST_F(PopplerImageMappingCopyTest_2487, CopyPreservesArea_2487)
{
    PopplerImageMapping mapping;
    mapping.area.x1 = 10.5;
    mapping.area.y1 = 20.3;
    mapping.area.x2 = 300.7;
    mapping.area.y2 = 400.9;
    mapping.image_id = 7;

    PopplerImageMapping *copy = poppler_image_mapping_copy(&mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 10.5);
    EXPECT_DOUBLE_EQ(copy->area.y1, 20.3);
    EXPECT_DOUBLE_EQ(copy->area.x2, 300.7);
    EXPECT_DOUBLE_EQ(copy->area.y2, 400.9);

    poppler_image_mapping_free(copy);
}

// Test that the copy is a distinct object (different address from original)
TEST_F(PopplerImageMappingCopyTest_2487, CopyIsDifferentObject_2487)
{
    PopplerImageMapping mapping;
    mapping.area.x1 = 0.0;
    mapping.area.y1 = 0.0;
    mapping.area.x2 = 50.0;
    mapping.area.y2 = 50.0;
    mapping.image_id = 1;

    PopplerImageMapping *copy = poppler_image_mapping_copy(&mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, &mapping);

    poppler_image_mapping_free(copy);
}

// Test copying with zero image_id
TEST_F(PopplerImageMappingCopyTest_2487, CopyWithZeroImageId_2487)
{
    PopplerImageMapping mapping;
    mapping.area.x1 = 0.0;
    mapping.area.y1 = 0.0;
    mapping.area.x2 = 0.0;
    mapping.area.y2 = 0.0;
    mapping.image_id = 0;

    PopplerImageMapping *copy = poppler_image_mapping_copy(&mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->image_id, 0);

    poppler_image_mapping_free(copy);
}

// Test copying with negative area coordinates
TEST_F(PopplerImageMappingCopyTest_2487, CopyWithNegativeAreaCoordinates_2487)
{
    PopplerImageMapping mapping;
    mapping.area.x1 = -100.0;
    mapping.area.y1 = -200.0;
    mapping.area.x2 = -50.0;
    mapping.area.y2 = -25.0;
    mapping.image_id = 555;

    PopplerImageMapping *copy = poppler_image_mapping_copy(&mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, -100.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, -200.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, -50.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, -25.0);
    EXPECT_EQ(copy->image_id, 555);

    poppler_image_mapping_free(copy);
}

// Test that modifying the copy does not affect the original
TEST_F(PopplerImageMappingCopyTest_2487, ModifyCopyDoesNotAffectOriginal_2487)
{
    PopplerImageMapping mapping;
    mapping.area.x1 = 1.0;
    mapping.area.y1 = 2.0;
    mapping.area.x2 = 3.0;
    mapping.area.y2 = 4.0;
    mapping.image_id = 10;

    PopplerImageMapping *copy = poppler_image_mapping_copy(&mapping);
    ASSERT_NE(copy, nullptr);

    copy->image_id = 999;
    copy->area.x1 = 500.0;

    EXPECT_EQ(mapping.image_id, 10);
    EXPECT_DOUBLE_EQ(mapping.area.x1, 1.0);

    poppler_image_mapping_free(copy);
}

// Test copying with large image_id value
TEST_F(PopplerImageMappingCopyTest_2487, CopyWithLargeImageId_2487)
{
    PopplerImageMapping mapping;
    mapping.area.x1 = 0.0;
    mapping.area.y1 = 0.0;
    mapping.area.x2 = 1.0;
    mapping.area.y2 = 1.0;
    mapping.image_id = 2147483647; // INT_MAX

    PopplerImageMapping *copy = poppler_image_mapping_copy(&mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->image_id, 2147483647);

    poppler_image_mapping_free(copy);
}
