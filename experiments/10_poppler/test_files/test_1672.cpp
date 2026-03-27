#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CairoFontEngine.h"



class CairoFontTest_1672 : public ::testing::Test {

protected:

    Ref ref;

    int *cairo_font_face;

    int codeToGID;

    bool substitute;

    bool printing;



    void SetUp() override {

        ref.num = 42;

        cairo_font_face = new int(0);

        codeToGID = 123;

        substitute = true;

        printing = false;

    }



    void TearDown() override {

        delete cairo_font_face;

    }

};



TEST_F(CairoFontTest_1672, isSubstitute_ReturnsTrueWhenSet_1672) {

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), substitute, printing);

    EXPECT_TRUE(font.isSubstitute());

}



TEST_F(CairoFontTest_1672, isSubstitute_ReturnsFalseWhenNotSet_1672) {

    substitute = false;

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), substitute, printing);

    EXPECT_FALSE(font.isSubstitute());

}
