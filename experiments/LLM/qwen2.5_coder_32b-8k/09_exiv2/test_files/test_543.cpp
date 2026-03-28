#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class AFPointTest_543 : public ::testing::Test {

protected:

    ExifData exif_data;

};



TEST_F(AFPointTest_543, NormalOperation_543) {

    const char* key = "Exif.CanonPi.AFPointsUsed";

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::unsignedLong);

    value->read("1");

    exif_data.add(key, value);



    auto it = afPoint(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(AFPointTest_543, BoundaryConditions_NoAFPoints_543) {

    auto it = afPoint(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(AFPointTest_543, BoundaryConditions_EmptyExifData_543) {

    exif_data.clear();

    auto it = afPoint(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(AFPointTest_543, ExceptionalCases_InvalidKey_543) {

    const char* key = "Exif.Invalid.AFPointsUsed";

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::unsignedLong);

    value->read("1");

    exif_data.add(key, value);



    auto it = afPoint(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(AFPointTest_543, MultipleAFPoints_ReturnsFirstMatch_543) {

    const char* key1 = "Exif.CanonPi.AFPointsUsed";

    Exiv2::Value* value1 = Exiv2::Value::create(Exiv2::unsignedLong);

    value1->read("1");

    exif_data.add(key1, value1);



    const char* key2 = "Exif.Nikon1.AFFocusPos";

    Exiv2::Value* value2 = Exiv2::Value::create(Exiv2::unsignedLong);

    value2->read("2");

    exif_data.add(key2, value2);



    auto it = afPoint(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key1);

}
