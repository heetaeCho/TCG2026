#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cairo.h>

#include <array>



// Mocking the necessary structures and functions for testing.

struct FontMock {

    MOCK_CONST_METHOD0(getFontBBox, const std::array<double, 4>&());

};



struct type3_font_info_t {

    FontMock* font;

};



namespace {



TEST(InitType3GlyphTest_1752, NormalOperation_1752) {

    // Arrange

    cairo_scaled_font_t scaled_font{};

    cairo_font_extents_t extents{};

    type3_font_info_t info{};

    FontMock mockFont;

    

    const std::array<double, 4> bbox = {0.0, -1.0, 1.0, 2.0}; // Example BBox

    EXPECT_CALL(mockFont, getFontBBox()).WillOnce(::testing::Return(bbox));

    

    cairo_font_face_t* font_face = reinterpret_cast<cairo_font_face_t*>(&info);

    cairo_scaled_font_set_font_face(&scaled_font, font_face);

    cairo_font_face_set_user_data(font_face, &type3_font_key, &info, nullptr);



    // Act

    cairo_status_t status = _init_type3_glyph(&scaled_font, nullptr, &extents);



    // Assert

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    EXPECT_DOUBLE_EQ(extents.ascent, 2.0); // y2

    EXPECT_DOUBLE_EQ(extents.descent, -2.0); // -y1

    EXPECT_DOUBLE_EQ(extents.height, 4.0); // ascent + descent

    EXPECT_DOUBLE_EQ(extents.max_x_advance, 2.0); // x2 - x1

    EXPECT_DOUBLE_EQ(extents.max_y_advance, 0.0);

}



TEST(InitType3GlyphTest_1752, BoundaryConditions_ZeroBBox_1752) {

    // Arrange

    cairo_scaled_font_t scaled_font{};

    cairo_font_extents_t extents{};

    type3_font_info_t info{};

    FontMock mockFont;

    

    const std::array<double, 4> bbox = {0.0, 0.0, 0.0, 0.0}; // Zero BBox

    EXPECT_CALL(mockFont, getFontBBox()).WillOnce(::testing::Return(bbox));

    

    cairo_font_face_t* font_face = reinterpret_cast<cairo_font_face_t*>(&info);

    cairo_scaled_font_set_font_face(&scaled_font, font_face);

    cairo_font_face_set_user_data(font_face, &type3_font_key, &info, nullptr);



    // Act

    cairo_status_t status = _init_type3_glyph(&scaled_font, nullptr, &extents);



    // Assert

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    EXPECT_DOUBLE_EQ(extents.ascent, 0.0); 

    EXPECT_DOUBLE_EQ(extents.descent, 0.0); 

    EXPECT_DOUBLE_EQ(extents.height, 0.0); 

    EXPECT_DOUBLE_EQ(extents.max_x_advance, 0.0); 

    EXPECT_DOUBLE_EQ(extents.max_y_advance, 0.0);

}



TEST(InitType3GlyphTest_1752, BoundaryConditions_NegativeBBox_1752) {

    // Arrange

    cairo_scaled_font_t scaled_font{};

    cairo_font_extents_t extents{};

    type3_font_info_t info{};

    FontMock mockFont;

    

    const std::array<double, 4> bbox = {-1.0, -2.0, -0.5, -0.8}; // Negative BBox

    EXPECT_CALL(mockFont, getFontBBox()).WillOnce(::testing::Return(bbox));

    

    cairo_font_face_t* font_face = reinterpret_cast<cairo_font_face_t*>(&info);

    cairo_scaled_font_set_font_face(&scaled_font, font_face);

    cairo_font_face_set_user_data(font_face, &type3_font_key, &info, nullptr);



    // Act

    cairo_status_t status = _init_type3_glyph(&scaled_font, nullptr, &extents);



    // Assert

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    EXPECT_DOUBLE_EQ(extents.ascent, -0.8); 

    EXPECT_DOUBLE_EQ(extents.descent, 0.8); 

    EXPECT_DOUBLE_EQ(extents.height, 1.6); 

    EXPECT_DOUBLE_EQ(extents.max_x_advance, 1.5); // x2 - x1

    EXPECT_DOUBLE_EQ(extents.max_y_advance, 0.0);

}



} // namespace
