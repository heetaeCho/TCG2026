// File: optional_reset_tests_408.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_optional.hpp"

namespace {

// Helper type whose destructor has an observable effect.
struct DestructionTracker {
  static int dtor_count;
  int value;

  DestructionTracker(int v = 0) : value(v) {}
  DestructionTracker(const DestructionTracker&) = default;
  DestructionTracker(DestructionTracker&&) noexcept = default;
  DestructionTracker& operator=(const DestructionTracker&) = default;
  DestructionTracker& operator=(DestructionTracker&&) noexcept = default;

  ~DestructionTracker() { ++dtor_count; }

  // Provide a simple method to test operator-> passthrough *before* reset.
  int get() const { return value; }

  static void ResetCounter() { dtor_count = 0; }
};

int DestructionTracker::dtor_count = 0;

using Catch::Optional;

}  // namespace

// --- Normal operation: reset() on a disengaged Optional is a no-op.
TEST(OptionalResetTest_408, ResetOnEmptyIsNoOp_408) {
  DestructionTracker::ResetCounter();

  Optional<DestructionTracker> opt;  // default-constructed -> empty

  EXPECT_FALSE(static_cast<bool>(opt));
  EXPECT_TRUE(opt.none());
  EXPECT_FALSE(opt.some());

  opt.reset();  // should be safe and do nothing observable

  EXPECT_FALSE(static_cast<bool>(opt));
  EXPECT_TRUE(opt.none());
  EXPECT_EQ(DestructionTracker::dtor_count, 0);
}

// --- Normal operation: reset() on an engaged Optional disengages it
// and triggers contained object's destructor exactly once.
TEST(OptionalResetTest_408, ResetOnEngagedDestroysValueAndEmpties_408) {
  DestructionTracker::ResetCounter();

  DestructionTracker t{42};
  Optional<DestructionTracker> opt{t};  // engaged via lvalue

  ASSERT_TRUE(static_cast<bool>(opt));
  ASSERT_TRUE(opt.some());
  ASSERT_FALSE(opt.none());
  ASSERT_EQ(opt->get(), 42);  // observable via operator->

  opt.reset();

  EXPECT_FALSE(static_cast<bool>(opt));
  EXPECT_TRUE(opt.none());
  EXPECT_FALSE(opt.some());
  EXPECT_EQ(DestructionTracker::dtor_count, 1);  // destructor called once
}

// --- Boundary: Calling reset() twice should not double-destroy the value.
TEST(OptionalResetTest_408, DoubleResetDoesNotDoubleDestroy_408) {
  DestructionTracker::ResetCounter();

  Optional<DestructionTracker> opt{DestructionTracker{7}};  // engaged via rvalue
  ASSERT_TRUE(static_cast<bool>(opt));

  opt.reset();
  opt.reset();  // no additional destruction expected

  EXPECT_FALSE(static_cast<bool>(opt));
  EXPECT_EQ(DestructionTracker::dtor_count, 1);
}

// --- Post-condition behavior: After reset(), valueOr returns the provided default.
TEST(OptionalResetTest_408, ValueOrReturnsDefaultAfterReset_408) {
  DestructionTracker::ResetCounter();

  Optional<DestructionTracker> opt{DestructionTracker{100}};
  ASSERT_TRUE(static_cast<bool>(opt));

  opt.reset();

  DestructionTracker def{555};
  auto out = opt.valueOr(def);
  EXPECT_EQ(out.value, 555);
  // Only one destruction from the reset; returning by value from valueOr
  // should not destroy the (non-existent) contained object.
  EXPECT_EQ(DestructionTracker::dtor_count, 1);
}

// --- Smoke: reset() on an rvalue-constructed Optional also empties and destroys once.
TEST(OptionalResetTest_408, ResetAfterRvalueConstruction_408) {
  DestructionTracker::ResetCounter();

  Optional<DestructionTracker> opt{DestructionTracker{321}};
  ASSERT_TRUE(static_cast<bool>(opt));
  EXPECT_EQ(opt->get(), 321);

  opt.reset();
  EXPECT_FALSE(static_cast<bool>(opt));
  EXPECT_EQ(DestructionTracker::dtor_count, 1);
}
