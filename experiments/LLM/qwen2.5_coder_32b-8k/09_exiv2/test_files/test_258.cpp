#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::Return;



// Test fixture class for TiffComponent tests

class TiffComponentTest_258 : public ::testing::Test {

protected:

    // Setup code here if needed

};



TEST_F(TiffComponentTest_258, NewTiffDirectory_CreatesInstance_258) {

    uint16_t tag = 0x013A; // Example TIFF_TAG_ExifIFD

    IfdId group = ifdExif;

    auto tiffDirectory = newTiffDirectory<ifdExif>(tag, group);

    EXPECT_NE(tiffDirectory, nullptr);

}



TEST_F(TiffComponentTest_258, NewTiffDirectory_CheckTag_258) {

    uint16_t tag = 0x013A; // Example TIFF_TAG_ExifIFD

    IfdId group = ifdExif;

    auto tiffDirectory = newTiffDirectory<ifdExif>(tag, group);

    EXPECT_EQ(tiffDirectory->tag(), tag);

}



TEST_F(TiffComponentTest_258, NewTiffDirectory_CheckGroup_258) {

    uint16_t tag = 0x013A; // Example TIFF_TAG_ExifIFD

    IfdId group = ifdExif;

    auto tiffDirectory = newTiffDirectory<ifdExif>(tag, group);

    EXPECT_EQ(tiffDirectory->group(), group);

}



TEST_F(TiffComponentTest_258, NewTiffDirectory_ZeroTag_258) {

    uint16_t tag = 0x0000; // Zero tag

    IfdId group = ifdExif;

    auto tiffDirectory = newTiffDirectory<ifdExif>(tag, group);

    EXPECT_NE(tiffDirectory, nullptr);

    EXPECT_EQ(tiffDirectory->tag(), tag);

}



TEST_F(TiffComponentTest_258, NewTiffDirectory_MaxTagValue_258) {

    uint16_t tag = 0xFFFF; // Maximum possible value for a uint16_t

    IfdId group = ifdExif;

    auto tiffDirectory = newTiffDirectory<ifdExif>(tag, group);

    EXPECT_NE(tiffDirectory, nullptr);

    EXPECT_EQ(tiffDirectory->tag(), tag);

}



TEST_F(TiffComponentTest_258, NewTiffDirectory_DifferentGroups_258) {

    uint16_t tag = 0x013A; // Example TIFF_TAG_ExifIFD

    IfdId group1 = ifdExif;

    auto tiffDirectory1 = newTiffDirectory<ifdExif>(tag, group1);

    EXPECT_EQ(tiffDirectory1->group(), group1);



    IfdId group2 = ifdGpsInfo;

    auto tiffDirectory2 = newTiffDirectory<ifdGpsInfo>(tag, group2);

    EXPECT_EQ(tiffDirectory2->group(), group2);

}
