#include <gtest/gtest.h>

#include "PDFDoc.h"

#include <memory>

#include <optional>

#include <functional>



class PDFDocTest_946 : public ::testing::Test {

protected:

    void SetUp() override {

        fileName = std::make_unique<GooString>("dummy.pdf");

        ownerPassword = std::nullopt;

        userPassword = std::nullopt;

        xrefReconstructedCallback = [](){};

    }



    std::unique_ptr<GooString> fileName;

    std::optional<GooString> ownerPassword;

    std::optional<GooString> userPassword;

    std::function<void(void)> xrefReconstructedCallback;

};



TEST_F(PDFDocTest_946, ConstructorValidFile_946) {

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_TRUE(doc.isOk());

}



TEST_F(PDFDocTest_946, ConstructorInvalidFile_946) {

    fileName = std::make_unique<GooString>("nonexistent.pdf");

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_FALSE(doc.isOk());

}



TEST_F(PDFDocTest_946, GetErrorCodeInitiallyZero_946) {

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ(0, doc.getErrorCode());

}



TEST_F(PDFDocTest_946, GetFopenErrnoInitiallyNegativeOne_946) {

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ(-1, doc.getFopenErrno());

}



TEST_F(PDFDocTest_946, GetFileNameReturnsProvidedName_946) {

    fileName = std::make_unique<GooString>("testfile.pdf");

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ("testfile.pdf", *(doc.getFileName()));

}



TEST_F(PDFDocTest_946, GetNumPagesOnInvalidDocumentReturnsZero_946) {

    fileName = std::make_unique<GooString>("nonexistent.pdf");

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ(0, doc.getNumPages());

}



TEST_F(PDFDocTest_946, GetNumPagesOnValidDocumentReturnsPositiveNumber_946) {

    // Assuming "dummy.pdf" is a valid PDF with at least one page

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_GT(doc.getNumPages(), 0);

}



TEST_F(PDFDocTest_946, GetPageOnInvalidDocumentReturnsNullptr_946) {

    fileName = std::make_unique<GooString>("nonexistent.pdf");

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ(nullptr, doc.getPage(1));

}



TEST_F(PDFDocTest_946, GetPageOnValidDocumentReturnsNonNullptrForExistingPage_946) {

    // Assuming "dummy.pdf" is a valid PDF with at least one page

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_NE(nullptr, doc.getPage(1));

}



TEST_F(PDFDocTest_946, GetPageOnValidDocumentReturnsNullptrForNonExistingPage_946) {

    // Assuming "dummy.pdf" is a valid PDF with at least one page

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ(nullptr, doc.getPage(1000)); // Assuming there's no 1000th page

}



TEST_F(PDFDocTest_946, GetOutlineOnInvalidDocumentReturnsNullptr_946) {

    fileName = std::make_unique<GooString>("nonexistent.pdf");

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ(nullptr, doc.getOutline());

}



TEST_F(PDFDocTest_946, GetOutlineOnValidDocumentReturnsNonNullptrIfOutlineExists_946) {

    // Assuming "dummy.pdf" is a valid PDF with an outline

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_NE(nullptr, doc.getOutline());

}



TEST_F(PDFDocTest_946, GetLinksOnInvalidDocumentReturnsNullptr_946) {

    fileName = std::make_unique<GooString>("nonexistent.pdf");

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ(nullptr, doc.getLinks(1).get());

}



TEST_F(PDFDocTest_946, GetLinksOnValidDocumentReturnsNonNullptrForExistingPage_946) {

    // Assuming "dummy.pdf" is a valid PDF with links on the first page

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_NE(nullptr, doc.getLinks(1).get());

}



TEST_F(PDFDocTest_946, GetLinksOnValidDocumentReturnsNullptrForNonExistingPage_946) {

    // Assuming "dummy.pdf" is a valid PDF with no 1000th page

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_EQ(nullptr, doc.getLinks(1000).get());

}



TEST_F(PDFDocTest_946, IsLinearizedReturnsFalseOnNonLinearizedDocument_946) {

    // Assuming "dummy.pdf" is a valid PDF that is not linearized

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_FALSE(doc.isLinearized(false));

}



TEST_F(PDFDocTest_946, IsEncryptedReturnsFalseOnUnencryptedDocument_946) {

    // Assuming "dummy.pdf" is a valid PDF that is not encrypted

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_FALSE(doc.isEncrypted());

}



TEST_F(PDFDocTest_946, OkToPrintReturnsTrueOnUnrestrictedDocument_946) {

    // Assuming "dummy.pdf" is a valid PDF with no restrictions on printing

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_TRUE(doc.okToPrint());

}



TEST_F(PDFDocTest_946, OkToChangeReturnsTrueOnUnrestrictedDocument_946) {

    // Assuming "dummy.pdf" is a valid PDF with no restrictions on changing the document

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_TRUE(doc.okToChange());

}



TEST_F(PDFDocTest_946, OkToAddNotesReturnsTrueOnUnrestrictedDocument_946) {

    // Assuming "dummy.pdf" is a valid PDF with no restrictions on adding notes

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_TRUE(doc.okToAddNotes());

}



TEST_F(PDFDocTest_946, OkToFillFormReturnsTrueOnUnrestrictedDocument_946) {

    // Assuming "dummy.pdf" is a valid PDF with no restrictions on filling forms

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_TRUE(doc.okToFillForm());

}



TEST_F(PDFDocTest_946, OkToAccessibilityReturnsTrueOnUnrestrictedDocument_946) {

    // Assuming "dummy.pdf" is a valid PDF with no restrictions on accessibility

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_TRUE(doc.okToAccessibility());

}



TEST_F(PDFDocTest_946, OkToAssembleReturnsTrueOnUnrestrictedDocument_946) {

    // Assuming "dummy.pdf" is a valid PDF with no restrictions on assembling

    PDFDoc doc(std::make_unique<GooString>("dummy.pdf"), ownerPassword, userPassword, xrefReconstructedCallback);

    EXPECT_TRUE(doc.okToAssemble());

}
