#include <gtest/gtest.h>
#include <glib.h>

// Include the header for PopplerPoint and related functions
extern "C" {
#include "poppler-page.h"
}

// Forward declarations of the functions we're testing
extern "C" {
PopplerPoint *poppler_point_new(void);
PopplerPoint *poppler_point_copy(PopplerPoint *point);
void poppler_point_free(PopplerPoint *point);
}

class PopplerPointTest_2471 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_point_free does not crash when given a valid point
TEST_F(PopplerPointTest_2471, FreeValidPoint_2471)
{
    // Allocate a PopplerPoint using g_slice_new (mimicking how the library would allocate)
    PopplerPoint *point = g_slice_new(PopplerPoint);
    ASSERT_NE(point, nullptr);

    // Should not crash or cause issues
    poppler_point_free(point);
}

// Test that poppler_point_free handles NULL gracefully
// g_slice_free with NULL should be safe (it's a no-op for NULL in GLib)
TEST_F(PopplerPointTest_2471, FreeNullPoint_2471)
{
    // This tests the boundary condition of passing NULL
    // g_slice_free macro typically handles NULL safely
    poppler_point_free(nullptr);
    // If we reach here without crashing, the test passes
    SUCCEED();
}

// Test that poppler_point_free can free multiple points without issues
TEST_F(PopplerPointTest_2471, FreeMultiplePoints_2471)
{
    PopplerPoint *point1 = g_slice_new(PopplerPoint);
    PopplerPoint *point2 = g_slice_new(PopplerPoint);
    PopplerPoint *point3 = g_slice_new(PopplerPoint);

    ASSERT_NE(point1, nullptr);
    ASSERT_NE(point2, nullptr);
    ASSERT_NE(point3, nullptr);

    poppler_point_free(point1);
    poppler_point_free(point2);
    poppler_point_free(point3);
    // If we reach here without crashing, all frees succeeded
    SUCCEED();
}

// Test that poppler_point_new returns a non-null pointer (if available)
TEST_F(PopplerPointTest_2471, NewReturnsNonNull_2471)
{
    PopplerPoint *point = poppler_point_new();
    ASSERT_NE(point, nullptr);
    poppler_point_free(point);
}

// Test that poppler_point_copy returns a non-null copy of a valid point
TEST_F(PopplerPointTest_2471, CopyReturnsNonNull_2471)
{
    PopplerPoint *original = poppler_point_new();
    ASSERT_NE(original, nullptr);

    PopplerPoint *copy = poppler_point_copy(original);
    ASSERT_NE(copy, nullptr);

    // The copy should be a different pointer
    EXPECT_NE(original, copy);

    poppler_point_free(original);
    poppler_point_free(copy);
}

// Test allocating and freeing in a loop (stress test / boundary)
TEST_F(PopplerPointTest_2471, AllocateAndFreeInLoop_2471)
{
    const int iterations = 100;
    for (int i = 0; i < iterations; ++i) {
        PopplerPoint *point = g_slice_new(PopplerPoint);
        ASSERT_NE(point, nullptr);
        poppler_point_free(point);
    }
    SUCCEED();
}

// Test that freeing a newly created point works correctly
TEST_F(PopplerPointTest_2471, NewThenFree_2471)
{
    PopplerPoint *point = poppler_point_new();
    ASSERT_NE(point, nullptr);
    poppler_point_free(point);
    SUCCEED();
}

// Test copy then free both original and copy
TEST_F(PopplerPointTest_2471, CopyThenFreeBoth_2471)
{
    PopplerPoint *original = poppler_point_new();
    ASSERT_NE(original, nullptr);

    PopplerPoint *copy = poppler_point_copy(original);
    ASSERT_NE(copy, nullptr);

    // Free in reverse order
    poppler_point_free(copy);
    poppler_point_free(original);
    SUCCEED();
}
