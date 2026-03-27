#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "easyaccess.cpp"



using namespace Exiv2;



class IsoSpeedTest : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(IsoSpeedTest_NormalOperation_511, FindsValidIsoSpeed_511) {

    Exifdatum exifDatum("Exif.Photo.ISOSpeedRatings", new UShortValue);

    exifDatum.setValue(static_cast<uint16_t>(800));

    ed.add(exifDatum);



    auto it = isoSpeed(ed);

    ASSERT_NE(it, ed.end());

    EXPECT_EQ(it->toInt64(), 800);

}



TEST_F(IsoSpeedTest_NormalOperation_511, FindsValidIsoFromSensitivityType_511) {

    Exifdatum sensitivityTypeDatum("Exif.Photo.SensitivityType", new UShortValue);

    sensitivityTypeDatum.setValue(static_cast<uint16_t>(3));

    ed.add(sensitivityTypeDatum);



    Exifdatum isoSpeedDatum("Exif.Photo.ISOSpeed", new UShortValue);

    isoSpeedDatum.setValue(static_cast<uint16_t>(800));

    ed.add(isoSpeedDatum);



    auto it = isoSpeed(ed);

    ASSERT_NE(it, ed.end());

    EXPECT_EQ(it->toInt64(), 800);

}



TEST_F(IsoSpeedTest_BoundaryConditions_511, EmptyExifData_511) {

    auto it = isoSpeed(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(IsoSpeedTest_ErrorCases_511, InvalidIsoValue_511) {

    Exifdatum exifDatum("Exif.Photo.ISOSpeedRatings", new UShortValue);

    exifDatum.setValue(static_cast<uint16_t>(0));

    ed.add(exifDatum);



    auto it = isoSpeed(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(IsoSpeedTest_ErrorCases_511, InvalidSensitivityType_511) {

    Exifdatum sensitivityTypeDatum("Exif.Photo.SensitivityType", new UShortValue);

    sensitivityTypeDatum.setValue(static_cast<uint16_t>(8)); // Out of bounds

    ed.add(sensitivityTypeDatum);



    auto it = isoSpeed(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(IsoSpeedTest_ErrorCases_511, InfValueInIso_511) {

    Exifdatum exifDatum("Exif.Photo.ISOSpeedRatings", new UShortValue);

    exifDatum.setValue(static_cast<uint16_t>(std::numeric_limits<uint16_t>::max()));

    ed.add(exifDatum);



    auto it = isoSpeed(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(IsoSpeedTest_ErrorCases_511, NegativeIsoValue_511) {

    Exifdatum exifDatum("Exif.Photo.ISOSpeedRatings", new ShortValue);

    exifDatum.setValue(static_cast<int16_t>(-1));

    ed.add(exifDatum);



    auto it = isoSpeed(ed);

    EXPECT_EQ(it, ed.end());

}
