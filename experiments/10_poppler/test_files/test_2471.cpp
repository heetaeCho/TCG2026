#include <gtest/gtest.h>

#include "poppler-page.h"



// Test fixture for PopplerPoint tests

class PopplerPointTest_2471 : public ::testing::Test {

protected:

    void SetUp() override {

        point = static_cast<PopplerPoint*>(g_slice_alloc(sizeof(PopplerPoint)));

    }



    void TearDown() override {

        poppler_point_free(point);

    }



    PopplerPoint* point;

};



// Test normal operation of poppler_point_free

TEST_F(PopplerPointTest_2471, FreeAllocatedPoint_NormalOperation_2471) {

    // The test itself is the act of allocating and then freeing a point.

    // Since there's no observable state to check, we assume that if no memory leaks occur,

    // the function works as expected.

}



// Test boundary condition: Freeing a nullptr

TEST_F(PopplerPointTest_2471, FreeNullPointer_BoundaryCondition_2471) {

    EXPECT_NO_THROW(poppler_point_free(nullptr));

}
