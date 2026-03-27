#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tgaimage.cpp"



using namespace Exiv2;



class TgaImageTest_1233 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image::UniquePtr image;



    void SetUp() override {

        io = BasicIo::createMemIo();

    }



    void TearDown() override {

        io.reset();

        image.reset();

    }

};



TEST_F(TgaImageTest_1233, NewTgaInstance_Success_1233) {

    image = newTgaInstance(std::move(io), false);

    EXPECT_NE(image, nullptr);

}



TEST_F(TgaImageTest_1233, NewTgaInstance_CreateFlagIgnored_1233) {

    image = newTgaInstance(BasicIo::createMemIo(), true);

    EXPECT_NE(image, nullptr);

}



TEST_F(TgaImageTest_1233, NewTgaInstance_NullptrOnFailure_1233) {

    io.reset(); // Simulate failure by invalidating the io

    image = newTgaInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);

}
