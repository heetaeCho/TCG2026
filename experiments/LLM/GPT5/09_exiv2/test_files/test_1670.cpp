// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1670
//
// Unit tests for: Exiv2::Internal::TiffEncoder::visitImageEntry
// File under test (per prompt): ./TestProjects/exiv2/src/tiffvisitor_int.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "tiffvisitor_int.hpp"  // Exiv2::Internal::TiffEncoder

namespace {

// The prompt provides TiffImageEntry in a separate header snippet; in the real codebase this type
// should be declared/defined by the included Exiv2 internal headers transitively.
// We keep tests interface-based and avoid constructing instances (ctor is not provided in prompt).
using Exiv2::Internal::TiffEncoder;
using Exiv2::Internal::TiffImageEntry;

template <typename T>
struct has_visitImageEntry {
  template <typename U>
  static auto test(int)
      -> decltype(std::declval<U&>().visitImageEntry(static_cast<TiffImageEntry*>(nullptr)),
                  std::true_type{});
  template <typename>
  static std::false_type test(...);

  static constexpr bool value = decltype(test<T>(0))::value;
};

}  // namespace

// Normal operation: the member function exists and is callable with TiffImageEntry*.
TEST(TiffEncoderVisitImageEntryTest_1670, IsCallableWithTiffImageEntryPtr_1670) {
  static_assert(has_visitImageEntry<TiffEncoder>::value,
                "TiffEncoder must provide visitImageEntry(TiffImageEntry*)");

  // Also verify the pointer-to-member type is well-formed (compile-time interface check).
  using PMF = void (TiffEncoder::*)(TiffImageEntry*);
  PMF pmf = &TiffEncoder::visitImageEntry;
  (void)pmf;

  SUCCEED();
}

// Boundary condition: nullptr is a valid value for a pointer parameter at the call site.
// This test is intentionally compile-time only (does NOT invoke the method) because the prompt
// does not provide a safe way to construct a TiffEncoder instance nor specify nullptr behavior.
TEST(TiffEncoderVisitImageEntryTest_1670, AcceptsNullptrAtCallSite_1670) {
  // If the signature changes to a reference or otherwise forbids nullptr, this will fail to compile.
  using Param = TiffImageEntry*;
  static_assert(std::is_pointer<Param>::value, "Parameter must be a pointer type");

  // Demonstrate the call expression is well-formed in an unevaluated context.
  static_assert(
      std::is_same<decltype(std::declval<TiffEncoder&>().visitImageEntry(
                                static_cast<TiffImageEntry*>(nullptr))),
                   void>::value,
      "visitImageEntry must return void");

  SUCCEED();
}

// Exceptional/error cases (interface-observable): none are specified in the prompt for this method.
// We at least assert that the return type is void (no error code channel via return value).
TEST(TiffEncoderVisitImageEntryTest_1670, ReturnTypeIsVoid_1670) {
  static_assert(std::is_same<decltype(&TiffEncoder::visitImageEntry),
                             void (TiffEncoder::*)(TiffImageEntry*)>::value,
                "visitImageEntry must be: void (TiffEncoder::*)(TiffImageEntry*)");
  SUCCEED();
}