#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/metadatum.hpp"



using namespace Exiv2;

using namespace testing;



namespace {

    bool getAFAreaModeSetting(const ExifData* metadata, uint32_t& val) {

        return Internal::getAFAreaModeSetting(metadata, val);

    }

}



class SonyMNTest_1585 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(SonyMNTest_1585, NormalOperation_ExifSoniaAFAModeSetting_1585) {

    uint32_t val = 0;

    ExifKey key("Exif.Sony1.AFAreaModeSetting");

    Exifdatum exifDatum(key, new UByteValue(1));

    exifData.add(exifDatum);

    

    EXPECT_TRUE(getAFAreaModeSetting(&exifData, val));

    EXPECT_EQ(val, 1U);

}



TEST_F(SonyMNTest_1585, NormalOperation_ExifSony2AFAModeSetting_1585) {

    uint32_t val = 0;

    ExifKey key("Exif.Sony2.AFAreaModeSetting");

    Exifdatum exifDatum(key, new UByteValue(2));

    exifData.add(exifDatum);

    

    EXPECT_TRUE(getAFAreaModeSetting(&exifData, val));

    EXPECT_EQ(val, 2U);

}



TEST_F(SonyMNTest_1585, BoundaryCondition_EmptyExifData_1585) {

    uint32_t val = 42;

    EXPECT_FALSE(getAFAreaModeSetting(&exifData, val));

    EXPECT_EQ(val, 0U);

}



TEST_F(SonyMNTest_1585, BoundaryCondition_ZeroSizeMetadatum_1585) {

    uint32_t val = 0;

    ExifKey key("Exif.Sony1.AFAreaModeSetting");

    Exifdatum exifDatum(key, new UByteValue());

    exifData.add(exifDatum);

    

    EXPECT_FALSE(getAFAreaModeSetting(&exifData, val));

    EXPECT_EQ(val, 0U);

}



TEST_F(SonyMNTest_1585, BoundaryCondition_IncorrectTypeId_1585) {

    uint32_t val = 0;

    ExifKey key("Exif.Sony1.AFAreaModeSetting");

    Exifdatum exifDatum(key, new AsciiValue("dummy"));

    exifData.add(exifDatum);

    

    EXPECT_FALSE(getAFAreaModeSetting(&exifData, val));

    EXPECT_EQ(val, 0U);

}



TEST_F(SonyMNTest_1585, BoundaryCondition_NaString_1585) {

    uint32_t val = 0;

    ExifKey key("Exif.Sony1.AFAreaModeSetting");

    Exifdatum exifDatum(key, new AsciiValue("n/a"));

    exifData.add(exifDatum);

    

    EXPECT_FALSE(getAFAreaModeSetting(&exifData, val));

    EXPECT_EQ(val, 0U);

}



TEST_F(SonyMNTest_1585, ErrorCase_MissingKeys_1585) {

    uint32_t val = 42;

    ExifKey key("Exif.SomethingElse");

    Exifdatum exifDatum(key, new UByteValue(1));

    exifData.add(exifDatum);

    

    EXPECT_FALSE(getAFAreaModeSetting(&exifData, val));

    EXPECT_EQ(val, 0U);

}
