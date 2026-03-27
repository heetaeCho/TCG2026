// -------------------------------------------------------------------------------------------------
// TEST_ID: 1636
// File: test_tiffvisitor_int_tifffinder_visitSubIfd_1636.cpp
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using Exiv2::IfdId;
using Exiv2::Internal::TiffFinder;
using Exiv2::Internal::TiffSubIfd;

class TiffFinderTest_1636 : public ::testing::Test {
 protected:
  static IfdId Ifd(int v) { return static_cast<IfdId>(v); }
};

TEST_F(TiffFinderTest_1636, VisitSubIfd_MatchingTagAndGroup_SetsResultToObject_1636) {
  const uint16_t tag = 0x1234;
  const IfdId group = Ifd(0);
  const IfdId newGroup = Ifd(1);

  TiffFinder finder(tag, group);
  finder.init(tag, group);

  TiffSubIfd sub(tag, group, newGroup);

  // Pre-condition: after init(), result should be empty.
  EXPECT_EQ(finder.result(), nullptr);

  finder.visitSubIfd(&sub);

  // Observable behavior: when visiting a sub-IFD that matches the configured key,
  // the finder should yield that component via result().
  EXPECT_EQ(finder.result(), &sub);
}

TEST_F(TiffFinderTest_1636, VisitSubIfd_MismatchedTag_DoesNotSetResult_1636) {
  const uint16_t finderTag = 0x1111;
  const uint16_t objectTag = 0x2222;
  const IfdId group = Ifd(0);
  const IfdId newGroup = Ifd(1);

  TiffFinder finder(finderTag, group);
  finder.init(finderTag, group);

  TiffSubIfd sub(objectTag, group, newGroup);

  EXPECT_EQ(finder.result(), nullptr);

  finder.visitSubIfd(&sub);

  // Observable behavior: with a tag mismatch, the finder should not report this object.
  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1636, VisitSubIfd_MismatchedGroup_DoesNotSetResult_1636) {
  const uint16_t tag = 0x3333;
  const IfdId finderGroup = Ifd(0);
  const IfdId objectGroup = Ifd(2);
  const IfdId newGroup = Ifd(1);

  TiffFinder finder(tag, finderGroup);
  finder.init(tag, finderGroup);

  TiffSubIfd sub(tag, objectGroup, newGroup);

  EXPECT_EQ(finder.result(), nullptr);

  finder.visitSubIfd(&sub);

  // Observable behavior: with a group mismatch, the finder should not report this object.
  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1636, VisitSubIfd_TwoMatchingObjects_ResultIsOneOfVisitedMatches_1636) {
  const uint16_t tag = 0x4444;
  const IfdId group = Ifd(0);
  const IfdId newGroup = Ifd(1);

  TiffFinder finder(tag, group);
  finder.init(tag, group);

  TiffSubIfd sub1(tag, group, newGroup);
  TiffSubIfd sub2(tag, group, newGroup);

  EXPECT_EQ(finder.result(), nullptr);

  finder.visitSubIfd(&sub1);
  ASSERT_NE(finder.result(), nullptr);

  finder.visitSubIfd(&sub2);

  // Without assuming internal selection policy (first match vs last match),
  // the result should be a matching object that was visited.
  EXPECT_TRUE(finder.result() == &sub1 || finder.result() == &sub2);
}

TEST_F(TiffFinderTest_1636, InitAfterFinding_ClearsResult_1636) {
  const uint16_t tag = 0x5555;
  const IfdId group = Ifd(0);
  const IfdId newGroup = Ifd(1);

  TiffFinder finder(tag, group);
  finder.init(tag, group);

  TiffSubIfd sub(tag, group, newGroup);

  finder.visitSubIfd(&sub);
  ASSERT_EQ(finder.result(), &sub);

  // Re-initialize; observable expectation is that it resets the current result.
  finder.init(tag, group);
  EXPECT_EQ(finder.result(), nullptr);
}

}  // namespace