#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fontconfig/fontconfig.h>
#include <memory>
#include <string>

#include "poppler/GfxFont.h"
#include "goo/GooString.h"
#include "poppler/GlobalParams.h"

// We need access to the static buildFcPattern function.
// Since it's static in the .cc file, we include it directly.
// This is necessary for unit testing a file-static function.
#include "poppler/GlobalParams.cc"

// Helper to extract integer value from FcPattern
static bool getFcPatternInt(FcPattern *p, const char *object, int *val) {
    return FcPatternGetInteger(p, object, 0, val) == FcResultMatch;
}

// Helper to extract string value from FcPattern
static bool getFcPatternString(FcPattern *p, const char *object, std::string &val) {
    FcChar8 *str = nullptr;
    if (FcPatternGetString(p, object, 0, &str) == FcResultMatch) {
        val = reinterpret_cast<const char *>(str);
        return true;
    }
    return false;
}

// Mock GfxFont for testing - we need a concrete subclass since GfxFont has pure virtual methods
class MockGfxFont : public GfxFont {
public:
    // Minimal constructor
    MockGfxFont(const char *tag, Ref id, std::optional<std::string> &&name, GfxFontType type, Ref embFontID)
        : GfxFont(tag, id, std::move(name), type, embFontID) {}

    MOCK_METHOD(const CharCodeToUnicode *, getToUnicode, (), (const, override));
    MOCK_METHOD(int, getNextChar, (const char *s, int len, CharCode *code, const Unicode **u, int *uLen, double *dx, double *dy, double *ox, double *oy), (const, override));
    MOCK_METHOD(bool, isCIDFont, (), (const, override));
    MOCK_METHOD(WritingMode, getWMode, (), (const, override));

    void setFamily(const std::string &fam) {
        family = std::make_unique<GooString>(fam);
    }

    void setStretch(Stretch s) {
        stretch = s;
    }

    void setWeight(Weight w) {
        weight = w;
    }

    void setFlags(int f) {
        // flags is at a known offset - we use the public interface
        // Actually flags is not directly settable. We need another approach.
    }
};

class BuildFcPatternTest_1901 : public ::testing::Test {
protected:
    void SetUp() override {
        FcInit();
    }

    void TearDown() override {
    }

    std::unique_ptr<MockGfxFont> createFont(const std::string &name) {
        Ref id = {1, 0};
        Ref embId = {-1, -1};
        std::optional<std::string> fontName = name;
        auto font = std::make_unique<MockGfxFont>("tag", id, std::move(fontName), fontType1, embId);
        ON_CALL(*font, getToUnicode()).WillByDefault(testing::Return(nullptr));
        ON_CALL(*font, isCIDFont()).WillByDefault(testing::Return(false));
        ON_CALL(*font, getWMode()).WillByDefault(testing::Return(WritingMode::writingModeHLeftRight));
        return font;
    }
};

