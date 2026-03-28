#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



// Mock class for CairoOutputDev to mock external interactions if needed

class MockCairoOutputDev {

public:

    MOCK_METHOD(void, someMethod, (), ());

};



// Test fixture for PopplerDocument tests

class PopplerDocumentTest_2175 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        document->doc = new _PopplerDocument();

        document->doc->output_dev = new MockCairoOutputDev();

    }



    void TearDown() override {

        delete document->doc->output_dev;

        delete document->doc;

        g_free(document);

    }



    PopplerDocument* document;

};



// Test normal operation with valid author

TEST_F(PopplerDocumentTest_2175, SetAuthor_NormalOperation_2175) {

    const gchar* author = "John Doe";

    poppler_document_set_author(document, author);

    // Since the implementation is a black box, we can only verify that no crash occurs.

}



// Test boundary condition with empty author

TEST_F(PopplerDocumentTest_2175, SetAuthor_EmptyString_2175) {

    const gchar* author = "";

    poppler_document_set_author(document, author);

    // Verify that setting an empty string does not cause a crash.

}



// Test boundary condition with nullptr author

TEST_F(PopplerDocumentTest_2175, SetAuthor_Nullptr_2175) {

    const gchar* author = nullptr;

    poppler_document_set_author(document, author);

    // Verify that setting nullptr does not cause a crash.

}



// Test exceptional case where _poppler_goo_string_from_utf8 fails

TEST_F(PopplerDocumentTest_2175, SetAuthor_UTF8ConversionFailure_2175) {

    const gchar* invalid_utf8 = "\xC3\x28"; // Invalid UTF-8 sequence

    poppler_document_set_author(document, invalid_utf8);

    // Verify that an invalid UTF-8 string does not cause a crash.

}
