#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class ExifdatumTest : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> exifKey;

    std::unique_ptr<Value> value;



    void SetUp() override {

        exifKey = std::make_unique<ExifKey>("Exif.Image.Artist");

        value = Value::create(stringType);

    }

};



TEST_F(ExifdatumTest_NormalOperation_2163, ConstructorWithKeyValue_2163) {

    Exifdatum exifdatum(*exifKey, value.get());

    EXPECT_EQ(exifdatum.key(), "Exif.Image.Artist");

}



TEST_F(ExifdatumTest_NormalOperation_2163, ConstructorCopy_2163) {

    Exifdatum original(*exifKey, value.get());

    Exifdatum copy = original;

    EXPECT_EQ(copy.key(), "Exif.Image.Artist");

}



TEST_F(ExifdatumTest_NormalOperation_2163, SetValueFromString_2163) {

    Exifdatum exifdatum(*exifKey, nullptr);

    exifdatum.setValue("John Doe");

    EXPECT_EQ(exifdatum.toString(), "John Doe");

}



TEST_F(ExifdatumTest_BoundaryConditions_2163, EmptyStringValue_2163) {

    Exifdatum exifdatum(*exifKey, nullptr);

    exifdatum.setValue("");

    EXPECT_EQ(exifdatum.toString(), "");

}



TEST_F(ExifdatumTest_ExceptionalCases_2163, InvalidTypeConversion_2163) {

    Exifdatum exifdatum(*exifKey, value.get());

    exifdatum.setValue("John Doe");

    EXPECT_THROW(exifdatum.toInt64(), Error);

}



TEST_F(ExifdatumTest_NormalOperation_2163, SetValueFromValuePtr_2163) {

    Exifdatum exifdatum(*exifKey, nullptr);

    value->setDataArea(reinterpret_cast<const byte*>("John Doe"), 8);

    exifdatum.setValue(value.get());

    EXPECT_EQ(exifdatum.toString(), "John Doe");

}



TEST_F(ExifdatumTest_NormalOperation_2163, KeyFunctions_2163) {

    Exifdatum exifdatum(*exifKey, value.get());

    EXPECT_EQ(exifdatum.key(), "Exif.Image.Artist");

    EXPECT_STREQ(exifdatum.familyName(), "Exif");

    EXPECT_EQ(exifdatum.groupName(), "Image");

    EXPECT_EQ(exifdatum.tagName(), "Artist");

}



TEST_F(ExifdatumTest_NormalOperation_2163, AssignmentOperatorString_2163) {

    Exifdatum exifdatum(*exifKey, nullptr);

    exifdatum = "John Doe";

    EXPECT_EQ(exifdatum.toString(), "John Doe");

}



TEST_F(ExifdatumTest_NormalOperation_2163, AssignmentOperatorInt_2163) {

    Exifdatum exifdatum(*exifKey, nullptr);

    exifdatum = 123;

    EXPECT_EQ(exifdatum.toInt64(), 123);

}



TEST_F(ExifdatumTest_NormalOperation_2163, AssignmentOperatorValue_2163) {

    Exifdatum exifdatum(*exifKey, nullptr);

    value->setDataArea(reinterpret_cast<const byte*>("John Doe"), 8);

    exifdatum = *value;

    EXPECT_EQ(exifdatum.toString(), "John Doe");

}
