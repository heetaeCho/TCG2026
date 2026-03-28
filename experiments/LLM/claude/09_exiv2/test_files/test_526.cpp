#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class ModelTest_526 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that model() returns end() when ExifData is empty
TEST_F(ModelTest_526, EmptyExifDataReturnsEnd_526) {
    auto it = Exiv2::model(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that model() finds "Exif.Image.Model" (first priority key)
TEST_F(ModelTest_526, FindsImageModel_526) {
    ed["Exif.Image.Model"] = "Canon EOS 5D";
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Model");
    EXPECT_EQ(it->toString(), "Canon EOS 5D");
}

// Test that model() finds "Exif.MinoltaCsOld.MinoltaModel"
TEST_F(ModelTest_526, FindsMinoltaCsOldModel_526) {
    ed["Exif.MinoltaCsOld.MinoltaModel"] = "Minolta Old";
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.MinoltaModel");
}

// Test that model() finds "Exif.MinoltaCsNew.MinoltaModel"
TEST_F(ModelTest_526, FindsMinoltaCsNewModel_526) {
    ed["Exif.MinoltaCsNew.MinoltaModel"] = "Minolta New";
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.MinoltaModel");
}

// Test that model() finds "Exif.PanasonicRaw.Model"
TEST_F(ModelTest_526, FindsPanasonicRawModel_526) {
    ed["Exif.PanasonicRaw.Model"] = "Panasonic Raw";
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PanasonicRaw.Model");
}

// Test that model() finds "Exif.Pentax.ModelID"
TEST_F(ModelTest_526, FindsPentaxModelID_526) {
    ed["Exif.Pentax.ModelID"] = uint16_t(12345);
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.ModelID");
}

// Test that model() finds "Exif.PentaxDng.ModelID"
TEST_F(ModelTest_526, FindsPentaxDngModelID_526) {
    ed["Exif.PentaxDng.ModelID"] = uint16_t(54321);
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.ModelID");
}

// Test that model() finds "Exif.Sony1.SonyModelID"
TEST_F(ModelTest_526, FindsSony1ModelID_526) {
    ed["Exif.Sony1.SonyModelID"] = uint16_t(100);
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.SonyModelID");
}

// Test that model() finds "Exif.Sony2.SonyModelID"
TEST_F(ModelTest_526, FindsSony2ModelID_526) {
    ed["Exif.Sony2.SonyModelID"] = uint16_t(200);
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.SonyModelID");
}

// Test priority: "Exif.Image.Model" should be returned when both it and lower-priority keys exist
TEST_F(ModelTest_526, PriorityImageModelOverSony_526) {
    ed["Exif.Sony1.SonyModelID"] = uint16_t(100);
    ed["Exif.Image.Model"] = "Canon EOS R5";
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Model");
}

// Test priority: MinoltaCsOld over MinoltaCsNew when both are present (but no Image.Model)
TEST_F(ModelTest_526, PriorityMinoltaOldOverNew_526) {
    ed["Exif.MinoltaCsNew.MinoltaModel"] = "New Minolta";
    ed["Exif.MinoltaCsOld.MinoltaModel"] = "Old Minolta";
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.MinoltaModel");
}

// Test that unrelated keys do not match
TEST_F(ModelTest_526, UnrelatedKeysReturnEnd_526) {
    ed["Exif.Image.Make"] = "Canon";
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:01 12:00:00";
    auto it = Exiv2::model(ed);
    EXPECT_EQ(it, ed.end());
}

// Test priority: PanasonicRaw over Pentax
TEST_F(ModelTest_526, PriorityPanasonicOverPentax_526) {
    ed["Exif.Pentax.ModelID"] = uint16_t(111);
    ed["Exif.PanasonicRaw.Model"] = "Panasonic GH5";
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PanasonicRaw.Model");
}

// Test priority: Pentax over PentaxDng
TEST_F(ModelTest_526, PriorityPentaxOverPentaxDng_526) {
    ed["Exif.PentaxDng.ModelID"] = uint16_t(222);
    ed["Exif.Pentax.ModelID"] = uint16_t(111);
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.ModelID");
}

// Test priority: Sony1 over Sony2
TEST_F(ModelTest_526, PrioritySony1OverSony2_526) {
    ed["Exif.Sony2.SonyModelID"] = uint16_t(200);
    ed["Exif.Sony1.SonyModelID"] = uint16_t(100);
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.SonyModelID");
}

// Test with all keys present - highest priority should win
TEST_F(ModelTest_526, AllKeysPresent_526) {
    ed["Exif.Image.Model"] = "Canon EOS 5D";
    ed["Exif.MinoltaCsOld.MinoltaModel"] = "Old Minolta";
    ed["Exif.MinoltaCsNew.MinoltaModel"] = "New Minolta";
    ed["Exif.PanasonicRaw.Model"] = "Panasonic";
    ed["Exif.Pentax.ModelID"] = uint16_t(111);
    ed["Exif.PentaxDng.ModelID"] = uint16_t(222);
    ed["Exif.Sony1.SonyModelID"] = uint16_t(100);
    ed["Exif.Sony2.SonyModelID"] = uint16_t(200);
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Model");
}

// Test that the returned iterator can be dereferenced and value is correct
TEST_F(ModelTest_526, ReturnedIteratorValueCorrect_526) {
    ed["Exif.Image.Model"] = "Nikon D850";
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toString(), "Nikon D850");
}

// Test with only the last priority key
TEST_F(ModelTest_526, OnlyLastPriorityKey_526) {
    ed["Exif.Sony2.SonyModelID"] = uint16_t(300);
    auto it = Exiv2::model(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.SonyModelID");
}

// Test const correctness - model takes const ExifData&
TEST_F(ModelTest_526, ConstExifDataAccess_526) {
    ed["Exif.Image.Model"] = "Test Camera";
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::model(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Image.Model");
    EXPECT_EQ(it->toString(), "Test Camera");
}
