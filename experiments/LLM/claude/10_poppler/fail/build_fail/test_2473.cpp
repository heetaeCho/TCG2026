#include <glib.h>
#include <gtest/gtest.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler-page.h"
}

// We need the declaration of poppler_quadrilateral_copy
extern "C" {
PopplerQuadrilateral *poppler_quadrilateral_copy(PopplerQuadrilateral *quad);
void poppler_quadrilateral_free(PopplerQuadrilateral *quad);
}

class PopplerQuadrilateralTest_2473 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that copying a valid quadrilateral returns a non-null pointer
TEST_F(PopplerQuadrilateralTest_2473, CopyValidQuadReturnsNonNull_2473)
{
    PopplerQuadrilateral quad;
    quad.p1.x = 1.0;
    quad.p1.y = 2.0;
    quad.p2.x = 3.0;
    quad.p2.y = 4.0;
    quad.p3.x = 5.0;
    quad.p3.y = 6.0;
    quad.p4.x = 7.0;
    quad.p4.y = 8.0;

    PopplerQuadrilateral *copy = poppler_quadrilateral_copy(&quad);
    ASSERT_NE(copy, nullptr);
    g_slice_free(PopplerQuadrilateral, copy);
}

// Test that the copied quadrilateral has the same values as the original
TEST_F(PopplerQuadrilateralTest_2473, CopyPreservesValues_2473)
{
    PopplerQuadrilateral quad;
    quad.p1.x = 10.5;
    quad.p1.y = 20.5;
    quad.p2.x = 30.5;
    quad.p2.y = 40.5;
    quad.p3.x = 50.5;
    quad.p3.y = 60.5;
    quad.p4.x = 70.5;
    quad.p4.y = 80.5;

    PopplerQuadrilateral *copy = poppler_quadrilateral_copy(&quad);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(copy->p1.x, quad.p1.x);
    EXPECT_DOUBLE_EQ(copy->p1.y, quad.p1.y);
    EXPECT_DOUBLE_EQ(copy->p2.x, quad.p2.x);
    EXPECT_DOUBLE_EQ(copy->p2.y, quad.p2.y);
    EXPECT_DOUBLE_EQ(copy->p3.x, quad.p3.x);
    EXPECT_DOUBLE_EQ(copy->p3.y, quad.p3.y);
    EXPECT_DOUBLE_EQ(copy->p4.x, quad.p4.x);
    EXPECT_DOUBLE_EQ(copy->p4.y, quad.p4.y);

    g_slice_free(PopplerQuadrilateral, copy);
}

// Test that passing nullptr returns NULL
TEST_F(PopplerQuadrilateralTest_2473, CopyNullReturnsNull_2473)
{
    PopplerQuadrilateral *copy = poppler_quadrilateral_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test that the copy is a distinct object (different address)
TEST_F(PopplerQuadrilateralTest_2473, CopyReturnsDifferentPointer_2473)
{
    PopplerQuadrilateral quad;
    quad.p1.x = 0.0;
    quad.p1.y = 0.0;
    quad.p2.x = 1.0;
    quad.p2.y = 0.0;
    quad.p3.x = 1.0;
    quad.p3.y = 1.0;
    quad.p4.x = 0.0;
    quad.p4.y = 1.0;

    PopplerQuadrilateral *copy = poppler_quadrilateral_copy(&quad);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, &quad);

    g_slice_free(PopplerQuadrilateral, copy);
}

// Test copying a quadrilateral with zero values
TEST_F(PopplerQuadrilateralTest_2473, CopyZeroValues_2473)
{
    PopplerQuadrilateral quad;
    memset(&quad, 0, sizeof(PopplerQuadrilateral));

    PopplerQuadrilateral *copy = poppler_quadrilateral_copy(&quad);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(copy->p1.x, 0.0);
    EXPECT_DOUBLE_EQ(copy->p1.y, 0.0);
    EXPECT_DOUBLE_EQ(copy->p2.x, 0.0);
    EXPECT_DOUBLE_EQ(copy->p2.y, 0.0);
    EXPECT_DOUBLE_EQ(copy->p3.x, 0.0);
    EXPECT_DOUBLE_EQ(copy->p3.y, 0.0);
    EXPECT_DOUBLE_EQ(copy->p4.x, 0.0);
    EXPECT_DOUBLE_EQ(copy->p4.y, 0.0);

    g_slice_free(PopplerQuadrilateral, copy);
}

