#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/minoltamn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class getKeyLongTest_1012 : public ::testing::Test {

protected:

    void SetUp() override {

        metadata = std::make_unique<ExifData>();

    }



    std::unique_ptr<ExifData> metadata;

};



TEST_F(getKeyLongTest_1012, KeyNotFound_ReturnsNegativeOne_1012) {

    EXPECT_EQ(getKeyLong("NonExistentKey", metadata.get(), 0), -1);

}



TEST_F(getKeyLongTest_1012, ValidKeyWithFloatValue_ReturnsCorrectLong_1012) {

    Exifdatum exifDatum(ExifKey("ValidKey"), new FloatValue(3.5f));

    metadata->add(exifDatum);



    EXPECT_EQ(getKeyLong("ValidKey", metadata.get(), 0), static_cast<long>(3.5f));

}



TEST_F(getKeyLongTest_1012, ValidKeyWithMultipleValues_ReturnsFirstFloatAsLong_1012) {

    Exifdatum exifDatum(ExifKey("MultiValueKey"), new FloatValue({3.5f, 4.5f}));

    metadata->add(exifDatum);



    EXPECT_EQ(getKeyLong("MultiValueKey", metadata.get(), 0), static_cast<long>(3.5f));

}



TEST_F(getKeyLongTest_1012, ValidKeyWithNonFloatValue_ReturnsNegativeOne_1012) {

    Exifdatum exifDatum(ExifKey("NonFloatKey"), new ShortValue(42));

    metadata->add(exifDatum);



    EXPECT_EQ(getKeyLong("NonFloatKey", metadata.get(), 0), -1);

}



TEST_F(getKeyLongTest_1012, ValidKeyWithOutOfRangeIndex_ReturnsNegativeOne_1012) {

    Exifdatum exifDatum(ExifKey("SingleValueKey"), new FloatValue(3.5f));

    metadata->add(exifDatum);



    EXPECT_EQ(getKeyLong("SingleValueKey", metadata.get(), 1), -1);

}
