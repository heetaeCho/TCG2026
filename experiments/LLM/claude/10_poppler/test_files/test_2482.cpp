#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definition based on the provided interface
extern "C" {

typedef struct _PopplerColor {
    int red;
    int green;
    int blue;
} PopplerColor;

// Function under test
void poppler_color_free(PopplerColor *color);

// We also need poppler_color_copy or similar allocation if available,
// but based on the interface we only have poppler_color_free which calls g_free.
// We'll allocate using g_new to match the expected g_free behavior.

}

class PopplerColorFreeTest_2482 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that freeing a properly allocated PopplerColor does not crash
TEST_F(PopplerColorFreeTest_2482, FreeValidColor_2482) {
    PopplerColor *color = g_new(PopplerColor, 1);
    color->red = 255;
    color->green = 128;
    color->blue = 0;

    // Should not crash or cause issues
    EXPECT_NO_FATAL_FAILURE(poppler_color_free(color));
}

// Test that freeing a NULL pointer does not crash (g_free handles NULL gracefully)
TEST_F(PopplerColorFreeTest_2482, FreeNullColor_2482) {
    EXPECT_NO_FATAL_FAILURE(poppler_color_free(nullptr));
}

// Test that freeing a color with zero values works correctly
TEST_F(PopplerColorFreeTest_2482, FreeColorWithZeroValues_2482) {
    PopplerColor *color = g_new0(PopplerColor, 1);
    // All fields should be zero after g_new0
    EXPECT_EQ(color->red, 0);
    EXPECT_EQ(color->green, 0);
    EXPECT_EQ(color->blue, 0);

    EXPECT_NO_FATAL_FAILURE(poppler_color_free(color));
}

// Test that freeing a color with maximum int values works
TEST_F(PopplerColorFreeTest_2482, FreeColorWithMaxValues_2482) {
    PopplerColor *color = g_new(PopplerColor, 1);
    color->red = G_MAXINT;
    color->green = G_MAXINT;
    color->blue = G_MAXINT;

    EXPECT_NO_FATAL_FAILURE(poppler_color_free(color));
}

// Test that freeing a color with negative values works (boundary)
TEST_F(PopplerColorFreeTest_2482, FreeColorWithNegativeValues_2482) {
    PopplerColor *color = g_new(PopplerColor, 1);
    color->red = -1;
    color->green = -255;
    color->blue = G_MININT;

    EXPECT_NO_FATAL_FAILURE(poppler_color_free(color));
}

// Test freeing multiple colors sequentially
TEST_F(PopplerColorFreeTest_2482, FreeMultipleColors_2482) {
    for (int i = 0; i < 100; i++) {
        PopplerColor *color = g_new(PopplerColor, 1);
        color->red = i;
        color->green = i * 2;
        color->blue = i * 3;
        EXPECT_NO_FATAL_FAILURE(poppler_color_free(color));
    }
}

// Test that g_new allocated color is properly freed (no leak expected, validated by not crashing)
TEST_F(PopplerColorFreeTest_2482, FreeColorAllocatedWithGNew_2482) {
    PopplerColor *color = (PopplerColor *)g_malloc(sizeof(PopplerColor));
    color->red = 100;
    color->green = 200;
    color->blue = 50;

    EXPECT_NO_FATAL_FAILURE(poppler_color_free(color));
}
