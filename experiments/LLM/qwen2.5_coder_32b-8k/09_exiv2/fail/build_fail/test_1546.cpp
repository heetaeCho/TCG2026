#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/cr2header_int.cpp"



using namespace Exiv2::Internal;



class Cr2HeaderTest : public ::testing::Test {

protected:

    Cr2Header cr2Header;

};



TEST_F(Cr2HeaderTest_1546, IsImageTag_ReturnsTrueForIfd2Id_1546) {

    uint16_t tag = 0x0117; // Example TIFF tag

    EXPECT_TRUE(cr2Header.isImageTag(tag, IfdId::ifd2Id, PrimaryGroups()));

}



TEST_F(Cr2HeaderTest_1546, IsImageTag_ReturnsTrueForIfd3Id_1546) {

    uint16_t tag = 0x0117; // Example TIFF tag

    EXPECT_TRUE(cr2Header.isImageTag(tag, IfdId::ifd3Id, PrimaryGroups()));

}



TEST_F(Cr2HeaderTest_1546, IsImageTag_DelegatesToIsTiffImageTagForOtherGroups_1546) {

    uint16_t tag = 0x0117; // Example TIFF tag

    EXPECT_EQ(cr2Header.isImageTag(tag, IfdId::ifd0Id, PrimaryGroups()), cr2Header.isTiffImageTag(tag, IfdId::ifd0Id));

}



TEST_F(Cr2HeaderTest_1546, IsImageTag_HandlesZeroTagValue_1546) {

    EXPECT_EQ(cr2Header.isImageTag(0x0000, IfdId::ifd0Id, PrimaryGroups()), cr2Header.isTiffImageTag(0x0000, IfdId::ifd0Id));

}



TEST_F(Cr2HeaderTest_1546, IsImageTag_HandlesMaxTagValue_1546) {

    EXPECT_EQ(cr2Header.isImageTag(0xFFFF, IfdId::ifd0Id, PrimaryGroups()), cr2Header.isTiffImageTag(0xFFFF, IfdId::ifd0Id));

}
