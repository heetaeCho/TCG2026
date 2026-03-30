#include <gtest/gtest.h>

#include "poppler/PDFDoc.h"



class PDFDocTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary state before each test

        pdfDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::nullopt, std::nullopt, [](){});

    }



    void TearDown() override {

        // Clean up any state after each test

        pdfDoc.reset();

    }



    std::unique_ptr<PDFDoc> pdfDoc;

};



TEST_F(PDFDocTest_950, GetXRef_ReturnsNonNullPointer_950) {

    EXPECT_NE(pdfDoc->getXRef(), nullptr);

}



TEST_F(PDFDocTest_950, IsOk_ReturnsTrue_WhenNoErrors_950) {

    EXPECT_TRUE(pdfDoc->isOk());

}



TEST_F(PDFDocTest_950, GetErrorCode_ReturnsZero_WhenNoErrors_950) {

    EXPECT_EQ(pdfDoc->getErrorCode(), 0);

}



TEST_F(PDFDocTest_950, GetFopenErrno_ReturnsZero_WhenNoFileOpenErrors_950) {

    EXPECT_EQ(pdfDoc->getFopenErrno(), 0);

}



TEST_F(PDFDocTest_950, GetFileName_ReturnsProvidedFileName_950) {

    auto fileName = pdfDoc->getFileName();

    ASSERT_NE(fileName, nullptr);

    EXPECT_STREQ(fileName->getCString(), "dummy.pdf");

}



TEST_F(PDFDocTest_950, GetCatalog_ReturnsNonNullPointer_950) {

    EXPECT_NE(pdfDoc->getCatalog(), nullptr);

}



TEST_F(PDFDocTest_950, GetOptContentConfig_ReturnsNullPointer_AsNotImplemented_950) {

    EXPECT_EQ(pdfDoc->getOptContentConfig(), nullptr);

}



TEST_F(PDFDocTest_950, GetBaseStream_ReturnsNonNullPointer_950) {

    EXPECT_NE(pdfDoc->getBaseStream(), nullptr);

}



TEST_F(PDFDocTest_950, GetNumPages_ReturnsZero_ForEmptyDocument_950) {

    EXPECT_EQ(pdfDoc->getNumPages(), 0);

}



TEST_F(PDFDocTest_950, IsEncrypted_ReturnsFalse_AsNoEncryptionSet_950) {

    EXPECT_FALSE(pdfDoc->isEncrypted());

}



TEST_F(PDFDocTest_950, OkToPrint_ReturnsTrue_AsNoRestrictionsByDefault_950) {

    EXPECT_TRUE(pdfDoc->okToPrint());

}



TEST_F(PDFDocTest_950, OkToChange_ReturnsTrue_AsNoRestrictionsByDefault_950) {

    EXPECT_TRUE(pdfDoc->okToChange());

}



TEST_F(PDFDocTest_950, OkToCopy_ReturnsTrue_AsNoRestrictionsByDefault_950) {

    EXPECT_TRUE(pdfDoc->okToCopy());

}



TEST_F(PDFDocTest_950, OkToAddNotes_ReturnsTrue_AsNoRestrictionsByDefault_950) {

    EXPECT_TRUE(pdfDoc->okToAddNotes());

}



TEST_F(PDFDocTest_950, OkToFillForm_ReturnsTrue_AsNoRestrictionsByDefault_950) {

    EXPECT_TRUE(pdfDoc->okToFillForm());

}



TEST_F(PDFDocTest_950, OkToAccessibility_ReturnsTrue_AsNoRestrictionsByDefault_950) {

    EXPECT_TRUE(pdfDoc->okToAccessibility());

}



TEST_F(PDFDocTest_950, OkToAssemble_ReturnsTrue_AsNoRestrictionsByDefault_950) {

    EXPECT_TRUE(pdfDoc->okToAssemble());

}
