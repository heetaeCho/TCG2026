#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1085 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io_;

    Image image_;



    ImageTest_1085()

        : io_(new BasicIo()), image_(ImageType::jpeg, 0x1, std::move(io_)) {}

};



TEST_F(ImageTest_1085, AppendIccProfile_NormalOperation_1085) {

    const uint8_t bytes[] = {0x00, 0x01, 0x02};

    size_t size = sizeof(bytes);

    image_.appendIccProfile(bytes, size, false);



    const DataBuf& iccProfile = image_.iccProfile();

    EXPECT_EQ(iccProfile.size(), size);

    EXPECT_EQ(memcmp(iccProfile.data(), bytes, size), 0);

}



TEST_F(ImageTest_1085, AppendIccProfile_EmptyProfile_1085) {

    const uint8_t* bytes = nullptr;

    size_t size = 0;

    image_.appendIccProfile(bytes, size, false);



    const DataBuf& iccProfile = image_.iccProfile();

    EXPECT_EQ(iccProfile.size(), size);

}



TEST_F(ImageTest_1085, AppendIccProfile_LargeSize_1085) {

    const uint8_t bytes[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

    size_t size = sizeof(bytes);

    image_.appendIccProfile(bytes, size, false);



    const DataBuf& iccProfile = image_.iccProfile();

    EXPECT_EQ(iccProfile.size(), size);

    EXPECT_EQ(memcmp(iccProfile.data(), bytes, size), 0);

}



TEST_F(ImageTest_1085, AppendIccProfile_MultipleAppends_1085) {

    const uint8_t bytes1[] = {0x00, 0x01};

    size_t size1 = sizeof(bytes1);

    image_.appendIccProfile(bytes1, size1, false);



    const uint8_t bytes2[] = {0x02, 0x03};

    size_t size2 = sizeof(bytes2);

    image_.appendIccProfile(bytes2, size2, false);



    const DataBuf& iccProfile = image_.iccProfile();

    EXPECT_EQ(iccProfile.size(), size1 + size2);

    EXPECT_EQ(memcmp(iccProfile.data(), bytes1, size1), 0);

    EXPECT_EQ(memcmp(iccProfile.data(size1), bytes2, size2), 0);

}



TEST_F(ImageTest_1085, AppendIccProfile_BoundarySize_1085) {

    const uint8_t bytes[] = {0x00};

    size_t size = sizeof(bytes);

    image_.appendIccProfile(bytes, size, false);



    const DataBuf& iccProfile = image_.iccProfile();

    EXPECT_EQ(iccProfile.size(), size);

    EXPECT_EQ(memcmp(iccProfile.data(), bytes, size), 0);

}



TEST_F(ImageTest_1085, AppendIccProfile_ValidCheck_1085) {

    const uint8_t validBytes[] = {0x73, 0x72, 0x63, 0x70}; // 'srCP' in ASCII

    size_t size = sizeof(validBytes);

    image_.appendIccProfile(validBytes, size, true);



    const DataBuf& iccProfile = image_.iccProfile();

    EXPECT_EQ(iccProfile.size(), size);

    EXPECT_EQ(memcmp(iccProfile.data(), validBytes, size), 0);

}



TEST_F(ImageTest_1085, AppendIccProfile_InvalidCheck_1085) {

    const uint8_t invalidBytes[] = {0x00, 0x01, 0x02};

    size_t size = sizeof(invalidBytes);



    EXPECT_THROW(image_.appendIccProfile(invalidBytes, size, true), Error);

}



TEST_F(ImageTest_1085, AppendIccProfile_ZeroSize_1085) {

    const uint8_t* bytes = nullptr;

    size_t size = 0;

    image_.appendIccProfile(bytes, size, false);



    const DataBuf& iccProfile = image_.iccProfile();

    EXPECT_EQ(iccProfile.size(), size);

}



TEST_F(ImageTest_1085, AppendIccProfile_WithExistingData_1085) {

    const uint8_t initialBytes[] = {0x00, 0x01};

    size_t initialSize = sizeof(initialBytes);

    image_.appendIccProfile(initialBytes, initialSize, false);



    const uint8_t newBytes[] = {0x02, 0x03};

    size_t newSize = sizeof(newBytes);

    image_.appendIccProfile(newBytes, newSize, false);



    const DataBuf& iccProfile = image_.iccProfile();

    EXPECT_EQ(iccProfile.size(), initialSize + newSize);

    EXPECT_EQ(memcmp(iccProfile.data(), initialBytes, initialSize), 0);

    EXPECT_EQ(memcmp(iccProfile.data(initialSize), newBytes, newSize), 0);

}
