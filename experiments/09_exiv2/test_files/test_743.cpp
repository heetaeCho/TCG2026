#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifdatumTest_743 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> exifKey;

    std::unique_ptr<Value> value;

    Exifdatum* exifDatum;



    void SetUp() override {

        exifKey = std::make_unique<ExifKey>("Exif.Image.Artist");

        value = std::make_unique<StringValue>(StringValue("TestArtist"));

        exifDatum = new Exifdatum(*exifKey, value.get());

    }



    void TearDown() override {

        delete exifDatum;

    }

};



TEST_F(ExifdatumTest_743, FamilyName_ReturnsCorrectFamilyName_743) {

    EXPECT_STREQ(exifDatum->familyName(), "Exif");

}



TEST_F(ExifdatumTest_743, FamilyName_ReturnsEmptyStringWhenKeyIsNull_743) {

    Exifdatum exifDatumWithoutKey({}, value.get());

    EXPECT_STREQ(exifDatumWithoutKey.familyName(), "");

}



TEST_F(ExifdatumTest_743, FamilyName_NotModifiedBySetValue_743) {

    exifDatum->setValue("NewArtist");

    EXPECT_STREQ(exifDatum->familyName(), "Exif");

}
