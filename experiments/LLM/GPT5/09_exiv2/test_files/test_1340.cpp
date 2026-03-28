// =================================================================================================
// Exiv2 unit tests for ExifKey::tagLabel()
// File: test_exifkey_taglabel_1340.cpp
//
// Constraints reminder:
// - Treat implementation as a black box.
// - Test only observable behavior via public interface.
// - No private state access.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>

#include "exiv2/tags.hpp"

namespace {

using Exiv2::ExifKey;
using Exiv2::TagInfo;

// ---- SFINAE helpers to detect optional TagInfo members (because provided snippet is partial) ----
template <typename T, typename = void>
struct has_member_tag_ : std::false_type {};
template <typename T>
struct has_member_tag_<T, std::void_t<decltype(std::declval<T&>().tag_)>> : std::true_type {};

template <typename T, typename = void>
struct has_member_title_ : std::false_type {};
template <typename T>
struct has_member_title_<T, std::void_t<decltype(std::declval<T&>().title_)>> : std::true_type {};

class ExifKeyTagLabelTest_1340 : public ::testing::Test {};

TEST_F(ExifKeyTagLabelTest_1340, TagLabel_DoesNotThrowForTypicalWellKnownTag_1340) {
  // Use a very common Exif tag in the "Image" IFD: 0x010F = "Make" (commonly present).
  // Observable requirement: tagLabel() should be callable and stable (no crash/throw).
  const ExifKey key(/*tag=*/0x010F, /*groupName=*/"Image");

  EXPECT_NO_THROW({
    const std::string label = key.tagLabel();
    (void)label;
  });
}

TEST_F(ExifKeyTagLabelTest_1340, TagLabel_IsStableAcrossRepeatedCalls_1340) {
  const ExifKey key(/*tag=*/0x0110, /*groupName=*/"Image");  // 0x0110 often "Model"

  const std::string a = key.tagLabel();
  const std::string b = key.tagLabel();
  EXPECT_EQ(a, b);
}

TEST_F(ExifKeyTagLabelTest_1340, TagLabel_PreservedByCopyConstructorAndAssignment_1340) {
  const ExifKey original(/*tag=*/0x0132, /*groupName=*/"Image");  // 0x0132 often "DateTime"

  const std::string origLabel = original.tagLabel();

  // Copy-construct
  const ExifKey copied(original);
  EXPECT_EQ(origLabel, copied.tagLabel());

  // Copy-assign
  ExifKey assigned(/*tag=*/0x010F, /*groupName=*/"Image");
  assigned = original;
  EXPECT_EQ(origLabel, assigned.tagLabel());
}

TEST_F(ExifKeyTagLabelTest_1340, TagLabel_UnchangedBySetIdxBoundaryValues_1340) {
  const ExifKey key(/*tag=*/0x010F, /*groupName=*/"Image");
  const std::string before = key.tagLabel();

  // Boundary-ish values; observable behavior: tagLabel unaffected.
  EXPECT_NO_THROW(key.setIdx(0));
  EXPECT_EQ(before, key.tagLabel());

  EXPECT_NO_THROW(key.setIdx(-1));
  EXPECT_EQ(before, key.tagLabel());

  EXPECT_NO_THROW(key.setIdx(std::numeric_limits<int>::max()));
  EXPECT_EQ(before, key.tagLabel());
}

TEST_F(ExifKeyTagLabelTest_1340, TagLabel_ReturnsEmptyWhenTagInfoHasSentinelTagIfSupported_1340) {
  // The implementation shows:
  //   if (!p_->tagInfo_ || p_->tagInfo_->tag_ == 0xffff) return "";
  //
  // We can only test the "tagInfo_->tag_ == 0xffff" path if TagInfo exposes tag_.
  if constexpr (!(has_member_tag_<TagInfo>::value && has_member_title_<TagInfo>::value)) {
    GTEST_SKIP() << "TagInfo does not expose expected members (tag_, title_) in this build; "
                    "cannot construct the sentinel TagInfo scenario.";
  } else {
    TagInfo ti{};
    ti.tag_ = 0xffff;
    ti.title_ = "SentinelTitleShouldNotMatter";

    const ExifKey key(ti);
    EXPECT_EQ(std::string(""), key.tagLabel());
  }
}

TEST_F(ExifKeyTagLabelTest_1340, TagLabel_ReturnsEmptyForLikelyUnknownKeyString_1340) {
  // If decomposeKey() can't resolve tagInfo_, tagLabel() should be empty per implementation.
  // We avoid assuming exact parsing rules: just supply a very unlikely-to-exist key.
  const ExifKey key(std::string("Exif.ThisGroupDoesNotExist.ThisTagDoesNotExist"));

  EXPECT_NO_THROW({
    const std::string label = key.tagLabel();
    // Observable expectation derived from tagLabel() contract: unresolved tagInfo => empty.
    // If upstream behavior differs (e.g., maps to something), this test may need adjustment.
    EXPECT_TRUE(label.empty());
  });
}

}  // namespace