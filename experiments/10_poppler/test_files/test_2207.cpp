#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "poppler-document.h"

}



class PopplerDocumentTest_2207 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if necessary

        document = static_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

    }



    void TearDown() override {

        // Teardown code, if necessary

        g_object_unref(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2207, ResetFormWithValidFieldsExcluded_2207) {

    GList *fields = nullptr;

    fields = g_list_append(fields, const_cast<gchar*>("field1"));

    fields = g_list_append(fields, const_cast<gchar*>("field2"));



    poppler_document_reset_form(document, fields, TRUE);



    // Verify that the function completes without errors and check any observable behavior

    EXPECT_EQ(g_list_length(fields), 2);

    g_list_free_full(fields, g_free);

}



TEST_F(PopplerDocumentTest_2207, ResetFormWithValidFieldsIncluded_2207) {

    GList *fields = nullptr;

    fields = g_list_append(fields, const_cast<gchar*>("field1"));

    fields = g_list_append(fields, const_cast<gchar*>("field2"));



    poppler_document_reset_form(document, fields, FALSE);



    // Verify that the function completes without errors and check any observable behavior

    EXPECT_EQ(g_list_length(fields), 2);

    g_list_free_full(fields, g_free);

}



TEST_F(PopplerDocumentTest_2207, ResetFormWithEmptyFieldsExcluded_2207) {

    GList *fields = nullptr;



    poppler_document_reset_form(document, fields, TRUE);



    // Verify that the function completes without errors and check any observable behavior

    EXPECT_EQ(g_list_length(fields), 0);

}



TEST_F(PopplerDocumentTest_2207, ResetFormWithEmptyFieldsIncluded_2207) {

    GList *fields = nullptr;



    poppler_document_reset_form(document, fields, FALSE);



    // Verify that the function completes without errors and check any observable behavior

    EXPECT_EQ(g_list_length(fields), 0);

}



TEST_F(PopplerDocumentTest_2207, ResetFormWithNullFieldsExcluded_2207) {

    GList *fields = nullptr;



    poppler_document_reset_form(document, fields, TRUE);



    // Verify that the function completes without errors and check any observable behavior

    EXPECT_EQ(g_list_length(fields), 0);

}



TEST_F(PopplerDocumentTest_2207, ResetFormWithNullFieldsIncluded_2207) {

    GList *fields = nullptr;



    poppler_document_reset_form(document, fields, FALSE);



    // Verify that the function completes without errors and check any observable behavior

    EXPECT_EQ(g_list_length(fields), 0);

}



TEST_F(PopplerDocumentTest_2207, ResetFormWithInvalidDocumentExcluded_2207) {

    GList *fields = nullptr;

    fields = g_list_append(fields, const_cast<gchar*>("field1"));

    fields = g_list_append(fields, const_cast<gchar*>("field2"));



    PopplerDocument* invalid_document = nullptr;



    poppler_document_reset_form(invalid_document, fields, TRUE);



    // Verify that the function completes without errors and check any observable behavior

    EXPECT_EQ(g_list_length(fields), 2);

    g_list_free_full(fields, g_free);

}



TEST_F(PopplerDocumentTest_2207, ResetFormWithInvalidDocumentIncluded_2207) {

    GList *fields = nullptr;

    fields = g_list_append(fields, const_cast<gchar*>("field1"));

    fields = g_list_append(fields, const_cast<gchar*>("field2"));



    PopplerDocument* invalid_document = nullptr;



    poppler_document_reset_form(invalid_document, fields, FALSE);



    // Verify that the function completes without errors and check any observable behavior

    EXPECT_EQ(g_list_length(fields), 2);

    g_list_free_full(fields, g_free);

}
