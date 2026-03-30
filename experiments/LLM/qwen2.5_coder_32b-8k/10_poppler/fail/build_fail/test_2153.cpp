#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "Catalog.h"



using namespace testing;



class PopplerDocumentTest : public ::testing::Test {

protected:

    MockPopplerDocument* mock_document;

    Catalog* mock_catalog;



    class MockPopplerDocument : public PopplerDocument {

    public:

        MOCK_METHOD(PDFDoc*, getDoc, (), (const));

    };



    class MockCatalog : public Catalog {

    public:

        using Catalog::Catalog; // Inherit constructor

        MOCK_METHOD(bool, labelToIndex, (const GooString&, int*), (override));

    };



    void SetUp() override {

        mock_document = new NiceMock<MockPopplerDocument>();

        mock_catalog = new NiceMock<MockCatalog>(nullptr);

        

        ON_CALL(*mock_document, getDoc()).WillByDefault(Return(mock_catalog->doc));

    }



    void TearDown() override {

        delete mock_document;

        delete mock_catalog;

    }

};



TEST_F(PopplerDocumentTest_2153, ValidLabelReturnsPage_2153) {

    int index = 0;

    EXPECT_CALL(*mock_catalog, labelToIndex(_, _))

        .WillOnce(DoAll(SetArgReferee<1>(index), Return(true)));



    PopplerPage* page = poppler_document_get_page_by_label(mock_document, "label");

    ASSERT_NE(page, nullptr);

}



TEST_F(PopplerDocumentTest_2153, InvalidLabelReturnsNull_2153) {

    EXPECT_CALL(*mock_catalog, labelToIndex(_, _))

        .WillOnce(Return(false));



    PopplerPage* page = poppler_document_get_page_by_label(mock_document, "invalid");

    ASSERT_EQ(page, nullptr);

}



TEST_F(PopplerDocumentTest_2153, EmptyLabelReturnsNull_2153) {

    EXPECT_CALL(*mock_catalog, labelToIndex(_, _))

        .WillOnce(Return(false));



    PopplerPage* page = poppler_document_get_page_by_label(mock_document, "");

    ASSERT_EQ(page, nullptr);

}



TEST_F(PopplerDocumentTest_2153, NullLabelReturnsNull_2153) {

    EXPECT_CALL(*mock_catalog, labelToIndex(_, _))

        .Times(0); // Should not be called if label is null



    PopplerPage* page = poppler_document_get_page_by_label(mock_document, nullptr);

    ASSERT_EQ(page, nullptr);

}



TEST_F(PopplerDocumentTest_2153, LargeLabelReturnsNullIfNotFound_2153) {

    EXPECT_CALL(*mock_catalog, labelToIndex(_, _))

        .WillOnce(Return(false));



    PopplerPage* page = poppler_document_get_page_by_label(mock_document, "aVeryLargeAndUnlikelyLabelThatWouldNotBeUsedInRealScenarios");

    ASSERT_EQ(page, nullptr);

}
