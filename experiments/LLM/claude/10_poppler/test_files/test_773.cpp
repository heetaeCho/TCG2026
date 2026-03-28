#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "poppler/Annot.h"
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"

// Helper to create a minimal Dict for AnnotAppearanceCharacs construction
class AnnotAppearanceCharacsTest_773 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create an empty dict wrapped in proper structure
    Dict *createEmptyDict() {
        // We need an XRef-less Dict for testing
        Object obj = Object(new Dict(nullptr));
        dictObj = std::move(obj);
        return dictObj.getDict();
    }

    // Helper to create a dict with rotation entry
    Dict *createDictWithRotation(int rotation) {
        Dict *dict = new Dict(nullptr);
        dict->add("R", Object(rotation));
        dictObj = Object(dict);
        return dict;
    }

    // Helper to create a dict with position entry
    Dict *createDictWithPosition(int pos) {
        Dict *dict = new Dict(nullptr);
        dict->add("TP", Object(pos));
        dictObj = Object(dict);
        return dict;
    }

    // Helper to create a dict with normal caption
    Dict *createDictWithCaption(const char *caption) {
        Dict *dict = new Dict(nullptr);
        dict->add("CA", Object(new GooString(caption)));
        dictObj = Object(dict);
        return dict;
    }

    Object dictObj;
};

// Test construction with empty dictionary - default values
TEST_F(AnnotAppearanceCharacsTest_773, ConstructWithEmptyDict_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    // With empty dict, rotation should default to 0
    EXPECT_EQ(characs.getRotation(), 0);
}

// Test getRotation with a specific rotation value
TEST_F(AnnotAppearanceCharacsTest_773, GetRotationWithValue_773) {
    Dict *dict = createDictWithRotation(90);
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getRotation(), 90);
}

// Test getRotation with zero rotation
TEST_F(AnnotAppearanceCharacsTest_773, GetRotationZero_773) {
    Dict *dict = createDictWithRotation(0);
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getRotation(), 0);
}

// Test getRotation with 180 degrees
TEST_F(AnnotAppearanceCharacsTest_773, GetRotation180_773) {
    Dict *dict = createDictWithRotation(180);
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getRotation(), 180);
}

// Test getRotation with 270 degrees
TEST_F(AnnotAppearanceCharacsTest_773, GetRotation270_773) {
    Dict *dict = createDictWithRotation(270);
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getRotation(), 270);
}

// Test getBorderColor returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_773, GetBorderColorNullWhenNotSet_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

// Test getBackColor returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_773, GetBackColorNullWhenNotSet_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getBackColor(), nullptr);
}

// Test getNormalCaption returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_773, GetNormalCaptionNullWhenNotSet_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getNormalCaption(), nullptr);
}

// Test getNormalCaption when set
TEST_F(AnnotAppearanceCharacsTest_773, GetNormalCaptionWhenSet_773) {
    Dict *dict = createDictWithCaption("Submit");
    AnnotAppearanceCharacs characs(dict);

    const GooString *caption = characs.getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "Submit");
}

// Test getPosition with default (empty dict)
TEST_F(AnnotAppearanceCharacsTest_773, GetPositionDefault_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    // Default position should be captionOnly (0)
    EXPECT_EQ(characs.getPosition(), AnnotAppearanceCharacs::captionOnly);
}

// Test getPosition with explicit value
TEST_F(AnnotAppearanceCharacsTest_773, GetPositionCaptionOnly_773) {
    Dict *dict = createDictWithPosition(0);
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getPosition(), AnnotAppearanceCharacs::captionOnly);
}

// Test getPosition with icon only
TEST_F(AnnotAppearanceCharacsTest_773, GetPositionIconOnly_773) {
    Dict *dict = createDictWithPosition(1);
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getPosition(), AnnotAppearanceCharacs::iconOnly);
}

// Test setBorderColor
TEST_F(AnnotAppearanceCharacsTest_773, SetBorderColor_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getBorderColor(), nullptr);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));

    EXPECT_NE(characs.getBorderColor(), nullptr);
}

// Test setBackColor
TEST_F(AnnotAppearanceCharacsTest_773, SetBackColor_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getBackColor(), nullptr);

    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBackColor(std::move(color));

    EXPECT_NE(characs.getBackColor(), nullptr);
}

// Test setBorderColor replaces existing color
TEST_F(AnnotAppearanceCharacsTest_773, SetBorderColorReplacesExisting_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    auto color1 = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color1));
    const AnnotColor *firstColor = characs.getBorderColor();
    ASSERT_NE(firstColor, nullptr);

    auto color2 = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
    characs.setBorderColor(std::move(color2));
    const AnnotColor *secondColor = characs.getBorderColor();
    ASSERT_NE(secondColor, nullptr);
}

// Test setBackColor with nullptr effectively clears it
TEST_F(AnnotAppearanceCharacsTest_773, SetBackColorToNull_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    auto color = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
    characs.setBackColor(std::move(color));
    EXPECT_NE(characs.getBackColor(), nullptr);

    characs.setBackColor(nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
}

// Test setBorderColor with nullptr
TEST_F(AnnotAppearanceCharacsTest_773, SetBorderColorToNull_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    auto color = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
    characs.setBorderColor(std::move(color));
    EXPECT_NE(characs.getBorderColor(), nullptr);

    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

// Test copy method
TEST_F(AnnotAppearanceCharacsTest_773, CopyMethod_773) {
    Dict *dict = createDictWithRotation(90);
    AnnotAppearanceCharacs characs(dict);

    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getRotation(), 90);
}

// Test copy preserves caption
TEST_F(AnnotAppearanceCharacsTest_773, CopyPreservesCaption_773) {
    Dict *dict = createDictWithCaption("OK");
    AnnotAppearanceCharacs characs(dict);

    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);

    const GooString *caption = copied->getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "OK");
}

// Test copy preserves border color
TEST_F(AnnotAppearanceCharacsTest_773, CopyPreservesBorderColor_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));

    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied->getBorderColor(), nullptr);
}

// Test empty caption string
TEST_F(AnnotAppearanceCharacsTest_773, EmptyCaption_773) {
    Dict *dict = createDictWithCaption("");
    AnnotAppearanceCharacs characs(dict);

    const GooString *caption = characs.getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "");
}

// Test getRolloverCaption returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_773, GetRolloverCaptionNullWhenNotSet_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getRolloverCaption(), nullptr);
}

// Test getAlternateCaption returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_773, GetAlternateCaptionNullWhenNotSet_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getAlternateCaption(), nullptr);
}

// Test getIconFit returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_773, GetIconFitNullWhenNotSet_773) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);

    EXPECT_EQ(characs.getIconFit(), nullptr);
}
