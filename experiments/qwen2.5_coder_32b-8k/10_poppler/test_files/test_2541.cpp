#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler-structure-element.cc"

#include "./TestProjects/poppler/poppler/MarkedContentOutputDev.h"

#include "./TestProjects/poppler/goo/GooString.h"

#include "./TestProjects/poppler/poppler/GfxFont.h"



using namespace GfxFont;

using ::testing::Return;

using ::testing::_;



class TextSpanMock : public TextSpan {

public:

    MOCK_CONST_METHOD0(getText, const GooString*());

    MOCK_CONST_METHOD0(getFont, std::shared_ptr<GfxFont>());

    MOCK_CONST_METHOD0(getColor, GfxRGB());

};



TEST(TextSpanToPopplerTextSpanTest_2541, NormalOperationWithTextAndFont_2541) {

    auto mock_text_span = std::make_unique<TextSpanMock>();

    auto font_mock = std::make_shared<GfxFontMock>();



    const char* text_data = "Sample Text";

    auto goo_string = std::make_unique<GooString>(text_data);



    GfxRGB color{0.1, 0.2, 0.3};



    EXPECT_CALL(*mock_text_span, getText()).WillRepeatedly(Return(goo_string.get()));

    EXPECT_CALL(*mock_text_span, getFont()).WillRepeatedly(Return(font_mock));

    EXPECT_CALL(*mock_text_span, getColor()).WillRepeatedly(Return(color));



    EXPECT_CALL(*font_mock, isFixedWidth()).WillOnce(Return(true));

    EXPECT_CALL(*font_mock, isSerif()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isItalic()).WillOnce(Return(true));

    EXPECT_CALL(*font_mock, isBold()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W700));



    const GooString* family_name = new GooString("Sample Font");

    EXPECT_CALL(*font_mock, getFamily()).WillRepeatedly(Return(family_name));



    PopplerTextSpan* result_span = text_span_poppler_text_span(*mock_text_span);



    ASSERT_STREQ(result_span->text, "Sample Text");

    EXPECT_EQ(result_span->color.red, 6554);

    EXPECT_EQ(result_span->color.green, 13107);

    EXPECT_EQ(result_span->color.blue, 19662);

    EXPECT_STREQ(result_span->font_name, "Sample Font");

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_FIXED_WIDTH);

    EXPECT_FALSE(result_span->flags & POPPLER_TEXT_SPAN_SERIF);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_ITALIC);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);



    g_free(result_span->text);

    g_free(result_span->font_name);

    delete result_span;

}



TEST(TextSpanToPopplerTextSpanTest_2541, NoTextNoFont_2541) {

    auto mock_text_span = std::make_unique<TextSpanMock>();



    EXPECT_CALL(*mock_text_span, getText()).WillRepeatedly(Return(nullptr));

    EXPECT_CALL(*mock_text_span, getFont()).WillRepeatedly(Return(nullptr));



    PopplerTextSpan* result_span = text_span_poppler_text_span(*mock_text_span);



    ASSERT_EQ(result_span->text, nullptr);

    EXPECT_EQ(result_span->color.red, 0);

    EXPECT_EQ(result_span->color.green, 0);

    EXPECT_EQ(result_span->color.blue, 0);

    EXPECT_EQ(result_span->font_name, nullptr);

    EXPECT_FALSE(result_span->flags & POPPLER_TEXT_SPAN_FIXED_WIDTH);

    EXPECT_FALSE(result_span->flags & POPPLER_TEXT_SPAN_SERIF);

    EXPECT_FALSE(result_span->flags & POPPLER_TEXT_SPAN_ITALIC);

    EXPECT_FALSE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);



    delete result_span;

}



TEST(TextSpanToPopplerTextSpanTest_2541, FontWithNoFamilyName_2541) {

    auto mock_text_span = std::make_unique<TextSpanMock>();

    auto font_mock = std::make_shared<GfxFontMock>();



    const char* text_data = "Sample Text";

    auto goo_string = std::make_unique<GooString>(text_data);



    GfxRGB color{0.1, 0.2, 0.3};



    EXPECT_CALL(*mock_text_span, getText()).WillRepeatedly(Return(goo_string.get()));

    EXPECT_CALL(*mock_text_span, getFont()).WillRepeatedly(Return(font_mock));

    EXPECT_CALL(*mock_text_span, getColor()).WillRepeatedly(Return(color));



    EXPECT_CALL(*font_mock, isFixedWidth()).WillOnce(Return(true));

    EXPECT_CALL(*font_mock, isSerif()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isItalic()).WillOnce(Return(true));

    EXPECT_CALL(*font_mock, isBold()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W700));



    EXPECT_CALL(*font_mock, getFamily()).WillRepeatedly(Return(nullptr));



    PopplerTextSpan* result_span = text_span_poppler_text_span(*mock_text_span);



    ASSERT_STREQ(result_span->text, "Sample Text");

    EXPECT_EQ(result_span->color.red, 6554);

    EXPECT_EQ(result_span->color.green, 13107);

    EXPECT_EQ(result_span->color.blue, 19662);

    EXPECT_EQ(result_span->font_name, nullptr);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_FIXED_WIDTH);

    EXPECT_FALSE(result_span->flags & POPPLER_TEXT_SPAN_SERIF);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_ITALIC);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);



    g_free(result_span->text);

    delete result_span;

}



