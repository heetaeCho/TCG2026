#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using testing::Return;



class ImageFactoryTest_1103 : public ::testing::Test {

protected:

    ImageFactory factory;

};



TEST_F(ImageFactoryTest_1103, GetTypeFromData_ReturnsValidImageType_1103) {

    const byte data[] = { 0xFF, 0xD8, 0xFF, 0xE0 }; // Example JPEG header

    size_t size = sizeof(data);

    ImageType type = factory.getType(data, size);

    EXPECT_NE(type, ImageType::none);

}



TEST_F(ImageFactoryTest_1103, GetTypeFromEmptyData_ReturnsNone_1103) {

    const byte data[] = {};

    size_t size = sizeof(data);

    ImageType type = factory.getType(data, size);

    EXPECT_EQ(type, ImageType::none);

}



TEST_F(ImageFactoryTest_1103, GetTypeFromPartialJPEGHeader_ReturnsValidImageType_1103) {

    const byte data[] = { 0xFF, 0xD8 }; // Partial JPEG header

    size_t size = sizeof(data);

    ImageType type = factory.getType(data, size);

    EXPECT_NE(type, ImageType::none);

}



TEST_F(ImageFactoryTest_1103, GetTypeFromInvalidData_ReturnsNone_1103) {

    const byte data[] = { 0x00, 0x01, 0x02, 0x03 }; // Invalid image header

    size_t size = sizeof(data);

    ImageType type = factory.getType(data, size);

    EXPECT_EQ(type, ImageType::none);

}



TEST_F(ImageFactoryTest_1103, GetTypeFromLargeData_ReturnsValidImageType_1103) {

    const byte data[1024] = { 0xFF, 0xD8, 0xFF, 0xE0 }; // Large buffer with valid JPEG header

    size_t size = sizeof(data);

    ImageType type = factory.getType(data, size);

    EXPECT_NE(type, ImageType::none);

}



TEST_F(ImageFactoryTest_1103, GetTypeFromMaxSizeData_ReturnsValidImageType_1103) {

    std::vector<byte> data(4096, 0); // Large buffer with valid JPEG header

    data[0] = 0xFF;

    data[1] = 0xD8;

    data[2] = 0xFF;

    data[3] = 0xE0;

    size_t size = data.size();

    ImageType type = factory.getType(data.data(), size);

    EXPECT_NE(type, ImageType::none);

}



TEST_F(ImageFactoryTest_1103, GetTypeFromDataWithNullPointer_ReturnsNone_1103) {

    const byte* data = nullptr;

    size_t size = 1024;

    ImageType type = factory.getType(data, size);

    EXPECT_EQ(type, ImageType::none);

}



TEST_F(ImageFactoryTest_1103, GetTypeFromDataWithZeroSize_ReturnsNone_1103) {

    const byte data[] = { 0xFF, 0xD8, 0xFF, 0xE0 }; // Example JPEG header

    size_t size = 0;

    ImageType type = factory.getType(data, size);

    EXPECT_EQ(type, ImageType::none);

}
