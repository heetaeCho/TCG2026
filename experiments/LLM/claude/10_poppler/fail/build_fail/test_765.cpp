#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class AnnotAppearanceCharacsTest_765 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create an empty Dict
    std::unique_ptr<Dict> createEmptyDict() {
        auto xref = (XRef *)nullptr;
        return std::make_unique<Dict>(xref);
    }
};

TEST_F(AnnotAppearanceCharacsTest_765, ConstructWithEmptyDict_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    // With empty dict, border color should be null
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
    EXPECT_EQ(characs.getNormalCaption(), nullptr);
    EXPECT_EQ(characs.getRotation(), 0);
}

TEST_F(AnnotAppearanceCharacsTest_765, GetBorderColorReturnsNullWhenNotSet_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    const AnnotColor *color = characs.getBorderColor();
    EXPECT_EQ(color, nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, GetBackColorReturnsNullWhenNotSet_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    const AnnotColor *color = characs.getBackColor();
    EXPECT_EQ(color, nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, SetBorderColor_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));

    const AnnotColor *result = characs.getBorderColor();
    ASSERT_NE(result, nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, SetBackColor_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBackColor(std::move(color));

    const AnnotColor *result = characs.getBackColor();
    ASSERT_NE(result, nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, SetBorderColorToNull_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    // First set a color
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));
    ASSERT_NE(characs.getBorderColor(), nullptr);

    // Then set to null
    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, SetBackColorToNull_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs.setBackColor(std::move(color));
    ASSERT_NE(characs.getBackColor(), nullptr);

    characs.setBackColor(nullptr);
    EXPECT_EQ(characs.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, GetRotationDefaultIsZero_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    EXPECT_EQ(characs.getRotation(), 0);
}

TEST_F(AnnotAppearanceCharacsTest_765, GetNormalCaptionReturnsNullWhenNotSet_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    EXPECT_EQ(characs.getNormalCaption(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, CopyCreatesValidObject_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));

    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied->getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, CopyPreservesNullColors_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto copied = characs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getBorderColor(), nullptr);
    EXPECT_EQ(copied->getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, ReplaceBorderColor_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color1 = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color1));
    const AnnotColor *first = characs.getBorderColor();
    ASSERT_NE(first, nullptr);

    auto color2 = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
    characs.setBorderColor(std::move(color2));
    const AnnotColor *second = characs.getBorderColor();
    ASSERT_NE(second, nullptr);

    // The pointer should have changed since we replaced the color
    EXPECT_NE(first, second);
}

TEST_F(AnnotAppearanceCharacsTest_765, CopyIsIndependent_765) {
    auto dict = createEmptyDict();
    AnnotAppearanceCharacs characs(dict.get());

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs.setBorderColor(std::move(color));

    auto copied = characs.copy();

    // Modifying original should not affect copy
    characs.setBorderColor(nullptr);
    EXPECT_EQ(characs.getBorderColor(), nullptr);
    EXPECT_NE(copied->getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_765, ConstructWithDictContainingRotation_765) {
    auto dict = createEmptyDict();

    Object rotObj(90);
    dict->add("R", std::move(rotObj));

    AnnotAppearanceCharacs characs(dict.get());
    EXPECT_EQ(characs.getRotation(), 90);
}

TEST_F(AnnotAppearanceCharacsTest_765, ConstructWithDictContainingNormalCaption_765) {
    auto dict = createEmptyDict();

    Object capObj(new GooString("OK"));
    dict->add("CA", std::move(capObj));

    AnnotAppearanceCharacs characs(dict.get());
    const GooString *caption = characs.getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "OK");
}

TEST_F(AnnotAppearanceCharacsTest_765, CopyPreservesRotation_765) {
    auto dict = createEmptyDict();

    Object rotObj(180);
    dict->add("R", std::move(rotObj));

    AnnotAppearanceCharacs characs(dict.get());
    auto copied = characs.copy();

    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getRotation(), 180);
}
