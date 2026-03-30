#include <gtest/gtest.h>

#include "poppler-private.h"



namespace Poppler {

    class FormFieldIcon;

}



class FormFieldIconDataTest_1291 : public ::testing::Test {

protected:

    using FormData = Poppler::FormFieldIconData;



    FormData formData;

    Poppler::FormFieldIcon formFieldIcon;

};



TEST_F(FormFieldIconDataTest_1291, GetDataReturnsNonNullPointer_1291) {

    // Test if getData returns a non-null pointer when called with a valid FormFieldIcon object.

    ASSERT_NE(formData.getData(formFieldIcon), nullptr);

}



TEST_F(FormFieldIconDataTest_1291, GetDataReturnsSameInstance_1291) {

    // Test if multiple calls to getData return the same instance for the same FormFieldIcon object.

    auto* data1 = formData.getData(formFieldIcon);

    auto* data2 = formData.getData(formFieldIcon);

    EXPECT_EQ(data1, data2);

}



TEST_F(FormFieldIconDataTest_1291, BoundaryConditionWithDefaultConstructedFormFieldIcon_1291) {

    // Test boundary condition with a default-constructed FormFieldIcon object.

    Poppler::FormFieldIcon defaultFormFieldIcon;

    ASSERT_NE(formData.getData(defaultFormFieldIcon), nullptr);

}
