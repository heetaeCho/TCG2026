// SPDX-License-Identifier: GPL-2.0-or-later
// File: tiffvisitor_int_test_1671.cpp
//
// Tests for: Exiv2::Internal::TiffEncoder::visitSizeEntry(TiffSizeEntry*)
// Partial impl (black-box): visitSizeEntry forwards a TiffSizeEntry* to encodeTiffComponent(..)

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the public interfaces under test.
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace Exiv2::Internal {
namespace {

// NOTE:
// In the provided snippet, visitSizeEntry simply calls encodeTiffComponent(object).
// In the full codebase, constructing a real TiffEncoder instance requires many concrete
// collaborators (header/root tree/etc.) that are not provided here. To stay within the
// constraints (no inference / no re-implementation), these tests validate the *interface-
// level* and *compile-time observable* behavior: signature, callability, and return type.

class TiffEncoderVisitSizeEntryTest_1671 : public ::testing::Test {};

TEST_F(TiffEncoderVisitSizeEntryTest_1671, Signature_IsVoidAndTakesPointer_1671) {
  using Encoder = Exiv2::Internal::TiffEncoder;

  // Ensure the member exists with the expected signature:
  //   void (TiffEncoder::*)(TiffSizeEntry*)
  using ExpectedPtr = void (Encoder::*)(TiffSizeEntry*);
  static_assert(std::is_same_v<decltype(&Encoder::visitSizeEntry), ExpectedPtr>,
                "TiffEncoder::visitSizeEntry must have signature void(TiffSizeEntry*)");

  SUCCEED();
}

TEST_F(TiffEncoderVisitSizeEntryTest_1671, IsInvocableWithNullptrPointerType_1671) {
  using Encoder = Exiv2::Internal::TiffEncoder;

  // Validate that the method is invocable with a TiffSizeEntry* argument type.
  // (Unevaluated context: does not require constructing Encoder.)
  static_assert(std::is_invocable_v<decltype(&Encoder::visitSizeEntry), Encoder*, TiffSizeEntry*>,
                "visitSizeEntry should be invocable on Encoder* with (TiffSizeEntry*)");

  // Boundary-type check: nullptr is convertible to TiffSizeEntry*
  static_assert(std::is_convertible_v<std::nullptr_t, TiffSizeEntry*>,
                "nullptr must be convertible to TiffSizeEntry*");

  SUCCEED();
}

TEST_F(TiffEncoderVisitSizeEntryTest_1671, MemberPointerTypeIsWellFormed_1671) {
  using Encoder = Exiv2::Internal::TiffEncoder;

  // If the method is present and addressable, the pointer-to-member expression is well-formed.
  auto pmf = &Encoder::visitSizeEntry;
  (void)pmf;

  SUCCEED();
}

}  // namespace
}  // namespace Exiv2::Internal