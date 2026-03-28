#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class ImageTest_1084 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image* image;



    void SetUp() override {

        io = BasicIo::createMemIo();

        image = new Image(imageJpeg, 0x0000, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1084, SetIccProfile_ValidProfile_TestValidFalse_1084) {

    DataBuf iccProfile(20);

    bool bTestValid = false;



    EXPECT_NO_THROW(image->setIccProfile(std::move(iccProfile), bTestValid));

}



TEST_F(ImageTest_1084, SetIccProfile_ValidProfile_TestValidTrue_1084) {

    DataBuf iccProfile(20);

    bool bTestValid = true;



    EXPECT_NO_THROW(image->setIccProfile(std::move(iccProfile), bTestValid));

}



TEST_F(ImageTest_1084, SetIccProfile_EmptyProfile_TestValidFalse_1084) {

    DataBuf iccProfile;

    bool bTestValid = false;



    EXPECT_NO_THROW(image->setIccProfile(std::move(iccProfile), bTestValid));

}



TEST_F(ImageTest_1084, SetIccProfile_EmptyProfile_TestValidTrue_1084) {

    DataBuf iccProfile;

    bool bTestValid = true;



    EXPECT_NO_THROW(image->setIccProfile(std::move(iccProfile), bTestValid));

}



TEST_F(ImageTest_1084, IccProfileDefined_AfterSet_ReturnsTrue_1084) {

    DataBuf iccProfile(20);

    bool bTestValid = false;

    image->setIccProfile(std::move(iccProfile), bTestValid);



    EXPECT_TRUE(image->iccProfileDefined());

}



TEST_F(ImageTest_1084, IccProfileDefined_AfterClear_ReturnsFalse_1084) {

    DataBuf iccProfile(20);

    bool bTestValid = false;

    image->setIccProfile(std::move(iccProfile), bTestValid);

    image->clearIccProfile();



    EXPECT_FALSE(image->iccProfileDefined());

}



TEST_F(ImageTest_1084, IccProfile_AfterSet_ReturnsSameData_1084) {

    const byte data[] = {0x01, 0x02, 0x03, 0x04};

    DataBuf iccProfile(data, sizeof(data));

    bool bTestValid = false;

    image->setIccProfile(std::move(iccProfile), bTestValid);



    const DataBuf& retrievedProfile = image->iccProfile();

    EXPECT_EQ(retrievedProfile.size(), sizeof(data));

    for (size_t i = 0; i < sizeof(data); ++i) {

        EXPECT_EQ(retrievedProfile.read_uint8(i), data[i]);

    }

}



TEST_F(ImageTest_1084, SetIccProfile_LargeProfile_TestValidFalse_1084) {

    DataBuf iccProfile(1024);

    bool bTestValid = false;



    EXPECT_NO_THROW(image->setIccProfile(std::move(iccProfile), bTestValid));

}



TEST_F(ImageTest_1084, SetIccProfile_LargeProfile_TestValidTrue_1084) {

    DataBuf iccProfile(1024);

    bool bTestValid = true;



    EXPECT_NO_THROW(image->setIccProfile(std::move(iccProfile), bTestValid));

}
