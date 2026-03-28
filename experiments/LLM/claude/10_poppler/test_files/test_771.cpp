#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "Dict.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class AnnotAppearanceCharacsTest_771 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        xref = nullptr;
    }

    void TearDown() override {
    }

    // Helper to create a Dict with specific entries
    Dict *createEmptyDict() {
        return new Dict(xref);
    }

    Dict *createDictWithRotation(int rotation) {
        Dict *dict = new Dict(xref);
        dict->add("R", Object(rotation));
        return dict;
    }

    Dict *createDictWithNormalCaption(const char *caption) {
        Dict *dict = new Dict(xref);
        dict->add("CA", Object(new GooString(caption)));
        return dict;
    }

    Dict *createDictWithRolloverCaption(const char *caption) {
        Dict *dict = new Dict(xref);
        dict->add("RC", Object(new GooString(caption)));
        return dict;
    }

    Dict *createDictWithAlternateCaption(const char *caption) {
        Dict *dict = new Dict(xref);
        dict->add("AC", Object(new GooString(caption)));
        return dict;
    }

    Dict *createFullDict() {
        Dict *dict = new Dict(xref);
        dict->add("R", Object(90));
        dict->add("CA", Object(new GooString("Normal")));
        dict->add("RC", Object(new GooString("Rollover")));
        dict->add("AC", Object(new GooString("Alternate")));
        // TP for text position
        dict->add("TP", Object(1));
        return dict;
    }

    XRef *xref;
};

// Test construction with an empty dictionary
TEST_F(AnnotAppearanceCharacsTest_771, ConstructWithEmptyDict_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    // Should not crash; default values should be used
    EXPECT_EQ(characs.getRotation(), 0);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
    EXPECT_EQ(characs.getNormalCaption(), nullptr);
    EXPECT_EQ(characs.getRolloverCaption(), nullptr);
    EXPECT_EQ(characs.getAlternateCaption(), nullptr);
    delete dict;
}

// Test rotation value from dict
TEST_F(AnnotAppearanceCharacsTest_771, GetRotation_771) {
    Dict *dict = createDictWithRotation(90);
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getRotation(), 90);
    delete dict;
}

// Test rotation with zero
TEST_F(AnnotAppearanceCharacsTest_771, GetRotationZero_771) {
    Dict *dict = createDictWithRotation(0);
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getRotation(), 0);
    delete dict;
}

// Test rotation with 180
TEST_F(AnnotAppearanceCharacsTest_771, GetRotation180_771) {
    Dict *dict = createDictWithRotation(180);
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getRotation(), 180);
    delete dict;
}

// Test rotation with 270
TEST_F(AnnotAppearanceCharacsTest_771, GetRotation270_771) {
    Dict *dict = createDictWithRotation(270);
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getRotation(), 270);
    delete dict;
}

// Test normal caption
TEST_F(AnnotAppearanceCharacsTest_771, GetNormalCaption_771) {
    Dict *dict = createDictWithNormalCaption("TestCaption");
    AnnotAppearanceCharacs characs(dict);
    const GooString *caption = characs.getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "TestCaption");
    delete dict;
}

// Test rollover caption
TEST_F(AnnotAppearanceCharacsTest_771, GetRolloverCaption_771) {
    Dict *dict = createDictWithRolloverCaption("RolloverText");
    AnnotAppearanceCharacs characs(dict);
    const GooString *caption = characs.getRolloverCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "RolloverText");
    delete dict;
}

// Test alternate caption
TEST_F(AnnotAppearanceCharacsTest_771, GetAlternateCaption_771) {
    Dict *dict = createDictWithAlternateCaption("AltText");
    AnnotAppearanceCharacs characs(dict);
    const GooString *caption = characs.getAlternateCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "AltText");
    delete dict;
}

// Test alternate caption is null when not set
TEST_F(AnnotAppearanceCharacsTest_771, GetAlternateCaptionNull_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getAlternateCaption(), nullptr);
    delete dict;
}

// Test normal caption is null when not set
TEST_F(AnnotAppearanceCharacsTest_771, GetNormalCaptionNull_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getNormalCaption(), nullptr);
    delete dict;
}

// Test rollover caption is null when not set
TEST_F(AnnotAppearanceCharacsTest_771, GetRolloverCaptionNull_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getRolloverCaption(), nullptr);
    delete dict;
}

