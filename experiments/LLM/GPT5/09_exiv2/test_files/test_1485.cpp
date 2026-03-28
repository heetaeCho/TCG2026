// =================================================================================================
// TEST_ID: 1485
// Unit tests for Exiv2::Internal::PentaxMnHeader (black-box; interface-based)
// File: test_pentax_mn_header_1485.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::PentaxMnHeader;

class PentaxMnHeaderTest_1485 : public ::testing::Test {};

TEST_F(PentaxMnHeaderTest_1485, SizeMethodHasExpectedReturnType_1485) {
  // Interface/ABI-level check: size() const returns size_t.
  static_assert(std::is_same_v<decltype(std::declval<const PentaxMnHeader&>().size()), size_t>,
                "PentaxMnHeader::size() const must return size_t");
  SUCCEED();
}

TEST_F(PentaxMnHeaderTest_1485, DefaultConstructedSizeIsStableAcrossCalls_1485) {
  PentaxMnHeader h;

  const size_t s1 = h.size();
  const size_t s2 = h.size();
  const size_t s3 = h.size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(PentaxMnHeaderTest_1485, SizeMatchesBetweenConstAndNonConstViews_1485) {
  PentaxMnHeader h;
  const PentaxMnHeader& ch = h;

  const size_t nonConstSize = h.size();
  const size_t constSize = ch.size();

  EXPECT_EQ(nonConstSize, constSize);
}

TEST_F(PentaxMnHeaderTest_1485, CopiedObjectReportsSameSize_1485) {
  PentaxMnHeader original;
  const size_t before = original.size();

  PentaxMnHeader copy = original;
  const size_t afterCopy = copy.size();

  EXPECT_EQ(before, afterCopy);
}

TEST_F(PentaxMnHeaderTest_1485, MoveConstructedObjectPreservesReportedSizeFromSourceAtMoveTime_1485) {
  PentaxMnHeader original;
  const size_t beforeMove = original.size();

  PentaxMnHeader moved = std::move(original);
  const size_t movedSize = moved.size();

  // We only assert the moved-to object retains the size observed just before the move.
  // (We do NOT assert anything about the moved-from object's subsequent state.)
  EXPECT_EQ(beforeMove, movedSize);
}

}  // namespace