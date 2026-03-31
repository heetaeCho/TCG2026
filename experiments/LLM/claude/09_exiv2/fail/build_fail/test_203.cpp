#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/value.hpp>

// We need to access the internal function findLensInfo
// Based on the code, it's in Exiv2::Internal namespace
namespace Exiv2 {
namespace Internal {

// Forward declare the exception type
class LensInfoNotFound : public std::exception {};

// Forward declare the function we're testing
ExifData::const_iterator findLensInfo(const ExifData* metadata);

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;

class FindLensInfoTest_203 : public ::testing::Test {
 protected:
  ExifData exifData;
};

// Test that when neither PentaxDng.LensInfo nor Pentax.LensInfo exists,
// LensInfoNotFound exception is thrown
TEST_F(FindLensInfoTest_203, ThrowsWhenNoLensInfoPresent_203) {
  // ExifData is empty, no lens info keys present
  EXPECT_THROW(Internal::findLensInfo(&exifData), Internal::LensInfoNotFound);
}

// Test that when only Exif.PentaxDng.LensInfo exists, it is returned
TEST_F(FindLensInfoTest_203, ReturnsPentaxDngLensInfoWhenPresent_203) {
  ExifKey dngKey("Exif.PentaxDng.LensInfo");
  Value::UniquePtr value = Value::create(unsignedByte);
  value->read("0");
  exifData.add(dngKey, value.get());

  ExifData::const_iterator result;
  ASSERT_NO_THROW(result = Internal::findLensInfo(&exifData));
  EXPECT_EQ(result->key(), "Exif.PentaxDng.LensInfo");
}

// Test that when only Exif.Pentax.LensInfo exists, it is returned
TEST_F(FindLensInfoTest_203, ReturnsPentaxLensInfoWhenPresent_203) {
  ExifKey pentaxKey("Exif.Pentax.LensInfo");
  Value::UniquePtr value = Value::create(unsignedByte);
  value->read("0");
  exifData.add(pentaxKey, value.get());

  ExifData::const_iterator result;
  ASSERT_NO_THROW(result = Internal::findLensInfo(&exifData));
  EXPECT_EQ(result->key(), "Exif.Pentax.LensInfo");
}

// Test that when both Exif.PentaxDng.LensInfo and Exif.Pentax.LensInfo exist,
// PentaxDng.LensInfo is returned (it has priority)
TEST_F(FindLensInfoTest_203, PrefersPentaxDngOverPentaxLensInfo_203) {
  ExifKey dngKey("Exif.PentaxDng.LensInfo");
  Value::UniquePtr dngValue = Value::create(unsignedByte);
  dngValue->read("1");
  exifData.add(dngKey, dngValue.get());

  ExifKey pentaxKey("Exif.Pentax.LensInfo");
  Value::UniquePtr pentaxValue = Value::create(unsignedByte);
  pentaxValue->read("2");
  exifData.add(pentaxKey, pentaxValue.get());

  ExifData::const_iterator result;
  ASSERT_NO_THROW(result = Internal::findLensInfo(&exifData));
  EXPECT_EQ(result->key(), "Exif.PentaxDng.LensInfo");
}

// Test that when ExifData has other keys but not the lens info keys,
// the exception is thrown
TEST_F(FindLensInfoTest_203, ThrowsWhenOtherKeysExistButNoLensInfo_203) {
  ExifKey otherKey("Exif.Image.Make");
  Value::UniquePtr value = Value::create(asciiString);
  value->read("Pentax");
  exifData.add(otherKey, value.get());

  EXPECT_THROW(Internal::findLensInfo(&exifData), Internal::LensInfoNotFound);
}

// Test that the returned iterator is valid and points to correct data
TEST_F(FindLensInfoTest_203, ReturnedIteratorPointsToValidData_203) {
  ExifKey pentaxKey("Exif.Pentax.LensInfo");
  Value::UniquePtr value = Value::create(unsignedByte);
  value->read("42");
  exifData.add(pentaxKey, value.get());

  ExifData::const_iterator result;
  ASSERT_NO_THROW(result = Internal::findLensInfo(&exifData));
  EXPECT_NE(result, exifData.end());
  EXPECT_EQ(result->key(), "Exif.Pentax.LensInfo");
}

// Test with multiple unrelated entries and only Pentax.LensInfo
TEST_F(FindLensInfoTest_203, FindsPentaxLensInfoAmongMultipleEntries_203) {
  ExifKey makeKey("Exif.Image.Make");
  Value::UniquePtr makeValue = Value::create(asciiString);
  makeValue->read("Pentax");
  exifData.add(makeKey, makeValue.get());

  ExifKey modelKey("Exif.Image.Model");
  Value::UniquePtr modelValue = Value::create(asciiString);
  modelValue->read("K-1");
  exifData.add(modelKey, modelValue.get());

  ExifKey pentaxKey("Exif.Pentax.LensInfo");
  Value::UniquePtr lensValue = Value::create(unsignedByte);
  lensValue->read("10");
  exifData.add(pentaxKey, lensValue.get());

  ExifData::const_iterator result;
  ASSERT_NO_THROW(result = Internal::findLensInfo(&exifData));
  EXPECT_EQ(result->key(), "Exif.Pentax.LensInfo");
}

// Test with multiple unrelated entries and only PentaxDng.LensInfo
TEST_F(FindLensInfoTest_203, FindsPentaxDngLensInfoAmongMultipleEntries_203) {
  ExifKey makeKey("Exif.Image.Make");
  Value::UniquePtr makeValue = Value::create(asciiString);
  makeValue->read("Pentax");
  exifData.add(makeKey, makeValue.get());

  ExifKey dngKey("Exif.PentaxDng.LensInfo");
  Value::UniquePtr lensValue = Value::create(unsignedByte);
  lensValue->read("20");
  exifData.add(dngKey, lensValue.get());

  ExifKey modelKey("Exif.Image.Model");
  Value::UniquePtr modelValue = Value::create(asciiString);
  modelValue->read("K-1");
  exifData.add(modelKey, modelValue.get());

  ExifData::const_iterator result;
  ASSERT_NO_THROW(result = Internal::findLensInfo(&exifData));
  EXPECT_EQ(result->key(), "Exif.PentaxDng.LensInfo");
}
