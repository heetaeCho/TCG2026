#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



// Mock for PopplerFormField to verify g_object_unref calls

class MockPopplerFormField {

public:

    MOCK_METHOD0(g_object_unref, void());

};



namespace {



TEST(poppler_form_field_mapping_free_Test_2494, NullMapping_2494) {

    // Test case: Verify that null pointer does not cause any issues

    poppler_form_field_mapping_free(nullptr);

}



TEST(poppler_form_field_mapping_free_Test_2494, NonNullMappingNoField_2494) {

    // Test case: Verify that if field is nullptr, no g_object_unref call occurs

    PopplerFormFieldMapping mapping = {nullptr};

    poppler_form_field_mapping_free(&mapping);

}



TEST(poppler_form_field_mapping_free_Test_2494, NonNullMappingWithField_2494) {

    // Test case: Verify that if field is not nullptr, g_object_unref is called once

    MockPopplerFormField* mockField = new MockPopplerFormField();

    PopplerFormFieldMapping mapping = {reinterpret_cast<PopplerFormField*>(mockField)};

    

    EXPECT_CALL(*mockField, g_object_unref()).Times(1);

    poppler_form_field_mapping_free(&mapping);



    // Clean up the mock object as it's no longer needed

    delete mockField;

}



TEST(poppler_form_field_mapping_free_Test_2494, MultipleMappingsWithFields_2494) {

    // Test case: Verify that multiple mappings with fields call g_object_unref on each field once

    MockPopplerFormField* mockField1 = new MockPopplerFormField();

    MockPopplerFormField* mockField2 = new MockPopplerFormField();



    PopplerFormFieldMapping mapping1 = {reinterpret_cast<PopplerFormField*>(mockField1)};

    PopplerFormFieldMapping mapping2 = {reinterpret_cast<PopplerFormField*>(mockField2)};



    EXPECT_CALL(*mockField1, g_object_unref()).Times(1);

    EXPECT_CALL(*mockField2, g_object_unref()).Times(1);



    poppler_form_field_mapping_free(&mapping1);

    poppler_form_field_mapping_free(&mapping2);



    // Clean up the mock objects as they are no longer needed

    delete mockField1;

    delete mockField2;

}



}  // namespace
