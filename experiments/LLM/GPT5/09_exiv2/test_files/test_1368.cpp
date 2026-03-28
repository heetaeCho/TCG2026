// =================================================================================================
//  Exiv2::Internal::tagInfo unit tests
//  File: ./TestProjects/exiv2/src/tags_int.cpp
//
//  TEST_ID: 1368
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

#include <string>

// Forward declarations (the implementation is in the production codebase).
namespace Exiv2 {
namespace Internal {
const TagInfo* tagInfo(const std::string& tagName, IfdId ifdId);
const TagInfo* tagList(IfdId ifdId);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class TagInfoTest_1368 : public ::testing::Test {};

TEST_F(TagInfoTest_1368, EmptyTagNameReturnsNullptr_1368) {
  // Observable behavior from provided interface: empty tagName => nullptr.
  const auto* ti = Exiv2::Internal::tagInfo(std::string{}, Exiv2::ifd0Id);
  EXPECT_EQ(ti, nullptr);
}

TEST_F(TagInfoTest_1368, UnknownTagNameReturnsNullptr_1368) {
  // If a tag name is not present for the given IFD, result should be nullptr.
  // Use a very unlikely name to avoid depending on specific tag catalogs.
  const std::string unknown = "THIS_TAG_NAME_SHOULD_NOT_EXIST__TEST_1368";

  const auto* ti = Exiv2::Internal::tagInfo(unknown, Exiv2::ifd0Id);
  EXPECT_EQ(ti, nullptr);
}

TEST_F(TagInfoTest_1368, KnownFirstEntryNameReturnsPointerToThatEntry_1368) {
  // Use tagList(ifdId) only to obtain stable test data (a known tag name),
  // without inferring internal logic beyond observable pointer identity.
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(Exiv2::ifd0Id);
  ASSERT_NE(list, nullptr) << "tagList(ifd0Id) returned nullptr; cannot derive a known tag name.";

  // In Exiv2, TagInfo entries include a C-string name_.
  ASSERT_NE(list[0].name_, nullptr);
  const std::string name0(list[0].name_);
  ASSERT_FALSE(name0.empty());

  const Exiv2::TagInfo* found = Exiv2::Internal::tagInfo(name0, Exiv2::ifd0Id);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, &list[0]) << "Expected tagInfo to return the address of the matching entry.";
}

TEST_F(TagInfoTest_1368, KnownSecondEntryNameReturnsPointerToThatEntry_1368) {
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(Exiv2::ifd0Id);
  ASSERT_NE(list, nullptr) << "tagList(ifd0Id) returned nullptr; cannot derive a known tag name.";

  // Be defensive in case a minimal build has an unusually small tag list.
  // (We do not inspect any terminator fields; we only check for a usable second name_.)
  if (list[1].name_ == nullptr) {
    GTEST_SKIP() << "Second entry name_ is null; cannot form a stable test case in this build.";
  }
  const std::string name1(list[1].name_);
  if (name1.empty()) {
    GTEST_SKIP() << "Second entry name_ is empty; cannot form a stable test case in this build.";
  }

  const Exiv2::TagInfo* found = Exiv2::Internal::tagInfo(name1, Exiv2::ifd0Id);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, &list[1]) << "Expected tagInfo to return the address of the matching entry.";
}

TEST_F(TagInfoTest_1368, EmptyTagNameReturnsNullptrForAnotherIfd_1368) {
  // Boundary/robustness: same empty-name rule should hold regardless of ifdId.
  const auto* ti = Exiv2::Internal::tagInfo("", Exiv2::exifId);
  EXPECT_EQ(ti, nullptr);
}

}  // namespace