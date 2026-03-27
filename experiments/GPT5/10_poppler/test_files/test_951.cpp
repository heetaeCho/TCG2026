// SPDX-License-Identifier: GPL-2.0-or-later
// File: PDFDoc_getCatalog_test_951.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the interface under test.
#include "PDFDoc.h"

namespace {

TEST(PDFDocTest_951, GetCatalogHasExpectedSignature_951) {
  // Verify: PDFDoc::getCatalog() is callable on a const PDFDoc and returns Catalog*.
  using ReturnT = decltype(std::declval<const PDFDoc&>().getCatalog());

  static_assert(std::is_same_v<ReturnT, Catalog*>,
                "PDFDoc::getCatalog() must return Catalog*");

  // Also verify: the member function pointer type matches exactly.
  using MemFnT = Catalog* (PDFDoc::*)() const;
  static_assert(std::is_same_v<decltype(&PDFDoc::getCatalog), MemFnT>,
                "PDFDoc::getCatalog() must have signature Catalog* () const");

  SUCCEED();
}

TEST(PDFDocTest_951, GetCatalogReturnIsPointerType_951) {
  // Boundary-ish check: ensure the return type is a raw pointer (not ref/value/smart ptr).
  using ReturnT = decltype(std::declval<const PDFDoc&>().getCatalog());
  static_assert(std::is_pointer_v<ReturnT>, "getCatalog() must return a pointer type");
  static_assert(std::is_same_v<std::remove_pointer_t<ReturnT>, Catalog>,
                "getCatalog() must return a pointer to Catalog");

  SUCCEED();
}

}  // namespace