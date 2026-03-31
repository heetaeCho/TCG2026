#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "Dict.h"
#include "XRef.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class AnnotAppearanceCharacsTest_772 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create an empty Dict for constructing AnnotAppearanceCharacs
    std::unique_ptr<AnnotAppearanceCharacs> createFromEmptyDict() {
        Object obj = Object(new Dict(nullptr));
        Dict *dict = obj.getDict();
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    std::unique_ptr<AnnotAppearanceCharacs> createWithRotation(int rotation) {
        Object obj = Object(new Dict(nullptr));
        Dict *dict = obj.getDict();
        dict->add("R", Object(rotation));
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    std::unique_ptr<AnnotAppearanceCharacs> createWithNormalCaption(const char *caption) {
        Object obj = Object(new Dict(nullptr));
        Dict *dict = obj.getDict();
        dict->add("CA", Object(new GooString(caption)));
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    std::unique_ptr<AnnotAppearanceCharacs> createWithRolloverCaption(const char *caption) {
        Object obj = Object(new Dict(nullptr));
        Dict *dict = obj.getDict();
        dict->add("RC", Object(new GooString(caption)));
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    std::unique_ptr<AnnotAppearanceCharacs> createWithAlternateCaption(const char *caption) {
        Object obj = Object(new Dict(nullptr));
        Dict *dict = obj.getDict();
        dict->add("AC", Object(new GooString(caption)));
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    std::unique_ptr<AnnotAppearanceCharacs> createWithPosition(int pos) {
        Object obj = Object(new Dict(nullptr));
        Dict *dict = obj.getDict();
        dict->add("TP", Object(pos));
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    std::unique_ptr<AnnotAppearanceCharacs> createWithBorderColor() {
        Object obj = Object(new Dict(nullptr));
        Dict *dict = obj.getDict();
        // Create a border color array with one component (grayscale)
        Object arr = Object(new Array(nullptr));
        arr.arrayAdd(Object(0.5));
        dict->add("BC", std::move(arr));
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    std::unique_ptr<AnnotAppearanceCharacs> createWithBackColor() {
        Object obj = Object(new Dict(nullptr));
        Dict *dict = obj.getDict();
        Object arr = Object(new Array(nullptr));
        arr.arrayAdd(Object(0.8));
        dict->add("BG", std::move(arr));
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }
};

// Test default rotation from empty dict
TEST_F(AnnotAppearanceCharacsTest_772, EmptyDictDefaultRotation_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getRotation(), 0);
}

// Test rotation value is read correctly
TEST_F(AnnotAppearanceCharacsTest_772, RotationValue_772) {
    auto characs = createWithRotation(90);
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getRotation(), 90);
}

// Test rotation with 180 degrees
TEST_F(AnnotAppearanceCharacsTest_772, Rotation180_772) {
    auto characs = createWithRotation(180);
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getRotation(), 180);
}

// Test rotation with 270 degrees
TEST_F(AnnotAppearanceCharacsTest_772, Rotation270_772) {
    auto characs = createWithRotation(270);
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getRotation(), 270);
}

// Test no border color from empty dict
TEST_F(AnnotAppearanceCharacsTest_772, EmptyDictNoBorderColor_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getBorderColor(), nullptr);
}

// Test no back color from empty dict
TEST_F(AnnotAppearanceCharacsTest_772, EmptyDictNoBackColor_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getBackColor(), nullptr);
}

// Test normal caption from empty dict is null
TEST_F(AnnotAppearanceCharacsTest_772, EmptyDictNoNormalCaption_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getNormalCaption(), nullptr);
}

// Test rollover caption from empty dict is null
TEST_F(AnnotAppearanceCharacsTest_772, EmptyDictNoRolloverCaption_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getRolloverCaption(), nullptr);
}

// Test alternate caption from empty dict is null
TEST_F(AnnotAppearanceCharacsTest_772, EmptyDictNoAlternateCaption_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getAlternateCaption(), nullptr);
}

// Test icon fit from empty dict is null
TEST_F(AnnotAppearanceCharacsTest_772, EmptyDictNoIconFit_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getIconFit(), nullptr);
}

// Test normal caption is set correctly
TEST_F(AnnotAppearanceCharacsTest_772, NormalCaptionSet_772) {
    auto characs = createWithNormalCaption("TestCaption");
    ASSERT_NE(characs, nullptr);
    const GooString *caption = characs->getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "TestCaption");
}

// Test rollover caption is set correctly
TEST_F(AnnotAppearanceCharacsTest_772, RolloverCaptionSet_772) {
    auto characs = createWithRolloverCaption("RolloverTest");
    ASSERT_NE(characs, nullptr);
    const GooString *caption = characs->getRolloverCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "RolloverTest");
}

// Test alternate caption is set correctly
TEST_F(AnnotAppearanceCharacsTest_772, AlternateCaptionSet_772) {
    auto characs = createWithAlternateCaption("AltTest");
    ASSERT_NE(characs, nullptr);
    const GooString *caption = characs->getAlternateCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "AltTest");
}

