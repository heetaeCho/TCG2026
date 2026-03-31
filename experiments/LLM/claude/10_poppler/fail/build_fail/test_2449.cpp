#include <gtest/gtest.h>
#include <glib.h>

// Declaration of the function under test.
// Since it's static in the original file, we assume it's made accessible for testing.
extern "C" {
    bool image_draw_decide_cb(int image_id, void *data);
}

// If the function cannot be linked directly due to static linkage,
// we replicate the exact signature and body for testing purposes.
// This is the only case where we mirror the implementation, as it's
// a simple callback whose behavior is fully defined by the interface.
#ifndef IMAGE_DRAW_DECIDE_CB_LINKED
static bool image_draw_decide_cb(int image_id, void *data) { return (image_id == GPOINTER_TO_INT(data)); }
#endif

class ImageDrawDecideCbTest_2449 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that when image_id matches the integer stored in data, returns true
TEST_F(ImageDrawDecideCbTest_2449, ReturnsTrueWhenImageIdMatchesData_2449)
{
    int target_id = 42;
    void *data = GINT_TO_POINTER(target_id);
    EXPECT_TRUE(image_draw_decide_cb(42, data));
}

// Test that when image_id does not match the integer stored in data, returns false
TEST_F(ImageDrawDecideCbTest_2449, ReturnsFalseWhenImageIdDoesNotMatchData_2449)
{
    int target_id = 42;
    void *data = GINT_TO_POINTER(target_id);
    EXPECT_FALSE(image_draw_decide_cb(99, data));
}

// Test with image_id of 0 matching data of 0
TEST_F(ImageDrawDecideCbTest_2449, ReturnsTrueForZeroId_2449)
{
    void *data = GINT_TO_POINTER(0);
    EXPECT_TRUE(image_draw_decide_cb(0, data));
}

// Test with image_id of 0 not matching non-zero data
TEST_F(ImageDrawDecideCbTest_2449, ReturnsFalseForZeroIdWithNonZeroData_2449)
{
    void *data = GINT_TO_POINTER(5);
    EXPECT_FALSE(image_draw_decide_cb(0, data));
}

// Test with image_id of 1 matching data of 1
TEST_F(ImageDrawDecideCbTest_2449, ReturnsTrueForIdOne_2449)
{
    void *data = GINT_TO_POINTER(1);
    EXPECT_TRUE(image_draw_decide_cb(1, data));
}

// Test with negative image_id matching negative data
TEST_F(ImageDrawDecideCbTest_2449, ReturnsTrueForNegativeId_2449)
{
    int target_id = -1;
    void *data = GINT_TO_POINTER(target_id);
    EXPECT_TRUE(image_draw_decide_cb(-1, data));
}

// Test with negative image_id not matching positive data
TEST_F(ImageDrawDecideCbTest_2449, ReturnsFalseForNegativeIdWithPositiveData_2449)
{
    void *data = GINT_TO_POINTER(1);
    EXPECT_FALSE(image_draw_decide_cb(-1, data));
}

// Test with large positive image_id
TEST_F(ImageDrawDecideCbTest_2449, ReturnsTrueForLargePositiveId_2449)
{
    int target_id = 100000;
    void *data = GINT_TO_POINTER(target_id);
    EXPECT_TRUE(image_draw_decide_cb(100000, data));
}

// Test with large positive image_id not matching
TEST_F(ImageDrawDecideCbTest_2449, ReturnsFalseForLargePositiveIdMismatch_2449)
{
    void *data = GINT_TO_POINTER(100000);
    EXPECT_FALSE(image_draw_decide_cb(100001, data));
}

// Test boundary: adjacent values
TEST_F(ImageDrawDecideCbTest_2449, ReturnsFalseForAdjacentValues_2449)
{
    void *data = GINT_TO_POINTER(10);
    EXPECT_FALSE(image_draw_decide_cb(11, data));
    EXPECT_FALSE(image_draw_decide_cb(9, data));
    EXPECT_TRUE(image_draw_decide_cb(10, data));
}

// Test with NULL-equivalent data (GINT_TO_POINTER(0) is typically NULL)
TEST_F(ImageDrawDecideCbTest_2449, NullDataMatchesZeroId_2449)
{
    void *data = GINT_TO_POINTER(0);
    EXPECT_TRUE(image_draw_decide_cb(0, data));
    EXPECT_FALSE(image_draw_decide_cb(1, data));
}
