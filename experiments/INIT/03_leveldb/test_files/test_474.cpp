// condvar_constructor_test_474.cc
#include <gtest/gtest.h>
#include <type_traits>
#include "port/port_stdcxx.h"

namespace lp = leveldb::port;

class CondVarTest_474 : public ::testing::Test {};

// [474] Normal case: constructing with a non-null Mutex* should succeed.
TEST_F(CondVarTest_474, ConstructWithValidMutex_DoesNotCrash_474) {
  lp::Mutex mu;
  // Construction should not throw or crash.
  // We don't call Wait/Signal/SignalAll to avoid relying on unspecified semantics.
  EXPECT_NO_THROW({
    lp::CondVar cv(&mu);
    (void)cv;  // silence unused warning
  });
}

// [474] Error case: constructing with nullptr should trigger the assert in debug builds.
// In release builds (NDEBUG), assert is disabled, so we skip the death test.
TEST_F(CondVarTest_474, ConstructorNullptr_TriggersAssertInDebug_474) {
#ifndef NDEBUG
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  EXPECT_DEATH(
      {
        // The constructor asserts mu != nullptr.
        lp::CondVar cv(nullptr);
        (void)cv;
      },
      "");  // Accept any assert message.
#else
  GTEST_SKIP() << "Assertions are disabled in release builds (NDEBUG defined).";
#endif
}

// [474] Interface traits: CondVar is non-copyable and non-assignable per the provided interface.
TEST_F(CondVarTest_474, NonCopyableAndNonAssignable_474) {
  static_assert(!std::is_copy_constructible<lp::CondVar>::value,
                "CondVar must be non-copy-constructible");
  static_assert(!std::is_copy_assignable<lp::CondVar>::value,
                "CondVar must be non-copy-assignable");
  // Also verify it isn't move-constructible/assignable given the interface & members.
  static_assert(!std::is_move_constructible<lp::CondVar>::value,
                "CondVar should not be move-constructible");
  static_assert(!std::is_move_assignable<lp::CondVar>::value,
                "CondVar should not be move-assignable");
  SUCCEED();
}
