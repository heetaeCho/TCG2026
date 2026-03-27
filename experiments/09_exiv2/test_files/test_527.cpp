#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



namespace {



class ExposureTimeTest : public ::testing::Test {

protected:

    Exiv2::ExifData ed;

};



TEST_F(ExposureTimeTest_527, NormalOperationWithValidKey_527) {

    const char* key = "Exif.Photo.ExposureTime";

    auto value = std::make_unique<Exiv2::RationalValue>(1, 100);

    ed.add(Exiv2::ExifKey(key), value.get());

    

    auto it = Exiv2::exposureTime(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(ExposureTimeTest_527, BoundaryConditionWithNoMatchingKeys_527) {

    auto it = Exiv2::exposureTime(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(ExposureTimeTest_527, BoundaryConditionWithEmptyExifData_527) {

    ed.clear();

    auto it = Exiv2::exposureTime(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(ExposureTimeTest_527, NormalOperationWithMultiplePossibleKeys_527) {

    const char* keys[] = {"Exif.Image.ExposureTime", "Exif.Pentax.ExposureTime"};

    for (const auto& key : keys) {

        auto value = std::make_unique<Exiv2::RationalValue>(1, 100);

        ed.add(Exiv2::ExifKey(key), value.get());

    }



    auto it = Exiv2::exposureTime(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Image.ExposureTime");

}



TEST_F(ExposureTimeTest_527, NormalOperationWithLastPossibleKey_527) {

    const char* key = "Exif.Samsung2.ExposureTime";

    auto value = std::make_unique<Exiv2::RationalValue>(1, 100);

    ed.add(Exiv2::ExifKey(key), value.get());



    auto it = Exiv2::exposureTime(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), key);

}



}  // namespace
