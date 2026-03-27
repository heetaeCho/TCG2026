#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "Catalog.h"



using namespace testing;



// Mock class for Catalog to simulate its behavior

class MockCatalog : public Catalog {

public:

    MOCK_METHOD(bool, isOk, (), (const, override));

    MOCK_METHOD(std::unique_ptr<GooString>, readMetadata, (), (override));

};



// Fixture for PopplerDocument tests

class PopplerDocumentTest_2206 : public Test {

protected:

    MockCatalog* mock_catalog;

    PopplerDocument document;



    void SetUp() override {

        // Initialize the PDFDoc pointer and Catalog mock

        document.doc = new PDFDoc();

        mock_catalog = new MockCatalog(document.doc);

        document.doc->setCatalog(mock_catalog);

    }



    void TearDown() override {

        // Clean up allocated resources

        delete document.doc;

        delete mock_catalog;

    }

};



// Test case: Normal operation - metadata is available

TEST_F(PopplerDocumentTest_2206, GetMetadata_NormalOperation_2206) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    auto metadata = std::make_unique<GooString>("Sample Metadata");

    EXPECT_CALL(*mock_catalog, readMetadata()).WillOnce(Return(ByMove(std::move(metadata))));



    gchar* result = poppler_document_get_metadata(&document);

    ASSERT_STREQ(result, "Sample Metadata");

    g_free(result); // Free the allocated memory

}



// Test case: Catalog is not OK - metadata should be nullptr

TEST_F(PopplerDocumentTest_2206, GetMetadata_CatalogNotOK_2206) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(false));



    gchar* result = poppler_document_get_metadata(&document);

    ASSERT_EQ(result, nullptr);

}



// Test case: Metadata not available - metadata should be nullptr

TEST_F(PopplerDocumentTest_2206, GetMetadata_NoMetadataAvailable_2206) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, readMetadata()).WillOnce(Return(ByMove(nullptr)));



    gchar* result = poppler_document_get_metadata(&document);

    ASSERT_EQ(result, nullptr);

}



// Test case: Boundary condition - document is nullptr

TEST_F(PopplerDocumentTest_2206, GetMetadata_NullDocument_2206) {

    PopplerDocument* null_document = nullptr;



    gchar* result = poppler_document_get_metadata(null_document);

    ASSERT_EQ(result, nullptr);

}
