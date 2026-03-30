#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {

    class ExifData;

    ExifData::const_iterator lensName(const ExifData& ed);

}



using namespace Exiv2;



class LensNameTest_519 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(LensNameTest_519, FindCanonLensType_519) {

    ExifKey key("Exif.CanonCs.LensType");

    Value* value = new StringValue("Some Lens Type");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.CanonCs.LensType");

}



TEST_F(LensNameTest_519, FindOlympusLensType_519) {

    ExifKey key("Exif.OlympusEq.LensType");

    Value* value = new StringValue("Some Lens Type");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.OlympusEq.LensType");

}



TEST_F(LensNameTest_519, FindPentaxLensType_519) {

    ExifKey key("Exif.Pentax.LensType");

    Value* value = new StringValue("Some Lens Type");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Pentax.LensType");

}



TEST_F(LensNameTest_519, FindPentaxDngLensType_519) {

    ExifKey key("Exif.PentaxDng.LensType");

    Value* value = new StringValue("Some Lens Type");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.PentaxDng.LensType");

}



TEST_F(LensNameTest_519, FindPhotoLensModel_519) {

    ExifKey key("Exif.Photo.LensModel");

    Value* value = new StringValue("Some Lens Model");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.LensModel");

}



TEST_F(LensNameTest_519, FindCanonLensModel_519) {

    ExifKey key("Exif.Canon.LensModel");

    Value* value = new StringValue("Some Lens Model");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Canon.LensModel");

}



TEST_F(LensNameTest_519, FindNikonLd1LensIDNumber_519) {

    ExifKey key("Exif.NikonLd1.LensIDNumber");

    Value* value = new StringValue("Some Lens ID Number");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.NikonLd1.LensIDNumber");

}



TEST_F(LensNameTest_519, FindNikonLd2LensIDNumber_519) {

    ExifKey key("Exif.NikonLd2.LensIDNumber");

    Value* value = new StringValue("Some Lens ID Number");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.NikonLd2.LensIDNumber");

}



TEST_F(LensNameTest_519, FindNikonLd3LensIDNumber_519) {

    ExifKey key("Exif.NikonLd3.LensIDNumber");

    Value* value = new StringValue("Some Lens ID Number");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.NikonLd3.LensIDNumber");

}



TEST_F(LensNameTest_519, FindNikonLd4LensID_519) {

    ExifKey key("Exif.NikonLd4.LensID");

    Value* value = new StringValue("Some Lens ID");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.NikonLd4.LensID");

}



TEST_F(LensNameTest_519, FindNikonLd4LensIDNumber_519) {

    ExifKey key("Exif.NikonLd4.LensIDNumber");

    Value* value = new StringValue("Some Lens ID Number");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.NikonLd4.LensIDNumber");

}



TEST_F(LensNameTest_519, FindMinoltaLensID_519) {

    ExifKey key("Exif.Minolta.LensID");

    Value* value = new StringValue("Some Lens ID");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Minolta.LensID");

}



TEST_F(LensNameTest_519, FindSonyMinoltaLensID_519) {

    ExifKey key("Exif.SonyMinolta.LensID");

    Value* value = new StringValue("Some Lens ID");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.SonyMinolta.LensID");

}



TEST_F(LensNameTest_519, FindSony1LensID_519) {

    ExifKey key("Exif.Sony1.LensID");

    Value* value = new StringValue("Some Lens ID");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Sony1.LensID");

}



TEST_F(LensNameTest_519, FindSony2LensID_519) {

    ExifKey key("Exif.Sony2.LensID");

    Value* value = new StringValue("Some Lens ID");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Sony2.LensID");

}



TEST_F(LensNameTest_519, FindSony1LensSpec_519) {

    ExifKey key("Exif.Sony1.LensSpec");

    Value* value = new StringValue("Some Lens Spec");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Sony1.LensSpec");

}



TEST_F(LensNameTest_519, FindSony2LensSpec_519) {

    ExifKey key("Exif.Sony2.LensSpec");

    Value* value = new StringValue("Some Lens Spec");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Sony2.LensSpec");

}



TEST_F(LensNameTest_519, FindPanasonicLensType_519) {

    ExifKey key("Exif.Panasonic.LensType");

    Value* value = new StringValue("Some Lens Type");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Panasonic.LensType");

}



TEST_F(LensNameTest_519, FindSamsung2LensType_519) {

    ExifKey key("Exif.Samsung2.LensType");

    Value* value = new StringValue("Some Lens Type");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Samsung2.LensType");

}



TEST_F(LensNameTest_519, FindPhotoLensSpecification_519) {

    ExifKey key("Exif.Photo.LensSpecification");

    Value* value = new StringValue("Some Lens Specification");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.LensSpecification");

}



TEST_F(LensNameTest_519, FindNikon3Lens_519) {

    ExifKey key("Exif.Nikon3.Lens");

    Value* value = new StringValue("Some Lens");

    exifData.add(key, value);

    auto it = lensName(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Nikon3.Lens");

}



TEST_F(LensNameTest_519, NoLensMetadata_519) {

    auto it = lensName(exifData);

    EXPECT_EQ(it, exifData.end());

}
