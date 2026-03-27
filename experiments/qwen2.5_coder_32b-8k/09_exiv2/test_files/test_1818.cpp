#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::NiceMock;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (AccessMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(uint32_t, read, (byte* data, uint32_t length), (override));

    MOCK_METHOD(uint32_t, write, (const byte* data, uint32_t length), (override));

    MOCK_METHOD(void, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(int64_t, tell, (), (const, override));

};



class CrwImageTest_1818 : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mockIo;

};



TEST_F(CrwImageTest_1818, NewCrwInstance_ReturnsNonNullPointer_WhenGood_1818) {

    EXPECT_CALL(mockIo, good()).WillOnce(::testing::Return(true));

    auto result = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), false);

    ASSERT_NE(result, nullptr);

}



TEST_F(CrwImageTest_1818, NewCrwInstance_ReturnsNullPointer_WhenNotGood_1818) {

    EXPECT_CALL(mockIo, good()).WillOnce(::testing::Return(false));

    auto result = newCrwInstance(std::make_unique<MockBasicIo>(mockIo), false);

    ASSERT_EQ(result, nullptr);

}



TEST_F(CrwImageTest_1818, NewCrwInstance_CallsGoodMethodOnIo_1818) {

    EXPECT_CALL(mockIo, good()).Times(1);

    newCrwInstance(std::make_unique<MockBasicIo>(mockIo), false);

}
