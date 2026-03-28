#include <gtest/gtest.h>

#include <gmock/gmock.h>



using namespace Exiv2::Internal;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));



    MockIoWrapper(BasicIo& io, const byte* pHeader, size_t size, OffsetWriter* pow)

        : IoWrapper(io, pHeader, size, pow) {}

};



class TiffComponentTest_382 : public ::testing::Test {

protected:

    MockIoWrapper mockIoWrapper;

    TiffComponent tiffComponent{1, IfdId::rootId};



    TiffComponentTest_382()

        : mockIoWrapper(mockBasicIo, nullptr, 0, nullptr) {}



private:

    BasicIo& mockBasicIo;

};



TEST_F(TiffComponentTest_382, WriteImage_ReturnsExpectedSize_382) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(42));



    size_t result = tiffComponent.writeImage(mockIoWrapper, ByteOrder::big);



    EXPECT_EQ(result, 42);

}



TEST_F(TiffComponentTest_382, WriteImage_ZeroSize_ReturnsZero_382) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(0));



    size_t result = tiffComponent.writeImage(mockIoWrapper, ByteOrder::big);



    EXPECT_EQ(result, 0);

}



TEST_F(TiffComponentTest_382, WriteImage_ExceptionHandling_ReturnsZero_382) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Throw(std::runtime_error("Failed to write")));



    size_t result = tiffComponent.writeImage(mockIoWrapper, ByteOrder::big);



    EXPECT_EQ(result, 0);

}



TEST_F(TiffComponentTest_382, WriteImage_LittleEndian_ReturnsExpectedSize_382) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(42));



    size_t result = tiffComponent.writeImage(mockIoWrapper, ByteOrder::little);



    EXPECT_EQ(result, 42);

}



TEST_F(TiffComponentTest_382, WriteImage_CallWrite_ReturnsExpectedSize_382) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(42));



    size_t result = tiffComponent.writeImage(mockIoWrapper, ByteOrder::big);



    EXPECT_EQ(result, 42);

}



TEST_F(TiffComponentTest_382, WriteImage_CallPutb_ReturnsExpectedSize_382) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIoWrapper, putb(::testing::_)).Times(4).WillRepeatedly(::testing::Return(1));



    size_t result = tiffComponent.writeImage(mockIoWrapper, ByteOrder::big);



    EXPECT_EQ(result, 4);

}
