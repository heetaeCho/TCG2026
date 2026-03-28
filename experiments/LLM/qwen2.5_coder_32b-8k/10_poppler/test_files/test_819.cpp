#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotFreeTextTest_819 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> doc;

    std::unique_ptr<PDFRectangle> rect;

    std::unique_ptr<AnnotFreeText> annot;



    void SetUp() override {

        doc = std::make_unique<PDFDoc>();

        rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);

        annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    }

};



TEST_F(AnnotFreeTextTest_819, GetCalloutLine_ReturnsNullptr_WhenNotSet_819) {

    EXPECT_EQ(annot->getCalloutLine(), nullptr);

}



TEST_F(AnnotFreeTextTest_819, SetAndGetCalloutLine_819) {

    auto calloutLine = std::make_unique<AnnotCalloutLine>();

    AnnotCalloutLine* rawPtr = calloutLine.get();

    annot->setCalloutLine(std::move(calloutLine));

    EXPECT_EQ(annot->getCalloutLine(), rawPtr);

}



TEST_F(AnnotFreeTextTest_819, SetAndGetCalloutLine_MultipleTimes_819) {

    auto firstCalloutLine = std::make_unique<AnnotCalloutLine>();

    AnnotCalloutLine* firstRawPtr = firstCalloutLine.get();

    annot->setCalloutLine(std::move(firstCalloutLine));

    EXPECT_EQ(annot->getCalloutLine(), firstRawPtr);



    auto secondCalloutLine = std::make_unique<AnnotCalloutLine>();

    AnnotCalloutLine* secondRawPtr = secondCalloutLine.get();

    annot->setCalloutLine(std::move(secondCalloutLine));

    EXPECT_EQ(annot->getCalloutLine(), secondRawPtr);

}



TEST_F(AnnotFreeTextTest_819, SetCalloutLine_ToNullptr_819) {

    auto calloutLine = std::make_unique<AnnotCalloutLine>();

    annot->setCalloutLine(std::move(calloutLine));

    EXPECT_NE(annot->getCalloutLine(), nullptr);



    annot->setCalloutLine(nullptr);

    EXPECT_EQ(annot->getCalloutLine(), nullptr);

}
