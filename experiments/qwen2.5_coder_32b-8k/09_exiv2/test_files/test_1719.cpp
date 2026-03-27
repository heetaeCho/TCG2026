#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "xmpsidecar.cpp"



using namespace Exiv2;

using testing::NiceMock;

using testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (OpenMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(size_t, read, (byte* data, size_t count), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t count), (override));

    MOCK_METHOD(bool, seek, (int64_t offset, Position whence), (override));

    MOCK_METHOD(int64_t, tell, (), (const, override));

};



class XmpSidecarTest_1719 : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;



    void SetUp() override {

        // Set up the mock object behavior if necessary

    }

};



TEST_F(XmpSidecarTest_1719, NewXmpInstanceWithCreateFalse_ReturnsValidImagePtr_1719) {

    auto image = newXmpInstance(std::make_unique<MockBasicIo>(), false);

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(XmpSidecarTest_1719, NewXmpInstanceWithCreateTrue_ReturnsValidImagePtr_1719) {

    auto image = newXmpInstance(std::make_unique<MockBasicIo>(), true);

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(XmpSidecarTest_1719, NewXmpInstanceWithInvalidIo_ReturnsNullPtr_1719) {

    BasicIo::UniquePtr invalid_io(nullptr);

    auto image = newXmpInstance(std::move(invalid_io), false);

    EXPECT_EQ(image.get(), nullptr);

}



TEST_F(XmpSidecarTest_1719, NewXmpInstanceWithGoodReturningFalse_ReturnsNullPtr_1719) {

    MockBasicIo mock_io;

    EXPECT_CALL(mock_io, good()).WillOnce(testing::Return(false));

    auto image = newXmpInstance(std::make_unique<MockBasicIo>(), false);

    EXPECT_EQ(image.get(), nullptr);

}



TEST_F(XmpSidecarTest_1719, NewXmpInstanceWithGoodReturningTrue_ReturnsValidImagePtr_1719) {

    MockBasicIo mock_io;

    EXPECT_CALL(mock_io, good()).WillOnce(testing::Return(true));

    auto image = newXmpInstance(std::make_unique<MockBasicIo>(), false);

    EXPECT_NE(image.get(), nullptr);

}
