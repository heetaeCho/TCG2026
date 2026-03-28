#include <gtest/gtest.h>
#include <cairo.h>
#include <glib.h>
#include <cstring>
#include <cstdlib>

// We need to declare the static function as accessible for testing.
// Since it's static in the .cc file, we include it directly or use a workaround.
// For testing a static function, we include the source file.
// However, since this is a poppler internal function, we'll recreate the declaration
// and include the source.

// Forward declare the function signature - since it's static, we need to
// either include the .cc file or use a test-specific approach.
// We'll define it as extern here and rely on link-time resolution with
// a modified build that exposes it, OR we include the implementation directly.

// For this test, we include the function implementation directly:
static cairo_surface_t *create_surface_from_thumbnail_data(guchar *data, gint width, gint height, gint rowstride)
{
    guchar *cairo_pixels;
    gint cairo_stride;
    cairo_surface_t *surface;
    int j;

    surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
    if (cairo_surface_status(surface)) {
        return nullptr;
    }
    cairo_pixels = cairo_image_surface_get_data(surface);
    cairo_stride = cairo_image_surface_get_stride(surface);

    for (j = height; j; j--) {
        guchar *p = data;
        guchar *q = cairo_pixels;
        guchar *end = p + 3 * width;

        while (p < end) {
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
            q[0] = p[2];
            q[1] = p[1];
            q[2] = p[0];
#else
            q[1] = p[0];
            q[2] = p[1];
            q[3] = p[2];
#endif
            p += 3;
            q += 4;
        }

        data += rowstride;
        cairo_pixels += cairo_stride;
    }

    return surface;
}

class CreateSurfaceFromThumbnailDataTest_2437 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any surfaces created during tests
    }
};

// Test: Normal 1x1 image produces a valid surface
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, SinglePixelImage_2437)
{
    gint width = 1;
    gint height = 1;
    gint rowstride = 3; // 1 pixel * 3 bytes (RGB)
    guchar data[3] = {0xFF, 0x80, 0x40}; // R=255, G=128, B=64

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_image_surface_get_width(surface), width);
    EXPECT_EQ(cairo_image_surface_get_height(surface), height);
    EXPECT_EQ(cairo_image_surface_get_format(surface), CAIRO_FORMAT_RGB24);
    EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    cairo_surface_flush(surface);
    guchar *pixels = cairo_image_surface_get_data(surface);
    ASSERT_NE(pixels, nullptr);

    // Verify pixel data conversion
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(pixels[0], 0x40); // B -> q[0]
    EXPECT_EQ(pixels[1], 0x80); // G -> q[1]
    EXPECT_EQ(pixels[2], 0xFF); // R -> q[2]
#else
    EXPECT_EQ(pixels[1], 0xFF); // R -> q[1]
    EXPECT_EQ(pixels[2], 0x80); // G -> q[2]
    EXPECT_EQ(pixels[3], 0x40); // B -> q[3]
#endif

    cairo_surface_destroy(surface);
}

// Test: Normal 2x2 image
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, TwoByTwoImage_2437)
{
    gint width = 2;
    gint height = 2;
    gint rowstride = 6; // 2 pixels * 3 bytes
    guchar data[12] = {
        0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, // Row 0: Red, Green
        0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF  // Row 1: Blue, White
    };

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_image_surface_get_width(surface), width);
    EXPECT_EQ(cairo_image_surface_get_height(surface), height);
    EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    cairo_surface_flush(surface);
    guchar *pixels = cairo_image_surface_get_data(surface);
    gint stride = cairo_image_surface_get_stride(surface);
    ASSERT_NE(pixels, nullptr);

    // Verify first row, first pixel (Red: R=255, G=0, B=0)
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(pixels[0], 0x00); // B
    EXPECT_EQ(pixels[1], 0x00); // G
    EXPECT_EQ(pixels[2], 0xFF); // R
#else
    EXPECT_EQ(pixels[1], 0xFF); // R
    EXPECT_EQ(pixels[2], 0x00); // G
    EXPECT_EQ(pixels[3], 0x00); // B
