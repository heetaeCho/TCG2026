// TEST_ID 1357
// File: test_tags_int_ifdTagList_1357.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "tags_int.hpp"  // Expected to declare Exiv2::Internal::ifdTagList()
#include "tags.hpp"      // Expected to declare Exiv2::TagInfo, IfdId, SectionId, TypeId (or similar)

namespace {

// Keep the fixture name aligned with your convention.
class IfdTagListTest_1357 : public ::testing::Test {};

static std::string SafeCStr(const char* s) {
  return s ? std::string(s) : std::string();
}

}  // namespace

TEST_F(IfdTagListTest_1357, ReturnsNonNullPointer_1357) {
  const Exiv2::TagInfo* p = Exiv2::Internal::ifdTagList();
  ASSERT_NE(p, nullptr);
}

TEST_F(IfdTagListTest_1357, ReturnsSamePointerAcrossCalls_1357) {
  const Exiv2::TagInfo* p1 = Exiv2::Internal::ifdTagList();
  const Exiv2::TagInfo* p2 = Exiv2::Internal::ifdTagList();
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2);
}

TEST_F(IfdTagListTest_1357, FirstEntryMatchesKnownProcessingSoftwareTag_1357) {
  const Exiv2::TagInfo* list = Exiv2::Internal::ifdTagList();
  ASSERT_NE(list, nullptr);

  // Known from provided dependency snapshot: {11, "ProcessingSoftware", ...}
  EXPECT_EQ(list[0].tag_, 11u);
  EXPECT_EQ(SafeCStr(list[0].name_), "ProcessingSoftware");
  EXPECT_EQ(SafeCStr(list[0].title_), "Processing Software");
  EXPECT_FALSE(SafeCStr(list[0].desc_).empty());

  // Spot-check some other fields that are part of the public struct.
  EXPECT_EQ(list[0].ifdId_, Exiv2::ifd0Id);
  EXPECT_EQ(list[0].sectionId_, Exiv2::otherTags);
}

TEST_F(IfdTagListTest_1357, SecondEntryMatchesKnownNewSubfileTypeTag_1357) {
  const Exiv2::TagInfo* list = Exiv2::Internal::ifdTagList();
  ASSERT_NE(list, nullptr);

  // Known from provided dependency snapshot: {254, "NewSubfileType", ...}
  EXPECT_EQ(list[1].tag_, 254u);
  EXPECT_EQ(SafeCStr(list[1].name_), "NewSubfileType");
  EXPECT_EQ(SafeCStr(list[1].title_), "New Subfile Type");
  EXPECT_FALSE(SafeCStr(list[1].desc_).empty());

  EXPECT_EQ(list[1].ifdId_, Exiv2::ifd0Id);
  EXPECT_EQ(list[1].sectionId_, Exiv2::imgStruct);
}

TEST_F(IfdTagListTest_1357, SeveralEarlyEntriesHaveNonNullTextFields_1357) {
  const Exiv2::TagInfo* list = Exiv2::Internal::ifdTagList();
  ASSERT_NE(list, nullptr);

  // Boundary-ish: verify a small prefix is well-formed without assuming more structure than exposed.
  for (std::size_t i = 0; i < 8; ++i) {
    EXPECT_NE(list[i].name_, nullptr) << "index=" << i;
    EXPECT_NE(list[i].title_, nullptr) << "index=" << i;
    EXPECT_NE(list[i].desc_, nullptr) << "index=" << i;

    // Names/titles shouldn't be empty strings in this table.
    EXPECT_FALSE(SafeCStr(list[i].name_).empty()) << "index=" << i;
    EXPECT_FALSE(SafeCStr(list[i].title_).empty()) << "index=" << i;
  }
}

TEST_F(IfdTagListTest_1357, LastEntryMatchesKnownUnknownIfdTagBoundary_1357) {
  const Exiv2::TagInfo* list = Exiv2::Internal::ifdTagList();
  ASSERT_NE(list, nullptr);

  // From the provided snapshot: const TagInfo[257] ... last is tag 65535 "(UnknownIfdTag)".
  constexpr std::size_t kExpectedCount = 257;
  const Exiv2::TagInfo& last = list[kExpectedCount - 1];

  EXPECT_EQ(last.tag_, 65535u);
  EXPECT_EQ(SafeCStr(last.name_), "(UnknownIfdTag)");
  EXPECT_EQ(SafeCStr(last.title_), "Unknown IFD tag");
  EXPECT_FALSE(SafeCStr(last.desc_).empty());

  // This boundary entry is shown as ifd0Id and sectionIdNotSet in the snapshot.
  EXPECT_EQ(last.ifdId_, Exiv2::ifd0Id);
  EXPECT_EQ(last.sectionId_, Exiv2::sectionIdNotSet);
}