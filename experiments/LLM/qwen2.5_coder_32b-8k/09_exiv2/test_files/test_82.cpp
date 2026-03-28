#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "riffvideo.cpp"

#include "image.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class RiffVideoTest_82 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock BasicIo object

        ioMock = std::make_unique<BasicIoMock>();

        io.reset(ioMock.release());

    }



    void TearDown() override {

        io.reset();

    }



    struct BasicIoMock : public BasicIo {

        MOCK_METHOD(bool, good, (), (const));

        MOCK_METHOD(void, close, (), ());

        // Add other necessary mock methods if needed

    };



    std::unique_ptr<BasicIo> io;

    std::unique_ptr<BasicIoMock> ioMock;

};



TEST_F(RiffVideoTest_82, NewRiffInstance_ReturnsValidPointerWhenGood_82) {

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(true));

    

    Image::UniquePtr result = newRiffInstance(std::move(io), false);

    ASSERT_NE(result.get(), nullptr);

}



TEST_F(RiffVideoTest_82, NewRiffInstance_ReturnsNullPointerWhenNotGood_82) {

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(false));

    

    Image::UniquePtr result = newRiffInstance(std::move(io), false);

    ASSERT_EQ(result.get(), nullptr);

}



TEST_F(RiffVideoTest_82, NewRiffInstance_ClosesIoWhenNotGood_82) {

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(false));

    EXPECT_CALL(*ioMock, close());

    

    Image::UniquePtr result = newRiffInstance(std::move(io), false);

}



TEST_F(RiffVideoTest_82, NewRiffInstance_CreatesRiffVideoInstanceWhenGood_82) {

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(true));

    

    Image::UniquePtr result = newRiffInstance(std::move(io), false);

    ASSERT_NE(result.get(), nullptr);

    RiffVideo* riffVideo = dynamic_cast<RiffVideo*>(result.get());

    ASSERT_NE(riffVideo, nullptr);

}



TEST_F(RiffVideoTest_82, NewRiffInstance_DoesNotCreateRiffVideoInstanceWhenNotGood_82) {

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(false));

    

    Image::UniquePtr result = newRiffInstance(std::move(io), false);

    ASSERT_EQ(result.get(), nullptr);

}
