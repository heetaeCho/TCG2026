#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



// Mocking Catalog class to control its behavior for testing.

class MockCatalog : public Catalog {

public:

    using Catalog::Catalog;

    MOCK_METHOD(bool, isOk, (), (const, override));

    MOCK_METHOD(PageMode, getPageMode, (), (override));

};



// Mocking PDFDoc class as it's required by Catalog constructor.

class MockPDFDoc {

};



// Test fixture for PopplerDocument tests.

class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Creating a mock document and catalog for testing.

        pdf_doc = std::make_unique<MockPDFDoc>();

        mock_catalog = std::make_unique<MockCatalog>(pdf_doc.get());

        

        // Creating the PopplerDocument instance with the mocked Catalog.

        document.doc = mock_catalog.get();

    }



    void TearDown() override {

        document.doc = nullptr;

    }



    _PopplerDocument document;

    std::unique_ptr<MockPDFDoc> pdf_doc;

    std::unique_ptr<MockCatalog> mock_catalog;

};



// Test: Normal operation - Catalog is OK and returns a valid PageMode.

TEST_F(PopplerDocumentTest_2196, GetPageMode_NormalOperation_ReturnsValidPageMode_2196) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_catalog, getPageMode()).WillOnce(::testing::Return(POPPLER_PAGE_MODE_USE_OUTLINES));



    PopplerPageMode mode = poppler_document_get_page_mode(&document);

    EXPECT_EQ(mode, POPPLER_PAGE_MODE_USE_OUTLINES);

}



// Test: Catalog is not OK - should return POPPLER_PAGE_MODE_UNSET.

TEST_F(PopplerDocumentTest_2196, GetPageMode_CatalogNotOK_ReturnsUnset_2196) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(::testing::Return(false));



    PopplerPageMode mode = poppler_document_get_page_mode(&document);

    EXPECT_EQ(mode, POPPLER_PAGE_MODE_UNSET);

}



// Test: Document is null - should return POPPLER_PAGE_MODE_UNSET.

TEST_F(PopplerDocumentTest_2196, GetPageMode_NullDocument_ReturnsUnset_2196) {

    PopplerDocument *null_document = nullptr;



    PopplerPageMode mode = poppler_document_get_page_mode(null_document);

    EXPECT_EQ(mode, POPPLER_PAGE_MODE_UNSET);

}



// Test: Boundary condition - Catalog returns minimum valid PageMode.

TEST_F(PopplerDocumentTest_2196, GetPageMode_MinimumValidPageMode_ReturnsCorrectValue_2196) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_catalog, getPageMode()).WillOnce(::testing::Return(POPPLER_PAGE_MODE_NONE));



    PopplerPageMode mode = poppler_document_get_page_mode(&document);

    EXPECT_EQ(mode, POPPLER_PAGE_MODE_NONE);

}



// Test: Boundary condition - Catalog returns maximum valid PageMode.

TEST_F(PopplerDocumentTest_2196, GetPageMode_MaximumValidPageMode_ReturnsCorrectValue_2196) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_catalog, getPageMode()).WillOnce(::testing::Return(POPPLER_PAGE_MODE_USE_ATTACHMENTS));



    PopplerPageMode mode = poppler_document_get_page_mode(&document);

    EXPECT_EQ(mode, POPPLER_PAGE_MODE_USE_ATTACHMENTS);

}
