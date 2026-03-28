// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Include the implementation directly so the internal-linkage (static) function
// is visible in this translation unit.
#include "minoltamn_int.cpp"

namespace {

// Test fixture (kept minimal; no reliance on internals)
class GetKeyLongTest_1012 : public ::testing::Test {};

TEST_F(GetKeyLongTest_1012, MissingKeyReturnsMinusOne_1012) {
  Exiv2::ExifData data;

  const long v = Exiv2::Internal::getKeyLong("Exif.Photo.ISOSpeedRatings", &data, 0);
  EXPECT_EQ(-1L, v);
}

TEST_F(GetKeyLongTest_1012, FoundKeyReturnsConvertedLong_1012) {
  Exiv2::ExifData data;

  // Use public ExifData/Exifdatum interface only.
  data["Exif.Photo.ISOSpeedRatings"] = static_cast<uint32_t>(400);

  const long v = Exiv2::Internal::getKeyLong("Exif.Photo.ISOSpeedRatings", &data, 0);
  EXPECT_EQ(400L, v);
}

TEST_F(GetKeyLongTest_1012, FoundKeyNegativeValuePreservedAfterConversion_1012) {
  Exiv2::ExifData data;

  data["Exif.Photo.BrightnessValue"] = static_cast<int32_t>(-42);

  const long v = Exiv2::Internal::getKeyLong("Exif.Photo.BrightnessValue", &data, 0);
  EXPECT_EQ(-42L, v);
}

TEST_F(GetKeyLongTest_1012, WhichSelectsNthComponentWhenValueHasMultipleItems_1012) {
  Exiv2::ExifData data;

  // Create a multi-value entry using Exiv2's public Value API.
  // (We don't assume internal storage—only that Exifdatum::toFloat(which) is observable.)
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_TRUE(static_cast<bool>(val));
  ASSERT_EQ(0, val->read("10 20"));

  data.add(Exiv2::ExifKey("Exif.Photo.ISOSpeedRatings"), val.get());

  EXPECT_EQ(10L, Exiv2::Internal::getKeyLong("Exif.Photo.ISOSpeedRatings", &data, 0));
  EXPECT_EQ(20L, Exiv2::Internal::getKeyLong("Exif.Photo.ISOSpeedRatings", &data, 1));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GetKeyLongTest_1012, NullMetadataPointerCausesDeath_1012) {
  // The interface accepts a pointer; passing nullptr is an observable error case.
  ASSERT_DEATH((void)Exiv2::Internal::getKeyLong("Exif.Photo.ISOSpeedRatings", nullptr, 0), "");
}
#endif

}  // namespace