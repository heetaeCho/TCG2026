// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for Exiv2::ExifKey::tagDesc()
// File under test: ./TestProjects/exiv2/src/tags.cpp (partial)
//
// Constraints honored:
// - Treat implementation as black box (assert only observable behavior via public API)
// - No private state access
// - No re-implementation of logic

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>  // Exiv2::ExifKey, Exiv2::TagInfo, enums/types used by TagInfo
#include <string>

namespace {

// TEST_ID = 1341
class ExifKeyTagDescTest_1341 : public ::testing::Test {
 protected:
  // Build a TagInfo suitable for exercising ExifKey(TagInfo) + tagDesc().
  // We only set the fields we need for observable behavior in these tests.
  static Exiv2::TagInfo MakeTagInfo(uint16_t tag, const char* desc) {
    Exiv2::TagInfo ti{};
    // These members exist in Exiv2's real TagInfo (the prompt shows a truncated excerpt).
    ti.tag_ = tag;
    ti.desc_ = desc;

    // Keep other fields default-initialized; tests do not depend on them.
    return ti;
  }
};

}  // namespace

// Normal / boundary: if TagInfo.tag_ is 0xffff, tagDesc() should be empty.
TEST_F(ExifKeyTagDescTest_1341, TagDesc_EmptyWhenTagIsFFFF_1341) {
  const auto ti = MakeTagInfo(/*tag=*/0xffffu, /*desc=*/"any desc");
  Exiv2::ExifKey key(ti);

  const std::string desc = key.tagDesc();
  EXPECT_TRUE(desc.empty());
}

// Normal: for a "valid" tag with a non-empty desc string, tagDesc() should be non-empty.
TEST_F(ExifKeyTagDescTest_1341, TagDesc_NonEmptyForValidTagWithNonEmptyDesc_1341) {
  const auto ti = MakeTagInfo(/*tag=*/0x0001u, /*desc=*/"Some description");
  Exiv2::ExifKey key(ti);

  const std::string desc = key.tagDesc();
  EXPECT_FALSE(desc.empty());
}

// Boundary: if desc is an empty C-string, tagDesc() should be empty (or at least not become non-empty).
TEST_F(ExifKeyTagDescTest_1341, TagDesc_EmptyWhenDescIsEmptyString_1341) {
  const auto ti = MakeTagInfo(/*tag=*/0x0002u, /*desc=*/"");
  Exiv2::ExifKey key(ti);

  const std::string desc = key.tagDesc();
  EXPECT_TRUE(desc.empty());
}

// Normal: copy construction preserves observable tagDesc() behavior.
TEST_F(ExifKeyTagDescTest_1341, TagDesc_CopyConstructorPreservesResult_1341) {
  const auto ti = MakeTagInfo(/*tag=*/0x0003u, /*desc=*/"Copy me");
  Exiv2::ExifKey original(ti);

  const Exiv2::ExifKey copy(original);

  EXPECT_EQ(copy.tagDesc(), original.tagDesc());
}

// Normal: copy assignment preserves observable tagDesc() behavior.
TEST_F(ExifKeyTagDescTest_1341, TagDesc_CopyAssignmentPreservesResult_1341) {
  const auto ti1 = MakeTagInfo(/*tag=*/0x0004u, /*desc=*/"Assigned");
  const auto ti2 = MakeTagInfo(/*tag=*/0xffffu, /*desc=*/"Other");  // different starting state

  Exiv2::ExifKey lhs(ti2);
  const Exiv2::ExifKey rhs(ti1);

  lhs = rhs;

  EXPECT_EQ(lhs.tagDesc(), rhs.tagDesc());
}

// Normal: clone() preserves observable tagDesc() behavior via the polymorphic Key interface.
TEST_F(ExifKeyTagDescTest_1341, TagDesc_ClonePreservesResult_1341) {
  const auto ti = MakeTagInfo(/*tag=*/0x0005u, /*desc=*/"Cloned");
  Exiv2::ExifKey key(ti);

  auto cloned = key.clone();
  ASSERT_TRUE(cloned.get() != nullptr);

  EXPECT_EQ(cloned->tagDesc(), key.tagDesc());
}