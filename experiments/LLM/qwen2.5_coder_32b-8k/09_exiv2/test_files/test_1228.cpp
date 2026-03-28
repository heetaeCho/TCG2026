#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "jpgimage.cpp"



using namespace Exiv2;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD0(open, bool());

    MOCK_METHOD0(close, void());

    MOCK_CONST_METHOD0(good, bool());

    MOCK_CONST_METHOD0(tellg, size_t());

    MOCK_METHOD1(seekg, bool(size_t));

    MOCK_METHOD2(read, long(char* buf, long len));

    MOCK_METHOD2(write, long(const char* buf, long len));

};



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIoMock> mockIo_;

    BasicIo::UniquePtr io_;

    bool create_ = false;



    void SetUp() override {

        mockIo_ = std::make_unique<BasicIoMock>();

        io_ = BasicIo::UniquePtr(mockIo_.release());

    }

};



TEST_F(ImageTest, NewExvInstance_ReturnsValidPointer_1228) {

    EXPECT_CALL(*mockIo_, good()).WillOnce(::testing::Return(true));

    auto image = newExvInstance(std::move(io_), create_);

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(ImageTest, NewExvInstance_ReturnsNullptrForInvalidIo_1228) {

    EXPECT_CALL(*mockIo_, good()).WillOnce(::testing::Return(false));

    auto image = newExvInstance(std::move(io_), create_);

    EXPECT_EQ(image.get(), nullptr);

}



TEST_F(ImageTest, NewExvInstance_CallsGoodOnBasicIo_1228) {

    EXPECT_CALL(*mockIo_, good()).Times(1).WillOnce(::testing::Return(true));

    auto image = newExvInstance(std::move(io_), create_);

}



TEST_F(ImageTest, NewExvInstance_TransfersOwnershipOfBasicIo_1228) {

    EXPECT_CALL(*mockIo_, good()).WillOnce(::testing::Return(true));

    auto image = newExvInstance(std::move(io_), create_);

    EXPECT_EQ(image->io().good(), true);

}
