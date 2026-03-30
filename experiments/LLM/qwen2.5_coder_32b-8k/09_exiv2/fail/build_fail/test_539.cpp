#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class SubjectAreaTest_539 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(SubjectAreaTest_539, FindSubjectAreaKey_539) {

    // Arrange

    const std::string key = "Exif.Photo.SubjectArea";

    exifData.add(ExifKey(key), new LongValue());



    // Act

    auto it = subjectArea(exifData);



    // Assert

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(SubjectAreaTest_539, FindSubjectLocationKey_539) {

    // Arrange

    const std::string key = "Exif.Image.SubjectLocation";

    exifData.add(ExifKey(key), new LongValue());



    // Act

    auto it = subjectArea(exifData);



    // Assert

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(SubjectAreaTest_539, NoMatchingKeys_539) {

    // Arrange

    const std::string key1 = "Exif.Image.Artist";

    const std::string key2 = "Exif.Photo.DateTime";

    exifData.add(ExifKey(key1), new AsciiValue());

    exifData.add(ExifKey(key2), new AsciiValue());



    // Act

    auto it = subjectArea(exifData);



    // Assert

    EXPECT_EQ(it, exifData.end());

}



TEST_F(SubjectAreaTest_539, MultipleMatchingKeys_539) {

    // Arrange

    const std::string key1 = "Exif.Photo.SubjectArea";

    const std::string key2 = "Exif.Image.SubjectLocation";

    exifData.add(ExifKey(key1), new LongValue());

    exifData.add(ExifKey(key2), new LongValue());



    // Act

    auto it = subjectArea(exifData);



    // Assert

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), key1);  // Should return the first match

}



TEST_F(SubjectAreaTest_539, EmptyExifData_539) {

    // Arrange (nothing to do)



    // Act

    auto it = subjectArea(exifData);



    // Assert

    EXPECT_EQ(it, exifData.end());

}