// Test copying a quadrilateral with negative values
TEST_F(PopplerQuadrilateralTest_2473, CopyNegativeValues_2473)
{
    PopplerQuadrilateral quad;
    quad.p1.x = -1.0;
    quad.p1.y = -2.0;
    quad.p2.x = -3.0;
    quad.p2.y = -4.0;
    quad.p3.x = -5.0;
    quad.p3.y = -6.0;
    quad.p4.x = -7.0;
    quad.p4.y = -8.0;

    PopplerQuadrilateral *copy = poppler_quadrilateral_copy(&quad);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(copy->p1.x, -1.0);
    EXPECT_DOUBLE_EQ(copy->p1.y, -2.0);
    EXPECT_DOUBLE_EQ(copy->p2.x, -3.0);
    EXPECT_DOUBLE_EQ(copy->p2.y, -4.0);
    EXPECT_DOUBLE_EQ(copy->p3.x, -5.0);
    EXPECT_DOUBLE_EQ(copy->p3.y, -6.0);
    EXPECT_DOUBLE_EQ(copy->p4.x, -7.0);
    EXPECT_DOUBLE_EQ(copy->p4.y, -8.0);

    g_slice_free(PopplerQuadrilateral, copy);
}

// Test copying with very large values
TEST_F(PopplerQuadrilateralTest_2473, CopyLargeValues_2473)
{
    PopplerQuadrilateral quad;
    quad.p1.x = 1e300;
    quad.p1.y = -1e300;
    quad.p2.x = 1e300;
    quad.p2.y = 1e300;
    quad.p3.x = -1e300;
    quad.p3.y = -1e300;
    quad.p4.x = -1e300;
    quad.p4.y = 1e300;

    PopplerQuadrilateral *copy = poppler_quadrilateral_copy(&quad);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(copy->p1.x, 1e300);
    EXPECT_DOUBLE_EQ(copy->p1.y, -1e300);
    EXPECT_DOUBLE_EQ(copy->p2.x, 1e300);
    EXPECT_DOUBLE_EQ(copy->p2.y, 1e300);
    EXPECT_DOUBLE_EQ(copy->p3.x, -1e300);
    EXPECT_DOUBLE_EQ(copy->p3.y, -1e300);
    EXPECT_DOUBLE_EQ(copy->p4.x, -1e300);
    EXPECT_DOUBLE_EQ(copy->p4.y, 1e300);

    g_slice_free(PopplerQuadrilateral, copy);
}

// Test that modifying the copy does not affect the original
TEST_F(PopplerQuadrilateralTest_2473, CopyIsIndependent_2473)
{
    PopplerQuadrilateral quad;
    quad.p1.x = 1.0;
    quad.p1.y = 2.0;
    quad.p2.x = 3.0;
    quad.p2.y = 4.0;
    quad.p3.x = 5.0;
    quad.p3.y = 6.0;
    quad.p4.x = 7.0;
    quad.p4.y = 8.0;

    PopplerQuadrilateral *copy = poppler_quadrilateral_copy(&quad);
    ASSERT_NE(copy, nullptr);

    // Modify the copy
    copy->p1.x = 100.0;
    copy->p2.y = 200.0;

    // Original should be unchanged
    EXPECT_DOUBLE_EQ(quad.p1.x, 1.0);
    EXPECT_DOUBLE_EQ(quad.p2.y, 4.0);

    g_slice_free(PopplerQuadrilateral, copy);
}

// Test copying multiple times produces independent copies
TEST_F(PopplerQuadrilateralTest_2473, MultipleCopiesAreIndependent_2473)
{
    PopplerQuadrilateral quad;
    quad.p1.x = 1.0;
    quad.p1.y = 2.0;
    quad.p2.x = 3.0;
    quad.p2.y = 4.0;
    quad.p3.x = 5.0;
    quad.p3.y = 6.0;
    quad.p4.x = 7.0;
    quad.p4.y = 8.0;

    PopplerQuadrilateral *copy1 = poppler_quadrilateral_copy(&quad);
    PopplerQuadrilateral *copy2 = poppler_quadrilateral_copy(&quad);

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);

    EXPECT_DOUBLE_EQ(copy1->p1.x, copy2->p1.x);
    EXPECT_DOUBLE_EQ(copy1->p4.y, copy2->p4.y);

    g_slice_free(PopplerQuadrilateral, copy1);
    g_slice_free(PopplerQuadrilateral, copy2);
}
