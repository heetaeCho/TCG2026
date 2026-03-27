#include <gtest/gtest.h>

#include "poppler/Annot.h"

#include "poppler/AnnotColor.h"



class AnnotLineTest_826 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    std::unique_ptr<AnnotLine> annotLine;



    void SetUp() override {

        doc = new PDFDoc();

        annotLine.reset(new AnnotLine(doc, &rect));

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(AnnotLineTest_826, GetInteriorColor_Default_ReturnsNullptr_826) {

    EXPECT_EQ(annotLine->getInteriorColor(), nullptr);

}



TEST_F(AnnotLineTest_826, SetAndGetInteriorColor_ValidColor_ReturnsSameColor_826) {

    auto color = std::make_unique<AnnotColor>();

    annotLine->setInteriorColor(std::move(color));

    EXPECT_NE(annotLine->getInteriorColor(), nullptr);

}



TEST_F(AnnotLineTest_826, SetAndGetInteriorColor_MultipleTimes_ReturnsLatestColor_826) {

    auto color1 = std::make_unique<AnnotColor>();

    auto color2 = std::make_unique<AnnotColor>();

    annotLine->setInteriorColor(std::move(color1));

    annotLine->setInteriorColor(std::move(color2));

    EXPECT_NE(annotLine->getInteriorColor(), nullptr);

}



TEST_F(AnnotLineTest_826, SetInteriorColor_Nullptr_DoesNotCrash_826) {

    auto color = std::make_unique<AnnotColor>();

    annotLine->setInteriorColor(std::move(color));

    annotLine->setInteriorColor(nullptr);

    EXPECT_EQ(annotLine->getInteriorColor(), nullptr);

}
