// File: test_exifdata_findkey_const_778.cpp
// TEST_ID: 778

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>   // Convenient umbrella include (ExifData, ExifKey, Exifdatum operators)
#include <exiv2/exif.hpp>    // ExifData
#include <exiv2/tags.hpp>    // ExifKey

namespace {

class ExifDataFindKeyConstTest_778 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey(const std::string& key) {
    return Exiv2::ExifKey(key);
  }

  static const Exiv2::ExifData& AsConst(const Exiv2::ExifData& d) {
    return d;
  }
};

TEST_F(ExifDataFindKeyConstTest_778, ReturnsEndWhenEmpty_778) {
  Exiv2::ExifData data;

  const auto& cdata = AsConst(data);
  const Exiv2::ExifKey key = MakeKey("Exif.Image.Make");

  const auto it = cdata.findKey(key);
  EXPECT_EQ(it, cdata.end());
}

TEST_F(ExifDataFindKeyConstTest_778, FindsExistingSingleEntry_778) {
  Exiv2::ExifData data;
  data["Exif.Image.Make"] = "Canon";

  const auto& cdata = AsConst(data);
  const Exiv2::ExifKey key = MakeKey("Exif.Image.Make");

  const auto it = cdata.findKey(key);
  ASSERT_NE(it, cdata.end());
  EXPECT_EQ(it->key(), key.key());
}

TEST_F(ExifDataFindKeyConstTest_778, ReturnsEndWhenKeyNotPresent_778) {
  Exiv2::ExifData data;
  data["Exif.Image.Make"] = "Canon";

  const auto& cdata = AsConst(data);
  const Exiv2::ExifKey missing = MakeKey("Exif.Image.Model");

  const auto it = cdata.findKey(missing);
  EXPECT_EQ(it, cdata.end());
}

TEST_F(ExifDataFindKeyConstTest_778, FindsCorrectEntryAmongMultiple_778) {
  Exiv2::ExifData data;
  data["Exif.Image.Make"] = "Canon";
  data["Exif.Image.Model"] = "EOS";
  data["Exif.Photo.DateTimeOriginal"] = "2020:01:02 03:04:05";

  const auto& cdata = AsConst(data);
  const Exiv2::ExifKey target = MakeKey("Exif.Photo.DateTimeOriginal");

  const auto it = cdata.findKey(target);
  ASSERT_NE(it, cdata.end());
  EXPECT_EQ(it->key(), target.key());
}

TEST_F(ExifDataFindKeyConstTest_778, ReflectsEraseByMakingPreviouslyFoundKeyDisappear_778) {
  Exiv2::ExifData data;
  data["Exif.Image.Make"] = "Canon";
  data["Exif.Image.Model"] = "EOS";

  const Exiv2::ExifKey key_make = MakeKey("Exif.Image.Make");

  // First, key is present.
  {
    const auto& cdata = AsConst(data);
    const auto it = cdata.findKey(key_make);
    ASSERT_NE(it, cdata.end());
    EXPECT_EQ(it->key(), key_make.key());
  }

  // Erase the found element using the non-const iterator returned by non-const findKey.
  {
    auto it_nc = data.findKey(key_make);
    ASSERT_NE(it_nc, data.end());
    data.erase(it_nc);
  }

  // Now, const findKey should return end.
  {
    const auto& cdata = AsConst(data);
    const auto it2 = cdata.findKey(key_make);
    EXPECT_EQ(it2, cdata.end());
  }
}

}  // namespace