#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "quicktimevideo.cpp"

#include "image.hpp"

#include "basicio.hpp"



using namespace Exiv2;



class QuickTimeVideoTest_661 : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<BasicIo>();

    }



    BasicIo::UniquePtr io;

};



TEST_F(QuickTimeVideoTest_661, NewQTimeInstance_ReturnsNonNullForGoodImage_661) {

    EXPECT_CALL(*io, good()).WillOnce(::testing::Return(true));

    auto image = newQTimeInstance(std::move(io), false);

    EXPECT_NE(image, nullptr);

}



TEST_F(QuickTimeVideoTest_661, NewQTimeInstance_ReturnsNullForBadImage_661) {

    EXPECT_CALL(*io, good()).WillOnce(::testing::Return(false));

    auto image = newQTimeInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);

}



TEST_F(QuickTimeVideoTest_661, NewQTimeInstance_CreatesUniquePointer_661) {

    EXPECT_CALL(*io, good()).WillOnce(::testing::Return(true));

    auto image = newQTimeInstance(std::move(io), false);

    EXPECT_TRUE(image.get() != nullptr);

}



TEST_F(QuickTimeVideoTest_661, NewQTimeInstance_DoesNotCreateImageWhenIoIsNull_661) {

    io.reset();

    auto image = newQTimeInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);

}
