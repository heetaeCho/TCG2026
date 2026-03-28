#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
ExifData::const_iterator sceneMode(const ExifData& ed);
}

class SceneModeTest_515 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(SceneModeTest_515, EmptyExifDataReturnsEnd_515) {
    auto it = Exiv2::sceneMode(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SceneModeTest_515, FindsCanonCsEasyMode_515) {
    ed["Exif.CanonCs.EasyMode"] = uint16_t(1);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.EasyMode");
}

TEST_F(SceneModeTest_515, FindsFujifilmPictureMode_515) {
    ed["Exif.Fujifilm.PictureMode"] = uint16_t(2);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.PictureMode");
}

TEST_F(SceneModeTest_515, FindsMinoltaCsNewSubjectProgram_515) {
    ed["Exif.MinoltaCsNew.SubjectProgram"] = uint16_t(3);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.SubjectProgram");
}

TEST_F(SceneModeTest_515, FindsMinoltaCsOldSubjectProgram_515) {
    ed["Exif.MinoltaCsOld.SubjectProgram"] = uint16_t(4);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.SubjectProgram");
}

TEST_F(SceneModeTest_515, FindsMinoltaSceneMode_515) {
    ed["Exif.Minolta.SceneMode"] = uint32_t(5);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Minolta.SceneMode");
}

TEST_F(SceneModeTest_515, FindsSonyMinoltaSceneMode_515) {
    ed["Exif.SonyMinolta.SceneMode"] = uint32_t(6);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.SonyMinolta.SceneMode");
}

TEST_F(SceneModeTest_515, FindsSony1SceneMode_515) {
    ed["Exif.Sony1.SceneMode"] = uint32_t(7);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.SceneMode");
}

TEST_F(SceneModeTest_515, FindsSony2SceneMode_515) {
    ed["Exif.Sony2.SceneMode"] = uint32_t(8);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.SceneMode");
}

TEST_F(SceneModeTest_515, FindsOlympusCsSceneMode_515) {
    ed["Exif.OlympusCs.SceneMode"] = uint16_t(9);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.SceneMode");
}

TEST_F(SceneModeTest_515, FindsPanasonicShootingMode_515) {
    ed["Exif.Panasonic.ShootingMode"] = uint16_t(10);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.ShootingMode");
}

TEST_F(SceneModeTest_515, FindsPanasonicSceneMode_515) {
    ed["Exif.Panasonic.SceneMode"] = uint16_t(11);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.SceneMode");
}

TEST_F(SceneModeTest_515, FindsPentaxPictureMode_515) {
    ed["Exif.Pentax.PictureMode"] = uint16_t(12);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.PictureMode");
}

TEST_F(SceneModeTest_515, FindsPentaxDngPictureMode_515) {
    ed["Exif.PentaxDng.PictureMode"] = uint16_t(13);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.PictureMode");
}

TEST_F(SceneModeTest_515, PriorityCanonOverFujifilm_515) {
    // Canon is first in the list, so it should be returned when both exist
    ed["Exif.CanonCs.EasyMode"] = uint16_t(1);
    ed["Exif.Fujifilm.PictureMode"] = uint16_t(2);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.EasyMode");
}

TEST_F(SceneModeTest_515, PriorityFujifilmOverMinolta_515) {
    ed["Exif.Fujifilm.PictureMode"] = uint16_t(2);
    ed["Exif.MinoltaCsNew.SubjectProgram"] = uint16_t(3);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.PictureMode");
}

TEST_F(SceneModeTest_515, PriorityPanasonicShootingOverSceneMode_515) {
    // ShootingMode comes before SceneMode in the list
    ed["Exif.Panasonic.ShootingMode"] = uint16_t(10);
    ed["Exif.Panasonic.SceneMode"] = uint16_t(11);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.ShootingMode");
}

TEST_F(SceneModeTest_515, PriorityPentaxOverPentaxDng_515) {
    ed["Exif.Pentax.PictureMode"] = uint16_t(12);
    ed["Exif.PentaxDng.PictureMode"] = uint16_t(13);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.PictureMode");
}

TEST_F(SceneModeTest_515, UnrelatedKeyReturnsEnd_515) {
    ed["Exif.Image.Make"] = "SomeCamera";
    auto it = Exiv2::sceneMode(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SceneModeTest_515, MultipleUnrelatedKeysReturnsEnd_515) {
    ed["Exif.Image.Make"] = "SomeCamera";
    ed["Exif.Image.Model"] = "SomeModel";
    ed["Exif.Photo.ExposureTime"] = "1/100";
    auto it = Exiv2::sceneMode(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SceneModeTest_515, LastPriorityKeyFoundWhenOnlyOnePresent_515) {
    // PentaxDng.PictureMode is the last in the priority list
    ed["Exif.PentaxDng.PictureMode"] = uint16_t(13);
    ed["Exif.Image.Make"] = "SomeCamera";
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.PictureMode");
}

TEST_F(SceneModeTest_515, AllKeysPresent_ReturnsHighestPriority_515) {
    ed["Exif.CanonCs.EasyMode"] = uint16_t(1);
    ed["Exif.Fujifilm.PictureMode"] = uint16_t(2);
    ed["Exif.MinoltaCsNew.SubjectProgram"] = uint16_t(3);
    ed["Exif.MinoltaCsOld.SubjectProgram"] = uint16_t(4);
    ed["Exif.Minolta.SceneMode"] = uint32_t(5);
    ed["Exif.SonyMinolta.SceneMode"] = uint32_t(6);
    ed["Exif.Sony1.SceneMode"] = uint32_t(7);
    ed["Exif.Sony2.SceneMode"] = uint32_t(8);
    ed["Exif.OlympusCs.SceneMode"] = uint16_t(9);
    ed["Exif.Panasonic.ShootingMode"] = uint16_t(10);
    ed["Exif.Panasonic.SceneMode"] = uint16_t(11);
    ed["Exif.Pentax.PictureMode"] = uint16_t(12);
    ed["Exif.PentaxDng.PictureMode"] = uint16_t(13);

    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.EasyMode");
}

TEST_F(SceneModeTest_515, LowerPriorityKeySelectedWhenHigherAbsent_515) {
    // Only Sony2 and Pentax are present; Sony2 has higher priority
    ed["Exif.Sony2.SceneMode"] = uint32_t(8);
    ed["Exif.Pentax.PictureMode"] = uint16_t(12);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.SceneMode");
}

TEST_F(SceneModeTest_515, MiddlePriorityKeyOlympus_515) {
    ed["Exif.OlympusCs.SceneMode"] = uint16_t(9);
    ed["Exif.PentaxDng.PictureMode"] = uint16_t(13);
    auto it = Exiv2::sceneMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.SceneMode");
}
