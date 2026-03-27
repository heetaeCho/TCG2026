#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/CairoFontEngine.h"

#include <memory>



class CairoFontTest_1673 : public ::testing::Test {

protected:

    Ref ref;

    int* cairo_font_face;

    int codeToGID;

    bool substitute;

    bool printing;



    void SetUp() override {

        ref = Ref(42, 0);

        cairo_font_face = new int(123);

        codeToGID = 6789;

        substitute = false;

        printing = true;

    }



    void TearDown() override {

        delete cairo_font_face;

    }

};



TEST_F(CairoFontTest_1673, GetRefReturnsCorrectValue_1673) {

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), substitute, printing);

    EXPECT_EQ(font.getRef(), ref);

}



TEST_F(CairoFontTest_1673, MatchesWithSameRefAndPrinting_1673) {

    Ref otherRef(42, 0);

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), substitute, printing);

    EXPECT_TRUE(font.matches(otherRef, printing));

}



TEST_F(CairoFontTest_1673, MatchesWithDifferentRefAndPrinting_1673) {

    Ref otherRef(43, 0);

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), substitute, printing);

    EXPECT_FALSE(font.matches(otherRef, printing));

}



TEST_F(CairoFontTest_1673, MatchesWithSameRefButDifferentPrinting_1673) {

    Ref otherRef(42, 0);

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), substitute, !printing);

    EXPECT_FALSE(font.matches(otherRef, printing));

}



TEST_F(CairoFontTest_1673, GetFontFaceReturnsCorrectValue_1673) {

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), substitute, printing);

    EXPECT_EQ(font.getFontFace(), cairo_font_face);

}



TEST_F(CairoFontTest_1673, IsSubstituteReturnsFalseWhenNotSubstituted_1673) {

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), false, printing);

    EXPECT_FALSE(font.isSubstitute());

}



TEST_F(CairoFontTest_1673, IsSubstituteReturnsTrueWhenSubstituted_1673) {

    CairoFont font(ref, cairo_font_face, std::move(codeToGID), true, printing);

    EXPECT_TRUE(font.isSubstitute());

}
