// File: test_canonmn_int_taglistvigcor_931.cpp
// Unit tests for: Exiv2::Internal::CanonMakerNote::tagListVigCor()
// TEST_ID: 931

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

// Helper to normalize various "tag list" return forms into a raw pointer for comparison.
// Works for common Exiv2 patterns: returning `const T*` or returning `const T (&)[N]`.
template <typename T>
const void* AsVoidPtr(T* p) {
  return static_cast<const void*>(p);
}

template <typename T, std::size_t N>
const void* AsVoidPtr(const T (&arr)[N]) {
  return static_cast<const void*>(arr);
}

}  // namespace

TEST(CanonMakerNoteTest_931, TagListVigCor_ReturnsSameAddressAcrossCalls_931) {
  const auto a = CanonMakerNote::tagListVigCor();
  const auto b = CanonMakerNote::tagListVigCor();

  const void* pa = AsVoidPtr(a);
  const void* pb = AsVoidPtr(b);

  EXPECT_EQ(pa, pb);
}

TEST(CanonMakerNoteTest_931, TagListVigCor_ReturnValueIsNotNullPointer_931) {
  const auto v = CanonMakerNote::tagListVigCor();
  const void* pv = AsVoidPtr(v);

  // If the API returns a pointer/array base address, it should be usable and stable.
  EXPECT_NE(pv, nullptr);
}

TEST(CanonMakerNoteTest_931, TagListVigCor_UsableInConstantExpressionContext_931) {
  // The interface says `static constexpr auto tagListVigCor()`.
  // This checks that it can be used in a constant-evaluated context without inspecting internals.
  constexpr auto v = CanonMakerNote::tagListVigCor();

  // If v is a pointer or array reference, taking AsVoidPtr at runtime is fine;
  // the key check here is that the constexpr declaration compiles and links.
  (void)v;
  SUCCEED();
}