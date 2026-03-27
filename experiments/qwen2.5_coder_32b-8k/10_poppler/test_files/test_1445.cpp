#include <gtest/gtest.h>

#include <poppler/qt5/src/poppler-page.cc>



class QFontHintingFromPopplerHintingTest_1445 : public ::testing::Test {

protected:

    // You can set up any common state here if necessary.

};



TEST_F(QFontHintingFromPopplerHintingTest_1445, NoHintsProvided_1445) {

    int renderHints = 0;

    QFont::HintingPreference result = Poppler::QFontHintingFromPopplerHinting(renderHints);

    EXPECT_EQ(result, QFont::PreferNoHinting);

}



TEST_F(QFontHintingFromPopplerHintingTest_1445, TextSlightHintingProvided_1445) {

    int renderHints = Document::TextHinting | Document::TextSlightHinting;

    QFont::HintingPreference result = Poppler::QFontHintingFromPopplerHinting(renderHints);

    EXPECT_EQ(result, QFont::PreferVerticalHinting);

}



TEST_F(QFontHintingFromPopplerHintingTest_1445, TextFullHintingProvided_1445) {

    int renderHints = Document::TextHinting;

    QFont::HintingPreference result = Poppler::QFontHintingFromPopplerHinting(renderHints);

    EXPECT_EQ(result, QFont::PreferFullHinting);

}



TEST_F(QFontHintingFromPopplerHintingTest_1445, OnlyTextSlightHintingIgnoredWithoutTextHinting_1445) {

    int renderHints = Document::TextSlightHinting;

    QFont::HintingPreference result = Poppler::QFontHintingFromPopplerHinting(renderHints);

    EXPECT_EQ(result, QFont::PreferNoHinting);

}



TEST_F(QFontHintingFromPopplerHintingTest_1445, BothHintsSetDefaultsToFullHinting_1445) {

    int renderHints = Document::TextHinting | Document::TextSlightHinting;

    QFont::HintingPreference result = Poppler::QFontHintingFromPopplerHinting(renderHints);

    EXPECT_EQ(result, QFont::PreferVerticalHinting);

}
