// ***************************************************************** -*- C++ -*-
/*
 * Unit tests for Exiv2::model(const ExifData&)
 * File under test: ./TestProjects/exiv2/src/easyaccess.cpp
 *
 * Constraints:
 *  - Treat implementation as black box
 *  - Test only observable behavior via public API
 *  - No private/internal state access
 */
// *****************************************************************************
// Include headers
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>  // Exiv2::model
#include <exiv2/exif.hpp>        // Exiv2::ExifData, Exiv2::ExifKey
#include <exiv2/value.hpp>       // Exiv2::Value::create, TypeId

#include <string>
#include <type_traits>

namespace {

// TEST_ID is 526
class ModelEasyAccessTest_526 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    // read() is part of Exiv2 Value public API; it parses from a string.
    v->read(s);
    return v;
  }

  static void addAscii(Exiv2::ExifData& ed, const std::string& key, const std::string& value) {
    Exiv2::ExifKey k(key);
    auto v = makeAsciiValue(value);
    ed.add(k, v.get());
  }
};

TEST_F(ModelEasyAccessTest_526, ReturnsEndWhenEmpty_526) {
  Exiv2::ExifData ed;

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::model(ced);

  EXPECT_TRUE(ced.empty());
  EXPECT_EQ(it, ced.end());
}

TEST_F(ModelEasyAccessTest_526, ReturnsEndWhenOnlyUnrelatedKeysPresent_526) {
  Exiv2::ExifData ed;
  addAscii(ed, "Exif.Photo.UserComment", "hello");
  addAscii(ed, "Exif.Image.Make", "SomeMake");

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::model(ced);

  EXPECT_NE(ced.count(), 0u);
  EXPECT_EQ(it, ced.end());
}

TEST_F(ModelEasyAccessTest_526, FindsExifImageModelWhenPresent_526) {
  Exiv2::ExifData ed;
  addAscii(ed, "Exif.Image.Model", "MyCameraModel");

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::model(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.Model"));
}

TEST_F(ModelEasyAccessTest_526, FindsFallbackKeyWhenPrimaryMissing_526) {
  Exiv2::ExifData ed;
  // One of the documented fallback keys in the implementation list.
  addAscii(ed, "Exif.Pentax.ModelID", "1234");

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::model(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Pentax.ModelID"));
}

TEST_F(ModelEasyAccessTest_526, PrefersEarlierKeyInSearchOrderWhenMultiplePresent_526) {
  Exiv2::ExifData ed;

  // Add a later-search key first, then add an earlier-search key.
  addAscii(ed, "Exif.Sony2.SonyModelID", "9999");  // later in the list
  addAscii(ed, "Exif.Image.Model", "Preferred");   // first in the list

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::model(ced);

  ASSERT_NE(it, ced.end());
  // Observable requirement: should return the first matching key in the function's search order.
  EXPECT_EQ(it->key(), std::string("Exif.Image.Model"));
}

TEST_F(ModelEasyAccessTest_526, ReturnTypeIsConstIterator_526) {
  using RetT = decltype(Exiv2::model(std::declval<const Exiv2::ExifData&>()));
  static_assert(std::is_same<RetT, Exiv2::ExifData::const_iterator>::value,
                "Exiv2::model must return Exiv2::ExifData::const_iterator");
  SUCCEED();
}

}  // namespace