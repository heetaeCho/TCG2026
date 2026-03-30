#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/tiffimage.hpp"



namespace {



using namespace testing;

using namespace Exiv2;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

    MOCK_METHOD(size_t, read, (byte*, size_t), (override));

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    MOCK_METHOD(BasicIo::AutoPtr, clone, (), (const, override));

    MOCK_METHOD(size_t, tellg, (), (const, override));

    MOCK_METHOD(void, seekg, (long, PositionFrom p), (override));

    MOCK_METHOD(size_t, size, (), (const, override));

};



class TiffImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        ioMock = std::make_unique<BasicIoMock>();

        EXPECT_CALL(*ioMock, good()).WillRepeatedly(Return(true));

    }



    std::unique_ptr<BasicIoMock> ioMock;

};



TEST_F(TiffImageTest, NewTiffInstance_ReturnsValidPointer_1736) {

    auto image = newTiffInstance(std::move(ioMock), false);

    EXPECT_NE(image, nullptr);

}



TEST_F(TiffImageTest, NewTiffInstance_GoodCalledTwice_1736) {

    InSequence seq;

    EXPECT_CALL(*ioMock, good()).WillOnce(Return(true)).WillOnce(Return(true));

    

    auto image = newTiffInstance(std::move(ioMock), false);

    EXPECT_NE(image, nullptr);

}



TEST_F(TiffImageTest, NewTiffInstance_ReturnsNullIfNotGood_1736) {

    EXPECT_CALL(*ioMock, good()).WillRepeatedly(Return(false));



    auto image = newTiffInstance(std::move(ioMock), false);

    EXPECT_EQ(image, nullptr);

}



}  // namespace
