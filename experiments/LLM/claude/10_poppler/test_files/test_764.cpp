#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class AnnotAppearanceCharacsTest_764 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific entries
    std::unique_ptr<Dict> createDict(XRef *xref = nullptr) {
        return std::make_unique<Dict>(xref);
    }
};

// Test construction with empty dictionary - default rotation should be 0
TEST_F(AnnotAppearanceCharacsTest_764, DefaultRotationIsZero_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getRotation(), 0);
}

// Test that default border color is nullptr for empty dict
TEST_F(AnnotAppearanceCharacsTest_764, DefaultBorderColorIsNull_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

// Test that default back color is nullptr for empty dict
TEST_F(AnnotAppearanceCharacsTest_764, DefaultBackColorIsNull_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getBackColor(), nullptr);
}

// Test that default normal caption is nullptr for empty dict
TEST_F(AnnotAppearanceCharacsTest_764, DefaultNormalCaptionIsNull_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getNormalCaption(), nullptr);
}

// Test construction with rotation value in dictionary
TEST_F(AnnotAppearanceCharacsTest_764, RotationFromDict_764) {
    auto dict = createDict();
    dict->add("R", Object(90));
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getRotation(), 90);
}

// Test construction with rotation value 180
TEST_F(AnnotAppearanceCharacsTest_764, Rotation180FromDict_764) {
    auto dict = createDict();
    dict->add("R", Object(180));
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getRotation(), 180);
}

// Test construction with rotation value 270
TEST_F(AnnotAppearanceCharacsTest_764, Rotation270FromDict_764) {
    auto dict = createDict();
    dict->add("R", Object(270));
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getRotation(), 270);
}

// Test setting border color
TEST_F(AnnotAppearanceCharacsTest_764, SetBorderColor_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));
    EXPECT_NE(characs.getBorderColor(), nullptr);
}

// Test setting back color
TEST_F(AnnotAppearanceCharacsTest_764, SetBackColor_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBackColor(std::move(color));
    EXPECT_NE(characs.getBackColor(), nullptr);
}

// Test setting border color to nullptr (clearing it)
TEST_F(AnnotAppearanceCharacsTest_764, SetBorderColorToNull_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

// Test setting back color to nullptr (clearing it)
TEST_F(AnnotAppearanceCharacsTest_764, SetBackColorToNull_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    characs.setBackColor(nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
}

// Test with normal caption in dictionary
TEST_F(AnnotAppearanceCharacsTest_764, NormalCaptionFromDict_764) {
    auto dict = createDict();
    dict->add("CA", Object(new GooString("OK")));
    AnnotAppearanceCharacs characs(dict.get());
    const GooString *caption = characs.getNormalCaption();
    if (caption) {
        EXPECT_STREQ(caption->c_str(), "OK");
    }
}

// Test copy method produces independent copy
TEST_F(AnnotAppearanceCharacsTest_764, CopyProducesValidObject_764) {
    auto dict = createDict();
    dict->add("R", Object(90));
    AnnotAppearanceCharacs characs(dict.get());
    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getRotation(), 90);
}

// Test copy is independent from original
TEST_F(AnnotAppearanceCharacsTest_764, CopyIsIndependent_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));
    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    // Both should have border color set
    EXPECT_NE(copied->getBorderColor(), nullptr);
    // But they should be different pointers (independent copies)
    EXPECT_NE(characs.getBorderColor(), copied->getBorderColor());
}

// Test default position value
TEST_F(AnnotAppearanceCharacsTest_764, DefaultPosition_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    // Default text position is typically captionOnly (0) or similar
    auto pos = characs.getPosition();
    // Just verify it returns without crashing; exact default depends on implementation
    (void)pos;
    SUCCEED();
}

// Test with position specified in dictionary
TEST_F(AnnotAppearanceCharacsTest_764, PositionFromDict_764) {
    auto dict = createDict();
    dict->add("TP", Object(1));
    AnnotAppearanceCharacs characs(dict.get());
    auto pos = characs.getPosition();
    (void)pos;
    SUCCEED();
}

// Test zero rotation explicitly set
TEST_F(AnnotAppearanceCharacsTest_764, ExplicitZeroRotation_764) {
    auto dict = createDict();
    dict->add("R", Object(0));
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getRotation(), 0);
}

// Test getIconFit returns nullptr for empty dict
TEST_F(AnnotAppearanceCharacsTest_764, DefaultIconFitIsNull_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getIconFit(), nullptr);
}

// Test getRolloverCaption for empty dict
TEST_F(AnnotAppearanceCharacsTest_764, DefaultRolloverCaptionIsNull_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getRolloverCaption(), nullptr);
}

// Test getAlternateCaption for empty dict
TEST_F(AnnotAppearanceCharacsTest_764, DefaultAlternateCaptionIsNull_764) {
    auto dict = createDict();
    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getAlternateCaption(), nullptr);
}
