#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"



namespace Exiv2 {

    void syncExifWithXmp(ExifData& exifData, XmpData& xmpData);

}



class SyncExifWithXmpTest_1859 : public ::testing::Test {

protected:

    Exiv2::ExifData exifData;

    Exiv2::XmpData xmpData;



    void SetUp() override {

        // Setup any common state here

    }



    void TearDown() override {

        // Cleanup any common state here

    }

};



TEST_F(SyncExifWithXmpTest_1859, EmptyDataSync_1859) {

    Exiv2::syncExifWithXmp(exifData, xmpData);

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(SyncExifWithXmpTest_1859, SingleEntrySync_1859) {

    Exiv2::Value* value = new Exiv2::AsciiValue("test_value");

    exifData.add(Exiv2::ExifKey("Exif.Image.Artist"), value);

    Exiv2::syncExifWithXmp(exifData, xmpData);

    EXPECT_EQ(xmpData.count(), 1);

}



TEST_F(SyncExifWithXmpTest_1859, MultipleEntriesSync_1859) {

    Exiv2::Value* value1 = new Exiv2::AsciiValue("test_value1");

    Exiv2::Value* value2 = new Exiv2::AsciiValue("test_value2");

    exifData.add(Exiv2::ExifKey("Exif.Image.Artist"), value1);

    exifData.add(Exiv2::ExifKey("Exif.Photo.UserComment"), value2);

    Exiv2::syncExifWithXmp(exifData, xmpData);

    EXPECT_EQ(xmpData.count(), 2);

}



TEST_F(SyncExifWithXmpTest_1859, OverwriteExistingEntrySync_1859) {

    Exiv2::Value* value1 = new Exiv2::AsciiValue("test_value1");

    exifData.add(Exiv2::ExifKey("Exif.Image.Artist"), value1);

    Exiv2::syncExifWithXmp(exifData, xmpData);



    Exiv2::Value* newValue = new Exiv2::AsciiValue("new_test_value");

    exifData["Exif.Image.Artist"] = *newValue;

    Exiv2::syncExifWithXmp(exifData, xmpData);

    EXPECT_EQ(xmpData.count(), 1);

}



TEST_F(SyncExifWithXmpTest_1859, EraseEntrySync_1859) {

    Exiv2::Value* value = new Exiv2::AsciiValue("test_value");

    exifData.add(Exiv2::ExifKey("Exif.Image.Artist"), value);

    Exiv2::syncExifWithXmp(exifData, xmpData);



    exifData.erase(exifData.findKey(Exiv2::ExifKey("Exif.Image.Artist")));

    Exiv2::syncExifWithXmp(exifData, xmpData);

    EXPECT_TRUE(xmpData.empty());

}
