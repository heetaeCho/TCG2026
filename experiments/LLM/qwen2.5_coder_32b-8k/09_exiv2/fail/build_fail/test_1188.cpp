#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/psdimage.cpp"



using namespace Exiv2;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(bool, good, (), (const, override));

};



class PsdImageTest_1188 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

    }



    std::unique_ptr<MockBasicIo> mock_io;

};



TEST_F(PsdImageTest_1188, NewPsdInstanceReturnsNonNullWhenGood_1188) {

    EXPECT_CALL(*mock_io, good()).WillOnce(Return(true));

    auto image = newPsdInstance(std::move(mock_io), false);

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(PsdImageTest_1188, NewPsdInstanceReturnsNullWhenNotGood_1188) {

    EXPECT_CALL(*mock_io, good()).WillOnce(Return(false));

    auto image = newPsdInstance(std::move(mock_io), false);

    EXPECT_EQ(image.get(), nullptr);

}



TEST_F(PsdImageTest_1188, NewPsdInstanceHandlesCreateFlagFalse_1188) {

    EXPECT_CALL(*mock_io, good()).WillOnce(Return(true));

    auto image = newPsdInstance(std::move(mock_io), false);

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(PsdImageTest_1188, NewPsdInstanceHandlesCreateFlagTrue_1188) {

    mock_io.reset(new MockBasicIo());

    EXPECT_CALL(*mock_io, good()).WillOnce(Return(true));

    auto image = newPsdInstance(std::move(mock_io), true);

    EXPECT_NE(image.get(), nullptr);

}
