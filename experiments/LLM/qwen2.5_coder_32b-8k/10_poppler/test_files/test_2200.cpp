#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "Catalog.h"



using ::testing::Return;

using ::testing::NiceMock;



class MockCatalog : public Catalog {

public:

    MOCK_METHOD(ViewerPreferences*, getViewerPreferences, (), (override));

    MOCK_METHOD(bool, isOk, (), (const override));

};



class MockViewerPreferences : public ViewerPreferences {

public:

    MOCK_METHOD(std::vector<std::pair<int, int>>, getPrintPageRange, (), (override));

};



class PopplerDocumentTest_2200 : public ::testing::Test {

protected:

    void SetUp() override {

        document = g_new0(PopplerDocument, 1);

        mock_catalog = new NiceMock<MockCatalog>(nullptr);

        mock_viewer_preferences = new NiceMock<MockViewerPreferences>();

    }



    void TearDown() override {

        g_free(document);

        delete mock_catalog;

        delete mock_viewer_preferences;

    }



    PopplerDocument *document;

    MockCatalog *mock_catalog;

    MockViewerPreferences *mock_viewer_preferences;

};



TEST_F(PopplerDocumentTest_2200, NullNRangesPointer_2200) {

    int *n_ranges = nullptr;

    EXPECT_EQ(poppler_document_get_print_page_ranges(document, n_ranges), nullptr);

}



TEST_F(PopplerDocumentTest_2200, InvalidDocumentPointer_2200) {

    int n_ranges = 0;

    EXPECT_EQ(poppler_document_get_print_page_ranges(nullptr, &n_ranges), nullptr);

}



TEST_F(PopplerDocumentTest_2200, CatalogNotOk_2200) {

    document->doc = mock_catalog;

    ON_CALL(*mock_catalog, isOk()).WillByDefault(Return(false));

    int n_ranges = 0;

    EXPECT_EQ(poppler_document_get_print_page_ranges(document, &n_ranges), nullptr);

    EXPECT_EQ(n_ranges, 0);

}



TEST_F(PopplerDocumentTest_2200, NoViewerPreferences_2200) {

    document->doc = mock_catalog;

    ON_CALL(*mock_catalog, isOk()).WillByDefault(Return(true));

    ON_CALL(*mock_catalog, getViewerPreferences()).WillByDefault(Return(nullptr));

    int n_ranges = 0;

    EXPECT_EQ(poppler_document_get_print_page_ranges(document, &n_ranges), nullptr);

    EXPECT_EQ(n_ranges, 0);

}



TEST_F(PopplerDocumentTest_2200, ValidSingleRange_2200) {

    document->doc = mock_catalog;

    ON_CALL(*mock_catalog, isOk()).WillByDefault(Return(true));

    ON_CALL(*mock_catalog, getViewerPreferences()).WillByDefault(Return(mock_viewer_preferences));



    std::vector<std::pair<int, int>> ranges = {{1, 2}};

    ON_CALL(*mock_viewer_preferences, getPrintPageRange()).WillByDefault(Return(ranges));



    int n_ranges = 0;

    PopplerPageRange *result = poppler_document_get_print_page_ranges(document, &n_ranges);

    EXPECT_EQ(n_ranges, 1);

    EXPECT_EQ(result[0].start_page, 1);

    EXPECT_EQ(result[0].end_page, 2);



    g_free(result);

}



TEST_F(PopplerDocumentTest_2200, ValidMultipleRanges_2200) {

    document->doc = mock_catalog;

    ON_CALL(*mock_catalog, isOk()).WillByDefault(Return(true));

    ON_CALL(*mock_catalog, getViewerPreferences()).WillByDefault(Return(mock_viewer_preferences));



    std::vector<std::pair<int, int>> ranges = {{1, 2}, {4, 5}};

    ON_CALL(*mock_viewer_preferences, getPrintPageRange()).WillByDefault(Return(ranges));



    int n_ranges = 0;

    PopplerPageRange *result = poppler_document_get_print_page_ranges(document, &n_ranges);

    EXPECT_EQ(n_ranges, 2);

    EXPECT_EQ(result[0].start_page, 1);

    EXPECT_EQ(result[0].end_page, 2);

    EXPECT_EQ(result[1].start_page, 4);

    EXPECT_EQ(result[1].end_page, 5);



    g_free(result);

}



TEST_F(PopplerDocumentTest_2200, NoPageRanges_2200) {

    document->doc = mock_catalog;

    ON_CALL(*mock_catalog, isOk()).WillByDefault(Return(true));

    ON_CALL(*mock_catalog, getViewerPreferences()).WillByDefault(Return(mock_viewer_preferences));



    std::vector<std::pair<int, int>> ranges = {};

    ON_CALL(*mock_viewer_preferences, getPrintPageRange()).WillByDefault(Return(ranges));



    int n_ranges = 0;

    PopplerPageRange *result = poppler_document_get_print_page_ranges(document, &n_ranges);

    EXPECT_EQ(n_ranges, 0);

    EXPECT_EQ(result, nullptr);

}
