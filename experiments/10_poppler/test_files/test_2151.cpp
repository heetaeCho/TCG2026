#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using ::testing::Eq;

using ::testing::Return;



// Mock class for testing purposes

class MockPopplerDocument {

public:

    MOCK_METHOD(int, getNumPages, (), (const));

};



// Test fixture for PopplerDocument tests

class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        document->doc = new MockPopplerDocument();

    }



    void TearDown() override {

        delete document->doc;

        delete document;

    }



    PopplerDocument* document;

};



// Test to verify normal operation of poppler_document_get_n_pages

TEST_F(PopplerDocumentTest_2151, GetNumPages_ReturnsCorrectValue_2151) {

    EXPECT_CALL(*document->doc, getNumPages()).WillOnce(Return(5));

    int num_pages = poppler_document_get_n_pages(document);

    EXPECT_EQ(num_pages, 5);

}



// Test to verify boundary condition when the document has zero pages

TEST_F(PopplerDocumentTest_2151, GetNumPages_ReturnsZeroForEmptyDocument_2151) {

    EXPECT_CALL(*document->doc, getNumPages()).WillOnce(Return(0));

    int num_pages = poppler_document_get_n_pages(document);

    EXPECT_EQ(num_pages, 0);

}



// Test to verify behavior when document is null

TEST_F(PopplerDocumentTest_2151, GetNumPages_ReturnsZeroForNullDocument_2151) {

    int num_pages = poppler_document_get_n_pages(nullptr);

    EXPECT_EQ(num_pages, 0);

}
