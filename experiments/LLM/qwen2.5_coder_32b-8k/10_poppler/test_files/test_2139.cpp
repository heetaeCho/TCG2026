#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include <glib.h>



class PopplerDocumentTest_2139 : public ::testing::Test {

protected:

    GError *error = nullptr;

};



TEST_F(PopplerDocumentTest_2139, CreateDocumentFromValidFileUri_2139) {

    const char *valid_uri = "file:///path/to/valid/document.pdf";

    PopplerDocument *doc = poppler_document_new_from_file(valid_uri, nullptr, &error);

    ASSERT_NE(doc, nullptr);

    g_object_unref(doc);

}



TEST_F(PopplerDocumentTest_2139, CreateDocumentFromInvalidFileUri_2139) {

    const char *invalid_uri = "file:///nonexistent/document.pdf";

    PopplerDocument *doc = poppler_document_new_from_file(invalid_uri, nullptr, &error);

    ASSERT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

}



TEST_F(PopplerDocumentTest_2139, CreateEncryptedDocumentWithCorrectPassword_2139) {

    const char *uri = "file:///path/to/encrypted/document.pdf";

    const char *password = "correct_password";

    PopplerDocument *doc = poppler_document_new_from_file(uri, password, &error);

    ASSERT_NE(doc, nullptr);

    g_object_unref(doc);

}



TEST_F(PopplerDocumentTest_2139, CreateEncryptedDocumentWithIncorrectPassword_2139) {

    const char *uri = "file:///path/to/encrypted/document.pdf";

    const char *password = "incorrect_password";

    PopplerDocument *doc = poppler_document_new_from_file(uri, password, &error);

    ASSERT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

}



TEST_F(PopplerDocumentTest_2139, CreateDocumentWithNullUri_2139) {

    const char *uri = nullptr;

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);

    ASSERT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

}



TEST_F(PopplerDocumentTest_2139, CreateDocumentWithNullPassword_2139) {

    const char *uri = "file:///path/to/document.pdf";

    const char *password = nullptr;

    PopplerDocument *doc = poppler_document_new_from_file(uri, password, &error);

    ASSERT_NE(doc, nullptr);

    g_object_unref(doc);

}



TEST_F(PopplerDocumentTest_2139, CreateDocumentWithEmptyUri_2139) {

    const char *uri = "";

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);

    ASSERT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

}



TEST_F(PopplerDocumentTest_2139, CreateDocumentWithEmptyPassword_2139) {

    const char *uri = "file:///path/to/encrypted/document.pdf";

    const char *password = "";

    PopplerDocument *doc = poppler_document_new_from_file(uri, password, &error);

    ASSERT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

}
