#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "Catalog.h"



using ::testing::Return;



class PopplerDocumentTest : public ::testing::Test {

protected:

    struct _PopplerDocument document;

    Catalog* mock_catalog;



    void SetUp() override {

        mock_catalog = new Catalog(nullptr);

        document.doc = mock_catalog;

    }



    void TearDown() override {

        delete mock_catalog;

    }

};



TEST_F(PopplerDocumentTest_2154, GetZeroAttachmentsWhenCatalogIsNull_2154) {

    document.doc = nullptr;

    EXPECT_EQ(poppler_document_get_n_attachments(&document), 0);

}



TEST_F(PopplerDocumentTest_2154, GetZeroAttachmentsWhenCatalogIsNotOk_2154) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(false));

    EXPECT_EQ(poppler_document_get_n_attachments(&document), 0);

}



TEST_F(PopplerDocumentTest_2154, GetOneAttachmentWhenCatalogHasOneEmbeddedFile_2154) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, numEmbeddedFiles()).WillOnce(Return(1));

    EXPECT_EQ(poppler_document_get_n_attachments(&document), 1);

}



TEST_F(PopplerDocumentTest_2154, GetMultipleAttachmentsWhenCatalogHasMultipleEmbeddedFiles_2154) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, numEmbeddedFiles()).WillOnce(Return(5));

    EXPECT_EQ(poppler_document_get_n_attachments(&document), 5);

}



TEST_F(PopplerDocumentTest_2154, GetNoAttachmentsWhenCatalogHasNoEmbeddedFiles_2154) {

    EXPECT_CALL(*mock_catalog, isOk()).WillOnce(Return(true));

    EXPECT_CALL(*mock_catalog, numEmbeddedFiles()).WillOnce(Return(0));

    EXPECT_EQ(poppler_document_get_n_attachments(&document), 0);

}
