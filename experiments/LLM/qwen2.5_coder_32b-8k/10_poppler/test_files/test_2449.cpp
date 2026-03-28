#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming image_draw_decide_cb is part of a class or can be tested in isolation.

// For this example, we will assume it's a standalone function and test it directly.



TEST(ImageDrawDecideCbTest_2449, ImageIdMatchesData_2449) {

    int image_id = 42;

    void* data = GINT_TO_POINTER(42);

    EXPECT_TRUE(image_draw_decide_cb(image_id, data));

}



TEST(ImageDrawDecideCbTest_2449, ImageIdDoesNotMatchData_2449) {

    int image_id = 42;

    void* data = GINT_TO_POINTER(24);

    EXPECT_FALSE(image_draw_decide_cb(image_id, data));

}



TEST(ImageDrawDecideCbTest_2449, ZeroImageIdMatchesZeroData_2449) {

    int image_id = 0;

    void* data = GINT_TO_POINTER(0);

    EXPECT_TRUE(image_draw_decide_cb(image_id, data));

}



TEST(ImageDrawDecideCbTest_2449, NegativeImageIdDoesNotMatchPositiveData_2449) {

    int image_id = -1;

    void* data = GINT_TO_POINTER(1);

    EXPECT_FALSE(image_draw_decide_cb(image_id, data));

}



TEST(ImageDrawDecideCbTest_2449, LargeImageIdMatchesLargeData_2449) {

    int image_id = 100000;

    void* data = GINT_TO_POINTER(100000);

    EXPECT_TRUE(image_draw_decide_cb(image_id, data));

}
