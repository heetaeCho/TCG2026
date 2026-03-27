#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"

#include "GooString.h"



class PDFDocTest_981 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        // Create a minimal setup for PDFDoc

        auto fileName = std::make_unique<GooString>("dummy.pdf");

        pdfDoc = std::make_unique<PDFDoc>(std::move(fileName), std::nullopt, std::nullopt, [](){});

    }

};



TEST_F(PDFDocTest_981, SetDocInfoCreatDate_NormalOperation_981) {

    auto createDate = std::make_unique<GooString>("D:20231005142356+01'00'");

    pdfDoc->setDocInfoCreatDate(std::move(createDate));

}



TEST_F(PDFDocTest_981, SetDocInfoCreatDate_EmptyString_981) {

    auto createDate = std::make_unique<GooString>("");

    pdfDoc->setDocInfoCreatDate(std::move(createDate));

}



TEST_F(PDFDocTest_981, SetDocInfoCreatDate_NullPointer_981) {

    // This is not directly testable since the method expects a unique_ptr and nullptr cannot be moved.

    // If this scenario is possible in your codebase, you need to adjust how you handle null inputs.

}



TEST_F(PDFDocTest_981, SetDocInfoCreatDate_InvalidDateFormat_981) {

    auto createDate = std::make_unique<GooString>("2023-10-05");

    pdfDoc->setDocInfoCreatDate(std::move(createDate));

}
