#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <gmock/gmock.h>



namespace Exiv2 {

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(int, open, (), (override));

        MOCK_METHOD(int, close, (), (override));

        MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

        MOCK_METHOD(size_t, write, (BasicIo & src), (override));

        MOCK_METHOD(int, putb, (byte data), (override));

        MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

        MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

        MOCK_METHOD(int, getb, (), (override));

        MOCK_METHOD(void, transfer, (BasicIo & src), (override));

        MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

        MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

        MOCK_METHOD(int, munmap, (), (override));

        MOCK_METHOD(const size_t, tell, (), (const override));

        MOCK_METHOD(const size_t, size, (), (const override));

        MOCK_METHOD(const bool, isopen, (), (const override));

        MOCK_METHOD(const int, error, (), (const override));

        MOCK_METHOD(const bool, eof, (), (const override));

        MOCK_METHOD(const std::string &, path, (), (const override));

    };

}



using namespace Exiv2;



class BasicIoTest_544 : public ::testing::Test {

protected:

    MockBasicIo mockBasicIo;

};



TEST_F(BasicIoTest_544, ReadOrThrow_SuccessfulRead_544) {

    const size_t bufferSize = 10;

    byte buffer[bufferSize];

    size_t bytesToRead = 5;



    EXPECT_CALL(mockBasicIo, read(buffer, bytesToRead)).WillOnce(::testing::Return(bytesToRead));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));



    mockBasicIo.readOrThrow(buffer, bytesToRead, ErrorCode::kerFailedToRead);

}



TEST_F(BasicIoTest_544, ReadOrThrow_NotEnoughBytesRead_544) {

    const size_t bufferSize = 10;

    byte buffer[bufferSize];

    size_t bytesToRead = 5;



    EXPECT_CALL(mockBasicIo, read(buffer, bytesToRead)).WillOnce(::testing::Return(bytesToRead - 1));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));



    EXPECT_THROW(mockBasicIo.readOrThrow(buffer, bytesToRead, ErrorCode::kerFailedToRead), Error);

}



TEST_F(BasicIoTest_544, ReadOrThrow_ErrorOccurred_544) {

    const size_t bufferSize = 10;

    byte buffer[bufferSize];

    size_t bytesToRead = 5;



    EXPECT_CALL(mockBasicIo, read(buffer, bytesToRead)).WillOnce(::testing::Return(bytesToRead));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(1));



    EXPECT_THROW(mockBasicIo.readOrThrow(buffer, bytesToRead, ErrorCode::kerFailedToRead), Error);

}



TEST_F(BasicIoTest_544, ReadOrThrow_ZeroBytesRead_544) {

    const size_t bufferSize = 10;

    byte buffer[bufferSize];

    size_t bytesToRead = 0;



    EXPECT_CALL(mockBasicIo, read(buffer, bytesToRead)).WillOnce(::testing::Return(bytesToRead));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));



    mockBasicIo.readOrThrow(buffer, bytesToRead, ErrorCode::kerFailedToRead);

}



TEST_F(BasicIoTest_544, ReadOrThrow_LargeBytesRead_544) {

    const size_t bufferSize = 10;

    byte buffer[bufferSize];

    size_t bytesToRead = bufferSize;



    EXPECT_CALL(mockBasicIo, read(buffer, bytesToRead)).WillOnce(::testing::Return(bytesToRead));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));



    mockBasicIo.readOrThrow(buffer, bytesToRead, ErrorCode::kerFailedToRead);

}
