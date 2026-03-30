#include <gtest/gtest.h>

#include <cairo/cairo.h>



// Assuming cairo_surface_create_similar_clip is part of a class or can be tested directly.

// For this example, we will create a simple wrapper to facilitate testing.



class CairoOutputDev {

public:

    static cairo_surface_t* createSimilarClipSurface(cairo_t* cr, cairo_content_t content) {

        return cairo_surface_create_similar_clip(cr, content);

    }

};



TEST(CairoOutputDevTest_1924, CreateSimilarClipSurface_NormalOperation_1924) {

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);

    cairo_t *cr = cairo_create(surface);



    cairo_surface_t *similarSurface = CairoOutputDev::createSimilarClipSurface(cr, CAIRO_CONTENT_COLOR_ALPHA);



    EXPECT_NE(similarSurface, nullptr);

    EXPECT_EQ(cairo_surface_status(similarSurface), CAIRO_STATUS_SUCCESS);



    cairo_surface_destroy(similarSurface);

    cairo_destroy(cr);

    cairo_surface_destroy(surface);

}



TEST(CairoOutputDevTest_1924, CreateSimilarClipSurface_BoundaryConditions_1924) {

    // Test with zero size

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 0, 0);

    cairo_t *cr = cairo_create(surface);



    cairo_surface_t *similarSurface = CairoOutputDev::createSimilarClipSurface(cr, CAIRO_CONTENT_COLOR_ALPHA);



    EXPECT_NE(similarSurface, nullptr);

    EXPECT_EQ(cairo_surface_status(similarSurface), CAIRO_STATUS_SUCCESS);



    cairo_surface_destroy(similarSurface);

    cairo_destroy(cr);

    cairo_surface_destroy(surface);

}



TEST(CairoOutputDevTest_1924, CreateSimilarClipSurface_ExceptionalCases_1924) {

    // Test with null context

    cairo_surface_t *similarSurface = CairoOutputDev::createSimilarClipSurface(nullptr, CAIRO_CONTENT_COLOR_ALPHA);



    EXPECT_EQ(similarSurface, nullptr);

}



TEST(CairoOutputDevTest_1924, CreateSimilarClipSurface_ContentTypes_1924) {

    // Test with different content types

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);

    cairo_t *cr = cairo_create(surface);



    cairo_surface_t *similarSurfaceColorAlpha = CairoOutputDev::createSimilarClipSurface(cr, CAIRO_CONTENT_COLOR_ALPHA);

    EXPECT_NE(similarSurfaceColorAlpha, nullptr);

    EXPECT_EQ(cairo_surface_status(similarSurfaceColorAlpha), CAIRO_STATUS_SUCCESS);

    cairo_surface_destroy(similarSurfaceColorAlpha);



    cairo_surface_t *similarSurfaceColor = CairoOutputDev::createSimilarClipSurface(cr, CAIRO_CONTENT_COLOR);

    EXPECT_NE(similarSurfaceColor, nullptr);

    EXPECT_EQ(cairo_surface_status(similarSurfaceColor), CAIRO_STATUS_SUCCESS);

    cairo_surface_destroy(similarSurfaceColor);



    cairo_surface_t *similarSurfaceAlpha = CairoOutputDev::createSimilarClipSurface(cr, CAIRO_CONTENT_ALPHA);

    EXPECT_NE(similarSurfaceAlpha, nullptr);

    EXPECT_EQ(cairo_surface_status(similarSurfaceAlpha), CAIRO_STATUS_SUCCESS);

    cairo_surface_destroy(similarSurfaceAlpha);



    cairo_destroy(cr);

    cairo_surface_destroy(surface);

}
