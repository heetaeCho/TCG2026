#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"

#include "GooString.h"



class GfxFontMock : public GfxFont {

public:

    MOCK_CONST_METHOD0(isSubset, bool());

    MOCK_CONST_METHOD0(getNameWithoutSubsetTag, std::string());

    MOCK_CONST_METHOD0(getFamily, const GooString*());

    MOCK_CONST_METHOD0(getStretch, Stretch());

    MOCK_CONST_METHOD0(getWeight, Weight());

    MOCK_CONST_METHOD0(isFixedWidth, bool());

    MOCK_CONST_METHOD0(isItalic, bool());

    MOCK_CONST_METHOD0(isBold, bool());



    using GfxFont::GfxFont;

};



TEST(buildFcPatternTest_1901, NormalOperationRegularFont_1901) {

    GfxFontMock font("tag", Ref(), std::nullopt, GfxFontType::type1, Ref());

    EXPECT_CALL(font, getNameWithoutSubsetTag()).WillOnce(::testing::Return("Arial-Regular"));

    EXPECT_CALL(font, getFamily()).WillOnce(::testing::Return(new GooString("Arial")));

    EXPECT_CALL(font, isFixedWidth()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isItalic()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isBold()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, getStretch()).WillOnce(::testing::Return(GfxFont::Normal));

    EXPECT_CALL(font, getWeight()).WillOnce(::testing::Return(GfxFont::W400));



    FcPattern* pattern = buildFcPattern(font, nullptr);

    ASSERT_NE(pattern, nullptr);



    int slant;

    FcPatternGetInteger(pattern, FC_SLANT, 0, &slant);

    EXPECT_EQ(slant, FC_SLANT_ROMAN);



    int weight;

    FcPatternGetInteger(pattern, FC_WEIGHT, 0, &weight);

    EXPECT_EQ(weight, FC_WEIGHT_NORMAL);



    int width;

    FcPatternGetInteger(pattern, FC_WIDTH, 0, &width);

    EXPECT_EQ(width, FC_WIDTH_NORMAL);



    FcPatternDestroy(pattern);

}



TEST(buildFcPatternTest_1901, NormalOperationBoldItalicFont_1901) {

    GfxFontMock font("tag", Ref(), std::nullopt, GfxFontType::type1, Ref());

    EXPECT_CALL(font, getNameWithoutSubsetTag()).WillOnce(::testing::Return("Arial-BoldItalic"));

    EXPECT_CALL(font, getFamily()).WillOnce(::testing::Return(new GooString("Arial")));

    EXPECT_CALL(font, isFixedWidth()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isItalic()).WillOnce(::testing::Return(true));

    EXPECT_CALL(font, isBold()).WillOnce(::testing::Return(true));

    EXPECT_CALL(font, getStretch()).WillOnce(::testing::Return(GfxFont::Normal));

    EXPECT_CALL(font, getWeight()).WillOnce(::testing::Return(GfxFont::W700));



    FcPattern* pattern = buildFcPattern(font, nullptr);

    ASSERT_NE(pattern, nullptr);



    int slant;

    FcPatternGetInteger(pattern, FC_SLANT, 0, &slant);

    EXPECT_EQ(slant, FC_SLANT_ITALIC);



    int weight;

    FcPatternGetInteger(pattern, FC_WEIGHT, 0, &weight);

    EXPECT_EQ(weight, FC_WEIGHT_BOLD);



    int width;

    FcPatternGetInteger(pattern, FC_WIDTH, 0, &width);

    EXPECT_EQ(width, FC_WIDTH_NORMAL);



    FcPatternDestroy(pattern);

}



