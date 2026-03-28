// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for ./TestProjects/exiv2/src/canonmn_int.hpp
//
// Focus: Exiv2::Internal::CanonMakerNote::tagListAm()
//
// Constraints honored:
// - Black-box: only observable behavior via public interface.
// - No reliance on private/internal state content.
// - Boundary/error cases: nullability (if pointer), stability across calls, constexpr usability.

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTagListAmTest_935 : public ::testing::Test {};

template <typename T>
constexpr bool IsPointerNull(T v) {
  if constexpr (std::is_pointer_v<T>) {
    return v == nullptr;
  } else {
    (void)v;
    return false;
  }
}

template <typename T>
std::uintptr_t StableIdentity(T&& v) {
  using U = std::remove_reference_t<T>;
  if constexpr (std::is_pointer_v<U>) {
    // If tagListAm() returns a pointer, compare the pointer value.
    return reinterpret_cast<std::uintptr_t>(v);
  } else {
    // If tagListAm() returns a reference (e.g., to an array), compare the address of the referred object.
    return reinterpret_cast<std::uintptr_t>(std::addressof(v));
  }
}

TEST_F(CanonMakerNoteTagListAmTest_935, ReturnsStableIdentityAcrossCalls_935) {
  auto v1 = CanonMakerNote::tagListAm();
  auto v2 = CanonMakerNote::tagListAm();

  const auto id1 = StableIdentity(v1);
  const auto id2 = StableIdentity(v2);

  EXPECT_EQ(id1, id2);
}

TEST_F(CanonMakerNoteTagListAmTest_935, NotNullWhenPointerReturnType_935) {
  const auto v = CanonMakerNote::tagListAm();
  // Only enforce non-null if the return type is actually a pointer.
  if constexpr (std::is_pointer_v<decltype(v)>) {
    EXPECT_NE(v, nullptr);
  } else {
    SUCCEED();  // Non-pointer types are not meaningfully "null".
  }
}

TEST_F(CanonMakerNoteTagListAmTest_935, UsableInConstexprContext_935) {
  // This will fail to compile if tagListAm() is not usable in a constant expression context.
  constexpr auto v = CanonMakerNote::tagListAm();

  // If it is a pointer, additionally ensure it's not nullptr at compile time.
  if constexpr (std::is_pointer_v<decltype(v)>) {
    static_assert(v != nullptr, "CanonMakerNote::tagListAm() returned nullptr in constexpr context.");
  }

  SUCCEED();
}

TEST_F(CanonMakerNoteTagListAmTest_935, CallableFromConstAndNonConstContexts_935) {
  // Boundary-ish: ensure the static function is callable without needing any object state.
  const auto a = CanonMakerNote::tagListAm();
  const auto b = CanonMakerNote::tagListAm();

  EXPECT_EQ(StableIdentity(a), StableIdentity(b));
}

}  // namespace