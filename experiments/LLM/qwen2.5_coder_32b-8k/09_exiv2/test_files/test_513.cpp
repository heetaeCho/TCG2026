#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class FlashBiasTest : public ::testing::Test {

protected:

    ExifData exif_data;

};



TEST_F(FlashBiasTest_513, NormalOperationWithCanon_513) {

    ExifKey key("Exif.CanonSi.FlashBias");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key.key());

}



TEST_F(FlashBiasTest_513, NormalOperationWithPanasonic_513) {

    ExifKey key("Exif.Panasonic.FlashBias");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key.key());

}



TEST_F(FlashBiasTest_513, NormalOperationWithOlympus_513) {

    ExifKey key("Exif.Olympus.FlashBias");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key.key());

}



TEST_F(FlashBiasTest_513, NormalOperationWithOlympusCs_513) {

    ExifKey key("Exif.OlympusCs.FlashExposureComp");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key.key());

}



TEST_F(FlashBiasTest_513, NormalOperationWithMinolta_513) {

    ExifKey key("Exif.Minolta.FlashExposureComp");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key.key());

}



TEST_F(FlashBiasTest_513, NormalOperationWithSonyMinolta_513) {

    ExifKey key("Exif.SonyMinolta.FlashExposureComp");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key.key());

}



TEST_F(FlashBiasTest_513, NormalOperationWithSony1_513) {

    ExifKey key("Exif.Sony1.FlashExposureComp");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key.key());

}



TEST_F(FlashBiasTest_513, NormalOperationWithSony2_513) {

    ExifKey key("Exif.Sony2.FlashExposureComp");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    ASSERT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), key.key());

}



TEST_F(FlashBiasTest_513, BoundaryConditionWithEmptyExifData_513) {

    ExifData::const_iterator it = flashBias(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(FlashBiasTest_513, BoundaryConditionWithNoRelevantKeys_513) {

    ExifKey key("Exif.SomeOther.Key");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(FlashBiasTest_513, ExceptionalCaseWithInvalidKeyFormat_513) {

    // Invalid key format should not affect the function

    ExifKey key("Exif.Invalid.Key");

    Value* value = new ShortValue();

    value->read("2");

    exif_data.add(key, value);

    ExifData::const_iterator it = flashBias(exif_data);

    EXPECT_EQ(it, exif_data.end());

}
