#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class MakeTest_525 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(MakeTest_525, ReturnsEndWhenExifDataIsEmpty_525) {
    auto it = Exiv2::make(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(MakeTest_525, FindsExifImageMake_525) {
    ed["Exif.Image.Make"] = "Canon";
    auto it = Exiv2::make(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
    EXPECT_EQ(it->toString(), "Canon");
}

TEST_F(MakeTest_525, FindsExifPanasonicRawMake_525) {
    ed["Exif.PanasonicRaw.Make"] = "Panasonic";
    auto it = Exiv2::make(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PanasonicRaw.Make");
    EXPECT_EQ(it->toString(), "Panasonic");
}

TEST_F(MakeTest_525, PrefersExifImageMakeOverPanasonicRawMake_525) {
    ed["Exif.Image.Make"] = "Canon";
    ed["Exif.PanasonicRaw.Make"] = "Panasonic";
    auto it = Exiv2::make(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
    EXPECT_EQ(it->toString(), "Canon");
}

TEST_F(MakeTest_525, FallsBackToPanasonicRawMakeWhenImageMakeAbsent_525) {
    ed["Exif.PanasonicRaw.Make"] = "Panasonic";
    auto it = Exiv2::make(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PanasonicRaw.Make");
    EXPECT_EQ(it->toString(), "Panasonic");
}

TEST_F(MakeTest_525, ReturnsEndWhenUnrelatedKeysExist_525) {
    ed["Exif.Image.Model"] = "EOS 5D";
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    auto it = Exiv2::make(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(MakeTest_525, HandlesEmptyValueForExifImageMake_525) {
    ed["Exif.Image.Make"] = "";
    auto it = Exiv2::make(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
    EXPECT_EQ(it->toString(), "");
}

TEST_F(MakeTest_525, HandlesLongMakeValue_525) {
    std::string longMake(1000, 'A');
    ed["Exif.Image.Make"] = longMake;
    auto it = Exiv2::make(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
    EXPECT_EQ(it->toString(), longMake);
}

TEST_F(MakeTest_525, WorksWithManyUnrelatedKeys_525) {
    for (int i = 0; i < 100; ++i) {
        ed["Exif.Image.Model"] = "SomeModel";
    }
    ed["Exif.Image.Make"] = "Nikon";
    auto it = Exiv2::make(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
    EXPECT_EQ(it->toString(), "Nikon");
}

TEST_F(MakeTest_525, ConstExifDataWorks_525) {
    ed["Exif.Image.Make"] = "Sony";
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::make(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Image.Make");
    EXPECT_EQ(it->toString(), "Sony");
}