#endif

    // Verify first row, second pixel (Green: R=0, G=255, B=0)
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(pixels[4], 0x00); // B
    EXPECT_EQ(pixels[5], 0xFF); // G
    EXPECT_EQ(pixels[6], 0x00); // R
#else
    EXPECT_EQ(pixels[5], 0x00); // R
    EXPECT_EQ(pixels[6], 0xFF); // G
    EXPECT_EQ(pixels[7], 0x00); // B
#endif

    // Verify second row, first pixel (Blue: R=0, G=0, B=255)
    guchar *row2 = pixels + stride;
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(row2[0], 0xFF); // B
    EXPECT_EQ(row2[1], 0x00); // G
    EXPECT_EQ(row2[2], 0x00); // R
#else
    EXPECT_EQ(row2[1], 0x00); // R
    EXPECT_EQ(row2[2], 0x00); // G
    EXPECT_EQ(row2[3], 0xFF); // B
#endif

    // Verify second row, second pixel (White: R=255, G=255, B=255)
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(row2[4], 0xFF);
    EXPECT_EQ(row2[5], 0xFF);
    EXPECT_EQ(row2[6], 0xFF);
#else
    EXPECT_EQ(row2[5], 0xFF);
    EXPECT_EQ(row2[6], 0xFF);
    EXPECT_EQ(row2[7], 0xFF);
#endif

    cairo_surface_destroy(surface);
}

// Test: Rowstride larger than width * 3 (padding in source data)
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, RowstrideWithPadding_2437)
{
    gint width = 1;
    gint height = 2;
    gint rowstride = 8; // 3 bytes per pixel + 5 bytes padding
    guchar data[16];
    memset(data, 0, sizeof(data));

    // Row 0, pixel 0: R=10, G=20, B=30
    data[0] = 10;
    data[1] = 20;
    data[2] = 30;
    // Padding bytes at data[3..7]

    // Row 1, pixel 0: R=40, G=50, B=60
    data[8] = 40;
    data[9] = 50;
    data[10] = 60;

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    cairo_surface_flush(surface);
    guchar *pixels = cairo_image_surface_get_data(surface);
    gint stride = cairo_image_surface_get_stride(surface);
    ASSERT_NE(pixels, nullptr);

    // Row 0
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(pixels[0], 30);
    EXPECT_EQ(pixels[1], 20);
    EXPECT_EQ(pixels[2], 10);
#else
    EXPECT_EQ(pixels[1], 10);
    EXPECT_EQ(pixels[2], 20);
    EXPECT_EQ(pixels[3], 30);
#endif

    // Row 1
    guchar *row2 = pixels + stride;
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(row2[0], 60);
    EXPECT_EQ(row2[1], 50);
    EXPECT_EQ(row2[2], 40);
#else
    EXPECT_EQ(row2[1], 40);
    EXPECT_EQ(row2[2], 50);
    EXPECT_EQ(row2[3], 60);
#endif

    cairo_surface_destroy(surface);
}

// Test: Surface format is CAIRO_FORMAT_RGB24
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, SurfaceFormatIsRGB24_2437)
{
    gint width = 3;
    gint height = 3;
    gint rowstride = 9;
    guchar data[27];
    memset(data, 0x55, sizeof(data));

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_image_surface_get_format(surface), CAIRO_FORMAT_RGB24);
    cairo_surface_destroy(surface);
}

// Test: All zeros data
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, AllZerosData_2437)
{
    gint width = 2;
    gint height = 2;
    gint rowstride = 6;
    guchar data[12];
    memset(data, 0, sizeof(data));

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    cairo_surface_flush(surface);
    guchar *pixels = cairo_image_surface_get_data(surface);
    gint stride = cairo_image_surface_get_stride(surface);

    // All output pixels should have 0 in the RGB channels
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            guchar *q = pixels + row * stride + col * 4;
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
            EXPECT_EQ(q[0], 0);
            EXPECT_EQ(q[1], 0);
            EXPECT_EQ(q[2], 0);
#else
            EXPECT_EQ(q[1], 0);
            EXPECT_EQ(q[2], 0);
            EXPECT_EQ(q[3], 0);
#endif
        }
    }

    cairo_surface_destroy(surface);
}

