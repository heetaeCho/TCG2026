// File: test_canonmn_int_taglisthdr_938.cpp
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListHdr()
// TEST_ID: 938

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTest_938 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_938, TagListHdr_IsCallableAtRuntime_938) {
  // Basic observable behavior: function is callable and returns a value.
  // We don't assume anything about the contents of the returned tag list.
  const auto v = CanonMakerNote::tagListHdr();
  (void)v;  // Ensure it compiles and can be evaluated at runtime.
  SUCCEED();
}

TEST_F(CanonMakerNoteTest_938, TagListHdr_ReturnValueIsStableAcrossCalls_938) {
  const auto v1 = CanonMakerNote::tagListHdr();
  const auto v2 = CanonMakerNote::tagListHdr();

  // For tag list accessors in Exiv2, the return is expected to be a stable
  // reference/pointer-like handle to static data. We only assert stability.
  EXPECT_EQ(v1, v2);
}

TEST_F(CanonMakerNoteTest_938, TagListHdr_ReturnTypeIsPointerOrReferenceLike_938) {
  using Ret = decltype(CanonMakerNote::tagListHdr());

  // Without inferring internal implementation, we can still sanity-check that
  // the accessor returns something addressable (pointer or reference).
  const bool is_ptr = std::is_pointer<Ret>::value;
  const bool is_ref = std::is_reference<Ret>::value;

  EXPECT_TRUE(is_ptr || is_ref);
}

TEST_F(CanonMakerNoteTest_938, TagListHdr_IsUsableInConstantExpression_938) {
  // The interface declares this as constexpr; verify it can be used in a
  // constant-evaluated context without relying on internal details.
  constexpr auto c1 = CanonMakerNote::tagListHdr();
  constexpr auto c2 = CanonMakerNote::tagListHdr();

  // Compile-time stability check.
  static_assert(c1 == c2, "tagListHdr() should yield a stable value in constexpr context.");

  // Also ensure runtime uses the same value as constexpr (observable equality).
  EXPECT_EQ(CanonMakerNote::tagListHdr(), c1);
}

}  // namespace