TEST(buildFcPatternTest_1901, BoundaryConditionEmptyFontName_1901) {

    GfxFontMock font("tag", Ref(), std::nullopt, GfxFontType::type1, Ref());

    EXPECT_CALL(font, getNameWithoutSubsetTag()).WillOnce(::testing::Return(""));

    EXPECT_CALL(font, getFamily()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(font, isFixedWidth()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isItalic()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isBold()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, getStretch()).WillOnce(::testing::Return(GfxFont::Normal));

    EXPECT_CALL(font, getWeight()).WillOnce(::testing::Return(GfxFont::W400));



    FcPattern* pattern = buildFcPattern(font, nullptr);

    ASSERT_NE(pattern, nullptr);



    int slant;

    FcResult slant_result = FcPatternGetInteger(pattern, FC_SLANT, 0, &slant);

    EXPECT_EQ(slant_result, FcResultNoMatch);



    int weight;

    FcResult weight_result = FcPatternGetInteger(pattern, FC_WEIGHT, 0, &weight);

    EXPECT_EQ(weight_result, FcResultNoMatch);



    int width;

    FcResult width_result = FcPatternGetInteger(pattern, FC_WIDTH, 0, &width);

    EXPECT_EQ(width_result, FcResultNoMatch);



    FcPatternDestroy(pattern);

}



TEST(buildFcPatternTest_1901, BoundaryConditionNullBase14Name_1901) {

    GfxFontMock font("tag", Ref(), std::nullopt, GfxFontType::type1, Ref());

    EXPECT_CALL(font, getNameWithoutSubsetTag()).WillOnce(::testing::Return("Arial-BoldItalic"));

    EXPECT_CALL(font, getFamily()).WillOnce(::testing::Return(new GooString("Arial")));

    EXPECT_CALL(font, isFixedWidth()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isItalic()).WillOnce(::testing::Return(true));

    EXPECT_CALL(font, isBold()).WillOnce(::testing::Return(true));

    EXPECT_CALL(font, getStretch()).WillOnce(::testing::Return(GfxFont::Normal));

    EXPECT_CALL(font, getWeight()).WillOnce(::testing::Return(GfxFont::W700));



    FcPattern* pattern = buildFcPattern(font, nullptr);

    ASSERT_NE(pattern, nullptr);



    int slant;

    FcPatternGetInteger(pattern, FC_SLANT, 0, &slant);

    EXPECT_EQ(slant, FC_SLANT_ITALIC);



    int weight;

    FcPatternGetInteger(pattern, FC_WEIGHT, 0, &weight);

    EXPECT_EQ(weight, FC_WEIGHT_BOLD);



    int width;

    FcPatternGetInteger(pattern, FC_WIDTH, 0, &width);

    EXPECT_EQ(width, FC_WIDTH_NORMAL);



    FcPatternDestroy(pattern);

}



TEST(buildFcPatternTest_1901, BoundaryConditionBase14NameProvided_1901) {

    GooString base14Name("Helvetica-BoldOblique");

    GfxFontMock font("tag", Ref(), std::nullopt, GfxFontType::type1, Ref());

    EXPECT_CALL(font, getNameWithoutSubsetTag()).WillOnce(::testing::ReturnRefOfCopy(base14Name));

    EXPECT_CALL(font, getFamily()).WillOnce(::testing::Return(new GooString("Helvetica")));

    EXPECT_CALL(font, isFixedWidth()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isItalic()).WillOnce(::testing::Return(true));

    EXPECT_CALL(font, isBold()).WillOnce(::testing::Return(true));

    EXPECT_CALL(font, getStretch()).WillOnce(::testing::Return(GfxFont::Normal));

    EXPECT_CALL(font, getWeight()).WillOnce(::testing::Return(GfxFont::W700));



    FcPattern* pattern = buildFcPattern(font, &base14Name);

    ASSERT_NE(pattern, nullptr);



    int slant;

    FcPatternGetInteger(pattern, FC_SLANT, 0, &slant);

    EXPECT_EQ(slant, FC_SLANT_OBLIQUE);



    int weight;

    FcPatternGetInteger(pattern, FC_WEIGHT, 0, &weight);

    EXPECT_EQ(weight, FC_WEIGHT_BOLD);



    int width;

    FcPatternGetInteger(pattern, FC_WIDTH, 0, &width);

    EXPECT_EQ(width, FC_WIDTH_NORMAL);



    FcPatternDestroy(pattern);

}



TEST(buildFcPatternTest_1901, ExceptionalCaseInvalidWeight_1901) {

    GfxFontMock font("tag", Ref(), std::nullopt, GfxFontType::type1, Ref());

    EXPECT_CALL(font, getNameWithoutSubsetTag()).WillOnce(::testing::Return("Arial"));

    EXPECT_CALL(font, getFamily()).WillOnce(::testing::Return(new GooString("Arial")));

    EXPECT_CALL(font, isFixedWidth()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isItalic()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isBold()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, getStretch()).WillOnce(::testing::Return(GfxFont::Normal));

    EXPECT_CALL(font, getWeight()).WillOnce(::testing::Return(static_cast<GfxFont::Weight>(0)));



    FcPattern* pattern = buildFcPattern(font, nullptr);

    ASSERT_NE(pattern, nullptr);



    int slant;

    FcResult slant_result = FcPatternGetInteger(pattern, FC_SLANT, 0, &slant);

    EXPECT_EQ(slant_result, FcResultNoMatch);



    int weight;

    FcResult weight_result = FcPatternGetInteger(pattern, FC_WEIGHT, 0, &weight);

    EXPECT_EQ(weight_result, FcResultNoMatch);



    int width;

    FcResult width_result = FcPatternGetInteger(pattern, FC_WIDTH, 0, &width);

    EXPECT_EQ(width_result, FcResultNoMatch);



    FcPatternDestroy(pattern);

}



TEST(buildFcPatternTest_1901, ExternalInteractionFamilyNameFromFont_1901) {

    GfxString familyName("TimesNewRoman");

    GfxFontMock font("tag", Ref(), std::nullopt, GfxFontType::type1, Ref());

    EXPECT_CALL(font, getNameWithoutSubsetTag()).WillOnce(::testing::Return("Times-NewRoman-Bold"));

    EXPECT_CALL(font, getFamily()).WillOnce(::testing::Return(&familyName));

    EXPECT_CALL(font, isFixedWidth()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isItalic()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isBold()).WillOnce(::testing::Return(true));

    EXPECT_CALL(font, getStretch()).WillOnce(::testing::Return(GfxFont::Normal));

    EXPECT_CALL(font, getWeight()).WillOnce(::testing::Return(GfxFont::W700));



    FcPattern* pattern = buildFcPattern(font, nullptr);

    ASSERT_NE(pattern, nullptr);



    int slant;

    FcPatternGetInteger(pattern, FC_SLANT, 0, &slant);

    EXPECT_EQ(slant, FC_SLANT_ROMAN);



    int weight;

    FcPatternGetInteger(pattern, FC_WEIGHT, 0, &weight);

    EXPECT_EQ(weight, FC_WEIGHT_BOLD);



    int width;

    FcPatternGetInteger(pattern, FC_WIDTH, 0, &width);

    EXPECT_EQ(width, FC_WIDTH_NORMAL);



    FcChar8* family_name = nullptr;

    FcPatternGetString(pattern, FC_FAMILY, 0, &family_name);

    EXPECT_STREQ(reinterpret_cast<const char*>(family_name), "TimesNewRoman");



    FcPatternDestroy(pattern);

}



TEST(buildFcPatternTest_1901, ExternalInteractionSpacingMonoFont_1901) {

    GfxFontMock font("tag", Ref(), std::nullopt, GfxFontType::type1, Ref());

    EXPECT_CALL(font, getNameWithoutSubsetTag()).WillOnce(::testing::Return("Courier"));

    EXPECT_CALL(font, getFamily()).WillOnce(::testing::Return(new GooString("Courier")));

    EXPECT_CALL(font, isFixedWidth()).WillOnce(::testing::Return(true));

    EXPECT_CALL(font, isItalic()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, isBold()).WillOnce(::testing::Return(false));

    EXPECT_CALL(font, getStretch()).WillOnce(::testing::Return(GfxFont::Normal));

    EXPECT_CALL(font, getWeight()).WillOnce(::testing::Return(GfxFont::W400));



    FcPattern* pattern = buildFcPattern(font, nullptr);

    ASSERT_NE(pattern, nullptr);



    int spacing;

    FcPatternGetInteger(pattern, FC_SPACING, 0, &spacing);

    EXPECT_EQ(spacing, FC_MONO);



    FcPatternDestroy(pattern);

}
