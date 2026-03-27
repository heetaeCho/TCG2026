// File: test_tiffvisitor_int_tifffinder_visitentry_1631.cpp
// Unit tests for Exiv2::Internal::TiffFinder::visitEntry (delegation behavior)

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"  // Exiv2::Internal::TiffFinder

namespace {

using Exiv2::Internal::IfdId;
using Exiv2::Internal::TiffFinder;
using Exiv2::Internal::TiffComponent;
using Exiv2::Internal::TiffEntry;

class TiffFinderTest_1631 : public ::testing::Test {
 protected:
  // Helper that runs a sequence and returns the observable result() pointer.
  static TiffComponent* RunFindObject(uint16_t tag, IfdId group, TiffComponent* obj) {
    TiffFinder finder(tag, group);
    finder.findObject(obj);
    return finder.result();
  }

  static TiffComponent* RunVisitEntry(uint16_t tag, IfdId group, TiffEntry* obj) {
    TiffFinder finder(tag, group);
    finder.visitEntry(obj);
    return finder.result();
  }

  static TiffComponent* RunInitThenFindObject(uint16_t tag1, IfdId group1, uint16_t tag2, IfdId group2,
                                             TiffComponent* obj) {
    TiffFinder finder(tag1, group1);
    finder.init(tag2, group2);
    finder.findObject(obj);
    return finder.result();
  }

  static TiffComponent* RunInitThenVisitEntry(uint16_t tag1, IfdId group1, uint16_t tag2, IfdId group2,
                                             TiffEntry* obj) {
    TiffFinder finder(tag1, group1);
    finder.init(tag2, group2);
    finder.visitEntry(obj);
    return finder.result();
  }
};

TEST_F(TiffFinderTest_1631, VisitEntryMatchesFindObjectForNull_1631) {
  // We can safely pass nullptr without needing to construct a concrete TiffEntry.
  // The key property tested: visitEntry(...) behaves consistently with findObject(...)
  // for the same initial state and same pointer value.
  const uint16_t tag = 0x1234;
  const IfdId group = static_cast<IfdId>(0);

  TiffComponent* r_find = RunFindObject(tag, group, nullptr);
  TiffComponent* r_visit = RunVisitEntry(tag, group, static_cast<TiffEntry*>(nullptr));

  EXPECT_EQ(r_find, r_visit);
}

TEST_F(TiffFinderTest_1631, VisitEntryMatchesFindObjectAcrossDifferentInitParams_1631) {
  // Boundary-ish coverage: vary tag/group values (including 0 and max tag).
  const uint16_t tagA = 0x0000;
  const IfdId groupA = static_cast<IfdId>(0);

  const uint16_t tagB = 0xFFFF;
  const IfdId groupB = static_cast<IfdId>(1);

  TiffComponent* r_find = RunInitThenFindObject(tagA, groupA, tagB, groupB, nullptr);
  TiffComponent* r_visit = RunInitThenVisitEntry(tagA, groupA, tagB, groupB, static_cast<TiffEntry*>(nullptr));

  EXPECT_EQ(r_find, r_visit);
}

TEST_F(TiffFinderTest_1631, VisitEntryIsIdempotentLikeFindObjectForNull_1631) {
  // Compare repeated calls: visitEntry(nullptr) twice vs findObject(nullptr) twice
  // within the same object lifetime, only checking observable result().
  const uint16_t tag = 0x00AB;
  const IfdId group = static_cast<IfdId>(0);

  TiffFinder finder_find(tag, group);
  finder_find.findObject(nullptr);
  TiffComponent* r_find_1 = finder_find.result();
  finder_find.findObject(nullptr);
  TiffComponent* r_find_2 = finder_find.result();

  TiffFinder finder_visit(tag, group);
  finder_visit.visitEntry(static_cast<TiffEntry*>(nullptr));
  TiffComponent* r_visit_1 = finder_visit.result();
  finder_visit.visitEntry(static_cast<TiffEntry*>(nullptr));
  TiffComponent* r_visit_2 = finder_visit.result();

  EXPECT_EQ(r_find_1, r_visit_1);
  EXPECT_EQ(r_find_2, r_visit_2);
}

TEST_F(TiffFinderTest_1631, VisitEntryDoesNotThrowOnNull_1631) {
  const uint16_t tag = 0x2222;
  const IfdId group = static_cast<IfdId>(0);

  TiffFinder finder(tag, group);
  EXPECT_NO_THROW(finder.visitEntry(static_cast<TiffEntry*>(nullptr)));
}

}  // namespace