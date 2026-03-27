#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "Catalog.h"



using namespace testing;



class MockPopplerDocument {

public:

    MOCK_METHOD(Catalog*, getCatalog, (), (const));

};



class MockCatalog {

public:

    MOCK_METHOD(bool, isOk, (), (const));

    MOCK_METHOD(ViewerPreferences*, getViewerPreferences, (), (const));

};



class MockViewerPreferences {

public:

    MOCK_METHOD(ViewerPreferences::PrintScaling, getPrintScaling, (), (const));

};



class PopplerDocumentTest : public Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        catalogMock = std::make_unique<StrictMock<MockCatalog>>();

        viewerPrefsMock = std::make_unique<StrictMock<MockViewerPreferences>>();



        ON_CALL(mockPopplerDocument, getCatalog())

            .WillByDefault(Return(catalogMock.get()));

        ON_CALL(*catalogMock, isOk())

            .WillByDefault(Return(true));

        ON_CALL(*catalogMock, getViewerPreferences())

            .WillByDefault(Return(viewerPrefsMock.get()));

    }



    void TearDown() override {

        delete document;

    }



    PopplerDocument* document;

    std::unique_ptr<StrictMock<MockCatalog>> catalogMock;

    std::unique_ptr<StrictMock<MockViewerPreferences>> viewerPrefsMock;

    NiceMock<MockPopplerDocument> mockPopplerDocument;

};



TEST_F(PopplerDocumentTest_2197, GetPrintScaling_ReturnsAppDefaultWhenCatalogIsNull_2197) {

    EXPECT_CALL(mockPopplerDocument, getCatalog())

        .WillOnce(Return(nullptr));



    EXPECT_EQ(poppler_document_get_print_scaling(document), POPPLER_PRINT_SCALING_APP_DEFAULT);

}



TEST_F(PopplerDocumentTest_2197, GetPrintScaling_ReturnsAppDefaultWhenCatalogIsNotOk_2197) {

    EXPECT_CALL(*catalogMock, isOk())

        .WillOnce(Return(false));



    EXPECT_EQ(poppler_document_get_print_scaling(document), POPPLER_PRINT_SCALING_APP_DEFAULT);

}



TEST_F(PopplerDocumentTest_2197, GetPrintScaling_ReturnsAppDefaultWhenViewerPreferencesIsNull_2197) {

    EXPECT_CALL(*catalogMock, getViewerPreferences())

        .WillOnce(Return(nullptr));



    EXPECT_EQ(poppler_document_get_print_scaling(document), POPPLER_PRINT_SCALING_APP_DEFAULT);

}



TEST_F(PopplerDocumentTest_2197, GetPrintScaling_ReturnsAppDefaultWhenPrintScalingIsAppDefault_2197) {

    EXPECT_CALL(*viewerPrefsMock, getPrintScaling())

        .WillOnce(Return(ViewerPreferences::printScalingAppDefault));



    EXPECT_EQ(poppler_document_get_print_scaling(document), POPPLER_PRINT_SCALING_APP_DEFAULT);

}



TEST_F(PopplerDocumentTest_2197, GetPrintScaling_ReturnsNoneWhenPrintScalingIsNone_2197) {

    EXPECT_CALL(*viewerPrefsMock, getPrintScaling())

        .WillOnce(Return(ViewerPreferences::printScalingNone));



    EXPECT_EQ(poppler_document_get_print_scaling(document), POPPLER_PRINT_SCALING_NONE);

}