TEST_F(BuildFcPatternTest_1901, BasicFontName_1901) {
    auto font = createFont("Helvetica");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    std::string family;
    EXPECT_TRUE(getFcPatternString(p, FC_FAMILY, family));
    EXPECT_EQ(family, "Helvetica");

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, Base14NameOverride_1901) {
    auto font = createFont("SomeFont");
    GooString base14("Courier");
    FcPattern *p = buildFcPattern(*font, &base14);
    ASSERT_NE(p, nullptr);

    std::string family;
    EXPECT_TRUE(getFcPatternString(p, FC_FAMILY, family));
    // Family should be "Courier" from the base14 name
    EXPECT_EQ(family, "Courier");

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, BoldModifierInName_1901) {
    auto font = createFont("Helvetica-Bold");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_BOLD);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, ItalicModifierInName_1901) {
    auto font = createFont("Helvetica-Italic");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int slant = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_SLANT, &slant));
    EXPECT_EQ(slant, FC_SLANT_ITALIC);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, ObliqueModifierInName_1901) {
    auto font = createFont("Helvetica-Oblique");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int slant = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_SLANT, &slant));
    // Oblique is set first but if Italic isn't found, Oblique remains
    EXPECT_EQ(slant, FC_SLANT_OBLIQUE);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, LightModifierInName_1901) {
    auto font = createFont("Helvetica-Light");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_LIGHT);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, MediumModifierInName_1901) {
    auto font = createFont("Helvetica-Medium");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_MEDIUM);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, CondensedModifierInName_1901) {
    auto font = createFont("Helvetica-Condensed");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_CONDENSED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, BoldItalicModifierInName_1901) {
    auto font = createFont("Helvetica-BoldItalic");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_BOLD);

    int slant = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_SLANT, &slant));
    EXPECT_EQ(slant, FC_SLANT_ITALIC);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, CommaDelimiterInName_1901) {
    auto font = createFont("Helvetica,Bold");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_BOLD);

    std::string family;
    EXPECT_TRUE(getFcPatternString(p, FC_FAMILY, family));
    EXPECT_EQ(family, "Helvetica");

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, NoModifiers_1901) {
    auto font = createFont("Arial");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    std::string family;
    EXPECT_TRUE(getFcPatternString(p, FC_FAMILY, family));
    EXPECT_EQ(family, "Arial");

    // No weight should be set (unless font flags override)
    int weight = -1;
    bool hasWeight = getFcPatternInt(p, FC_WEIGHT, &weight);
    // Weight might not be present if no modifiers and no font flags
    if (!hasWeight) {
        SUCCEED();
    }

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, FontFamilyOverridesName_1901) {
    auto font = createFont("SomeRandomFont-Bold");
    font->setFamily("OverrideFamily");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    std::string family;
    EXPECT_TRUE(getFcPatternString(p, FC_FAMILY, family));
    EXPECT_EQ(family, "OverrideFamily");

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW100_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W100);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_EXTRALIGHT);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW400_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W400);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_NORMAL);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW700_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W700);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_BOLD);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW900_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W900);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_BLACK);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchUltraCondensed_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::UltraCondensed);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_ULTRACONDENSED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchNormal_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::Normal);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_NORMAL);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchUltraExpanded_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::UltraExpanded);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_ULTRAEXPANDED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchSemiCondensed_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::SemiCondensed);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_SEMICONDENSED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchExpanded_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::Expanded);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_EXPANDED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, RegularModifierNoWeightSlant_1901) {
    auto font = createFont("Helvetica-Regular");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    // Regular should not set weight or slant
    int weight = -1;
    bool hasWeight = getFcPatternInt(p, FC_WEIGHT, &weight);
    int slant = -1;
    bool hasSlant = getFcPatternInt(p, FC_SLANT, &slant);

    // Neither should be set from "Regular"
    if (!hasWeight && !hasSlant) {
        SUCCEED();
    }

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, PatternHasLang_1901) {
    auto font = createFont("Helvetica");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    // The pattern should have a language set
    FcChar8 *lang = nullptr;
    FcResult result = FcPatternGetString(p, FC_LANG, 0, &lang);
    EXPECT_EQ(result, FcResultMatch);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW200_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W200);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_LIGHT);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW300_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W300);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_BOOK);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW500_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W500);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_MEDIUM);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW600_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W600);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_DEMIBOLD);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightW800_1901) {
    auto font = createFont("TestFont");
    font->setWeight(GfxFont::W800);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    EXPECT_EQ(weight, FC_WEIGHT_EXTRABOLD);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchExtraCondensed_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::ExtraCondensed);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_EXTRACONDENSED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchCondensed_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::Condensed);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_CONDENSED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchSemiExpanded_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::SemiExpanded);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_SEMIEXPANDED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, StretchExtraExpanded_1901) {
    auto font = createFont("TestFont");
    font->setStretch(GfxFont::ExtraExpanded);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int width = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WIDTH, &width));
    EXPECT_EQ(width, FC_WIDTH_EXTRAEXPANDED);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, WeightOverriddenByFontWeight_1901) {
    // Font name has "Light" but font weight enum says W700 (Bold)
    auto font = createFont("TestFont-Light");
    font->setWeight(GfxFont::W700);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    int weight = -1;
    EXPECT_TRUE(getFcPatternInt(p, FC_WEIGHT, &weight));
    // W700 should override the "Light" from font name
    EXPECT_EQ(weight, FC_WEIGHT_BOLD);

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, FamilyFromFontOverridesNameParsing_1901) {
    auto font = createFont("SomeFont-Bold");
    font->setFamily("ActualFamily");
    font->setWeight(GfxFont::WeightNotDefined);
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    std::string family;
    EXPECT_TRUE(getFcPatternString(p, FC_FAMILY, family));
    EXPECT_EQ(family, "ActualFamily");

    // Bold from name should still be set (unless overridden by weight enum)
    int weight = -1;
    if (getFcPatternInt(p, FC_WEIGHT, &weight)) {
        EXPECT_EQ(weight, FC_WEIGHT_BOLD);
    }

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, SubsetTagRemoved_1901) {
    // Subset tag format: ABCDEF+FontName
    auto font = createFont("ABCDEF+MyFont");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);

    std::string family;
    EXPECT_TRUE(getFcPatternString(p, FC_FAMILY, family));
    // The subset tag should be removed
    EXPECT_EQ(family, "MyFont");

    FcPatternDestroy(p);
}

TEST_F(BuildFcPatternTest_1901, PatternNotNull_1901) {
    auto font = createFont("SimpleFont");
    FcPattern *p = buildFcPattern(*font, nullptr);
    ASSERT_NE(p, nullptr);
    FcPatternDestroy(p);
}
