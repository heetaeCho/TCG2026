// create_surface_from_thumbnail_data_test_2437.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include <glib.h>
#include <cairo.h>

// Include the implementation file so we can call the internal `static` function
// from the same translation unit (black-box tests via the provided signature).
#include "./TestProjects/poppler/glib/poppler-page.cc"

namespace {

class CreateSurfaceFromThumbnailDataTest_2437 : public ::testing::Test {
protected:
  static void ExpectSurfacePixelEqualsRGB(cairo_surface_t* surface,
                                         int x,
                                         int y,
                                         uint8_t r,
                                         uint8_t g,
                                         uint8_t b) {
    ASSERT_NE(surface, nullptr);

    cairo_surface_flush(surface);
    ASSERT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    const unsigned char* bytes =
        cairo_image_surface_get_data(surface);
    const int stride =
        cairo_image_surface_get_stride(surface);

    ASSERT_NE(bytes, nullptr);
    ASSERT_GT(stride, 0);

    const unsigned char* px = bytes + y * stride + x * 4;

#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    // For CAIRO_FORMAT_RGB24 on little-endian, memory is typically B, G, R, X.
    EXPECT_EQ(px[0], b);
    EXPECT_EQ(px[1], g);
    EXPECT_EQ(px[2], r);
#else
    // For CAIRO_FORMAT_RGB24 on big-endian, bytes are typically X, R, G, B.
    EXPECT_EQ(px[1], r);
    EXPECT_EQ(px[2], g);
    EXPECT_EQ(px[3], b);
#endif
  }
};

TEST_F(CreateSurfaceFromThumbnailDataTest_2437, CreatesSurfaceAndConvertsSinglePixel_2437) {
  // 1x1 thumbnail: RGB = (0x11, 0x22, 0x33)
  guchar data[3] = {0x11, 0x22, 0x33};
  const gint width = 1;
  const gint height = 1;
  const gint rowstride = 3;

  cairo_surface_t* surface = create_surface_from_thumbnail_data(data, width, height, rowstride);
  ASSERT_NE(surface, nullptr);

  EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);
  EXPECT_EQ(cairo_image_surface_get_format(surface), CAIRO_FORMAT_RGB24);
  EXPECT_EQ(cairo_image_surface_get_width(surface), width);
  EXPECT_EQ(cairo_image_surface_get_height(surface), height);

  ExpectSurfacePixelEqualsRGB(surface, 0, 0, /*r=*/0x11, /*g=*/0x22, /*b=*/0x33);

  cairo_surface_destroy(surface);
}

TEST_F(CreateSurfaceFromThumbnailDataTest_2437, HonorsRowstrideWithPaddingAcrossRows_2437) {
  // width=2 => 6 bytes per row; use rowstride=8 with 2 bytes padding.
  // Row 0 pixels: (R,G,B) = (1,2,3) and (4,5,6)
  // Row 1 pixels: (R,G,B) = (7,8,9) and (10,11,12)
  const gint width = 2;
  const gint height = 2;
  const gint rowstride = 8;

  std::vector<guchar> data(static_cast<size_t>(rowstride * height), 0xEE); // padding filled with 0xEE
  // Row 0
  data[0] = 1;  data[1] = 2;  data[2] = 3;
  data[3] = 4;  data[4] = 5;  data[5] = 6;
  // Row 0 padding: data[6], data[7] remain 0xEE
  // Row 1 starts at offset rowstride
  const int row1 = rowstride;
  data[row1 + 0] = 7;   data[row1 + 1] = 8;   data[row1 + 2] = 9;
  data[row1 + 3] = 10;  data[row1 + 4] = 11;  data[row1 + 5] = 12;
  // Row 1 padding: data[row1+6], data[row1+7] remain 0xEE

  cairo_surface_t* surface =
      create_surface_from_thumbnail_data(data.data(), width, height, rowstride);
  ASSERT_NE(surface, nullptr);

  EXPECT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);
  EXPECT_EQ(cairo_image_surface_get_format(surface), CAIRO_FORMAT_RGB24);
  EXPECT_EQ(cairo_image_surface_get_width(surface), width);
  EXPECT_EQ(cairo_image_surface_get_height(surface), height);

  // Verify all four pixels landed in the right spots.
  ExpectSurfacePixelEqualsRGB(surface, 0, 0, 1, 2, 3);
  ExpectSurfacePixelEqualsRGB(surface, 1, 0, 4, 5, 6);
  ExpectSurfacePixelEqualsRGB(surface, 0, 1, 7, 8, 9);
  ExpectSurfacePixelEqualsRGB(surface, 1, 1, 10, 11, 12);

  cairo_surface_destroy(surface);
}

TEST_F(CreateSurfaceFromThumbnailDataTest_2437, ReturnsNullptrForZeroWidth_2437) {
  // If the surface can't be created (invalid size), function should return nullptr
  // and must not dereference `data`.
  cairo_surface_t* surface =
      create_surface_from_thumbnail_data(/*data=*/nullptr, /*width=*/0, /*height=*/1, /*rowstride=*/0);
  EXPECT_EQ(surface, nullptr);
}

TEST_F(CreateSurfaceFromThumbnailDataTest_2437, ReturnsNullptrForZeroHeight_2437) {
  cairo_surface_t* surface =
      create_surface_from_thumbnail_data(/*data=*/nullptr, /*width=*/1, /*height=*/0, /*rowstride=*/0);
  EXPECT_EQ(surface, nullptr);
}

TEST_F(CreateSurfaceFromThumbnailDataTest_2437, ReturnsNullptrForNegativeDimensions_2437) {
  // Negative sizes are invalid for cairo_image_surface_create and should yield a failed surface status.
  cairo_surface_t* surface1 =
      create_surface_from_thumbnail_data(/*data=*/nullptr, /*width=*/-1, /*height=*/10, /*rowstride=*/0);
  EXPECT_EQ(surface1, nullptr);

  cairo_surface_t* surface2 =
      create_surface_from_thumbnail_data(/*data=*/nullptr, /*width=*/10, /*height=*/-1, /*rowstride=*/0);
  EXPECT_EQ(surface2, nullptr);
}

}  // namespace