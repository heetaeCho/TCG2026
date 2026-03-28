#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class SubjectDistanceTest : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(SubjectDistanceTest_534, NormalOperationFound_534) {

    Exifdatum datum("Exif.Photo.SubjectDistance", 0);

    exifData.add(datum.key(), &datum.value());

    auto it = subjectDistance(exifData);

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.SubjectDistance");

}



TEST_F(SubjectDistanceTest_534, NormalOperationNotFound_534) {

    auto it = subjectDistance(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(SubjectDistanceTest_534, BoundaryConditionEmptyMetadata_534) {

    exifData.clear();

    auto it = subjectDistance(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(SubjectDistanceTest_534, BoundaryConditionMultipleKeysPresent_534) {

    Exifdatum datum1("Exif.Image.SubjectDistance", 0);

    Exifdatum datum2("Exif.CanonSi.SubjectDistance", 0);

    exifData.add(datum1.key(), &datum1.value());

    exifData.add(datum2.key(), &datum2.value());



    auto it = subjectDistance(exifData);

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Image.SubjectDistance");

}



TEST_F(SubjectDistanceTest_534, BoundaryConditionFirstKeyPresent_534) {

    Exifdatum datum("Exif.Photo.SubjectDistance", 0);

    exifData.add(datum.key(), &datum.value());



    auto it = subjectDistance(exifData);

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.SubjectDistance");

}



TEST_F(SubjectDistanceTest_534, BoundaryConditionLastKeyPresent_534) {

    Exifdatum datum("Exif.Casio2.ObjectDistance", 0);

    exifData.add(datum.key(), &datum.value());



    auto it = subjectDistance(exifData);

    EXPECT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Casio2.ObjectDistance");

}
