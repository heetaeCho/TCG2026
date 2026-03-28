#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-annot.h>



class PopplerAnnotMarkupTest_2075 : public ::testing::Test {

protected:

    PopplerAnnotMarkup *poppler_annot;



    void SetUp() override {

        poppler_annot = POPPLER_ANNOT_MARKUP(g_object_new(POPPLER_TYPE_ANNOT_MARKUP, nullptr));

    }



    void TearDown() override {

        g_object_unref(poppler_annot);

    }

};



TEST_F(PopplerAnnotMarkupTest_2075, GetLabel_ReturnsNull_WhenNoLabelSet_2075) {

    gchar *label = poppler_annot_markup_get_label(poppler_annot);

    EXPECT_EQ(label, nullptr);

}



TEST_F(PopplerAnnotMarkupTest_2075, GetLabel_ReturnsCorrectLabel_WhenLabelSet_2075) {

    std::unique_ptr<GooString> label(new GooString("Test Label"));

    static_cast<AnnotMarkup *>(POPPLER_ANNOT(poppler_annot)->annot.get())->setLabel(std::move(label));

    gchar *result = poppler_annot_markup_get_label(poppler_annot);

    EXPECT_STREQ(result, "Test Label");

    g_free(result);

}



TEST_F(PopplerAnnotMarkupTest_2075, GetLabel_HandlesEmptyLabel_2075) {

    std::unique_ptr<GooString> label(new GooString(""));

    static_cast<AnnotMarkup *>(POPPLER_ANNOT(poppler_annot)->annot.get())->setLabel(std::move(label));

    gchar *result = poppler_annot_markup_get_label(poppler_annot);

    EXPECT_STREQ(result, "");

    g_free(result);

}



TEST_F(PopplerAnnotMarkupTest_2075, GetLabel_ReturnsNull_WhenInvalidObjectPassed_2075) {

    gchar *label = poppler_annot_markup_get_label(nullptr);

    EXPECT_EQ(label, nullptr);

}
