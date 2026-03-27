#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "asfvideo.hpp"



namespace {



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(bool, good, (), (const, override));

};



class AsfVideoTest_1573 : public ::testing::Test {

protected:

    void SetUp() override {

        mockBasicIo = std::make_unique<MockBasicIo>();

    }



    std::unique_ptr<MockBasicIo> mockBasicIo;

};



TEST_F(AsfVideoTest_1573, NewAsfInstanceReturnsNonNullWhenGood_1573) {

    EXPECT_CALL(*mockBasicIo, good()).WillOnce(::testing::Return(true));

    auto image = newAsfInstance(std::move(mockBasicIo), false);

    ASSERT_NE(image, nullptr);

}



TEST_F(AsfVideoTest_1573, NewAsfInstanceReturnsNullWhenNotGood_1573) {

    EXPECT_CALL(*mockBasicIo, good()).WillOnce(::testing::Return(false));

    auto image = newAsfInstance(std::move(mockBasicIo), false);

    ASSERT_EQ(image, nullptr);

}



TEST_F(AsfVideoTest_1573, NewAsfInstanceWithCreateFlagDoesNotAffectGoodCheck_1573) {

    EXPECT_CALL(*mockBasicIo, good()).WillOnce(::testing::Return(true));

    auto image = newAsfInstance(std::move(mockBasicIo), true);

    ASSERT_NE(image, nullptr);

}



TEST_F(AsfVideoTest_1573, NewAsfInstanceWithCreateFlagAndNotGoodReturnsNull_1573) {

    EXPECT_CALL(*mockBasicIo, good()).WillOnce(::testing::Return(false));

    auto image = newAsfInstance(std::move(mockBasicIo), true);

    ASSERT_EQ(image, nullptr);

}



}  // namespace
