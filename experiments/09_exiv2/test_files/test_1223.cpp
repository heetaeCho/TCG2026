#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "./TestProjects/exiv2/src/jpgimage.cpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(bool, good, (), (override));

};



class JpegImageTest_1223 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIoMock> ioMock_;

    void SetUp() override {

        ioMock_ = std::make_unique<BasicIoMock>();

    }

};



TEST_F(JpegImageTest_1223, NewJpegInstance_ReturnsNonNullPtrWhenGood_1223) {

    EXPECT_CALL(*ioMock_, good()).WillOnce(Return(true));

    auto result = newJpegInstance(std::move(ioMock_), false);

    ASSERT_NE(result, nullptr);

}



TEST_F(JpegImageTest_1223, NewJpegInstance_ReturnsNullPtrWhenNotGood_1223) {

    EXPECT_CALL(*ioMock_, good()).WillOnce(Return(false));

    auto result = newJpegInstance(std::move(ioMock_), false);

    ASSERT_EQ(result, nullptr);

}



TEST_F(JpegImageTest_1223, NewJpegInstance_CreatesInstanceWhenCreateFlagIsTrue_1223) {

    EXPECT_CALL(*ioMock_, good()).WillOnce(Return(true));

    auto result = newJpegInstance(std::move(ioMock_), true);

    ASSERT_NE(result, nullptr);

}



TEST_F(JpegImageTest_1223, NewJpegInstance_DoesNotCreateInstanceWhenIoIsNullptr_1223) {

    BasicIo::UniquePtr nullIo;

    auto result = newJpegInstance(std::move(nullIo), false);

    ASSERT_EQ(result, nullptr);

}
