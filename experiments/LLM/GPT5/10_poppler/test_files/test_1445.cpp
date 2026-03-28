#include <gtest/gtest.h>
#include <QFont>
#include "poppler-page.h"

namespace Poppler {

class PopplerPageTest_1445 : public ::testing::Test {
protected:
    // You may include setup or teardown code if necessary, but for now it's empty.
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerPageTest_1445, TestQFontHintingFromPopplerHinting_NormalTextHinting_1445) {
    // Test normal behavior with text hinting
    int renderHints = Document::TextHinting;
    QFont::HintingPreference result = QFontHintingFromPopplerHinting(renderHints);
    EXPECT_EQ(result, QFont::PreferNoHinting);  // As per the provided logic, this should be PreferNoHinting
}

TEST_F(PopplerPageTest_1445, TestQFontHintingFromPopplerHinting_SlightTextHinting_1445) {
    // Test behavior with slight text hinting
    int renderHints = Document::TextHinting | Document::TextSlightHinting;
    QFont::HintingPreference result = QFontHintingFromPopplerHinting(renderHints);
    EXPECT_EQ(result, QFont::PreferVerticalHinting);  // Expecting PreferVerticalHinting due to slight hinting
}

TEST_F(PopplerPageTest_1445, TestQFontHintingFromPopplerHinting_FullTextHinting_1445) {
    // Test behavior with full text hinting
    int renderHints = Document::TextHinting | Document::TextFullHinting;
    QFont::HintingPreference result = QFontHintingFromPopplerHinting(renderHints);
    EXPECT_EQ(result, QFont::PreferFullHinting);  // Expecting PreferFullHinting due to full hinting
}

TEST_F(PopplerPageTest_1445, TestQFontHintingFromPopplerHinting_NoTextHinting_1445) {
    // Test behavior when there is no text hinting
    int renderHints = 0;
    QFont::HintingPreference result = QFontHintingFromPopplerHinting(renderHints);
    EXPECT_EQ(result, QFont::PreferNoHinting);  // Expecting PreferNoHinting due to no hinting
}

TEST_F(PopplerPageTest_1445, TestQFontHintingFromPopplerHinting_InvalidRenderHints_1445) {
    // Test for an invalid render hint value (this is a boundary case)
    int renderHints = 999;  // Arbitrary invalid hint value
    QFont::HintingPreference result = QFontHintingFromPopplerHinting(renderHints);
    EXPECT_EQ(result, QFont::PreferNoHinting);  // Expecting PreferNoHinting as a default fallback
}

}  // namespace Poppler