TEST(TextSpanToPopplerTextSpanTest_2541, FontWithOptionalName_2541) {

    auto mock_text_span = std::make_unique<TextSpanMock>();

    auto font_mock = std::make_shared<GfxFontMock>();



    const char* text_data = "Sample Text";

    auto goo_string = std::make_unique<GooString>(text_data);



    GfxRGB color{0.1, 0.2, 0.3};



    EXPECT_CALL(*mock_text_span, getText()).WillRepeatedly(Return(goo_string.get()));

    EXPECT_CALL(*mock_text_span, getFont()).WillRepeatedly(Return(font_mock));

    EXPECT_CALL(*mock_text_span, getColor()).WillRepeatedly(Return(color));



    EXPECT_CALL(*font_mock, isFixedWidth()).WillOnce(Return(true));

    EXPECT_CALL(*font_mock, isSerif()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isItalic()).WillOnce(Return(true));

    EXPECT_CALL(*font_mock, isBold()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W700));



    EXPECT_CALL(*font_mock, getFamily()).WillRepeatedly(Return(nullptr));



    std::optional<std::string> font_name = "Optional Font";

    EXPECT_CALL(*font_mock, getName()).WillOnce(Return(font_name));



    PopplerTextSpan* result_span = text_span_poppler_text_span(*mock_text_span);



    ASSERT_STREQ(result_span->text, "Sample Text");

    EXPECT_EQ(result_span->color.red, 6554);

    EXPECT_EQ(result_span->color.green, 13107);

    EXPECT_EQ(result_span->color.blue, 19662);

    EXPECT_STREQ(result_span->font_name, "Optional Font");

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_FIXED_WIDTH);

    EXPECT_FALSE(result_span->flags & POPPLER_TEXT_SPAN_SERIF);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_ITALIC);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);



    g_free(result_span->text);

    g_free(result_span->font_name);

    delete result_span;

}



TEST(TextSpanToPopplerTextSpanTest_2541, BoundaryWeightCases_2541) {

    auto mock_text_span = std::make_unique<TextSpanMock>();

    auto font_mock = std::make_shared<GfxFontMock>();



    GfxRGB color{0.1, 0.2, 0.3};



    EXPECT_CALL(*mock_text_span, getText()).WillRepeatedly(Return(nullptr));

    EXPECT_CALL(*mock_text_span, getFont()).WillRepeatedly(Return(font_mock));

    EXPECT_CALL(*mock_text_span, getColor()).WillRepeatedly(Return(color));



    std::optional<std::string> font_name = "Test Font";

    EXPECT_CALL(*font_mock, getName()).WillOnce(Return(font_name));

    EXPECT_CALL(*font_mock, isFixedWidth()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isSerif()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isItalic()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isBold()).WillOnce(Return(false));



    // Test Weight W500

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W500));

    PopplerTextSpan* result_span = text_span_poppler_text_span(*mock_text_span);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);

    delete result_span;



    // Test Weight W600

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W600));

    result_span = text_span_poppler_text_span(*mock_text_span);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);

    delete result_span;



    // Test Weight W700

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W700));

    result_span = text_span_poppler_text_span(*mock_text_span);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);

    delete result_span;



    // Test Weight W800

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W800));

    result_span = text_span_poppler_text_span(*mock_text_span);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);

    delete result_span;



    // Test Weight W900

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W900));

    result_span = text_span_poppler_text_span(*mock_text_span);

    EXPECT_TRUE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);

    delete result_span;

}



TEST(TextSpanToPopplerTextSpanTest_2541, WeightBelowThresholdNotBold_2541) {

    auto mock_text_span = std::make_unique<TextSpanMock>();

    auto font_mock = std::make_shared<GfxFontMock>();



    GfxRGB color{0.1, 0.2, 0.3};



    EXPECT_CALL(*mock_text_span, getText()).WillRepeatedly(Return(nullptr));

    EXPECT_CALL(*mock_text_span, getFont()).WillRepeatedly(Return(font_mock));

    EXPECT_CALL(*mock_text_span, getColor()).WillRepeatedly(Return(color));



    std::optional<std::string> font_name = "Test Font";

    EXPECT_CALL(*font_mock, getName()).WillOnce(Return(font_name));

    EXPECT_CALL(*font_mock, isFixedWidth()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isSerif()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isItalic()).WillOnce(Return(false));

    EXPECT_CALL(*font_mock, isBold()).WillOnce(Return(false));



    // Test Weight W400

    EXPECT_CALL(*font_mock, getWeight()).WillOnce(Return(W400));

    PopplerTextSpan* result_span = text_span_poppler_text_span(*mock_text_span);

    EXPECT_FALSE(result_span->flags & POPPLER_TEXT_SPAN_BOLD);

    delete result_span;

}
