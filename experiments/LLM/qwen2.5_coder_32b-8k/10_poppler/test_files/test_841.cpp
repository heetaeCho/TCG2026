#include <gtest/gtest.h>

#include "Annot.h"



class AnnotStampTest_841 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    std::unique_ptr<AnnotStamp> annot_stamp;



    void SetUp() override {

        doc = new PDFDoc();

        annot_stamp = std::make_unique<AnnotStamp>(doc, &rect);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(AnnotStampTest_841, InitialIconIsEmpty_841) {

    EXPECT_EQ(annot_stamp->getIcon(), "");

}



TEST_F(AnnotStampTest_841, SetIconAndGetIcon_841) {

    annot_stamp->setIcon("test_icon");

    EXPECT_EQ(annot_stamp->getIcon(), "test_icon");

}



TEST_F(AnnotStampTest_841, SetCustomImageUniquePtr_841) {

    auto image_helper = std::make_unique<AnnotStampImageHelper>();

    EXPECT_NO_THROW(annot_stamp->setCustomImage(std::move(image_helper)));

}



TEST_F(AnnotStampTest_841, SetCustomImageInt_841) {

    int image_helper_id = 1;

    EXPECT_NO_THROW(annot_stamp->setCustomImage(std::move(image_helper_id)));

}
