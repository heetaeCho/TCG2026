// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifkey_tag_1343.cpp

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

#include <cstdint>
#include <limits>
#include <memory>
#include <string>

namespace {

// Focused fixture for Exiv2::ExifKey::tag() observable behavior.
class ExifKeyTest_1343 : public ::testing::Test {
 protected:
  static constexpr const char* kGroupName = "Exif.Image";
};

TEST_F(ExifKeyTest_1343, TagReturnsConstructorTagValue_1343) {
  const uint16_t tag = 0x1234;
  Exiv2::ExifKey key(tag, std::string(kGroupName));

  EXPECT_EQ(key.tag(), tag);
}

TEST_F(ExifKeyTest_1343, TagBoundaryZero_1343) {
  const uint16_t tag = 0;
  Exiv2::ExifKey key(tag, std::string(kGroupName));

  EXPECT_EQ(key.tag(), tag);
}

TEST_F(ExifKeyTest_1343, TagBoundaryMaxUint16_1343) {
  const uint16_t tag = std::numeric_limits<uint16_t>::max();
  Exiv2::ExifKey key(tag, std::string(kGroupName));

  EXPECT_EQ(key.tag(), tag);
}

TEST_F(ExifKeyTest_1343, TagIndependentOfGroupName_1343) {
  const uint16_t tag = 0x00AB;

  Exiv2::ExifKey keyA(tag, std::string("Exif.Image"));
  Exiv2::ExifKey keyB(tag, std::string("Exif.Photo"));
  Exiv2::ExifKey keyC(tag, std::string("Some.Custom.Group"));

  EXPECT_EQ(keyA.tag(), tag);
  EXPECT_EQ(keyB.tag(), tag);
  EXPECT_EQ(keyC.tag(), tag);
}

TEST_F(ExifKeyTest_1343, CopyConstructorPreservesTag_1343) {
  const uint16_t tag = 0xBEEF;
  Exiv2::ExifKey original(tag, std::string(kGroupName));

  Exiv2::ExifKey copy(original);

  EXPECT_EQ(copy.tag(), original.tag());
  EXPECT_EQ(copy.tag(), tag);
}

TEST_F(ExifKeyTest_1343, CopyAssignmentPreservesTag_1343) {
  Exiv2::ExifKey lhs(static_cast<uint16_t>(0x0001), std::string(kGroupName));
  Exiv2::ExifKey rhs(static_cast<uint16_t>(0x2222), std::string(kGroupName));

  lhs = rhs;

  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.tag(), static_cast<uint16_t>(0x2222));
}

TEST_F(ExifKeyTest_1343, SelfAssignmentDoesNotChangeTag_1343) {
  const uint16_t tag = 0x0F0F;
  Exiv2::ExifKey key(tag, std::string(kGroupName));

  key = key;

  EXPECT_EQ(key.tag(), tag);
}

TEST_F(ExifKeyTest_1343, CloneProducesKeyWithSameTag_1343) {
  const uint16_t tag = 0x1357;
  Exiv2::ExifKey key(tag, std::string(kGroupName));

  // clone() is part of the public interface; verify observable equality via tag().
  Exiv2::ExifKey::UniquePtr cloned = key.clone();
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_EQ(cloned->tag(), key.tag());
  EXPECT_EQ(cloned->tag(), tag);
}

}  // namespace