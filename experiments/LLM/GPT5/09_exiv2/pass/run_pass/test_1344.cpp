// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_exifkey_clone_1344.cpp
//
// Tests for Exiv2::ExifKey::clone() (black-box via public interface)

#include <gtest/gtest.h>

#include <climits>
#include <memory>
#include <string>

#include "exiv2/tags.hpp"

namespace {

class ExifKeyTest_1344 : public ::testing::Test {
 protected:
  static void ExpectPublicIdentityEqual(const Exiv2::ExifKey& a, const Exiv2::ExifKey& b) {
    // Compare only observable public interface outputs (no assumptions about formatting/content).
    EXPECT_EQ(a.key(), b.key());
    EXPECT_STREQ(a.familyName(), b.familyName());
    EXPECT_EQ(a.groupName(), b.groupName());
    EXPECT_EQ(a.tagName(), b.tagName());
    EXPECT_EQ(a.tagLabel(), b.tagLabel());
    EXPECT_EQ(a.tagDesc(), b.tagDesc());
    EXPECT_EQ(a.tag(), b.tag());
    EXPECT_EQ(a.defaultTypeId(), b.defaultTypeId());
    EXPECT_EQ(a.ifdId(), b.ifdId());
    EXPECT_EQ(a.idx(), b.idx());
  }
};

TEST_F(ExifKeyTest_1344, CloneFromStringKey_ReturnsNonNullAndMatchesPublicState_1344) {
  const Exiv2::ExifKey original(std::string("Exif.Image.Make"));

  auto cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Should be a different object instance.
  EXPECT_NE(cloned.get(), &original);

  ExpectPublicIdentityEqual(original, *cloned);
}

TEST_F(ExifKeyTest_1344, CloneFromTagAndGroup_ReturnsNonNullAndMatchesPublicState_1344) {
  const Exiv2::ExifKey original(static_cast<uint16_t>(0x010F), std::string("Image"));

  auto cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);

  EXPECT_NE(cloned.get(), &original);
  ExpectPublicIdentityEqual(original, *cloned);
}

TEST_F(ExifKeyTest_1344, ClonePreservesIdxForTypicalValues_1344) {
  Exiv2::ExifKey original(std::string("Exif.Photo.FNumber"));

  original.setIdx(0);
  {
    auto c0 = original.clone();
    ASSERT_NE(c0.get(), nullptr);
    EXPECT_EQ(c0->idx(), original.idx());
  }

  original.setIdx(7);
  {
    auto c7 = original.clone();
    ASSERT_NE(c7.get(), nullptr);
    EXPECT_EQ(c7->idx(), original.idx());
  }
}

TEST_F(ExifKeyTest_1344, CloneHandlesIdxBoundaryValues_1344) {
  Exiv2::ExifKey original(std::string("Exif.Photo.ExposureTime"));

  original.setIdx(-1);
  {
    auto cneg = original.clone();
    ASSERT_NE(cneg.get(), nullptr);
    EXPECT_EQ(cneg->idx(), original.idx());
  }

  original.setIdx(INT_MAX);
  {
    auto cmax = original.clone();
    ASSERT_NE(cmax.get(), nullptr);
    EXPECT_EQ(cmax->idx(), original.idx());
  }

  original.setIdx(INT_MIN);
  {
    auto cmin = original.clone();
    ASSERT_NE(cmin.get(), nullptr);
    EXPECT_EQ(cmin->idx(), original.idx());
  }
}

TEST_F(ExifKeyTest_1344, CloneIsUnaffectedBySubsequentOriginalMutation_1344) {
  Exiv2::ExifKey original(std::string("Exif.Image.Model"));
  original.setIdx(1);

  auto cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);
  ExpectPublicIdentityEqual(original, *cloned);

  // Mutate the original after cloning; clone should remain stable via public interface.
  // (This is an observable contract test; no internal assumptions beyond public results.)
  original.setIdx(99);

  EXPECT_NE(cloned->idx(), original.idx());
}

TEST_F(ExifKeyTest_1344, CloneOfCopyConstructedObject_MatchesPublicState_1344) {
  Exiv2::ExifKey base(std::string("Exif.Image.Artist"));
  base.setIdx(3);

  const Exiv2::ExifKey copy(base);
  auto cloned = copy.clone();

  ASSERT_NE(cloned.get(), nullptr);
  EXPECT_NE(cloned.get(), &copy);

  ExpectPublicIdentityEqual(copy, *cloned);
}

TEST_F(ExifKeyTest_1344, CloneAfterAssignment_MatchesPublicState_1344) {
  Exiv2::ExifKey a(std::string("Exif.Image.Copyright"));
  a.setIdx(2);

  Exiv2::ExifKey b(std::string("Exif.Image.Software"));
  b.setIdx(8);

  b = a;

  auto cloned = b.clone();
  ASSERT_NE(cloned.get(), nullptr);

  ExpectPublicIdentityEqual(b, *cloned);
}

TEST_F(ExifKeyTest_1344, CloneWithEmptyKeyString_DoesNotThrowAndReturnsObject_1344) {
  // We do not assume whether empty is "valid" semantically; we only check observable behavior:
  // construction succeeds here (if it throws in some builds, this test will reveal it).
  Exiv2::ExifKey original(std::string(""));

  EXPECT_NO_THROW({
    auto cloned = original.clone();
    ASSERT_NE(cloned.get(), nullptr);
    ExpectPublicIdentityEqual(original, *cloned);
  });
}

TEST_F(ExifKeyTest_1344, CloneCanBeCalledMultipleTimes_ProducesIndependentObjects_1344) {
  Exiv2::ExifKey original(std::string("Exif.Photo.ISOSpeedRatings"));
  original.setIdx(5);

  auto c1 = original.clone();
  auto c2 = original.clone();

  ASSERT_NE(c1.get(), nullptr);
  ASSERT_NE(c2.get(), nullptr);

  EXPECT_NE(c1.get(), &original);
  EXPECT_NE(c2.get(), &original);
  EXPECT_NE(c1.get(), c2.get());

  ExpectPublicIdentityEqual(original, *c1);
  ExpectPublicIdentityEqual(original, *c2);
}

}  // namespace