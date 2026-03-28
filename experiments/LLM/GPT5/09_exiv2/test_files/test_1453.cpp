// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_fuji_mn_header_1453.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include <cstddef>
#include <type_traits>
#include <utility>

namespace {

using Exiv2::Internal::FujiMnHeader;

// Detect non-static member: size_t (T::*)()
template <typename T, typename = void>
struct has_nonstatic_sos : std::false_type {};
template <typename T>
struct has_nonstatic_sos<T, std::void_t<decltype(static_cast<size_t (T::*)()>(&T::sizeOfSignature))>>
    : std::true_type {};

// Detect const non-static member: size_t (T::*)() const
template <typename T, typename = void>
struct has_const_nonstatic_sos : std::false_type {};
template <typename T>
struct has_const_nonstatic_sos<
    T, std::void_t<decltype(static_cast<size_t (T::*)() const>(&T::sizeOfSignature))>> : std::true_type {};

// Detect static: size_t (*)()
template <typename T, typename = void>
struct has_static_sos : std::false_type {};
template <typename T>
struct has_static_sos<T, std::void_t<decltype(static_cast<size_t (*)()>(&T::sizeOfSignature))>> : std::true_type {};

template <typename T>
size_t CallSizeOfSignatureNonStatic(T& obj) {
  if constexpr (has_nonstatic_sos<T>::value) {
    auto pmf = static_cast<size_t (T::*)()>(&T::sizeOfSignature);
    return (obj.*pmf)();
  } else if constexpr (has_const_nonstatic_sos<T>::value) {
    auto pmf = static_cast<size_t (T::*)() const>(&T::sizeOfSignature);
    return (obj.*pmf)();
  } else {
    return 0;
  }
}

template <typename T>
size_t CallSizeOfSignatureStatic() {
  if constexpr (has_static_sos<T>::value) {
    auto pf = static_cast<size_t (*)()>(&T::sizeOfSignature);
    return (*pf)();
  } else {
    return 0;
  }
}

class FujiMnHeaderTest_1453 : public ::testing::Test {
 protected:
  FujiMnHeader header_;
};

TEST_F(FujiMnHeaderTest_1453, SizeOfSignature_ReturnsNonZero_1453) {
  const size_t via_member = CallSizeOfSignatureNonStatic(header_);
  const size_t via_static = CallSizeOfSignatureStatic<FujiMnHeader>();

  // At least one of the two forms should be available and return a non-zero size.
  if (via_member != 0) {
    EXPECT_GT(via_member, 0u);
  }
  if (via_static != 0) {
    EXPECT_GT(via_static, 0u);
  }

  EXPECT_TRUE(via_member != 0 || via_static != 0);
}

TEST_F(FujiMnHeaderTest_1453, SizeOfSignature_IsStableAcrossCalls_1453) {
  // Whichever call form is available, it should be stable across multiple invocations.
  const size_t via_member_1 = CallSizeOfSignatureNonStatic(header_);
  const size_t via_member_2 = CallSizeOfSignatureNonStatic(header_);

  if (via_member_1 != 0 || via_member_2 != 0) {
    EXPECT_EQ(via_member_1, via_member_2);
    EXPECT_GT(via_member_1, 0u);
  }

  const size_t via_static_1 = CallSizeOfSignatureStatic<FujiMnHeader>();
  const size_t via_static_2 = CallSizeOfSignatureStatic<FujiMnHeader>();

  if (via_static_1 != 0 || via_static_2 != 0) {
    EXPECT_EQ(via_static_1, via_static_2);
    EXPECT_GT(via_static_1, 0u);
  }

  // If only one form exists, at least ensure that form returned something valid.
  EXPECT_TRUE((via_member_1 != 0) || (via_static_1 != 0));
}

TEST_F(FujiMnHeaderTest_1453, SizeOfSignature_StaticAndMemberMatch_WhenBothExist_1453) {
  const size_t via_member = CallSizeOfSignatureNonStatic(header_);
  const size_t via_static = CallSizeOfSignatureStatic<FujiMnHeader>();

  // Only compare when both are present (non-zero sentinel means "callable" here).
  if (via_member != 0 && via_static != 0) {
    EXPECT_EQ(via_member, via_static);
  } else {
    // Otherwise, still validate the available one.
    EXPECT_TRUE(via_member != 0 || via_static != 0);
  }
}

}  // namespace