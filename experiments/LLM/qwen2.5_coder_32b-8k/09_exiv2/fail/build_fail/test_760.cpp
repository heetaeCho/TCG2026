#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class ExifdatumTest_760 : public ::testing::Test {

protected:

    ExifKey key;

    Value value;

    std::unique_ptr<Value> pValue = std::make_unique<Value>(TypeByte);

    Exifdatum exifdatum;



    ExifdatumTest_760() : exifdatum(key, pValue.get()) {}

};



TEST_F(ExifdatumTest_760, ToInt64_ReturnsNegativeOneWhenNoValue_760) {

    Exifdatum emptyExifdatum(key, nullptr);

    EXPECT_EQ(emptyExifdatum.toInt64(0), -1);

}



TEST_F(ExifdatumTest_760, ToInt64_CallsToInt64OfValue_760) {

    EXPECT_CALL(*pValue, toInt64(0)).WillOnce(::testing::Return(123));

    EXPECT_EQ(exifdatum.toInt64(0), 123);

}



TEST_F(ExifdatumTest_760, ToInt64_ReturnsNegativeOneForOutofBoundsIndex_760) {

    EXPECT_CALL(*pValue, toInt64(::testing::Ge(pValue->count()))).WillOnce(::testing::Return(-1));

    EXPECT_EQ(exifdatum.toInt64(pValue->count()), -1);

}



TEST_F(ExifdatumTest_760, ToInt64_HandlesMultipleIndexes_760) {

    EXPECT_CALL(*pValue, toInt64(0)).WillOnce(::testing::Return(123));

    EXPECT_CALL(*pValue, toInt64(1)).WillOnce(::testing::Return(456));

    EXPECT_EQ(exifdatum.toInt64(0), 123);

    EXPECT_EQ(exifdatum.toInt64(1), 456);

}
