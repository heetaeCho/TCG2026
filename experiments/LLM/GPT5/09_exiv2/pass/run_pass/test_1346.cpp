// ============================================================================
// TEST_ID: 1346
// File: test_exifkey_idx_1346.cpp
// Unit tests for Exiv2::ExifKey::idx() (and observable interactions via setIdx)
// ============================================================================

#include <gtest/gtest.h>

#include <climits>
#include <cstdint>
#include <string>

#include "exiv2/tags.hpp"

namespace {

// Keep a dedicated fixture name that includes the TEST_ID.
class ExifKeyTest_1346 : public ::testing::Test {};

TEST_F(ExifKeyTest_1346, DefaultIdxIsZero_ForStringConstructor_1346) {
  Exiv2::ExifKey key(std::string("Exif.Photo.DateTimeOriginal"));
  EXPECT_EQ(0, key.idx());
}

TEST_F(ExifKeyTest_1346, DefaultIdxIsZero_ForTagGroupConstructor_1346) {
  Exiv2::ExifKey key(static_cast<uint16_t>(0x0132), std::string("Exif.Image"));
  EXPECT_EQ(0, key.idx());
}

TEST_F(ExifKeyTest_1346, SetIdxUpdatesIdx_NormalValue_1346) {
  Exiv2::ExifKey key(std::string("Exif.Photo.DateTimeOriginal"));

  key.setIdx(7);
  EXPECT_EQ(7, key.idx());

  key.setIdx(0);
  EXPECT_EQ(0, key.idx());
}

TEST_F(ExifKeyTest_1346, SetIdxUpdatesIdx_NegativeValue_1346) {
  Exiv2::ExifKey key(std::string("Exif.Photo.DateTimeOriginal"));

  key.setIdx(-1);
  EXPECT_EQ(-1, key.idx());

  key.setIdx(-12345);
  EXPECT_EQ(-12345, key.idx());
}

TEST_F(ExifKeyTest_1346, SetIdxHandlesLargeValues_NoThrow_1346) {
  Exiv2::ExifKey key(std::string("Exif.Photo.DateTimeOriginal"));

  EXPECT_NO_THROW(key.setIdx(INT_MAX));
  (void)key.idx();

  EXPECT_NO_THROW(key.setIdx(INT_MIN));
  (void)key.idx();
}

TEST_F(ExifKeyTest_1346, CopyConstructorCopiesIdx_1346) {
  Exiv2::ExifKey original(std::string("Exif.Photo.DateTimeOriginal"));
  original.setIdx(42);

  Exiv2::ExifKey copied(original);
  EXPECT_EQ(42, copied.idx());

  // Mutating the copy should not require assumptions about aliasing;
  // we only verify the copy reflects its own observable state after mutation.
  copied.setIdx(100);
  EXPECT_EQ(100, copied.idx());
}

TEST_F(ExifKeyTest_1346, AssignmentOperatorCopiesIdx_1346) {
  Exiv2::ExifKey rhs(std::string("Exif.Photo.DateTimeOriginal"));
  rhs.setIdx(9);

  Exiv2::ExifKey lhs(std::string("Exif.Image.Make"));
  lhs.setIdx(1);
  ASSERT_EQ(1, lhs.idx());

  lhs = rhs;
  EXPECT_EQ(9, lhs.idx());
}

TEST_F(ExifKeyTest_1346, SelfAssignmentKeepsIdx_1346) {
  Exiv2::ExifKey key(std::string("Exif.Photo.DateTimeOriginal"));
  key.setIdx(55);
  ASSERT_EQ(55, key.idx());

  key = key;
  EXPECT_EQ(55, key.idx());
}

}  // namespace