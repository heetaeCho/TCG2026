#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "poppler-private.h"



// Mocking external collaborators if needed

class MockPopplerAction {

public:

    MOCK_METHOD(void, free, ());

};



using ::testing::Return;

using ::testing::_;



TEST_F(PopplerFormFieldTest_2305, FinalizeWithDocumentAndActions_2305) {

    // Arrange

    GObject obj;

    PopplerFormField* field = reinterpret_cast<PopplerFormField*>(&obj);

    field->document = reinterpret_cast<GObject*>(new char);  // Mock document

    field->action = new MockPopplerAction;  // Mock action



    EXPECT_CALL(*reinterpret_cast<MockPopplerAction*>(field->action), free()).Times(1);



    // Act

    poppler_form_field_finalize(&obj);



    // Assert

    ASSERT_EQ(field->document, nullptr);

    ASSERT_EQ(field->action, nullptr);

}



TEST_F(PopplerFormFieldTest_2305, FinalizeWithoutDocumentAndActions_2305) {

    // Arrange

    GObject obj;

    PopplerFormField* field = reinterpret_cast<PopplerFormField*>(&obj);

    field->document = nullptr;

    field->action = nullptr;



    // Act

    poppler_form_field_finalize(&obj);



    // Assert

    ASSERT_EQ(field->document, nullptr);

    ASSERT_EQ(field->action, nullptr);

}



TEST_F(PopplerFormFieldTest_2305, FinalizeWithDocumentNoActions_2305) {

    // Arrange

    GObject obj;

    PopplerFormField* field = reinterpret_cast<PopplerFormField*>(&obj);

    field->document = reinterpret_cast<GObject*>(new char);  // Mock document

    field->action = nullptr;



    // Act

    poppler_form_field_finalize(&obj);



    // Assert

    ASSERT_EQ(field->document, nullptr);

    ASSERT_EQ(field->action, nullptr);

}



TEST_F(PopplerFormFieldTest_2305, FinalizeNoDocumentWithActions_2305) {

    // Arrange

    GObject obj;

    PopplerFormField* field = reinterpret_cast<PopplerFormField*>(&obj);

    field->document = nullptr;

    field->action = new MockPopplerAction;  // Mock action



    EXPECT_CALL(*reinterpret_cast<MockPopplerAction*>(field->action), free()).Times(1);



    // Act

    poppler_form_field_finalize(&obj);



    // Assert

    ASSERT_EQ(field->document, nullptr);

    ASSERT_EQ(field->action, nullptr);

}



TEST_F(PopplerFormFieldTest_2305, FinalizeWidgetPointerReset_2305) {

    // Arrange

    GObject obj;

    PopplerFormField* field = reinterpret_cast<PopplerFormField*>(&obj);

    field->document = nullptr;

    field->action = nullptr;

    field->widget = new FormWidget;  // Mock widget



    // Act

    poppler_form_field_finalize(&obj);



    // Assert

    ASSERT_EQ(field->widget, nullptr);

}
