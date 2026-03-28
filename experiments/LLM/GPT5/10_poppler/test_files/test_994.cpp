#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"
#include "Catalog.h"

// Mocking Catalog since it is a dependency of PDFDoc.
class MockCatalog : public Catalog {
public:
    MOCK_METHOD(int, getPDFMajorVersion, (), (const, override));
};

class PDFDocTest_994 : public testing::Test {
protected:
    MockCatalog* mockCatalog;
    PDFDoc* pdfDoc;

    void SetUp() override {
        mockCatalog = new MockCatalog(nullptr);  // Passing nullptr as Catalog's constructor expects PDFDoc* which is not needed here.
        pdfDoc = new PDFDoc();  // Creating an instance of PDFDoc.
        pdfDoc->catalog = mockCatalog;  // Injecting the mock catalog into the PDFDoc.
    }

    void TearDown() override {
        delete pdfDoc;
        delete mockCatalog;
    }
};

// Normal operation test
TEST_F(PDFDocTest_994, GetPDFMajorVersion_ReturnsCorrectVersion_994) {
    // Arrange
    int headerVersion = 1;
    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(2));

    pdfDoc->headerPdfMajorVersion = headerVersion;

    // Act
    int version = pdfDoc->getPDFMajorVersion();

    // Assert
    EXPECT_EQ(version, 2);
}

// Boundary condition test for headerPdfMajorVersion being 0
TEST_F(PDFDocTest_994, GetPDFMajorVersion_HeaderVersionZero_994) {
    // Arrange
    int headerVersion = 0;
    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(5));

    pdfDoc->headerPdfMajorVersion = headerVersion;

    // Act
    int version = pdfDoc->getPDFMajorVersion();

    // Assert
    EXPECT_EQ(version, 5);
}

// Exceptional case when catalog's getPDFMajorVersion() returns a negative value
TEST_F(PDFDocTest_994, GetPDFMajorVersion_CatalogReturnsNegative_994) {
    // Arrange
    int headerVersion = 2;
    EXPECT_CALL(*mockCatalog, getPDFMajorVersion()).WillOnce(testing::Return(-1));

    pdfDoc->headerPdfMajorVersion = headerVersion;

    // Act
    int version = pdfDoc->getPDFMajorVersion();

    // Assert
    EXPECT_EQ(version, 2);  // The header version should take precedence over the negative catalog version.
}