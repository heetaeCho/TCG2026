#include <gtest/gtest.h>

#include "Annot.h"



class AnnotTextTest_807 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    AnnotText* annotText;



    void SetUp() override {

        doc = new PDFDoc();

        annotText = new AnnotText(doc, &rect);

    }



    void TearDown() override {

        delete annotText;

        delete doc;

    }

};



TEST_F(AnnotTextTest_807, GetIcon_DefaultValue_807) {

    // Default value of icon should be an empty string

    EXPECT_EQ(annotText->getIcon(), "");

}



TEST_F(AnnotTextTest_807, SetAndGetIcon_NormalOperation_807) {

    // Setting and getting the icon should work as expected

    annotText->setIcon("Comment");

    EXPECT_EQ(annotText->getIcon(), "Comment");

}



TEST_F(AnnotTextTest_807, SetAndGetIcon_EmptyString_807) {

    // Setting an empty string as icon should be handled correctly

    annotText->setIcon("");

    EXPECT_EQ(annotText->getIcon(), "");

}



TEST_F(AnnotTextTest_807, SetAndGetIcon_SpecialCharacters_807) {

    // Setting special characters as icon should be handled correctly

    annotText->setIcon("!@#$%^&*()_+");

    EXPECT_EQ(annotText->getIcon(), "!@#$%^&*()_+");

}
