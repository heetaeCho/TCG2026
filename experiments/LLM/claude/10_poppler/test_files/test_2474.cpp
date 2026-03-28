#include <gtest/gtest.h>
#include <glib-object.h>

extern "C" {
#include "poppler.h"
}

class PopplerQuadrilateralTest_2474 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerQuadrilateralTest_2474, FreeValidQuadrilateral_2474)
{
    PopplerQuadrilateral *quad = g_slice_new(PopplerQuadrilateral);
    quad->p1.x = 0.0;
    quad->p1.y = 0.0;
    quad->p2.x = 1.0;
    quad->p2.y = 0.0;
    quad->p3.x = 1.0;
    quad->p3.y = 1.0;
    quad->p4.x = 0.0;
    quad->p4.y = 1.0;

    // Should not crash or leak
    poppler_quadrilateral_free(quad);
}

TEST_F(PopplerQuadrilateralTest_2474, FreeNullQuadrilateral_2474)
{
    // g_slice_free with NULL should be safe (g_slice_free checks for NULL)
    poppler_quadrilateral_free(nullptr);
}

TEST_F(PopplerQuadrilateralTest_2474, FreeQuadrilateralWithZeroCoordinates_2474)
{
    PopplerQuadrilateral *quad = g_slice_new0(PopplerQuadrilateral);
    // All fields are zero-initialized
    poppler_quadrilateral_free(quad);
}

TEST_F(PopplerQuadrilateralTest_2474, FreeQuadrilateralWithNegativeCoordinates_2474)
{
    PopplerQuadrilateral *quad = g_slice_new(PopplerQuadrilateral);
    quad->p1.x = -100.5;
    quad->p1.y = -200.3;
    quad->p2.x = -50.0;
    quad->p2.y = -100.0;
    quad->p3.x = -25.0;
    quad->p3.y = -50.0;
    quad->p4.x = -10.0;
    quad->p4.y = -20.0;

    poppler_quadrilateral_free(quad);
}

TEST_F(PopplerQuadrilateralTest_2474, FreeQuadrilateralWithLargeCoordinates_2474)
{
    PopplerQuadrilateral *quad = g_slice_new(PopplerQuadrilateral);
    quad->p1.x = 1e15;
    quad->p1.y = 1e15;
    quad->p2.x = 1e15;
    quad->p2.y = -1e15;
    quad->p3.x = -1e15;
    quad->p3.y = -1e15;
    quad->p4.x = -1e15;
    quad->p4.y = 1e15;

    poppler_quadrilateral_free(quad);
}

TEST_F(PopplerQuadrilateralTest_2474, FreeMultipleQuadrilaterals_2474)
{
    // Allocate and free multiple quadrilaterals to ensure no issues with repeated calls
    for (int i = 0; i < 100; i++) {
        PopplerQuadrilateral *quad = g_slice_new(PopplerQuadrilateral);
        quad->p1.x = static_cast<double>(i);
        quad->p1.y = static_cast<double>(i);
        quad->p2.x = static_cast<double>(i + 1);
        quad->p2.y = static_cast<double>(i);
        quad->p3.x = static_cast<double>(i + 1);
        quad->p3.y = static_cast<double>(i + 1);
        quad->p4.x = static_cast<double>(i);
        quad->p4.y = static_cast<double>(i + 1);
        poppler_quadrilateral_free(quad);
    }
}

TEST_F(PopplerQuadrilateralTest_2474, CopyAndFreeQuadrilateral_2474)
{
    PopplerQuadrilateral *quad = g_slice_new(PopplerQuadrilateral);
    quad->p1.x = 10.0;
    quad->p1.y = 20.0;
    quad->p2.x = 30.0;
    quad->p2.y = 40.0;
    quad->p3.x = 50.0;
    quad->p3.y = 60.0;
    quad->p4.x = 70.0;
    quad->p4.y = 80.0;

    // Copy the quadrilateral using poppler_quadrilateral_copy if available,
    // otherwise manually copy
    PopplerQuadrilateral *quad_copy = poppler_quadrilateral_copy(quad);
    ASSERT_NE(quad_copy, nullptr);

    EXPECT_DOUBLE_EQ(quad_copy->p1.x, 10.0);
    EXPECT_DOUBLE_EQ(quad_copy->p1.y, 20.0);
    EXPECT_DOUBLE_EQ(quad_copy->p2.x, 30.0);
    EXPECT_DOUBLE_EQ(quad_copy->p2.y, 40.0);
    EXPECT_DOUBLE_EQ(quad_copy->p3.x, 50.0);
    EXPECT_DOUBLE_EQ(quad_copy->p3.y, 60.0);
    EXPECT_DOUBLE_EQ(quad_copy->p4.x, 70.0);
    EXPECT_DOUBLE_EQ(quad_copy->p4.y, 80.0);

    poppler_quadrilateral_free(quad);
    poppler_quadrilateral_free(quad_copy);
}
