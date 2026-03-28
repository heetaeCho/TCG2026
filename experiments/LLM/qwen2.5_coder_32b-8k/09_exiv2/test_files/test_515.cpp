#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class SceneModeTest : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(SceneModeTest_NormalOperation_515, CanonEasyModeFound_515) {

    exifData.add(ExifKey("Exif.CanonCs.EasyMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.CanonCs.EasyMode");

}



TEST_F(SceneModeTest_NormalOperation_515, FujifilmPictureModeFound_515) {

    exifData.add(ExifKey("Exif.Fujifilm.PictureMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Fujifilm.PictureMode");

}



TEST_F(SceneModeTest_NormalOperation_515, MinoltaCsNewSubjectProgramFound_515) {

    exifData.add(ExifKey("Exif.MinoltaCsNew.SubjectProgram"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.SubjectProgram");

}



TEST_F(SceneModeTest_NormalOperation_515, MinoltaCsOldSubjectProgramFound_515) {

    exifData.add(ExifKey("Exif.MinoltaCsOld.SubjectProgram"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.SubjectProgram");

}



TEST_F(SceneModeTest_NormalOperation_515, MinoltaSceneModeFound_515) {

    exifData.add(ExifKey("Exif.Minolta.SceneMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Minolta.SceneMode");

}



TEST_F(SceneModeTest_NormalOperation_515, SonyMinoltaSceneModeFound_515) {

    exifData.add(ExifKey("Exif.SonyMinolta.SceneMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.SonyMinolta.SceneMode");

}



TEST_F(SceneModeTest_NormalOperation_515, Sony1SceneModeFound_515) {

    exifData.add(ExifKey("Exif.Sony1.SceneMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Sony1.SceneMode");

}



TEST_F(SceneModeTest_NormalOperation_515, Sony2SceneModeFound_515) {

    exifData.add(ExifKey("Exif.Sony2.SceneMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Sony2.SceneMode");

}



TEST_F(SceneModeTest_NormalOperation_515, OlympusCsSceneModeFound_515) {

    exifData.add(ExifKey("Exif.OlympusCs.SceneMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.OlympusCs.SceneMode");

}



TEST_F(SceneModeTest_NormalOperation_515, PanasonicShootingModeFound_515) {

    exifData.add(ExifKey("Exif.Panasonic.ShootingMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Panasonic.ShootingMode");

}



TEST_F(SceneModeTest_NormalOperation_515, PanasonicSceneModeFound_515) {

    exifData.add(ExifKey("Exif.Panasonic.SceneMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Panasonic.SceneMode");

}



TEST_F(SceneModeTest_NormalOperation_515, PentaxPictureModeFound_515) {

    exifData.add(ExifKey("Exif.Pentax.PictureMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Pentax.PictureMode");

}



TEST_F(SceneModeTest_NormalOperation_515, PentaxDngPictureModeFound_515) {

    exifData.add(ExifKey("Exif.PentaxDng.PictureMode"), new Value);

    auto it = sceneMode(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.PentaxDng.PictureMode");

}



TEST_F(SceneModeTest_BoundaryConditions_515, NoSceneModeFound_515) {

    auto it = sceneMode(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(SceneModeTest_ExceptionalCases_515, EmptyExifData_515) {

    ExifData emptyData;

    auto it = sceneMode(emptyData);

    EXPECT_EQ(it, emptyData.end());

}
