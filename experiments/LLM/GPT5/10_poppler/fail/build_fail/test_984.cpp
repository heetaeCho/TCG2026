#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"

class PDFDocTest_984 : public ::testing::Test {
protected:
    // Mock dependencies and setup code, if needed.
    // For this specific test, the PDFDoc class is a black-box and doesn't require external mocks.
};

TEST_F(PDFDocTest_984, GetDocInfoAuthor_ReturnsCorrectAuthor_984) {
    // Arrange
    std::unique_ptr<GooString> author = std::make_unique<GooString>("John Doe");
    PDFDoc pdfDoc(/* necessary constructor arguments */);
    pdfDoc.setDocInfoAuthor(std::move(author));

    // Act
    std::unique_ptr<GooString> retrievedAuthor = pdfDoc.getDocInfoAuthor();

    // Assert
    EXPECT_EQ(*retrievedAuthor, "John Doe");
}

TEST_F(PDFDocTest_984, GetDocInfoAuthor_WhenNotSet_ReturnsNullptr_984) {
    // Arrange
    PDFDoc pdfDoc(/* necessary constructor arguments */);

    // Act
    std::unique_ptr<GooString> retrievedAuthor = pdfDoc.getDocInfoAuthor();

    // Assert
    EXPECT_EQ(retrievedAuthor, nullptr);
}

TEST_F(PDFDocTest_984, SetDocInfoAuthor_SetsCorrectAuthor_984) {
    // Arrange
    std::unique_ptr<GooString> author = std::make_unique<GooString>("Jane Smith");
    PDFDoc pdfDoc(/* necessary constructor arguments */);

    // Act
    pdfDoc.setDocInfoAuthor(std::move(author));
    std::unique_ptr<GooString> retrievedAuthor = pdfDoc.getDocInfoAuthor();

    // Assert
    EXPECT_EQ(*retrievedAuthor, "Jane Smith");
}

TEST_F(PDFDocTest_984, GetDocInfoAuthor_WithEmptyString_ReturnsEmptyString_984) {
    // Arrange
    std::unique_ptr<GooString> author = std::make_unique<GooString>("");
    PDFDoc pdfDoc(/* necessary constructor arguments */);
    pdfDoc.setDocInfoAuthor(std::move(author));

    // Act
    std::unique_ptr<GooString> retrievedAuthor = pdfDoc.getDocInfoAuthor();

    // Assert
    EXPECT_EQ(*retrievedAuthor, "");
}

TEST_F(PDFDocTest_984, GetDocInfoAuthor_WithSpecialCharacters_ReturnsCorrectString_984) {
    // Arrange
    std::unique_ptr<GooString> author = std::make_unique<GooString>("John O'Conner");
    PDFDoc pdfDoc(/* necessary constructor arguments */);
    pdfDoc.setDocInfoAuthor(std::move(author));

    // Act
    std::unique_ptr<GooString> retrievedAuthor = pdfDoc.getDocInfoAuthor();

    // Assert
    EXPECT_EQ(*retrievedAuthor, "John O'Conner");
}