#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/jp2image_int.hpp"

#include "./TestProjects/exiv2/types.hpp"



using namespace Exiv2::Internal;



TEST(isValidBoxFileType_Test_1751, ValidJp2BoxData_1751) {

    std::vector<uint8_t> boxData = {0x00, 0x00, 0x00, 0x14, 0x6A, 0x70, 0x32, 0x20, 0x6A, 0x70, 0x32, 0x20};

    EXPECT_TRUE(isValidBoxFileType(boxData));

}



TEST(isValidBoxFileType_Test_1751, ValidJphBoxData_1751) {

    std::vector<uint8_t> boxData = {0x00, 0x00, 0x00, 0x14, 0x6A, 0x70, 0x68, 0x20, 0x6A, 0x70, 0x68, 0x20};

    EXPECT_TRUE(isValidBoxFileType(boxData));

}



TEST(isValidBoxFileType_Test_1751, InvalidSizeTooSmall_1751) {

    std::vector<uint8_t> boxData = {0x00, 0x00, 0x00, 0x04};

    EXPECT_FALSE(isValidBoxFileType(boxData));

}



TEST(isValidBoxFileType_Test_1751, InvalidSizeNotMultipleOfFour_1751) {

    std::vector<uint8_t> boxData = {0x00, 0x00, 0x00, 0x13, 0x6A, 0x70, 0x32, 0x20, 0x6A, 0x70, 0x32};

    EXPECT_FALSE(isValidBoxFileType(boxData));

}



TEST(isValidBoxFileType_Test_1751, InvalidMinorVersion_1751) {

    std::vector<uint8_t> boxData = {0x00, 0x00, 0x00, 0x14, 0x6A, 0x70, 0x32, 0x21, 0x6A, 0x70, 0x32, 0x20};

    EXPECT_FALSE(isValidBoxFileType(boxData));

}



TEST(isValidBoxFileType_Test_1751, InvalidCompatibilityList_1751) {

    std::vector<uint8_t> boxData = {0x00, 0x00, 0x00, 0x14, 0x6A, 0x70, 0x32, 0x20, 0x6A, 0x70, 0x33, 0x20};

    EXPECT_FALSE(isValidBoxFileType(boxData));

}



TEST(isValidBoxFileType_Test_1751, MixedCompatibilityList_1751) {

    std::vector<uint8_t> boxData = {0x00, 0x00, 0x00, 0x18, 0x6A, 0x70, 0x32, 0x20, 0x6A, 0x70, 0x33, 0x20, 0x6A, 0x70, 0x32, 0x20};

    EXPECT_TRUE(isValidBoxFileType(boxData));

}
