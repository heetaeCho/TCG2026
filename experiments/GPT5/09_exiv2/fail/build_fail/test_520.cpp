// File: test_easyaccess_saturation_520.cpp
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/value.hpp>

#include <string>
#include <vector>

namespace {

// Helper: add a simple numeric value for a given Exif key string.
static void addUShort(Exiv2::ExifData& ed, const std::string& keyStr, const std::string& valueStr = "1") {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_NO_THROW(v->read(valueStr));
  Exiv2::ExifKey key(keyStr);
  ASSERT_NO_THROW(ed.add(key, v.get()));
}

// Keys listed in easyaccess.cpp for saturation()
static const std::vector<std::string> kSaturationKeys = {
    "Exif.Photo.Saturation",
    "Exif.CanonCs.Saturation",
    "Exif.MinoltaCsNew.Saturation",
    "Exif.MinoltaCsOld.Saturation",
    "Exif.MinoltaCs7D.Saturation",
    "Exif.MinoltaCs5D.Saturation",
    "Exif.Fujifilm.Color",
    "Exif.Nikon3.Saturation",
    "Exif.Nikon3.Saturation2",
    "Exif.NikonPc.Saturation",
    "Exif.Panasonic.Saturation",
    "Exif.Pentax.Saturation",
    "Exif.PentaxDng.Saturation",
    "Exif.Sigma.Saturation",
    "Exif.Sony1.Saturation",
    "Exif.Sony2.Saturation",
    "Exif.Casio.Saturation",
    "Exif.Casio2.Saturation",
    "Exif.Casio2.Saturation2",
};

static bool isOneOfSaturationKeys(const std::string& keyStr) {
  for (const auto& k : kSaturationKeys) {
    if (k == keyStr) return true;
  }
  return false;
}

}  // namespace

class EasyAccessSaturationTest_520 : public ::testing::Test {};

TEST_F(EasyAccessSaturationTest_520, EmptyExifDataReturnsEnd_520) {
  Exiv2::ExifData ed;

  Exiv2::ExifData::const_iterator it = Exiv2::saturation(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(EasyAccessSaturationTest_520, NoMatchingKeyReturnsEnd_520) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Image.Make", "123");  // unrelated key

  Exiv2::ExifData::const_iterator it = Exiv2::saturation(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(EasyAccessSaturationTest_520, SingleMatchingKeyReturnsIteratorToThatKey_520) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Photo.Saturation", "2");

  Exiv2::ExifData::const_iterator it = Exiv2::saturation(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.Saturation"));
}

TEST_F(EasyAccessSaturationTest_520, AnotherMatchingKeyReturnsIteratorToThatKey_520) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Nikon3.Saturation2", "3");

  Exiv2::ExifData::const_iterator it = Exiv2::saturation(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Nikon3.Saturation2"));
}

TEST_F(EasyAccessSaturationTest_520, MultipleMatchingKeysReturnsOneOfThem_520) {
  Exiv2::ExifData ed;
  // Add two different keys from the supported list.
  addUShort(ed, "Exif.CanonCs.Saturation", "4");
  addUShort(ed, "Exif.Pentax.Saturation", "5");

  Exiv2::ExifData::const_iterator it = Exiv2::saturation(ed);

  ASSERT_NE(it, ed.end());
  // Black-box friendly: verify we got a supported saturation key, and it is one we inserted.
  const std::string foundKey = it->key();
  EXPECT_TRUE(foundKey == "Exif.CanonCs.Saturation" || foundKey == "Exif.Pentax.Saturation");
  EXPECT_TRUE(isOneOfSaturationKeys(foundKey));
}

TEST_F(EasyAccessSaturationTest_520, UnrelatedKeysDoNotInterfereWithMatch_520) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Image.Make", "1");
  addUShort(ed, "Exif.Image.Model", "2");
  addUShort(ed, "Exif.Sony2.Saturation", "6");  // a supported key

  Exiv2::ExifData::const_iterator it = Exiv2::saturation(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Sony2.Saturation"));
}

TEST_F(EasyAccessSaturationTest_520, WorksWithSortedExifData_520) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Panasonic.Saturation", "7");
  addUShort(ed, "Exif.Image.Make", "1");
  addUShort(ed, "Exif.Photo.FNumber", "2");

  ASSERT_NO_THROW(ed.sortByKey());

  Exiv2::ExifData::const_iterator it = Exiv2::saturation(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Panasonic.Saturation"));
}

TEST_F(EasyAccessSaturationTest_520, ReturnedIteratorIsUsableForDereference_520) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Casio2.Saturation2", "8");

  Exiv2::ExifData::const_iterator it = Exiv2::saturation(ed);

  ASSERT_NE(it, ed.end());
  // Observable behavior: iterator can be dereferenced and yields a metadatum with a non-empty key.
  EXPECT_FALSE(it->key().empty());
  EXPECT_EQ(it->key(), std::string("Exif.Casio2.Saturation2"));
}