#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class BasicIoTest_545 : public ::testing::Test {

protected:

    BasicIoMock mockBasicIo;

};



TEST_F(BasicIoTest_545, SeekOrThrow_NormalOperation_545) {

    EXPECT_CALL(mockBasicIo, seek(100, Position::beg)).WillOnce(Return(0));

    ASSERT_NO_THROW(mockBasicIo.seekOrThrow(100, Position::beg, ErrorCode::kerFailedToSeek));

}



TEST_F(BasicIoTest_545, SeekOrThrow_SeekFails_545) {

    EXPECT_CALL(mockBasicIo, seek(100, Position::beg)).WillOnce(Return(-1));

    ASSERT_THROW(mockBasicIo.seekOrThrow(100, Position::beg, ErrorCode::kerFailedToSeek), Error);

}



TEST_F(BasicIoTest_545, SeekOrThrow_BoundaryCondition_StartOfFile_545) {

    EXPECT_CALL(mockBasicIo, seek(0, Position::beg)).WillOnce(Return(0));

    ASSERT_NO_THROW(mockBasicIo.seekOrThrow(0, Position::beg, ErrorCode::kerFailedToSeek));

}



TEST_F(BasicIoTest_545, SeekOrThrow_BoundaryCondition_EndOfFile_545) {

    EXPECT_CALL(mockBasicIo, seek(-1, Position::end)).WillOnce(Return(0));

    ASSERT_NO_THROW(mockBasicIo.seekOrThrow(-1, Position::end, ErrorCode::kerFailedToSeek));

}



TEST_F(BasicIoTest_545, SeekOrThrow_ErrorCode_Verification_545) {

    EXPECT_CALL(mockBasicIo, seek(100, Position::beg)).WillOnce(Return(-1));

    try {

        mockBasicIo.seekOrThrow(100, Position::beg, ErrorCode::kerFailedToSeek);

    } catch (const Error &e) {

        EXPECT_EQ(e.code(), ErrorCode::kerFailedToSeek);

    }

}
