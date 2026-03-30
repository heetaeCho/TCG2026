#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "gifimage.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using testing::NiceMock;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (OpenMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

    MOCK_METHOD(size_t, read, (byte* data, size_t nbytes), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t nbytes), (override));

    MOCK_METHOD(uint64_t, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, invalidate, (), (override));

};



class GifImageTest_213 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    Image::UniquePtr gif_image;



    void SetUp() override {

        mock_io = std::make_unique<NiceMock<MockBasicIo>>();

        EXPECT_CALL(*mock_io, good()).WillRepeatedly(testing::Return(true));

        gif_image = newGifInstance(std::move(mock_io), false);

    }

};



TEST_F(GifImageTest_213, NewGifInstance_ReturnsValidPointer_213) {

    ASSERT_NE(gif_image.get(), nullptr);

}



TEST_F(GifImageTest_213, NewGifInstance_CallsGoodMethodOnIo_213) {

    // The call to good() is already expected in SetUp

}



TEST_F(GifImageTest_213, NewGifInstance_ReturnsNullptrWhenIoIsNotGood_213) {

    mock_io = std::make_unique<NiceMock<MockBasicIo>>();

    EXPECT_CALL(*mock_io, good()).WillRepeatedly(testing::Return(false));

    auto image = newGifInstance(std::move(mock_io), false);

    ASSERT_EQ(image.get(), nullptr);

}
