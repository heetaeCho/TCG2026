// File: test_tags_exifkey_key_1336.cpp
// Unit tests for Exiv2::ExifKey::key() (black-box via public interface)

#include <gtest/gtest.h>

#include <string>

#include "exiv2/tags.hpp"

namespace {

class ExifKeyTest_1336 : public ::testing::Test {};

TEST_F(ExifKeyTest_1336, KeyReturnsOriginalStringFromStringCtor_1336) {
  const std::string input = "Exif.Image.Make";
  Exiv2::ExifKey key(input);

  const std::string first = key.key();
  const std::string second = key.key();

  EXPECT_EQ(first, input);
  EXPECT_EQ(second, input);
  EXPECT_EQ(first, second);
}

TEST_F(ExifKeyTest_1336, KeySupportsEmptyString_1336) {
  const std::string input;
  Exiv2::ExifKey key(input);

  EXPECT_EQ(key.key(), input);
}

TEST_F(ExifKeyTest_1336, CopyConstructorPreservesKey_1336) {
  Exiv2::ExifKey original("Exif.Photo.DateTimeOriginal");
  Exiv2::ExifKey copy(original);

  EXPECT_EQ(copy.key(), original.key());
}

TEST_F(ExifKeyTest_1336, AssignmentOperatorPreservesKey_1336) {
  Exiv2::ExifKey lhs("Exif.Image.Model");
  Exiv2::ExifKey rhs("Exif.Photo.FNumber");

  lhs = rhs;

  EXPECT_EQ(lhs.key(), rhs.key());
}

TEST_F(ExifKeyTest_1336, ClonePreservesKey_1336) {
  Exiv2::ExifKey original("Exif.Image.Software");

  auto cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Use only the public Key interface (virtual key()).
  EXPECT_EQ(cloned->key(), original.key());
}

TEST_F(ExifKeyTest_1336, KeyHandlesLongString_1336) {
  std::string longKey = "Exif.Custom.";
  longKey.append(4096, 'A');

  Exiv2::ExifKey key(longKey);
  EXPECT_EQ(key.key(), longKey);
}

}  // namespace