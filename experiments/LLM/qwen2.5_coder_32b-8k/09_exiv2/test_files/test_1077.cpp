#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1077 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    Image image{ImageType::jpeg, 0x00ff, std::move(io)};



    void SetUp() override {

        // Setup any state before each test (if needed)

    }



    void TearDown() override {

        // Cleanup any state after each test (if needed)

    }

};



TEST_F(ImageTest_1077, ClearXmpPacket_SetsWriteXmpFromPacketToTrue_1077) {

    image.writeXmpFromPacket(false);

    image.clearXmpPacket();

    EXPECT_TRUE(image.writeXmpFromPacket());

}



TEST_F(ImageTest_1077, ClearXmpPacket_ClearsXmpPacket_1077) {

    std::string initialXmpPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">Initial Packet</x:xmpmeta>";

    image.setXmpPacket(initialXmpPacket);

    image.clearXmpPacket();

    EXPECT_EQ(image.xmpPacket(), "");

}



TEST_F(ImageTest_1077, ClearXmpPacket_IdempotentOperation_1077) {

    image.clearXmpPacket(); // First call

    image.clearXmpPacket(); // Second call should have no effect

    EXPECT_TRUE(image.writeXmpFromPacket());

    EXPECT_EQ(image.xmpPacket(), "");

}



TEST_F(ImageTest_1077, ClearXmpPacket_DoesNotAffectOtherData_1077) {

    std::string initialComment = "Initial Comment";

    image.setComment(initialComment);

    image.clearXmpPacket();

    EXPECT_EQ(image.comment(), initialComment);

}
