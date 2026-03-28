#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {

    ExifData::const_iterator macroMode(const ExifData& ed);

}



class MacroModeTest_516 : public ::testing::Test {

protected:

    Exiv2::ExifData exifData;

};



TEST_F(MacroModeTest_516, NoMacroTags_516) {

    auto result = Exiv2::macroMode(exifData);

    EXPECT_EQ(result, exifData.end());

}



TEST_F(MacroModeTest_516, CanonMacroPresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.CanonCs.Macro"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.CanonCs.Macro");

}



TEST_F(MacroModeTest_516, FujifilmMacroPresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.Fujifilm.Macro"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Fujifilm.Macro");

}



TEST_F(MacroModeTest_516, OlympusMacroPresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.Olympus.Macro"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Olympus.Macro");

}



TEST_F(MacroModeTest_516, Olympus2MacroPresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.Olympus2.Macro"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Olympus2.Macro");

}



TEST_F(MacroModeTest_516, OlympusCsMacroModePresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.OlympusCs.MacroMode"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.OlympusCs.MacroMode");

}



TEST_F(MacroModeTest_516, PanasonicMacroPresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.Panasonic.Macro"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Panasonic.Macro");

}



TEST_F(MacroModeTest_516, MinoltaCsNewMacroModePresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.MinoltaCsNew.MacroMode"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.MinoltaCsNew.MacroMode");

}



TEST_F(MacroModeTest_516, MinoltaCsOldMacroModePresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.MinoltaCsOld.MacroMode"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.MinoltaCsOld.MacroMode");

}



TEST_F(MacroModeTest_516, Sony1MacroPresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.Sony1.Macro"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Sony1.Macro");

}



TEST_F(MacroModeTest_516, Sony2MacroPresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.Sony2.Macro"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.Sony2.Macro");

}



TEST_F(MacroModeTest_516, MultipleMacroTagsPresent_516) {

    exifData.add(Exiv2::ExifKey("Exif.CanonCs.Macro"), new Exiv2::ShortValue(1));

    exifData.add(Exiv2::ExifKey("Exif.Fujifilm.Macro"), new Exiv2::ShortValue(1));

    auto result = Exiv2::macroMode(exifData);

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), "Exif.CanonCs.Macro");

}
