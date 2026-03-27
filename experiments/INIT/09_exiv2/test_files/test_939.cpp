// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 939
//
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListAfC()
// File under test: ./TestProjects/exiv2/src/canonmn_int.hpp

#include <gtest/gtest.h>

#include "canonmn_int.hpp"

// Exiv2 TagInfo definition (used to validate basic, observable properties of tag lists)
#include <exiv2/tags.hpp>

namespace {

using Exiv2::TagInfo;
using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTest_939 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_939, TagListAfCReturnsNonNull_939) {
  const TagInfo* list = CanonMakerNote::tagListAfC();
  ASSERT_NE(list, nullptr);
}

TEST_F(CanonMakerNoteTest_939, TagListAfCIsStableAcrossCalls_939) {
  const TagInfo* list1 = CanonMakerNote::tagListAfC();
  const TagInfo* list2 = CanonMakerNote::tagListAfC();
  ASSERT_NE(list1, nullptr);
  ASSERT_NE(list2, nullptr);

  // Observable behavior: repeated calls should return the same tag list object.
  EXPECT_EQ(list1, list2);
}

TEST_F(CanonMakerNoteTest_939, TagListAfCHasTerminatorSentinelWithinReasonableBound_939) {
  const TagInfo* list = CanonMakerNote::tagListAfC();
  ASSERT_NE(list, nullptr);

  // Exiv2 tag lists are typically terminated by a sentinel entry. We only assert
  // that a terminator exists within a large, reasonable bound to avoid runaway
  // reads if something is wrong.
  //
  // We avoid asserting specific tag values or ordering (internal details).
  constexpr size_t kMaxScan = 10000;

  bool foundTerminator = false;
  for (size_t i = 0; i < kMaxScan; ++i) {
    const TagInfo& ti = list[i];

    // Common Exiv2 convention: the terminating entry has tag_ == 0 and name_ == nullptr.
    // This is a minimal, observable structural property of the returned array.
    if (ti.tag_ == 0 && ti.name_ == nullptr) {
      foundTerminator = true;
      break;
    }
  }

  EXPECT_TRUE(foundTerminator);
}

TEST_F(CanonMakerNoteTest_939, TagListAfCFirstEntriesAreReadable_939) {
  const TagInfo* list = CanonMakerNote::tagListAfC();
  ASSERT_NE(list, nullptr);

  // Boundary-ish sanity: accessing a few entries should be safe and not crash.
  // We do not assume any particular content beyond being readable.
  //
  // If the list is empty, the first entry may already be the sentinel; that's fine.
  const TagInfo& e0 = list[0];
  (void)e0;

  const TagInfo& e1 = list[1];
  (void)e1;

  const TagInfo& e2 = list[2];
  (void)e2;

  SUCCEED();
}

}  // namespace