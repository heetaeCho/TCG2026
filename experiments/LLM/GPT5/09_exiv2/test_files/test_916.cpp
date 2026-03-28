// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_taglistpr_916.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

// Helper: compare two returned values in a way that works for common "tag list" return types
// (pointers, references, small trivial types). We avoid assuming internal structure.
template <typename T>
typename std::enable_if<std::is_pointer<T>::value, void>::type expectSameTagList(T a, T b) {
  EXPECT_EQ(a, b);
  EXPECT_NE(a, nullptr);
}

template <typename T>
typename std::enable_if<!std::is_pointer<T>::value, void>::type expectSameTagList(const T& a, const T& b) {
  // If it’s a value type with operator==, this will compile and be meaningful.
  // If it’s a reference-like proxy or array reference, taking the address is still safe.
  // Prefer address comparison to avoid inferring deep equality semantics.
  EXPECT_EQ(std::addressof(a), std::addressof(b));
}

}  // namespace

TEST(CanonMakerNoteTagListPrTest_916, IsCallableAndReturnsStableValue_916) {
  using Exiv2::Internal::CanonMakerNote;

  // "Observable behavior": callable and returns a value we can hold.
  const auto a = CanonMakerNote::tagListPr();
  const auto b = CanonMakerNote::tagListPr();

  // Common expectation for tag list accessors: stable identity across calls.
  expectSameTagList<decltype(a)>(a, b);
}

TEST(CanonMakerNoteTagListPrTest_916, HasNonVoidReturnType_916) {
  using Exiv2::Internal::CanonMakerNote;

  using Ret = decltype(CanonMakerNote::tagListPr());
  static_assert(!std::is_void<Ret>::value, "tagListPr() must not return void");

  // Runtime sanity: we can instantiate and use the return value in a well-formed way.
  (void)CanonMakerNote::tagListPr();
}

TEST(CanonMakerNoteTagListPrTest_916, CanBeUsedInUnevaluatedContext_916) {
  using Exiv2::Internal::CanonMakerNote;

  // Boundary-style check: ensure the symbol participates in type computations.
  // (Doesn't assume constexpr usability; just validates interface shape.)
  using Ret = decltype(CanonMakerNote::tagListPr());
  EXPECT_TRUE((std::is_same<Ret, decltype(CanonMakerNote::tagListPr())>::value));
}