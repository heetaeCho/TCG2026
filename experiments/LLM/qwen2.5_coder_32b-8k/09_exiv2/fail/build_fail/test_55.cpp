#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



using namespace Exiv2;



class ImageTest_55 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    Image image{ImageType::jpeg, 0x0f, std::move(io)};



    void SetUp() override {

        // Additional setup can be done here if necessary

    }

};



TEST_F(ImageTest_55, IccProfileDefault_55) {

    const DataBuf& iccProfile = image.iccProfile();

    EXPECT_TRUE(iccProfile.empty());

}



TEST_F(ImageTest_55, SetIccProfileAndGet_55) {

    uint8_t profileData[] = {0x49, 0x43, 0x43, 0x5F};

    DataBuf iccProfile(profileData, sizeof(profileData));

    image.setIccProfile(std::move(iccProfile), true);



    const DataBuf& retrievedProfile = image.iccProfile();

    EXPECT_EQ(retrievedProfile.size(), sizeof(profileData));

    EXPECT_TRUE(memcmp(retrievedProfile.pData_, profileData, sizeof(profileData)) == 0);

}



TEST_F(ImageTest_55, ClearIccProfileAndGet_55) {

    uint8_t profileData[] = {0x49, 0x43, 0x43, 0x5F};

    DataBuf iccProfile(profileData, sizeof(profileData));

    image.setIccProfile(std::move(iccProfile), true);



    image.clearIccProfile();

    const DataBuf& retrievedProfile = image.iccProfile();

    EXPECT_TRUE(retrievedProfile.empty());

}



TEST_F(ImageTest_55, IccProfileDefinedAfterSet_55) {

    uint8_t profileData[] = {0x49, 0x43, 0x43, 0x5F};

    DataBuf iccProfile(profileData, sizeof(profileData));

    image.setIccProfile(std::move(iccProfile), true);



    EXPECT_TRUE(image.iccProfileDefined());

}



TEST_F(ImageTest_55, IccProfileNotDefinedAfterClear_55) {

    uint8_t profileData[] = {0x49, 0x43, 0x43, 0x5F};

    DataBuf iccProfile(profileData, sizeof(profileData));

    image.setIccProfile(std::move(iccProfile), true);

    image.clearIccProfile();



    EXPECT_FALSE(image.iccProfileDefined());

}



TEST_F(ImageTest_55, AppendIccProfileAndGet_55) {

    uint8_t profileData[] = {0x49, 0x43, 0x43, 0x5F};

    image.appendIccProfile(profileData, sizeof(profileData), true);



    const DataBuf& retrievedProfile = image.iccProfile();

    EXPECT_EQ(retrievedProfile.size(), sizeof(profileData));

    EXPECT_TRUE(memcmp(retrievedProfile.pData_, profileData, sizeof(profileData)) == 0);

}



TEST_F(ImageTest_55, AppendMultipleIccProfilesAndGet_55) {

    uint8_t profileData1[] = {0x49, 0x43, 0x43, 0x5F};

    uint8_t profileData2[] = {0x61, 0x62, 0x63, 0x64};



    image.appendIccProfile(profileData1, sizeof(profileData1), true);

    image.appendIccProfile(profileData2, sizeof(profileData2), true);



    const DataBuf& retrievedProfile = image.iccProfile();

    EXPECT_EQ(retrievedProfile.size(), sizeof(profileData1) + sizeof(profileData2));

    EXPECT_TRUE(memcmp(retrievedProfile.pData_, profileData1, sizeof(profileData1)) == 0);

    EXPECT_TRUE(memcmp(retrievedProfile.pData_ + sizeof(profileData1), profileData2, sizeof(profileData2)) == 0);

}
