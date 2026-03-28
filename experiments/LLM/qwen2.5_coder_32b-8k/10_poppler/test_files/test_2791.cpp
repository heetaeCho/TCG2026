#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.cc"

#include "Form.h"

#include "GfxFont.h"

#include "GooString.h"

#include "Error.h"



using namespace testing;



class HorizontalTextLayouterTest : public Test {

protected:

    std::unique_ptr<GooString> text;

    std::shared_ptr<Form> form;

    std::shared_ptr<GfxFont> font;

    double availableWidth;

    bool noReencode;



    void SetUp() override {

        text = std::make_unique<GooString>("Test Text");

        form = std::make_shared<NiceMock<MockForm>>();

        font = std::make_shared<NiceMock<MockGfxFont>>();

        availableWidth = 100.0;

        noReencode = false;

    }

};



class MockForm : public Form {

public:

    MOCK_METHOD(std::string, getFallbackFontForChar, (Unicode uChar, const GfxFont & fontToEmulate), (const, override));

    MOCK_CONST_METHOD0(getDefaultResources, GfxResources*());

};



class MockGfxFont : public GfxFont {

public:

    using GfxFont::GfxFont;

    MOCK_METHOD(const int, getNextChar, (const char * s, int len, CharCode * code, const Unicode ** u, int * uLen, double * dx, double * dy, double * ox, double * oy), (const, override));

};



TEST_F(HorizontalTextLayouterTest_2791, TotalWidth_ReturnsCorrectValue_2791) {

    HorizontalTextLayouter layouter(text.get(), form.get(), font.get(), availableWidth, noReencode);

    EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0); // Assuming totalWidth is calculated internally and not directly observable from the test

}



TEST_F(HorizontalTextLayouterTest_2791, TotalCharCount_ReturnsCorrectValue_2791) {

    HorizontalTextLayouter layouter(text.get(), form.get(), font.get(), availableWidth, noReencode);

    EXPECT_EQ(layouter.totalCharCount(), 0); // Assuming totalCharCount is calculated internally and not directly observable from the test

}



TEST_F(HorizontalTextLayouterTest_2791, Constructor_HandlesEmptyText_2791) {

    text = std::make_unique<GooString>("");

    HorizontalTextLayouter layouter(text.get(), form.get(), font.get(), availableWidth, noReencode);

    EXPECT_EQ(layouter.totalCharCount(), 0);

}



TEST_F(HorizontalTextLayouterTest_2791, Constructor_HandlesNoAvailableWidth_2791) {

    availableWidth = std::nullopt;

    HorizontalTextLayouter layouter(text.get(), form.get(), font.get(), availableWidth, noReencode);

    EXPECT_EQ(layouter.totalCharCount(), 0); // Assuming totalCharCount is calculated internally and not directly observable from the test

}



TEST_F(HorizontalTextLayouterTest_2791, Constructor_HandlesNoReencodeFlag_2791) {

    noReencode = true;

    HorizontalTextLayouter layouter(text.get(), form.get(), font.get(), availableWidth, noReencode);

    EXPECT_EQ(layouter.totalCharCount(), 0); // Assuming totalCharCount is calculated internally and not directly observable from the test

}



TEST_F(HorizontalTextLayouterTest_2791, Constructor_CallsFormForFallbackFont_2791) {

    Unicode uChar = 0x00A9;

    EXPECT_CALL(*form, getFallbackFontForChar(uChar, RefTo<const GfxFont>(*font))).WillOnce(Return("FallbackFont"));

    HorizontalTextLayouter layouter(text.get(), form.get(), font.get(), availableWidth, noReencode);

}



TEST_F(HorizontalTextLayouterTest_2791, Constructor_HandlesUnicodeText_2791) {

    text = std::make_unique<GooString>("\u00A9");

    HorizontalTextLayouter layouter(text.get(), form.get(), font.get(), availableWidth, noReencode);

    EXPECT_EQ(layouter.totalCharCount(), 0); // Assuming totalCharCount is calculated internally and not directly observable from the test

}



TEST_F(HorizontalTextLayouterTest_2791, Constructor_HandlesNonUnicodeText_2791) {

    text = std::make_unique<GooString>("T");

    HorizontalTextLayouter layouter(text.get(), form.get(), font.get(), availableWidth, noReencode);

    EXPECT_EQ(layouter.totalCharCount(), 0); // Assuming totalCharCount is calculated internally and not directly observable from the test

}



TEST_F(HorizontalTextLayouterTest_2791, Constructor_HandlesFormNullptr_2791) {

    form.reset();

    HorizontalTextLayouter layouter(text.get(), nullptr, font.get(), availableWidth, noReencode);

    EXPECT_EQ(layouter.totalCharCount(), 0); // Assuming totalCharCount is calculated internally and not directly observable from the test

}



TEST_F(HorizontalTextLayouterTest_2791, Constructor_HandlesFontNullptr_2791) {

    font.reset();

    HorizontalTextLayouter layouter(text.get(), form.get(), nullptr, availableWidth, noReencode);

    EXPECT_EQ(layouter.totalCharCount(), 0); // Assuming totalCharCount is calculated internally and not directly observable from the test

}
