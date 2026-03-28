#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include <memory>



using namespace Exiv2;



class ImageTest_1081 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> ioMock = std::make_unique<BasicIo>();

    Image image{ImageType::jpeg, 0x1F, std::move(ioMock)};

};



TEST_F(ImageTest_1081, WriteXmpFromPacket_DefaultValue_1081) {

    EXPECT_FALSE(image.writeXmpFromPacket());

}



TEST_F(ImageTest_1081, WriteXmpFromPacket_SetTrue_1081) {

    image.writeXmpFromPacket(true);

    EXPECT_TRUE(image.writeXmpFromPacket());

}



TEST_F(ImageTest_1081, WriteXmpFromPacket_SetFalse_1081) {

    image.writeXmpFromPacket(false);

    EXPECT_FALSE(image.writeXmpFromPacket());

}



TEST_F(ImageTest_1081, WriteXmpFromPacket_ToggleMultipleTimes_1081) {

    image.writeXmpFromPacket(true);

    EXPECT_TRUE(image.writeXmpFromPacket());



    image.writeXmpFromPacket(false);

    EXPECT_FALSE(image.writeXmpFromPacket());



    image.writeXmpFromPacket(true);

    EXPECT_TRUE(image.writeXmpFromPacket());

}
