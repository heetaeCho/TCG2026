#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include <string>



using namespace Exiv2;



class ExifdatumTest_731 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key;

    Value* value;

    Exifdatum exifdatum;



    void SetUp() override {

        // Initialize with a mock key and value

        key = std::make_unique<ExifKey>("0x927C");

        value = new StringValue("InitialValue");

        exifdatum = Exifdatum(*key, value);

    }



    void TearDown() override {

        delete value;

    }

};



TEST_F(ExifdatumTest_731, OperatorAssignString_NormalOperation_731) {

    std::string newValue = "NewValue";

    exifdatum = newValue;

    EXPECT_EQ(exifdatum.toString(), newValue);

}



TEST_F(ExifdatumTest_731, OperatorAssignString_EmptyString_731) {

    std::string emptyValue = "";

    exifdatum = emptyValue;

    EXPECT_EQ(exifdatum.toString(), emptyValue);

}



TEST_F(ExifdatumTest_731, ToString_NormalOperation_731) {

    std::string expectedValue = "InitialValue";

    EXPECT_EQ(exifdatum.toString(), expectedValue);

}



TEST_F(ExifdatumTest_731, Key_ReturnsCorrectKey_731) {

    std::string expectedKey = "0x927C";

    EXPECT_EQ(exifdatum.key(), expectedKey);

}



TEST_F(ExifdatumTest_731, TypeId_ReturnsStringTypeId_731) {

    EXPECT_EQ(exifdatum.typeId(), StringType);

}
