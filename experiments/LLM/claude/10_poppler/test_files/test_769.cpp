#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "Dict.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class AnnotAppearanceCharacsTest_769 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create an empty Dict-based AnnotAppearanceCharacs
    std::unique_ptr<AnnotAppearanceCharacs> createFromEmptyDict() {
        xref = nullptr;
        Object dictObj = Object(new Dict(xref));
        Dict *dict = dictObj.getDict();
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    // Helper to create a Dict with specific entries
    std::unique_ptr<AnnotAppearanceCharacs> createWithEntries(
        int rotation = -1,
        const char *normalCaption = nullptr,
        const char *rolloverCaption = nullptr,
        const char *alternateCaption = nullptr) {
        
        xref = nullptr;
        Dict *dict = new Dict(xref);
        
        if (rotation >= 0) {
            dict->add("R", Object(rotation));
        }
        if (normalCaption) {
            dict->add("CA", Object(new GooString(normalCaption)));
        }
        if (rolloverCaption) {
            dict->add("RC", Object(new GooString(rolloverCaption)));
        }
        if (alternateCaption) {
            dict->add("AC", Object(new GooString(alternateCaption)));
        }
        
        return std::make_unique<AnnotAppearanceCharacs>(dict);
    }

    XRef *xref = nullptr;
};

// Test construction with empty dictionary
TEST_F(AnnotAppearanceCharacsTest_769, ConstructWithEmptyDict_769) {
    auto characs = createFromEmptyDict();
    ASSERT_NE(characs, nullptr);
}

// Test default rotation is 0 when not specified
TEST_F(AnnotAppearanceCharacsTest_769, DefaultRotationIsZero_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getRotation(), 0);
}

// Test rotation with specified value
TEST_F(AnnotAppearanceCharacsTest_769, RotationWithValue_769) {
    auto characs = createWithEntries(90);
    EXPECT_EQ(characs->getRotation(), 90);
}

// Test rotation with 0
TEST_F(AnnotAppearanceCharacsTest_769, RotationZero_769) {
    auto characs = createWithEntries(0);
    EXPECT_EQ(characs->getRotation(), 0);
}

// Test rotation with 180
TEST_F(AnnotAppearanceCharacsTest_769, Rotation180_769) {
    auto characs = createWithEntries(180);
    EXPECT_EQ(characs->getRotation(), 180);
}

// Test rotation with 270
TEST_F(AnnotAppearanceCharacsTest_769, Rotation270_769) {
    auto characs = createWithEntries(270);
    EXPECT_EQ(characs->getRotation(), 270);
}

// Test getNormalCaption returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_769, NormalCaptionNullWhenNotSet_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getNormalCaption(), nullptr);
}

// Test getNormalCaption returns correct value when set
TEST_F(AnnotAppearanceCharacsTest_769, NormalCaptionReturnsValue_769) {
    auto characs = createWithEntries(-1, "TestCaption");
    const GooString *caption = characs->getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "TestCaption");
}

// Test getRolloverCaption returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_769, RolloverCaptionNullWhenNotSet_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getRolloverCaption(), nullptr);
}

// Test getRolloverCaption returns correct value when set
TEST_F(AnnotAppearanceCharacsTest_769, RolloverCaptionReturnsValue_769) {
    auto characs = createWithEntries(-1, nullptr, "RolloverCap");
    const GooString *caption = characs->getRolloverCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "RolloverCap");
}

// Test getAlternateCaption returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_769, AlternateCaptionNullWhenNotSet_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getAlternateCaption(), nullptr);
}

// Test getAlternateCaption returns correct value when set
TEST_F(AnnotAppearanceCharacsTest_769, AlternateCaptionReturnsValue_769) {
    auto characs = createWithEntries(-1, nullptr, nullptr, "AltCap");
    const GooString *caption = characs->getAlternateCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_STREQ(caption->c_str(), "AltCap");
}

// Test getBorderColor returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_769, BorderColorNullWhenNotSet_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getBorderColor(), nullptr);
}

// Test getBackColor returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_769, BackColorNullWhenNotSet_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getBackColor(), nullptr);
}

