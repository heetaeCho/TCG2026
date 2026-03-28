#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



// Mock GError for error handling verification

class MockGError {

public:

    MOCK_METHOD1(set_error, void(const std::string& message));

};



// Test fixture for PopplerDocument tests

class PopplerDocumentTest_2146 : public ::testing::Test {

protected:

    PopplerDocument *document;

    GError **error;



    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        error = nullptr;  // Assuming no error handling in tests for now

    }



    void TearDown() override {

        g_free(document);

    }

};



// Test normal operation of poppler_document_save

TEST_F(PopplerDocumentTest_2146, SaveNormalOperation_2146) {

    const char* uri = "file:///path/to/document.pdf";

    EXPECT_TRUE(poppler_document_save(document, uri, error));

}



// Test boundary condition with an empty URI

TEST_F(PopplerDocumentTest_2146, SaveEmptyUri_2146) {

    const char* uri = "";

    EXPECT_FALSE(poppler_document_save(document, uri, error));

}



// Test boundary condition with a null URI

TEST_F(PopplerDocumentTest_2146, SaveNullUri_2146) {

    const char* uri = nullptr;

    EXPECT_FALSE(poppler_document_save(document, uri, error));

}



// Test exceptional case where g_filename_from_uri fails

TEST_F(PopplerDocumentTest_2146, SaveInvalidUri_2146) {

    const char* uri = "invalid://uri";

    EXPECT_FALSE(poppler_document_save(document, uri, error));

}



// Test normal operation with an error handler (mocked)

TEST_F(PopplerDocumentTest_2146, SaveWithErrorHandler_2146) {

    MockGError mock_error;

    GError* local_error = nullptr;

    error = &local_error;



    // Assuming the document save fails and sets an error

    EXPECT_CALL(mock_error, set_error(::testing::_)).Times(1);

    EXPECT_FALSE(poppler_document_save(document, "file:///path/to/document.pdf", error));



    g_clear_error(error);

}



// Test boundary condition with a relative path URI

TEST_F(PopplerDocumentTest_2146, SaveRelativePathUri_2146) {

    const char* uri = "relative/path/document.pdf";

    EXPECT_TRUE(poppler_document_save(document, uri, error));

}
