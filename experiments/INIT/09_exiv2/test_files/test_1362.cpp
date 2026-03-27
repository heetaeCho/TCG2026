// =================================================================================================
// TestProjects/exiv2/tests/unit_tests/test_tags_int_mnTagList_1362.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include "tags_int.hpp"  // Exiv2::Internal::mnTagList(), TagInfo, IfdId, SectionId, TypeId (e.g., unsignedLong)

// The function under test is:
//   namespace Exiv2 { namespace Internal { const TagInfo* mnTagList() { return mnTagInfo; } } }

namespace {

using Exiv2::Internal::mnTagList;
using Exiv2::Internal::TagInfo;

class MnTagListTest_1362 : public ::testing::Test {};

TEST_F(MnTagListTest_1362, ReturnsNonNullPointer_1362) {
  const TagInfo* list = mnTagList();
  ASSERT_NE(list, nullptr);
}

TEST_F(MnTagListTest_1362, ReturnsStablePointerAcrossCalls_1362) {
  const TagInfo* a = mnTagList();
  const TagInfo* b = mnTagList();
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_EQ(a, b);
}

TEST_F(MnTagListTest_1362, FirstEntryHasExpectedTagIdAndNames_1362) {
  const TagInfo* list = mnTagList();
  ASSERT_NE(list, nullptr);

  EXPECT_EQ(list[0].tag_, 1);
  EXPECT_STREQ(list[0].name_, "Offset");
  EXPECT_STREQ(list[0].title_, "Offset");
  EXPECT_STREQ(list[0].desc_, "Offset of the makernote from the start of the TIFF header.");
}

TEST_F(MnTagListTest_1362, SecondEntryHasExpectedTagIdAndNames_1362) {
  const TagInfo* list = mnTagList();
  ASSERT_NE(list, nullptr);

  EXPECT_EQ(list[1].tag_, 2);
  EXPECT_STREQ(list[1].name_, "ByteOrder");
  EXPECT_STREQ(list[1].title_, "Byte Order");
  EXPECT_STREQ(
      list[1].desc_,
      "Byte order used to encode MakerNote tags, 'MM' (big-endian) or 'II' (little-endian).");
}

TEST_F(MnTagListTest_1362, AllEntriesShareExpectedIfdAndSection_1362) {
  const TagInfo* list = mnTagList();
  ASSERT_NE(list, nullptr);

  // Verify a boundary across the known entries we can observe by indexing.
  // (We do not attempt to infer list length beyond what is provided/observable here.)
  EXPECT_EQ(list[0].ifdId_, Exiv2::IfdId::mnId);
  EXPECT_EQ(list[1].ifdId_, Exiv2::IfdId::mnId);
  EXPECT_EQ(list[2].ifdId_, Exiv2::IfdId::mnId);

  EXPECT_EQ(list[0].sectionId_, Exiv2::SectionId::makerTags);
  EXPECT_EQ(list[1].sectionId_, Exiv2::SectionId::makerTags);
  EXPECT_EQ(list[2].sectionId_, Exiv2::SectionId::makerTags);
}

TEST_F(MnTagListTest_1362, ThirdEntryRepresentsUnknownSentinel_1362) {
  const TagInfo* list = mnTagList();
  ASSERT_NE(list, nullptr);

  // Boundary/sentinel style entry (commonly used for "unknown tag" handling).
  EXPECT_EQ(list[2].tag_, 65535);
  EXPECT_STREQ(list[2].name_, "(UnknownMnTag)");
  EXPECT_STREQ(list[2].title_, "Unknown Exiv2 Makernote info tag");
  EXPECT_STREQ(list[2].desc_, "Unknown Exiv2 Makernote info tag");
}

TEST_F(MnTagListTest_1362, TypesAndCountsMatchKnownObservableValues_1362) {
  const TagInfo* list = mnTagList();
  ASSERT_NE(list, nullptr);

  // Check a few additional observable fields without assuming any internal logic.
  EXPECT_EQ(list[0].typeId_, Exiv2::unsignedLong);
  EXPECT_EQ(list[0].count_, 1);

  EXPECT_EQ(list[1].typeId_, Exiv2::asciiString);
  EXPECT_EQ(list[1].count_, 0);

  EXPECT_EQ(list[2].typeId_, Exiv2::asciiString);
  EXPECT_EQ(list[2].count_, -1);
}

}  // namespace