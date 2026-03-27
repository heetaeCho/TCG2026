#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = nullptr;

    Image* image = nullptr;



    void SetUp() override {

        io = BasicIo::createMemIo();

        image = new Image(imageTypeUndefined, 0, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1094, InitialWriteXmpFromPacketValueIsFalse_1094) {

    EXPECT_FALSE(image->writeXmpFromPacket());

}



TEST_F(ImageTest_1094, SetWriteXmpFromPacketToTrueReflectsInGetter_1094) {

    image->writeXmpFromPacket(true);

    EXPECT_TRUE(image->writeXmpFromPacket());

}



TEST_F(ImageTest_1094, SetWriteXmpFromPacketToFalseReflectsInGetter_1094) {

    image->writeXmpFromPacket(false);

    EXPECT_FALSE(image->writeXmpFromPacket());

}
