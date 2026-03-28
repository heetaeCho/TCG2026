// RefTest_56.cpp
// Unit tests for poppler::Ref (partial interface)
//
// Constraints reminder (applied):
// - Treat implementation as black box: only test observable behavior via public interface.
// - Do not access private/internal state (none here).
// - No re-implementation of logic beyond what the interface guarantees.

#include <gtest/gtest.h>

// Include the real header from the codebase.
#include "./TestProjects/poppler/poppler/Object.h"

namespace {

// Simple helper to avoid repeating field checks in every test.
static void ExpectRefEq(const Ref& r, int num, int gen) {
  EXPECT_EQ(r.num, num);
  EXPECT_EQ(r.gen, gen);
}

class RefTest_56 : public ::testing::Test {};

TEST_F(RefTest_56, InvalidReturnsMinusOneMinusOne_56) {
  const Ref invalid = Ref::INVALID();
  ExpectRefEq(invalid, -1, -1);
}

TEST_F(RefTest_56, InvalidIsConstexprUsable_56) {
  // If INVALID() is truly constexpr, this should compile and work.
  // (We still also assert runtime values for clarity.)
  constexpr Ref invalid = Ref::INVALID();
  static_assert(invalid.num == -1, "Ref::INVALID().num must be -1");
  static_assert(invalid.gen == -1, "Ref::INVALID().gen must be -1");

  ExpectRefEq(invalid, -1, -1);
}

TEST_F(RefTest_56, InvalidIsDeterministicAcrossCalls_56) {
  const Ref a = Ref::INVALID();
  const Ref b = Ref::INVALID();

  // Boundary-ish / stability check: repeated calls should yield same observable values.
  ExpectRefEq(a, -1, -1);
  ExpectRefEq(b, -1, -1);
}

TEST_F(RefTest_56, InvalidDoesNotAliasBetweenInstances_56) {
  // Ensure separate objects can be independently modified without affecting others.
  Ref a = Ref::INVALID();
  Ref b = Ref::INVALID();

  a.num = 123;
  a.gen = 456;

  // b should remain as returned by INVALID(), since it's a distinct value object.
  ExpectRefEq(b, -1, -1);
  ExpectRefEq(a, 123, 456);
}

TEST_F(RefTest_56, RefIsAggregateInitializableAndFieldsArePublic_56) {
  // Boundary / basic sanity: Ref can be created and fields are writable.
  Ref r{.num = 0, .gen = 0};
  ExpectRefEq(r, 0, 0);

  r.num = 7;
  r.gen = 9;
  ExpectRefEq(r, 7, 9);
}

}  // namespace