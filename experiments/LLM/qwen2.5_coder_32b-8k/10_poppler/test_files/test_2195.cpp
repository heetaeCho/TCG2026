#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using ::testing::Return;



class MockCatalog : public Catalog {

public:

    MOCK_METHOD(bool, isOk, (), (const override));

    MOCK_METHOD(PageLayout, getPageLayout, (), (override));

};



class PopplerDocumentTest_2195 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        mock_catalog = std::make_unique<MockCatalog>();

        document->doc = mock_catalog.get();

    }



    void TearDown() override {

        delete document;

    }



    PopplerDocument* document;

    std::unique_ptr<MockCatalog> mock_catalog;

};



TEST_F(PopplerDocumentTest_2195, ValidDocumentReturnsPageLayout_2195) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, getPageLayout()).WillOnce(Return(PageLayout::SINGLE_PAGE));



    PopplerPageLayout layout = poppler_document_get_page_layout(document);

    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_SINGLE_PAGE);

}



TEST_F(PopplerDocumentTest_2195, InvalidDocumentReturnsUnset_2195) {

    document->doc = nullptr;



    PopplerPageLayout layout = poppler_document_get_page_layout(document);

    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_UNSET);

}



TEST_F(PopplerDocumentTest_2195, CatalogNotOkReturnsUnset_2195) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(false));



    PopplerPageLayout layout = poppler_document_get_page_layout(document);

    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_UNSET);

}



TEST_F(PopplerDocumentTest_2195, CatalogReturnsOneColumn_2195) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, getPageLayout()).WillOnce(Return(PageLayout::ONE_COLUMN));



    PopplerPageLayout layout = poppler_document_get_page_layout(document);

    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_ONE_COLUMN);

}



TEST_F(PopplerDocumentTest_2195, CatalogReturnsTwoColumnLeft_2195) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, getPageLayout()).WillOnce(Return(PageLayout::TWO_COLUMN_LEFT));



    PopplerPageLayout layout = poppler_document_get_page_layout(document);

    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT);

}



TEST_F(PopplerDocumentTest_2195, CatalogReturnsTwoColumnRight_2195) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, getPageLayout()).WillOnce(Return(PageLayout::TWO_COLUMN_RIGHT));



    PopplerPageLayout layout = poppler_document_get_page_layout(document);

    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT);

}



TEST_F(PopplerDocumentTest_2195, CatalogReturnsTwoPageLeft_2195) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, getPageLayout()).WillOnce(Return(PageLayout::TWO_PAGE_LEFT));



    PopplerPageLayout layout = poppler_document_get_page_layout(document);

    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT);

}



TEST_F(PopplerDocumentTest_2195, CatalogReturnsTwoPageRight_2195) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, getPageLayout()).WillOnce(Return(PageLayout::TWO_PAGE_RIGHT));



    PopplerPageLayout layout = poppler_document_get_page_layout(document);

    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);

}
