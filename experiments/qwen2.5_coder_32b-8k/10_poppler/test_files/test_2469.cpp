#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "poppler-page.h"



class PopplerPointTest_2469 : public ::testing::Test {

protected:

    void SetUp() override {

        point = poppler_point_new();

    }



    void TearDown() override {

        g_slice_free(PopplerPoint, point);

    }



    PopplerPoint* point;

};



TEST_F(PopplerPointTest_2469, NewPointInitializesCoordinatesToZero_2469) {

    EXPECT_EQ(point->x, 0.0);

    EXPECT_EQ(point->y, 0.0);

}



TEST_F(PopplerPointTest_2469, NewPointDoesNotCrashWithNull_2469) {

    // This test is more of a sanity check to ensure that poppler_point_new does not crash

    // when called in the context of a test setup and teardown.

    SUCCEED();

}



// Since the function poppler_point_new() does not take any parameters and only allocates memory,

// there are no boundary conditions or exceptional/error cases to test based on the provided interface.



```


