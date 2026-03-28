#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifdatumTest_761 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key;

    std::unique_ptr<Value> value;

    Exifdatum exifDatum;



    void SetUp() override {

        key = std::make_unique<ExifKey>();

        value = std::make_unique<Value>(TypeId::floatType);

        exifDatum = Exifdatum(*key, value.get());

    }

};



TEST_F(ExifdatumTest_761, ToFloat_ReturnsCorrectValueForValidIndex_761) {

    // Assuming the internal value is set to a known float value

    EXPECT_CALL(*value, toFloat(0)).WillOnce(::testing::Return(3.14f));

    EXPECT_FLOAT_EQ(exifDatum.toFloat(0), 3.14f);

}



TEST_F(ExifdatumTest_761, ToFloat_ReturnsMinusOneForInvalidIndex_761) {

    // Assuming the internal value is set to a known float value

    EXPECT_CALL(*value, toFloat(::testing::_)).WillOnce(::testing::Return(-1.0f));

    EXPECT_FLOAT_EQ(exifDatum.toFloat(1), -1.0f);

}



TEST_F(ExifdatumTest_761, ToFloat_ReturnsMinusOneWhenValueIsNull_761) {

    exifDatum = Exifdatum(*key, nullptr);

    EXPECT_FLOAT_EQ(exifDatum.toFloat(0), -1.0f);

}
