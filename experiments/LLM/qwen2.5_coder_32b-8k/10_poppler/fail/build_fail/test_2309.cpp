#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"



using namespace testing;



class PopplerFormFieldTest_2309 : public Test {

protected:

    MockPopplerFormField mockField;

    std::unique_ptr<FormWidget> formWidget;



    class MockFormWidget : public FormWidget {

    public:

        MOCK_METHOD(unsigned, getID, (), (const, override));

    };



    class MockPopplerFormField {

    public:

        MockFormWidget* widget;

    };



    void SetUp() override {

        formWidget = std::make_unique<MockFormWidget>();

        mockField.widget = formWidget.get();

    }

};



TEST_F(PopplerFormFieldTest_2309, GetId_NormalOperation_2309) {

    EXPECT_CALL(*formWidget, getID()).WillOnce(Return(42));

    gint id = poppler_form_field_get_id(reinterpret_cast<PopplerFormField*>(&mockField));

    EXPECT_EQ(id, 42);

}



TEST_F(PopplerFormFieldTest_2309, GetId_NullPointer_2309) {

    gint id = poppler_form_field_get_id(nullptr);

    EXPECT_EQ(id, -1);

}



TEST_F(PopplerFormFieldTest_2309, GetId_BoundaryCondition_2309) {

    EXPECT_CALL(*formWidget, getID()).WillOnce(Return(0));

    gint id = poppler_form_field_get_id(reinterpret_cast<PopplerFormField*>(&mockField));

    EXPECT_EQ(id, 0);

}



TEST_F(PopplerFormFieldTest_2309, GetId_ExceptionalCase_2309) {

    // Assuming getID() could throw an exception, although the actual implementation does not show this.

    // This is more of a hypothetical test case to demonstrate handling exceptional cases if needed.

    EXPECT_CALL(*formWidget, getID()).WillOnce(Throw(std::runtime_error("Simulated Exception")));

    // Since the function returns -1 on failure and we are treating it as a black box,

    // we expect it to handle exceptions internally and return -1.

    gint id = poppler_form_field_get_id(reinterpret_cast<PopplerFormField*>(&mockField));

    EXPECT_EQ(id, -1);

}
