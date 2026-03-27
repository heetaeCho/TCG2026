#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifdatumTest_750 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> exifKey;

    Value* valuePtr = nullptr; // Assuming no specific value is needed for the test

    Exifdatum exifDatum;



    void SetUp() override {

        exifKey = std::make_unique<ExifKey>("Exif.Image.Artist");

        exifDatum = Exifdatum(*exifKey, valuePtr);

    }

};



TEST_F(ExifdatumTest_750, IfdName_ReturnsCorrectValueForKnownTag_750) {

    EXPECT_STREQ(exifDatum.ifdName(), "IFD0");

}



TEST_F(ExifdatumTest_750, IfdName_ReturnsEmptyStringForNullKey_750) {

    Exifdatum exifDatumWithoutKey = Exifdatum(ExifKey(""), nullptr);

    EXPECT_STREQ(exifDatumWithoutKey.ifdName(), "");

}
