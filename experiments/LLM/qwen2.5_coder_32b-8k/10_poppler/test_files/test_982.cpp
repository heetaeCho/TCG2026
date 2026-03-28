#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include <memory>



using namespace testing;



class PDFDocTest_982 : public ::testing::Test {

protected:

    std::unique_ptr<GooString> modDate;

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        modDate = std::make_unique<GooString>("D:20231005123456Z");

        pdfDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::nullopt, std::nullopt, [](){});

    }

};



TEST_F(PDFDocTest_982, SetDocInfoModDate_ValidDate_982) {

    pdfDoc->setDocInfoModDate(std::move(modDate));

}



TEST_F(PDFDocTest_982, GetDocInfoModDate_AfterSet_ReturnsSame_982) {

    auto originalModDate = modDate.get();

    pdfDoc->setDocInfoModDate(std::move(modDate));



    auto retrievedModDate = pdfDoc->getDocInfoStringEntry("ModDate").release();

    EXPECT_STREQ(originalModDate->getCString(), retrievedModDate->getCString());

}



TEST_F(PDFDocTest_982, SetDocInfoModDate_NullPointer_982) {

    std::unique_ptr<GooString> nullModDate;

    pdfDoc->setDocInfoModDate(std::move(nullModDate));

}



TEST_F(PDFDocTest_982, GetDocInfoModDate_NotSet_ReturnsNull_982) {

    auto modDate = pdfDoc->getDocInfoStringEntry("ModDate").release();

    EXPECT_EQ(modDate, nullptr);

}
