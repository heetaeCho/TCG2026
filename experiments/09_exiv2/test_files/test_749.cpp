#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifdatumTest_749 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create an instance of ExifKey with a known IfdId

        ExifKey exifKey("Exif.Image.Artist", 0, 1);

        exifdatum = std::make_unique<Exifdatum>(exifKey, nullptr);

    }



    std::unique_ptr<Exifdatum> exifdatum;

};



TEST_F(ExifdatumTest_749, IfdIdReturnsCorrectValue_749) {

    EXPECT_EQ(exifdatum->ifdId(), IfdId::ifd0Id);

}



TEST_F(ExifdatumTest_749, IfdIdReturnsDefaultIfKeyIsNullptr_749) {

    Exifdatum exifdatumWithNullKey(nullptr, nullptr);

    EXPECT_EQ(exifdatumWithNullKey.ifdId(), IfdId::ifdIdNotSet);

}



TEST_F(ExifdatumTest_749, IfdIdBoundaryCondition_749) {

    ExifKey boundaryKey("Unknown.Tag", 0, 1); // Assuming an unknown tag defaults to ifd0Id

    Exifdatum exifdatumWithBoundaryKey(boundaryKey, nullptr);

    EXPECT_EQ(exifdatumWithBoundaryKey.ifdId(), IfdId::ifd0Id);

}



TEST_F(ExifdatumTest_749, IfdIdExceptionalCase_749) {

    // No exceptional cases are observable through the interface for ifdId()

    SUCCEED();

}
