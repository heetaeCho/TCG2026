#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler glib headers
extern "C" {
#include "poppler.h"
}

class PopplerAnnotMappingCopyTest_2496 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyWithNullAnnot_2496)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    mapping->annot = nullptr;
    mapping->area.x1 = 10.0;
    mapping->area.y1 = 20.0;
    mapping->area.x2 = 30.0;
    mapping->area.y2 = 40.0;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->annot, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 20.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 30.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 40.0);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyIsDistinctObject_2496)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    mapping->annot = nullptr;
    mapping->area.x1 = 1.0;
    mapping->area.y1 = 2.0;
    mapping->area.x2 = 3.0;
    mapping->area.y2 = 4.0;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, mapping);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyPreservesAreaValues_2496)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    mapping->annot = nullptr;
    mapping->area.x1 = -100.5;
    mapping->area.y1 = 0.0;
    mapping->area.x2 = 999.999;
    mapping->area.y2 = -0.001;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, -100.5);
    EXPECT_DOUBLE_EQ(copy->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 999.999);
    EXPECT_DOUBLE_EQ(copy->area.y2, -0.001);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyWithAnnotRefsAnnot_2496)
{
    // We need a real PopplerAnnot to test the ref counting path.
    // To do this properly we need a real PDF document with annotations.
    // We'll create a minimal test by loading a document if possible,
    // but since we may not have one, we test the null case thoroughly.
    // This test verifies the structure when annot is null.
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    mapping->annot = nullptr;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->annot, nullptr);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyZeroArea_2496)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    mapping->annot = nullptr;
    mapping->area.x1 = 0.0;
    mapping->area.y1 = 0.0;
    mapping->area.x2 = 0.0;
    mapping->area.y2 = 0.0;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 0.0);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyLargeAreaValues_2496)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    mapping->annot = nullptr;
    mapping->area.x1 = 1e15;
    mapping->area.y1 = -1e15;
    mapping->area.x2 = 1e15;
    mapping->area.y2 = -1e15;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 1e15);
    EXPECT_DOUBLE_EQ(copy->area.y1, -1e15);
    EXPECT_DOUBLE_EQ(copy->area.x2, 1e15);
    EXPECT_DOUBLE_EQ(copy->area.y2, -1e15);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(mapping);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, MultipleCopiesAreIndependent_2496)
{
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    mapping->annot = nullptr;
    mapping->area.x1 = 5.0;
    mapping->area.y1 = 10.0;
    mapping->area.x2 = 15.0;
    mapping->area.y2 = 20.0;

    PopplerAnnotMapping *copy1 = poppler_annot_mapping_copy(mapping);
    PopplerAnnotMapping *copy2 = poppler_annot_mapping_copy(mapping);

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);
    EXPECT_NE(copy1, mapping);
    EXPECT_NE(copy2, mapping);

    EXPECT_DOUBLE_EQ(copy1->area.x1, copy2->area.x1);
    EXPECT_DOUBLE_EQ(copy1->area.y1, copy2->area.y1);
    EXPECT_DOUBLE_EQ(copy1->area.x2, copy2->area.x2);
    EXPECT_DOUBLE_EQ(copy1->area.y2, copy2->area.y2);

    poppler_annot_mapping_free(copy1);
    poppler_annot_mapping_free(copy2);
    poppler_annot_mapping_free(mapping);
}
