#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.h"

#include "./TestProjects/poppler/glib/poppler-annot-private.h"



using namespace testing;



class PopplerAnnotTextTest_2092 : public Test {

protected:

    void SetUp() override {

        // Create a mock PDFDoc and PDFRectangle for the AnnotText constructor

        PDFDoc* doc = new NiceMock<MockPDFDoc>();

        PDFRectangle rect;

        poppler_annot_text = static_cast<PopplerAnnotText*>(poppler_annot_text_new(doc, &rect));

    }



    void TearDown() override {

        g_object_unref(poppler_annot_text);

    }



    PopplerAnnotText* poppler_annot_text;

};



TEST_F(PopplerAnnotTextTest_2092, SetIcon_NormalOperation_2092) {

    const gchar* icon = "Comment";

    poppler_annot_text_set_icon(poppler_annot_text, icon);

    EXPECT_EQ(std::string(icon), static_cast<AnnotText*>(POPPLER_ANNOT(poppler_annot_text)->annot.get())->getIcon());

}



TEST_F(PopplerAnnotTextTest_2092, SetIcon_EmptyString_2092) {

    const gchar* icon = "";

    poppler_annot_text_set_icon(poppler_annot_text, icon);

    EXPECT_EQ(std::string(icon), static_cast<AnnotText*>(POPPLER_ANNOT(poppler_annot_text)->annot.get())->getIcon());

}



TEST_F(PopplerAnnotTextTest_2092, SetIcon_NullPointer_2092) {

    poppler_annot_text_set_icon(poppler_annot_text, nullptr);

    EXPECT_EQ(std::string(""), static_cast<AnnotText*>(POPPLER_ANNOT(poppler_annot_text)->annot.get())->getIcon());

}
