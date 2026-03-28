#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "Catalog.h"



using namespace testing;



// Mock Catalog class to control its behavior for testing.

class MockCatalog : public Catalog {

public:

    MOCK_METHOD(bool, isOk, (), (const, override));

    MOCK_METHOD(int, numEmbeddedFiles, (), (override));

    MOCK_METHOD(std::unique_ptr<FileSpec>, embeddedFile, (int), (override));

};



// Test Fixture class for PopplerDocument tests.

class PopplerDocumentTest_2156 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock catalog and inject it into the document.

        document = new PopplerDocument();

        document->doc = new PDFDoc();

        document->doc->setCatalog(new NiceMock<MockCatalog>());

    }



    void TearDown() override {

        delete document->doc->getCatalog();

        delete document->doc;

        delete document;

    }



    PopplerDocument *document;

};



TEST_F(PopplerDocumentTest_2156, GetAttachments_ReturnsNullIfCatalogIsNull_2156) {

    // Arrange

    document->doc->setCatalog(nullptr);



    // Act & Assert

    EXPECT_EQ(poppler_document_get_attachments(document), nullptr);

}



TEST_F(PopplerDocumentTest_2156, GetAttachments_ReturnsNullIfCatalogIsNotOk_2156) {

    // Arrange

    ON_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), isOk()).WillByDefault(Return(false));



    // Act & Assert

    EXPECT_EQ(poppler_document_get_attachments(document), nullptr);

}



TEST_F(PopplerDocumentTest_2156, GetAttachments_ReturnsEmptyListIfNoEmbeddedFiles_2156) {

    // Arrange

    ON_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), isOk()).WillByDefault(Return(true));

    ON_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), numEmbeddedFiles()).WillByDefault(Return(0));



    // Act & Assert

    EXPECT_EQ(poppler_document_get_attachments(document), nullptr);

}



TEST_F(PopplerDocumentTest_2156, GetAttachments_ReturnsListOfAttachmentsIfEmbeddedFilesExist_2156) {

    // Arrange

    ON_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), isOk()).WillByDefault(Return(true));

    ON_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), numEmbeddedFiles()).WillByDefault(Return(3));



    auto mockFileSpec1 = std::make_unique<FileSpec>();

    mockFileSpec1->isOkReturn = true;

    mockFileSpec1->embeddedFileReturn = std::make_unique<EmbeddedFile>();



    auto mockFileSpec2 = std::make_unique<FileSpec>();

    mockFileSpec2->isOkReturn = false;



    auto mockFileSpec3 = std::make_unique<FileSpec>();

    mockFileSpec3->isOkReturn = true;

    mockFileSpec3->embeddedFileReturn = std::make_unique<EmbeddedFile>();



    EXPECT_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), embeddedFile(0)).WillOnce(ReturnByMove(std::move(mockFileSpec1)));

    EXPECT_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), embeddedFile(1)).WillOnce(ReturnByMove(std::move(mockFileSpec2)));

    EXPECT_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), embeddedFile(2)).WillOnce(ReturnByMove(std::move(mockFileSpec3)));



    // Act

    GList *attachments = poppler_document_get_attachments(document);



    // Assert

    ASSERT_NE(attachments, nullptr);

    EXPECT_EQ(g_list_length(attachments), 2); // Only two valid attachments



    g_list_free_full(attachments, reinterpret_cast<GDestroyNotify>(poppler_attachment_free));

}



TEST_F(PopplerDocumentTest_2156, GetAttachments_HandlesEmbeddedFileNotOkGracefully_2156) {

    // Arrange

    ON_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), isOk()).WillByDefault(Return(true));

    ON_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), numEmbeddedFiles()).WillByDefault(Return(1));



    auto mockFileSpec = std::make_unique<FileSpec>();

    mockFileSpec->isOkReturn = true;

    mockFileSpec->embeddedFileReturn = std::make_unique<EmbeddedFile>();

    mockFileSpec->embeddedFileReturn->isOkReturn = false;



    EXPECT_CALL(*static_cast<MockCatalog*>(document->doc->getCatalog()), embeddedFile(0)).WillOnce(ReturnByMove(std::move(mockFileSpec)));



    // Act

    GList *attachments = poppler_document_get_attachments(document);



    // Assert

    EXPECT_EQ(attachments, nullptr); // No valid attachments



    g_list_free_full(attachments, reinterpret_cast<GDestroyNotify>(poppler_attachment_free));

}
