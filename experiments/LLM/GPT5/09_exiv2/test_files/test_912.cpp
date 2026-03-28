// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

template <typename T>
const void* identityAddress(T&& v) {
  using U = std::remove_reference_t<T>;
  if constexpr (std::is_pointer_v<U>) {
    // If the API returns a pointer, the pointer value itself identifies the target.
    return static_cast<const void*>(v);
  } else {
    // If the API returns a reference/value to some object/array, use its address.
    return static_cast<const void*>(std::addressof(v));
  }
}

template <typename T>
void expectNotNullIfPointer(T&& v) {
  using U = std::remove_reference_t<T>;
  if constexpr (std::is_pointer_v<U>) {
    EXPECT_NE(v, nullptr);
  } else {
    SUCCEED();  // Non-pointer return types are inherently "present".
  }
}

class CanonMakerNoteTagListCfTest_912 : public ::testing::Test {};

}  // namespace

TEST_F(CanonMakerNoteTagListCfTest_912, CallableWithoutInstance_912) {
  // Verifies the static API is callable (no instance required) and returns something usable.
  const auto& list = CanonMakerNote::tagListCf();
  (void)list;
  SUCCEED();
}

TEST_F(CanonMakerNoteTagListCfTest_912, ReturnsStableIdentityAcrossCalls_912) {
  // Observable behavior: repeated calls should refer to the same underlying list object/pointer.
  const auto& a = CanonMakerNote::tagListCf();
  const auto& b = CanonMakerNote::tagListCf();

  EXPECT_EQ(identityAddress(a), identityAddress(b));
}

TEST_F(CanonMakerNoteTagListCfTest_912, ReturnIsNonNullWhenPointer_912) {
  // Boundary-style check: if the API returns a pointer, it should not be null.
  const auto& list = CanonMakerNote::tagListCf();
  expectNotNullIfPointer(list);
}

TEST_F(CanonMakerNoteTagListCfTest_912, ReturnTypeIsConsistent_912) {
  // Compile-time observable property: the function's return type should be stable.
  using R1 = decltype(CanonMakerNote::tagListCf());
  using R2 = decltype(CanonMakerNote::tagListCf());
  static_assert(std::is_same_v<R1, R2>, "tagListCf() return type must be consistent");

  SUCCEED();
}