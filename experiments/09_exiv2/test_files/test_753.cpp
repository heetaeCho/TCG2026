#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class ExifdatumTest_753 : public ::testing::Test {

protected:

    std::unique_ptr<Value> value;

    ExifKey key{"Exif.Image.Artist"};

    Exifdatum exifDatum{key, nullptr};



    void SetUp() override {

        value = Value::create(unsignedByte);

        exifDatum.setValue(value.get());

    }

};



TEST_F(ExifdatumTest_753, TypeId_ReturnsCorrectType_753) {

    EXPECT_EQ(exifDatum.typeId(), unsignedByte);

}



TEST_F(ExifdatumTest_753, TypeId_ReturnsInvalidTypeIdWhenNoValueSet_753) {

    Exifdatum exifDatumWithoutValue{key, nullptr};

    EXPECT_EQ(exifDatumWithoutValue.typeId(), invalidTypeId);

}



// Additional tests for boundary conditions and exceptional cases

TEST_F(ExifdatumTest_753, TypeId_DifferentTypes_ReturnCorrectType_753) {

    value = Value::create(asciiString);

    exifDatum.setValue(value.get());

    EXPECT_EQ(exifDatum.typeId(), asciiString);



    value = Value::create(unsignedShort);

    exifDatum.setValue(value.get());

    EXPECT_EQ(exifDatum.typeId(), unsignedShort);



    value = Value::create(unsignedLong);

    exifDatum.setValue(value.get());

    EXPECT_EQ(exifDatum.typeId(), unsignedLong);



    value = Value::create(unsignedRational);

    exifDatum.setValue(value.get());

    EXPECT_EQ(exifDatum.typeId(), unsignedRational);

}



TEST_F(ExifdatumTest_753, TypeId_LastTypeId_ReturnCorrectType_753) {

    value = Value::create(lastTypeId);

    exifDatum.setValue(value.get());

    EXPECT_EQ(exifDatum.typeId(), lastTypeId);

}
