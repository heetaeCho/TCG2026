#include <gtest/gtest.h>

#include "Annot.h"



class AnnotFreeTextTest_818 : public ::testing::Test {

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



TEST_F(AnnotFreeTextTest_818, GetStyleString_ReturnsNullPointerByDefault_818) {

    EXPECT_EQ(annot->getStyleString(), nullptr);

}



TEST_F(AnnotFreeTextTest_818, SetAndGetStyleString_NormalOperation_818) {

    auto styleStr = std::make_unique<GooString>("FreetextStyle");

    annot->setStyleString(styleStr.get());

    EXPECT_STREQ(annot->getStyleString()->c_str(), "FreetextStyle");

}



TEST_F(AnnotFreeTextTest_818, SetAndGetStyleString_BoundaryConditionEmptyString_818) {

    auto styleStr = std::make_unique<GooString>("");

    annot->setStyleString(styleStr.get());

    EXPECT_STREQ(annot->getStyleString()->c_str(), "");

}



TEST_F(AnnotFreeTextTest_818, SetAndGetStyleString_BoundaryConditionLongString_818) {

    auto styleStr = std::make_unique<GooString>("A very long string that should not cause any issues in setting and getting the style string of AnnotFreeText");

    annot->setStyleString(styleStr.get());

    EXPECT_STREQ(annot->getStyleString()->c_str(), "A very long string that should not cause any issues in setting and getting the style string of AnnotFreeText");

}
