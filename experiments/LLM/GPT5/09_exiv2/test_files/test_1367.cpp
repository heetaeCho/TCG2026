// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_taginfo_1367.cpp
//
// Unit tests for Exiv2::Internal::tagInfo (from ./src/tags_int.cpp)
//
// Constraints honored:
// - Treat implementation as a black box (no re-implementation of internal logic beyond what is observable).
// - Use only public/available interfaces and observable behavior.
// - No access to private state.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include <exiv2/tags.hpp>

// The implementation under test lives in Exiv2::Internal and depends on tagList(IfdId).
// In Exiv2, the internal declarations are typically exposed via this internal header.
#include "tags_int.hpp"

namespace {

using Exiv2::Internal::tagInfo;
using Exiv2::Internal::tagList;
using Exiv2::IfdId;

class TagInfoTest_1367 : public ::testing::Test {
 protected:
  static constexpr uint16_t kSentinelTag = 0xffff;

  static const Exiv2::TagInfo* FindSentinel(const Exiv2::TagInfo* list) {
    if (!list) return nullptr;
    // Termination is observable via the sentinel contract used by tagInfo().
    for (int i = 0; /*bounded by sentinel*/; ++i) {
      if (list[i].tag_ == kSentinelTag) return &list[i];
      // Hard safety guard against pathological lists (should never trigger in real Exiv2 lists).
      if (i > 1'000'000) return nullptr;
    }
  }

