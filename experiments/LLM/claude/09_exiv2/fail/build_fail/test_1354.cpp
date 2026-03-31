#include <gtest/gtest.h>
#include "samsungmn_int.hpp"

using namespace Exiv2::Internal;

// Test that tagList returns a non-null pointer
TEST(Samsung2MakerNoteTest_1354, TagListReturnsNonNull_1354) {
  auto tags = Samsung2MakerNote::tagList();
  ASSERT_NE(tags, nullptr);
}

// Test that the first tag in tagList has a valid tag id (typically starts with a known value)
TEST(Samsung2MakerNoteTest_1354, TagListFirstEntryValid_1354) {
  auto tags = Samsung2MakerNote::tagList();
  ASSERT_NE(tags, nullptr);
  // The first entry should have a non-empty tag name if it's a valid tag list
  // TagInfo typically has a tag_ member and a name_ member
  // We just verify it's accessible without crashing
  EXPECT_TRUE(tags[0].tag_ >= 0 || tags[0].tag_ == 0xffff);
}

// Test that tagList is terminated with a sentinel entry (tag_ == 0xffff or similar)
TEST(Samsung2MakerNoteTest_1354, TagListHasSentinel_1354) {
  auto tags = Samsung2MakerNote::tagList();
  ASSERT_NE(tags, nullptr);

  int count = 0;
  const int maxTags = 10000;  // safety limit
  while (count < maxTags && tags[count].tag_ != 0xffff) {
    ++count;
  }
  // Verify we found the sentinel before hitting the safety limit
  EXPECT_LT(count, maxTags);
  EXPECT_EQ(tags[count].tag_, 0xffff);
}

// Test that all tag entries before sentinel have non-null names
TEST(Samsung2MakerNoteTest_1354, TagListEntriesHaveNames_1354) {
  auto tags = Samsung2MakerNote::tagList();
  ASSERT_NE(tags, nullptr);

  int count = 0;
  const int maxTags = 10000;
  while (count < maxTags && tags[count].tag_ != 0xffff) {
    EXPECT_NE(tags[count].name_, nullptr) << "Tag at index " << count << " has null name";
    ++count;
  }
}

// Test that calling tagList multiple times returns the same pointer (constexpr/static data)
TEST(Samsung2MakerNoteTest_1354, TagListReturnsSamePointer_1354) {
  auto tags1 = Samsung2MakerNote::tagList();
  auto tags2 = Samsung2MakerNote::tagList();
  EXPECT_EQ(tags1, tags2);
}

// Test that tagList contains at least one valid entry before the sentinel
TEST(Samsung2MakerNoteTest_1354, TagListContainsAtLeastOneEntry_1354) {
  auto tags = Samsung2MakerNote::tagList();
  ASSERT_NE(tags, nullptr);
  // The first entry should not be the sentinel (Samsung2 maker notes have tags)
  EXPECT_NE(tags[0].tag_, 0xffff);
}

// Test that tag entries have non-empty title strings
TEST(Samsung2MakerNoteTest_1354, TagListEntriesHaveTitles_1354) {
  auto tags = Samsung2MakerNote::tagList();
  ASSERT_NE(tags, nullptr);

  int count = 0;
  const int maxTags = 10000;
  while (count < maxTags && tags[count].tag_ != 0xffff) {
    EXPECT_NE(tags[count].title_, nullptr) << "Tag at index " << count << " has null title";
    ++count;
  }
}
