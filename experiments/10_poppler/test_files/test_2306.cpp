#include <gtest/gtest.h>

#include "poppler-form-field.h"



// Assuming PopplerFormField and its related classes are properly included or defined in the scope



class PopplerFormFieldTest_2306 : public ::testing::Test {

protected:

    // Setup and teardown can be added if needed, but for this class definition, it's not necessary

};



TEST_F(PopplerFormFieldTest_2306, ClassInitSetsFinalizeFunction_2306) {

    // Arrange

    PopplerFormFieldClass klass = {};

    

    // Act

    poppler_form_field_class_init(&klass);

    

    // Assert

    ASSERT_TRUE(klass.finalize != nullptr);

}



// Since the provided function only sets a finalize method, there are no additional normal operation,

// boundary conditions, or exceptional/error cases to test based on the given interface.
