#include <gtest/gtest.h>

#include "Annot.h"



class AnnotFreeTextTest_817 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming PDFDoc and PDFRectangle are properly mockable or can be instantiated for testing.

        auto doc = new PDFDoc();

        auto rect = new PDFRectangle(0, 0, 100, 100);

        annotFreeText = std::make_unique<AnnotFreeText>(doc, rect);

    }



    void TearDown() override {

        // Clean up if necessary

        annotFreeText.reset();

    }



    std::unique_ptr<AnnotFreeText> annotFreeText;

};



TEST_F(AnnotFreeTextTest_817, GetQuadding_DefaultValue_817) {

    EXPECT_EQ(annotFreeText->getQuadding(), VariableTextQuadding::leftJustify);

}



TEST_F(AnnotFreeTextTest_817, SetAndGetQuadding_NormalOperation_817) {

    annotFreeText->setQuadding(VariableTextQuadding::centered);

    EXPECT_EQ(annotFreeText->getQuadding(), VariableTextQuadding::centered);



    annotFreeText->setQuadding(VariableTextQuadding::rightJustify);

    EXPECT_EQ(annotFreeText->getQuadding(), VariableTextQuadding::rightJustify);

}



TEST_F(AnnotFreeTextTest_817, SetAndGetStyleString_NormalOperation_817) {

    auto styleString = std::make_unique<GooString>("Sample Style");

    annotFreeText->setStyleString(styleString.release());

    EXPECT_STREQ(annotFreeText->getStyleString()->c_str(), "Sample Style");



    auto newStyleString = std::make_unique<GooString>("New Sample Style");

    annotFreeText->setStyleString(newStyleString.release());

    EXPECT_STREQ(annotFreeText->getStyleString()->c_str(), "New Sample Style");

}



TEST_F(AnnotFreeTextTest_817, SetAndGetCalloutLine_NormalOperation_817) {

    auto calloutLine = std::make_unique<AnnotCalloutLine>(std::vector<GooPoint>{{0, 0}, {50, 50}});

    annotFreeText->setCalloutLine(std::move(calloutLine));

    EXPECT_EQ(annotFreeText->getCalloutLine()->points.size(), 2);

    EXPECT_EQ(annotFreeText->getCalloutLine()->points[0], GooPoint{0, 0});

    EXPECT_EQ(annotFreeText->getCalloutLine()->points[1], GooPoint{50, 50});



    auto newCalloutLine = std::make_unique<AnnotCalloutLine>(std::vector<GooPoint>{{10, 10}, {60, 60}});

    annotFreeText->setCalloutLine(std::move(newCalloutLine));

    EXPECT_EQ(annotFreeText->getCalloutLine()->points.size(), 2);

    EXPECT_EQ(annotFreeText->getCalloutLine()->points[0], GooPoint{10, 10});

    EXPECT_EQ(annotFreeText->getCalloutLine()->points[1], GooPoint{60, 60});

}



TEST_F(AnnotFreeTextTest_817, SetAndGetIntent_NormalOperation_817) {

    annotFreeText->setIntent(AnnotFreeTextIntent::freeTextTypewriter);

    EXPECT_EQ(annotFreeText->getIntent(), AnnotFreeTextIntent::freeTextTypewriter);



    annotFreeText->setIntent(AnnotFreeTextIntent::freeTextCallout);

    EXPECT_EQ(annotFreeText->getIntent(), AnnotFreeTextIntent::freeTextCallout);

}
