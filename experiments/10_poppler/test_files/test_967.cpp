#include <gtest/gtest.h>

#include "PDFDoc.h"

#include "XRef.h"



class PDFDocTest_967 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize PDFDoc with necessary parameters if required

        pdfDoc = std::make_unique<PDFDoc>(nullptr, std::nullopt, std::nullopt, nullptr);

    }



    std::unique_ptr<PDFDoc> pdfDoc;

};



TEST_F(PDFDocTest_967, OkToCopy_Default_967) {

    EXPECT_EQ(pdfDoc->okToCopy(), false);

}



TEST_F(PDFDocTest_967, OkToCopy_IgnoreOwnerPW_False_967) {

    EXPECT_EQ(pdfDoc->okToCopy(false), false);

}



TEST_F(PDFDocTest_967, OkToCopy_IgnoreOwnerPW_True_967) {

    EXPECT_EQ(pdfDoc->okToCopy(true), false);

}

```


