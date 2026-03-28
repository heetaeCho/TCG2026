#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "mrwimage.cpp"



using namespace Exiv2;

using ::testing::Return;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(void, open, (AccessMode mode), (override));

    MOCK_METHOD(bool, good, (), (const override));

    MOCK_METHOD(void, close, (), (override));

};



class MrwImageTest_983 : public ::testing::Test {

protected:

    void SetUp() override {

        ioMock = std::make_unique<BasicIoMock>();

    }



    std::unique_ptr<BasicIoMock> ioMock;

};



TEST_F(MrwImageTest_983, CreateInstanceWithGoodIo_983) {

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(true));

    auto image = newMrwInstance(std::move(ioMock), false);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(MrwImageTest_983, CreateInstanceWithBadIo_983) {

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(false));

    auto image = newMrwInstance(std::move(ioMock), false);

    ASSERT_EQ(image.get(), nullptr);

}



TEST_F(MrwImageTest_983, CreateInstanceWithCreateFlagTrue_983) {

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(true));

    auto image = newMrwInstance(std::move(ioMock), true);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(MrwImageTest_983, CreateInstanceWithNullIo_983) {

    BasicIo::UniquePtr io(nullptr);

    auto image = newMrwInstance(std::move(io), false);

    ASSERT_EQ(image.get(), nullptr);

}
