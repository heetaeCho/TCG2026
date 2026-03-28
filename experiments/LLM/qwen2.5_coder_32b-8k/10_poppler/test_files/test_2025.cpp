#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.cc"

#include "GooString.h"

#include "Form.h"

#include "GfxFont.h"



using namespace testing;



class MockForm : public Form {

public:

    MOCK_METHOD(std::string, findFontInDefaultResources, (const std::string &fontFamily, const std::string &fontStyle), (const, override));

};



class MockGfxFont : public GfxFont {

public:

    using GfxFont::GfxFont;

    MOCK_METHOD(double, getAscent, (), (const, override));

    MOCK_METHOD(double, getDescent, (), (const, override));

};



class DrawMultiLineTextTest_2025 : public Test {

protected:

    std::unique_ptr<MockForm> form;

    std::unique_ptr<MockGfxFont> font;



    void SetUp() override {

        form = std::make_unique<MockForm>();

        font = std::make_unique<MockGfxFont>("Arial", Ref(), "Arial", GfxFontType::type1, Ref());

    }

};



TEST_F(DrawMultiLineTextTest_2025, PutIncreasesCount_2025) {

    ON_CALL(*form, findFontInDefaultResources(_, _)).WillByDefault(Return("Arial"));

    EXPECT_CALL(*font, getAscent()).WillOnce(Return(1.0));

    EXPECT_CALL(*font, getDescent()).WillOnce(Return(-0.2));



    auto result = drawMultiLineText("Hello\nWorld", 100, form.get(), *font, "Arial", 12, VariableTextQuadding::leftJustified, 2);

    EXPECT_EQ(result.nLines, 2);

}



TEST_F(DrawMultiLineTextTest_2025, SingleLineText_2025) {

    ON_CALL(*form, findFontInDefaultResources(_, _)).WillByDefault(Return("Arial"));

    EXPECT_CALL(*font, getAscent()).WillOnce(Return(1.0));

    EXPECT_CALL(*font, getDescent()).WillOnce(Return(-0.2));



    auto result = drawMultiLineText("Hello", 100, form.get(), *font, "Arial", 12, VariableTextQuadding::leftJustified, 2);

    EXPECT_EQ(result.nLines, 1);

}



TEST_F(DrawMultiLineTextTest_2025, RightJustifiedText_2025) {

    ON_CALL(*form, findFontInDefaultResources(_, _)).WillByDefault(Return("Arial"));

    EXPECT_CALL(*font, getAscent()).WillOnce(Return(1.0));

    EXPECT_CALL(*font, getDescent()).WillOnce(Return(-0.2));



    auto result = drawMultiLineText("Hello\nWorld", 100, form.get(), *font, "Arial", 12, VariableTextQuadding::rightJustified, 2);

    EXPECT_EQ(result.nLines, 2);

}



TEST_F(DrawMultiLineTextTest_2025, CenteredText_2025) {

    ON_CALL(*form, findFontInDefaultResources(_, _)).WillByDefault(Return("Arial"));

    EXPECT_CALL(*font, getAscent()).WillOnce(Return(1.0));

    EXPECT_CALL(*font, getDescent()).WillOnce(Return(-0.2));



    auto result = drawMultiLineText("Hello\nWorld", 100, form.get(), *font, "Arial", 12, VariableTextQuadding::centered, 2);

    EXPECT_EQ(result.nLines, 2);

}



TEST_F(DrawMultiLineTextTest_2025, EmptyText_2025) {

    ON_CALL(*form, findFontInDefaultResources(_, _)).WillByDefault(Return("Arial"));

    EXPECT_CALL(*font, getAscent()).WillOnce(Return(1.0));

    EXPECT_CALL(*font, getDescent()).WillOnce(Return(-0.2));



    auto result = drawMultiLineText("", 100, form.get(), *font, "Arial", 12, VariableTextQuadding::leftJustified, 2);

    EXPECT_EQ(result.nLines, 0);

}



TEST_F(DrawMultiLineTextTest_2025, UnicodeBOMHandling_2025) {

    ON_CALL(*form, findFontInDefaultResources(_, _)).WillByDefault(Return("Arial"));

    EXPECT_CALL(*font, getAscent()).WillOnce(Return(1.0));

    EXPECT_CALL(*font, getDescent()).WillOnce(Return(-0.2));



    auto result = drawMultiLineText("\ufeffHello\nWorld", 100, form.get(), *font, "Arial", 12, VariableTextQuadding::leftJustified, 2);

    EXPECT_EQ(result.nLines, 2);

}



TEST_F(DrawMultiLineTextTest_2025, LargeBorderWidth_2025) {

    ON_CALL(*form, findFontInDefaultResources(_, _)).WillByDefault(Return("Arial"));

    EXPECT_CALL(*font, getAscent()).WillOnce(Return(1.0));

    EXPECT_CALL(*font, getDescent()).WillOnce(Return(-0.2));



    auto result = drawMultiLineText("Hello\nWorld", 100, form.get(), *font, "Arial", 12, VariableTextQuadding::leftJustified, 50);

    EXPECT_EQ(result.nLines, 2);

}



TEST_F(DrawMultiLineTextTest_2025, SmallAvailableWidth_2025) {

    ON_CALL(*form, findFontInDefaultResources(_, _)).WillByDefault(Return("Arial"));

    EXPECT_CALL(*font, getAscent()).WillOnce(Return(1.0));

    EXPECT_CALL(*font, getDescent()).WillOnce(Return(-0.2));



    auto result = drawMultiLineText("Hello\nWorld", 5, form.get(), *font, "Arial", 12, VariableTextQuadding::leftJustified, 2);

    EXPECT_EQ(result.nLines, 4); // Assuming each character needs more than the available width

}
