#include <gtest/gtest.h>

#include "poppler-annot.cc"

#include "poppler-private.h"



class PopplerAnnotTest_2072 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot = new PopplerAnnot();

        poppler_annot->annot = std::make_shared<Annot>();

    }



    void TearDown() override {

        delete poppler_annot;

    }



    PopplerAnnot* poppler_annot;

};



TEST_F(PopplerAnnotTest_2072, GetCropboxReturnsNonNullPointer_2072) {

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox(poppler_annot);

    EXPECT_NE(cropbox, nullptr);

}



TEST_F(PopplerAnnotTest_2072, GetCropboxConsistentWithGetCropboxAndPage_2072) {

    const PDFRectangle* cropbox1 = _poppler_annot_get_cropbox(poppler_annot);

    const PDFRectangle* cropbox2 = _poppler_annot_get_cropbox_and_page(poppler_annot, nullptr);

    EXPECT_EQ(cropbox1, cropbox2);

}



TEST_F(PopplerAnnotTest_2072, GetCropboxWithNullPopplerAnnotReturnsNull_2072) {

    const PDFRectangle* cropbox = _poppler_annot_get_cropbox(nullptr);

    EXPECT_EQ(cropbox, nullptr);

}
