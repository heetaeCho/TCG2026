#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "Catalog.h"

#include "ViewerPreferences.h"



using namespace testing;



class PopplerDocumentTest : public ::testing::Test {

protected:

    struct _PopplerDocument docStruct;

    PopplerDocument* document;

    Catalog* catalogMock;

    ViewerPreferences* viewerPrefsMock;



    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(&docStruct);

        catalogMock = new NiceMock<Catalog>(nullptr);

        viewerPrefsMock = new NiceMock<ViewerPreferences>(Dict());

        ON_CALL(*catalogMock, isOk()).WillByDefault(Return(true));

        ON_CALL(*catalogMock, getViewerPreferences()).WillByDefault(Return(viewerPrefsMock));

    }



    void TearDown() override {

        delete catalogMock;

        delete viewerPrefsMock;

    }

};



TEST_F(PopplerDocumentTest_NormalOperation_2198, GetPrintDuplexNone_2198) {

    EXPECT_CALL(*viewerPrefsMock, getDuplex()).WillOnce(Return(ViewerPreferences::duplexNone));

    document->doc = catalogMock;

    EXPECT_EQ(poppler_document_get_print_duplex(document), POPPLER_PRINT_DUPLEX_NONE);

}



TEST_F(PopplerDocumentTest_NormalOperation_2198, GetPrintDuplexSimplex_2198) {

    EXPECT_CALL(*viewerPrefsMock, getDuplex()).WillOnce(Return(ViewerPreferences::duplexSimplex));

    document->doc = catalogMock;

    EXPECT_EQ(poppler_document_get_print_duplex(document), POPPLER_PRINT_DUPLEX_SIMPLEX);

}



TEST_F(PopplerDocumentTest_NormalOperation_2198, GetPrintDuplexFlipShortEdge_2198) {

    EXPECT_CALL(*viewerPrefsMock, getDuplex()).WillOnce(Return(ViewerPreferences::duplexDuplexFlipShortEdge));

    document->doc = catalogMock;

    EXPECT_EQ(poppler_document_get_print_duplex(document), POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_SHORT_EDGE);

}



TEST_F(PopplerDocumentTest_NormalOperation_2198, GetPrintDuplexFlipLongEdge_2198) {

    EXPECT_CALL(*viewerPrefsMock, getDuplex()).WillOnce(Return(ViewerPreferences::duplexDuplexFlipLongEdge));

    document->doc = catalogMock;

    EXPECT_EQ(poppler_document_get_print_duplex(document), POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_LONG_EDGE);

}



TEST_F(PopplerDocumentTest_BoundaryConditions_2198, CatalogNotOk_2198) {

    EXPECT_CALL(*catalogMock, isOk()).WillOnce(Return(false));

    document->doc = catalogMock;

    EXPECT_EQ(poppler_document_get_print_duplex(document), POPPLER_PRINT_DUPLEX_NONE);

}



TEST_F(PopplerDocumentTest_BoundaryConditions_2198, NullCatalog_2198) {

    document->doc = nullptr;

    EXPECT_EQ(poppler_document_get_print_duplex(document), POPPLER_PRINT_DUPLEX_NONE);

}



TEST_F(PopplerDocumentTest_ExceptionalCases_2198, ViewerPreferencesNull_2198) {

    ON_CALL(*catalogMock, getViewerPreferences()).WillByDefault(Return(nullptr));

    document->doc = catalogMock;

    EXPECT_EQ(poppler_document_get_print_duplex(document), POPPLER_PRINT_DUPLEX_NONE);

}
