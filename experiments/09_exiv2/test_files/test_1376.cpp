#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tags.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TagNumberTest_1376 : public ::testing::Test {

protected:

    virtual void SetUp() {}

    virtual void TearDown() {}

};



TEST_F(TagNumberTest_1376, ValidTagName_ReturnsCorrectTagNumber_1376) {

    // Assuming tagInfo("Exif.Image.Artist", ifdId) returns a TagInfo with tag_ = 0x013b

    uint16_t result = tagNumber("Exif.Image.Artist", IfdId::exifIFD);

    EXPECT_EQ(result, 0x013b);

}



TEST_F(TagNumberTest_1376, InvalidTagName_ThrowsError_1376) {

    // Assuming tagInfo("InvalidTag", ifdId) returns nullptr

    EXPECT_THROW(tagNumber("InvalidTag", IfdId::exifIFD), Error);

}



TEST_F(TagNumberTest_1376, HexadecimalTagName_ReturnsCorrectTagNumber_1376) {

    uint16_t result = tagNumber("0x013b", IfdId::exifIFD);

    EXPECT_EQ(result, 0x013b);

}



TEST_F(TagNumberTest_1376, InvalidHexadecimalTagName_ThrowsError_1376) {

    EXPECT_THROW(tagNumber("0xGHIJ", IfdId::exifIFD), Error);

}



TEST_F(TagNumberTest_1376, BoundaryCondition_HexMinValue_ReturnsCorrectTagNumber_1376) {

    uint16_t result = tagNumber("0x0000", IfdId::exifIFD);

    EXPECT_EQ(result, 0x0000);

}



TEST_F(TagNumberTest_1376, BoundaryCondition_HexMaxValue_ReturnsCorrectTagNumber_1376) {

    uint16_t result = tagNumber("0xFFFF", IfdId::exifIFD);

    EXPECT_EQ(result, 0xFFFF);

}
