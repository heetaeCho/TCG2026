// RefRecursionCheckerRemover_test_62.cpp
#include <gtest/gtest.h>

#include "poppler/Object.h" // Ref, RefRecursionChecker, RefRecursionCheckerRemover

namespace {

// Helper to build a Ref without assuming an explicit constructor exists.
static Ref MakeRef(int num, int gen) {
  Ref r{};
  r.num = num;
  r.gen = gen;
  return r;
}

} // namespace

TEST(RefRecursionCheckerRemoverTest_62, DestructorRestoresAbilityToInsertSameRef_62) {
  RefRecursionChecker checker;
  const Ref r = MakeRef(1, 0);

  const bool firstInsert = checker.insert(r);
  const bool secondInsert = checker.insert(r);

  // If insert() doesn't distinguish repeated refs, we can't observe "remove()" via the public API.
  if (secondInsert == firstInsert) {
    GTEST_SKIP() << "insert() does not appear to track repeated refs; cannot observe removal via insert().";
  }

  {
    RefRecursionCheckerRemover remover(checker, r);
  } // remover dtor should call checker.remove(r)

  const bool thirdInsert = checker.insert(r);
  EXPECT_EQ(thirdInsert, firstInsert);
}

TEST(RefRecursionCheckerRemoverTest_62, DestructorOnlyAffectsItsOwnRef_62) {
  RefRecursionChecker checker;
  const Ref r1 = MakeRef(10, 0);
  const Ref r2 = MakeRef(11, 0);

  const bool r1_first = checker.insert(r1);
  const bool r1_second = checker.insert(r1);
  if (r1_second == r1_first) {
    GTEST_SKIP() << "insert() does not appear to track repeated refs; cannot observe targeted removal.";
  }

  // Make r2 "seen" too, so we can verify it is not altered by removing r1.
  const bool r2_first = checker.insert(r2);
  const bool r2_second = checker.insert(r2);
  if (r2_second == r2_first) {
    GTEST_SKIP() << "insert() does not appear to track repeated refs for r2; cannot observe non-interference.";
  }

  {
    RefRecursionCheckerRemover remover(checker, r1);
  }

  // r1 should be removable/insertable again; r2 should remain in its previous (repeated) state.
  EXPECT_EQ(checker.insert(r1), r1_first);
  EXPECT_EQ(checker.insert(r2), r2_second);
}

TEST(RefRecursionCheckerRemoverTest_62, DestructorDoesNotThrow_62) {
  RefRecursionChecker checker;
  const Ref r = MakeRef(2, 0);

  // We only assert "no throw" here; it is an observable behavior for destructors in C++.
  EXPECT_NO_THROW({
    RefRecursionCheckerRemover remover(checker, r);
  });
}

TEST(RefRecursionCheckerRemoverTest_62, NestedRemoversSameRefAreSafeAndRestoreState_62) {
  RefRecursionChecker checker;
  const Ref r = MakeRef(3, 1);

  const bool firstInsert = checker.insert(r);
  const bool secondInsert = checker.insert(r);
  if (secondInsert == firstInsert) {
    GTEST_SKIP() << "insert() does not appear to track repeated refs; cannot observe restoration after nested removers.";
  }

  EXPECT_NO_THROW({
    {
      RefRecursionCheckerRemover remover1(checker, r);
      {
        RefRecursionCheckerRemover remover2(checker, r);
      }
    }
  });

  EXPECT_EQ(checker.insert(r), firstInsert);
}

TEST(RefRecursionCheckerRemoverTest_62, WorksWithBoundaryLikeRefs_62) {
  RefRecursionChecker checker;

  const Ref rZero = MakeRef(0, 0);
  const bool z1 = checker.insert(rZero);
  const bool z2 = checker.insert(rZero);
  if (z2 == z1) {
    GTEST_SKIP() << "insert() does not appear to track repeated refs; cannot observe removal for boundary refs.";
  }

  {
    RefRecursionCheckerRemover remover(checker, rZero);
  }
  EXPECT_EQ(checker.insert(rZero), z1);

  const Ref rNeg = MakeRef(-1, -1);
  const bool n1 = checker.insert(rNeg);
  const bool n2 = checker.insert(rNeg);
  if (n2 == n1) {
    GTEST_SKIP() << "insert() does not appear to track repeated refs for negative refs; cannot observe removal.";
  }

  {
    RefRecursionCheckerRemover remover(checker, rNeg);
  }
  EXPECT_EQ(checker.insert(rNeg), n1);
}