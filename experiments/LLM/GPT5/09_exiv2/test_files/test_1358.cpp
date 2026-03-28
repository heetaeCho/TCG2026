// ***************************************************************** -*- C++ -*-
// Unit tests for ./TestProjects/exiv2/src/tags_int.cpp
//
// Function under test:
//   const Exiv2::TagInfo* Exiv2::Internal::exifTagList();
//
// Constraints:
// - Treat implementation as a black box (no logic reimplementation).
// - Test only observable behavior via public interfaces / exported symbols.
//
// TEST_ID: 1358
// *****************************************************************

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

// Exiv2 headers (internal). The exact include path may vary by your build setup.
// Try the common internal header locations used by Exiv2 builds.
#if __has_include("tags_int.hpp")
#include "tags_int.hpp"
#elif __has_include("exiv2/tags_int.hpp")
#include "exiv2/tags_int.hpp"
#elif __has_include(<exiv2/tags_int.hpp>)
#include <exiv2/tags_int.hpp>
#else
// If your environment uses a different include layout, adjust the include above.
#include "tags_int.hpp"
#endif

namespace {

class ExifTagListTest_1358 : public ::testing::Test {};

TEST_F(ExifTagListTest_1358, ReturnsNonNullPointer_1358) {
  const Exiv2::TagInfo* p = Exiv2::Internal::exifTagList();
  EXPECT_NE(p, nullptr);
}

TEST_F(ExifTagListTest_1358, ReturnsSamePointerAcrossCalls_1358) {
  const Exiv2::TagInfo* p1 = Exiv2::Internal::exifTagList();
  const Exiv2::TagInfo* p2 = Exiv2::Internal::exifTagList();
  EXPECT_EQ(p1, p2);
}

TEST_F(ExifTagListTest_1358, ReturnedPointerMatchesGlobalArrayStart_1358) {
  // Observable behavior: exifTagList() should return a pointer to the Exiv2
  // internal exif tag list. The code under test is expected to return exifTagInfo.
  const Exiv2::TagInfo* p = Exiv2::Internal::exifTagList();
  EXPECT_EQ(p, Exiv2::Internal::exifTagInfo);
}

TEST_F(ExifTagListTest_1358, FirstEntryMatchesKnownExposureTimeTag_1358) {
  const Exiv2::TagInfo* p = Exiv2::Internal::exifTagList();
  ASSERT_NE(p, nullptr);

  // Verify a few well-known, externally observable fields from the exported table.
  // (Data checks only; no inference about internal logic.)
  EXPECT_EQ(p[0].tag_, static_cast<uint16_t>(33434));
  EXPECT_STREQ(p[0].name_, "ExposureTime");
  EXPECT_STREQ(p[0].title_, "Exposure Time");
  ASSERT_NE(p[0].desc_, nullptr);
  EXPECT_NE(std::strlen(p[0].desc_), 0u);
}

TEST_F(ExifTagListTest_1358, SecondEntryMatchesKnownFNumberTag_1358) {
  const Exiv2::TagInfo* p = Exiv2::Internal::exifTagList();
  ASSERT_NE(p, nullptr);

  EXPECT_EQ(p[1].tag_, static_cast<uint16_t>(33437));
  EXPECT_STREQ(p[1].name_, "FNumber");
  EXPECT_STREQ(p[1].title_, "FNumber");
  ASSERT_NE(p[1].desc_, nullptr);
  EXPECT_NE(std::strlen(p[1].desc_), 0u);
}

TEST_F(ExifTagListTest_1358, LastEntryIsUnknownExifTagSentinel_1358) {
  // Boundary-style check: the table is known (in this build) to have a fixed size.
  // We validate the last element matches the published "Unknown Exif tag" sentinel.
  //
  // This is a data/ABI verification against the exported constant table, not an
  // inference about how exifTagList works.
  constexpr std::size_t kCount = std::size(Exiv2::Internal::exifTagInfo);
  ASSERT_GT(kCount, 0u);

  const Exiv2::TagInfo* p = Exiv2::Internal::exifTagList();
  ASSERT_NE(p, nullptr);

  const Exiv2::TagInfo& last = p[kCount - 1];
  EXPECT_EQ(last.tag_, static_cast<uint16_t>(65535));
  EXPECT_STREQ(last.name_, "(UnknownExifTag)");
  EXPECT_STREQ(last.title_, "Unknown Exif tag");
  ASSERT_NE(last.desc_, nullptr);
  EXPECT_NE(std::strlen(last.desc_), 0u);
}

TEST_F(ExifTagListTest_1358, ReturnedPointerAllowsIndexingWithinKnownBounds_1358) {
  // Boundary condition: ensure the returned pointer is usable for reading within
  // the known array bounds.
  constexpr std::size_t kCount = std::size(Exiv2::Internal::exifTagInfo);
  ASSERT_GT(kCount, 2u);

  const Exiv2::TagInfo* p = Exiv2::Internal::exifTagList();
  ASSERT_NE(p, nullptr);

  // Access a couple of boundary-adjacent entries to ensure no UB/crash and values
  // look like valid TagInfo records (basic sanity).
  const Exiv2::TagInfo& first = p[0];
  const Exiv2::TagInfo& nearEnd = p[kCount - 2];
  const Exiv2::TagInfo& end = p[kCount - 1];

  EXPECT_NE(first.name_, nullptr);
  EXPECT_NE(nearEnd.name_, nullptr);
  EXPECT_NE(end.name_, nullptr);
}

}  // namespace