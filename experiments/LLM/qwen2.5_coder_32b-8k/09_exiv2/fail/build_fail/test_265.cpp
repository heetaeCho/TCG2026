#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



// Mock any external collaborators if needed



class TiffComponentTest_265 : public ::testing::Test {

protected:

    // Set up any necessary state before each test

};



TEST_F(TiffComponentTest_265, NewTiffImageData_ReturnsUniquePtr_265) {

    uint16_t tag = 0x112;  // Example TIFF tag for Orientation

    IfdId group = ifdExif; // Example IFD Group



    TiffComponent::UniquePtr result = newTiffImageData<0x112, ifdExif>(tag, group);



    EXPECT_NE(result.get(), nullptr);

}



TEST_F(TiffComponentTest_265, NewTiffImageData_CorrectTagAndGroup_265) {

    uint16_t tag = 0x112;  // Example TIFF tag for Orientation

    IfdId group = ifdExif; // Example IFD Group



    TiffComponent::UniquePtr result = newTiffImageData<0x112, ifdExif>(tag, group);



    EXPECT_EQ(result->tag(), tag);

    EXPECT_EQ(result->group(), group);

}



TEST_F(TiffComponentTest_265, NewTiffImageData_BoundaryTagValue_265) {

    uint16_t tag = 0xFFFF; // Maximum value for a 16-bit unsigned integer

    IfdId group = ifdExif;



    TiffComponent::UniquePtr result = newTiffImageData<0xFFFF, ifdExif>(tag, group);



    EXPECT_NE(result.get(), nullptr);

    EXPECT_EQ(result->tag(), tag);

}



TEST_F(TiffComponentTest_265, NewTiffImageData_BoundaryGroupValue_265) {

    uint16_t tag = 0x112;

    IfdId group = ifdCount; // Last valid IFD Group in the enum



    TiffComponent::UniquePtr result = newTiffImageData<0x112, ifdCount>(tag, group);



    EXPECT_NE(result.get(), nullptr);

    EXPECT_EQ(result->group(), group);

}
