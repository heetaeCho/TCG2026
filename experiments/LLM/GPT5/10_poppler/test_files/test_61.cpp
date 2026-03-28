// RefRecursionChecker_test_61.cpp
// Unit tests for RefRecursionChecker::remove (and observable interactions with insert)
//
// File under test: ./TestProjects/poppler/poppler/Object.h

#include <gtest/gtest.h>

#include "Object.h"  // Ref, RefRecursionChecker

namespace {

static Ref MakeRef(int num, int gen = 0)
{
  Ref r;
  r.num = num;
  r.gen = gen;
  return r;
}

class RefRecursionCheckerTest_61 : public ::testing::Test {
protected:
  RefRecursionChecker checker;
};

} // namespace

TEST_F(RefRecursionCheckerTest_61, RemoveUnseenRefDoesNotCrash_61)
{
  // Removing something that was never inserted should be safe.
  EXPECT_NO_THROW(checker.remove(MakeRef(1, 0)));
  EXPECT_NO_THROW(checker.remove(MakeRef(0, 0)));
  EXPECT_NO_THROW(checker.remove(MakeRef(-1, 0)));
}

TEST_F(RefRecursionCheckerTest_61, RemoveAfterInsertAllowsReinsert_61)
{
  Ref r = MakeRef(123, 0);

  // First insert should succeed for a fresh checker.
  EXPECT_TRUE(checker.insert(r));

  // Inserting the same ref again should indicate "already seen".
  EXPECT_FALSE(checker.insert(r));

  // After remove, inserting again should succeed.
  checker.remove(r);
  EXPECT_TRUE(checker.insert(r));
}

TEST_F(RefRecursionCheckerTest_61, RemoveUsesRefNumNotGen_61)
{
  Ref r1 = MakeRef(77, 0);
  Ref rSameNumDifferentGen = MakeRef(77, 999);

  EXPECT_TRUE(checker.insert(r1));
  EXPECT_FALSE(checker.insert(r1));

  // Remove with same num but different gen should still remove the tracked entry.
  checker.remove(rSameNumDifferentGen);

  // Should behave like a fresh insert again.
  EXPECT_TRUE(checker.insert(r1));
}

TEST_F(RefRecursionCheckerTest_61, RemoveIsIdempotentForSameRef_61)
{
  Ref r = MakeRef(42, 1);

  EXPECT_TRUE(checker.insert(r));
  checker.remove(r);

  // Removing again should still be safe and not change correctness.
  EXPECT_NO_THROW(checker.remove(r));
  EXPECT_TRUE(checker.insert(r));
}

TEST_F(RefRecursionCheckerTest_61, BoundaryValuesForRefNum_61)
{
  Ref rMinish = MakeRef(-2147483647, 0);
  Ref rZero = MakeRef(0, 0);
  Ref rMax = MakeRef(2147483647, 0);

  // Insert should accept boundary-ish values if supported by the implementation.
  EXPECT_TRUE(checker.insert(rMinish));
  EXPECT_TRUE(checker.insert(rZero));
  EXPECT_TRUE(checker.insert(rMax));

  // Removing boundary values should be safe.
  EXPECT_NO_THROW(checker.remove(rMinish));
  EXPECT_NO_THROW(checker.remove(rZero));
  EXPECT_NO_THROW(checker.remove(rMax));

  // After remove, should be re-insertable.
  EXPECT_TRUE(checker.insert(rMinish));
  EXPECT_TRUE(checker.insert(rZero));
  EXPECT_TRUE(checker.insert(rMax));
}