#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "rafimage.cpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::ByMove;



class RafImageTest_223 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> basicIoMock;

    

    void SetUp() override {

        basicIoMock = std::make_unique<BasicIo>();

    }

};



TEST_F(RafImageTest_223, NewRafInstance_ReturnsNonNullPointerForValidInput_223) {

    EXPECT_CALL(*basicIoMock, good()).WillRepeatedly(Return(true));

    

    auto image = newRafInstance(std::move(basicIoMock), false);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(RafImageTest_223, NewRafInstance_ReturnsNullPointerForInvalidInput_223) {

    EXPECT_CALL(*basicIoMock, good()).WillRepeatedly(Return(false));

    

    auto image = newRafInstance(std::move(basicIoMock), false);

    ASSERT_EQ(image.get(), nullptr);

}



TEST_F(RafImageTest_223, NewRafInstance_HandlesCreateFlagTrue_223) {

    EXPECT_CALL(*basicIoMock, good()).WillRepeatedly(Return(true));

    

    auto image = newRafInstance(std::move(basicIoMock), true);

    ASSERT_NE(image.get(), nullptr);

}



TEST_F(RafImageTest_223, NewRafInstance_HandlesCreateFlagFalse_223) {

    EXPECT_CALL(*basicIoMock, good()).WillRepeatedly(Return(true));

    

    auto image = newRafInstance(std::move(basicIoMock), false);

    ASSERT_NE(image.get(), nullptr);

}
