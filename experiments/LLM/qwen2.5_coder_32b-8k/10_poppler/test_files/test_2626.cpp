#include <gtest/gtest.h>

#include "HtmlFonts.h"

#include <array>



class HtmlFontTest_2626 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming GfxFont and GfxRGB are properly defined elsewhere in the codebase.

        GfxFont font;  // Mock or stub as necessary

        GfxRGB rgb = {0, 0, 0};  // Black color for simplicity

        double opacity = 1.0;

        test_font = std::make_unique<HtmlFont>(font, 12, rgb, opacity);

    }



    void TearDown() override {

        test_font.reset();

    }



    std::unique_ptr<HtmlFont> test_font;

};



TEST_F(HtmlFontTest_2626, GetRotMat_ReturnsArray_2626) {

    const auto& rot_mat = test_font->getRotMat();

    EXPECT_EQ(rot_mat.size(), 4);

}



TEST_F(HtmlFontTest_2626, SetAndGetRotMat_ConsistentValues_2626) {

    std::array<double, 4> new_rot_mat = {1.0, 0.0, 0.0, 1.0};

    test_font->setRotMat(new_rot_mat);

    const auto& rot_mat = test_font->getRotMat();

    EXPECT_EQ(rot_mat, new_rot_mat);

}



TEST_F(HtmlFontTest_2626, IsRotOrSkewed_DefaultValue_2626) {

    // Assuming default value is false

    EXPECT_FALSE(test_font->isRotOrSkewed());

}



TEST_F(HtmlFontTest_2626, GetSize_ReturnsSetValue_2626) {

    EXPECT_EQ(test_font->getSize(), 12);

}



TEST_F(HtmlFontTest_2626, SetAndGetLineSize_ConsistentValues_2626) {

    int new_line_size = 14;

    test_font->setLineSize(new_line_size);

    EXPECT_EQ(test_font->getLineSize(), new_line_size);

}



// Assuming isEqual and isEqualIgnoreBold return false when comparing with a different font

TEST_F(HtmlFontTest_2626, IsEqual_DifferentFont_ReturnsFalse_2626) {

    GfxFont another_font;  // Mock or stub as necessary

    GfxRGB rgb = {0, 0, 0};  // Black color for simplicity

    double opacity = 1.0;

    HtmlFont another_html_font(another_font, 14, rgb, opacity);

    EXPECT_FALSE(test_font->isEqual(another_html_font));

}



TEST_F(HtmlFontTest_2626, IsEqualIgnoreBold_DifferentFont_ReturnsFalse_2626) {

    GfxFont another_font;  // Mock or stub as necessary

    GfxRGB rgb = {0, 0, 0};  // Black color for simplicity

    double opacity = 1.0;

    HtmlFont another_html_font(another_font, 14, rgb, opacity);

    EXPECT_FALSE(test_font->isEqualIgnoreBold(another_html_font));

}
