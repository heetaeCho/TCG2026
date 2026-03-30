#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "TestProjects/exiv2/src/orfimage.cpp"



using namespace Exiv2;

using testing::NiceMock;

using testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (OpenMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

    MOCK_METHOD(uint32_t, size, (), (const, override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

    MOCK_METHOD(long, tell, (), (const, override));

    MOCK_METHOD(ptrdiff_t, read, (byte* data, long numBytes), (override));

    MOCK_METHOD(ptrdiff_t, write, (const byte* data, long numBytes), (override));

};



class OrfImageTest_1555 : public ::testing::Test {

protected:

    std::unique_ptr<NiceMock<MockBasicIo>> mock_io;



    void SetUp() override {

        mock_io = std::make_unique<NiceMock<MockBasicIo>>();

    }

};



TEST_F(OrfImageTest_1555, CreateInstanceWithValidIo_1555) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(true));

    auto image = newOrfInstance(std::move(mock_io), false);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(OrfImageTest_1555, CreateInstanceWithInvalidIo_1555) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(false));

    auto image = newOrfInstance(std::move(mock_io), false);

    ASSERT_EQ(image.get(), nullptr);

}



TEST_F(OrfImageTest_1555, CreateInstanceWithCreateFlagTrue_1555) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(true));

    auto image = newOrfInstance(std::move(mock_io), true);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(OrfImageTest_1555, CreateInstanceWithCreateFlagFalseAndGoodIo_1555) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(true));

    auto image = newOrfInstance(std::move(mock_io), false);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(OrfImageTest_1555, CreateInstanceWithCreateFlagFalseAndBadIo_1555) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(false));

    auto image = newOrfInstance(std::move(mock_io), false);

    ASSERT_EQ(image.get(), nullptr);

}
