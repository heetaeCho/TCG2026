#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class AnnotAppearanceCharacsTest_767 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create an empty Dict
    Dict* createEmptyDict() {
        // We need an XRef, but for testing we can use nullptr if the Dict allows it
        return new Dict(nullptr);
    }

    // Helper to create a Dict with rotation
    Object createDictWithRotation(int rotation) {
        Object dictObj = Object(new Dict(nullptr));
        dictObj.dictSet("R", Object(rotation));
        return dictObj;
    }

    // Helper to create a Dict with back color
    Object createDictWithBackColor(double r, double g, double b) {
        Object dictObj = Object(new Dict(nullptr));
        Object colorArray = Object(new Array(nullptr));
        colorArray.arrayAdd(Object(r));
        colorArray.arrayAdd(Object(g));
        colorArray.arrayAdd(Object(b));
        dictObj.dictSet("BG", std::move(colorArray));
        return dictObj;
    }

    // Helper to create a Dict with border color
    Object createDictWithBorderColor(double r, double g, double b) {
        Object dictObj = Object(new Dict(nullptr));
        Object colorArray = Object(new Array(nullptr));
        colorArray.arrayAdd(Object(r));
        colorArray.arrayAdd(Object(g));
        colorArray.arrayAdd(Object(b));
        dictObj.dictSet("BC", std::move(colorArray));
        return dictObj;
    }

    // Helper to create a Dict with normal caption
    Object createDictWithNormalCaption(const char* caption) {
        Object dictObj = Object(new Dict(nullptr));
        dictObj.dictSet("CA", Object(new GooString(caption)));
        return dictObj;
    }
};

TEST_F(AnnotAppearanceCharacsTest_767, EmptyDictGetBackColorReturnsNull_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, EmptyDictGetBorderColorReturnsNull_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, EmptyDictGetRotationReturnsZero_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getRotation(), 0);
}

TEST_F(AnnotAppearanceCharacsTest_767, DictWithRotationReturnsCorrectRotation_767) {
    Object dictObj = createDictWithRotation(90);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getRotation(), 90);
}

TEST_F(AnnotAppearanceCharacsTest_767, DictWithBackColorReturnsNonNull_767) {
    Object dictObj = createDictWithBackColor(1.0, 0.0, 0.0);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_NE(characs.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, DictWithBorderColorReturnsNonNull_767) {
    Object dictObj = createDictWithBorderColor(0.0, 1.0, 0.0);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_NE(characs.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, SetBackColorChangesBackColor_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getBackColor(), nullptr);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBackColor(std::move(color));
    EXPECT_NE(characs.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, SetBorderColorChangesBorderColor_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getBorderColor(), nullptr);

    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBorderColor(std::move(color));
    EXPECT_NE(characs.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, SetBackColorToNullptrClearsColor_767) {
    Object dictObj = createDictWithBackColor(1.0, 0.0, 0.0);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_NE(characs.getBackColor(), nullptr);

    characs.setBackColor(nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, SetBorderColorToNullptrClearsColor_767) {
    Object dictObj = createDictWithBorderColor(0.0, 1.0, 0.0);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_NE(characs.getBorderColor(), nullptr);

    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, EmptyDictGetNormalCaptionReturnsNull_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getNormalCaption(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, DictWithNormalCaptionReturnsNonNull_767) {
    Object dictObj = createDictWithNormalCaption("OK");
    AnnotAppearanceCharacs characs(dictObj.getDict());
    const GooString* caption = characs.getNormalCaption();
    EXPECT_NE(caption, nullptr);
    if (caption) {
        EXPECT_STREQ(caption->c_str(), "OK");
    }
}

TEST_F(AnnotAppearanceCharacsTest_767, CopyCreatesIndependentObject_767) {
    Object dictObj = createDictWithBackColor(1.0, 0.5, 0.0);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    
    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    
    // The copied object should have same back color (non-null)
    EXPECT_NE(copied->getBackColor(), nullptr);
    
    // Modifying the original should not affect the copy
    characs.setBackColor(nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
    EXPECT_NE(copied->getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, CopyPreservesRotation_767) {
    Object dictObj = createDictWithRotation(180);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    
    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getRotation(), 180);
}

TEST_F(AnnotAppearanceCharacsTest_767, EmptyDictGetRolloverCaptionReturnsNull_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getRolloverCaption(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, EmptyDictGetAlternateCaptionReturnsNull_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getAlternateCaption(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, EmptyDictGetIconFitReturnsNull_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getIconFit(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, RotationZeroByDefault_767) {
    Object dictObj = Object(new Dict(nullptr));
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getRotation(), 0);
}

TEST_F(AnnotAppearanceCharacsTest_767, SetBackColorOverwritesPreviousColor_767) {
    Object dictObj = createDictWithBackColor(1.0, 0.0, 0.0);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    
    auto newColor = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
    characs.setBackColor(std::move(newColor));
    
    const AnnotColor* color = characs.getBackColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, SetBorderColorOverwritesPreviousColor_767) {
    Object dictObj = createDictWithBorderColor(1.0, 0.0, 0.0);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    
    auto newColor = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
    characs.setBorderColor(std::move(newColor));
    
    const AnnotColor* color = characs.getBorderColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_767, DictWithRotation270_767) {
    Object dictObj = createDictWithRotation(270);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    EXPECT_EQ(characs.getRotation(), 270);
}

TEST_F(AnnotAppearanceCharacsTest_767, CopyPreservesBorderColor_767) {
    Object dictObj = createDictWithBorderColor(0.5, 0.5, 0.5);
    AnnotAppearanceCharacs characs(dictObj.getDict());
    
    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied->getBorderColor(), nullptr);
    
    // Modify original, copy should be unaffected
    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    EXPECT_NE(copied->getBorderColor(), nullptr);
}
