#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class ExifdatumTest : public ::testing::Test {

protected:

    MockExifKey mockKey;

    MockValue* mockValue = new MockValue(TypeId::uint32);

    std::unique_ptr<MockValue> uniqueMockValue(mockValue);



    ExifdatumTest() : exifDatum(mockKey, uniqueMockValue.get()) {}



    Exifdatum exifDatum;

};



TEST_F(ExifdatumTest_764, SizeDataArea_ReturnsZeroWhenNoValueSet_764) {

    EXPECT_CALL(*mockValue, sizeDataArea()).WillOnce(::testing::Return(0));

    EXPECT_EQ(exifDatum.sizeDataArea(), 0);

}



TEST_F(ExifdatumTest_764, SizeDataArea_ReturnsCorrectSize_764) {

    const size_t expectedSize = 10;

    EXPECT_CALL(*mockValue, sizeDataArea()).WillOnce(::testing::Return(expectedSize));

    EXPECT_EQ(exifDatum.sizeDataArea(), expectedSize);

}



TEST_F(ExifdatumTest_764, SizeDataArea_ReturnsZeroWhenValueIsNull_764) {

    Exifdatum exifDatumWithoutValue(mockKey, nullptr);

    EXPECT_EQ(exifDatumWithoutValue.sizeDataArea(), 0);

}
