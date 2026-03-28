#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    Image* image;

    DataBuf iccProfile_;



    void SetUp() override {

        auto io = std::make_unique<BasicIo>();

        image = new Image(imageTypeNone, 0, std::move(io));

    }



    void TearDown() override {

        delete image;

    }



    void setIccProfile(const uint8_t* data, size_t size) {

        iccProfile_ = DataBuf(data, size);

        image->setIccProfile(std::move(iccProfile_), false);

    }

};



TEST_F(ImageTest_1086, CheckIccProfile_ValidProfile_1086) {

    const uint8_t validData[] = {0x00, 0x00, 0x00, 0x0C}; // Size is 12

    setIccProfile(validData, sizeof(validData));

    EXPECT_NO_THROW(image->checkIccProfile());

}



TEST_F(ImageTest_1086, CheckIccProfile_TooSmallProfile_1086) {

    const uint8_t smallData[] = {0x00, 0x00}; // Size is less than sizeof(long)

    setIccProfile(smallData, sizeof(smallData));

    EXPECT_THROW(image->checkIccProfile(), Error);

}



TEST_F(ImageTest_1086, CheckIccProfile_SizeMismatch_1086) {

    const uint8_t mismatchData[] = {0x00, 0x00, 0x00, 0x10}; // Claimed size is 16

    setIccProfile(mismatchData, sizeof(mismatchData));

    EXPECT_THROW(image->checkIccProfile(), Error);

}



TEST_F(ImageTest_1086, CheckIccProfile_EmptyProfile_1086) {

    const uint8_t emptyData[] = {};

    setIccProfile(emptyData, sizeof(emptyData));

    EXPECT_THROW(image->checkIccProfile(), Error);

}
