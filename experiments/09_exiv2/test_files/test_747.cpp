#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"



namespace {



class ExifdatumTest_747 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create an instance of ExifKey and Value for testing

        exifKey = std::make_unique<Exiv2::ExifKey>("some.tag");

        value = std::make_unique<Exiv2::Value>();

        exifdatum = std::make_unique<Exiv2::Exifdatum>(*exifKey, value.get());

    }



    void TearDown() override {

        // Clean up resources if necessary

    }



    std::unique_ptr<Exiv2::ExifKey> exifKey;

    std::unique_ptr<Exiv2::Value> value;

    std::unique_ptr<Exiv2::Exifdatum> exifdatum;

};



TEST_F(ExifdatumTest_747, TagDescReturnsEmptyStringWhenKeyIsNull_747) {

    Exiv2::Exifdatum exifdatumWithoutKey(*exifKey.get(), value.get());

    exifdatumWithoutKey.key_.reset(); // Manually set key to null

    EXPECT_EQ(exifdatumWithoutKey.tagDesc(), "");

}



TEST_F(ExifdatumTest_747, TagDescReturnsValidStringWhenKeyIsSet_747) {

    EXPECT_EQ(exifdatum->tagDesc(), exifKey->tagDesc());

}



} // namespace
