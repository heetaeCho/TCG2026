#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

// Forward declaration of the struct and function
typedef struct {
    double x;
    double y;
} PopplerPoint;

PopplerPoint *poppler_point_new(void);
}

class PopplerPointTest_2469 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated points
        for (auto p : allocated_points) {
            if (p) {
                g_slice_free(PopplerPoint, p);
            }
        }
    }

    PopplerPoint *createAndTrack() {
        PopplerPoint *p = poppler_point_new();
        if (p) {
            allocated_points.push_back(p);
        }
        return p;
    }

    std::vector<PopplerPoint *> allocated_points;
};

TEST_F(PopplerPointTest_2469, ReturnsNonNull_2469)
{
    PopplerPoint *point = createAndTrack();
    ASSERT_NE(point, nullptr);
}

TEST_F(PopplerPointTest_2469, InitializedToZero_2469)
{
    PopplerPoint *point = createAndTrack();
    ASSERT_NE(point, nullptr);
    EXPECT_DOUBLE_EQ(point->x, 0.0);
    EXPECT_DOUBLE_EQ(point->y, 0.0);
}

TEST_F(PopplerPointTest_2469, FieldsAreWritable_2469)
{
    PopplerPoint *point = createAndTrack();
    ASSERT_NE(point, nullptr);

    point->x = 3.14;
    point->y = 2.71;

    EXPECT_DOUBLE_EQ(point->x, 3.14);
    EXPECT_DOUBLE_EQ(point->y, 2.71);
}

TEST_F(PopplerPointTest_2469, MultipleAllocationsAreIndependent_2469)
{
    PopplerPoint *p1 = createAndTrack();
    PopplerPoint *p2 = createAndTrack();

    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    EXPECT_NE(p1, p2);

    p1->x = 1.0;
    p1->y = 2.0;
    p2->x = 3.0;
    p2->y = 4.0;

    EXPECT_DOUBLE_EQ(p1->x, 1.0);
    EXPECT_DOUBLE_EQ(p1->y, 2.0);
    EXPECT_DOUBLE_EQ(p2->x, 3.0);
    EXPECT_DOUBLE_EQ(p2->y, 4.0);
}

TEST_F(PopplerPointTest_2469, NegativeValues_2469)
{
    PopplerPoint *point = createAndTrack();
    ASSERT_NE(point, nullptr);

    point->x = -100.5;
    point->y = -200.75;

    EXPECT_DOUBLE_EQ(point->x, -100.5);
    EXPECT_DOUBLE_EQ(point->y, -200.75);
}

TEST_F(PopplerPointTest_2469, LargeValues_2469)
{
    PopplerPoint *point = createAndTrack();
    ASSERT_NE(point, nullptr);

    point->x = 1e15;
    point->y = 1e15;

    EXPECT_DOUBLE_EQ(point->x, 1e15);
    EXPECT_DOUBLE_EQ(point->y, 1e15);
}

TEST_F(PopplerPointTest_2469, VerySmallValues_2469)
{
    PopplerPoint *point = createAndTrack();
    ASSERT_NE(point, nullptr);

    point->x = 1e-15;
    point->y = 1e-15;

    EXPECT_DOUBLE_EQ(point->x, 1e-15);
    EXPECT_DOUBLE_EQ(point->y, 1e-15);
}

TEST_F(PopplerPointTest_2469, MultipleAllocationsAllZeroInitialized_2469)
{
    for (int i = 0; i < 10; i++) {
        PopplerPoint *point = createAndTrack();
        ASSERT_NE(point, nullptr);
        EXPECT_DOUBLE_EQ(point->x, 0.0) << "Iteration " << i;
        EXPECT_DOUBLE_EQ(point->y, 0.0) << "Iteration " << i;
    }
}
