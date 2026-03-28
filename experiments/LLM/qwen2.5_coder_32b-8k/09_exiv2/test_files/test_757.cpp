#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



namespace {



using namespace Exiv2;



class ExifdatumTest : public ::testing::Test {

protected:

    ExifdatumTest() 

        : key(IfdId::IFD0, 0x135), // Example key

          value(new UShort(1)) { 

        exifDatum = new Exifdatum(key, value.get());

    }



    ~ExifdatumTest() override {

        delete exifDatum;

    }



    ExifKey key;

    std::unique_ptr<UShort> value;

    Exifdatum* exifDatum;

};



TEST_F(ExifdatumTest_757, SizeReturnsCorrectValue_757) {

    EXPECT_EQ(exifDatum->size(), 2); // Assuming UShort has a size of 2

}



TEST_F(ExifdatumTest_757, SizeReturnsZeroWhenNoValue_757) {

    Exifdatum exifDatumWithoutValue(key);

    EXPECT_EQ(exifDatumWithoutValue.size(), 0);

}



} // namespace
