// SPDX-License-Identifier: GPL-2.0-or-later
//
// TEST_ID 1359
//
// Unit tests for Exiv2::Internal::gpsTagList()
// File under test: ./TestProjects/exiv2/src/tags_int.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// Be tolerant to different include layouts in various Exiv2 setups.
#if __has_include("tags_int.hpp")
#include "tags_int.hpp"
#elif __has_include("exiv2/tags_int.hpp")
#include <exiv2/tags_int.hpp>
#else
// Fallback: some builds may expose internal tags via a different header name.
#include "exiv2/tags_int.hpp"
#endif

#if __has_include("tags.hpp")
#include "tags.hpp"
#elif __has_include("exiv2/tags.hpp")
#include <exiv2/tags.hpp>
#endif

namespace {

class GpsTagListTest_1359 : public ::testing::Test {
 protected:
  static const Exiv2::TagInfo* GetList() { return Exiv2::Internal::gpsTagList(); }

  // Defensive scan to avoid any chance of runaway iteration if sentinel is missing.
  static std::size_t CountUntilSentinel(const Exiv2::TagInfo* list,
                                       uint16_t sentinel_tag,
                                       std::size_t hard_limit) {
    if (!list) return 0;
    for (std::size_t i = 0; i < hard_limit; ++i) {
      if (list[i].tag_ == sentinel_tag) {
        return i + 1;  // include sentinel entry
      }
    }
    return 0;  // not found within limit
  }
};

TEST_F(GpsTagListTest_1359, ReturnsNonNullPointer_1359) {
  const Exiv2::TagInfo* list = GetList();
  ASSERT_NE(list, nullptr);
}

TEST_F(GpsTagListTest_1359, ReturnsStablePointerAcrossCalls_1359) {
  const Exiv2::TagInfo* list1 = GetList();
  const Exiv2::TagInfo* list2 = GetList();
  ASSERT_NE(list1, nullptr);
  ASSERT_NE(list2, nullptr);
  EXPECT_EQ(list1, list2);
}

TEST_F(GpsTagListTest_1359, ListContainsSentinelAndExpectedCount_1359) {
  const Exiv2::TagInfo* list = GetList();
  ASSERT_NE(list, nullptr);

  // Known dependency: gpsTagInfo has 33 entries including the 0xFFFF sentinel.
  constexpr uint16_t kSentinel = 0xFFFF;
  constexpr std::size_t kHardLimit = 256;

  const std::size_t count = CountUntilSentinel(list, kSentinel, kHardLimit);
  ASSERT_NE(count, 0u) << "Sentinel tag 0xFFFF was not found within hard limit";
  EXPECT_EQ(count, 33u);
}

TEST_F(GpsTagListTest_1359, FirstEntryMatchesGpsVersionIdBasics_1359) {
  const Exiv2::TagInfo* list = GetList();
  ASSERT_NE(list, nullptr);

  EXPECT_EQ(list[0].tag_, 0u);
  ASSERT_NE(list[0].name_, nullptr);
  ASSERT_NE(list[0].title_, nullptr);

  EXPECT_STREQ(list[0].name_, "GPSVersionID");
  EXPECT_STREQ(list[0].title_, "GPS Version ID");

  // Basic category identifiers (observable via public data).
  EXPECT_EQ(list[0].ifdId_, Exiv2::IfdId::gpsId);
  EXPECT_EQ(list[0].sectionId_, Exiv2::SectionId::gpsTags);
}

TEST_F(GpsTagListTest_1359, SampleMiddleEntriesHaveExpectedTagsAndNames_1359) {
  const Exiv2::TagInfo* list = GetList();
  ASSERT_NE(list, nullptr);

  // Tag 1: GPSLatitudeRef
  EXPECT_EQ(list[1].tag_, 1u);
  ASSERT_NE(list[1].name_, nullptr);
  EXPECT_STREQ(list[1].name_, "GPSLatitudeRef");
  EXPECT_EQ(list[1].ifdId_, Exiv2::IfdId::gpsId);
  EXPECT_EQ(list[1].sectionId_, Exiv2::SectionId::gpsTags);

  // Tag 2: GPSLatitude
  EXPECT_EQ(list[2].tag_, 2u);
  ASSERT_NE(list[2].name_, nullptr);
  EXPECT_STREQ(list[2].name_, "GPSLatitude");

  // Tag 4: GPSLongitude
  EXPECT_EQ(list[4].tag_, 4u);
  ASSERT_NE(list[4].name_, nullptr);
  EXPECT_STREQ(list[4].name_, "GPSLongitude");

  // Tag 29: GPSDateStamp
  EXPECT_EQ(list[29].tag_, 29u);
  ASSERT_NE(list[29].name_, nullptr);
  EXPECT_STREQ(list[29].name_, "GPSDateStamp");
}

TEST_F(GpsTagListTest_1359, SentinelEntryHasExpectedCharacteristics_1359) {
  const Exiv2::TagInfo* list = GetList();
  ASSERT_NE(list, nullptr);

  constexpr uint16_t kSentinel = 0xFFFF;
  constexpr std::size_t kHardLimit = 256;

  const std::size_t count = CountUntilSentinel(list, kSentinel, kHardLimit);
  ASSERT_NE(count, 0u);

  const Exiv2::TagInfo& sentinel = list[count - 1];
  EXPECT_EQ(sentinel.tag_, kSentinel);

  ASSERT_NE(sentinel.name_, nullptr);
  ASSERT_NE(sentinel.title_, nullptr);
  EXPECT_STREQ(sentinel.name_, "(UnknownGpsTag)");
  EXPECT_STREQ(sentinel.title_, "Unknown GPSInfo tag");

  EXPECT_EQ(sentinel.ifdId_, Exiv2::IfdId::gpsId);
  EXPECT_EQ(sentinel.sectionId_, Exiv2::SectionId::gpsTags);
}

TEST_F(GpsTagListTest_1359, AllEntriesBelongToGpsIfdAndGpsSectionUntilSentinel_1359) {
  const Exiv2::TagInfo* list = GetList();
  ASSERT_NE(list, nullptr);

  constexpr uint16_t kSentinel = 0xFFFF;
  constexpr std::size_t kHardLimit = 256;

  const std::size_t count = CountUntilSentinel(list, kSentinel, kHardLimit);
  ASSERT_NE(count, 0u);

  for (std::size_t i = 0; i < count; ++i) {
    EXPECT_EQ(list[i].ifdId_, Exiv2::IfdId::gpsId) << "Index " << i;
    EXPECT_EQ(list[i].sectionId_, Exiv2::SectionId::gpsTags) << "Index " << i;
    ASSERT_NE(list[i].name_, nullptr) << "Index " << i;
    ASSERT_NE(list[i].title_, nullptr) << "Index " << i;
  }
}

}  // namespace