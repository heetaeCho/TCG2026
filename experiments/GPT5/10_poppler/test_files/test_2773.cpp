// File: movie_time_test_2773.cc

#include <gtest/gtest.h>

#include "Movie.h"  // Expected to provide MovieActivationParameters::MovieTime

namespace {

using MovieTime = MovieActivationParameters::MovieTime;

class MovieTimeTest_2773 : public ::testing::Test {};

TEST_F(MovieTimeTest_2773, DefaultConstructorSetsUnitsPerSecondToZero_2773)
{
  MovieTime t;
  EXPECT_EQ(t.units_per_second, 0);
}

TEST_F(MovieTimeTest_2773, CanAssignMembersAfterDefaultConstruction_2773)
{
  MovieTime t;
  t.units = 123UL;
  t.units_per_second = 60;

  EXPECT_EQ(t.units, 123UL);
  EXPECT_EQ(t.units_per_second, 60);
}

TEST_F(MovieTimeTest_2773, CopyConstructionCopiesPublicFields_2773)
{
  MovieTime a;
  a.units = 999UL;
  a.units_per_second = 30;

  MovieTime b(a);

  EXPECT_EQ(b.units, 999UL);
  EXPECT_EQ(b.units_per_second, 30);
}

TEST_F(MovieTimeTest_2773, CopyAssignmentCopiesPublicFields_2773)
{
  MovieTime a;
  a.units = 7UL;
  a.units_per_second = 24;

  MovieTime b;
  b.units = 0UL;
  b.units_per_second = 0;

  b = a;

  EXPECT_EQ(b.units, 7UL);
  EXPECT_EQ(b.units_per_second, 24);
}

TEST_F(MovieTimeTest_2773, SupportsBoundaryValuesForUnitsAndUnitsPerSecond_2773)
{
  MovieTime t;

  // Boundary-ish values (do not assume any internal validation).
  t.units = 0UL;
  t.units_per_second = 0;
  EXPECT_EQ(t.units, 0UL);
  EXPECT_EQ(t.units_per_second, 0);

  t.units = ~0UL;   // max for unsigned long without <limits>
  t.units_per_second = -1; // int boundary-ish
  EXPECT_EQ(t.units, ~0UL);
  EXPECT_EQ(t.units_per_second, -1);
}

}  // namespace