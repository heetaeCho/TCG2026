// =================================================================================================
// Unit tests for Exiv2::Internal::TiffFinder::visitDirectory
// File under test: ./TestProjects/exiv2/src/tiffvisitor_int.cpp
//
// TEST_ID: 1635
// =================================================================================================

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

// Use a safe way to create an IfdId without assuming specific enumerators exist in all builds.
inline Exiv2::Internal::IfdId Ifd0() {
  return static_cast<Exiv2::Internal::IfdId>(0);
}
inline Exiv2::Internal::IfdId Ifd1() {
  return static_cast<Exiv2::Internal::IfdId>(1);
}

class TiffFinderVisitDirectoryTest_1635 : public ::testing::Test {};

TEST_F(TiffFinderVisitDirectoryTest_1635, ForwardsToFindObject_SameEffectAsDirectCall_1635_1) {
  using namespace Exiv2::Internal;

  const uint16_t finderTag = 0x1234;
  const IfdId finderGroup = Ifd0();

  TiffDirectory dir(/*tag=*/0x9999, /*group=*/Ifd1(), /*hasNext=*/false);

  TiffFinder viaVisit(finderTag, finderGroup);
  viaVisit.init(finderTag, finderGroup);
  ASSERT_EQ(nullptr, viaVisit.result());

  // Behavior under test
  viaVisit.visitDirectory(&dir);
  TiffComponent* resultViaVisit = viaVisit.result();

  TiffFinder direct(finderTag, finderGroup);
  direct.init(finderTag, finderGroup);
  ASSERT_EQ(nullptr, direct.result());

  // Reference behavior: directly calling the publicly exposed target method.
  direct.findObject(&dir);
  TiffComponent* resultDirect = direct.result();

  // We don't assume what the result "should" be; only that visitDirectory behaves like findObject.
  EXPECT_EQ(resultDirect, resultViaVisit);
}

TEST_F(TiffFinderVisitDirectoryTest_1635, ForwardsToFindObject_AfterReinit_SameEffectAsDirectCall_1635_2) {
  using namespace Exiv2::Internal;

  const uint16_t tagA = 0x0001;
  const uint16_t tagB = 0x00FE;
  const IfdId groupA = Ifd0();
  const IfdId groupB = Ifd1();

  TiffDirectory dirA(/*tag=*/0x1111, /*group=*/groupA, /*hasNext=*/false);
  TiffDirectory dirB(/*tag=*/0x2222, /*group=*/groupB, /*hasNext=*/false);

  // Path 1: visitDirectory after reinit twice
  TiffFinder viaVisit(tagA, groupA);
  viaVisit.init(tagA, groupA);
  viaVisit.visitDirectory(&dirA);
  TiffComponent* r1_visit = viaVisit.result();

  viaVisit.init(tagB, groupB);
  viaVisit.visitDirectory(&dirB);
  TiffComponent* r2_visit = viaVisit.result();

  // Path 2: direct findObject after the same reinit sequence
  TiffFinder direct(tagA, groupA);
  direct.init(tagA, groupA);
  direct.findObject(&dirA);
  TiffComponent* r1_direct = direct.result();

  direct.init(tagB, groupB);
  direct.findObject(&dirB);
  TiffComponent* r2_direct = direct.result();

  EXPECT_EQ(r1_direct, r1_visit);
  EXPECT_EQ(r2_direct, r2_visit);
}

TEST_F(TiffFinderVisitDirectoryTest_1635, RepeatedCalls_MatchDirectRepeatedCalls_1635_3) {
  using namespace Exiv2::Internal;

  const uint16_t finderTag = 0x7777;
  const IfdId finderGroup = Ifd0();

  TiffDirectory dir1(/*tag=*/0xAAAA, /*group=*/Ifd0(), /*hasNext=*/false);
  TiffDirectory dir2(/*tag=*/0xBBBB, /*group=*/Ifd1(), /*hasNext=*/false);

  // visitDirectory sequence
  TiffFinder viaVisit(finderTag, finderGroup);
  viaVisit.init(finderTag, finderGroup);

  viaVisit.visitDirectory(&dir1);
  TiffComponent* after1_visit = viaVisit.result();

  viaVisit.visitDirectory(&dir2);
  TiffComponent* after2_visit = viaVisit.result();

  // direct sequence
  TiffFinder direct(finderTag, finderGroup);
  direct.init(finderTag, finderGroup);

  direct.findObject(&dir1);
  TiffComponent* after1_direct = direct.result();

  direct.findObject(&dir2);
  TiffComponent* after2_direct = direct.result();

  EXPECT_EQ(after1_direct, after1_visit);
  EXPECT_EQ(after2_direct, after2_visit);
}

TEST_F(TiffFinderVisitDirectoryTest_1635, DoesNotThrow_OnValidPointer_1635_4) {
  using namespace Exiv2::Internal;

  TiffDirectory dir(/*tag=*/0x0000, /*group=*/Ifd0(), /*hasNext=*/false);
  TiffFinder finder(/*tag=*/0x0000, /*group=*/Ifd0());
  finder.init(/*tag=*/0x0000, /*group=*/Ifd0());

  EXPECT_NO_THROW(finder.visitDirectory(&dir));
}

}  // namespace