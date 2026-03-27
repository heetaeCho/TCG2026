#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/jp2image.cpp"

#include "exiv2/image.hpp"



using namespace Exiv2;

using testing::NiceMock;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (AccessMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

    MOCK_METHOD(uint64_t, size, (), (const, override));

    MOCK_METHOD(bool, seek, (uint64_t offset, Position pos), (override));

    MOCK_METHOD(uint64_t, tell, (), (const, override));

    MOCK_METHOD(bool, read, (byte* data, long numBytes), (override));

    MOCK_METHOD(bool, write, (const byte* data, long numBytes), (override));

};



class Jp2InstanceTest : public testing::Test {

protected:

    NiceMock<MockBasicIo> mockIo;

};



TEST_F(Jp2InstanceTest_88, CreateValidJp2Image_88) {

    EXPECT_CALL(mockIo, good()).WillOnce(testing::Return(true));

    auto image = newJp2Instance(BasicIo::UniquePtr(&mockIo, [](BasicIo*){}), false);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(Jp2InstanceTest_88, CreateInvalidJp2Image_88) {

    EXPECT_CALL(mockIo, good()).WillOnce(testing::Return(false));

    auto image = newJp2Instance(BasicIo::UniquePtr(&mockIo, [](BasicIo*){}), false);

    ASSERT_EQ(image.get(), nullptr);

}



TEST_F(Jp2InstanceTest_88, CreateWithCreateFlagTrue_88) {

    EXPECT_CALL(mockIo, good()).WillOnce(testing::Return(true));

    auto image = newJp2Instance(BasicIo::UniquePtr(&mockIo, [](BasicIo*){}), true);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(Jp2InstanceTest_88, CreateWithCreateFlagFalse_88) {

    EXPECT_CALL(mockIo, good()).WillOnce(testing::Return(true));

    auto image = newJp2Instance(BasicIo::UniquePtr(&mockIo, [](BasicIo*){}), false);

    ASSERT_NE(image.get(), nullptr);

}
