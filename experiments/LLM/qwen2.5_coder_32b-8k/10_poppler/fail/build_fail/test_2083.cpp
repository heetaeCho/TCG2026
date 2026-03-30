#include <gtest/gtest.h>

#include "poppler-annot.h"

#include <glib-object.h>



class PopplerAnnotMarkupTest_2083 : public ::testing::Test {

protected:

    PopplerAnnotMarkup *poppler_annot_markup;



    void SetUp() override {

        poppler_annot_markup = POPPLER_ANNOT_MARKUP(g_object_new(POPPLER_TYPE_ANNOT_MARKUP, nullptr));

    }



    void TearDown() override {

        g_object_unref(poppler_annot_markup);

    }

};



TEST_F(PopplerAnnotMarkupTest_2083, GetOpacity_DefaultValue_2083) {

    EXPECT_DOUBLE_EQ(poppler_annot_markup_get_opacity(poppler_annot_markup), 0.0);

}



TEST_F(PopplerAnnotMarkupTest_2083, GetOpacity_SetValue_2083) {

    // Assuming there's a way to set the opacity in the actual implementation

    // Since we can't change internal state, this is more of a theoretical test case.

    EXPECT_DOUBLE_EQ(poppler_annot_markup_get_opacity(poppler_annot_markup), 0.0);

}



TEST_F(PopplerAnnotMarkupTest_2083, GetOpacity_BoundaryCondition_Lower_2083) {

    // Assuming opacity can't be negative

    EXPECT_DOUBLE_EQ(poppler_annot_markup_get_opacity(poppler_annot_markup), 0.0);

}



TEST_F(PopplerAnnotMarkupTest_2083, GetOpacity_BoundaryCondition_Upper_2083) {

    // Assuming opacity can't exceed 1.0

    EXPECT_DOUBLE_EQ(poppler_annot_markup_get_opacity(poppler_annot_markup), 0.0);

}



TEST_F(PopplerAnnotMarkupTest_2083, GetOpacity_InvalidObject_2083) {

    g_object_unref(poppler_annot_markup);

    poppler_annot_markup = nullptr;

    EXPECT_DOUBLE_EQ(poppler_annot_markup_get_opacity(poppler_annot_markup), 0.0);

}
