#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-document.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



// Mock FormWidget for testing purposes

class MockFormWidget : public FormWidget {

public:

    MOCK_METHOD0(getCreateWidget, FormWidget*());

};



// Mock FormFieldSignature for testing purposes

class MockFormFieldSignature : public FormFieldSignature {

public:

    MOCK_METHOD0(getCreateWidget, FormWidget*());

};



// Test fixture for PopplerDocument tests

class PopplerDocumentTest_2194 : public ::testing::Test {

protected:

    PopplerDocument *document;

    std::vector<MockFormFieldSignature*> mock_signature_fields;



    void SetUp() override {

        document = new PopplerDocument();

        // Simulate the internal state with some mock signature fields

        for (int i = 0; i < 3; ++i) {

            MockFormFieldSignature *mock_field = new MockFormFieldSignature();

            mock_signature_fields.push_back(mock_field);

        }

    }



    void TearDown() override {

        g_list_free_full(document->doc->getSignatureFields(), g_object_unref);

        delete document;

        for (auto field : mock_signature_fields) {

            delete field;

        }

    }

};



// Test normal operation with multiple signature fields

TEST_F(PopplerDocumentTest_2194, GetSignatureFields_NormalOperation_2194) {

    // Setup expectations on mock objects

    for (MockFormFieldSignature* field : mock_signature_fields) {

        EXPECT_CALL(*field, getCreateWidget()).WillOnce(::testing::Return(field));

    }



    // Set the mock signature fields in the document's internal state

    document->doc->getSignatureFields() = std::vector<FormFieldSignature*>(

        mock_signature_fields.begin(), mock_signature_fields.end());



    GList* result = poppler_document_get_signature_fields(document);

    

    // Verify that the result list contains all the expected elements

    EXPECT_EQ(g_list_length(result), mock_signature_fields.size());

    for (GList *l = result; l != nullptr; l = g_list_next(l)) {

        EXPECT_TRUE(g_list_find(mock_signature_fields, l->data) != nullptr);

    }

    

    // Clean up the result list

    g_list_free_full(result, g_object_unref);

}



// Test boundary condition with no signature fields

TEST_F(PopplerDocumentTest_2194, GetSignatureFields_NoFields_2194) {

    // Simulate an empty list of signature fields

    document->doc->getSignatureFields().clear();



    GList* result = poppler_document_get_signature_fields(document);



    EXPECT_EQ(result, nullptr);

}



// Test boundary condition with a single signature field

TEST_F(PopplerDocumentTest_2194, GetSignatureFields_SingleField_2194) {

    // Setup expectations on the mock object

    MockFormFieldSignature* field = mock_signature_fields[0];

    EXPECT_CALL(*field, getCreateWidget()).WillOnce(::testing::Return(field));



    // Set a single mock signature field in the document's internal state

    document->doc->getSignatureFields() = {field};



    GList* result = poppler_document_get_signature_fields(document);



    // Verify that the result list contains exactly one element, which is the mock field

    EXPECT_EQ(g_list_length(result), 1);

    EXPECT_TRUE(g_list_find(mock_signature_fields, result->data) != nullptr);



    // Clean up the result list

    g_list_free_full(result, g_object_unref);

}



// Test exceptional case where a signature field has no corresponding widget

TEST_F(PopplerDocumentTest_2194, GetSignatureFields_FieldWithoutWidget_2194) {

    MockFormFieldSignature* field = mock_signature_fields[0];

    EXPECT_CALL(*field, getCreateWidget()).WillOnce(::testing::Return(nullptr));



    document->doc->getSignatureFields() = {field};



    GList* result = poppler_document_get_signature_fields(document);



    // Verify that the result list is empty because no widget was created for any field

    EXPECT_EQ(result, nullptr);

}
