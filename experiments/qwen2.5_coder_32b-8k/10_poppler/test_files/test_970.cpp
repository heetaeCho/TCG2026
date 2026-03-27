#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"

#include "TestProjects/poppler/poppler/XRef.h"



class PDFDocTest_970 : public ::testing::Test {

protected:

    PDFDoc* pdfDoc;

    XRef mockXRef;



    void SetUp() override {

        // Mocking the xref pointer in PDFDoc to point to our mockXRef

        pdfDoc = new PDFDoc();

        pdfDoc->xref = &mockXRef;

    }



    void TearDown() override {

        delete pdfDoc;

    }

};



TEST_F(PDFDocTest_970, OkToAccessibility_Default_ReturnsFalse_970) {

    EXPECT_CALL(mockXRef, okToAccessibility(false)).WillOnce(::testing::Return(false));

    bool result = pdfDoc->okToAccessibility();

    EXPECT_FALSE(result);

}



TEST_F(PDFDocTest_970, OkToAccessibility_IgnoreOwnerPW_False_ReturnsFalse_970) {

    EXPECT_CALL(mockXRef, okToAccessibility(false)).WillOnce(::testing::Return(false));

    bool result = pdfDoc->okToAccessibility(false);

    EXPECT_FALSE(result);

}



TEST_F(PDFDocTest_970, OkToAccessibility_IgnoreOwnerPW_True_ReturnsTrue_970) {

    EXPECT_CALL(mockXRef, okToAccessibility(true)).WillOnce(::testing::Return(true));

    bool result = pdfDoc->okToAccessibility(true);

    EXPECT_TRUE(result);

}



TEST_F(PDFDocTest_970, OkToAccessibility_Default_ReturnsTrue_970) {

    EXPECT_CALL(mockXRef, okToAccessibility(false)).WillOnce(::testing::Return(true));

    bool result = pdfDoc->okToAccessibility();

    EXPECT_TRUE(result);

}
