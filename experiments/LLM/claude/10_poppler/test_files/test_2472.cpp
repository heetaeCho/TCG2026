#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

// Forward declaration of the struct and function
typedef struct _PopplerQuadrilateral PopplerQuadrilateral;

struct _PopplerQuadrilateral {
    double p1_x, p1_y;
    double p2_x, p2_y;
    double p3_x, p3_y;
    double p4_x, p4_y;
};

PopplerQuadrilateral *poppler_quadrilateral_new(void);
}

class PopplerQuadrilateralTest_2472 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated quadrilaterals
    }
};

TEST_F(PopplerQuadrilateralTest_2472, NewReturnsNonNull_2472)
{
    PopplerQuadrilateral *quad = poppler_quadrilateral_new();
    ASSERT_NE(quad, nullptr);
    g_slice_free(PopplerQuadrilateral, quad);
}

TEST_F(PopplerQuadrilateralTest_2472, NewReturnsZeroInitialized_2472)
{
    PopplerQuadrilateral *quad = poppler_quadrilateral_new();
    ASSERT_NE(quad, nullptr);

    // g_slice_new0 zero-initializes the memory, so all fields should be 0
    EXPECT_DOUBLE_EQ(quad->p1_x, 0.0);
    EXPECT_DOUBLE_EQ(quad->p1_y, 0.0);
    EXPECT_DOUBLE_EQ(quad->p2_x, 0.0);
    EXPECT_DOUBLE_EQ(quad->p2_y, 0.0);
    EXPECT_DOUBLE_EQ(quad->p3_x, 0.0);
    EXPECT_DOUBLE_EQ(quad->p3_y, 0.0);
    EXPECT_DOUBLE_EQ(quad->p4_x, 0.0);
    EXPECT_DOUBLE_EQ(quad->p4_y, 0.0);

    g_slice_free(PopplerQuadrilateral, quad);
}

TEST_F(PopplerQuadrilateralTest_2472, MultipleAllocationsReturnDistinctPointers_2472)
{
    PopplerQuadrilateral *quad1 = poppler_quadrilateral_new();
    PopplerQuadrilateral *quad2 = poppler_quadrilateral_new();

    ASSERT_NE(quad1, nullptr);
    ASSERT_NE(quad2, nullptr);
    EXPECT_NE(quad1, quad2);

    g_slice_free(PopplerQuadrilateral, quad1);
    g_slice_free(PopplerQuadrilateral, quad2);
}

TEST_F(PopplerQuadrilateralTest_2472, FieldsAreWritableAfterNew_2472)
{
    PopplerQuadrilateral *quad = poppler_quadrilateral_new();
    ASSERT_NE(quad, nullptr);

    quad->p1_x = 1.0;
    quad->p1_y = 2.0;
    quad->p2_x = 3.0;
    quad->p2_y = 4.0;
    quad->p3_x = 5.0;
    quad->p3_y = 6.0;
    quad->p4_x = 7.0;
    quad->p4_y = 8.0;

    EXPECT_DOUBLE_EQ(quad->p1_x, 1.0);
    EXPECT_DOUBLE_EQ(quad->p1_y, 2.0);
    EXPECT_DOUBLE_EQ(quad->p2_x, 3.0);
    EXPECT_DOUBLE_EQ(quad->p2_y, 4.0);
    EXPECT_DOUBLE_EQ(quad->p3_x, 5.0);
    EXPECT_DOUBLE_EQ(quad->p3_y, 6.0);
    EXPECT_DOUBLE_EQ(quad->p4_x, 7.0);
    EXPECT_DOUBLE_EQ(quad->p4_y, 8.0);

    g_slice_free(PopplerQuadrilateral, quad);
}

TEST_F(PopplerQuadrilateralTest_2472, RepeatedAllocAndFree_2472)
{
    // Stress test: allocate and free multiple times to check for issues
    for (int i = 0; i < 100; i++) {
        PopplerQuadrilateral *quad = poppler_quadrilateral_new();
        ASSERT_NE(quad, nullptr);
        EXPECT_DOUBLE_EQ(quad->p1_x, 0.0);
        EXPECT_DOUBLE_EQ(quad->p1_y, 0.0);
        g_slice_free(PopplerQuadrilateral, quad);
    }
}
