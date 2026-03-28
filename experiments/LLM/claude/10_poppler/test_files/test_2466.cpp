#include <gtest/gtest.h>

// Include necessary headers
extern "C" {
#include <glib.h>
}

// Forward declarations and type definitions based on the interface
typedef struct _PopplerRectangle {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

// The extended rectangle type used internally
typedef struct _PopplerRectangleExtended {
    PopplerRectangle base;
    // Potentially additional fields; we don't know or care
} PopplerRectangleExtended;

// Declare the function under test
extern "C" {
    void poppler_rectangle_free(PopplerRectangle *rectangle);
    PopplerRectangle *poppler_rectangle_new(void);
    PopplerRectangle *poppler_rectangle_copy(PopplerRectangle *rectangle);
}

class PopplerRectangleTest_2466 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_rectangle_free does not crash when given a valid rectangle
TEST_F(PopplerRectangleTest_2466, FreeValidRectangle_2466)
{
    // Allocate a PopplerRectangleExtended via g_slice_new to match expected allocation
    PopplerRectangleExtended *ext = g_slice_new0(PopplerRectangleExtended);
    ASSERT_NE(ext, nullptr);

    PopplerRectangle *rect = reinterpret_cast<PopplerRectangle *>(ext);
    rect->x1 = 1.0;
    rect->y1 = 2.0;
    rect->x2 = 3.0;
    rect->y2 = 4.0;

    // This should not crash or leak
    EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(rect));
}

// Test that poppler_rectangle_free handles a rectangle with zero values
TEST_F(PopplerRectangleTest_2466, FreeRectangleWithZeroValues_2466)
{
    PopplerRectangleExtended *ext = g_slice_new0(PopplerRectangleExtended);
    ASSERT_NE(ext, nullptr);

    PopplerRectangle *rect = reinterpret_cast<PopplerRectangle *>(ext);
    rect->x1 = 0.0;
    rect->y1 = 0.0;
    rect->x2 = 0.0;
    rect->y2 = 0.0;

    EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(rect));
}

// Test that poppler_rectangle_free handles a rectangle with negative values
TEST_F(PopplerRectangleTest_2466, FreeRectangleWithNegativeValues_2466)
{
    PopplerRectangleExtended *ext = g_slice_new0(PopplerRectangleExtended);
    ASSERT_NE(ext, nullptr);

    PopplerRectangle *rect = reinterpret_cast<PopplerRectangle *>(ext);
    rect->x1 = -100.5;
    rect->y1 = -200.3;
    rect->x2 = -50.1;
    rect->y2 = -25.7;

    EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(rect));
}

// Test that poppler_rectangle_free handles a rectangle with large values
TEST_F(PopplerRectangleTest_2466, FreeRectangleWithLargeValues_2466)
{
    PopplerRectangleExtended *ext = g_slice_new0(PopplerRectangleExtended);
    ASSERT_NE(ext, nullptr);

    PopplerRectangle *rect = reinterpret_cast<PopplerRectangle *>(ext);
    rect->x1 = 1e15;
    rect->y1 = 1e15;
    rect->x2 = 1e15;
    rect->y2 = 1e15;

    EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(rect));
}

// Test freeing multiple rectangles sequentially
TEST_F(PopplerRectangleTest_2466, FreeMultipleRectanglesSequentially_2466)
{
    for (int i = 0; i < 100; ++i) {
        PopplerRectangleExtended *ext = g_slice_new0(PopplerRectangleExtended);
        ASSERT_NE(ext, nullptr);

        PopplerRectangle *rect = reinterpret_cast<PopplerRectangle *>(ext);
        rect->x1 = static_cast<double>(i);
        rect->y1 = static_cast<double>(i * 2);
        rect->x2 = static_cast<double>(i * 3);
        rect->y2 = static_cast<double>(i * 4);

        EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(rect));
    }
}

// Test that poppler_rectangle_free can handle a freshly allocated (uninitialized values) rectangle
TEST_F(PopplerRectangleTest_2466, FreeUninitializedRectangle_2466)
{
    PopplerRectangleExtended *ext = g_slice_new(PopplerRectangleExtended);
    ASSERT_NE(ext, nullptr);

    // Don't initialize - just free it
    PopplerRectangle *rect = reinterpret_cast<PopplerRectangle *>(ext);
    EXPECT_NO_FATAL_FAILURE(poppler_rectangle_free(rect));
}
