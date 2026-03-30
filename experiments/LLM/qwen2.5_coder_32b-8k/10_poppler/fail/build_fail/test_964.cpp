#include <gtest/gtest.h>

#include "PDFDoc.h"

#include <gmock/gmock.h>



using namespace testing;



class PDFDocTest_964 : public ::testing::Test {

protected:

    class MockXRef : public XRef {

    public:

        MOCK_CONST_METHOD1(okToPrint, bool(bool));

        MOCK_CONST_METHOD1(okToPrintHighRes, bool(bool));

        MOCK_CONST_METHOD1(okToChange, bool(bool));

        MOCK_CONST_METHOD1(okToCopy, bool(bool));

        MOCK_CONST_METHOD1(okToAddNotes, bool(bool));

        MOCK_CONST_METHOD1(okToFillForm, bool(bool));

        MOCK_CONST_METHOD1(okToAccessibility, bool(bool));

        MOCK_CONST_METHOD1(okToAssemble, bool(bool));

    };



    MockXRef mockXRef;

    PDFDoc pdfDoc;



    PDFDocTest_964() {

        pdfDoc.xref = &mockXRef;

    }

};



TEST_F(PDFDocTest_964, OkToPrint_ReturnsTrue_WhenIgnoreOwnerPWIsFalse_964) {

    EXPECT_CALL(mockXRef, okToPrint(false)).WillOnce(Return(true));

    EXPECT_TRUE(pdfDoc.okToPrint());

}



TEST_F(PDFDocTest_964, OkToPrint_ReturnsFalse_WhenIgnoreOwnerPWIsFalse_964) {

    EXPECT_CALL(mockXRef, okToPrint(false)).WillOnce(Return(false));

    EXPECT_FALSE(pdfDoc.okToPrint());

}



TEST_F(PDFDocTest_964, OkToPrint_ReturnsTrue_WhenIgnoreOwnerPWIsTrue_964) {

    EXPECT_CALL(mockXRef, okToPrint(true)).WillOnce(Return(true));

    EXPECT_TRUE(pdfDoc.okToPrint(true));

}



TEST_F(PDFDocTest_964, OkToPrintHighRes_ReturnsTrue_WhenIgnoreOwnerPWIsFalse_964) {

    EXPECT_CALL(mockXRef, okToPrintHighRes(false)).WillOnce(Return(true));

    EXPECT_TRUE(pdfDoc.okToPrintHighRes());

}



TEST_F(PDFDocTest_964, OkToPrintHighRes_ReturnsFalse_WhenIgnoreOwnerPWIsFalse_964) {

    EXPECT_CALL(mockXRef, okToPrintHighRes(false)).WillOnce(Return(false));

    EXPECT_FALSE(pdfDoc.okToPrintHighRes());

}



TEST_F(PDFDocTest_964, OkToChange_ReturnsTrue_WhenIgnoreOwnerPWIsFalse_964) {

    EXPECT_CALL(mockXRef, okToChange(false)).WillOnce(Return(true));

    EXPECT_TRUE(pdfDoc.okToChange());

}



TEST_F(PDFDocTest_964, OkToCopy_ReturnsFalse_WhenIgnoreOwnerPWIsFalse_964) {

    EXPECT_CALL(mockXRef, okToCopy(false)).WillOnce(Return(false));

    EXPECT_FALSE(pdfDoc.okToCopy());

}



TEST_F(PDFDocTest_964, OkToAddNotes_ReturnsTrue_WhenIgnoreOwnerPWIsFalse_964) {

    EXPECT_CALL(mockXRef, okToAddNotes(false)).WillOnce(Return(true));

    EXPECT_TRUE(pdfDoc.okToAddNotes());

}



TEST_F(PDFDocTest_964, OkToFillForm_ReturnsFalse_WhenIgnoreOwnerPWIsTrue_964) {

    EXPECT_CALL(mockXRef, okToFillForm(true)).WillOnce(Return(false));

    EXPECT_FALSE(pdfDoc.okToFillForm(true));

}



TEST_F(PDFDocTest_964, OkToAccessibility_ReturnsTrue_WhenIgnoreOwnerPWIsFalse_964) {

    EXPECT_CALL(mockXRef, okToAccessibility(false)).WillOnce(Return(true));

    EXPECT_TRUE(pdfDoc.okToAccessibility());

}



TEST_F(PDFDocTest_964, OkToAssemble_ReturnsFalse_WhenIgnoreOwnerPWIsTrue_964) {

    EXPECT_CALL(mockXRef, okToAssemble(true)).WillOnce(Return(false));

    EXPECT_FALSE(pdfDoc.okToAssemble(true));

}
