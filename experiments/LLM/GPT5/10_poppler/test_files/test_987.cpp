#include <gtest/gtest.h>
#include <memory>
#include <functional>
#include "PDFDoc.h"  // Include the header file for the PDFDoc class

// Test suite for the PDFDoc class
class PDFDocTest : public ::testing::Test {
protected:
    // This can be used to set up test fixtures if needed
    void SetUp() override {
        // Setup code if necessary
    }

    // This can be used to clean up after tests if needed
    void TearDown() override {
        // Cleanup code if necessary
    }
};

// Test for the getDocInfoCreator function
TEST_F(PDFDocTest, GetDocInfoCreator_987) {
    // Arrange
    std::unique_ptr<GooString> creatorString = std::make_unique<GooString>("Test Creator");
    PDFDoc pdfDoc;

    // Assuming setDocInfoCreator sets the "Creator" entry.
    pdfDoc.setDocInfoCreator(std::move(creatorString));

    // Act
    std::unique_ptr<GooString> result = pdfDoc.getDocInfoCreator();

    // Assert
    ASSERT_NE(result, nullptr);  // Check that the result is not null
    EXPECT_EQ(result->c_str(), "Test Creator");  // Verify the content of the creator string
}

// Test for the normal behavior when retrieving document info title
TEST_F(PDFDocTest, GetDocInfoTitle_987) {
    // Arrange
    std::unique_ptr<GooString> title = std::make_unique<GooString>("Test Title");
    PDFDoc pdfDoc;
    pdfDoc.setDocInfoTitle(std::move(title));

    // Act
    std::unique_ptr<GooString> result = pdfDoc.getDocInfoTitle();

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c_str(), "Test Title");
}

// Test for the exceptional case when attempting to get an unset document info creator
TEST_F(PDFDocTest, GetDocInfoCreator_Unset_987) {
    // Arrange
    PDFDoc pdfDoc;  // Not setting creator

    // Act
    std::unique_ptr<GooString> result = pdfDoc.getDocInfoCreator();

    // Assert
    EXPECT_EQ(result, nullptr);  // Expect null if not set
}

// Test for boundary conditions - handling maximum length of document info creator
TEST_F(PDFDocTest, GetDocInfoCreator_MaxLength_987) {
    // Arrange
    std::string longString(1000, 'A');  // 1000 characters
    std::unique_ptr<GooString> creator = std::make_unique<GooString>(longString);
    PDFDoc pdfDoc;
    pdfDoc.setDocInfoCreator(std::move(creator));

    // Act
    std::unique_ptr<GooString> result = pdfDoc.getDocInfoCreator();

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c_str(), longString);  // Check that the long string is handled properly
}

// Test for boundary conditions - handling empty string for document info creator
TEST_F(PDFDocTest, GetDocInfoCreator_Empty_987) {
    // Arrange
    std::unique_ptr<GooString> creator = std::make_unique<GooString>("");
    PDFDoc pdfDoc;
    pdfDoc.setDocInfoCreator(std::move(creator));

    // Act
    std::unique_ptr<GooString> result = pdfDoc.getDocInfoCreator();

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c_str(), "");  // Verify empty string is handled
}