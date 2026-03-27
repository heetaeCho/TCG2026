#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers are included and the classes/functions are declared



class PopplerAnnotMarkupTest_2081 : public ::testing::Test {

protected:

    struct _PopplerAnnotMarkup poppler_annot_markup;

    PopplerRectangle poppler_rect;



    void SetUp() override {

        // Initialize necessary members if needed

    }



    void TearDown() override {

        // Clean up if needed

    }

};



TEST_F(PopplerAnnotMarkupTest_2081, NormalOperation_2081) {

    AnnotMarkup *annot = static_cast<AnnotMarkup *>(POPPLER_ANNOT(&poppler_annot_markup)->annot.get());

    std::unique_ptr<Annot> popup(new Annot(/* mock parameters */));

    PDFRectangle rect_popup(1.0, 2.0, 3.0, 4.0);

    popup->setRect(rect_popup);

    annot->getPopup() = std::move(popup);



    gboolean result = poppler_annot_markup_get_popup_rectangle(&poppler_annot_markup, &poppler_rect);



    EXPECT_TRUE(result);

    EXPECT_EQ(poppler_rect.x1, 1.0);

    EXPECT_EQ(poppler_rect.y1, 2.0);

    EXPECT_EQ(poppler_rect.x2, 3.0);

    EXPECT_EQ(poppler_rect.y2, 4.0);

}



TEST_F(PopplerAnnotMarkupTest_2081, NoPopupRectangle_2081) {

    AnnotMarkup *annot = static_cast<AnnotMarkup *>(POPPLER_ANNOT(&poppler_annot_markup)->annot.get());

    annot->getPopup() = nullptr;



    gboolean result = poppler_annot_markup_get_popup_rectangle(&poppler_annot_markup, &poppler_rect);



    EXPECT_FALSE(result);

}



TEST_F(PopplerAnnotMarkupTest_2081, NullPopplerAnnot_2081) {

    PopplerAnnotMarkup *null_poppler_annot = nullptr;



    gboolean result = poppler_annot_markup_get_popup_rectangle(null_poppler_annot, &poppler_rect);



    EXPECT_FALSE(result);

}



TEST_F(PopplerAnnotMarkupTest_2081, NullPopplerRect_2081) {

    AnnotMarkup *annot = static_cast<AnnotMarkup *>(POPPLER_ANNOT(&poppler_annot_markup)->annot.get());

    std::unique_ptr<Annot> popup(new Annot(/* mock parameters */));

    PDFRectangle rect_popup(1.0, 2.0, 3.0, 4.0);

    popup->setRect(rect_popup);

    annot->getPopup() = std::move(popup);



    PopplerRectangle *null_poppler_rect = nullptr;



    gboolean result = poppler_annot_markup_get_popup_rectangle(&poppler_annot_markup, null_poppler_rect);



    EXPECT_FALSE(result);

}



TEST_F(PopplerAnnotMarkupTest_2081, BoundaryConditions_2081) {

    AnnotMarkup *annot = static_cast<AnnotMarkup *>(POPPLER_ANNOT(&poppler_annot_markup)->annot.get());

    std::unique_ptr<Annot> popup(new Annot(/* mock parameters */));

    PDFRectangle rect_popup(-1.0, -2.0, 1.0, 2.0);

    popup->setRect(rect_popup);

    annot->getPopup() = std::move(popup);



    gboolean result = poppler_annot_markup_get_popup_rectangle(&poppler_annot_markup, &poppler_rect);



    EXPECT_TRUE(result);

    EXPECT_EQ(poppler_rect.x1, -1.0);

    EXPECT_EQ(poppler_rect.y1, -2.0);

    EXPECT_EQ(poppler_rect.x2, 1.0);

    EXPECT_EQ(poppler_rect.y2, 2.0);

}
