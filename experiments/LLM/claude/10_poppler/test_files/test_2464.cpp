#include <gtest/gtest.h>

// Include necessary headers for poppler types and functions
extern "C" {
#include <glib-object.h>

// Forward declarations based on the interface
typedef struct _PopplerRectangle PopplerRectangle;

struct _PopplerRectangle
{
    double x1;
    double y1;
    double x2;
    double y2;
};

// Function under test
PopplerRectangle *poppler_rectangle_new(void);

// We need poppler_rectangle_free or g_free to clean up
void poppler_rectangle_free(PopplerRectangle *rectangle);
}

class PopplerRectangleTest_2464 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_rectangle_new returns a non-null pointer
TEST_F(PopplerRectangleTest_2464, ReturnsNonNull_2464)
{
    PopplerRectangle *rect = poppler_rectangle_new();
    ASSERT_NE(rect, nullptr);
    poppler_rectangle_free(rect);
}

// Test that the returned rectangle can be used (fields are accessible)
TEST_F(PopplerRectangleTest_2464, FieldsAreAccessible_2464)
{
    PopplerRectangle *rect = poppler_rectangle_new();
    ASSERT_NE(rect, nullptr);

    // We should be able to set and read fields on the allocated rectangle
    rect->x1 = 1.0;
    rect->y1 = 2.0;
    rect->x2 = 3.0;
    rect->y2 = 4.0;

    EXPECT_DOUBLE_EQ(rect->x1, 1.0);
    EXPECT_DOUBLE_EQ(rect->y1, 2.0);
    EXPECT_DOUBLE_EQ(rect->x2, 3.0);
    EXPECT_DOUBLE_EQ(rect->y2, 4.0);

    poppler_rectangle_free(rect);
}

// Test that multiple allocations return distinct pointers
TEST_F(PopplerRectangleTest_2464, MultipleAllocationsReturnDistinctPointers_2464)
{
    PopplerRectangle *rect1 = poppler_rectangle_new();
    PopplerRectangle *rect2 = poppler_rectangle_new();

    ASSERT_NE(rect1, nullptr);
    ASSERT_NE(rect2, nullptr);
    EXPECT_NE(rect1, rect2);

    poppler_rectangle_free(rect1);
    poppler_rectangle_free(rect2);
}

// Test that allocated rectangles are independent (modifying one doesn't affect another)
TEST_F(PopplerRectangleTest_2464, AllocationsAreIndependent_2464)
{
    PopplerRectangle *rect1 = poppler_rectangle_new();
    PopplerRectangle *rect2 = poppler_rectangle_new();

    ASSERT_NE(rect1, nullptr);
    ASSERT_NE(rect2, nullptr);

    rect1->x1 = 10.0;
    rect1->y1 = 20.0;
    rect1->x2 = 30.0;
    rect1->y2 = 40.0;

    rect2->x1 = 100.0;
    rect2->y1 = 200.0;
    rect2->x2 = 300.0;
    rect2->y2 = 400.0;

    // Verify they remain independent
    EXPECT_DOUBLE_EQ(rect1->x1, 10.0);
    EXPECT_DOUBLE_EQ(rect1->y1, 20.0);
    EXPECT_DOUBLE_EQ(rect1->x2, 30.0);
    EXPECT_DOUBLE_EQ(rect1->y2, 40.0);

    EXPECT_DOUBLE_EQ(rect2->x1, 100.0);
    EXPECT_DOUBLE_EQ(rect2->y1, 200.0);
    EXPECT_DOUBLE_EQ(rect2->x2, 300.0);
    EXPECT_DOUBLE_EQ(rect2->y2, 400.0);

    poppler_rectangle_free(rect1);
    poppler_rectangle_free(rect2);
}

// Test boundary values for rectangle fields
TEST_F(PopplerRectangleTest_2464, BoundaryValues_2464)
{
    PopplerRectangle *rect = poppler_rectangle_new();
    ASSERT_NE(rect, nullptr);

    // Test with zero values
    rect->x1 = 0.0;
    rect->y1 = 0.0;
    rect->x2 = 0.0;
    rect->y2 = 0.0;
    EXPECT_DOUBLE_EQ(rect->x1, 0.0);
    EXPECT_DOUBLE_EQ(rect->y1, 0.0);
    EXPECT_DOUBLE_EQ(rect->x2, 0.0);
    EXPECT_DOUBLE_EQ(rect->y2, 0.0);

    // Test with negative values
    rect->x1 = -1.5;
    rect->y1 = -2.5;
    rect->x2 = -3.5;
    rect->y2 = -4.5;
    EXPECT_DOUBLE_EQ(rect->x1, -1.5);
    EXPECT_DOUBLE_EQ(rect->y1, -2.5);
    EXPECT_DOUBLE_EQ(rect->x2, -3.5);
    EXPECT_DOUBLE_EQ(rect->y2, -4.5);

    // Test with very large values
    rect->x1 = 1e308;
    rect->y1 = 1e308;
    rect->x2 = -1e308;
    rect->y2 = -1e308;
    EXPECT_DOUBLE_EQ(rect->x1, 1e308);
    EXPECT_DOUBLE_EQ(rect->y1, 1e308);
    EXPECT_DOUBLE_EQ(rect->x2, -1e308);
    EXPECT_DOUBLE_EQ(rect->y2, -1e308);

    poppler_rectangle_free(rect);
}

// Test repeated allocation and deallocation (stress/leak check)
TEST_F(PopplerRectangleTest_2464, RepeatedAllocationDeallocation_2464)
{
    for (int i = 0; i < 100; i++) {
        PopplerRectangle *rect = poppler_rectangle_new();
        ASSERT_NE(rect, nullptr);
        rect->x1 = static_cast<double>(i);
        rect->y1 = static_cast<double>(i + 1);
        rect->x2 = static_cast<double>(i + 2);
        rect->y2 = static_cast<double>(i + 3);
        EXPECT_DOUBLE_EQ(rect->x1, static_cast<double>(i));
        poppler_rectangle_free(rect);
    }
}
