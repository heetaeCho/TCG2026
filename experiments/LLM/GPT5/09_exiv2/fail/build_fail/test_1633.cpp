// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tiff_finder_visit_image_entry_1633.cpp

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"  // Exiv2::Internal::TiffFinder, TiffVisitor
#include "tiffcomposite_int.hpp" // Exiv2::Internal::TiffImageEntry (type)

namespace {

using Exiv2::Internal::TiffFinder;
using Exiv2::Internal::TiffImageEntry;

class TiffFinderVisitImageEntryTest_1633 : public ::testing::Test {
 protected:
  static constexpr uint16_t kTag = 0; // Do not assume tag semantics; any value is fine for construction.
  static constexpr auto kGroup = static_cast<Exiv2::Internal::IfdId>(0);

  TiffFinder makeFinder() const {
    // The interface provides a constexpr constructor (tag, group).
    return TiffFinder(kTag, kGroup);
  }
};

TEST_F(TiffFinderVisitImageEntryTest_1633, NullptrDoesNotThrow_1633) {
  auto finder = makeFinder();
  EXPECT_NO_THROW(finder.visitImageEntry(static_cast<TiffImageEntry*>(nullptr)));
}

TEST_F(TiffFinderVisitImageEntryTest_1633, NullptrMatchesFindObjectObservableResult_1633) {
  // Black-box equivalence test:
  // visitImageEntry(object) is documented/implemented as a forwarding call to findObject(object).
  // We do NOT assume what "finding" means; we only compare observable state via result().
  auto finder1 = makeFinder();
  finder1.init(kTag, kGroup);
  finder1.findObject(nullptr);
  auto r1 = finder1.result();

  auto finder2 = makeFinder();
  finder2.init(kTag, kGroup);
  finder2.visitImageEntry(nullptr);
  auto r2 = finder2.result();

  EXPECT_EQ(r1, r2);
}

TEST_F(TiffFinderVisitImageEntryTest_1633, MultipleNullptrCallsStayEquivalentToFindObject_1633) {
  auto finder1 = makeFinder();
  finder1.init(kTag, kGroup);
  finder1.findObject(nullptr);
  finder1.findObject(nullptr);
  auto r1 = finder1.result();

  auto finder2 = makeFinder();
  finder2.init(kTag, kGroup);
  finder2.visitImageEntry(nullptr);
  finder2.visitImageEntry(nullptr);
  auto r2 = finder2.result();

  EXPECT_EQ(r1, r2);
}

}  // namespace