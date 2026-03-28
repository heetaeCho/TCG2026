#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



// Test fixture for dateTimeOriginal function tests

class DateTimeOriginalTest_512 : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(DateTimeOriginalTest_512, FoundExifPhotoDateTimeOriginal_512) {

    // Arrange

    const char* key = "Exif.Photo.DateTimeOriginal";

    Exifdatum datum(key);

    ed.add(datum);



    // Act

    auto it = dateTimeOriginal(ed);



    // Assert

    EXPECT_EQ(it->key(), key);

}



TEST_F(DateTimeOriginalTest_512, FoundExifImageDateTimeOriginal_512) {

    // Arrange

    const char* key = "Exif.Image.DateTimeOriginal";

    Exifdatum datum(key);

    ed.add(datum);



    // Act

    auto it = dateTimeOriginal(ed);



    // Assert

    EXPECT_EQ(it->key(), key);

}



TEST_F(DateTimeOriginalTest_512, NotFoundDateTimeOriginal_512) {

    // Arrange - No DateTimeOriginal keys added



    // Act

    auto it = dateTimeOriginal(ed);



    // Assert

    EXPECT_EQ(it, ed.end());

}



TEST_F(DateTimeOriginalTest_512, MultipleEntriesFoundExifPhotoDateTimeOriginalFirst_512) {

    // Arrange

    Exifdatum photoDatum("Exif.Photo.DateTimeOriginal");

    Exifdatum imageDatum("Exif.Image.DateTimeOriginal");

    ed.add(photoDatum);

    ed.add(imageDatum);



    // Act

    auto it = dateTimeOriginal(ed);



    // Assert

    EXPECT_EQ(it->key(), "Exif.Photo.DateTimeOriginal");

}



TEST_F(DateTimeOriginalTest_512, MultipleEntriesFoundExifImageDateTimeOriginalFirst_512) {

    // Arrange

    Exifdatum imageDatum("Exif.Image.DateTimeOriginal");

    Exifdatum photoDatum("Exif.Photo.DateTimeOriginal");

    ed.add(imageDatum);

    ed.add(photoDatum);



    // Act

    auto it = dateTimeOriginal(ed);



    // Assert

    EXPECT_EQ(it->key(), "Exif.Image.DateTimeOriginal");

}



TEST_F(DateTimeOriginalTest_512, EmptyExifData_512) {

    // Arrange - ExifData is empty



    // Act

    auto it = dateTimeOriginal(ed);



    // Assert

    EXPECT_EQ(it, ed.end());

}
