#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <gio/gio.h>

#include <poppler-document.cc>



using namespace testing;



class PopplerDocumentTest : public Test {

protected:

    void SetUp() override {

        stream = GMemoryInputStream::new_from_data("", 0, nullptr);

        cancellable = g_cancellable_new();

        error = nullptr;

    }



    void TearDown() override {

        if (stream) {

            g_object_unref(stream);

        }

        if (cancellable) {

            g_object_unref(cancellable);

        }

        if (error) {

            g_error_free(error);

        }

    }



    GInputStream* stream;

    GCancellable* cancellable;

    GError** error;

};



TEST_F(PopplerDocumentTest_2142, NewFromStreamNullPointer_2142) {

    PopplerDocument* doc = poppler_document_new_from_stream(nullptr, 0, nullptr, cancellable, &error);

    EXPECT_EQ(doc, nullptr);

}



TEST_F(PopplerDocumentTest_2142, NewFromStreamInvalidLength_2142) {

    gsize data_length = 0;

    const char* data = "some data";

    stream = GMemoryInputStream::new_from_data(data, data_length, nullptr);



    PopplerDocument* doc = poppler_document_new_from_stream(stream, -5, nullptr, cancellable, &error);

    EXPECT_EQ(doc, nullptr);

}



TEST_F(PopplerDocumentTest_2142, NewFromStreamNonSeekableStream_2142) {

    GInputStream* non_seekable_stream = g_memory_input_stream_new();

    PopplerDocument* doc = poppler_document_new_from_stream(non_seekable_stream, -1, nullptr, cancellable, &error);

    EXPECT_EQ(doc, nullptr);

    EXPECT_TRUE(g_error_matches(error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED));

    g_object_unref(non_seekable_stream);

}



TEST_F(PopplerDocumentTest_2142, NewFromStreamEmptyMemoryBuffer_2142) {

    const char* data = "";

    stream = GMemoryInputStream::new_from_data(data, 0, nullptr);



    PopplerDocument* doc = poppler_document_new_from_stream(stream, -1, nullptr, cancellable, &error);

    EXPECT_EQ(doc, nullptr); // Assuming an empty file is not a valid PDF

}



TEST_F(PopplerDocumentTest_2142, NewFromStreamValidPDF_2142) {

    const char* data = "%PDF-1.5\n";

    stream = GMemoryInputStream::new_from_data(data, strlen(data), nullptr);



    PopplerDocument* doc = poppler_document_new_from_stream(stream, -1, nullptr, cancellable, &error);

    EXPECT_NE(doc, nullptr);

    if (doc) {

        poppler_document_free(doc);

    }

}



TEST_F(PopplerDocumentTest_2142, NewFromStreamEncryptedPDFNoPassword_2142) {

    const char* data = "%PDF-1.5\n%Encrypt\n";

    stream = GMemoryInputStream::new_from_data(data, strlen(data), nullptr);



    PopplerDocument* doc = poppler_document_new_from_stream(stream, -1, nullptr, cancellable, &error);

    EXPECT_EQ(doc, nullptr); // Assuming an encrypted PDF without a password cannot be opened

}



TEST_F(PopplerDocumentTest_2142, NewFromStreamEncryptedPDFWithPassword_2142) {

    const char* data = "%PDF-1.5\n%Encrypt\n";

    stream = GMemoryInputStream::new_from_data(data, strlen(data), nullptr);



    PopplerDocument* doc = poppler_document_new_from_stream(stream, -1, "password", cancellable, &error);

    EXPECT_EQ(doc, nullptr); // Assuming an encrypted PDF with the wrong password cannot be opened

}
