#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.cpp"



using namespace Exiv2::Internal;



// Test fixture for TiffComponent tests

class TiffBinaryElementCreationTest_416 : public ::testing::Test {

protected:

    // No additional setup needed for this test suite

};



TEST_F(TiffBinaryElementCreationTest_416, CreateWithValidTagAndGroup_416) {

    uint16_t tag = 0x0112; // Example valid TIFF tag (Orientation)

    IfdId group = ifdExif; // Example IFD group



    TiffComponent::UniquePtr element = newTiffBinaryElement(tag, group);



    EXPECT_NE(element.get(), nullptr);

}



TEST_F(TiffBinaryElementCreationTest_416, CreateWithZeroTag_416) {

    uint16_t tag = 0x0000; // Zero is a valid TIFF tag for some purposes

    IfdId group = ifdExif;



    TiffComponent::UniquePtr element = newTiffBinaryElement(tag, group);



    EXPECT_NE(element.get(), nullptr);

}



TEST_F(TiffBinaryElementCreationTest_416, CreateWithMaxTagValue_416) {

    uint16_t tag = 0xFFFF; // Maximum value for a 16-bit tag

    IfdId group = ifdExif;



    TiffComponent::UniquePtr element = newTiffBinaryElement(tag, group);



    EXPECT_NE(element.get(), nullptr);

}



TEST_F(TiffBinaryElementCreationTest_416, CreateWithInvalidGroup_416) {

    uint16_t tag = 0x0112; // Valid TIFF tag

    IfdId group = static_cast<IfdId>(-1); // Invalid IFD group



    TiffComponent::UniquePtr element = newTiffBinaryElement(tag, group);



    EXPECT_NE(element.get(), nullptr);

}
