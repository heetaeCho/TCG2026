// =================================================================================================
// TestProjects/exiv2/src/canonmn_int.hpp - Unit Tests (TEST_ID = 928)
// =================================================================================================

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTest_928 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_928, TagListPreI_ReturnsNonNull_928) {
  // Observable behavior: callable and returns a usable handle/pointer-like object.
  const auto list = CanonMakerNote::tagListPreI();
  ASSERT_NE(list, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListPreI_RepeatedCallsReturnSameAddress_928) {
  // Observable behavior: stable identity across calls (typical for static tag tables).
  const auto a = CanonMakerNote::tagListPreI();
  const auto b = CanonMakerNote::tagListPreI();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_EQ(a, b);
}

TEST_F(CanonMakerNoteTest_928, TagListPreI_IsPointerLikeAndConstexprFriendly_928) {
  // Based only on the interface: return type properties + constexpr-usage.
  using Ret = decltype(CanonMakerNote::tagListPreI());
  static_assert(std::is_pointer_v<Ret>, "tagListPreI() is expected to return a pointer type.");

  // If the function is truly constexpr in the build, this will compile and be usable at compile time.
  constexpr Ret p = CanonMakerNote::tagListPreI();
  (void)p;

  // Also verify runtime consistency with the constexpr value.
  EXPECT_EQ(p, CanonMakerNote::tagListPreI());
}

}  // namespace