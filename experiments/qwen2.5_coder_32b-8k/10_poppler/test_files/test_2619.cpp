#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlFonts.h"

#include <memory>



class HtmlFontTest_2619 : public ::testing::Test {

protected:

    std::unique_ptr<GfxFont> mockGfxFont;

    GfxRGB mockRgb = {0, 0, 0};

    double opacity = 1.0;



    void SetUp() override {

        // Assuming a way to create a mock or dummy GfxFont object

        mockGfxFont = std::make_unique<GfxFont>();

    }



    HtmlFont createHtmlFont(bool italic) {

        HtmlFont font(*mockGfxFont, 12, mockRgb, opacity);

        // Manually set the italic state since we cannot directly modify private members

        const_cast<bool&>(font.italic) = italic;

        return font;

    }

};



TEST_F(HtmlFontTest_2619, IsItalic_ReturnsTrueWhenItalic_2619) {

    HtmlFont font = createHtmlFont(true);

    EXPECT_TRUE(font.isItalic());

}



TEST_F(HtmlFontTest_2619, IsItalic_ReturnsFalseWhenNotItalic_2619) {

    HtmlFont font = createHtmlFont(false);

    EXPECT_FALSE(font.isItalic());

}



TEST_F(HtmlFontTest_2619, GetSize_ReturnsCorrectSize_2619) {

    int size = 14;

    HtmlFont font(*mockGfxFont, size, mockRgb, opacity);

    EXPECT_EQ(font.getSize(), size);

}



TEST_F(HtmlFontTest_2619, GetLineSize_ReturnsInitialValue_2619) {

    HtmlFont font(*mockGfxFont, 12, mockRgb, opacity);

    EXPECT_EQ(font.getLineSize(), 0); // Assuming default initialization is 0

}



TEST_F(HtmlFontTest_2619, SetLineSize_ChangesLineSizeCorrectly_2619) {

    int newLineSize = 18;

    HtmlFont font(*mockGfxFont, 12, mockRgb, opacity);

    font.setLineSize(newLineSize);

    EXPECT_EQ(font.getLineSize(), newLineSize);

}



TEST_F(HtmlFontTest_2619, IsBold_ReturnsFalseByDefault_2619) {

    HtmlFont font(*mockGfxFont, 12, mockRgb, opacity);

    EXPECT_FALSE(font.isBold());

}



TEST_F(HtmlFontTest_2619, IsRotOrSkewed_ReturnsFalseByDefault_2619) {

    HtmlFont font(*mockGfxFont, 12, mockRgb, opacity);

    EXPECT_FALSE(font.isRotOrSkewed());

}



TEST_F(HtmlFontTest_2619, GetRotMat_ReturnsInitialValue_2619) {

    HtmlFont font(*mockGfxFont, 12, mockRgb, opacity);

    std::array<double, 4> identityMatrix = {1.0, 0.0, 0.0, 1.0}; // Assuming default is identity matrix

    EXPECT_EQ(font.getRotMat(), identityMatrix);

}



TEST_F(HtmlFontTest_2619, SetRotMat_ChangesRotationMatrixCorrectly_2619) {

    std::array<double, 4> newMatrix = {0.5, 0.5, -0.5, 0.5};

    HtmlFont font(*mockGfxFont, 12, mockRgb, opacity);

    font.setRotMat(newMatrix);

    EXPECT_EQ(font.getRotMat(), newMatrix);

}
