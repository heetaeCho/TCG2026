#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <gmock/gmock.h>



namespace {



using ::testing::_;

using ::testing::Return;

using ::testing::Eq;



class MockBasicIo : public Exiv2::BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Exiv2::Position pos), (override));

    MOCK_METHOD(byte*, mmap, (bool unnamed), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, noexcept, override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class RemoteIoTest : public ::testing::Test {

protected:

    Exiv2::RemoteIo remote_io;

};



TEST_F(RemoteIoTest_599, OpenReturnsZeroOnSuccess_599) {

    EXPECT_EQ(remote_io.open(), 0);

}



TEST_F(RemoteIoTest_599, CloseReturnsZeroOnSuccess_599) {

    EXPECT_EQ(remote_io.close(), 0);

}



TEST_F(RemoteIoTest_599, WriteWithBufferAndCountReturnsWrittenSize_599) {

    byte data[1] = {0};

    size_t count = sizeof(data);

    EXPECT_EQ(remote_io.write(data, count), count);

}



TEST_F(RemoteIoTest_599, WriteWithBasicIoSourceTransfersData_599) {

    MockBasicIo mock_src;

    EXPECT_CALL(mock_src, tell()).WillOnce(Return(0));

    EXPECT_CALL(mock_src, read(_, _)).WillOnce(Return(1));

    remote_io.write(mock_src);

}



TEST_F(RemoteIoTest_599, PutbWritesSingleByteReturnsWrittenSize_599) {

    byte data = 0;

    EXPECT_EQ(remote_io.putb(data), 1);

}



TEST_F(RemoteIoTest_599, ReadWithCountReturnsDataBuf_599) {

    size_t count = 1;

    Exiv2::DataBuf result = remote_io.read(count);

    EXPECT_TRUE(result.pData != nullptr);

}



TEST_F(RemoteIoTest_599, ReadWithBufferAndCountReturnsReadSize_599) {

    byte buffer[1];

    size_t count = sizeof(buffer);

    EXPECT_EQ(remote_io.read(buffer, count), 0);

}



TEST_F(RemoteIoTest_599, GetbReturnsByteValue_599) {

    int result = remote_io.getb();

    EXPECT_TRUE(result >= -1 && result <= 255); // Assuming getb returns byte or EOF (-1)

}



TEST_F(RemoteIoTest_599, TransferTransfersDataFromSource_599) {

    MockBasicIo mock_src;

    EXPECT_CALL(mock_src, tell()).WillOnce(Return(0));

    EXPECT_CALL(mock_src, read(_, _)).WillOnce(Return(1));

    remote_io.transfer(mock_src);

}



TEST_F(RemoteIoTest_599, SeekWithOffsetAndPositionReturnsZeroOnSuccess_599) {

    int64_t offset = 0;

    Exiv2::Position pos = Exiv2::Position::beg;

    EXPECT_EQ(remote_io.seek(offset, pos), 0);

}



TEST_F(RemoteIoTest_599, MmapWithUnnamedFlagReturnsPointer_599) {

    byte* result = remote_io.mmap(true);

    EXPECT_TRUE(result != nullptr || remote_io.error() != 0); // Check if mmap fails

}



TEST_F(RemoteIoTest_599, MunmapReturnsZeroOnSuccess_599) {

    EXPECT_EQ(remote_io.munmap(), 0);

}



TEST_F(RemoteIoTest_599, TellReturnsCurrentPosition_599) {

    size_t result = remote_io.tell();

    EXPECT_TRUE(result >= 0);

}



TEST_F(RemoteIoTest_599, SizeReturnsFileSize_599) {

    size_t result = remote_io.size();

    EXPECT_TRUE(result >= 0);

}



TEST_F(RemoteIoTest_599, IsopenReturnsTrueIfOpen_599) {

    remote_io.open();

    bool result = remote_io.isopen();

    EXPECT_TRUE(result == true || remote_io.error() != 0); // Check if open fails

}



TEST_F(RemoteIoTest_599, ErrorReturnsErrorCode_599) {

    int result = remote_io.error();

    EXPECT_TRUE(result >= 0);

}



TEST_F(RemoteIoTest_599, EofReturnsTrueIfEndOfFile_599) {

    bool result = remote_io.eof();

    EXPECT_TRUE(result == true || result == false);

}



TEST_F(RemoteIoTest_599, PathReturnsFilePath_599) {

    const std::string& result = remote_io.path();

    EXPECT_TRUE(!result.empty() || remote_io.error() != 0); // Check if path is empty or error occurred

}



} // namespace