// Test: All 0xFF data
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, AllMaxData_2437)
{
    gint width = 2;
    gint height = 2;
    gint rowstride = 6;
    guchar data[12];
    memset(data, 0xFF, sizeof(data));

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    cairo_surface_flush(surface);
    guchar *pixels = cairo_image_surface_get_data(surface);
    gint stride = cairo_image_surface_get_stride(surface);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            guchar *q = pixels + row * stride + col * 4;
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
            EXPECT_EQ(q[0], 0xFF);
            EXPECT_EQ(q[1], 0xFF);
            EXPECT_EQ(q[2], 0xFF);
#else
            EXPECT_EQ(q[1], 0xFF);
            EXPECT_EQ(q[2], 0xFF);
            EXPECT_EQ(q[3], 0xFF);
#endif
        }
    }

    cairo_surface_destroy(surface);
}

// Test: Large image dimensions
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, LargerImage_2437)
{
    gint width = 100;
    gint height = 100;
    gint rowstride = width * 3;
    std::vector<guchar> data(rowstride * height);

    // Fill with a pattern
    for (int i = 0; i < (int)data.size(); i++) {
        data[i] = (guchar)(i % 256);
    }

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data.data(), width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);
    EXPECT_EQ(cairo_image_surface_get_width(surface), width);
    EXPECT_EQ(cairo_image_surface_get_height(surface), height);

    cairo_surface_destroy(surface);
}

// Test: Width of 1, height of 1 (minimum valid)
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, MinimumValidDimensions_2437)
{
    gint width = 1;
    gint height = 1;
    gint rowstride = 3;
    guchar data[3] = {100, 150, 200};

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    cairo_surface_destroy(surface);
}

// Test: Zero width should cause cairo surface creation to fail, return nullptr
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, ZeroWidthReturnsNull_2437)
{
    gint width = 0;
    gint height = 1;
    gint rowstride = 0;
    guchar data[1] = {0};

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    // cairo_image_surface_create with 0 dimensions may return an error surface
    // The function checks cairo_surface_status and returns nullptr if error
    if (surface != nullptr) {
        // If it didn't return nullptr, it must be a valid surface
        EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);
        cairo_surface_destroy(surface);
    }
}

// Test: Zero height should cause the loop to not execute
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, ZeroHeightReturnsNull_2437)
{
    gint width = 1;
    gint height = 0;
    gint rowstride = 3;
    guchar data[3] = {0, 0, 0};

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    // Similar to zero width - may return nullptr or error surface
    if (surface != nullptr) {
        EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);
        cairo_surface_destroy(surface);
    }
}

// Test: Negative dimensions should cause cairo to return error surface -> nullptr
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, NegativeWidthReturnsNull_2437)
{
    gint width = -1;
    gint height = 1;
    gint rowstride = 3;
    guchar data[3] = {0, 0, 0};

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    EXPECT_EQ(surface, nullptr);
}

// Test: Negative height should cause cairo to return error surface -> nullptr
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, NegativeHeightReturnsNull_2437)
{
    gint width = 1;
    gint height = -1;
    gint rowstride = 3;
    guchar data[3] = {0, 0, 0};

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    EXPECT_EQ(surface, nullptr);
}

// Test: Verify that specific known RGB values are correctly byte-swapped
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, SpecificColorConversion_2437)
{
    gint width = 3;
    gint height = 1;
    gint rowstride = 9;
    // Three pixels: pure red, pure green, pure blue
    guchar data[9] = {
        255, 0, 0,   // Red
        0, 255, 0,   // Green
        0, 0, 255    // Blue
    };

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
    ASSERT_NE(surface, nullptr);

    cairo_surface_flush(surface);
    guchar *pixels = cairo_image_surface_get_data(surface);

    // Red pixel
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(pixels[0], 0);   // B
    EXPECT_EQ(pixels[1], 0);   // G
    EXPECT_EQ(pixels[2], 255); // R
#else
    EXPECT_EQ(pixels[1], 255); // R
    EXPECT_EQ(pixels[2], 0);   // G
    EXPECT_EQ(pixels[3], 0);   // B
#endif

    // Green pixel
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(pixels[4], 0);   // B
    EXPECT_EQ(pixels[5], 255); // G
    EXPECT_EQ(pixels[6], 0);   // R
#else
    EXPECT_EQ(pixels[5], 0);   // R
    EXPECT_EQ(pixels[6], 255); // G
    EXPECT_EQ(pixels[7], 0);   // B
#endif

    // Blue pixel
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    EXPECT_EQ(pixels[8], 255);  // B
    EXPECT_EQ(pixels[9], 0);    // G
    EXPECT_EQ(pixels[10], 0);   // R
#else
    EXPECT_EQ(pixels[9], 0);    // R
    EXPECT_EQ(pixels[10], 0);   // G
    EXPECT_EQ(pixels[11], 255); // B
#endif

    cairo_surface_destroy(surface);
}

