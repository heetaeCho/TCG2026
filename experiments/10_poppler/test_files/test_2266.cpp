#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <glib-object.h>

#include "poppler-document.cc"



using ::testing::NotNull;

using ::testing::IsNull;

using ::testing::Eq;



class PopplerDocumentTest_2266 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_object_new(G_TYPE_OBJECT, nullptr));

        result = g_task_new(document, nullptr, nullptr, nullptr);

    }



    void TearDown() override {

        g_clear_object(&document);

        g_object_unref(result);

    }



    PopplerDocument* document;

    GAsyncResult* result;

};



TEST_F(PopplerDocumentTest_2266, NormalOperation_Success_2266) {

    GError *error = nullptr;

    g_task_return_boolean(G_TASK(result), TRUE);

    EXPECT_TRUE(poppler_document_sign_finish(document, result, &error));

    EXPECT_THAT(error, IsNull());

}



TEST_F(PopplerDocumentTest_2266, NormalOperation_Failure_2266) {

    GError *error = nullptr;

    g_task_return_boolean(G_TASK(result), FALSE);

    EXPECT_FALSE(poppler_document_sign_finish(document, result, &error));

    EXPECT_THAT(error, IsNull());

}



TEST_F(PopplerDocumentTest_2266, InvalidResult_2266) {

    GError *error = nullptr;

    EXPECT_FALSE(poppler_document_sign_finish(document, nullptr, &error));

    EXPECT_NE(error, nullptr);

    g_clear_error(&error);

}



TEST_F(PopplerDocumentTest_2266, InvalidDocument_2266) {

    GError *error = nullptr;

    EXPECT_FALSE(poppler_document_sign_finish(nullptr, result, &error));

    EXPECT_NE(error, nullptr);

    g_clear_error(&error);

}



TEST_F(PopplerDocumentTest_2266, ErrorPropagation_2266) {

    GError *expected_error = g_error_new(G_IO_ERROR, G_IO_ERROR_FAILED, "Operation failed");

    g_task_return_error(G_TASK(result), expected_error);



    GError *actual_error = nullptr;

    EXPECT_FALSE(poppler_document_sign_finish(document, result, &actual_error));

    EXPECT_NE(actual_error, nullptr);

    EXPECT_EQ(actual_error->domain, expected_error->domain);

    EXPECT_EQ(actual_error->code, expected_error->code);

    EXPECT_STREQ(actual_error->message, expected_error->message);



    g_clear_error(&expected_error);

    g_clear_error(&actual_error);

}
