#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "bmpimage.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::NiceMock;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

};



class BmpImageTest_1041 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    

    void SetUp() override {

        mock_io = std::make_unique<NiceMock<MockBasicIo>>();

    }

};



TEST_F(BmpImageTest_1041, GoodIo_ReturnsValidInstance_1041) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(true));



    auto image = newBmpInstance(std::move(mock_io), false);



    ASSERT_NE(image, nullptr);

}



TEST_F(BmpImageTest_1041, BadIo_ReturnsNullptr_1041) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(false));



    auto image = newBmpInstance(std::move(mock_io), false);



    ASSERT_EQ(image, nullptr);

}



TEST_F(BmpImageTest_1041, CreateFlag_DoesNotAffectGoodCheck_1041) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(true));



    auto image = newBmpInstance(std::move(mock_io), true);



    ASSERT_NE(image, nullptr);

}



TEST_F(BmpImageTest_1041, CreateFlagWithBadIo_ReturnsNullptr_1041) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(false));



    auto image = newBmpInstance(std::move(mock_io), true);



    ASSERT_EQ(image, nullptr);

}
