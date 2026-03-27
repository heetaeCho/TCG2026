#include <gtest/gtest.h>

#include "poppler/glib/poppler-annot.h"



class PopplerAnnotTest_2062 : public ::testing::Test {

protected:

    std::shared_ptr<Annot> annot;

    PopplerAnnot* poppler_annot;



    void SetUp() override {

        annot = std::make_shared<Annot>();

        poppler_annot = reinterpret_cast<PopplerAnnot*>(malloc(sizeof(PopplerAnnot)));

        poppler_annot->annot = annot;

    }



    void TearDown() override {

        free(poppler_annot);

    }

};



TEST_F(PopplerAnnotTest_2062, GetTextAnnotationType_2062) {

    annot->type = Annot::typeText;

    EXPECT_EQ(POPPLER_ANNOT_TEXT, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetLinkAnnotationType_2062) {

    annot->type = Annot::typeLink;

    EXPECT_EQ(POPPLER_ANNOT_LINK, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetFreeTextAnnotationType_2062) {

    annot->type = Annot::typeFreeText;

    EXPECT_EQ(POPPLER_ANNOT_FREE_TEXT, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetLineAnnotationType_2062) {

    annot->type = Annot::typeLine;

    EXPECT_EQ(POPPLER_ANNOT_LINE, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetSquareAnnotationType_2062) {

    annot->type = Annot::typeSquare;

    EXPECT_EQ(POPPLER_ANNOT_SQUARE, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetCircleAnnotationType_2062) {

    annot->type = Annot::typeCircle;

    EXPECT_EQ(POPPLER_ANNOT_CIRCLE, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetPolygonAnnotationType_2062) {

    annot->type = Annot::typePolygon;

    EXPECT_EQ(POPPLER_ANNOT_POLYGON, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetPolyLineAnnotationType_2062) {

    annot->type = Annot::typePolyLine;

    EXPECT_EQ(POPPLER_ANNOT_POLY_LINE, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetHighlightAnnotationType_2062) {

    annot->type = Annot::typeHighlight;

    EXPECT_EQ(POPPLER_ANNOT_HIGHLIGHT, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetUnderlineAnnotationType_2062) {

    annot->type = Annot::typeUnderline;

    EXPECT_EQ(POPPLER_ANNOT_UNDERLINE, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetSquigglyAnnotationType_2062) {

    annot->type = Annot::typeSquiggly;

    EXPECT_EQ(POPPLER_ANNOT_SQUIGGLY, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetStrikeOutAnnotationType_2062) {

    annot->type = Annot::typeStrikeOut;

    EXPECT_EQ(POPPLER_ANNOT_STRIKE_OUT, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetStampAnnotationType_2062) {

    annot->type = Annot::typeStamp;

    EXPECT_EQ(POPPLER_ANNOT_STAMP, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetCaretAnnotationType_2062) {

    annot->type = Annot::typeCaret;

    EXPECT_EQ(POPPLER_ANNOT_CARET, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetInkAnnotationType_2062) {

    annot->type = Annot::typeInk;

    EXPECT_EQ(POPPLER_ANNOT_INK, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetPopupAnnotationType_2062) {

    annot->type = Annot::typePopup;

    EXPECT_EQ(POPPLER_ANNOT_POPUP, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetFileAttachmentAnnotationType_2062) {

    annot->type = Annot::typeFileAttachment;

    EXPECT_EQ(POPPLER_ANNOT_FILE_ATTACHMENT, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetSoundAnnotationType_2062) {

    annot->type = Annot::typeSound;

    EXPECT_EQ(POPPLER_ANNOT_SOUND, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetMovieAnnotationType_2062) {

    annot->type = Annot::typeMovie;

    EXPECT_EQ(POPPLER_ANNOT_MOVIE, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetWidgetAnnotationType_2062) {

    annot->type = Annot::typeWidget;

    EXPECT_EQ(POPPLER_ANNOT_WIDGET, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetScreenAnnotationType_2062) {

    annot->type = Annot::typeScreen;

    EXPECT_EQ(POPPLER_ANNOT_SCREEN, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetPrinterMarkAnnotationType_2062) {

    annot->type = Annot::typePrinterMark;

    EXPECT_EQ(POPPLER_ANNOT_PRINTER_MARK, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetTrapNetAnnotationType_2062) {

    annot->type = Annot::typeTrapNet;

    EXPECT_EQ(POPPLER_ANNOT_TRAP_NET, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetWatermarkAnnotationType_2062) {

    annot->type = Annot::typeWatermark;

    EXPECT_EQ(POPPLER_ANNOT_WATERMARK, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, Get3DAnnotationType_2062) {

    annot->type = Annot::type3D;

    EXPECT_EQ(POPPLER_ANNOT_3D, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetUnknownAnnotationType_2062) {

    annot->type = Annot::typeUnknown;

    EXPECT_EQ(POPPLER_ANNOT_UNKNOWN, poppler_annot_get_annot_type(poppler_annot));

}



TEST_F(PopplerAnnotTest_2062, GetUnsupportedAnnotationType_2062) {

    annot->type = static_cast<Annot::AnnotSubtype>(100); // Assuming 100 is an unsupported type

    EXPECT_EQ(POPPLER_ANNOT_UNKNOWN, poppler_annot_get_annot_type(poppler_annot));

}



TEST(PopplerAnnotInvalidTest_2062, InvalidPointer_2062) {

    EXPECT_EQ(POPPLER_ANNOT_UNKNOWN, poppler_annot_get_annot_type(nullptr));

}
