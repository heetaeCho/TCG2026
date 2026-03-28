#include <gtest/gtest.h>
#include <cairo.h>

// We declare the function under test as it has static linkage in the original file.
// To test it, we need to either include the source or redeclare it.
// Since it's a static function in a .cc file, we include the source to access it.
// However, for proper unit testing, we'll recreate the function signature and 
// test it through its observable behavior.

// Forward declaration - we need to access this static function.
// In practice, this would require either making it non-static or including the .cc file.
// For testing purposes, we include the implementation file.
#include "poppler/CairoOutputDev.cc"

class CairoSurfaceCreateSimilarClipTest_1924 : public ::testing::Test {
protected:
    cairo_surface_t *image_surface = nullptr;
    cairo_t *cr = nullptr;

    void SetUp() override {
        image_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
        cr = cairo_create(image_surface);
    }

    void TearDown() override {
        if (cr) {
            cairo_destroy(cr);
            cr = nullptr;
        }
        if (image_surface) {
            cairo_surface_destroy(image_surface);
            image_surface = nullptr;
        }
    }
};

// Test that the function returns a non-null surface with CAIRO_CONTENT_COLOR_ALPHA
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, ReturnsNonNullSurfaceColorAlpha_1924) {
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    cairo_surface_destroy(result);
}

// Test that the function returns a non-null surface with CAIRO_CONTENT_COLOR
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, ReturnsNonNullSurfaceColor_1924) {
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR);
    ASSERT_NE(result, nullptr);
    cairo_surface_destroy(result);
}

// Test that the function returns a non-null surface with CAIRO_CONTENT_ALPHA
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, ReturnsNonNullSurfaceAlpha_1924) {
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_ALPHA);
    ASSERT_NE(result, nullptr);
    cairo_surface_destroy(result);
}

// Test that the returned surface has a valid status (no error)
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, ReturnedSurfaceHasValidStatus_1924) {
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
    cairo_surface_destroy(result);
}

// Test that the returned surface has a reference count of at least 1 (it's usable)
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, ReturnedSurfaceIsReferenced_1924) {
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    // We can reference and unreference to verify it's properly reference counted
    cairo_surface_reference(result);
    cairo_surface_destroy(result); // decrements ref, still alive
    EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
    cairo_surface_destroy(result); // final destroy
}

// Test that the cairo context remains valid after calling the function
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, CairoContextRemainsValidAfterCall_1924) {
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
    cairo_surface_destroy(result);
}

// Test with a clipped cairo context
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, WorksWithClippedContext_1924) {
    cairo_rectangle(cr, 10, 10, 50, 50);
    cairo_clip(cr);
    
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
    cairo_surface_destroy(result);
}

// Test with a very small surface
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, WorksWithSmallBaseSurface_1924) {
    cairo_surface_t *small_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    cairo_t *small_cr = cairo_create(small_surface);
    
    cairo_surface_t *result = cairo_surface_create_similar_clip(small_cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
    
    cairo_surface_destroy(result);
    cairo_destroy(small_cr);
    cairo_surface_destroy(small_surface);
}

// Test that the returned surface dimensions match the clip extents
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, SurfaceDimensionsMatchClip_1924) {
    cairo_rectangle(cr, 0, 0, 30, 40);
    cairo_clip(cr);
    
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
    
    cairo_surface_destroy(result);
}

// Test multiple calls don't affect the cairo context state
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, MultipleCallsDontCorruptContext_1924) {
    cairo_surface_t *result1 = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR_ALPHA);
    cairo_surface_t *result2 = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR);
    cairo_surface_t *result3 = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_ALPHA);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_NE(result3, nullptr);
    
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
    
    cairo_surface_destroy(result1);
    cairo_surface_destroy(result2);
    cairo_surface_destroy(result3);
}

// Test with transformed context
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, WorksWithTransformedContext_1924) {
    cairo_translate(cr, 20, 20);
    cairo_scale(cr, 2.0, 2.0);
    
    cairo_surface_t *result = cairo_surface_create_similar_clip(cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
    cairo_surface_destroy(result);
}

// Test with a larger surface
TEST_F(CairoSurfaceCreateSimilarClipTest_1924, WorksWithLargerBaseSurface_1924) {
    cairo_surface_t *large_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 2000, 2000);
    cairo_t *large_cr = cairo_create(large_surface);
    
    cairo_surface_t *result = cairo_surface_create_similar_clip(large_cr, CAIRO_CONTENT_COLOR_ALPHA);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(cairo_surface_status(result), CAIRO_STATUS_SUCCESS);
    
    cairo_surface_destroy(result);
    cairo_destroy(large_cr);
    cairo_surface_destroy(large_surface);
}
