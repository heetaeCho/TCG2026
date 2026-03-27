#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class ExifdatumTest_729 : public ::testing::Test {

protected:

    std::unique_ptr<Value> value_;

    ExifKey key_;



    void SetUp() override {

        value_ = std::make_unique<StringValue>("test_value");

        key_ = ExifKey("Exif.Image.Artist");

    }

};



TEST_F(ExifdatumTest_729, ConstructorWithValue_729) {

    Exifdatum exifDatum(key_, value_.get());

    EXPECT_EQ(exifDatum.value().toString(), "test_value");

}



TEST_F(ExifdatumTest_729, CopyConstructor_729) {

    Exifdatum original(key_, value_.get());

    Exifdatum copy(original);

    EXPECT_EQ(copy.value().toString(), "test_value");

}



TEST_F(ExifdatumTest_729, AssignmentOperator_729) {

    Exifdatum exifDatum1(key_, value_.get());

    Exifdatum exifDatum2(key_);

    exifDatum2 = exifDatum1;

    EXPECT_EQ(exifDatum2.value().toString(), "test_value");

}



TEST_F(ExifdatumTest_729, SetValueWithString_729) {

    Exifdatum exifDatum(key_);

    exifDatum.setValue("new_test_value");

    EXPECT_EQ(exifDatum.value().toString(), "new_test_value");

}



TEST_F(ExifdatumTest_729, ValueNotSetException_729) {

    Exifdatum exifDatum(key_);

    EXPECT_THROW(exifDatum.value(), Error);

}



TEST_F(ExifdatumTest_729, KeyMethod_729) {

    Exifdatum exifDatum(key_, value_.get());

    EXPECT_EQ(exifDatum.key(), "Exif.Image.Artist");

}
