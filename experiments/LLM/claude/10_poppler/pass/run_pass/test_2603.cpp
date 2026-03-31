#include <gtest/gtest.h>

// Replicate the necessary structures from the codebase
struct SplashScreenPoint {
    int dist;
};

struct cmpDistancesFunctor {
    bool operator()(const SplashScreenPoint &p0, const SplashScreenPoint &p1) {
        return p0.dist < p1.dist;
    }
};

class CmpDistancesFunctorTest_2603 : public ::testing::Test {
protected:
    cmpDistancesFunctor cmp;
};

TEST_F(CmpDistancesFunctorTest_2603, FirstLessThanSecond_2603) {
    SplashScreenPoint p0{1};
    SplashScreenPoint p1{2};
    EXPECT_TRUE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, FirstGreaterThanSecond_2603) {
    SplashScreenPoint p0{5};
    SplashScreenPoint p1{3};
    EXPECT_FALSE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, EqualDistances_2603) {
    SplashScreenPoint p0{4};
    SplashScreenPoint p1{4};
    EXPECT_FALSE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, ZeroDistances_2603) {
    SplashScreenPoint p0{0};
    SplashScreenPoint p1{0};
    EXPECT_FALSE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, NegativeDistances_FirstLess_2603) {
    SplashScreenPoint p0{-5};
    SplashScreenPoint p1{-2};
    EXPECT_TRUE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, NegativeDistances_FirstGreater_2603) {
    SplashScreenPoint p0{-1};
    SplashScreenPoint p1{-3};
    EXPECT_FALSE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, NegativeAndPositive_2603) {
    SplashScreenPoint p0{-1};
    SplashScreenPoint p1{1};
    EXPECT_TRUE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, PositiveAndNegative_2603) {
    SplashScreenPoint p0{1};
    SplashScreenPoint p1{-1};
    EXPECT_FALSE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, LargePositiveValues_2603) {
    SplashScreenPoint p0{2147483646};
    SplashScreenPoint p1{2147483647};
    EXPECT_TRUE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, LargeNegativeValues_2603) {
    SplashScreenPoint p0{-2147483648};
    SplashScreenPoint p1{-2147483647};
    EXPECT_TRUE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, ZeroAndPositive_2603) {
    SplashScreenPoint p0{0};
    SplashScreenPoint p1{1};
    EXPECT_TRUE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, ZeroAndNegative_2603) {
    SplashScreenPoint p0{0};
    SplashScreenPoint p1{-1};
    EXPECT_FALSE(cmp(p0, p1));
}

TEST_F(CmpDistancesFunctorTest_2603, Antisymmetry_2603) {
    SplashScreenPoint p0{3};
    SplashScreenPoint p1{7};
    // If p0 < p1, then !(p1 < p0)
    EXPECT_TRUE(cmp(p0, p1));
    EXPECT_FALSE(cmp(p1, p0));
}

TEST_F(CmpDistancesFunctorTest_2603, Irreflexivity_2603) {
    SplashScreenPoint p0{42};
    // An element should not be less than itself
    EXPECT_FALSE(cmp(p0, p0));
}

TEST_F(CmpDistancesFunctorTest_2603, UsableWithStdSort_2603) {
    std::vector<SplashScreenPoint> points = {{5}, {1}, {3}, {2}, {4}};
    std::sort(points.begin(), points.end(), cmp);
    for (size_t i = 1; i < points.size(); ++i) {
        EXPECT_LE(points[i - 1].dist, points[i].dist);
    }
}

TEST_F(CmpDistancesFunctorTest_2603, UsableWithStdSortNegatives_2603) {
    std::vector<SplashScreenPoint> points = {{-3}, {-1}, {-5}, {0}, {2}};
    std::sort(points.begin(), points.end(), cmp);
    for (size_t i = 1; i < points.size(); ++i) {
        EXPECT_LE(points[i - 1].dist, points[i].dist);
    }
}
