// RefRecursionChecker_insert_tests_60.cpp
#include <gtest/gtest.h>

#include "Object.h" // From ./TestProjects/poppler/poppler/Object.h

namespace {

Ref MakeRef(int num, int gen) {
  Ref r;
  r.num = num;
  r.gen = gen;
  return r;
}

} // namespace

TEST(RefRecursionCheckerTest_60, InsertInvalidAlwaysReturnsTrue_60) {
  RefRecursionChecker checker;

  EXPECT_TRUE(checker.insert(Ref::INVALID()));
  EXPECT_TRUE(checker.insert(Ref::INVALID()));

  // Inserting INVALID should not prevent normal refs from being inserted.
  EXPECT_TRUE(checker.insert(MakeRef(1, 0)));
}

TEST(RefRecursionCheckerTest_60, FirstInsertOfValidRefReturnsTrue_60) {
  RefRecursionChecker checker;

  EXPECT_TRUE(checker.insert(MakeRef(123, 0)));
}

TEST(RefRecursionCheckerTest_60, SecondInsertOfSameNumReturnsFalse_60) {
  RefRecursionChecker checker;

  EXPECT_TRUE(checker.insert(MakeRef(7, 0)));
  EXPECT_FALSE(checker.insert(MakeRef(7, 0)));
}

TEST(RefRecursionCheckerTest_60, SameNumDifferentGenIsStillConsideredAlreadySeen_60) {
  RefRecursionChecker checker;

  EXPECT_TRUE(checker.insert(MakeRef(42, 0)));
  EXPECT_FALSE(checker.insert(MakeRef(42, 999)));
}

TEST(RefRecursionCheckerTest_60, DifferentNumsAreTrackedIndependently_60) {
  RefRecursionChecker checker;

  EXPECT_TRUE(checker.insert(MakeRef(1, 0)));
  EXPECT_TRUE(checker.insert(MakeRef(2, 0)));
  EXPECT_FALSE(checker.insert(MakeRef(1, 5))); // Same num as the first insert.
}

TEST(RefRecursionCheckerTest_60, NegativeNumBehavesLikeAnyOtherNum_60) {
  RefRecursionChecker checker;

  EXPECT_TRUE(checker.insert(MakeRef(-1, 0)));
  EXPECT_FALSE(checker.insert(MakeRef(-1, 1)));
}