  static const Exiv2::TagInfo* FindLastRealEntry(const Exiv2::TagInfo* list) {
    const Exiv2::TagInfo* sentinel = FindSentinel(list);
    if (!sentinel) return nullptr;
    if (sentinel == list) return nullptr;  // Empty list (only sentinel)
    return sentinel - 1;
  }
};

TEST_F(TagInfoTest_1367, ReturnsNullptrWhenTagListIsNull_1367) {
  // Use an out-of-range/unknown IfdId value. Observable behavior: tagInfo returns nullptr
  // iff tagList(ifdId) is nullptr.
  const auto invalidIfd = static_cast<IfdId>(std::numeric_limits<int>::max());

  const Exiv2::TagInfo* list = tagList(invalidIfd);
  const Exiv2::TagInfo* ti = tagInfo(/*tag=*/0x0000, invalidIfd);

  // This test verifies the observable contract: tagInfo mirrors whether a list exists.
  if (list == nullptr) {
    EXPECT_EQ(ti, nullptr);
  } else {
    // If the library happens to map this value to a valid list, ensure tagInfo is consistent
    // with the interface (returns a pointer into the list, never nullptr).
    EXPECT_NE(ti, nullptr);
  }
}

TEST_F(TagInfoTest_1367, ReturnsPointerToFirstEntryForFirstTagWhenListExists_1367) {
  // Choose a well-known, standard IFD id that should exist in Exiv2.
  // If this environment/library build lacks it, we skip rather than guessing behavior.
  const IfdId ifdId = static_cast<IfdId>(0);  // commonly ifd0Id in Exiv2

  const Exiv2::TagInfo* list = tagList(ifdId);
  ASSERT_NE(list, nullptr) << "tagList(ifdId=0) returned nullptr; cannot validate pointer behavior.";

  // If list contains only sentinel, skip.
  const Exiv2::TagInfo* sentinel = FindSentinel(list);
  ASSERT_NE(sentinel, nullptr) << "Could not locate sentinel entry (tag_==0xffff).";
  ASSERT_NE(sentinel, list) << "List appears empty (only sentinel).";

  const uint16_t firstTag = list[0].tag_;
  const Exiv2::TagInfo* found = tagInfo(firstTag, ifdId);

  // Observable: for an existing tag equal to the first entry, result must be that entry.
  EXPECT_EQ(found, &list[0]);
}

TEST_F(TagInfoTest_1367, ReturnsPointerToSentinelWhenTagIsSentinelValue_1367) {
  const IfdId ifdId = static_cast<IfdId>(0);  // commonly ifd0Id in Exiv2

  const Exiv2::TagInfo* list = tagList(ifdId);
  ASSERT_NE(list, nullptr) << "tagList(ifdId=0) returned nullptr; cannot validate sentinel behavior.";

  const Exiv2::TagInfo* sentinel = FindSentinel(list);
  ASSERT_NE(sentinel, nullptr) << "Could not locate sentinel entry (tag_==0xffff).";

  const Exiv2::TagInfo* found = tagInfo(kSentinelTag, ifdId);

  // Observable behavior from the interface: searching for the sentinel tag yields the sentinel entry.
  EXPECT_EQ(found, sentinel);
}

TEST_F(TagInfoTest_1367, ReturnsPointerToLastRealEntryForLastRealTag_1367) {
  const IfdId ifdId = static_cast<IfdId>(0);  // commonly ifd0Id in Exiv2

  const Exiv2::TagInfo* list = tagList(ifdId);
  ASSERT_NE(list, nullptr) << "tagList(ifdId=0) returned nullptr; cannot validate last-entry behavior.";

  const Exiv2::TagInfo* lastReal = FindLastRealEntry(list);
  ASSERT_NE(lastReal, nullptr) << "List appears empty (only sentinel) or sentinel not found.";

  const uint16_t lastTag = lastReal->tag_;
  const Exiv2::TagInfo* found = tagInfo(lastTag, ifdId);

  // Observable: for an existing tag equal to the last real entry, result must be that entry.
  EXPECT_EQ(found, lastReal);
}

TEST_F(TagInfoTest_1367, ForNonexistentTagReturnsPointerEqualToSentinel_1367) {
  const IfdId ifdId = static_cast<IfdId>(0);  // commonly ifd0Id in Exiv2

  const Exiv2::TagInfo* list = tagList(ifdId);
  ASSERT_NE(list, nullptr) << "tagList(ifdId=0) returned nullptr; cannot validate not-found behavior.";

  const Exiv2::TagInfo* sentinel = FindSentinel(list);
  ASSERT_NE(sentinel, nullptr) << "Could not locate sentinel entry (tag_==0xffff).";

  // Pick a tag that is very unlikely to exist in typical Exiv2 lists, but still a valid uint16_t.
  // To avoid guessing, we *verify* it's not present by scanning the observable list.
  const uint16_t candidate = 0xfffe;
  for (const Exiv2::TagInfo* p = list; p && p->tag_ != kSentinelTag; ++p) {
    if (p->tag_ == candidate) {
      GTEST_SKIP() << "Candidate tag 0xfffe exists in this list; cannot use it as a not-found tag.";
    }
  }

  const Exiv2::TagInfo* found = tagInfo(candidate, ifdId);

  // Observable behavior of the function: if tag is not found, it returns pointer positioned
  // at the terminal sentinel entry.
  EXPECT_EQ(found, sentinel);
}

TEST_F(TagInfoTest_1367, ReturnedPointerIsWithinListRangeWhenListExists_1367) {
  const IfdId ifdId = static_cast<IfdId>(0);  // commonly ifd0Id in Exiv2

  const Exiv2::TagInfo* list = tagList(ifdId);
  ASSERT_NE(list, nullptr) << "tagList(ifdId=0) returned nullptr; cannot validate range behavior.";

  const Exiv2::TagInfo* sentinel = FindSentinel(list);
  ASSERT_NE(sentinel, nullptr) << "Could not locate sentinel entry (tag_==0xffff).";

  // Choose a tag that is guaranteed to be "in range": use the first entry.
  if (sentinel == list) {
    GTEST_SKIP() << "List appears empty (only sentinel).";
  }

  const uint16_t someExistingTag = list[0].tag_;
  const Exiv2::TagInfo* found = tagInfo(someExistingTag, ifdId);
  ASSERT_NE(found, nullptr);

  // Observable property: tagInfo returns a pointer into the list [list, sentinel] inclusive.
  EXPECT_GE(found, list);
  EXPECT_LE(found, sentinel);
}

}  // namespace