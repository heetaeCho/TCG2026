// File: walker_test_592.cc
#include <type_traits>
#include "gtest/gtest.h"

#include "TestProjects/re2/re2/walker-inl.h"

namespace {

using WalkerInt = re2::Regexp::Walker<int>;

class WalkerTest_592 : public ::testing::Test {};

TEST_F(WalkerTest_592, DefaultConstruction_StoppedEarlyIsFalse_592) {
  WalkerInt w;
  // Observable behavior via public accessor.
  EXPECT_FALSE(w.stopped_early());
}

// These compile-time checks validate interface constraints (deleted copy ops).
TEST_F(WalkerTest_592, NotCopyConstructibleOrCopyAssignable_592) {
  static_assert(!std::is_copy_constructible<WalkerInt>::value,
                "Walker should not be copy-constructible");
  static_assert(!std::is_copy_assignable<WalkerInt>::value,
                "Walker should not be copy-assignable");
  SUCCEED();  // Keeps the test from being empty at runtime.
}

}  // namespace
