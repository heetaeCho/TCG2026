#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (OpenMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, read, (byte* data, size_t count), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t count), (override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

    MOCK_METHOD(long, tell, (), (const, override));

};



class Cr2ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    BasicIo::UniquePtr io_holder;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        io_holder = BasicIo::UniquePtr(mock_io.release());

    }

};



TEST_F(Cr2ImageTest_1747, NewCr2InstanceReturnsNullIfNotGood_1747) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(false));



    Image::UniquePtr image = newCr2Instance(std::move(io_holder), false);

    EXPECT_EQ(image, nullptr);

}



TEST_F(Cr2ImageTest_1747, NewCr2InstanceSucceedsIfGood_1747) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(true));



    Image::UniquePtr image = newCr2Instance(std::move(io_holder), false);

    EXPECT_NE(image, nullptr);

}



TEST_F(Cr2ImageTest_1747, NewCr2InstanceDoesNotOpenWhenCreateFalse_1747) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_io, open(_)).Times(0);



    Image::UniquePtr image = newCr2Instance(std::move(io_holder), false);

}



TEST_F(Cr2ImageTest_1747, NewCr2InstanceOpensWhenCreateTrue_1747) {

    EXPECT_CALL(*mock_io, good()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_io, open(OpenMode::create)).Times(1);



    Image::UniquePtr image = newCr2Instance(std::move(io_holder), true);

}
