#include <glib.h>
#include <gtest/gtest.h>

// Include the header that defines PopplerPoint and the function under test
extern "C" {
#include "poppler-page.h"

// Declare the function under test
PopplerPoint *poppler_point_new(void);
PopplerPoint *poppler_point_copy(PopplerPoint *point);
void poppler_point_free(PopplerPoint *point);
}

class PopplerPointCopyTest_2470 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerPointCopyTest_2470, CopyReturnsNonNullForValidPoint_2470)
{
    PopplerPoint point;
    point.x = 1.0;
    point.y = 2.0;

    PopplerPoint *copied = poppler_point_copy(&point);
    ASSERT_NE(copied, nullptr);

    g_slice_free(PopplerPoint, copied);
}

TEST_F(PopplerPointCopyTest_2470, CopyPreservesXValue_2470)
{
    PopplerPoint point;
    point.x = 42.5;
    point.y = 99.9;

    PopplerPoint *copied = poppler_point_copy(&point);
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->x, 42.5);

    g_slice_free(PopplerPoint, copied);
}

TEST_F(PopplerPointCopyTest_2470, CopyPreservesYValue_2470)
{
    PopplerPoint point;
    point.x = 42.5;
    point.y = 99.9;

    PopplerPoint *copied = poppler_point_copy(&point);
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->y, 99.9);

    g_slice_free(PopplerPoint, copied);
}

TEST_F(PopplerPointCopyTest_2470, CopyReturnsDifferentPointer_2470)
{
    PopplerPoint point;
    point.x = 10.0;
    point.y = 20.0;

    PopplerPoint *copied = poppler_point_copy(&point);
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied, &point);

    g_slice_free(PopplerPoint, copied);
}

TEST_F(PopplerPointCopyTest_2470, CopyNullReturnsNull_2470)
{
    // poppler_point_copy with NULL should return NULL due to g_return_val_if_fail
    // Note: g_return_val_if_fail will emit a critical warning; we suppress it for the test
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*point*failed*");

    PopplerPoint *copied = poppler_point_copy(nullptr);
    EXPECT_EQ(copied, nullptr);

    g_test_assert_expected_messages();
}

TEST_F(PopplerPointCopyTest_2470, CopyZeroValues_2470)
{
    PopplerPoint point;
    point.x = 0.0;
    point.y = 0.0;

    PopplerPoint *copied = poppler_point_copy(&point);
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->x, 0.0);
    EXPECT_DOUBLE_EQ(copied->y, 0.0);

    g_slice_free(PopplerPoint, copied);
}

TEST_F(PopplerPointCopyTest_2470, CopyNegativeValues_2470)
{
    PopplerPoint point;
    point.x = -123.456;
    point.y = -789.012;

    PopplerPoint *copied = poppler_point_copy(&point);
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->x, -123.456);
    EXPECT_DOUBLE_EQ(copied->y, -789.012);

    g_slice_free(PopplerPoint, copied);
}

TEST_F(PopplerPointCopyTest_2470, CopyLargeValues_2470)
{
    PopplerPoint point;
    point.x = 1e15;
    point.y = -1e15;

    PopplerPoint *copied = poppler_point_copy(&point);
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->x, 1e15);
    EXPECT_DOUBLE_EQ(copied->y, -1e15);

    g_slice_free(PopplerPoint, copied);
}

TEST_F(PopplerPointCopyTest_2470, CopyIsIndependentOfOriginal_2470)
{
    PopplerPoint point;
    point.x = 5.0;
    point.y = 10.0;

    PopplerPoint *copied = poppler_point_copy(&point);
    ASSERT_NE(copied, nullptr);

    // Modify original
    point.x = 100.0;
    point.y = 200.0;

    // Copied values should remain unchanged
    EXPECT_DOUBLE_EQ(copied->x, 5.0);
    EXPECT_DOUBLE_EQ(copied->y, 10.0);

    g_slice_free(PopplerPoint, copied);
}
