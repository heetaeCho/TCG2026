// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 775
//
// Unit tests for Exiv2::ExifData::operator[](const std::string&)
// File under test: ./TestProjects/exiv2/src/exif.cpp

#include <gtest/gtest.h>

#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/tags.hpp"

namespace {

class ExifDataTest_775 : public ::testing::Test {
 protected:
  Exiv2::ExifData data_;
};

TEST_F(ExifDataTest_775, StartsEmpty_775) {
  EXPECT_TRUE(data_.empty());
  EXPECT_EQ(data_.count(), 0u);
  EXPECT_EQ(data_.begin(), data_.end());
}

TEST_F(ExifDataTest_775, OperatorBracketInsertsWhenMissing_775) {
  const std::string keyStr = "Exif.Image.Make";
  Exiv2::ExifKey key(keyStr);

  EXPECT_EQ(data_.findKey(key), data_.end());
  EXPECT_TRUE(data_.empty());
  EXPECT_EQ(data_.count(), 0u);

  Exiv2::Exifdatum& d = data_[keyStr];
  (void)d;

  EXPECT_FALSE(data_.empty());
  EXPECT_EQ(data_.count(), 1u);
  EXPECT_NE(data_.findKey(key), data_.end());
}

TEST_F(ExifDataTest_775, OperatorBracketReturnsExistingWhenPresent_775) {
  const std::string keyStr = "Exif.Image.Model";
  Exiv2::ExifKey key(keyStr);

  Exiv2::Exifdatum& first = data_[keyStr];
  ASSERT_EQ(data_.count(), 1u);
  ASSERT_NE(data_.findKey(key), data_.end());

  Exiv2::Exifdatum& second = data_[keyStr];

  // Observable behavior: accessing same key again should not create a new entry.
  EXPECT_EQ(data_.count(), 1u);

  // Also observable: returned reference should refer to the same datum.
  EXPECT_EQ(&first, &second);
}

TEST_F(ExifDataTest_775, MultipleDifferentKeysIncreaseCount_775) {
  const std::string k1 = "Exif.Image.Make";
  const std::string k2 = "Exif.Image.Model";
  const std::string k3 = "Exif.Photo.DateTimeOriginal";

  (void)data_[k1];
  EXPECT_EQ(data_.count(), 1u);

  (void)data_[k2];
  EXPECT_EQ(data_.count(), 2u);

  (void)data_[k3];
  EXPECT_EQ(data_.count(), 3u);

  // Re-access should not increase.
  (void)data_[k2];
  EXPECT_EQ(data_.count(), 3u);
}

TEST_F(ExifDataTest_775, FindKeyTransitionsFromMissingToPresentAfterOperatorBracket_775) {
  const std::string keyStr = "Exif.Photo.ExposureTime";
  Exiv2::ExifKey key(keyStr);

  EXPECT_EQ(data_.findKey(key), data_.end());
  (void)data_[keyStr];
  EXPECT_NE(data_.findKey(key), data_.end());
}

TEST_F(ExifDataTest_775, OperatorBracketWithPotentiallyInvalidKeyEitherThrowsOrInserts_775) {
  // We do not assume the ExifKey parsing/validation rules.
  // This test verifies observable behavior in either case:
  // - If an exception is thrown, container remains unchanged.
  // - If no exception is thrown, an element becomes accessible.
  const std::string maybeInvalid = "InvalidKeyFormat";

  const size_t beforeCount = data_.count();

  try {
    Exiv2::Exifdatum& d = data_[maybeInvalid];
    (void)d;

    // If it didn't throw, it must have produced a datum and count is >= beforeCount.
    EXPECT_GE(data_.count(), beforeCount);
    EXPECT_FALSE(data_.empty());
  } catch (...) {
    // If it throws, ExifData should not have been modified (strong-ish observable expectation).
    EXPECT_EQ(data_.count(), beforeCount);
  }
}

TEST_F(ExifDataTest_775, OperatorBracketWithEmptyStringEitherThrowsOrInserts_775) {
  const std::string emptyKey;

  const size_t beforeCount = data_.count();

  try {
    Exiv2::Exifdatum& d = data_[emptyKey];
    (void)d;

    EXPECT_GE(data_.count(), beforeCount);
  } catch (...) {
    EXPECT_EQ(data_.count(), beforeCount);
  }
}

TEST_F(ExifDataTest_775, OperatorBracketWithEmbeddedNullEitherThrowsOrInserts_775) {
  // Boundary: strings may contain embedded NULs.
  std::string keyWithNull = std::string("Exif.Image.Make") + '\0' + "Trailing";
  const size_t beforeCount = data_.count();

  try {
    Exiv2::Exifdatum& d = data_[keyWithNull];
    (void)d;
    EXPECT_GE(data_.count(), beforeCount);
  } catch (...) {
    EXPECT_EQ(data_.count(), beforeCount);
  }
}

}  // namespace