// File: prefilter_anychar_anybyte_test.cc

#include <gtest/gtest.h>
#include "re2/prefilter.h"      // Declares Prefilter and Prefilter::Info

namespace {

using re2::Prefilter;

// A small fixture in case future tests need shared setup/teardown.
class PrefilterAnyCharOrAnyByteTest_554 : public ::testing::Test {
 protected:
  // Helpers to ensure we don't leak in tests that call TakeMatch().
  static void SafeDeleteMatch(Prefilter* p) { delete p; }
};

// --- Tests ---

// [Normal operation] Factory should return a non-null Info instance.
TEST_F(PrefilterAnyCharOrAnyByteTest_554, FactoryReturnsNonNull_554) {
  Prefilter::Info* info = Prefilter::Info::AnyCharOrAnyByte();
  ASSERT_NE(info, nullptr);
  delete info;  // Info owns its internal state unless taken via TakeMatch()
}

// [Observable property] Newly-created Info from AnyCharOrAnyByte should not be "exact"
// according to the public is_exact() accessor.
TEST_F(PrefilterAnyCharOrAnyByteTest_554, IsNotExact_554) {
  Prefilter::Info* info = Prefilter::Info::AnyCharOrAnyByte();
  ASSERT_NE(info, nullptr);
  EXPECT_FALSE(info->is_exact());
  delete info;
}

// [Observable behavior] A match object should be obtainable via TakeMatch().
// We don't assume anything beyond non-null on the first call.
TEST_F(PrefilterAnyCharOrAnyByteTest_554, TakeMatchReturnsNonNullOnce_554) {
  Prefilter::Info* info = Prefilter::Info::AnyCharOrAnyByte();
  ASSERT_NE(info, nullptr);

  Prefilter* match = info->TakeMatch();
  // Must expose a Prefilter through the public API.
  EXPECT_NE(match, nullptr);

  // Clean up whichever side owns it post-TakeMatch:
  // If ownership was transferred, deleting 'match' is correct and Info won't double-delete.
  // If not transferred, Info will still own it and this pointer should be null in that design.
  // We only delete if non-null to avoid double-deletion.
  SafeDeleteMatch(match);

  delete info;
}

// [String representation] ToString() should provide some description for black-box verification.
// We only assert it returns a non-empty string; we don't depend on any specific wording.
TEST_F(PrefilterAnyCharOrAnyByteTest_554, ToStringIsNonEmpty_554) {
  Prefilter::Info* info = Prefilter::Info::AnyCharOrAnyByte();
  ASSERT_NE(info, nullptr);

  std::string s = info->ToString();
  EXPECT_FALSE(s.empty());

  delete info;
}

// [Boundary / independence] Multiple calls produce independent Info objects.
// We verify pointers differ (distinct instances) without asserting internal equality.
TEST_F(PrefilterAnyCharOrAnyByteTest_554, MultipleFactoriesYieldDistinctInstances_554) {
  Prefilter::Info* a = Prefilter::Info::AnyCharOrAnyByte();
  Prefilter::Info* b = Prefilter::Info::AnyCharOrAnyByte();
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_NE(a, b);

  delete a;
  delete b;
}

}  // namespace
