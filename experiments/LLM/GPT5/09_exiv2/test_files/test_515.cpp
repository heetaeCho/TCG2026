// File: test_easyaccess_sceneMode_515.cpp
// TEST_ID: 515

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

#include <string>
#include <vector>

namespace {

class SceneModeTest_515 : public ::testing::Test {
 protected:
  static std::vector<std::string> SceneModeKeys() {
    return {
        "Exif.CanonCs.EasyMode",
        "Exif.Fujifilm.PictureMode",
        "Exif.MinoltaCsNew.SubjectProgram",
        "Exif.MinoltaCsOld.SubjectProgram",
        "Exif.Minolta.SceneMode",
        "Exif.SonyMinolta.SceneMode",
        "Exif.Sony1.SceneMode",
        "Exif.Sony2.SceneMode",
        "Exif.OlympusCs.SceneMode",
        "Exif.Panasonic.ShootingMode",
        "Exif.Panasonic.SceneMode",
        "Exif.Pentax.PictureMode",
        "Exif.PentaxDng.PictureMode",
    };
  }
};

TEST_F(SceneModeTest_515, ReturnsEndWhenExifDataIsEmpty_515) {
  const Exiv2::ExifData ed;
  const auto it = Exiv2::sceneMode(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(SceneModeTest_515, ReturnsEndWhenNoSceneModeKeysArePresent_515) {
  Exiv2::ExifData ed;
  ed["Exif.Image.Make"] = "AnyMake";
  ed["Exif.Image.Model"] = "AnyModel";

  const auto& ced = ed;
  const auto it = Exiv2::sceneMode(ced);
  EXPECT_EQ(it, ced.end());
}

class SceneModeKeyParamTest_515 : public ::testing::TestWithParam<std::string> {};

TEST_P(SceneModeKeyParamTest_515, ReturnsIteratorToPresentSceneModeKey_515) {
  Exiv2::ExifData ed;
  const std::string key = GetParam();

  // Use a simple string assignment to create/populate the metadatum via operator[].
  ed[key] = "1";

  const auto& ced = ed;
  const auto it = Exiv2::sceneMode(ced);

  ASSERT_NE(it, ced.end());

  // Verify the returned iterator points to the same key we inserted.
  // (Using only public interface; no assumptions about internal storage.)
  const auto expected = ced.findKey(Exiv2::ExifKey(key));
  ASSERT_NE(expected, ced.end());
  EXPECT_EQ(it, expected);
}

INSTANTIATE_TEST_SUITE_P(
    SceneModeKeys_515, SceneModeKeyParamTest_515,
    ::testing::Values(
        "Exif.CanonCs.EasyMode", "Exif.Fujifilm.PictureMode",
        "Exif.MinoltaCsNew.SubjectProgram", "Exif.MinoltaCsOld.SubjectProgram",
        "Exif.Minolta.SceneMode", "Exif.SonyMinolta.SceneMode",
        "Exif.Sony1.SceneMode", "Exif.Sony2.SceneMode",
        "Exif.OlympusCs.SceneMode", "Exif.Panasonic.ShootingMode",
        "Exif.Panasonic.SceneMode", "Exif.Pentax.PictureMode",
        "Exif.PentaxDng.PictureMode"));

TEST_F(SceneModeTest_515, WhenMultipleSceneModeKeysPresentReturnsOneOfThem_515) {
  Exiv2::ExifData ed;

  const auto keys = SceneModeKeys();
  ASSERT_GE(keys.size(), 2u);

  const std::string k1 = keys[0];
  const std::string k2 = keys[1];

  ed[k1] = "10";
  ed[k2] = "20";

  const auto& ced = ed;
  const auto it = Exiv2::sceneMode(ced);

  ASSERT_NE(it, ced.end());

  // Without assuming key-priority/order, only assert it is one of the present keys.
  const auto it1 = ced.findKey(Exiv2::ExifKey(k1));
  const auto it2 = ced.findKey(Exiv2::ExifKey(k2));
  ASSERT_NE(it1, ced.end());
  ASSERT_NE(it2, ced.end());

  const bool matches_first = (it == it1);
  const bool matches_second = (it == it2);
  EXPECT_TRUE(matches_first || matches_second);
}

TEST_F(SceneModeTest_515, IgnoresUnrelatedKeysEvenIfTheyLookSimilar_515) {
  Exiv2::ExifData ed;

  // Similar prefix but not one of the supported keys.
  ed["Exif.CanonCs.EasyModeX"] = "1";
  ed["Exif.Pentax.PictureModeExtra"] = "2";

  const auto& ced = ed;
  const auto it = Exiv2::sceneMode(ced);
  EXPECT_EQ(it, ced.end());
}

}  // namespace