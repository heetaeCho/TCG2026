#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



using ::testing::NotNull;



TEST(PopplerFormFieldMappingTest_2493, CopyCreatesNewInstance_2493) {

    PopplerFormFieldMapping original;

    original.field = nullptr;



    PopplerFormFieldMapping* copy = poppler_form_field_mapping_copy(&original);



    EXPECT_NE(copy, &original);

    EXPECT_EQ(copy->field, nullptr);



    g_slice_free(PopplerFormFieldMapping, copy);

}



TEST(PopplerFormFieldMappingTest_2493, CopyHandlesNullField_2493) {

    PopplerFormFieldMapping original;

    original.field = nullptr;



    PopplerFormFieldMapping* copy = poppler_form_field_mapping_copy(&original);



    EXPECT_EQ(copy->field, nullptr);



    g_slice_free(PopplerFormFieldMapping, copy);

}



TEST(PopplerFormFieldMappingTest_2493, CopyHandlesNonNullField_2493) {

    PopplerFormField dummy_field;

    PopplerFormFieldMapping original;

    original.field = &dummy_field;



    PopplerFormFieldMapping* copy = poppler_form_field_mapping_copy(&original);



    EXPECT_NE(copy->field, nullptr);

    EXPECT_EQ(copy->field, original.field);



    g_slice_free(PopplerFormFieldMapping, copy);

}
