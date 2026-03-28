// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for ./TestProjects/exiv2/src/canonmn_int.hpp
//
// The TEST_ID is 913

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

// Helper to avoid making assumptions about the exact return type.
// We only check properties that are observable through the interface.
template <typename T>
constexpr bool is_pointer_v = std::is_pointer<T>::value;

}  // namespace

namespace Exiv2 {
namespace Internal {

class CanonMakerNoteTest_913 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_913, TagListPi_IsCallable_913) {
  // Smoke test: the function exists and is callable.
  auto ret = CanonMakerNote::tagListPi();
  (void)ret;
  SUCCEED();
}

TEST_F(CanonMakerNoteTest_913, TagListPi_ReturnTypeIsStableAcrossCalls_913) {
  // Observable behavior: repeated calls should produce a value of the same type,
  // and the returned value should be comparable for equality when the type allows it.
  auto a = CanonMakerNote::tagListPi();
  auto b = CanonMakerNote::tagListPi();

  // If the returned type is a pointer, it should typically be stable and non-null.
  using Ret = decltype(a);
  if constexpr (is_pointer_v<Ret>) {
    EXPECT_NE(a, nullptr);
    EXPECT_NE(b, nullptr);
    EXPECT_EQ(a, b);
  } else {
    // For non-pointer return types (e.g., references/arrays), we avoid assuming
    // comparability or sentinel layout. Just ensure both expressions are well-formed.
    (void)a;
    (void)b;
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTest_913, TagListPi_CanBeUsedInConstexprContextIfSupported_913) {
  // The interface declares tagListPi() as constexpr. We validate that it can be
  // odr-used in a constexpr context *when the return type permits it*.
  //
  // If the return type is not a literal type, this may not be possible; in that case
  // we still validate runtime callability (covered by other tests).
  using Ret = decltype(CanonMakerNote::tagListPi());

  if constexpr (std::is_literal_type<Ret>::value) {
    constexpr Ret v = CanonMakerNote::tagListPi();
    (void)v;
    SUCCEED();
  } else {
    // Not a literal type: cannot enforce constexpr initialization without
    // making assumptions about implementation/types. Still ok.
    auto v = CanonMakerNote::tagListPi();
    (void)v;
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTest_913, TagListPi_AddressCanBeTaken_913) {
  // Boundary/ABI-style check: taking the function pointer is well-formed.
  // (No assumptions about internal contents.)
  auto fn = &CanonMakerNote::tagListPi;
  (void)fn;
  SUCCEED();
}

}  // namespace Internal
}  // namespace Exiv2