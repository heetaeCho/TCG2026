#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include <glib.h>



// Mock GError structure for testing purposes

class MockGError : public GError {

public:

    MOCK_METHOD(void, reset, (), (override));

};



TEST(poppler_document_new_from_data_2140, ValidDataNoPassword_2140) {

    char data[] = "Sample PDF data";

    int length = sizeof(data) - 1;

    const char* password = nullptr;

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_NE(doc, nullptr);

    EXPECT_EQ(error, nullptr);



    g_object_unref(doc);

}



TEST(poppler_document_new_from_data_2140, ValidDataWithPassword_2140) {

    char data[] = "Sample PDF data";

    int length = sizeof(data) - 1;

    const char* password = "secret";

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_NE(doc, nullptr);

    EXPECT_EQ(error, nullptr);



    g_object_unref(doc);

}



TEST(poppler_document_new_from_data_2140, InvalidDataNoPassword_2140) {

    char data[] = "Invalid PDF data";

    int length = sizeof(data) - 1;

    const char* password = nullptr;

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);



    g_error_free(error);

}



TEST(poppler_document_new_from_data_2140, InvalidDataWithPassword_2140) {

    char data[] = "Invalid PDF data";

    int length = sizeof(data) - 1;

    const char* password = "secret";

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);



    g_error_free(error);

}



TEST(poppler_document_new_from_data_2140, EncryptedDataCorrectPassword_2140) {

    char data[] = "Encrypted PDF data";

    int length = sizeof(data) - 1;

    const char* password = "correct_password";

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_NE(doc, nullptr);

    EXPECT_EQ(error, nullptr);



    g_object_unref(doc);

}



TEST(poppler_document_new_from_data_2140, EncryptedDataIncorrectPassword_2140) {

    char data[] = "Encrypted PDF data";

    int length = sizeof(data) - 1;

    const char* password = "wrong_password";

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);



    g_error_free(error);

}



TEST(poppler_document_new_from_data_2140, NullDataPointer_2140) {

    char* data = nullptr;

    int length = 0;

    const char* password = nullptr;

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);



    g_error_free(error);

}



TEST(poppler_document_new_from_data_2140, ZeroLengthData_2140) {

    char data[] = "";

    int length = 0;

    const char* password = nullptr;

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);



    g_error_free(error);

}



TEST(poppler_document_new_from_data_2140, NullPasswordPointer_2140) {

    char data[] = "Sample PDF data";

    int length = sizeof(data) - 1;

    const char* password = nullptr;

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_NE(doc, nullptr);

    EXPECT_EQ(error, nullptr);



    g_object_unref(doc);

}



TEST(poppler_document_new_from_data_2140, EmptyPasswordString_2140) {

    char data[] = "Sample PDF data";

    int length = sizeof(data) - 1;

    const char* password = "";

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_NE(doc, nullptr);

    EXPECT_EQ(error, nullptr);



    g_object_unref(doc);

}



TEST(poppler_document_new_from_data_2140, ErrorHandling_2140) {

    char data[] = "Invalid PDF data";

    int length = sizeof(data) - 1;

    const char* password = nullptr;

    GError *error = nullptr;



    PopplerDocument *doc = poppler_document_new_from_data(data, length, password, &error);



    EXPECT_EQ(doc, nullptr);

    EXPECT_NE(error->message, nullptr);



    g_error_free(error);

}
