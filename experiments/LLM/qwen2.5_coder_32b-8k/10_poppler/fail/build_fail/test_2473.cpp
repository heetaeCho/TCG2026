#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



// Test fixture for PopplerQuadrilateral tests

class PopplerQuadrilateralTest_2473 : public ::testing::Test {

protected:

    void SetUp() override {

        quad = new PopplerQuadrilateral();

        quad->p1.x = 0.0;

        quad->p1.y = 0.0;

        quad->p2.x = 1.0;

        quad->p2.y = 0.0;

        quad->p3.x = 1.0;

        quad->p3.y = 1.0;

        quad->p4.x = 0.0;

        quad->p4.y = 1.0;

    }



    void TearDown() override {

        delete quad;

    }



    PopplerQuadrilateral* quad;

};



// Test normal operation of poppler_quadrilateral_copy

TEST_F(PopplerQuadrilateralTest_2473, CopyCreatesIdenticalObject_2473) {

    PopplerQuadrilateral* copy = poppler_quadrilateral_copy(quad);

    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->p1.x, quad->p1.x);

    EXPECT_EQ(copy->p1.y, quad->p1.y);

    EXPECT_EQ(copy->p2.x, quad->p2.x);

    EXPECT_EQ(copy->p2.y, quad->p2.y);

    EXPECT_EQ(copy->p3.x, quad->p3.x);

    EXPECT_EQ(copy->p3.y, quad->p3.y);

    EXPECT_EQ(copy->p4.x, quad->p4.x);

    EXPECT_EQ(copy->p4.y, quad->p4.y);

    g_slice_free(PopplerQuadrilateral, copy);

}



// Test boundary condition with null input

TEST_F(PopplerQuadrilateralTest_2473, CopyWithNullInput_ReturnsNull_2473) {

    PopplerQuadrilateral* result = poppler_quadrilateral_copy(nullptr);

    EXPECT_EQ(result, nullptr);

}
