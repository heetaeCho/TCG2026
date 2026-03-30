// File: test_mpfTagList_1360.cpp
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <set>

// Exiv2 internal tag list API
#include "tags_int.hpp"  // for Exiv2::Internal::mpfTagList(), TagInfo, IfdId, SectionId, TypeId (as available)

namespace {

// mpfTagInfo is a global defined in tags_int.cpp; declare it here for address/identity checks.
extern const Exiv2::TagInfo Exiv2_Internal_mpfTagInfo_1360[20];

// Some Exiv2 builds keep it in Exiv2::Internal namespace directly with this name.
// Provide a fallback declaration that matches the common Exiv2 layout.
extern const Exiv2::TagInfo mpfTagInfo[20];

constexpr std::size_t kMpfTagCount_1360 = 20;

}  // namespace

class MpfTagListTest_1360 : public ::testing::Test {};

TEST_F(MpfTagListTest_1360, ReturnsNonNullPointer_1360) {
  const Exiv2::TagInfo* p = Exiv2::Internal::mpfTagList();
  ASSERT_NE(p, nullptr);
}

TEST_F(MpfTagListTest_1360, ReturnsStablePointerAcrossCalls_1360) {
  const Exiv2::TagInfo* p1 = Exiv2::Internal::mpfTagList();
  const Exiv2::TagInfo* p2 = Exiv2::Internal::mpfTagList();
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2);
}

TEST_F(MpfTagListTest_1360, PointsToFirstElementOfGlobalMpfTagInfo_1360) {
  const Exiv2::TagInfo* p = Exiv2::Internal::mpfTagList();
  ASSERT_NE(p, nullptr);

  // Prefer the canonical symbol in Exiv2::Internal if available.
  // If your build exposes only Exiv2::Internal::mpfTagInfo, this will compile and pass.
  // If not, the second extern (mpfTagInfo) covers the common layout.
#if defined(__clang__) || defined(__GNUC__) || defined(_MSC_VER)
  // Use the more common name first.
  EXPECT_EQ(p, &Exiv2::Internal::mpfTagInfo[0]);
#else
  EXPECT_EQ(p, &mpfTagInfo[0]);
#endif
}

TEST_F(MpfTagListTest_1360, ContainsExpectedSentinelUnknownTagAtEnd_1360) {
  const Exiv2::TagInfo* p = Exiv2::Internal::mpfTagList();
  ASSERT_NE(p, nullptr);

  const Exiv2::TagInfo& last = p[kMpfTagCount_1360 - 1];

  // Observable boundary: the list ends with an "Unknown MPF tag" entry.
  EXPECT_EQ(last.tag_, 65535);
  ASSERT_NE(last.name_, nullptr);
  ASSERT_NE(last.title_, nullptr);
  ASSERT_NE(last.desc_, nullptr);

  EXPECT_STREQ(last.name_, "(UnknownMpfTag)");
  EXPECT_STREQ(last.title_, "Unknown MPF tag");
  EXPECT_STREQ(last.desc_, "Unknown MPF tag");
  EXPECT_EQ(last.ifdId_, Exiv2::IfdId::mpfId);
  EXPECT_EQ(last.sectionId_, Exiv2::SectionId::mpfTags);
}

TEST_F(MpfTagListTest_1360, FirstEntryMatchesMpfVersion_1360) {
  const Exiv2::TagInfo* p = Exiv2::Internal::mpfTagList();
  ASSERT_NE(p, nullptr);

  const Exiv2::TagInfo& first = p[0];

  EXPECT_EQ(first.tag_, 45056);
  ASSERT_NE(first.name_, nullptr);
  ASSERT_NE(first.title_, nullptr);
  ASSERT_NE(first.desc_, nullptr);

  EXPECT_STREQ(first.name_, "MPFVersion");
  EXPECT_STREQ(first.title_, "MPFVersion");
  EXPECT_STREQ(first.desc_, "MPF Version");
  EXPECT_EQ(first.ifdId_, Exiv2::IfdId::mpfId);
  EXPECT_EQ(first.sectionId_, Exiv2::SectionId::mpfTags);
}

TEST_F(MpfTagListTest_1360, AllEntriesAreInMpfIfdAndMpfSection_1360) {
  const Exiv2::TagInfo* p = Exiv2::Internal::mpfTagList();
  ASSERT_NE(p, nullptr);

  for (std::size_t i = 0; i < kMpfTagCount_1360; ++i) {
    EXPECT_EQ(p[i].ifdId_, Exiv2::IfdId::mpfId) << "index=" << i;
    EXPECT_EQ(p[i].sectionId_, Exiv2::SectionId::mpfTags) << "index=" << i;
  }
}

TEST_F(MpfTagListTest_1360, TagIdsAreUniqueWithinList_1360) {
  const Exiv2::TagInfo* p = Exiv2::Internal::mpfTagList();
  ASSERT_NE(p, nullptr);

  std::set<uint16_t> seen;
  for (std::size_t i = 0; i < kMpfTagCount_1360; ++i) {
    const auto inserted = seen.insert(static_cast<uint16_t>(p[i].tag_));
    EXPECT_TRUE(inserted.second) << "duplicate tag id at index=" << i << " tag=" << p[i].tag_;
  }
}

TEST_F(MpfTagListTest_1360, EachEntryHasNonNullStrings_1360) {
  const Exiv2::TagInfo* p = Exiv2::Internal::mpfTagList();
  ASSERT_NE(p, nullptr);

  for (std::size_t i = 0; i < kMpfTagCount_1360; ++i) {
    EXPECT_NE(p[i].name_, nullptr) << "index=" << i;
    EXPECT_NE(p[i].title_, nullptr) << "index=" << i;
    EXPECT_NE(p[i].desc_, nullptr) << "index=" << i;
  }
}