// Test getIconFit returns nullptr when not set
TEST_F(AnnotAppearanceCharacsTest_769, IconFitNullWhenNotSet_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getIconFit(), nullptr);
}

// Test setBorderColor
TEST_F(AnnotAppearanceCharacsTest_769, SetBorderColor_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getBorderColor(), nullptr);
    
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs->setBorderColor(std::move(color));
    
    const AnnotColor *bc = characs->getBorderColor();
    ASSERT_NE(bc, nullptr);
}

// Test setBackColor
TEST_F(AnnotAppearanceCharacsTest_769, SetBackColor_769) {
    auto characs = createFromEmptyDict();
    EXPECT_EQ(characs->getBackColor(), nullptr);
    
    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    characs->setBackColor(std::move(color));
    
    const AnnotColor *bgc = characs->getBackColor();
    ASSERT_NE(bgc, nullptr);
}

// Test setBorderColor with nullptr resets it
TEST_F(AnnotAppearanceCharacsTest_769, SetBorderColorToNull_769) {
    auto characs = createFromEmptyDict();
    
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    characs->setBorderColor(std::move(color));
    ASSERT_NE(characs->getBorderColor(), nullptr);
    
    characs->setBorderColor(nullptr);
    EXPECT_EQ(characs->getBorderColor(), nullptr);
}

// Test setBackColor with nullptr resets it
TEST_F(AnnotAppearanceCharacsTest_769, SetBackColorToNull_769) {
    auto characs = createFromEmptyDict();
    
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
    characs->setBackColor(std::move(color));
    ASSERT_NE(characs->getBackColor(), nullptr);
    
    characs->setBackColor(nullptr);
    EXPECT_EQ(characs->getBackColor(), nullptr);
}

// Test copy method
TEST_F(AnnotAppearanceCharacsTest_769, CopyMethod_769) {
    auto characs = createWithEntries(90, "NormalCap", "RollCap", "AltCap");
    
    auto copied = characs->copy();
    ASSERT_NE(copied, nullptr);
    
    EXPECT_EQ(copied->getRotation(), 90);
    
    const GooString *normalCap = copied->getNormalCaption();
    ASSERT_NE(normalCap, nullptr);
    EXPECT_STREQ(normalCap->c_str(), "NormalCap");
}

// Test that copy is independent (deep copy)
TEST_F(AnnotAppearanceCharacsTest_769, CopyIsIndependent_769) {
    auto characs = createWithEntries(-1, "Original");
    
    auto copied = characs->copy();
    ASSERT_NE(copied, nullptr);
    
    const GooString *origCaption = characs->getNormalCaption();
    const GooString *copiedCaption = copied->getNormalCaption();
    
    ASSERT_NE(origCaption, nullptr);
    ASSERT_NE(copiedCaption, nullptr);
    
    // They should have same content but be different objects
    EXPECT_STREQ(origCaption->c_str(), copiedCaption->c_str());
    EXPECT_NE(origCaption, copiedCaption);
}

// Test empty normal caption string
TEST_F(AnnotAppearanceCharacsTest_769, EmptyNormalCaption_769) {
    auto characs = createWithEntries(-1, "");
    const GooString *caption = characs->getNormalCaption();
    ASSERT_NE(caption, nullptr);
    EXPECT_EQ(caption->getLength(), 0);
}

// Test all captions set simultaneously
TEST_F(AnnotAppearanceCharacsTest_769, AllCaptionsSet_769) {
    auto characs = createWithEntries(0, "Normal", "Rollover", "Alternate");
    
    const GooString *normal = characs->getNormalCaption();
    ASSERT_NE(normal, nullptr);
    EXPECT_STREQ(normal->c_str(), "Normal");
    
    const GooString *rollover = characs->getRolloverCaption();
    ASSERT_NE(rollover, nullptr);
    EXPECT_STREQ(rollover->c_str(), "Rollover");
    
    const GooString *alternate = characs->getAlternateCaption();
    ASSERT_NE(alternate, nullptr);
    EXPECT_STREQ(alternate->c_str(), "Alternate");
}
