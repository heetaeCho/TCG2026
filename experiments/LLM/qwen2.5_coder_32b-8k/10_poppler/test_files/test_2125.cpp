#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



class PopplerFontDescriptionTest_2125 : public ::testing::Test {

protected:

    void SetUp() override {

        font_desc = static_cast<PopplerFontDescription*>(g_malloc0(sizeof(PopplerFontDescription)));

        font_desc->font_name = g_strdup("Arial");

        font_desc->size_pt = 12.0;

        font_desc->stretch = POPPLER_STRETCH_NORMAL;

        font_desc->weight = POPPLER_WEIGHT_NORMAL;

        font_desc->style = POPPLER_STYLE_NORMAL;

    }



    void TearDown() override {

        poppler_font_description_free(font_desc);

    }



    PopplerFontDescription *font_desc;

};



TEST_F(PopplerFontDescriptionTest_2125, FreeReleasesMemory_2125) {

    // Since g_free is used internally, we can't directly verify memory release.

    // But we can test that there are no memory leaks by running valgrind or similar tools.

    // Here, we assume that if the function does not crash, it behaves correctly.

    poppler_font_description_free(font_desc);

    font_desc = nullptr;  // To prevent use-after-free in TearDown

}



TEST_F(PopplerFontDescriptionTest_2125, FreeNullPointer_2125) {

    // Test that freeing a null pointer does not cause issues

    poppler_font_description_free(nullptr);

}
