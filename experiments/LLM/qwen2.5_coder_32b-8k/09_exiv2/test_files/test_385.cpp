#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

namespace Internal {



class MockIoWrapper : public IoWrapper {

public:

    using IoWrapper::IoWrapper;

    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));

};



class MockIfd : public TiffComponent {

public:

    using TiffComponent::TiffComponent;

    MOCK_METHOD(size_t, writeImage, (IoWrapper& ioWrapper, ByteOrder byteOrder), (const, override));

};



class TiffSubIfdTest_385 : public ::testing::Test {

protected:

    MockIoWrapper mockIoWrapper;

    std::vector<std::shared_ptr<MockIfd>> ifds;



    TiffSubIfdTest_385() 

        : mockIoWrapper(BasicIo::createMemIo(), nullptr, 0, nullptr), tiffSubIfd(123, IfdId::exif, IfdId::subIfd) {

        for (int i = 0; i < 3; ++i) {

            ifds.push_back(std::make_shared<MockIfd>());

            tiffSubIfd.ifds_.push_back(ifds.back());

        }

    }



    TiffSubIfd tiffSubIfd;

};



TEST_F(TiffSubIfdTest_385, DoWriteImage_NormalOperation_385) {

    EXPECT_CALL(*ifds[0], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(10));

    EXPECT_CALL(*ifds[1], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(20));

    EXPECT_CALL(*ifds[2], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(30));



    size_t result = tiffSubIfd.doWriteImage(mockIoWrapper, ByteOrder::big);



    ASSERT_EQ(result, 60);

}



TEST_F(TiffSubIfdTest_385, DoWriteImage_NoIfds_385) {

    tiffSubIfd.ifds_.clear();



    size_t result = tiffSubIfd.doWriteImage(mockIoWrapper, ByteOrder::big);



    ASSERT_EQ(result, 0);

}



TEST_F(TiffSubIfdTest_385, DoWriteImage_AllZeroSizes_385) {

    EXPECT_CALL(*ifds[0], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(0));

    EXPECT_CALL(*ifds[1], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(0));

    EXPECT_CALL(*ifds[2], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(0));



    size_t result = tiffSubIfd.doWriteImage(mockIoWrapper, ByteOrder::big);



    ASSERT_EQ(result, 0);

}



TEST_F(TiffSubIfdTest_385, DoWriteImage_MixedSizes_385) {

    EXPECT_CALL(*ifds[0], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(15));

    EXPECT_CALL(*ifds[1], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(0));

    EXPECT_CALL(*ifds[2], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(25));



    size_t result = tiffSubIfd.doWriteImage(mockIoWrapper, ByteOrder::big);



    ASSERT_EQ(result, 40);

}



TEST_F(TiffSubIfdTest_385, DoWriteImage_LargeSizes_385) {

    EXPECT_CALL(*ifds[0], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(100000));

    EXPECT_CALL(*ifds[1], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(200000));

    EXPECT_CALL(*ifds[2], writeImage(::testing::Ref(mockIoWrapper), ByteOrder::big)).WillOnce(::testing::Return(300000));



    size_t result = tiffSubIfd.doWriteImage(mockIoWrapper, ByteOrder::big);



    ASSERT_EQ(result, 600000);

}



} // namespace Internal

} // namespace Exiv2
