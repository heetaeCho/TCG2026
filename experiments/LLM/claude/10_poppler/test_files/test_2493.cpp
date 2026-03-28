#include <gtest/gtest.h>
#include <glib-object.h>

extern "C" {
#include "poppler.h"
}

class PopplerFormFieldMappingTest_2493 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerFormFieldMappingTest_2493, CopyNullField_2493)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    mapping->field = nullptr;

    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->field, nullptr);
    EXPECT_NE(copy, mapping);

    poppler_form_field_mapping_free(copy);
    poppler_form_field_mapping_free(mapping);
}

TEST_F(PopplerFormFieldMappingTest_2493, CopyReturnsDifferentPointer_2493)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    mapping->field = nullptr;

    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, mapping);

    poppler_form_field_mapping_free(copy);
    poppler_form_field_mapping_free(mapping);
}

TEST_F(PopplerFormFieldMappingTest_2493, CopyPreservesArea_2493)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
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

    poppler_form_field_mapping_free(copy);
    poppler_form_field_mapping_free(mapping);
}

TEST_F(PopplerFormFieldMappingTest_2493, CopyWithFieldRefsObject_2493)
{
    // We need a real PopplerDocument and PopplerPage to get a real form field.
    // Since we can't easily create one without a PDF, we test the null field case thoroughly.
    // This test verifies that when field is NULL, copy works correctly.
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    mapping->field = nullptr;
    mapping->area.x1 = 0.0;
    mapping->area.y1 = 0.0;
    mapping->area.x2 = 100.0;
    mapping->area.y2 = 100.0;

    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->field, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 100.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 100.0);

    poppler_form_field_mapping_free(copy);
    poppler_form_field_mapping_free(mapping);
}

TEST_F(PopplerFormFieldMappingTest_2493, NewMappingInitialization_2493)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();

    ASSERT_NE(mapping, nullptr);

    poppler_form_field_mapping_free(mapping);
}

TEST_F(PopplerFormFieldMappingTest_2493, CopyBoundaryAreaValues_2493)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    mapping->field = nullptr;
    mapping->area.x1 = -999999.0;
    mapping->area.y1 = -999999.0;
    mapping->area.x2 = 999999.0;
    mapping->area.y2 = 999999.0;

    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, -999999.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, -999999.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 999999.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 999999.0);

    poppler_form_field_mapping_free(copy);
    poppler_form_field_mapping_free(mapping);
}

TEST_F(PopplerFormFieldMappingTest_2493, CopyZeroArea_2493)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    mapping->field = nullptr;
    mapping->area.x1 = 0.0;
    mapping->area.y1 = 0.0;
    mapping->area.x2 = 0.0;
    mapping->area.y2 = 0.0;

    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 0.0);

    poppler_form_field_mapping_free(copy);
    poppler_form_field_mapping_free(mapping);
}

TEST_F(PopplerFormFieldMappingTest_2493, MultipleCopiesAreIndependent_2493)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    mapping->field = nullptr;
    mapping->area.x1 = 1.0;
    mapping->area.y1 = 2.0;
    mapping->area.x2 = 3.0;
    mapping->area.y2 = 4.0;

    PopplerFormFieldMapping *copy1 = poppler_form_field_mapping_copy(mapping);
    PopplerFormFieldMapping *copy2 = poppler_form_field_mapping_copy(mapping);

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);
    EXPECT_NE(copy1, mapping);
    EXPECT_NE(copy2, mapping);

    EXPECT_DOUBLE_EQ(copy1->area.x1, 1.0);
    EXPECT_DOUBLE_EQ(copy2->area.x1, 1.0);

    poppler_form_field_mapping_free(copy1);
    poppler_form_field_mapping_free(copy2);
    poppler_form_field_mapping_free(mapping);
}
