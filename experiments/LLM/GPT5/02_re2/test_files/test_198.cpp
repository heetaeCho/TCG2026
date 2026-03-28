// File: ./TestProjects/re2/util/pcre_clear_hit_limit_test.cc

#include <gtest/gtest.h>
#include <new>          // std::aligned_storage
#include <type_traits>  // std::aligned_storage, alignof
#include "re2/util/pcre.h"

namespace {

using re2::PCRE;

// Test fixture kept minimal; we only need the type to exist.
class PCRE_ClearHitLimitTest_198 : public ::testing::Test {};

// [TEST_ID = 198]
// Verifies that ClearHitLimit can be invoked on a PCRE instance without
// requiring a working constructor (none provided in the snippet) and
// that the call does not crash or throw.
TEST_F(PCRE_ClearHitLimitTest_198, ClearHitLimit_DoesNotCrash_198) {
  // Allocate storage with correct size/alignment without invoking any constructor.
  typename std::aligned_storage<sizeof(PCRE), alignof(PCRE)>::type storage;
  auto* p = reinterpret_cast<PCRE*>(&storage);

  // Act & Assert: Just ensure the call is well-formed and does not crash/throw.
  // We avoid ASSERT_NO_THROW since the function is 'noexcept' by default in C++,
  // and exceptions are not expected; SUCCEED confirms the call completed.
  p->ClearHitLimit();
  SUCCEED() << "PCRE::ClearHitLimit() completed without crashing.";
}

// [TEST_ID = 198]
// Idempotence/safety: calling ClearHitLimit multiple times should remain safe.
// We do not assert internal state—only that repeated invocation is stable.
TEST_F(PCRE_ClearHitLimitTest_198, ClearHitLimit_MultipleCallsSafe_198) {
  typename std::aligned_storage<sizeof(PCRE), alignof(PCRE)>::type storage;
  auto* p = reinterpret_cast<PCRE*>(&storage);

  // Call ClearHitLimit multiple times; expect no crash/throw each time.
  p->ClearHitLimit();
  p->ClearHitLimit();
  p->ClearHitLimit();

  SUCCEED() << "Multiple calls to PCRE::ClearHitLimit() were safe.";
}

}  // namespace
