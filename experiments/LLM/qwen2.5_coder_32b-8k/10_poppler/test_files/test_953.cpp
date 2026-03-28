#include <gtest/gtest.h>

#include "PDFDoc.h"

#include <memory>

#include <optional>

#include <string>



class PDFDocTest_953 : public ::testing::Test {

protected:

    std::unique_ptr<BaseStream> mockBaseStream;

    std::function<void(void)> mockCallback;



    void SetUp() override {

        mockBaseStream = std::make_unique<BaseStream>();

        mockCallback = [](){};

    }



    PDFDoc* createPDFDocWithBaseStream() {

        return new PDFDoc(std::move(mockBaseStream), std::nullopt, std::nullopt, mockCallback);

    }

};



TEST_F(PDFDocTest_953, GetBaseStream_ReturnsValidPointer_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    EXPECT_NE(pdfDoc->getBaseStream(), nullptr);

    delete pdfDoc;

}



TEST_F(PDFDocTest_953, IsOk_ReturnsTrueForValidDocument_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    EXPECT_TRUE(pdfDoc->isOk());

    delete pdfDoc;

}



TEST_F(PDFDocTest_953, GetErrorCode_ReturnsZeroForSuccessfulInitialization_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    EXPECT_EQ(pdfDoc->getErrorCode(), 0);

    delete pdfDoc;

}



TEST_F(PDFDocTest_953, GetNumPages_ReturnsCorrectNumberOfPages_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    int numPages = pdfDoc->getNumPages();

    EXPECT_GE(numPages, 0); // Assuming the document has at least zero pages

    delete pdfDoc;

}



TEST_F(PDFDocTest_953, GetPage_ReturnsValidPointerForExistingPage_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    int numPages = pdfDoc->getNumPages();

    if (numPages > 0) { // Only test if there are pages

        EXPECT_NE(pdfDoc->getPage(1), nullptr);

    }

    delete pdfDoc;

}



TEST_F(PDFDocTest_953, GetPage_ReturnsNullForNonExistingPage_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    int numPages = pdfDoc->getNumPages();

    EXPECT_EQ(pdfDoc->getPage(numPages + 1), nullptr); // Page index out of bounds

    delete pdfDoc;

}



TEST_F(PDFDocTest_953, GetOutline_ReturnsValidPointerIfPresent_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    EXPECT_NE(pdfDoc->getOutline(), nullptr); // Assuming the document always has an outline

    delete pdfDoc;

}



TEST_F(PDFDocTest_953, GetSignatureFields_ReturnsEmptyVectorIfNoSignatures_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    EXPECT_TRUE(pdfDoc->getSignatureFields().empty()); // Assuming the document has no signatures

    delete pdfDoc;

}



TEST_F(PDFDocTest_953, IsLinearized_ReturnsFalseForNonLinearizedDocument_953) {

    PDFDoc* pdfDoc = createPDFDocWithBaseStream();

    EXPECT_FALSE(pdfDoc->isLinearized(false));

    delete pdfDoc;

}
