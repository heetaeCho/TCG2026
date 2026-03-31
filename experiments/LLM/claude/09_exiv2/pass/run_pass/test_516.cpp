#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class MacroModeTest_516 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(MacroModeTest_516, ReturnsEndWhenExifDataIsEmpty_516) {
    auto it = Exiv2::macroMode(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(MacroModeTest_516, FindsCanonCsMacro_516) {
    ed["Exif.CanonCs.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Macro");
}

TEST_F(MacroModeTest_516, FindsFujifilmMacro_516) {
    ed["Exif.Fujifilm.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.Macro");
}

TEST_F(MacroModeTest_516, FindsOlympusMacro_516) {
    ed["Exif.Olympus.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.Macro");
}

TEST_F(MacroModeTest_516, FindsOlympus2Macro_516) {
    ed["Exif.Olympus2.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus2.Macro");
}

TEST_F(MacroModeTest_516, FindsOlympusCsMacroMode_516) {
    ed["Exif.OlympusCs.MacroMode"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.MacroMode");
}

TEST_F(MacroModeTest_516, FindsPanasonicMacro_516) {
    ed["Exif.Panasonic.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.Macro");
}

TEST_F(MacroModeTest_516, FindsMinoltaCsNewMacroMode_516) {
    ed["Exif.MinoltaCsNew.MacroMode"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.MacroMode");
}

TEST_F(MacroModeTest_516, FindsMinoltaCsOldMacroMode_516) {
    ed["Exif.MinoltaCsOld.MacroMode"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.MacroMode");
}

TEST_F(MacroModeTest_516, FindsSony1Macro_516) {
    ed["Exif.Sony1.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Macro");
}

TEST_F(MacroModeTest_516, FindsSony2Macro_516) {
    ed["Exif.Sony2.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.Macro");
}

TEST_F(MacroModeTest_516, PrefersHigherPriorityKeyWhenMultiplePresent_516) {
    // CanonCs.Macro is first in the list, so it should be preferred
    ed["Exif.Sony2.Macro"] = uint16_t(2);
    ed["Exif.CanonCs.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Macro");
}

TEST_F(MacroModeTest_516, ReturnsEndWhenNoMatchingKeysExist_516) {
    // Add an unrelated key
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:01 12:00:00";
    auto it = Exiv2::macroMode(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(MacroModeTest_516, PrefersCanonOverFujifilmWhenBothPresent_516) {
    ed["Exif.Fujifilm.Macro"] = uint16_t(1);
    ed["Exif.CanonCs.Macro"] = uint16_t(2);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Macro");
}

TEST_F(MacroModeTest_516, PrefersFujifilmOverOlympusWhenBothPresent_516) {
    ed["Exif.Olympus.Macro"] = uint16_t(1);
    ed["Exif.Fujifilm.Macro"] = uint16_t(2);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.Macro");
}

TEST_F(MacroModeTest_516, PrefersMinoltaCsNewOverSony1_516) {
    ed["Exif.Sony1.Macro"] = uint16_t(1);
    ed["Exif.MinoltaCsNew.MacroMode"] = uint16_t(2);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.MacroMode");
}

TEST_F(MacroModeTest_516, SingleUnrelatedKeyReturnsEnd_516) {
    ed["Exif.Image.Make"] = "TestCamera";
    auto it = Exiv2::macroMode(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(MacroModeTest_516, MultipleUnrelatedKeysReturnEnd_516) {
    ed["Exif.Image.Make"] = "TestCamera";
    ed["Exif.Image.Model"] = "TestModel";
    ed["Exif.Photo.ExposureTime"] = "1/100";
    auto it = Exiv2::macroMode(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(MacroModeTest_516, LastPriorityKeySony2Found_516) {
    // Only the last priority key is present
    ed["Exif.Image.Make"] = "Sony";
    ed["Exif.Sony2.Macro"] = uint16_t(1);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.Macro");
}

TEST_F(MacroModeTest_516, AllKeysPresent_ReturnsFirstPriority_516) {
    ed["Exif.CanonCs.Macro"] = uint16_t(1);
    ed["Exif.Fujifilm.Macro"] = uint16_t(2);
    ed["Exif.Olympus.Macro"] = uint16_t(3);
    ed["Exif.Olympus2.Macro"] = uint16_t(4);
    ed["Exif.OlympusCs.MacroMode"] = uint16_t(5);
    ed["Exif.Panasonic.Macro"] = uint16_t(6);
    ed["Exif.MinoltaCsNew.MacroMode"] = uint16_t(7);
    ed["Exif.MinoltaCsOld.MacroMode"] = uint16_t(8);
    ed["Exif.Sony1.Macro"] = uint16_t(9);
    ed["Exif.Sony2.Macro"] = uint16_t(10);
    auto it = Exiv2::macroMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Macro");
}
