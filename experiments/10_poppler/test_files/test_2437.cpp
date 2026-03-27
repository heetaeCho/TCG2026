#include <gtest/gtest.h>

#include <cairo/cairo.h>



// Assuming guchar and gint are defined appropriately.

typedef unsigned char guchar;

typedef int gint;



extern "C" cairo_surface_t *create_surface_from_thumbnail_data(guchar *data, gint width, gint height, gint rowstride);



class CreateSurfaceFromThumbnailDataTest_2437 : public ::testing::Test {

protected:

    void SetUp() override {

        // No setup needed for this test suite

    }



    void TearDown() override {

        // No teardown needed for this test suite

    }

};



TEST_F(CreateSurfaceFromThumbnailDataTest_2437, NormalOperation_2437) {

    const gint width = 10;

    const gint height = 10;

    const gint rowstride = 3 * width; // Assuming RGB format with no padding



    guchar data[rowstride * height];

    for (gint i = 0; i < rowstride * height; ++i) {

        data[i] = static_cast<guchar>(i % 256);

    }



    cairo_surface_t* surface = create_surface_from_thumbnail_data(data, width, height, rowstride);

    ASSERT_NE(surface, nullptr);



    // Verify the surface properties

    EXPECT_EQ(cairo_image_surface_get_width(surface), width);

    EXPECT_EQ(cairo_image_surface_get_height(surface), height);

    EXPECT_EQ(cairo_image_surface_get_format(surface), CAIRO_FORMAT_RGB24);



    cairo_surface_destroy(surface);

}



TEST_F(CreateSurfaceFromThumbnailDataTest_2437, ZeroWidth_2437) {

    const gint width = 0;

    const gint height = 10;

    const gint rowstride = 3 * width; // Assuming RGB format with no padding



    guchar data[rowstride * height];

    for (gint i = 0; i < rowstride * height; ++i) {

        data[i] = static_cast<guchar>(i % 256);

    }



    cairo_surface_t* surface = create_surface_from_thumbnail_data(data, width, height, rowstride);

    EXPECT_EQ(surface, nullptr);

}



TEST_F(CreateSurfaceFromThumbnailDataTest_2437, ZeroHeight_2437) {

    const gint width = 10;

    const gint height = 0;

    const gint rowstride = 3 * width; // Assuming RGB format with no padding



    guchar data[rowstride * height];

    for (gint i = 0; i < rowstride * height; ++i) {

        data[i] = static_cast<guchar>(i % 256);

    }



    cairo_surface_t* surface = create_surface_from_thumbnail_data(data, width, height, rowstride);

    EXPECT_EQ(surface, nullptr);

}



TEST_F(CreateSurfaceFromThumbnailDataTest_2437, ZeroRowStride_2437) {

    const gint width = 10;

    const gint height = 10;

    const gint rowstride = 0;



    guchar data[rowstride * height];

    for (gint i = 0; i < rowstride * height; ++i) {

        data[i] = static_cast<guchar>(i % 256);

    }



    cairo_surface_t* surface = create_surface_from_thumbnail_data(data, width, height, rowstride);

    EXPECT_EQ(surface, nullptr);

}



TEST_F(CreateSurfaceFromThumbnailDataTest_2437, NullData_2437) {

    const gint width = 10;

    const gint height = 10;

    const gint rowstride = 3 * width; // Assuming RGB format with no padding



    guchar* data = nullptr;



    cairo_surface_t* surface = create_surface_from_thumbnail_data(data, width, height, rowstride);

    EXPECT_EQ(surface, nullptr);

}



TEST_F(CreateSurfaceFromThumbnailDataTest_2437, LargeValues_2437) {

    const gint width = 1000;

    const gint height = 1000;

    const gint rowstride = 3 * width; // Assuming RGB format with no padding



    guchar data[rowstride * height];

    for (gint i = 0; i < rowstride * height; ++i) {

        data[i] = static_cast<guchar>(i % 256);

    }



    cairo_surface_t* surface = create_surface_from_thumbnail_data(data, width, height, rowstride);

    ASSERT_NE(surface, nullptr);



    // Verify the surface properties

    EXPECT_EQ(cairo_image_surface_get_width(surface), width);

    EXPECT_EQ(cairo_image_surface_get_height(surface), height);

    EXPECT_EQ(cairo_image_surface_get_format(surface), CAIRO_FORMAT_RGB24);



    cairo_surface_destroy(surface);

}
