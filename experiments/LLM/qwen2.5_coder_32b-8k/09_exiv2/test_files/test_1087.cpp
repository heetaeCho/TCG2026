#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



namespace {



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io_;

    Image image_{ImageType::jpeg, 0x1F, std::move(io_)};



    void SetUp() override {

        // Initialize the BasicIo mock or any other setup if needed

        io_ = std::make_unique<MockBasicIo>();

    }

};



TEST_F(ImageTest_1087, ClearIccProfileResetsData_1087) {

    DataBuf initialProfile({0x12, 0x34, 0x56}, 3);

    image_.setIccProfile(std::move(initialProfile), false);



    EXPECT_FALSE(image_.iccProfile().empty());



    image_.clearIccProfile();



    EXPECT_TRUE(image_.iccProfile().empty());

}



TEST_F(ImageTest_1087, ClearIccProfileOnEmptyData_1087) {

    EXPECT_TRUE(image_.iccProfile().empty());



    image_.clearIccProfile();



    EXPECT_TRUE(image_.iccProfile().empty());

}



}  // namespace
