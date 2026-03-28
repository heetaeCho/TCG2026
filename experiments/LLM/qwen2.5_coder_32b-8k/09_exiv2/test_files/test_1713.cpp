#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/pgfimage.hpp"

#include "exiv2/image.hpp"



using namespace Exiv2;

using ::testing::NiceMock;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (AccessMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

    MOCK_METHOD(size_t, read, (byte* data, size_t count), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t count), (override));

    MOCK_METHOD(void, seek, (int64_t offset, Position whence), (override));

    MOCK_METHOD(int64_t, tell, (), (const, override));

};



TEST(newPgfInstanceTest_1713, ValidIoCreatesImage_1713) {

    auto mockIo = std::make_unique<NiceMock<MockBasicIo>>();

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(true));



    Image::UniquePtr image = newPgfInstance(std::move(mockIo), false);

    ASSERT_NE(image.get(), nullptr);

}



TEST(newPgfInstanceTest_1713, InvalidIoReturnsNull_1713) {

    auto mockIo = std::make_unique<NiceMock<MockBasicIo>>();

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(false));



    Image::UniquePtr image = newPgfInstance(std::move(mockIo), false);

    ASSERT_EQ(image.get(), nullptr);

}



TEST(newPgfInstanceTest_1713, CreateFlagTrueDoesNotThrow_1713) {

    auto mockIo = std::make_unique<NiceMock<MockBasicIo>>();

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(true));



    Image::UniquePtr image = newPgfInstance(std::move(mockIo), true);

    ASSERT_NE(image.get(), nullptr);

}



TEST(newPgfInstanceTest_1713, CreateFlagFalseDoesNotThrow_1713) {

    auto mockIo = std::make_unique<NiceMock<MockBasicIo>>();

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(true));



    Image::UniquePtr image = newPgfInstance(std::move(mockIo), false);

    ASSERT_NE(image.get(), nullptr);

}
