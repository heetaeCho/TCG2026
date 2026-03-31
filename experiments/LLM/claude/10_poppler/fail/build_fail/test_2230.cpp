#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and minimal type definitions needed for testing
// Based on the provided interface, we need PopplerFontsIter and related functions

extern "C" {
// These are the public API functions we're testing
typedef struct _PopplerFontsIter PopplerFontsIter;

void poppler_fonts_iter_free(PopplerFontsIter *iter);
}

// Test fixture
class PopplerFontsIterTest_2230 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr to poppler_fonts_iter_free does not crash
TEST_F(PopplerFontsIterTest_2230, FreeNullIterDoesNotCrash_2230)
{
    // Passing nullptr should be handled gracefully (early return)
    EXPECT_NO_FATAL_FAILURE(poppler_fonts_iter_free(nullptr));
}

// Test that passing nullptr multiple times is safe
TEST_F(PopplerFontsIterTest_2230, FreeNullIterMultipleTimesDoesNotCrash_2230)
{
    EXPECT_NO_FATAL_FAILURE(poppler_fonts_iter_free(nullptr));
    EXPECT_NO_FATAL_FAILURE(poppler_fonts_iter_free(nullptr));
    EXPECT_NO_FATAL_FAILURE(poppler_fonts_iter_free(nullptr));
}
