#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class ExifDataModelTest : public ::testing::Test {

protected:

    ExifData exif_data;

};



TEST_F(ExifDataModelTest_526, NormalOperation_ModelFound_526) {

    const char* modelKey = "Exif.Image.Model";

    Exifdatum datum(modelKey);

    datum.setValue("Test Model");

    exif_data.add(datum);



    ExifData::const_iterator it = Exiv2::model(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), modelKey);

}



TEST_F(ExifDataModelTest_526, NormalOperation_ModelNotFound_526) {

    ExifData::const_iterator it = Exiv2::model(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(ExifDataModelTest_526, BoundaryCondition_EmptyExifData_526) {

    ExifData::const_iterator it = Exiv2::model(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(ExifDataModelTest_526, BoundaryCondition_MultipleModels_526) {

    const char* modelKey1 = "Exif.Image.Model";

    const char* modelKey2 = "Exif.MinoltaCsOld.MinoltaModel";



    Exifdatum datum1(modelKey1);

    datum1.setValue("Test Model 1");

    exif_data.add(datum1);



    Exifdatum datum2(modelKey2);

    datum2.setValue("Test Model 2");

    exif_data.add(datum2);



    ExifData::const_iterator it = Exiv2::model(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), modelKey1); // Should return the first found key

}



TEST_F(ExifDataModelTest_526, ExceptionalCase_ModelKeyEmpty_526) {

    Exifdatum datum("");

    datum.setValue("Invalid Model");

    exif_data.add(datum);



    ExifData::const_iterator it = Exiv2::model(exif_data);

    EXPECT_EQ(it, exif_data.end());

}
