#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/XRef.h"



using namespace testing;



class PDFDocTest_972 : public Test {

protected:

    std::unique_ptr<GooString> fileName = std::make_unique<GooString>("dummy.pdf");

    std::optional<GooString> ownerPassword;

    std::optional<GooString> userPassword;

    MockFunction<void()> xrefReconstructedCallbackMock;



    PDFDocTest_972() : pdfDoc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallbackMock.AsStdFunction()) {

        EXPECT_CALL(xrefReconstructedCallbackMock, Call()).Times(0); // Default expectation for callback

    }



    std::unique_ptr<PDFDoc> pdfDoc;

};



TEST_F(PDFDocTest_972, GetDocInfo_NormalOperation_972) {

    Object docInfo = pdfDoc->getDocInfo();

    EXPECT_TRUE(docInfo.isDict() || docInfo.isNull()); // Assuming normal operation returns a dictionary or null

}



TEST_F(PDFDocTest_972, GetDocInfo_CallbackNotCalled_972) {

    pdfDoc->getDocInfo();

    EXPECT_CALL(xrefReconstructedCallbackMock, Call()).Times(0); // Ensure callback is not invoked during getDocInfo

}



// Assuming PDFDoc can be in an error state that affects getDocInfo

TEST_F(PDFDocTest_972, GetDocInfo_ErrorState_972) {

    pdfDoc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));

    Object docInfo = pdfDoc->getDocInfo();

    EXPECT_TRUE(docInfo.isNull()); // Assuming in error state getDocInfo returns a null object

}



// Boundary condition: If the document has no metadata, it should return a null or empty dictionary.

TEST_F(PDFDocTest_972, GetDocInfo_NoMetadata_972) {

    Object docInfo = pdfDoc->getDocInfo();

    EXPECT_TRUE(docInfo.isNull() || (docInfo.isDict() && !docInfo.dictLookup("Title"))); // Assuming no metadata means empty dict or null

}
