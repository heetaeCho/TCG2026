#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "Catalog.h"

#include "ViewerPreferences.h"



using ::testing::NiceMock;

using ::testing::Return;



class MockCatalog : public Catalog {

public:

    MOCK_METHOD(bool, isOk, (), (const override));

    MOCK_METHOD(ViewerPreferences*, getViewerPreferences, (), (override));

};



class MockViewerPreferences : public ViewerPreferences {

public:

    MOCK_METHOD(int, getNumCopies, (), (const override));

};



class PopplerDocumentTest_2199 : public ::testing::Test {

protected:

    void SetUp() override {

        catalogMock = new NiceMock<MockCatalog>(nullptr);

        viewerPreferencesMock = new NiceMock<MockViewerPreferences>();

        document.doc = catalogMock;

    }



    void TearDown() override {

        delete catalogMock;

        delete viewerPreferencesMock;

    }



    PopplerDocument document;

    MockCatalog* catalogMock;

    MockViewerPreferences* viewerPreferencesMock;

};



TEST_F(PopplerDocumentTest_2199, GetPrintNCopies_ReturnsDefaultWhenCatalogIsNull_2199) {

    EXPECT_CALL(*catalogMock, isOk()).WillOnce(Return(false));

    EXPECT_EQ(poppler_document_get_print_n_copies(&document), 1);

}



TEST_F(PopplerDocumentTest_2199, GetPrintNCopies_ReturnsDefaultWhenViewerPreferencesIsNull_2199) {

    EXPECT_CALL(*catalogMock, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*catalogMock, getViewerPreferences()).WillOnce(Return(nullptr));

    EXPECT_EQ(poppler_document_get_print_n_copies(&document), 1);

}



TEST_F(PopplerDocumentTest_2199, GetPrintNCopies_ReturnsDefaultWhenCatalogNotOk_2199) {

    EXPECT_CALL(*catalogMock, isOk()).WillOnce(Return(false));

    EXPECT_EQ(poppler_document_get_print_n_copies(&document), 1);

}



TEST_F(PopplerDocumentTest_2199, GetPrintNCopies_ReturnsNumCopiesFromViewerPreferences_2199) {

    EXPECT_CALL(*catalogMock, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*catalogMock, getViewerPreferences()).WillOnce(Return(viewerPreferencesMock));

    EXPECT_CALL(*viewerPreferencesMock, getNumCopies()).WillOnce(Return(3));

    EXPECT_EQ(poppler_document_get_print_n_copies(&document), 3);

}



TEST_F(PopplerDocumentTest_2199, GetPrintNCopies_ReturnsBoundaryValue_2199) {

    EXPECT_CALL(*catalogMock, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*catalogMock, getViewerPreferences()).WillOnce(Return(viewerPreferencesMock));

    EXPECT_CALL(*viewerPreferencesMock, getNumCopies()).WillOnce(Return(0));

    EXPECT_EQ(poppler_document_get_print_n_copies(&document), 1);

}



TEST_F(PopplerDocumentTest_2199, GetPrintNCopies_ReturnsBoundaryValueMax_2199) {

    EXPECT_CALL(*catalogMock, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*catalogMock, getViewerPreferences()).WillOnce(Return(viewerPreferencesMock));

    EXPECT_CALL(*viewerPreferencesMock, getNumCopies()).WillOnce(Return(INT_MAX));

    EXPECT_EQ(poppler_document_get_print_n_copies(&document), INT_MAX);

}
