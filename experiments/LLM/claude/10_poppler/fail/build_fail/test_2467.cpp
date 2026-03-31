#include <gtest/gtest.h>
#include <glib.h>

// Include necessary headers
// We need the structures and the function declaration

// Forward declare/define the structures as they appear in the codebase
// Based on the known dependencies

// From poppler-page.h - PopplerRectangle
typedef struct _PopplerRectangle {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

// From poppler-private.h - PopplerRectangleExtended
// This struct must start with the same layout as PopplerRectangle
// so that reinterpret_cast works correctly
struct PopplerRectangleExtended {
    double x1;
    double y1;
    double x2;
    double y2;
    bool match_continued;
    bool ignored_hyphen;
};

// Declare the function under test
extern "C" {
    gboolean poppler_rectangle_find_get_match_continued(const PopplerRectangle *rectangle);
}

class PopplerRectangleFindGetMatchContinuedTest_2467 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that when match_continued is true, the function returns TRUE
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ReturnsTrueWhenMatchContinuedIsTrue_2467) {
    PopplerRectangleExtended ext_rect = {};
    ext_rect.x1 = 0.0;
    ext_rect.y1 = 0.0;
    ext_rect.x2 = 100.0;
    ext_rect.y2 = 100.0;
    ext_rect.match_continued = true;
    ext_rect.ignored_hyphen = false;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_match_continued(rect);
    EXPECT_TRUE(result);
}

// Test that when match_continued is false, the function returns FALSE
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ReturnsFalseWhenMatchContinuedIsFalse_2467) {
    PopplerRectangleExtended ext_rect = {};
    ext_rect.x1 = 0.0;
    ext_rect.y1 = 0.0;
    ext_rect.x2 = 50.0;
    ext_rect.y2 = 50.0;
    ext_rect.match_continued = false;
    ext_rect.ignored_hyphen = false;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_match_continued(rect);
    EXPECT_FALSE(result);
}

// Test that passing nullptr returns false (boundary/error case)
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ReturnsFalseWhenNullPointerPassed_2467) {
    gboolean result = poppler_rectangle_find_get_match_continued(nullptr);
    EXPECT_FALSE(result);
}

// Test that match_continued true with ignored_hyphen true still returns the correct match_continued value
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ReturnsTrueRegardlessOfIgnoredHyphen_2467) {
    PopplerRectangleExtended ext_rect = {};
    ext_rect.x1 = 10.0;
    ext_rect.y1 = 20.0;
    ext_rect.x2 = 30.0;
    ext_rect.y2 = 40.0;
    ext_rect.match_continued = true;
    ext_rect.ignored_hyphen = true;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_match_continued(rect);
    EXPECT_TRUE(result);
}

// Test that match_continued false with ignored_hyphen true still returns false
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ReturnsFalseWhenMatchContinuedFalseAndIgnoredHyphenTrue_2467) {
    PopplerRectangleExtended ext_rect = {};
    ext_rect.x1 = 5.0;
    ext_rect.y1 = 15.0;
    ext_rect.x2 = 25.0;
    ext_rect.y2 = 35.0;
    ext_rect.match_continued = false;
    ext_rect.ignored_hyphen = true;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_match_continued(rect);
    EXPECT_FALSE(result);
}

// Test with zero-initialized extended rectangle (all defaults)
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ReturnsFalseForZeroInitializedStruct_2467) {
    PopplerRectangleExtended ext_rect = {};
    // All fields zero/false by default

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_match_continued(rect);
    EXPECT_FALSE(result);
}

// Test multiple calls on the same rectangle return consistent results
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ConsistentResultsOnMultipleCalls_2467) {
    PopplerRectangleExtended ext_rect = {};
    ext_rect.match_continued = true;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    
    gboolean result1 = poppler_rectangle_find_get_match_continued(rect);
    gboolean result2 = poppler_rectangle_find_get_match_continued(rect);
    gboolean result3 = poppler_rectangle_find_get_match_continued(rect);
    
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
    EXPECT_TRUE(result3);
}
