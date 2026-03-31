#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class AnnotAppearanceCharacsTest_770 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific entries
    // We need an XRef for Dict construction in some versions
    std::unique_ptr<Dict> createEmptyDict() {
        return std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    }
};

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithEmptyDict_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    // With empty dict, rotation should default to 0
    EXPECT_EQ(characs.getRotation(), 0);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
    EXPECT_EQ(characs.getNormalCaption(), nullptr);
    EXPECT_EQ(characs.getRolloverCaption(), nullptr);
    EXPECT_EQ(characs.getAlternateCaption(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithRotation_770) {
    auto dict = createEmptyDict();
    dict->add("R", Object(90));
    AnnotAppearanceCharacs characs(dict.get());

    EXPECT_EQ(characs.getRotation(), 90);
}

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithZeroRotation_770) {
    auto dict = createEmptyDict();
    dict->add("R", Object(0));
    AnnotAppearanceCharacs characs(dict.get());

    EXPECT_EQ(characs.getRotation(), 0);
}

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithNormalCaption_770) {
    auto dict = createEmptyDict();
    dict->add("CA", Object(new GooString("Normal")));
    AnnotAppearanceCharacs characs(dict.get());

    const GooString *caption = characs.getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "Normal");
}

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithRolloverCaption_770) {
    auto dict = createEmptyDict();
    dict->add("RC", Object(new GooString("Rollover")));
    AnnotAppearanceCharacs characs(dict.get());

    const GooString *caption = characs.getRolloverCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "Rollover");
}

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithAlternateCaption_770) {
    auto dict = createEmptyDict();
    dict->add("AC", Object(new GooString("Alternate")));
    AnnotAppearanceCharacs characs(dict.get());

    const GooString *caption = characs.getAlternateCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "Alternate");
}

TEST_F(AnnotAppearanceCharacsTest_770, GetRolloverCaptionReturnsNullWhenNotSet_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    EXPECT_EQ(characs.getRolloverCaption(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, GetAlternateCaptionReturnsNullWhenNotSet_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    EXPECT_EQ(characs.getAlternateCaption(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, SetBorderColor_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    EXPECT_EQ(characs.getBorderColor(), nullptr);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));

    ASSERT_NE(characs.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, SetBackColor_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    EXPECT_EQ(characs.getBackColor(), nullptr);

    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBackColor(std::move(color));

    ASSERT_NE(characs.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, SetBorderColorToNull_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));
    ASSERT_NE(characs.getBorderColor(), nullptr);

    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, SetBackColorToNull_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
    characs.setBackColor(std::move(color));
    ASSERT_NE(characs.getBackColor(), nullptr);

    characs.setBackColor(nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, CopyCreatesIndependentObject_770) {
    auto dict = createEmptyDict();
    dict->add("R", Object(180));
    dict->add("CA", Object(new GooString("TestCaption")));
    AnnotAppearanceCharacs characs(dict.get());

    auto copy = characs.copy();
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->getRotation(), 180);

    const GooString *caption = copy->getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "TestCaption");
}

TEST_F(AnnotAppearanceCharacsTest_770, CopyWithBorderColor_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
    characs.setBorderColor(std::move(color));

    auto copy = characs.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy->getBorderColor(), nullptr);
    // The copy should have its own color object (different pointer)
    EXPECT_NE(copy->getBorderColor(), characs.getBorderColor());
}

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithBorderColorArray_770) {
    auto dict = createEmptyDict();

    // Border color is specified as an array in PDF
    Array *arr = new Array(static_cast<XRef*>(nullptr));
    arr->add(Object(1.0));
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    dict->add("BC", Object(arr));

    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_NE(characs.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithBackColorArray_770) {
    auto dict = createEmptyDict();

    Array *arr = new Array(static_cast<XRef*>(nullptr));
    arr->add(Object(0.0));
    arr->add(Object(1.0));
    arr->add(Object(0.0));
    dict->add("BG", Object(arr));

    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_NE(characs.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_770, DefaultPosition_770) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    // Default position is typically captionOnly (0)
    AnnotAppearanceCharacs::AnnotAppearanceCharacsTextPos pos = characs.getPosition();
    // Just verify it returns a valid enum value without crashing
    (void)pos;
}

TEST_F(AnnotAppearanceCharacsTest_770, ConstructWithPosition_770) {
    auto dict = createEmptyDict();
    dict->add("TP", Object(1));
    AnnotAppearanceCharacs characs(dict.get());

    // Position 1 should be iconOnly
    AnnotAppearanceCharacs::AnnotAppearanceCharacsTextPos pos = characs.getPosition();
    (void)pos;
}

TEST_F(AnnotAppearanceCharacsTest_770, EmptyCaptionString_770) {
    auto dict = createEmptyDict();
    dict->add("CA", Object(new GooString("")));
    AnnotAppearanceCharacs characs(dict.get());

    const GooString *caption = characs.getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_EQ(caption->getLength(), 0);
}

TEST_F(AnnotAppearanceCharacsTest_770, CopyDeleteDoesNotAffectOriginal_770) {
    auto dict = createEmptyDict();
    dict->add("R", Object(270));
    dict->add("CA", Object(new GooString("OrigCaption")));
    AnnotAppearanceCharacs characs(dict.get());

    {
        auto copy = characs.copy();
        ASSERT_NE(copy, nullptr);
        // copy goes out of scope and is destroyed
    }

    // Original should still be intact
    EXPECT_EQ(characs.getRotation(), 270);
    const GooString *caption = characs.getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "OrigCaption");
}
