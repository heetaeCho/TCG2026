#include <gtest/gtest.h>

#include "PDFDoc.h"

#include "XRef.h"



class PDFDocTest_969 : public ::testing::Test {

protected:

    std::unique_ptr<XRef> mockXRef;

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        mockXRef = std::make_unique<XRef>();

        pdfDoc = std::make_unique<PDFDoc>(std::move(mockXRef), std::nullopt, std::nullopt, [](){});

    }

};



TEST_F(PDFDocTest_969, OkToFillForm_DefaultCase_969) {

    EXPECT_CALL(*mockXRef.get(), okToFillForm(false)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(pdfDoc->okToFillForm());

}



TEST_F(PDFDocTest_969, OkToFillForm_IgnoreOwnerPW_False_969) {

    EXPECT_CALL(*mockXRef.get(), okToFillForm(false)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(pdfDoc->okToFillForm(false));

}



TEST_F(PDFDocTest_969, OkToFillForm_IgnoreOwnerPW_True_969) {

    EXPECT_CALL(*mockXRef.get(), okToFillForm(true)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(pdfDoc->okToFillForm(true));

}



TEST_F(PDFDocTest_969, OkToFillForm_MultipleCallsConsistent_969) {

    EXPECT_CALL(*mockXRef.get(), okToFillForm(false)).Times(2).WillRepeatedly(::testing::Return(true));

    EXPECT_TRUE(pdfDoc->okToFillForm());

    EXPECT_TRUE(pdfDoc->okToFillForm());

}



TEST_F(PDFDocTest_969, OkToFillForm_MultipleCallsDifferentParams_969) {

    EXPECT_CALL(*mockXRef.get(), okToFillForm(false)).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockXRef.get(), okToFillForm(true)).WillOnce(::testing::Return(false));

    EXPECT_TRUE(pdfDoc->okToFillForm(false));

    EXPECT_FALSE(pdfDoc->okToFillForm(true));

}
