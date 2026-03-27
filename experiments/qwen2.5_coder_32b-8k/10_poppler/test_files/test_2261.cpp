#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-document.cc"

#include "./TestProjects/poppler/poppler/Form.h"



using namespace testing;



class PopplerDocumentMock : public PopplerDocument {

public:

    MOCK_METHOD(PopplerFormField*, get_form_field, (gint id), override);

};



TEST_F(PopplerDocumentMock, GetFormField_ValidID_ReturnsFormField_2261) {

    // Arrange

    PopplerDocument document;

    gint valid_id = 100; // Example valid ID

    FormWidget* formWidgetMock = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr);

    EXPECT_CALL(*reinterpret_cast<FormPageWidgets*>(document.doc->getPage(0)->getFormWidgets().release()), getWidget(0))

        .WillOnce(Return(formWidgetMock));



    // Act

    PopplerFormField* result = poppler_document_get_form_field(&document, valid_id);



    // Assert

    ASSERT_NE(result, nullptr);

}



TEST_F(PopplerDocumentMock, GetFormField_InvalidPage_ReturnsNull_2261) {

    // Arrange

    PopplerDocument document;

    gint invalid_page_id = FormWidget::encodeID(999, 0); // Assuming page does not exist



    // Act

    PopplerFormField* result = poppler_document_get_form_field(&document, invalid_page_id);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentMock, GetFormField_InvalidField_ReturnsNull_2261) {

    // Arrange

    PopplerDocument document;

    gint invalid_field_id = FormWidget::encodeID(0, 999); // Assuming field does not exist on page 0



    EXPECT_CALL(*reinterpret_cast<FormPageWidgets*>(document.doc->getPage(0)->getFormWidgets().release()), getWidget(999))

        .WillOnce(Return(nullptr));



    // Act

    PopplerFormField* result = poppler_document_get_form_field(&document, invalid_field_id);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentMock, GetFormField_ZeroID_ReturnsNull_2261) {

    // Arrange

    PopplerDocument document;

    gint zero_id = 0; // Assuming zero ID is not valid



    // Act

    PopplerFormField* result = poppler_document_get_form_field(&document, zero_id);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentMock, GetFormField_NegativeID_ReturnsNull_2261) {

    // Arrange

    PopplerDocument document;

    gint negative_id = -1; // Assuming negative ID is not valid



    // Act

    PopplerFormField* result = poppler_document_get_form_field(&document, negative_id);



    // Assert

    ASSERT_EQ(result, nullptr);

}
