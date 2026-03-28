#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifdatumTest_744 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> exifKey;

    Value* value = nullptr;

    Exifdatum exifDatum;



    void SetUp() override {

        exifKey = std::make_unique<ExifKey>("0x9003", "Exif.Image");

        exifDatum = Exifdatum(*exifKey, value);

    }

};



TEST_F(ExifdatumTest_744, GroupName_ReturnsCorrectGroupName_744) {

    EXPECT_EQ(exifDatum.groupName(), "Exif.Image");

}



TEST_F(ExifdatumTest_744, GroupName_ReturnsEmptyStringWhenKeyIsNull_744) {

    Exifdatum exifDatumWithoutKey(ExifKey(""), value);

    EXPECT_EQ(exifDatumWithoutKey.groupName(), "");

}
