// File: test_easyaccess_macroMode_516.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/easyaccess.hpp>

#include <string>

namespace {

class MacroModeTest_516 : public ::testing::Test {
 protected:
  static void addUShort(Exiv2::ExifData& ed, const std::string& keyStr, uint16_t v) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read(std::to_string(v));
    ed.add(Exiv2::ExifKey(keyStr), value.get());
  }
};

TEST_F(MacroModeTest_516, EmptyExifDataReturnsEnd_516) {
  Exiv2::ExifData ed;
  ASSERT_TRUE(ed.empty());

  const auto it = Exiv2::macroMode(ed);
  EXPECT_EQ(it, ed.end());
  EXPECT_TRUE(ed.empty());
  EXPECT_EQ(ed.count(), 0u);
}

TEST_F(MacroModeTest_516, NoMatchingKeysReturnsEnd_516) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Image.ImageWidth", 640);

  const auto beforeCount = ed.count();
  const auto it = Exiv2::macroMode(ed);

  EXPECT_EQ(it, ed.end());
  EXPECT_EQ(ed.count(), beforeCount);
}

TEST_F(MacroModeTest_516, FindsPresentKeyCanonCsMacro_516) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.CanonCs.Macro", 1);

  const auto expected = ed.findKey(Exiv2::ExifKey("Exif.CanonCs.Macro"));
  ASSERT_NE(expected, ed.end());

  const auto beforeCount = ed.count();
  const auto it = Exiv2::macroMode(ed);

  EXPECT_NE(it, ed.end());
  EXPECT_EQ(it, expected);
  EXPECT_EQ(it->key(), std::string("Exif.CanonCs.Macro"));
  EXPECT_EQ(ed.count(), beforeCount);  // should not modify
}

TEST_F(MacroModeTest_516, FindsPresentKeyAtEndOfListSony2Macro_516) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Sony2.Macro", 2);

  const auto expected = ed.findKey(Exiv2::ExifKey("Exif.Sony2.Macro"));
  ASSERT_NE(expected, ed.end());

  const auto it = Exiv2::macroMode(ed);

  EXPECT_NE(it, ed.end());
  EXPECT_EQ(it, expected);
  EXPECT_EQ(it->key(), std::string("Exif.Sony2.Macro"));
}

TEST_F(MacroModeTest_516, WhenMultipleMatchingKeysPresentReturnsFirstInKeyPreferenceOrder_516) {
  Exiv2::ExifData ed;

  // Add a later key and an earlier key; observable behavior should prefer the earlier key
  // based on the published key list passed into macroMode().
  addUShort(ed, "Exif.Sony2.Macro", 2);      // later in list
  addUShort(ed, "Exif.Fujifilm.Macro", 1);   // earlier in list

  const auto expectedEarlier = ed.findKey(Exiv2::ExifKey("Exif.Fujifilm.Macro"));
  const auto alsoPresentLater = ed.findKey(Exiv2::ExifKey("Exif.Sony2.Macro"));
  ASSERT_NE(expectedEarlier, ed.end());
  ASSERT_NE(alsoPresentLater, ed.end());

  const auto it = Exiv2::macroMode(ed);

  EXPECT_NE(it, ed.end());
  EXPECT_EQ(it, expectedEarlier);
  EXPECT_EQ(it->key(), std::string("Exif.Fujifilm.Macro"));
}

}  // namespace