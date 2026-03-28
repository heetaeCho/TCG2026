#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include <gio/gio.h>



using ::testing::_;

using ::testing::NotNull;

using ::testing::IsNull;

using ::testing::Return;

using ::testing::SetArgPointee;



class PopplerDocumentTest_2143 : public ::testing::Test {

protected:

    void SetUp() override {

        g_type_init();

        file = G_FILE(g_file_new_for_path("dummy.pdf"));

        error = nullptr;

    }



    void TearDown() override {

        if (file) {

            g_object_unref(file);

        }

        if (error) {

            g_error_free(error);

        }

    }



    GFile* file;

    GError* error;

};



TEST_F(PopplerDocumentTest_2143, NewFromGFile_NativePath_ReturnsDocument_2143) {

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, &error);

    ASSERT_NE(doc, nullptr);

    g_object_unref(doc);

}



TEST_F(PopplerDocumentTest_2143, NewFromGFile_NativePathWithPassword_ReturnsDocument_2143) {

    PopplerDocument *doc = poppler_document_new_from_gfile(file, "secret", nullptr, &error);

    ASSERT_NE(doc, nullptr);

    g_object_unref(doc);

}



TEST_F(PopplerDocumentTest_2143, NewFromGFile_NonNativePath_ReturnsDocument_2143) {

    GFile* non_native_file = g_file_new_for_uri("file://dummy.pdf");

    PopplerDocument *doc = poppler_document_new_from_gfile(non_native_file, nullptr, nullptr, &error);

    ASSERT_NE(doc, nullptr);

    g_object_unref(non_native_file);

    g_object_unref(doc);

}



TEST_F(PopplerDocumentTest_2143, NewFromGFile_NullFile_ReturnsNull_2143) {

    PopplerDocument *doc = poppler_document_new_from_gfile(nullptr, nullptr, nullptr, &error);

    ASSERT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);

}



TEST_F(PopplerDocumentTest_2143, NewFromGFile_ReadFailure_ReturnsNull_2143) {

    GFileInputStream* mock_stream = G_FILE_INPUT_STREAM(g_file_read(file, nullptr, &error));

    g_object_unref(mock_stream); // Simulate failure by not returning a valid stream

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, &error);

    ASSERT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);

}



TEST_F(PopplerDocumentTest_2143, NewFromGFile_NativePathWithError_ReturnsNull_2143) {

    PopplerDocument *doc = poppler_document_new_from_gfile(file, "wrong_password", nullptr, &error);

    ASSERT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);

}
