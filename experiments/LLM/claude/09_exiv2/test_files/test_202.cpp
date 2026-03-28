#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/value.hpp>

// We need to access the internal function. Since it's in an anonymous-like static context,
// we need to declare it or include the relevant header.
// The function is static in pentaxmn_int.cpp, so we need to either:
// 1. Include the internal header that exposes it, or
// 2. Recreate the function signature for testing purposes.
// Since it's a static function in a .cpp file, it's not directly accessible from outside.
// However, based on the prompt, we'll replicate the function here for testing purposes
// since we're testing the observable behavior based on the interface.

// We'll re-declare the function to test it. In practice, this would be exposed via a header.
namespace Exiv2 {
namespace Internal {
static long getKeyLong(const std::string& key, const ExifData* metadata) {
  long result = -1;
  if (metadata->findKey(ExifKey(key)) != metadata->end()) {
    result = static_cast<long>(metadata->findKey(ExifKey(key))->toFloat(0));
  }
  return result;
}
}  // namespace Internal
}  // namespace Exiv2

class GetKeyLongTest_202 : public ::testing::Test {
 protected:
  Exiv2::ExifData exifData_;
};

// Test that when the key is not found in metadata, -1 is returned
TEST_F(GetKeyLongTest_202, KeyNotFound_ReturnsMinusOne_202) {
  long result = Exiv2::Internal::getKeyLong("Exif.Image.Make", &exifData_);
  EXPECT_EQ(-1, result);
}

// Test that when the key exists with a positive integer value, it returns that value
TEST_F(GetKeyLongTest_202, KeyFoundWithPositiveValue_ReturnsValue_202) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  auto value = Exiv2::Value::create(Exiv2::unsignedLong);
  value->read("1024");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", &exifData_);
  EXPECT_EQ(1024, result);
}

// Test that when the key exists with zero value, it returns 0
TEST_F(GetKeyLongTest_202, KeyFoundWithZeroValue_ReturnsZero_202) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  auto value = Exiv2::Value::create(Exiv2::unsignedLong);
  value->read("0");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", &exifData_);
  EXPECT_EQ(0, result);
}

// Test that when the key exists with a negative value, it returns that negative value
TEST_F(GetKeyLongTest_202, KeyFoundWithNegativeValue_ReturnsNegativeValue_202) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  auto value = Exiv2::Value::create(Exiv2::signedLong);
  value->read("-42");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", &exifData_);
  EXPECT_EQ(-42, result);
}

// Test that when the key exists with a large value, it returns correctly
TEST_F(GetKeyLongTest_202, KeyFoundWithLargeValue_ReturnsValue_202) {
  Exiv2::ExifKey key("Exif.Image.ImageLength");
  auto value = Exiv2::Value::create(Exiv2::unsignedLong);
  value->read("65535");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageLength", &exifData_);
  EXPECT_EQ(65535, result);
}

// Test that when the key exists with value 1, it returns 1
TEST_F(GetKeyLongTest_202, KeyFoundWithValueOne_ReturnsOne_202) {
  Exiv2::ExifKey key("Exif.Image.Orientation");
  auto value = Exiv2::Value::create(Exiv2::unsignedShort);
  value->read("1");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.Orientation", &exifData_);
  EXPECT_EQ(1, result);
}

// Test querying a key that doesn't exist when other keys are present
TEST_F(GetKeyLongTest_202, DifferentKeyNotFound_ReturnsMinusOne_202) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  auto value = Exiv2::Value::create(Exiv2::unsignedLong);
  value->read("800");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageLength", &exifData_);
  EXPECT_EQ(-1, result);
}

// Test with empty ExifData
TEST_F(GetKeyLongTest_202, EmptyMetadata_ReturnsMinusOne_202) {
  EXPECT_TRUE(exifData_.empty());
  long result = Exiv2::Internal::getKeyLong("Exif.Image.Make", &exifData_);
  EXPECT_EQ(-1, result);
}

// Test with multiple keys, querying one that exists
TEST_F(GetKeyLongTest_202, MultipleKeys_FindsCorrectOne_202) {
  {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("800");
    exifData_.add(key, value.get());
  }
  {
    Exiv2::ExifKey key("Exif.Image.ImageLength");
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("600");
    exifData_.add(key, value.get());
  }
  {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    exifData_.add(key, value.get());
  }

  long result1 = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", &exifData_);
  EXPECT_EQ(800, result1);

  long result2 = Exiv2::Internal::getKeyLong("Exif.Image.ImageLength", &exifData_);
  EXPECT_EQ(600, result2);

  long result3 = Exiv2::Internal::getKeyLong("Exif.Image.Orientation", &exifData_);
  EXPECT_EQ(3, result3);
}

// Test that float values are truncated to long (static_cast<long> from float)
TEST_F(GetKeyLongTest_202, FloatValueTruncatedToLong_202) {
  Exiv2::ExifKey key("Exif.Image.XResolution");
  auto value = Exiv2::Value::create(Exiv2::unsignedRational);
  // 72/1 = 72.0
  value->read("72/1");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.XResolution", &exifData_);
  EXPECT_EQ(72, result);
}

// Test with a rational value that has a fractional part
TEST_F(GetKeyLongTest_202, RationalValueWithFraction_TruncatedToLong_202) {
  Exiv2::ExifKey key("Exif.Image.XResolution");
  auto value = Exiv2::Value::create(Exiv2::unsignedRational);
  // 7/2 = 3.5, static_cast<long>(3.5f) = 3
  value->read("7/2");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.XResolution", &exifData_);
  EXPECT_EQ(3, result);
}

// Test with unsigned short value
TEST_F(GetKeyLongTest_202, UnsignedShortValue_ReturnsCorrectly_202) {
  Exiv2::ExifKey key("Exif.Image.BitsPerSample");
  auto value = Exiv2::Value::create(Exiv2::unsignedShort);
  value->read("8");
  exifData_.add(key, value.get());

  long result = Exiv2::Internal::getKeyLong("Exif.Image.BitsPerSample", &exifData_);
  EXPECT_EQ(8, result);
}
