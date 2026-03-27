// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 932
//
// File: ./TestProjects/exiv2/src/canonmn_int_test_932.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

// SFINAE helper: returns (a == b) if supported, otherwise returns true (we only
// want to verify the interface is callable without assuming comparability).
template <typename T>
auto AreEqualIfSupported(const T& a, const T& b, int) -> decltype(a == b, bool()) {
  return a == b;
}
template <typename T>
bool AreEqualIfSupported(const T&, const T&, long) {
  return true;
}

// SFINAE helper: checks (v != nullptr) if pointer-like, otherwise returns true.
template <typename T>
auto IsNonNullIfPointer(const T& v, int) -> decltype(v != nullptr, bool()) {
  return v != nullptr;
}
template <typename T>
bool IsNonNullIfPointer(const T&, long) {
  return true;
}

class CanonMakerNoteTagListVigCor2Test_932 : public ::testing::Test {};

}  // namespace

TEST_F(CanonMakerNoteTagListVigCor2Test_932, IsCallable_932) {
  // Normal operation: the API is callable and yields a value.
  auto v = Exiv2::Internal::CanonMakerNote::tagListVigCor2();
  (void)v;
  SUCCEED();
}

TEST_F(CanonMakerNoteTagListVigCor2Test_932, MultipleCallsAreConsistent_932) {
  // Boundary-ish: repeated calls should be usable and (if equality is defined)
  // should compare equal. We do not assume the returned type is comparable.
  auto v1 = Exiv2::Internal::CanonMakerNote::tagListVigCor2();
  auto v2 = Exiv2::Internal::CanonMakerNote::tagListVigCor2();

  EXPECT_TRUE(AreEqualIfSupported(v1, v2, 0));
}

TEST_F(CanonMakerNoteTagListVigCor2Test_932, ReturnedValueIsNonNullIfPointer_932) {
  // Error/boundary-ish: if the return type is a pointer, it should not be null.
  // If it's not a pointer (or not comparable to nullptr), we just verify the call.
  auto v = Exiv2::Internal::CanonMakerNote::tagListVigCor2();
  EXPECT_TRUE(IsNonNullIfPointer(v, 0));
}

TEST_F(CanonMakerNoteTagListVigCor2Test_932, ReturnTypeIsStableAcrossUses_932) {
  // Compile-time observable property: the return type should be stable.
  using R1 = decltype(Exiv2::Internal::CanonMakerNote::tagListVigCor2());
  using R2 = decltype(Exiv2::Internal::CanonMakerNote::tagListVigCor2());
  EXPECT_TRUE((std::is_same<R1, R2>::value));
}