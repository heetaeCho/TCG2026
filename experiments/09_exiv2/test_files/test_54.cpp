#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_54 : public ::testing::Test {

protected:

    std::unique_ptr<Image> image;

    

    void SetUp() override {

        // Assuming a valid constructor for Image is available.

        // Here we're mocking the necessary arguments, assuming placeholders or defaults can be used.

        auto io = std::make_unique<BasicIo>();

        image = std::make_unique<Image>(ImageType::jpeg, 0x1, std::move(io));

    }

};



TEST_F(ImageTest_54, IccProfileDefined_NoIccProfile_54) {

    EXPECT_FALSE(image->iccProfileDefined());

}



TEST_F(ImageTest_54, IccProfileDefined_HasIccProfile_54) {

    DataBuf iccProfile(10); // Create a non-empty DataBuf to simulate ICC profile presence.

    image->setIccProfile(std::move(iccProfile), true);

    EXPECT_TRUE(image->iccProfileDefined());

}



TEST_F(ImageTest_54, IccProfileDefined_AfterClearing_54) {

    DataBuf iccProfile(10); // Create a non-empty DataBuf to simulate ICC profile presence.

    image->setIccProfile(std::move(iccProfile), true);

    image->clearIccProfile();

    EXPECT_FALSE(image->iccProfileDefined());

}



TEST_F(ImageTest_54, SetAndGetIccProfile_NormalOperation_54) {

    uint8_t bytes[] = {0x01, 0x02, 0x03};

    size_t size = sizeof(bytes);

    image->appendIccProfile(bytes, size, true);

    const DataBuf& retrievedProfile = image->iccProfile();

    EXPECT_EQ(retrievedProfile.size(), size);

    for (size_t i = 0; i < size; ++i) {

        EXPECT_EQ(retrievedProfile.c_data(i), bytes[i]);

    }

}



TEST_F(ImageTest_54, SetAndGetIccProfile_EmptyProfile_54) {

    DataBuf emptyProfile;

    image->setIccProfile(std::move(emptyProfile), true);

    const DataBuf& retrievedProfile = image->iccProfile();

    EXPECT_TRUE(retrievedProfile.empty());

}



TEST_F(ImageTest_54, ClearIccProfile_Idempotency_54) {

    // Initially no ICC profile should be defined.

    EXPECT_FALSE(image->iccProfileDefined());



    // Clearing an undefined ICC profile should not cause any issues.

    image->clearIccProfile();

    EXPECT_FALSE(image->iccProfileDefined());

}
