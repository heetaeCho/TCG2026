#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"

#include <memory>

#include <optional>



using namespace std;



class PDFDocTest_949 : public ::testing::Test {

protected:

    void SetUp() override {

        fileName = make_unique<GooString>("testfile.pdf");

        pdfDoc = make_unique<PDFDoc>(move(fileName), nullopt, nullopt, [](){});

    }



    unique_ptr<GooString> fileName;

    unique_ptr<PDFDoc> pdfDoc;

};



TEST_F(PDFDocTest_949, GetFileName_ReturnsCorrectFileName_949) {

    const GooString* result = pdfDoc->getFileName();

    EXPECT_EQ(strcmp(result->getCString(), "testfile.pdf"), 0);

}



TEST_F(PDFDocTest_949, IsOk_ReturnsTrueForValidPDF_949) {

    EXPECT_TRUE(pdfDoc->isOk());

}



TEST_F(PDFDocTest_949, GetErrorCode_ReturnsZeroForValidPDF_949) {

    EXPECT_EQ(pdfDoc->getErrorCode(), 0);

}



TEST_F(PDFDocTest_949, GetFopenErrno_ReturnsNegativeOneForValidPDF_949) {

    EXPECT_EQ(pdfDoc->getFopenErrno(), -1);

}



TEST_F(PDFDocTest_949, GetXRef_ReturnsNonNullPointer_949) {

    XRef* xref = pdfDoc->getXRef();

    EXPECT_NE(xref, nullptr);

}



TEST_F(PDFDocTest_949, GetCatalog_ReturnsNonNullPointer_949) {

    Catalog* catalog = pdfDoc->getCatalog();

    EXPECT_NE(catalog, nullptr);

}



TEST_F(PDFDocTest_949, GetBaseStream_ReturnsNonNullPointer_949) {

    BaseStream* baseStream = pdfDoc->getBaseStream();

    EXPECT_NE(baseStream, nullptr);

}



TEST_F(PDFDocTest_949, GetPDFMajorVersion_ReturnsValidVersionNumber_949) {

    int majorVersion = pdfDoc->getPDFMajorVersion();

    EXPECT_GE(majorVersion, 0);

}



TEST_F(PDFDocTest_949, GetPDFMinorVersion_ReturnsValidVersionNumber_949) {

    int minorVersion = pdfDoc->getPDFMinorVersion();

    EXPECT_GE(minorVersion, 0);

}
