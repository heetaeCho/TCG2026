// =================================================================================================
// TEST_ID: 1331
// File: test_exifkey_impl_tagname_1331.cpp
// Unit tests for Exiv2::ExifKey::Impl::tagName() / tagName() const
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/tags.hpp"

// NOTE:
// - These tests treat Exiv2::ExifKey::Impl as a black box and only validate observable results
//   from its public interface.
// - The implementation under test uses TagInfo::tag_ and TagInfo::name_, which are expected to
//   exist in the real Exiv2 TagInfo definition (even if not shown in the truncated snippet).

namespace {

class ExifKeyImplTagNameTest_1331 : public ::testing::Test {
 protected:
  // Helper to create a TagInfo with the fields used by ExifKey::Impl::tagName().
  // (Other fields are left default-initialized.)
  static Exiv2::TagInfo MakeTagInfo(uint16_t tag, const char* name) {
    Exiv2::TagInfo ti{};
    ti.tag_ = tag;
    ti.name_ = name;
    return ti;
  }
};

}  // namespace

TEST_F(ExifKeyImplTagNameTest_1331, ReturnsHexWhenTagInfoIsNull_1331) {
  Exiv2::ExifKey::Impl impl;
  impl.tagInfo_ = nullptr;
  impl.tag_ = 0x0000;

  const std::string s1 = impl.tagName();
  const std::string s2 = static_cast<const Exiv2::ExifKey::Impl&>(impl).tagName();

  EXPECT_EQ(s1, "0x0000");
  EXPECT_EQ(s2, "0x0000");
}

TEST_F(ExifKeyImplTagNameTest_1331, ReturnsLowercaseFourDigitHexFormatting_1331) {
  Exiv2::ExifKey::Impl impl;
  impl.tagInfo_ = nullptr;
  impl.tag_ = 0xABCD;

  const std::string s = static_cast<const Exiv2::ExifKey::Impl&>(impl).tagName();
  EXPECT_EQ(s, "0xabcd");  // expects "{:04x}" formatting (lowercase, width 4)
}

TEST_F(ExifKeyImplTagNameTest_1331, ReturnsTagInfoNameWhenTagInfoPresentAndTagNotFFFF_1331) {
  Exiv2::TagInfo ti = MakeTagInfo(/*tag=*/0x0102, /*name=*/"MyTagName");
  Exiv2::ExifKey::Impl impl;

  impl.tag_ = 0x9999;      // should be ignored in this branch
  impl.tagInfo_ = &ti;

  const std::string s1 = impl.tagName();
  const std::string s2 = static_cast<const Exiv2::ExifKey::Impl&>(impl).tagName();

  EXPECT_EQ(s1, "MyTagName");
  EXPECT_EQ(s2, "MyTagName");
}

TEST_F(ExifKeyImplTagNameTest_1331, ReturnsHexWhenTagInfoTagIsFFFFEvenIfNameProvided_1331) {
  Exiv2::TagInfo ti = MakeTagInfo(/*tag=*/0xFFFF, /*name=*/"ShouldNotBeReturned");
  Exiv2::ExifKey::Impl impl;

  impl.tag_ = 0x0001;
  impl.tagInfo_ = &ti;

  const std::string s1 = impl.tagName();
  const std::string s2 = static_cast<const Exiv2::ExifKey::Impl&>(impl).tagName();

  EXPECT_EQ(s1, "0x0001");
  EXPECT_EQ(s2, "0x0001");
}

TEST_F(ExifKeyImplTagNameTest_1331, BoundaryTagValueFFFFWithNullTagInfo_1331) {
  Exiv2::ExifKey::Impl impl;
  impl.tagInfo_ = nullptr;
  impl.tag_ = 0xFFFF;

  const std::string s = static_cast<const Exiv2::ExifKey::Impl&>(impl).tagName();
  EXPECT_EQ(s, "0xffff");
}

TEST_F(ExifKeyImplTagNameTest_1331, SwitchingTagInfoPointerChangesObservedResult_1331) {
  Exiv2::TagInfo ti = MakeTagInfo(/*tag=*/0x0002, /*name=*/"Two");
  Exiv2::ExifKey::Impl impl;

  impl.tag_ = 0x0002;

  // First: no tagInfo => formatted hex.
  impl.tagInfo_ = nullptr;
  EXPECT_EQ(impl.tagName(), "0x0002");

  // Then: provide tagInfo with tag != 0xffff => name.
  impl.tagInfo_ = &ti;
  EXPECT_EQ(impl.tagName(), "Two");

  // Finally: remove tagInfo again => back to formatted hex.
  impl.tagInfo_ = nullptr;
  EXPECT_EQ(impl.tagName(), "0x0002");
}