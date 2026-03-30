// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_taglist_1366.cpp
//
// Unit tests for Exiv2::Internal::tagList(IfdId)
//
// Constraints respected:
// - Treat implementation as a black box
// - Test only observable behavior via the public/declared interface
// - No access to internal/private state
// - No re-implementation of logic

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

// The function under test lives in src/tags_int.cpp (Internal namespace).
// Prefer including the internal header if it exists in this codebase.
// If not available, forward-declare the function signature (no logic inferred).
#if __has_include("tags_int.hpp")
#include "tags_int.hpp"
#elif __has_include(<exiv2/tags_int.hpp>)
#include <exiv2/tags_int.hpp>
#else
namespace Exiv2 {
enum class IfdId : int;  // If the full enum is not visible here, compilation will fail and indicates headers differ.
struct TagInfo;
namespace Internal {
const TagInfo* tagList(IfdId ifdId);
}  // namespace Internal
}  // namespace Exiv2
#endif

namespace {

class TagListTest_1366 : public ::testing::Test {};

TEST_F(TagListTest_1366, ReturnsNullptrForNotSetIfd_1366) {
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(Exiv2::IfdId::ifdIdNotSet);
  EXPECT_EQ(list, nullptr);
}

TEST_F(TagListTest_1366, ReturnsNullptrForLastIdIfd_1366) {
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(Exiv2::IfdId::lastId);
  EXPECT_EQ(list, nullptr);
}

TEST_F(TagListTest_1366, ReturnsNonNullForCommonIfd0_1366) {
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(Exiv2::IfdId::ifd0Id);
  EXPECT_NE(list, nullptr);
}

TEST_F(TagListTest_1366, ReturnsNonNullForExifIfd_1366) {
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(Exiv2::IfdId::exifId);
  EXPECT_NE(list, nullptr);
}

TEST_F(TagListTest_1366, ReturnsNonNullForGpsIfd_1366) {
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(Exiv2::IfdId::gpsId);
  EXPECT_NE(list, nullptr);
}

TEST_F(TagListTest_1366, RepeatedCallsForSameIdAreStable_1366) {
  const Exiv2::TagInfo* first = Exiv2::Internal::tagList(Exiv2::IfdId::ifd0Id);
  const Exiv2::TagInfo* second = Exiv2::Internal::tagList(Exiv2::IfdId::ifd0Id);
  const Exiv2::TagInfo* third = Exiv2::Internal::tagList(Exiv2::IfdId::ifd0Id);

  // Observable stability: pointer should not change across calls for the same id.
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(TagListTest_1366, UnknownNegativeEnumValueReturnsNullptr_1366) {
  // Boundary / error-ish case: invalid enumerator value.
  // We only assert it doesn't crash and returns nullptr (observable behavior).
  const auto bad = static_cast<Exiv2::IfdId>(-1);
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(bad);
  EXPECT_EQ(list, nullptr);
}

TEST_F(TagListTest_1366, UnknownLargeEnumValueReturnsNullptr_1366) {
  // Boundary / error-ish case: out-of-range enumerator value.
  const auto bad = static_cast<Exiv2::IfdId>(0x7fffffff);
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(bad);
  EXPECT_EQ(list, nullptr);
}

}  // namespace