#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "rw2image.cpp"  // Assuming the header file is included here for the interface



using namespace Exiv2;

using testing::_;

using testing::Return;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(bool, good, (), (const, override));

};



TEST_F(BasicIoTest_1582, NewRw2Instance_ReturnsValidPointerWhenGoodIsTrue_1582) {

    auto io = std::make_unique<BasicIoMock>();

    EXPECT_CALL(*io, good()).WillOnce(Return(true));



    Image::UniquePtr image = newRw2Instance(std::move(io), false);

    ASSERT_NE(image, nullptr);

}



TEST_F(BasicIoTest_1582, NewRw2Instance_ReturnsNullPointerWhenGoodIsFalse_1582) {

    auto io = std::make_unique<BasicIoMock>();

    EXPECT_CALL(*io, good()).WillOnce(Return(false));



    Image::UniquePtr image = newRw2Instance(std::move(io), false);

    ASSERT_EQ(image, nullptr);

}



TEST_F(BasicIoTest_1582, NewRw2Instance_HandlesNullInputPointer_1582) {

    BasicIo::UniquePtr io = nullptr;

    

    Image::UniquePtr image = newRw2Instance(std::move(io), false);

    ASSERT_EQ(image, nullptr);

}



TEST_F(BasicIoTest_1582, NewRw2Instance_IgnoresCreateParameter_1582) {

    auto io = std::make_unique<BasicIoMock>();

    EXPECT_CALL(*io, good()).WillOnce(Return(true));



    Image::UniquePtr image = newRw2Instance(std::move(io), true);

    ASSERT_NE(image, nullptr);

}
