// File: cmpDistancesFunctor_test_2603.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <set>
#include <vector>

// Minimal declarations matching the provided interface / partial code.
struct SplashScreenPoint {
  int dist;
};

struct cmpDistancesFunctor {
  bool operator()(const SplashScreenPoint p0, const SplashScreenPoint p1) { return p0.dist < p1.dist; }
};

class cmpDistancesFunctorTest_2603 : public ::testing::Test {
protected:
  cmpDistancesFunctor cmp_;
};

// Normal operation: basic true/false behavior.
TEST_F(cmpDistancesFunctorTest_2603, ReturnsTrueWhenLeftDistanceIsSmaller_2603) {
  SplashScreenPoint a{1};
  SplashScreenPoint b{2};

  EXPECT_TRUE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

TEST_F(cmpDistancesFunctorTest_2603, ReturnsFalseWhenDistancesAreEqual_2603) {
  SplashScreenPoint a{5};
  SplashScreenPoint b{5};

  EXPECT_FALSE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

// Boundary/edge values: negatives and int limits.
TEST_F(cmpDistancesFunctorTest_2603, HandlesNegativeDistances_2603) {
  SplashScreenPoint neg{-10};
  SplashScreenPoint zero{0};
  SplashScreenPoint pos{3};

  EXPECT_TRUE(cmp_(neg, zero));
  EXPECT_TRUE(cmp_(neg, pos));
  EXPECT_TRUE(cmp_(zero, pos));

  EXPECT_FALSE(cmp_(zero, neg));
  EXPECT_FALSE(cmp_(pos, neg));
  EXPECT_FALSE(cmp_(pos, zero));
}

TEST_F(cmpDistancesFunctorTest_2603, HandlesIntMinAndIntMax_2603) {
  SplashScreenPoint minPt{std::numeric_limits<int>::min()};
  SplashScreenPoint maxPt{std::numeric_limits<int>::max()};

  EXPECT_TRUE(cmp_(minPt, maxPt));
  EXPECT_FALSE(cmp_(maxPt, minPt));
  EXPECT_FALSE(cmp_(minPt, minPt));
  EXPECT_FALSE(cmp_(maxPt, maxPt));
}

// External interaction / integration-style observable behavior: use in std::sort.
TEST_F(cmpDistancesFunctorTest_2603, SortOrdersPointsByAscendingDistance_2603) {
  std::vector<SplashScreenPoint> pts = {{3}, {-1}, {2}, {2}, {0}};

  std::sort(pts.begin(), pts.end(), cmp_);

  ASSERT_EQ(pts.size(), 5u);
  EXPECT_EQ(pts[0].dist, -1);
  EXPECT_EQ(pts[1].dist, 0);
  EXPECT_EQ(pts[2].dist, 2);
  EXPECT_EQ(pts[3].dist, 2);
  EXPECT_EQ(pts[4].dist, 3);

  // Additionally verify the result is non-decreasing according to the interface.
  for (size_t i = 1; i < pts.size(); ++i) {
    EXPECT_LE(pts[i - 1].dist, pts[i].dist);
    // If previous is not less-than current, comparator should be false in that direction.
    if (pts[i - 1].dist == pts[i].dist) {
      EXPECT_FALSE(cmp_(pts[i - 1], pts[i]));
      EXPECT_FALSE(cmp_(pts[i], pts[i - 1]));
    } else {
      EXPECT_TRUE(cmp_(pts[i - 1], pts[i]));
      EXPECT_FALSE(cmp_(pts[i], pts[i - 1]));
    }
  }
}

// Boundary/behavior with associative containers: duplicates collapse when comparator deems them equivalent.
TEST_F(cmpDistancesFunctorTest_2603, SetTreatsEqualDistancesAsEquivalentKeys_2603) {
  std::set<SplashScreenPoint, cmpDistancesFunctor> s;
  s.insert(SplashScreenPoint{7});
  s.insert(SplashScreenPoint{7});  // Equivalent under comparator (neither less-than the other).
  s.insert(SplashScreenPoint{6});
  s.insert(SplashScreenPoint{8});

  ASSERT_EQ(s.size(), 3u);

  auto it = s.begin();
  ASSERT_NE(it, s.end());
  EXPECT_EQ(it->dist, 6);
  ++it;
  ASSERT_NE(it, s.end());
  EXPECT_EQ(it->dist, 7);
  ++it;
  ASSERT_NE(it, s.end());
  EXPECT_EQ(it->dist, 8);
}