// Test border color is set via dict
TEST_F(AnnotAppearanceCharacsTest_772, BorderColorFromDict_772) {
    auto characs = createWithBorderColor();
    ASSERT_NE(characs, nullptr);
    const AnnotColor *color = characs->getBorderColor();
    ASSERT_NE(color, nullptr);
}

// Test back color is set via dict
TEST_F(AnnotAppearanceCharacsTest_772, BackColorFromDict_772) {
    auto characs = createWithBackColor();
    ASSERT_NE(characs, nullptr);
    const AnnotColor *color = characs->getBackColor();
    ASSERT_NE(color, nullptr);
}

// Test setBorderColor
TEST_F(AnnotAppearanceCharacsTest_772, SetBorderColor_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getBorderColor(), nullptr);

    auto color = std::make_unique<AnnotColor>(0.5);
    characs->setBorderColor(std::move(color));
    EXPECT_NE(characs->getBorderColor(), nullptr);
}

// Test setBackColor
TEST_F(AnnotAppearanceCharacsTest_772, SetBackColor_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getBackColor(), nullptr);

    auto color = std::make_unique<AnnotColor>(0.3);
    characs->setBackColor(std::move(color));
    EXPECT_NE(characs->getBackColor(), nullptr);
}

// Test setBorderColor to nullptr clears it
TEST_F(AnnotAppearanceCharacsTest_772, SetBorderColorToNull_772) {
    auto characs = createWithBorderColor();
    ASSERT_NE(characs, nullptr);
    EXPECT_NE(characs->getBorderColor(), nullptr);

    characs->setBorderColor(nullptr);
    EXPECT_EQ(characs->getBorderColor(), nullptr);
}

// Test setBackColor to nullptr clears it
TEST_F(AnnotAppearanceCharacsTest_772, SetBackColorToNull_772) {
    auto characs = createWithBackColor();
    ASSERT_NE(characs, nullptr);
    EXPECT_NE(characs->getBackColor(), nullptr);

    characs->setBackColor(nullptr);
    EXPECT_EQ(characs->getBackColor(), nullptr);
}

// Test copy method
TEST_F(AnnotAppearanceCharacsTest_772, CopyPreservesRotation_772) {
    auto characs = createWithRotation(90);
    ASSERT_NE(characs, nullptr);

    auto copied = characs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getRotation(), 90);
}

// Test copy preserves normal caption
TEST_F(AnnotAppearanceCharacsTest_772, CopyPreservesNormalCaption_772) {
    auto characs = createWithNormalCaption("CopyTest");
    ASSERT_NE(characs, nullptr);

    auto copied = characs->copy();
    ASSERT_NE(copied, nullptr);
    const GooString *caption = copied->getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "CopyTest");
}

// Test copy produces independent object (modifying copy doesn't affect original)
TEST_F(AnnotAppearanceCharacsTest_772, CopyIsIndependent_772) {
    auto characs = createWithBorderColor();
    ASSERT_NE(characs, nullptr);

    auto copied = characs->copy();
    ASSERT_NE(copied, nullptr);

    copied->setBorderColor(nullptr);
    EXPECT_EQ(copied->getBorderColor(), nullptr);
    // Original should still have border color
    EXPECT_NE(characs->getBorderColor(), nullptr);
}

// Test position from empty dict
TEST_F(AnnotAppearanceCharacsTest_772, DefaultPosition_772) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
    // Default position should be captionNoIcon (0)
    EXPECT_EQ(static_cast<int>(characs->getPosition()), 0);
}

// Test position set via dict
TEST_F(AnnotAppearanceCharacsTest_772, PositionFromDict_772) {
    auto characs = createWithPosition(1);
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(static_cast<int>(characs->getPosition()), 1);
}

// Test zero rotation
TEST_F(AnnotAppearanceCharacsTest_772, ZeroRotation_772) {
    auto characs = createWithRotation(0);
    ASSERT_NE(characs, nullptr);
    EXPECT_EQ(characs->getRotation(), 0);
}

// Test empty normal caption string
TEST_F(AnnotAppearanceCharacsTest_772, EmptyNormalCaption_772) {
    auto characs = createWithNormalCaption("");
    ASSERT_NE(characs, nullptr);
    const GooString *caption = characs->getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "");
}

// Test replacing border color with new color
TEST_F(AnnotAppearanceCharacsTest_772, ReplaceBorderColor_772) {
    auto characs = createWithBorderColor();
    ASSERT_NE(characs, nullptr);

    auto newColor = std::make_unique<AnnotColor>(1.0);
    characs->setBorderColor(std::move(newColor));
    EXPECT_NE(characs->getBorderColor(), nullptr);
}

// Test replacing back color with new color
TEST_F(AnnotAppearanceCharacsTest_772, ReplaceBackColor_772) {
    auto characs = createWithBackColor();
    ASSERT_NE(characs, nullptr);

    auto newColor = std::make_unique<AnnotColor>(0.0);
    characs->setBackColor(std::move(newColor));
    EXPECT_NE(characs->getBackColor(), nullptr);
}
