// File: walker_reset_test_215.cc
#include "gtest/gtest.h"

// Include the header under test.
// Adjust the relative path if your build layout differs.
#include "TestProjects/re2/re2/walker-inl.h"

namespace re2 {
namespace {

using ::testing::Test;

// Simple compile-time sanity: we can instantiate the template with a basic type.
class WalkerResetTest_215 : public Test {};

// [Normal] Reset on a freshly constructed walker should be a no-op (no crash, no throw).
TEST_F(WalkerResetTest_215, ResetOnFreshWalker_NoCrash_215) {
  Regexp::Walker<int> walker;
  // Expect: calling Reset() is safe and returns void.
  walker.Reset();
  SUCCEED();  // If we got here, behavior is as expected (no observable errors).
}

// [Boundary] Calling Reset() multiple times should remain safe (idempotent from the interface POV).
TEST_F(WalkerResetTest_215, ResetIsIdempotent_215) {
  Regexp::Walker<int> walker;
  walker.Reset();
  walker.Reset();  // Repeated call should not cause failures.
  SUCCEED();
}

}  // namespace
}  // namespace re2
