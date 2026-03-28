#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"
#include "Catalog.h"

using namespace ::testing;

class PDFDocTest_995 : public testing::Test {
protected:
    void SetUp() override {
        // Setup mock catalog and PDFDoc instances
        mockCatalog = std::make_unique<MockCatalog>();
        pdfDoc = std::make_unique<PDFDoc>(std::move(mockCatalog));
    }

    std::unique_ptr<MockCatalog> mockCatalog;
    std::unique_ptr<PDFDoc> pdfDoc;
};

// Mock Catalog class to simulate behavior of Catalog in PDFDoc
class MockCatalog : public Catalog {
public:
    MOCK_METHOD(int, getPDFMajorVersion, (), (const));
    MOCK_METHOD(int, getPDFMinorVersion, (), (const));
};

TEST_F(PDFDocTest_995, GetPDFMinorVersion_WhenCatalogMajorGreaterThanHeaderVersion_ReturnsCatalogMinor_995) {
    // Setup: Mock behavior when catalog's major version is greater than header version
    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(Return(2));  // Catalog Major version is 2
    pdfDoc->headerPdfMajorVersion = 1;  // Header version is 1
    EXPECT_CALL(*mockCatalog, getPDFMinorVersion()).WillOnce(Return(5));  // Catalog Minor version is 5

    // Act & Assert
    EXPECT_EQ(pdfDoc->getPDFMinorVersion(), 5);  // Expect Catalog's minor version to be returned
}

TEST_F(PDFDocTest_995, GetPDFMinorVersion_WhenHeaderVersionGreaterThanCatalogMajorVersion_ReturnsHeaderMinor_995) {
    // Setup: Mock behavior when header version is greater than catalog's major version
    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(Return(1));  // Catalog Major version is 1
    pdfDoc->headerPdfMajorVersion = 2;  // Header version is 2
    EXPECT_CALL(*mockCatalog, getPDFMinorVersion()).WillOnce(Return(5));  // Catalog Minor version is 5

    // Act & Assert
    EXPECT_EQ(pdfDoc->getPDFMinorVersion(), 5);  // Expect Header's minor version to be returned
}

TEST_F(PDFDocTest_995, GetPDFMinorVersion_WhenMajorVersionsEqual_ReturnsMaxOfMinorVersions_995) {
    // Setup: Mock behavior when major versions are equal
    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(Return(1));  // Catalog Major version is 1
    pdfDoc->headerPdfMajorVersion = 1;  // Header version is also 1
    EXPECT_CALL(*mockCatalog, getPDFMinorVersion()).WillOnce(Return(5));  // Catalog Minor version is 5
    pdfDoc->headerPdfMinorVersion = 6;  // Header Minor version is 6

    // Act & Assert
    EXPECT_EQ(pdfDoc->getPDFMinorVersion(), 6);  // Expect maximum minor version to be returned
}

TEST_F(PDFDocTest_995, GetPDFMinorVersion_WhenCatalogHasInvalidMinorVersion_ReturnsHeaderMinor_995) {
    // Setup: Mock behavior for an invalid catalog minor version
    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(Return(1));  // Catalog Major version is 1
    pdfDoc->headerPdfMajorVersion = 1;  // Header version is also 1
    EXPECT_CALL(*mockCatalog, getPDFMinorVersion()).WillOnce(Return(-1));  // Invalid Catalog Minor version (-1)
    pdfDoc->headerPdfMinorVersion = 6;  // Header Minor version is 6

    // Act & Assert
    EXPECT_EQ(pdfDoc->getPDFMinorVersion(), 6);  // Expect Header's minor version to be returned
}

TEST_F(PDFDocTest_995, GetPDFMinorVersion_WhenCatalogAndHeaderHaveEqualVersions_ReturnsCatalogMinor_995) {
    // Setup: Mock behavior when both versions are equal
    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(Return(1));  // Catalog Major version is 1
    pdfDoc->headerPdfMajorVersion = 1;  // Header version is 1
    EXPECT_CALL(*mockCatalog, getPDFMinorVersion()).WillOnce(Return(5));  // Catalog Minor version is 5
    pdfDoc->headerPdfMinorVersion = 5;  // Header Minor version is 5

    // Act & Assert
    EXPECT_EQ(pdfDoc->getPDFMinorVersion(), 5);  // Expect Catalog's minor version to be returned
}