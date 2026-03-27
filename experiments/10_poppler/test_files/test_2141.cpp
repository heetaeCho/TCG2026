#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-document.h>

#include <glib-object.h>



namespace {



class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        error = nullptr;

    }



    GBytes* createSampleGBytes(const std::string& data) {

        return g_bytes_new(data.c_str(), data.size());

    }



    GError *error;

};



TEST_F(PopplerDocumentTest_2141, CreateFromValidBytes_2141) {

    auto bytes = createSampleGBytes("%PDF-1.7\n");

    auto doc = poppler_document_new_from_bytes(bytes, nullptr, &error);

    EXPECT_NE(doc, nullptr);

    g_object_unref(doc);

    g_bytes_unref(bytes);

}



TEST_F(PopplerDocumentTest_2141, CreateFromNullBytes_2141) {

    auto doc = poppler_document_new_from_bytes(nullptr, nullptr, &error);

    EXPECT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

}



TEST_F(PopplerDocumentTest_2141, CreateWithNonEmptyPassword_2141) {

    auto bytes = createSampleGBytes("%PDF-1.7\n");

    const char* password = "secret";

    auto doc = poppler_document_new_from_bytes(bytes, password, &error);

    EXPECT_NE(doc, nullptr); // Assuming the document is not encrypted or password is correct

    g_object_unref(doc);

    g_bytes_unref(bytes);

}



TEST_F(PopplerDocumentTest_2141, CreateWithNullPassword_2141) {

    auto bytes = createSampleGBytes("%PDF-1.7\n");

    auto doc = poppler_document_new_from_bytes(bytes, nullptr, &error);

    EXPECT_NE(doc, nullptr); // Assuming the document is not encrypted

    g_object_unref(doc);

    g_bytes_unref(bytes);

}



TEST_F(PopplerDocumentTest_2141, CreateWithInvalidBytes_2141) {

    auto bytes = createSampleGBytes("This is not a PDF file.");

    auto doc = poppler_document_new_from_bytes(bytes, nullptr, &error);

    EXPECT_EQ(doc, nullptr);

    EXPECT_NE(error, nullptr);

    g_error_free(error);

    g_bytes_unref(bytes);

}



TEST_F(PopplerDocumentTest_2141, CreateWithNonLatin1Password_2141) {

    auto bytes = createSampleGBytes("%PDF-1.7\n");

    const char* password = "café"; // Non-Latin1 character

    auto doc = poppler_document_new_from_bytes(bytes, password, &error);

    EXPECT_NE(doc, nullptr); // Assuming the document is not encrypted or password handling works correctly

    g_object_unref(doc);

    g_bytes_unref(bytes);

}



TEST_F(PopplerDocumentTest_2141, CreateWithErrorAlreadySet_2141) {

    auto bytes = createSampleGBytes("%PDF-1.7\n");

    error = g_error_new(G_MARKUP_ERROR, G_MARKUP_ERROR_INVALID_CONTENT, "Error already set");

    auto doc = poppler_document_new_from_bytes(bytes, nullptr, &error);

    EXPECT_EQ(doc, nullptr);

    g_bytes_unref(bytes);

}



} // namespace
