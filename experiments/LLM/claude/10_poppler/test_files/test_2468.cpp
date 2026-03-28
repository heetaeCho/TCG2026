#include <gtest/gtest.h>
#include <glib.h>

// Include necessary headers
// We need the structures and the function declaration

// Forward declarations based on the provided interface
typedef struct _PopplerRectangle {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

struct PopplerRectangleExtended {
    PopplerRectangle base;
    gboolean match_continued;
    gboolean ignored_hyphen;
};

// Declaration of the function under test
extern "C" {
    gboolean poppler_rectangle_find_get_ignored_hyphen(const PopplerRectangle *rectangle);
}

class PopplerRectangleFindGetIgnoredHyphenTest_2468 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, ReturnsTrue_WhenIgnoredHyphenIsTrue_2468)
{
    PopplerRectangleExtended ext_rect = {};
    ext_rect.ignored_hyphen = TRUE;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_ignored_hyphen(rect);

    EXPECT_TRUE(result);
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, ReturnsFalse_WhenIgnoredHyphenIsFalse_2468)
{
    PopplerRectangleExtended ext_rect = {};
    ext_rect.ignored_hyphen = FALSE;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_ignored_hyphen(rect);

    EXPECT_FALSE(result);
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, ReturnsFalse_WhenRectangleIsNull_2468)
{
    // When nullptr is passed, g_return_val_if_fail should return false
    // Note: This will trigger a GLib critical warning, but should return FALSE
    gboolean result = poppler_rectangle_find_get_ignored_hyphen(nullptr);

    EXPECT_FALSE(result);
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, ReturnsFalse_WhenDefaultInitialized_2468)
{
    PopplerRectangleExtended ext_rect = {};
    // Default initialization should set ignored_hyphen to FALSE (0)

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_ignored_hyphen(rect);

    EXPECT_FALSE(result);
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, IgnoredHyphenIndependentOfMatchContinued_WhenMatchContinuedTrue_2468)
{
    PopplerRectangleExtended ext_rect = {};
    ext_rect.match_continued = TRUE;
    ext_rect.ignored_hyphen = FALSE;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_ignored_hyphen(rect);

    EXPECT_FALSE(result);
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, IgnoredHyphenIndependentOfMatchContinued_BothTrue_2468)
{
    PopplerRectangleExtended ext_rect = {};
    ext_rect.match_continued = TRUE;
    ext_rect.ignored_hyphen = TRUE;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_ignored_hyphen(rect);

    EXPECT_TRUE(result);
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, IgnoredHyphenIndependentOfRectangleCoordinates_2468)
{
    PopplerRectangleExtended ext_rect = {};
    ext_rect.base.x1 = 100.0;
    ext_rect.base.y1 = 200.0;
    ext_rect.base.x2 = 300.0;
    ext_rect.base.y2 = 400.0;
    ext_rect.ignored_hyphen = TRUE;

    const PopplerRectangle *rect = reinterpret_cast<const PopplerRectangle *>(&ext_rect);
    gboolean result = poppler_rectangle_find_get_ignored_hyphen(rect);

    EXPECT_TRUE(result);
}
