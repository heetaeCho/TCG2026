#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentTest_264 : public ::testing::Test {

protected:

    uint16_t tag = 0x0117; // Example TIFF Tag for ImageWidth

    IfdId group = ifdExif; // Example IFD Group

};



TEST_F(TiffComponentTest_264, CreateUniquePtrWithValidTagAndGroup_264) {

    auto ptr = newTiffThumbSize<0x0117, ifdExif>(tag, group);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(TiffComponentTest_264, CheckTypeOfCreatedObject_264) {

    auto ptr = newTiffThumbSize<0x0117, ifdExif>(tag, group);

    EXPECT_TRUE(dynamic_cast<TiffSizeEntry*>(ptr.get()) != nullptr);

}



TEST_F(TiffComponentTest_264, CreateUniquePtrWithDifferentTagAndGroup_264) {

    uint16_t differentTag = 0x011A; // ImageHeight

    IfdId differentGroup = ifdGpsInfo;

    auto ptr = newTiffThumbSize<0x011A, ifdGpsInfo>(differentTag, differentGroup);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(TiffComponentTest_264, CheckTypeOfCreatedObjectWithDifferentTagAndGroup_264) {

    uint16_t differentTag = 0x011A; // ImageHeight

    IfdId differentGroup = ifdGpsInfo;

    auto ptr = newTiffThumbSize<0x011A, ifdGpsInfo>(differentTag, differentGroup);

    EXPECT_TRUE(dynamic_cast<TiffSizeEntry*>(ptr.get()) != nullptr);

}
