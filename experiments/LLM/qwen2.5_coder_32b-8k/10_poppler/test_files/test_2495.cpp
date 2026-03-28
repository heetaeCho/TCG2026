#include <gtest/gtest.h>

#include "poppler-page.h"



// Test fixture for PopplerAnnotMapping tests

class PopplerAnnotMappingTest_2495 : public ::testing::Test {

protected:

    void SetUp() override {

        // No setup needed as the function under test does not require any initial state.

    }



    void TearDown() override {

        // No teardown needed for this simple test case.

    }

};



// Test that poppler_annot_mapping_new returns a non-null pointer

TEST_F(PopplerAnnotMappingTest_2495, NewReturnsNonNullPointer_2495) {

    PopplerAnnotMapping* mapping = poppler_annot_mapping_new();

    EXPECT_NE(mapping, nullptr);

    g_slice_free(PopplerAnnotMapping, mapping);  // Clean up the allocated memory

}



// Test that multiple calls to poppler_annot_mapping_new return different instances

TEST_F(PopplerAnnotMappingTest_2495, MultipleCallsReturnDifferentInstances_2495) {

    PopplerAnnotMapping* mapping1 = poppler_annot_mapping_new();

    PopplerAnnotMapping* mapping2 = poppler_annot_mapping_new();

    EXPECT_NE(mapping1, mapping2);

    g_slice_free(PopplerAnnotMapping, mapping1);  // Clean up the allocated memory

    g_slice_free(PopplerAnnotMapping, mapping2);  // Clean up the allocated memory

}
