#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifdatumTest_742 : public ::testing::Test {

protected:

    void SetUp() override {

        exifKey = std::make_unique<ExifKey>("Exif.Image.Artist");

        exifdatum = std::make_unique<Exifdatum>(*exifKey);

    }



    std::unique_ptr<ExifKey> exifKey;

    std::unique_ptr<Exifdatum> exifdatum;

};



TEST_F(ExifdatumTest_742, KeyReturnsCorrectValue_742) {

    EXPECT_EQ(exifdatum->key(), "Exif.Image.Artist");

}



TEST_F(ExifdatumTest_742, SetStringValueChangesKey_742) {

    exifdatum->setValue("John Doe");

    EXPECT_EQ(exifdatum->key(), "Exif.Image.Artist");

}



TEST_F(ExifdatumTest_742, AssignmentOperatorString_742) {

    *exifdatum = "Jane Smith";

    EXPECT_EQ(exifdatum->key(), "Exif.Image.Artist");

}



TEST_F(ExifdatumTest_742, CopyConstructorPreservesKey_742) {

    Exifdatum exifdatumCopy(*exifdatum);

    EXPECT_EQ(exifdatumCopy.key(), "Exif.Image.Artist");

}



TEST_F(ExifdatumTest_742, AssignmentOperatorObject_742) {

    Exifdatum exifdatumOther(*exifKey);

    exifdatumOther = *exifdatum;

    EXPECT_EQ(exifdatumOther.key(), "Exif.Image.Artist");

}
