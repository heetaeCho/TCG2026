#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {



class ExifdatumTest_758 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key;

    std::unique_ptr<Value> value;

    Exifdatum exifDatum;



    ExifdatumTest_758() 

        : key(std::make_unique<ExifKey>()),

          value(std::make_unique<Value>(TypeId::undefined)),

          exifDatum(*key, value.get()) {}

};



TEST_F(ExifdatumTest_758, ToString_ReturnsEmptyStringWhenValueIsNull_758) {

    Exifdatum datumWithNullValue(*key, nullptr);

    EXPECT_EQ(datumWithNullValue.toString(), "");

}



TEST_F(ExifdatumTest_758, ToString_ReturnsStringValue_758) {

    value->setValue("test_value");

    exifDatum.setValue(value.get());

    EXPECT_EQ(exifDatum.toString(), "test_value");

}



TEST_F(ExifdatumTest_758, CopyOperator_StringValue_758) {

    exifDatum = std::string("copy_test");

    EXPECT_EQ(exifDatum.toString(), "copy_test");

}



TEST_F(ExifdatumTest_758, CopyOperator_Uint16Value_758) {

    exifDatum = static_cast<uint16_t>(42);

    EXPECT_NE(exifDatum.toString().find("42"), std::string::npos);

}



TEST_F(ExifdatumTest_758, CopyOperator_Uint32Value_758) {

    exifDatum = static_cast<uint32_t>(1024);

    EXPECT_NE(exifDatum.toString().find("1024"), std::string::npos);

}



TEST_F(ExifdatumTest_758, CopyOperator_Int16Value_758) {

    exifDatum = static_cast<int16_t>(-1);

    EXPECT_NE(exifDatum.toString().find("-1"), std::string::npos);

}



TEST_F(ExifdatumTest_758, CopyOperator_Int32Value_758) {

    exifDatum = static_cast<int32_t>(-1024);

    EXPECT_NE(exifDatum.toString().find("-1024"), std::string::npos);

}



TEST_F(ExifdatumTest_758, CopyOperator_StringLiteral_758) {

    exifDatum = "string_literal";

    EXPECT_EQ(exifDatum.toString(), "string_literal");

}



}  // namespace Exiv2
