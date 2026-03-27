#include <gtest/gtest.h>

#include "poppler-page.h"



class PopplerFormFieldMappingTest : public ::testing::Test {

protected:

    void SetUp() override {

        mapping = poppler_form_field_mapping_new();

    }



    void TearDown() override {

        g_slice_free(PopplerFormFieldMapping, mapping);

    }



    PopplerFormFieldMapping* mapping;

};



TEST_F(PopplerFormFieldMappingTest_2492, NewInstanceNotNull_2492) {

    EXPECT_NE(mapping, nullptr);

}



// Since the provided interface is very limited and does not include any methods to interact with the PopplerFormFieldMapping instance,

// there are no additional normal operation, boundary conditions, or exceptional cases to test based on the given function signature.

// The only observable behavior is that a non-null pointer is returned when creating a new instance.



// If there were more functions in the interface, we could write tests for those as well, but with the current information,

// this is the extent of the test coverage possible.
