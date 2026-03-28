#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"



// Test fixture for PDFDoc tests.

class PDFDocTest_951 : public ::testing::Test {

protected:

    // Create a mock PDFDoc instance using a dummy file name and empty passwords.

    std::unique_ptr<PDFDoc> pdfDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::nullopt, std::nullopt, [](){});

};



// Test to verify that getCatalog() returns a non-null pointer if the PDFDoc is initialized correctly.

TEST_F(PDFDocTest_951, GetCatalog_ReturnsNonNullPointer_951) {

    EXPECT_NE(pdfDoc->getCatalog(), nullptr);

}



// Test to verify that getNumPages() returns 0 for an uninitialized or empty document.

TEST_F(PDFDocTest_951, GetNumPages_ReturnsZeroForEmptyDocument_951) {

    EXPECT_EQ(pdfDoc->getNumPages(), 0);

}



// Test to verify that getPage() returns nullptr for a page number out of bounds.

TEST_F(PDFDocTest_951, GetPage_ReturnsNullForInvalidPageNumber_951) {

    EXPECT_EQ(pdfDoc->getPage(-1), nullptr);

    EXPECT_EQ(pdfDoc->getPage(100), nullptr); // Assuming the document has less than 100 pages.

}



// Test to verify that isOk() returns true if the PDFDoc instance is initialized successfully.

TEST_F(PDFDocTest_951, IsOk_ReturnsTrueForSuccessfulInitialization_951) {

    EXPECT_TRUE(pdfDoc->isOk());

}



// Test to verify that getErrorCode() returns 0 for a successful initialization.

TEST_F(PDFDocTest_951, GetErrorCode_ReturnsZeroForSuccessfulInitialization_951) {

    EXPECT_EQ(pdfDoc->getErrorCode(), 0);

}



// Test to verify that getPageMediaWidth() throws an exception or returns 0 for an invalid page number.

TEST_F(PDFDocTest_951, GetPageMediaWidth_ReturnsZeroForInvalidPageNumber_951) {

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaWidth(-1), 0.0);

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaWidth(100), 0.0); // Assuming the document has less than 100 pages.

}



// Test to verify that getPageMediaHeight() throws an exception or returns 0 for an invalid page number.

TEST_F(PDFDocTest_951, GetPageMediaHeight_ReturnsZeroForInvalidPageNumber_951) {

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaHeight(-1), 0.0);

    EXPECT_DOUBLE_EQ(pdfDoc->getPageMediaHeight(100), 0.0); // Assuming the document has less than 100 pages.

}



// Test to verify that getBaseStream() returns a non-null pointer if the PDFDoc is initialized correctly with a BaseStream.

TEST_F(PDFDocTest_951, GetBaseStream_ReturnsNonNullPointer_951) {

    // Assuming the constructor using BaseStream is used instead of file name.

    std::unique_ptr<BaseStream> stream = std::make_unique<BaseStream>();

    auto pdfDocWithStream = std::make_unique<PDFDoc>(std::move(stream), std::nullopt, std::nullopt, [](){});

    EXPECT_NE(pdfDocWithStream->getBaseStream(), nullptr);

}
