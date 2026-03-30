#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Forward declarations and necessary includes for testing

extern "C" {

    #include "./TestProjects/poppler/glib/poppler-form-field.cc"

}

#include "./TestProjects/poppler/poppler/Form.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



using namespace std;

using ::testing::_;

using ::testing::Return;



class MockFormWidgetChoice : public FormWidget {

public:

    MOCK_METHOD(void, setEditChoice, (std::unique_ptr<GooString>), (override));

    MOCK_METHOD(FormFieldType, getType, (), (const, override));



    MockFormWidgetChoice(PDFDoc* docA, Object* aobj, unsigned int num, Ref aref, FormField* fieldA)

        : FormWidget(docA, aobj, num, aref, fieldA) {}

};



class PopplerFormFieldTest_2351 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create mock objects

        pdfDocMock = new PDFDoc();

        objectMock = new Object();

        formFieldMock = new FormField(pdfDocMock, objectMock, 0, Ref(), nullptr);

        formWidgetChoiceMock = new MockFormWidgetChoice(pdfDocMock, objectMock, 1, Ref(), formFieldMock);



        // Initialize PopplerFormField structure

        popplerFormField.widget = formWidgetChoiceMock;

    }



    void TearDown() override {

        delete pdfDocMock;

        delete objectMock;

        delete formFieldMock;

        delete formWidgetChoiceMock;

    }



    PDFDoc* pdfDocMock;

    Object* objectMock;

    FormField* formFieldMock;

    MockFormWidgetChoice* formWidgetChoiceMock;

    _PopplerFormField popplerFormField;

};



TEST_F(PopplerFormFieldTest_2351, SetText_NormalOperation_2351) {

    EXPECT_CALL(*formWidgetChoiceMock, getType()).WillOnce(Return(formChoice));

    EXPECT_CALL(*formWidgetChoiceMock, setEditChoice(_)).Times(1);



    poppler_form_field_choice_set_text(&popplerFormField, "Sample Text");

}



TEST_F(PopplerFormFieldTest_2351, SetText_EmptyString_2351) {

    EXPECT_CALL(*formWidgetChoiceMock, getType()).WillOnce(Return(formChoice));

    EXPECT_CALL(*formWidgetChoiceMock, setEditChoice(_)).Times(1);



    poppler_form_field_choice_set_text(&popplerFormField, "");

}



TEST_F(PopplerFormFieldTest_2351, SetText_NullPointer_2351) {

    EXPECT_CALL(*formWidgetChoiceMock, getType()).WillOnce(Return(formChoice));

    EXPECT_CALL(*formWidgetChoiceMock, setEditChoice(_)).Times(1);



    poppler_form_field_choice_set_text(&popplerFormField, nullptr);

}



TEST_F(PopplerFormFieldTest_2351, SetText_WrongType_2351) {

    EXPECT_CALL(*formWidgetChoiceMock, getType()).WillOnce(Return(formText));

    EXPECT_CALL(*formWidgetChoiceMock, setEditChoice(_)).Times(0);



    poppler_form_field_choice_set_text(&popplerFormField, "Sample Text");

}
