#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "poppler-private.h"



using namespace testing;



class PopplerFormFieldChoiceTest : public Test {

protected:

    PDFDoc* mockPDFDoc = nullptr;

    Object* mockObject = nullptr;

    Ref mockRef;

    FormField* mockFormField = nullptr;

    FormWidgetChoice* formWidgetChoice = new FormWidgetChoice(mockPDFDoc, mockObject, 0, mockRef, mockFormField);

    PopplerFormField popplerFormField;



    void SetUp() override {

        popplerFormField.widget = formWidgetChoice;

    }



    void TearDown() override {

        delete formWidgetChoice;

    }

};



TEST_F(PopplerFormFieldChoiceTest_2349, UnselectAllOnChoiceField_2349) {

    EXPECT_CALL(*formWidgetChoice, deselectAll());



    poppler_form_field_choice_unselect_all(&popplerFormField);

}



TEST_F(PopplerFormFieldChoiceTest_2349, UnselectAllOnNonChoiceFieldThrows_2349) {

    formWidgetChoice->setType(formText); // Assuming a method to set type for testing purposes

    EXPECT_DEATH(poppler_form_field_choice_unselect_all(&popplerFormField), ".*");

}



TEST_F(PopplerFormFieldChoiceTest_2349, UnselectAllNullFieldPointer_2349) {

    EXPECT_DEATH(poppler_form_field_choice_unselect_all(nullptr), ".*");

}
