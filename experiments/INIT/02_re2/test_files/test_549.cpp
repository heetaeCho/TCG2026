// File: prefilter_info_plus_test_549.cc

#include <gtest/gtest.h>
#include <memory>

// Assuming the library exposes this header. Adjust include as needed for your tree.
#include "re2/prefilter.h"

using re2::Prefilter;

namespace {

// Simple deleter to manage raw Info* returned by factory functions.
struct InfoDeleter {
  void operator()(Prefilter::Info* p) const { delete p; }
};
using InfoPtr = std::unique_ptr<Prefilter::Info, InfoDeleter>;

// --- Tests ---

// [Normal operation] Plus on a reasonable, valid operand returns a non-null Info
// and the result is not exact per the public is_exact() accessor.
TEST(PrefilterInfoPlusTest_549, PlusOnAnyMatch_NotExact_549) {
  InfoPtr a(Prefilter::Info::AnyMatch());
  ASSERT_NE(a.get(), nullptr) << "Factory should return a valid Info";

  InfoPtr result(Prefilter::Info::Plus(a.release()));
  ASSERT_NE(result.get(), nullptr) << "Plus should produce a valid Info";
  EXPECT_FALSE(result->is_exact()) << "Plus(*) should not be exact per interface";
}

// [Boundary condition] Plus on an Info representing empty string should still
// yield a non-exact result (observable via is_exact()).
TEST(PrefilterInfoPlusTest_549, PlusOnEmptyString_NotExact_549) {
  InfoPtr a(Prefilter::Info::EmptyString());
  ASSERT_NE(a.get(), nullptr) << "Factory should return a valid Info";

  InfoPtr result(Prefilter::Info::Plus(a.release()));
  ASSERT_NE(result.get(), nullptr);
  EXPECT_FALSE(result->is_exact());
}

// [Exceptional/error case] Passing nullptr is invalid; verify the program
// dies (or at least triggers a death test) when Plus is invoked with nullptr.
// We do not assert the exact message to avoid depending on implementation details.
#if GTEST_HAS_DEATH_TEST
TEST(PrefilterInfoPlusTest_549, PlusWithNullptr_Death_549) {
  EXPECT_DEATH(
      {
        Prefilter::Info* res = Prefilter::Info::Plus(nullptr);
        // If it somehow returns, avoid leak.
        delete res;
      },
      ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