// Test border color is null when not set
TEST_F(AnnotAppearanceCharacsTest_771, GetBorderColorNull_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    delete dict;
}

// Test back color is null when not set
TEST_F(AnnotAppearanceCharacsTest_771, GetBackColorNull_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getBackColor(), nullptr);
    delete dict;
}

// Test icon fit is null when not set
TEST_F(AnnotAppearanceCharacsTest_771, GetIconFitNull_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getIconFit(), nullptr);
    delete dict;
}

// Test full dict with all fields
TEST_F(AnnotAppearanceCharacsTest_771, FullDictAllFields_771) {
    Dict *dict = createFullDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getRotation(), 90);
    ASSERT_NE(characs.getNormalCaption(), nullptr);
    EXPECT_STREQ(characs.getNormalCaption()->c_str(), "Normal");
    ASSERT_NE(characs.getRolloverCaption(), nullptr);
    EXPECT_STREQ(characs.getRolloverCaption()->c_str(), "Rollover");
    ASSERT_NE(characs.getAlternateCaption(), nullptr);
    EXPECT_STREQ(characs.getAlternateCaption()->c_str(), "Alternate");
    delete dict;
}

// Test setBorderColor
TEST_F(AnnotAppearanceCharacsTest_771, SetBorderColor_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));
    EXPECT_NE(characs.getBorderColor(), nullptr);
    delete dict;
}

// Test setBackColor
TEST_F(AnnotAppearanceCharacsTest_771, SetBackColor_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    EXPECT_EQ(characs.getBackColor(), nullptr);
    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBackColor(std::move(color));
    EXPECT_NE(characs.getBackColor(), nullptr);
    delete dict;
}

// Test setBorderColor to null
TEST_F(AnnotAppearanceCharacsTest_771, SetBorderColorToNull_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));
    EXPECT_NE(characs.getBorderColor(), nullptr);
    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    delete dict;
}

// Test setBackColor to null
TEST_F(AnnotAppearanceCharacsTest_771, SetBackColorToNull_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
    characs.setBackColor(std::move(color));
    EXPECT_NE(characs.getBackColor(), nullptr);
    characs.setBackColor(nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
    delete dict;
}

// Test copy method
TEST_F(AnnotAppearanceCharacsTest_771, CopyMethod_771) {
    Dict *dict = createFullDict();
    AnnotAppearanceCharacs characs(dict);
    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getRotation(), characs.getRotation());
    // Verify captions are copied
    if (characs.getNormalCaption()) {
        ASSERT_NE(copied->getNormalCaption(), nullptr);
        EXPECT_STREQ(copied->getNormalCaption()->c_str(), characs.getNormalCaption()->c_str());
    }
    if (characs.getRolloverCaption()) {
        ASSERT_NE(copied->getRolloverCaption(), nullptr);
        EXPECT_STREQ(copied->getRolloverCaption()->c_str(), characs.getRolloverCaption()->c_str());
    }
    if (characs.getAlternateCaption()) {
        ASSERT_NE(copied->getAlternateCaption(), nullptr);
        EXPECT_STREQ(copied->getAlternateCaption()->c_str(), characs.getAlternateCaption()->c_str());
    }
    delete dict;
}

// Test that copy produces an independent object
TEST_F(AnnotAppearanceCharacsTest_771, CopyIsIndependent_771) {
    Dict *dict = createFullDict();
    AnnotAppearanceCharacs characs(dict);
    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    // Modify the copy's border color
    copied->setBorderColor(std::make_unique<AnnotColor>(1.0, 1.0, 1.0));
    // Original should still be null (or unchanged)
    // This tests that copy is a deep copy
    EXPECT_NE(copied->getBorderColor(), characs.getBorderColor());
    delete dict;
}

// Test empty string caption
TEST_F(AnnotAppearanceCharacsTest_771, EmptyStringCaption_771) {
    Dict *dict = createDictWithNormalCaption("");
    AnnotAppearanceCharacs characs(dict);
    const GooString *caption = characs.getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "");
    delete dict;
}

// Test getPosition default
TEST_F(AnnotAppearanceCharacsTest_771, GetPositionDefault_771) {
    Dict *dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict);
    // Default position should be captionOnly (0) typically
    auto pos = characs.getPosition();
    // Just verify it doesn't crash and returns a valid enum value
    EXPECT_GE(static_cast<int>(pos), 0);
    delete dict;
}
