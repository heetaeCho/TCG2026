// TEST_ID 1660
//
// Unit tests for Exiv2::Internal::findTag (tiffvisitor_int.cpp)
//
// Notes:
// - findTag has internal linkage (static in .cpp), so we include the .cpp to test it
//   without re-implementing its logic.
// - Tests only validate observable behavior via return values.

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "exiv2/tags.hpp"

// Include the implementation file to access the internal static function under test.
#include "tiffvisitor_int.cpp"

namespace {

using Exiv2::TagInfo;

TagInfo MakeTagInfo(uint16_t tag) {
  TagInfo ti{};
  ti.tag_ = tag;
  return ti;
}

TagInfo MakeSentinel() {
  return MakeTagInfo(static_cast<uint16_t>(0xffff));
}

class FindTagTest_1660 : public ::testing::Test {};

}  // namespace

TEST_F(FindTagTest_1660, ReturnsPointerWhenTagIsFirstElement_1660) {
  std::vector<TagInfo> list;
  list.push_back(MakeTagInfo(0x0001));
  list.push_back(MakeTagInfo(0x0002));
  list.push_back(MakeSentinel());

  const TagInfo* found = Exiv2::Internal::findTag(list.data(), static_cast<uint16_t>(0x0001));
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, &list[0]);
  EXPECT_EQ(found->tag_, 0x0001);
}

TEST_F(FindTagTest_1660, ReturnsPointerWhenTagIsInMiddle_1660) {
  std::vector<TagInfo> list;
  list.push_back(MakeTagInfo(0x0100));
  list.push_back(MakeTagInfo(0x0101));
  list.push_back(MakeTagInfo(0x0102));
  list.push_back(MakeSentinel());

  const TagInfo* found = Exiv2::Internal::findTag(list.data(), static_cast<uint16_t>(0x0101));
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, &list[1]);
  EXPECT_EQ(found->tag_, 0x0101);
}

TEST_F(FindTagTest_1660, ReturnsPointerWhenTagIsLastBeforeSentinel_1660) {
  std::vector<TagInfo> list;
  list.push_back(MakeTagInfo(0x1000));
  list.push_back(MakeTagInfo(0x1001));
  list.push_back(MakeTagInfo(0x1002));
  list.push_back(MakeSentinel());

  const TagInfo* found = Exiv2::Internal::findTag(list.data(), static_cast<uint16_t>(0x1002));
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, &list[2]);
  EXPECT_EQ(found->tag_, 0x1002);
}

TEST_F(FindTagTest_1660, ReturnsNullWhenTagNotFound_1660) {
  std::vector<TagInfo> list;
  list.push_back(MakeTagInfo(0x2000));
  list.push_back(MakeTagInfo(0x2001));
  list.push_back(MakeSentinel());

  const TagInfo* found = Exiv2::Internal::findTag(list.data(), static_cast<uint16_t>(0x2002));
  EXPECT_EQ(found, nullptr);
}

TEST_F(FindTagTest_1660, ReturnsNullWhenListIsOnlySentinel_1660) {
  std::vector<TagInfo> list;
  list.push_back(MakeSentinel());

  const TagInfo* found = Exiv2::Internal::findTag(list.data(), static_cast<uint16_t>(0x0001));
  EXPECT_EQ(found, nullptr);
}

TEST_F(FindTagTest_1660, ReturnsNullWhenSearchingForSentinelTagValue_1660) {
  std::vector<TagInfo> list;
  list.push_back(MakeTagInfo(0x0001));
  list.push_back(MakeTagInfo(0x0002));
  list.push_back(MakeSentinel());

  const TagInfo* found = Exiv2::Internal::findTag(list.data(), static_cast<uint16_t>(0xffff));
  EXPECT_EQ(found, nullptr);
}