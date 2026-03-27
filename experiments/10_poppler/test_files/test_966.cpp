#include <gtest/gtest.h>

#include "PDFDoc.h"

#include "XRef.h"



class PDFDocTest_966 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;

    std::unique_ptr<XRef> xref;



    void SetUp() override {

        xref = std::make_unique<XRef>();

        pdfDoc = std::make_unique<PDFDoc>(nullptr, std::nullopt, std::nullopt, nullptr);

        // Assuming that the internal XRef pointer can be set for testing purposes

        pdfDoc->xref = xref.get();

    }

};



TEST_F(PDFDocTest_966, OkToChange_Default_966) {

    EXPECT_EQ(pdfDoc->okToChange(), false);  // Assuming default behavior when no owner password is provided

}



TEST_F(PDFDocTest_966, OkToChange_IgnoreOwnerPW_False_966) {

    EXPECT_EQ(pdfDoc->okToChange(false), false);  // Assuming default behavior when ignoring owner password is set to false

}



TEST_F(PDFDocTest_966, OkToChange_IgnoreOwnerPW_True_966) {

    EXPECT_EQ(pdfDoc->okToChange(true), true);  // Assuming behavior when ignoring owner password is set to true

}
