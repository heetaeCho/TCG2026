#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler glib headers
extern "C" {
#include "poppler.h"
}

class PopplerRectangleCopyTest_2465 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that copying a valid rectangle returns a non-null result
TEST_F(PopplerRectangleCopyTest_2465, CopyValidRectangle_ReturnsNonNull_2465)
{
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 30.0;
    rect.y2 = 40.0;

    PopplerRectangle *copy = poppler_rectangle_copy(&rect);
    ASSERT_NE(copy, nullptr);
    poppler_rectangle_free(copy);
}

// Test that the copied rectangle has the same values as the original
TEST_F(PopplerRectangleCopyTest_2465, CopyPreservesValues_2465)
{
    PopplerRectangle rect;
    rect.x1 = 1.5;
    rect.y1 = 2.5;
    rect.x2 = 3.5;
    rect.y2 = 4.5;

    PopplerRectangle *copy = poppler_rectangle_copy(&rect);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->x1, rect.x1);
    EXPECT_DOUBLE_EQ(copy->y1, rect.y1);
    EXPECT_DOUBLE_EQ(copy->x2, rect.x2);
    EXPECT_DOUBLE_EQ(copy->y2, rect.y2);
    poppler_rectangle_free(copy);
}

// Test that passing nullptr returns NULL
TEST_F(PopplerRectangleCopyTest_2465, CopyNullReturnsNull_2465)
{
    PopplerRectangle *copy = poppler_rectangle_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test that the copy is independent of the original (modifying copy doesn't affect original)
TEST_F(PopplerRectangleCopyTest_2465, CopyIsIndependent_2465)
{
    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 200.0;
    rect.x2 = 300.0;
    rect.y2 = 400.0;

    PopplerRectangle *copy = poppler_rectangle_copy(&rect);
    ASSERT_NE(copy, nullptr);

    // Modify the copy
    copy->x1 = 0.0;
    copy->y1 = 0.0;
    copy->x2 = 0.0;
    copy->y2 = 0.0;

    // Original should be unchanged
    EXPECT_DOUBLE_EQ(rect.x1, 100.0);
    EXPECT_DOUBLE_EQ(rect.y1, 200.0);
    EXPECT_DOUBLE_EQ(rect.x2, 300.0);
    EXPECT_DOUBLE_EQ(rect.y2, 400.0);

    poppler_rectangle_free(copy);
}

// Test copying a rectangle with zero values
TEST_F(PopplerRectangleCopyTest_2465, CopyZeroValueRectangle_2465)
{
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 0.0;
    rect.y2 = 0.0;

    PopplerRectangle *copy = poppler_rectangle_copy(&rect);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->x1, 0.0);
    EXPECT_DOUBLE_EQ(copy->y1, 0.0);
    EXPECT_DOUBLE_EQ(copy->x2, 0.0);
    EXPECT_DOUBLE_EQ(copy->y2, 0.0);
    poppler_rectangle_free(copy);
}

// Test copying a rectangle with negative values
TEST_F(PopplerRectangleCopyTest_2465, CopyNegativeValueRectangle_2465)
{
    PopplerRectangle rect;
    rect.x1 = -10.5;
    rect.y1 = -20.5;
    rect.x2 = -5.5;
    rect.y2 = -1.5;

    PopplerRectangle *copy = poppler_rectangle_copy(&rect);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->x1, -10.5);
    EXPECT_DOUBLE_EQ(copy->y1, -20.5);
    EXPECT_DOUBLE_EQ(copy->x2, -5.5);
    EXPECT_DOUBLE_EQ(copy->y2, -1.5);
    poppler_rectangle_free(copy);
}

// Test copying a rectangle with very large values
TEST_F(PopplerRectangleCopyTest_2465, CopyLargeValueRectangle_2465)
{
    PopplerRectangle rect;
    rect.x1 = 1e15;
    rect.y1 = 1e15;
    rect.x2 = 1e15;
    rect.y2 = 1e15;

    PopplerRectangle *copy = poppler_rectangle_copy(&rect);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->x1, 1e15);
    EXPECT_DOUBLE_EQ(copy->y1, 1e15);
    EXPECT_DOUBLE_EQ(copy->x2, 1e15);
    EXPECT_DOUBLE_EQ(copy->y2, 1e15);
    poppler_rectangle_free(copy);
}

// Test that the returned pointer is different from the original
TEST_F(PopplerRectangleCopyTest_2465, CopyReturnsDifferentPointer_2465)
{
    PopplerRectangle rect;
    rect.x1 = 1.0;
    rect.y1 = 2.0;
    rect.x2 = 3.0;
    rect.y2 = 4.0;

    PopplerRectangle *copy = poppler_rectangle_copy(&rect);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, &rect);
    poppler_rectangle_free(copy);
}

// Test multiple copies are independent
TEST_F(PopplerRectangleCopyTest_2465, MultipleCopiesAreIndependent_2465)
{
    PopplerRectangle rect;
    rect.x1 = 5.0;
    rect.y1 = 10.0;
    rect.x2 = 15.0;
    rect.y2 = 20.0;

    PopplerRectangle *copy1 = poppler_rectangle_copy(&rect);
    PopplerRectangle *copy2 = poppler_rectangle_copy(&rect);
    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);

    EXPECT_DOUBLE_EQ(copy1->x1, copy2->x1);
    EXPECT_DOUBLE_EQ(copy1->y1, copy2->y1);
    EXPECT_DOUBLE_EQ(copy1->x2, copy2->x2);
    EXPECT_DOUBLE_EQ(copy1->y2, copy2->y2);

    // Modify one copy, the other should be unaffected
    copy1->x1 = 999.0;
    EXPECT_DOUBLE_EQ(copy2->x1, 5.0);

    poppler_rectangle_free(copy1);
    poppler_rectangle_free(copy2);
}
