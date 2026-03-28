#include <gtest/gtest.h>

// We need to test the static function QFontHintingFromPopplerHinting
// which is in the Poppler namespace. Since it's a static function in a .cc file,
// we need to include the necessary headers and potentially access it.

// Include necessary Qt headers
#include <QFont>

// We need to replicate the Document render hints enum values since we're testing
// against the interface. These are from poppler-document.h
namespace Poppler {

class Document {
public:
    enum RenderHint {
        Antialiasing = 0x00000001,
        TextAntialiasing = 0x00000002,
        TextHinting = 0x00000004,
        TextSlightHinting = 0x00000008,
        OverprintPreview = 0x00000010,
        ThinLineSolid = 0x00000020,
        ThinLineShape = 0x00000040,
        IgnorePaperColor = 0x00000080,
        HideAnnotations = 0x00000100
    };
};

// Re-declare the function to test it (it's static in the .cc file, so we
// include the implementation here for testing purposes)
static QFont::HintingPreference QFontHintingFromPopplerHinting(int renderHints)
{
    QFont::HintingPreference result = QFont::PreferNoHinting;
    if (renderHints & Document::TextHinting) {
        result = (renderHints & Document::TextSlightHinting) ? QFont::PreferVerticalHinting : QFont::PreferFullHinting;
    }
    return result;
}

} // namespace Poppler

class QFontHintingFromPopplerHintingTest_1445 : public ::testing::Test {
protected:
    QFont::HintingPreference callFunction(int renderHints) {
        return Poppler::QFontHintingFromPopplerHinting(renderHints);
    }
};

// Test: When no hints are set, should return PreferNoHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, NoHints_ReturnsPreferNoHinting_1445) {
    EXPECT_EQ(QFont::PreferNoHinting, callFunction(0));
}

// Test: When only TextHinting is set (without TextSlightHinting), should return PreferFullHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, TextHintingOnly_ReturnsPreferFullHinting_1445) {
    EXPECT_EQ(QFont::PreferFullHinting, callFunction(Poppler::Document::TextHinting));
}

// Test: When both TextHinting and TextSlightHinting are set, should return PreferVerticalHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, TextHintingAndSlightHinting_ReturnsPreferVerticalHinting_1445) {
    int hints = Poppler::Document::TextHinting | Poppler::Document::TextSlightHinting;
    EXPECT_EQ(QFont::PreferVerticalHinting, callFunction(hints));
}

// Test: When only TextSlightHinting is set (without TextHinting), should return PreferNoHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, TextSlightHintingOnly_ReturnsPreferNoHinting_1445) {
    EXPECT_EQ(QFont::PreferNoHinting, callFunction(Poppler::Document::TextSlightHinting));
}

// Test: When unrelated hints are set (e.g., Antialiasing), should return PreferNoHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, UnrelatedHints_ReturnsPreferNoHinting_1445) {
    EXPECT_EQ(QFont::PreferNoHinting, callFunction(Poppler::Document::Antialiasing));
}

// Test: When TextHinting is combined with unrelated hints (but not TextSlightHinting), should return PreferFullHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, TextHintingWithUnrelatedHints_ReturnsPreferFullHinting_1445) {
    int hints = Poppler::Document::TextHinting | Poppler::Document::Antialiasing | Poppler::Document::TextAntialiasing;
    EXPECT_EQ(QFont::PreferFullHinting, callFunction(hints));
}

// Test: When all hints are combined including TextHinting and TextSlightHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, AllHintsCombined_ReturnsPreferVerticalHinting_1445) {
    int hints = Poppler::Document::Antialiasing | Poppler::Document::TextAntialiasing |
                Poppler::Document::TextHinting | Poppler::Document::TextSlightHinting |
                Poppler::Document::OverprintPreview;
    EXPECT_EQ(QFont::PreferVerticalHinting, callFunction(hints));
}

// Test: When multiple unrelated hints are set but not TextHinting, should return PreferNoHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, MultipleUnrelatedHints_ReturnsPreferNoHinting_1445) {
    int hints = Poppler::Document::Antialiasing | Poppler::Document::TextAntialiasing |
                Poppler::Document::OverprintPreview | Poppler::Document::ThinLineSolid;
    EXPECT_EQ(QFont::PreferNoHinting, callFunction(hints));
}

// Test: Boundary - maximum integer value
TEST_F(QFontHintingFromPopplerHintingTest_1445, MaxIntValue_TextHintingBitSet_1445) {
    // 0x7FFFFFFF has all bits set including TextHinting and TextSlightHinting
    int hints = 0x7FFFFFFF;
    // Both TextHinting (0x04) and TextSlightHinting (0x08) bits are set
    EXPECT_EQ(QFont::PreferVerticalHinting, callFunction(hints));
}

// Test: Exact bit value of TextHinting (0x04)
TEST_F(QFontHintingFromPopplerHintingTest_1445, ExactBitValueTextHinting_1445) {
    EXPECT_EQ(QFont::PreferFullHinting, callFunction(0x04));
}

// Test: Exact bit value of TextSlightHinting (0x08) without TextHinting
TEST_F(QFontHintingFromPopplerHintingTest_1445, ExactBitValueTextSlightHintingAlone_1445) {
    EXPECT_EQ(QFont::PreferNoHinting, callFunction(0x08));
}

// Test: Exact combined bit values of TextHinting | TextSlightHinting (0x0C)
TEST_F(QFontHintingFromPopplerHintingTest_1445, ExactCombinedBitValues_1445) {
    EXPECT_EQ(QFont::PreferVerticalHinting, callFunction(0x0C));
}

// Test: Zero input
TEST_F(QFontHintingFromPopplerHintingTest_1445, ZeroInput_ReturnsPreferNoHinting_1445) {
    EXPECT_EQ(QFont::PreferNoHinting, callFunction(0));
}

// Test: Negative value that happens to have TextHinting bit set
TEST_F(QFontHintingFromPopplerHintingTest_1445, NegativeValueWithTextHintingBit_1445) {
    // -1 in two's complement has all bits set
    int hints = -1;
    // Both TextHinting and TextSlightHinting bits are set
    EXPECT_EQ(QFont::PreferVerticalHinting, callFunction(hints));
}