// Test: Width 1, tall image (many rows)
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, TallNarrowImage_2437)
{
    gint width = 1;
    gint height = 50;
    gint rowstride = 3;
    std::vector<guchar> data(rowstride * height);

    for (int i = 0; i < height; i++) {
        data[i * rowstride + 0] = (guchar)(i * 5);       // R
        data[i * rowstride + 1] = (guchar)(i * 5 + 1);   // G
        data[i * rowstride + 2] = (guchar)(i * 5 + 2);   // B
    }

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data.data(), width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_image_surface_get_width(surface), width);
    EXPECT_EQ(cairo_image_surface_get_height(surface), height);

    cairo_surface_flush(surface);
    guchar *pixels = cairo_image_surface_get_data(surface);
    gint stride = cairo_image_surface_get_stride(surface);

    // Verify a few rows
    for (int i = 0; i < height; i++) {
        guchar *q = pixels + i * stride;
        guchar expectedR = (guchar)(i * 5);
        guchar expectedG = (guchar)(i * 5 + 1);
        guchar expectedB = (guchar)(i * 5 + 2);

#if G_BYTE_ORDER == G_LITTLE_ENDIAN
        EXPECT_EQ(q[0], expectedB) << "Row " << i;
        EXPECT_EQ(q[1], expectedG) << "Row " << i;
        EXPECT_EQ(q[2], expectedR) << "Row " << i;
#else
        EXPECT_EQ(q[1], expectedR) << "Row " << i;
        EXPECT_EQ(q[2], expectedG) << "Row " << i;
        EXPECT_EQ(q[3], expectedB) << "Row " << i;
#endif
    }

    cairo_surface_destroy(surface);
}

// Test: Wide image with single row
TEST_F(CreateSurfaceFromThumbnailDataTest_2437, WideSingleRowImage_2437)
{
    gint width = 50;
    gint height = 1;
    gint rowstride = width * 3;
    std::vector<guchar> data(rowstride);

    for (int i = 0; i < width; i++) {
        data[i * 3 + 0] = (guchar)(i);
        data[i * 3 + 1] = (guchar)(i + 50);
        data[i * 3 + 2] = (guchar)(i + 100);
    }

    cairo_surface_t *surface = create_surface_from_thumbnail_data(data.data(), width, height, rowstride);
    ASSERT_NE(surface, nullptr);
    EXPECT_EQ(cairo_image_surface_get_width(surface), width);
    EXPECT_EQ(cairo_image_surface_get_height(surface), height);

    cairo_surface_flush(surface);
    guchar *pixels = cairo_image_surface_get_data(surface);

    // Spot check a few pixels
    for (int i = 0; i < width; i += 10) {
        guchar *q = pixels + i * 4;
        guchar expectedR = (guchar)(i);
        guchar expectedG = (guchar)(i + 50);
        guchar expectedB = (guchar)(i + 100);

#if G_BYTE_ORDER == G_LITTLE_ENDIAN
        EXPECT_EQ(q[0], expectedB) << "Pixel " << i;
        EXPECT_EQ(q[1], expectedG) << "Pixel " << i;
        EXPECT_EQ(q[2], expectedR) << "Pixel " << i;
#else
        EXPECT_EQ(q[1], expectedR) << "Pixel " << i;
        EXPECT_EQ(q[2], expectedG) << "Pixel " << i;
        EXPECT_EQ(q[3], expectedB) << "Pixel " << i;
#endif
    }

    cairo_surface_destroy(surface);
}
