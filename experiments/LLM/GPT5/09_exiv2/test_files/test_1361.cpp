// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iop_tag_list_1361.cpp
//
// Unit tests for Exiv2::Internal::iopTagList()
// TEST_ID: 1361

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>

// Try common include locations used by Exiv2 builds.
#if __has_include("tags_int.hpp")
#include "tags_int.hpp"
#elif __has_include("exiv2/tags_int.hpp")
#include "exiv2/tags_int.hpp"
#else
// Fallback: some setups expose declarations via tags.hpp (or similar).
#include "tags.hpp"
#endif

namespace {

using Exiv2::Internal::iopTagList;

class IopTagListTest_1361 : public ::testing::Test {};

static void ExpectCStrEq(const char* actual, const char* expected) {
  ASSERT_NE(actual, nullptr);
  ASSERT_NE(expected, nullptr);
  EXPECT_STREQ(actual, expected);
}

}  // namespace

TEST_F(IopTagListTest_1361, ReturnsNonNullPointer_1361) {
  const auto* list = iopTagList();
  ASSERT_NE(list, nullptr);
}

TEST_F(IopTagListTest_1361, ReturnsSamePointerOnRepeatedCalls_1361) {
  const auto* p1 = iopTagList();
  const auto* p2 = iopTagList();
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2);
}

TEST_F(IopTagListTest_1361, ContainsExpectedKnownEntries_1361) {
  const auto* list = iopTagList();
  ASSERT_NE(list, nullptr);

  // These expectations are based on the observable contract of the returned list
  // (known contents in this codebase).
  // Entry 0
  EXPECT_EQ(list[0].tag_, 1);
  ExpectCStrEq(list[0].name_, "InteroperabilityIndex");
  ExpectCStrEq(list[0].title_, "Interoperability Index");
  ASSERT_NE(list[0].desc_, nullptr);

  EXPECT_EQ(list[0].ifdId_, Exiv2::IfdId::iopId);
  EXPECT_EQ(list[0].sectionId_, Exiv2::SectionId::iopTags);
  EXPECT_EQ(list[0].typeId_, Exiv2::asciiString);
  EXPECT_EQ(list[0].count_, 0);

  // Entry 1
  EXPECT_EQ(list[1].tag_, 2);
  ExpectCStrEq(list[1].name_, "InteroperabilityVersion");
  ExpectCStrEq(list[1].title_, "Interoperability Version");
  ASSERT_NE(list[1].desc_, nullptr);

  EXPECT_EQ(list[1].ifdId_, Exiv2::IfdId::iopId);
  EXPECT_EQ(list[1].sectionId_, Exiv2::SectionId::iopTags);
  EXPECT_EQ(list[1].typeId_, Exiv2::undefined);
  EXPECT_EQ(list[1].count_, -1);

  // Entry 2
  EXPECT_EQ(list[2].tag_, 4096);
  ExpectCStrEq(list[2].name_, "RelatedImageFileFormat");
  ExpectCStrEq(list[2].title_, "Related Image File Format");
  ASSERT_NE(list[2].desc_, nullptr);

  EXPECT_EQ(list[2].ifdId_, Exiv2::IfdId::iopId);
  EXPECT_EQ(list[2].sectionId_, Exiv2::SectionId::iopTags);
  EXPECT_EQ(list[2].typeId_, Exiv2::asciiString);
  EXPECT_EQ(list[2].count_, 0);

  // Entry 3
  EXPECT_EQ(list[3].tag_, 4097);
  ExpectCStrEq(list[3].name_, "RelatedImageWidth");
  ExpectCStrEq(list[3].title_, "Related Image Width");
  ASSERT_NE(list[3].desc_, nullptr);

  EXPECT_EQ(list[3].ifdId_, Exiv2::IfdId::iopId);
  EXPECT_EQ(list[3].sectionId_, Exiv2::SectionId::iopTags);
  EXPECT_EQ(list[3].typeId_, Exiv2::unsignedLong);
  EXPECT_EQ(list[3].count_, 1);

  // Entry 4
  EXPECT_EQ(list[4].tag_, 4098);
  ExpectCStrEq(list[4].name_, "RelatedImageLength");
  ExpectCStrEq(list[4].title_, "Related Image Length");
  ASSERT_NE(list[4].desc_, nullptr);

  EXPECT_EQ(list[4].ifdId_, Exiv2::IfdId::iopId);
  EXPECT_EQ(list[4].sectionId_, Exiv2::SectionId::iopTags);
  EXPECT_EQ(list[4].typeId_, Exiv2::unsignedLong);
  EXPECT_EQ(list[4].count_, 1);
}

TEST_F(IopTagListTest_1361, HasUnknownSentinelEntry_1361) {
  const auto* list = iopTagList();
  ASSERT_NE(list, nullptr);

  // In this codebase, the IOP tag list ends with an "unknown" sentinel entry.
  EXPECT_EQ(list[5].tag_, 65535);
  ExpectCStrEq(list[5].name_, "(UnknownIopTag)");
  ExpectCStrEq(list[5].title_, "Unknown Exif Interoperability tag");
  ASSERT_NE(list[5].desc_, nullptr);

  EXPECT_EQ(list[5].ifdId_, Exiv2::IfdId::iopId);
  EXPECT_EQ(list[5].sectionId_, Exiv2::SectionId::iopTags);
  EXPECT_EQ(list[5].typeId_, Exiv2::asciiString);
  EXPECT_EQ(list[5].count_, -1);
}