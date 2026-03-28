#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tags.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



// Mock TagInfo for testing purposes

struct MockTagInfo : public TagInfo {

    MOCK_CONST_METHOD0(tag, uint16_t());

};



TEST(ExifKeyTest_2181, ValidConstructorNormalOperation_2181) {

    EXPECT_NO_THROW(ExifKey key(0x0132, "Exif.Photo"));

}



TEST(ExifKeyTest_2181, InvalidIfdIdThrowsException_2181) {

    EXPECT_THROW(ExifKey key(0x0132, "InvalidGroupName"), Error);

}



TEST(ExifKeyTest_2181, ValidConstructorBoundaryCondition_2181) {

    EXPECT_NO_THROW(ExifKey key(0xFFFF, "Exif.Photo"));

}



TEST(ExifKeyTest_2181, TagInfoConstructorNormalOperation_2181) {

    MockTagInfo mockTagInfo;

    EXPECT_CALL(mockTagInfo, tag()).WillOnce(::testing::Return(0x0132));

    EXPECT_NO_THROW(ExifKey key(mockTagInfo));

}



TEST(ExifKeyTest_2181, CopyConstructorNormalOperation_2181) {

    ExifKey originalKey(0x0132, "Exif.Photo");

    EXPECT_NO_THROW(ExifKey copiedKey(originalKey));

}



TEST(ExifKeyTest_2181, MoveConstructorNormalOperation_2181) {

    ExifKey originalKey(0x0132, "Exif.Photo");

    EXPECT_NO_THROW(ExifKey movedKey(std::move(originalKey)));

}
